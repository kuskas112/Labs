#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <unordered_map>
#include <string>

#define TYPE_FILE 1
#define TYPE_DIR 2
#define TYPE_DOT 3

// ==== ПРОТОТИПЫ ====
DWORD Options(int argc, LPTSTR argv[], const std::unordered_map<TCHAR, BOOL*>& flag_map);
BOOL TraverseDirectory(LPCTSTR PathName, BOOL* recursive, BOOL* showDetails);
BOOL ProcessItem(LPWIN32_FIND_DATA pFileData, BOOL showDetails);
DWORD FileType(LPWIN32_FIND_DATA pFileData);

// ==== ГЛАВНАЯ ФУНКЦИЯ ====
int _tmain(int argc, LPTSTR argv[])
{
    BOOL recursive = FALSE;
    BOOL showDetails = FALSE;

    // Ассоциация флагов с переменными
    std::unordered_map<TCHAR, BOOL*> flags = {
        { _T('R'), &recursive },
        { _T('1'), &showDetails }
    };

    TCHAR CurrPath[MAX_PATH + 1];
    DWORD FileIndex;
    BOOL ok = TRUE;

    //test
    const wchar_t* arg1 = _T("-1R"); 
    const wchar_t* arg2 = _T("*.cpp");
    const TCHAR* new_argv[] = { argv[0], _T("-1R"), _T("*.cpp") };
    argc = sizeof(new_argv) / sizeof(new_argv[0]);
    //test

    // Разбор флагов
    FileIndex = Options(argc, (LPTSTR*)new_argv, flags);
    GetCurrentDirectory(MAX_PATH, CurrPath);

    // Если шаблон не указан — использовать "*"
    if (argc < static_cast<int>(FileIndex + 1)) {
        ok = TraverseDirectory(_T("*"), &recursive, &showDetails);
    }
    else {
        for (int i = FileIndex; i < argc; ++i) {
            ok = TraverseDirectory(new_argv[i], &recursive, &showDetails) && ok;
            SetCurrentDirectory(CurrPath);
        }
    }

    return ok ? 0 : 1;
}

// ==== ОБРАБОТКА ФЛАГОВ ====
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


BOOL TraverseDirectory(LPCTSTR PathName, BOOL* recursive, BOOL* showDetails)
    /* Обход каталога; выполняем Processltem для каждого найденного
    соответствия. */
    /* PathName: относительный или абсолютный путь для обхода. */
{
    HANDLE SearchHandle;
    WIN32_FIND_DATA FindData;
    DWORD FType, iPass;
    TCHAR CurrPath[MAX_PATH + 1];
    GetCurrentDirectory(MAX_PATH, CurrPath);
    for (iPass = 1; iPass <= 2; iPass++)
    {
        /* 1-й проход: список файлов. */
        /* 2-й проход: обход каталогов (если указана опция -R). */
        SearchHandle = FindFirstFile(PathName, &FindData);
        do
        {
            FType = FileType(&FindData); /* Файл или каталог? */
            if (iPass == 1) /* Выводим имя и атрибуты. */
                ProcessItem(&FindData, *showDetails);
            if (FType == TYPE_DIR && iPass == 2 && *recursive)
            {
                /* Обрабатываем подкаталог. */
                _tprintf(_T("\n%s\\%s:"), CurrPath, FindData.cFileName);
                /* Подготовка к обходу каталога. */
                SetCurrentDirectory(FindData.cFileName);
                TraverseDirectory(_T("*"), recursive, showDetails);
                /* Рекурсивный вызов. */
                SetCurrentDirectory(_T("."));
            }
        } while (FindNextFile(SearchHandle, &FindData));
        FindClose(SearchHandle);
    }
    return TRUE;
}

// ==== ОПРЕДЕЛЕНИЕ ТИПА ФАЙЛА ====
DWORD FileType(LPWIN32_FIND_DATA pFileData)
{
    if (pFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        if (_tcscmp(pFileData->cFileName, _T(".")) == 0 ||
            _tcscmp(pFileData->cFileName, _T("..")) == 0)
            return TYPE_DOT;
        else
            return TYPE_DIR;
    }
    return TYPE_FILE;
}

// ==== ВЫВОД ИНФОРМАЦИИ О ФАЙЛЕ ====
BOOL ProcessItem(LPWIN32_FIND_DATA pFileData, BOOL showDetails)
{
    const TCHAR FileTypeChar[] = { ' ', 'd' };
    DWORD fType = FileType(pFileData);
    SYSTEMTIME st;

    if (fType != TYPE_FILE && fType != TYPE_DIR) return FALSE;

    _tprintf(_T("\n"));
    if (showDetails) {
        _tprintf(_T("%c "), FileTypeChar[fType - 1]);
        _tprintf(_T("%10d "), pFileData->nFileSizeLow);
        FileTimeToSystemTime(&(pFileData->ftLastWriteTime), &st);
        _tprintf(_T("%02d/%02d/%04d %02d:%02d:%02d "),
            st.wMonth, st.wDay, st.wYear,
            st.wHour, st.wMinute, st.wSecond);
    }

    _tprintf(_T("%s"), pFileData->cFileName);
    return TRUE;
}
