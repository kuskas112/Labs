#include <windows.h>
#include <tchar.h>
#include <unordered_map>
#define BUF_SIZE 0x200
VOID ReportError(LPCTSTR UserMessage, DWORD ExitCode, BOOL PrintErrorMsg);
BOOL PrintStrings(HANDLE hOut, ...);
BOOL PrintMsg(HANDLE hOut, LPCTSTR pMsg);
static VOID CatFile(HANDLE, HANDLE);
DWORD Options(int argc, LPTSTR argv[], const std::unordered_map<TCHAR, BOOL*>& flag_map)
{
	int iArg = 1;
	for (; iArg < argc && argv[iArg][0] == _T('-'); ++iArg) {
		LPTSTR currentArg = argv[iArg] + 1; // Пропустить '-'
		while (*currentArg) {
			auto it = flag_map.find(*currentArg);
			if (it != flag_map.end()) {
				*(it->second) = TRUE;
			}
			++currentArg;
		}
	}
	return iArg;
}
VOID ReportError(LPCTSTR UserMessage, DWORD ExitCode, BOOL
	PrintErrorMsg)
	/*Универсальная функция для сообщения о системных ошибках. */
{
	DWORD eMsgLen, LastErr = GetLastError();
	LPTSTR lpvSysMsg;
	HANDLE hStdErr = GetStdHandle(STD_ERROR_HANDLE);
	PrintMsg(hStdErr, UserMessage);
	if (PrintErrorMsg)
	{
		eMsgLen = FormatMessage
		(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM, NULL, LastErr,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpvSysMsg, 0, NULL);
		PrintStrings(hStdErr, TEXT("\n"), lpvSysMsg, TEXT("\n"), NULL);
		/* Освобождаем блок памяти, содержащий сообщение об ошибке. */
		HeapFree(GetProcessHeap(), 0, lpvSysMsg);
	}
	if (ExitCode > 0)
		ExitProcess(ExitCode);
	else
		return;
}
BOOL PrintStrings(HANDLE hOut, ...)
{
	/* Записывает сообщения в дескриптор вывода. */
	DWORD MsgLen, Count;
	LPCTSTR pMsg;
	va_list pMsgList; /* Текущая строка сообщения. */
	va_start(pMsgList, hOut); /* Начало обработки сообщений. */
	while ((pMsg = va_arg(pMsgList, LPCTSTR)) != NULL)
	{
		MsgLen = wcslen(pMsg);
		/* WriteConsole работает только с дескрипторами консоли. */
		if (!WriteConsole(hOut, pMsg, MsgLen, &Count, NULL)
			/* Вызываем WriteFile только при неудаче WriteConsole */
			&& !WriteFile(hOut, pMsg, MsgLen * sizeof(TCHAR), &Count, NULL))
			return FALSE;
	}
	va_end(pMsgList);
	return TRUE;
}
BOOL PrintMsg(HANDLE hOut, LPCTSTR pMsg)
/* Версия PrintStrings для одного сообщения. */
{
	return PrintStrings(hOut, pMsg, NULL);
}
int _tmain(int argc, LPTSTR argv[])
{
	BOOL DashS = FALSE;

	std::unordered_map<TCHAR, BOOL*> flags = {
		{ _T('s'), &DashS },
	};

	HANDLE hInFile, hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int iArg, iFirstFile;
	iFirstFile = Options(argc, argv, flags);
	if (iFirstFile == argc)
	{
		/* В списке аргументов нет файлов. */
		/* Используется стандартный ввод. */
		CatFile(hStdIn, hStdOut);
		return 0;
	}
	/* Обрабатываем каждый входной файл. */
	for (iArg = iFirstFile; iArg < argc; iArg++)
	{
		hInFile = CreateFile(argv[iArg], GENERIC_READ,
			0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hInFile == INVALID_HANDLE_VALUE && !DashS)
			ReportError(_T("\nCat - ошибка открытия файла"), 1, TRUE);
		CatFile(hInFile, hStdOut);
		CloseHandle(hInFile);
	}
	return 0;
}
/* Функция, которая непосредственно выполняет работу:
читает входные данные и копирует их в стандартный вывод. */
static VOID CatFile(HANDLE hInFile, HANDLE hOutFile)
{
	DWORD nIn, nOut;
	BYTE Buffer[BUF_SIZE];
	while (ReadFile(hInFile, Buffer, BUF_SIZE, &nIn, NULL)
		&& (nIn != 0)
		&& WriteFile(hOutFile, Buffer, nIn, &nOut, NULL));
	return;
}