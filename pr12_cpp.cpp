#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

#define MUTEX L"printer"

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    HANDLE hMutex = CreateMutex(NULL, FALSE, MUTEX);
    if (!hMutex) {
        cout << "Ошибка создания мьютекса: " << GetLastError() << endl;
        return GetLastError();
    }

    cout << "Принтер запущен" << endl;

    DWORD lastClientTime = GetTickCount();

    while (true)
    {
        DWORD result = WaitForSingleObject(hMutex, 600000);

        if (result == WAIT_TIMEOUT)
        {
            cout << "Принтер умер" << endl;
            break;
        }

        if (result == WAIT_OBJECT_0)
        {
            lastClientTime = GetTickCount();

            cout << "Печатаю..." << endl;

            int printTime = 5000 + rand() % 10000; 
            Sleep(printTime);

            if (printTime > 10000) {
                cout << "Принтер скушал бумагу.." << endl;
            }
            else {
                cout << "Успешно" << endl;;
            }

            ReleaseMutex(hMutex);
        }
    }
    CloseHandle(hMutex);
    return 0;
}
