#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

#define MUTEX L"printer"
#define EVENT L"event"

int main()
{
    setlocale(LC_ALL, "Russian");

    //HANDLE hEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, EVENT);
    HANDLE hMutex = OpenMutex(SYNCHRONIZE, FALSE, L"printer");
    if (!hMutex) {
        cout << "Принтер не включен" << endl;
    }

    while (true) {
        cout << "\n1. Отправить на печать" << endl;
        cout << "Любая клавиша = Выйти\n" << endl;

        char input = _getch();
        if (input != '1') {
            cout << "Пока!" << endl;
            break;
        }
        WaitForSingleObject(hMutex, INFINITE);
        cout << "Отправил в очередь" << endl;


        ReleaseMutex(hMutex);

        WaitForSingleObject(hMutex, INFINITE);

        cout << "Печать завершена!!!\n" << endl;

        ReleaseMutex(hMutex);
    }
    if (!hMutex)
        CloseHandle(hMutex);
}
