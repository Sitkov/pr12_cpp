
#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;


#define EVENT L"event"

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    
    //HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, EVENT);
    HANDLE hMutex = CreateMutex(NULL, FALSE, L"printer");
    if (!hMutex) {
        cout << "Ошибка создания мьютекса: " << GetLastError() << endl;
        return GetLastError();
    }

    wchar_t appName[] = L"C:\\Sitkov\\pr12_cpp\\x64\\Debug\\Client.exe";

    PROCESS_INFORMATION pi{};
    STARTUPINFO si{};

    si.cb = sizeof(si);

    if (!CreateProcess(NULL, appName, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        cout << "Клиент не создан" << endl;
    }

    cout << "Принтер запущен" << endl;

    DWORD lastClientTime = GetTickCount();

    while (true)
    {
        DWORD result = WaitForSingleObject(hMutex, 600000);
        //WaitForSingleObject(hEvent, INFINITE);

        if (result == WAIT_TIMEOUT)
        {
            cout << "Принтер умер" << endl;
            break;
        }

        if (result == WAIT_OBJECT_0) {
            cout << "Печатаю..." << endl;

            int printTime = 5000 + rand() % 10000;
            Sleep(printTime);

            if (printTime > 10000) {
                cout << "Ошибка печати.." << endl;
            }
            else {
                cout << "Успешно" << endl;;
            }
            ReleaseMutex(hMutex);
        }
        else 
        {
            Sleep(2000);
            cout << "Принтер готов к печати" << endl;
            
            ReleaseMutex(hMutex);
        }
    }
    CloseHandle(hMutex);
    return 0;
}