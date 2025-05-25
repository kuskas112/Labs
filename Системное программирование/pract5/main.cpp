#include <windows.h>
#include <tchar.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 256

int _tmain(DWORD argc, LPTSTR argv[])
{
    HANDLE hTempFile = INVALID_HANDLE_VALUE;
    BOOL prov;
    TCHAR outFile[MAX_PATH + 100];
    SECURITY_ATTRIBUTES StdOutSA = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    TCHAR CommandLine[MAX_PATH + 100];
    STARTUPINFO StartUpSearch, StartUp;
    PROCESS_INFORMATION ProcessInfo;
    DWORD iProc, ExCode;
    HANDLE* hProc;

    typedef struct {
        TCHAR TempFile[MAX_PATH];
    } PROCFILE;
    PROCFILE* ProcFile;

    GetStartupInfo(&StartUpSearch);
    GetStartupInfo(&StartUp);

    // Проверка количества аргументов
    if (argc < 3) {
        _tprintf(_T("Usage: %s <pattern> <file1> <file2> ...\n"), argv[0]);
        return 1;
    }

    ProcFile = (PROCFILE*)malloc((argc - 2) * sizeof(PROCFILE));
    hProc = (HANDLE*)malloc((argc - 2) * sizeof(HANDLE));

    // Вывод текущей директории для отладки
    TCHAR currentDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDir);
    _tprintf(_T("Current directory: %s\n"), currentDir);

    for (iProc = 0; iProc < argc - 2; iProc++) {
        // Создаем командную строку для findstr с правильным форматом
        _stprintf_s(CommandLine, _T("%s /C:\"%s\" \"%s\""),
            _T("findstr"), argv[1], argv[iProc + 2]);
        _tprintf(_T("Command: %s\n"), CommandLine);

        // Создаем временный файл
        if (GetTempFileName(_T("."), _T("gtm"), 0, ProcFile[iProc].TempFile) == 0) {
            _tprintf(_T("GetTempFileName failed (%d)\n"), GetLastError());
            continue;
        }

        hTempFile = CreateFile(ProcFile[iProc].TempFile, GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE, &StdOutSA,
            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if (hTempFile == INVALID_HANDLE_VALUE) {
            _tprintf(_T("CreateFile failed (%d)\n"), GetLastError());
            continue;
        }

        StartUpSearch.dwFlags = STARTF_USESTDHANDLES;
        StartUpSearch.hStdOutput = hTempFile;
        StartUpSearch.hStdError = hTempFile;
        StartUpSearch.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

        // Создаем процесс
        if (!CreateProcess(NULL, CommandLine, NULL, NULL,
            TRUE, 0, NULL, NULL, &StartUpSearch, &ProcessInfo)) {
            _tprintf(_T("CreateProcess failed (%d)\n"), GetLastError());
            CloseHandle(hTempFile);
            continue;
        }

        CloseHandle(hTempFile);
        CloseHandle(ProcessInfo.hThread);
        hProc[iProc] = ProcessInfo.hProcess;
    }

    // Ожидаем завершения всех процессов
    for (iProc = 0; iProc < argc - 2; iProc += MAXIMUM_WAIT_OBJECTS) {
        WaitForMultipleObjects(min(MAXIMUM_WAIT_OBJECTS, argc - 2 - iProc),
            &hProc[iProc], TRUE, INFINITE);
    }

    // Обрабатываем результаты
    for (iProc = 0; iProc < argc - 2; iProc++) {
        _tprintf(_T("Proc= %d\n"), iProc);
        prov = GetExitCodeProcess(hProc[iProc], &ExCode);

        if (ExCode != 0) {
            DeleteFile(ProcFile[iProc].TempFile);
        }
        else {
            if (argc > 3) _tprintf(_T("%s : \n"), argv[iProc + 2]);
            fflush(stdout);

            _stprintf_s(CommandLine, _T("cmd.exe /C type \"%s\""), ProcFile[iProc].TempFile);
            //_tprintf_s(_T("%s\n"), CommandLine);

            GetStartupInfo(&StartUp);
            StartUp.dwFlags = STARTF_USESTDHANDLES;
            StartUp.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
            StartUp.hStdError = GetStdHandle(STD_ERROR_HANDLE);
            StartUp.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

            if (CreateProcess(NULL, CommandLine, NULL, NULL,
                TRUE, 0, NULL, NULL, &StartUp, &ProcessInfo)) {
                WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
                CloseHandle(ProcessInfo.hProcess);
                CloseHandle(ProcessInfo.hThread);
            }
            else {
                _tprintf_s(L"Failed creation of type process (%d)\n", GetLastError());
            }
        }
        CloseHandle(hProc[iProc]);
        DeleteFile(ProcFile[iProc].TempFile);
    }

    free(ProcFile);
    free(hProc);
    return 0;
}
