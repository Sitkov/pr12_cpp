#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    cout << "<-- ПРИНТЕР -->" << endl;

    HANDLE hMutex = CreateMutex(NULL, FALSE, L"printer");
    if (!hMutex) {
        cout << "Ошибка создания мьютекса: " << GetLastError() << endl;
        return GetLastError();
    }

    cout << "Принтер ждет клиентов" << endl;

    wchar_t appName[] = L"C:\\Users\\CustomPC\\Desktop\\pr12_cpp\\x64\\Debug\\Client.exe";

    PROCESS_INFORMATION pi{};
    STARTUPINFO si{};
    si.cb = sizeof(si);

    if (!CreateProcess(NULL, appName, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        cout << "Клиент не создан. Ошибка: " << GetLastError() << endl;
    }
    else {
        cout << "Клиент запущен" << endl;
    }

    while (true)
    {
        DWORD result = WaitForSingleObject(hMutex, 0);

        if (result == WAIT_OBJECT_0) {
            ReleaseMutex(hMutex);
        }
        else if (result == WAIT_TIMEOUT) {
            WaitForSingleObject(hMutex, INFINITE);

            cout << "Начинаю печатать" << endl;

            int printTime = 5000 + rand() % 10000;

            Sleep(printTime);

            if (printTime > 10000) {
                cout << "Ошибка печати!" << endl;
                cout << endl;
            }
            else {
                cout << "Закончил печать" << endl;
                cout << endl;
            }

            ReleaseMutex(hMutex);
        }
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hMutex);
    return 0;
}
