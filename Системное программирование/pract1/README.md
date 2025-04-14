Там в задании хотели какое то нищее консольное приложение для этой практики.
Я такой нищетой заниматься не стал, вот кайфовое оконное приложение.
Вот еще палите какую фишку научился делать
```cpp
case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case 1:  // ручное win32
            OnButtonClick(hWnd);
            break;
        case 2:  // полуфабрикатное win32
            OnButtonClickCopyFileFunc(hWnd);
            break;
        case 3:  // только с++
            OnButtonClickOnlyC(hWnd);
            break;
        }
    }
    break;
```
Код по красоте должен отображаться