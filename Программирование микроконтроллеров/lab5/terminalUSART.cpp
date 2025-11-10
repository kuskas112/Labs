#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <atomic>
#include <conio.h>

class SerialTerminal {
private:
    HANDLE hSerial;
    std::atomic<bool> running;
    std::thread readThread;

public:
    SerialTerminal() : hSerial(INVALID_HANDLE_VALUE), running(false) {}

    ~SerialTerminal() {
        disconnect();
    }

    // Подключение к COM-порту
    bool connect(const std::string& portName, DWORD baudRate = 4800) {
        // Форматируем имя порта: "\\.\COM4"
        std::string fullPortName = "\\\\.\\" + portName;

        hSerial = CreateFileA(
            fullPortName.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

        if (hSerial == INVALID_HANDLE_VALUE) {
            std::cout << "Ошибка: Не удалось открыть порт " << portName << std::endl;
            return false;
        }

        // Настройка параметров порта
        DCB dcbSerialParams = { 0 };
        dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

        if (!GetCommState(hSerial, &dcbSerialParams)) {
            std::cout << "Ошибка получения параметров порта" << std::endl;
            return false;
        }

        dcbSerialParams.BaudRate = baudRate;
        dcbSerialParams.ByteSize = 8;
        dcbSerialParams.StopBits = ONESTOPBIT;
        dcbSerialParams.Parity = NOPARITY;

        if (!SetCommState(hSerial, &dcbSerialParams)) {
            std::cout << "Ошибка установки параметров порта" << std::endl;
            return false;
        }

        // Настройка таймаутов
        COMMTIMEOUTS timeouts = { 0 };
        timeouts.ReadIntervalTimeout = 50;
        timeouts.ReadTotalTimeoutConstant = 50;
        timeouts.ReadTotalTimeoutMultiplier = 10;
        timeouts.WriteTotalTimeoutConstant = 50;
        timeouts.WriteTotalTimeoutMultiplier = 10;

        if (!SetCommTimeouts(hSerial, &timeouts)) {
            std::cout << "Ошибка установки таймаутов" << std::endl;
            return false;
        }

        std::cout << "Успешно подключено к " << portName << " (" << baudRate << " бод)" << std::endl;
        return true;
    }

    // Отправка команды
    bool sendCommand(const std::string& command) {
        if (hSerial == INVALID_HANDLE_VALUE) {
            std::cout << "Нет подключения к порту!" << std::endl;
            return false;
        }

        DWORD bytesWritten;
        BOOL result = WriteFile(
            hSerial,
            command.c_str(),
            command.length(),
            &bytesWritten,
            NULL
        );

        if (result && bytesWritten == command.length()) {
            std::cout << "Отправлено: " << command << std::endl;
            return true;
        }
        else {
            std::cout << "Ошибка отправки команды" << std::endl;
            return false;
        }
    }

    // Чтение данных из порта (в отдельном потоке)
    void readFromPort() {
        char buffer[256];
        DWORD bytesRead;

        while (running) {
            if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
                buffer[bytesRead] = '\0';  // Добавляем нуль-терминатор
                std::cout << "\nМК: " << buffer << std::endl;
            }
            Sleep(10);
        }
    }

    // Запуск потока чтения
    void startReading() {
        running = true;
        readThread = std::thread(&SerialTerminal::readFromPort, this);
    }

    // Отключение от порта
    void disconnect() {
        running = false;

        if (readThread.joinable()) {
            readThread.join();
        }

        if (hSerial != INVALID_HANDLE_VALUE) {
            CloseHandle(hSerial);
            hSerial = INVALID_HANDLE_VALUE;
            std::cout << "Отключено от COM-порта" << std::endl;
        }
    }

    // Показать справку
    void showHelp() {
        std::cout << "\n=== Команды управления гирляндой ===" << std::endl;
        std::cout << "1 - Включить питание" << std::endl;
        std::cout << "0 - Выключить питание" << std::endl;
        std::cout << "m - Следующий режим" << std::endl;
        std::cout << "s - Следующая скорость" << std::endl;
        std::cout << "h - Показать справку" << std::endl;
        std::cout << "q - Выход из программы" << std::endl;
        std::cout << "=====================================" << std::endl;
    }

    // Главный цикл терминала
    void run() {
        std::cout << "Терминал управления гирляндой" << std::endl;
        std::cout << "==============================" << std::endl;

        // Подключаемся к порту
        if (!connect("COM2", 4800)) {
            std::cout << "Не удалось подключиться к порту. Завершение работы." << std::endl;
            return;
        }

        // Запускаем поток чтения
        startReading();

        showHelp();

        // Главный цикл ввода команд
        std::string input;
        while (true) {
            std::cout << "Введите команду: ";
            std::getline(std::cin, input);

            if (input == "q" || input == "Q") {
                break;
            }
            else if (input == "h" || input == "H") {
                showHelp();
            }
            else if (input == "0" || input == "1" || input == "m" || input == "s") {
                sendCommand(input);
            }
            else {
                std::cout << "Неизвестная команда. Нажмите 'h' для справки." << std::endl;
            }
        }

        disconnect();
        std::cout << "Терминал закрыт." << std::endl;
    }
};

// Терминал с обработкой клавиш в реальном времени (альтернативная версия)
class InteractiveTerminal : public SerialTerminal {
public:
    void runInteractive() {
        std::cout << "Интерактивный терминал управления гирляндой" << std::endl;
        std::cout << "============================================" << std::endl;
        std::cout << "Используйте клавиши: 1, 0, M, S, H, Q" << std::endl;
        std::cout << "Нажмите H для справки" << std::endl;

        if (!connect("COM2", 4800)) {
            return;
        }

        startReading();

        char ch;
        while (true) {
            if (_kbhit()) {  // Проверяем нажатие клавиши
                ch = _getch();

                switch (ch) {
                case '1': sendCommand("1"); break;
                case '0': sendCommand("0"); break;
                case 'm': case 'M': sendCommand("m"); break;
                case 's': case 'S': sendCommand("s"); break;
                case 'h': case 'H': showHelp(); break;
                case 'q': case 'Q':
                    disconnect();
                    std::cout << "Выход..." << std::endl;
                    return;
                default: break;
                }
            }
            Sleep(50);
        }
    }
};

int main() {
    setlocale(LC_ALL, "rus");

    SerialTerminal terminal;
    terminal.run();

    return 0;
}