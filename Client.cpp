#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

#define MUTEX L"printer"

int main()
{
    setlocale(LC_ALL, "Russian");

    HANDLE hMutex = OpenMutex(SYNCHRONIZE, FALSE, MUTEX);
    if (!hMutex)
    {
        cout << "Принтер не найден!\n";
        return GetLastError();
    }

    while (true)
    {
        cout << "\n1 - Отправить на печать \nЛюбая клавиша - выход" << endl << endl;
        char c = _getch();
        if (c != '1') break;

        WaitForSingleObject(hMutex, INFINITE);

        cout << "Отправил печатать" << endl;

        ReleaseMutex(hMutex);

        cout << "Ожидание завершения печати..." << endl;

        WaitForSingleObject(hMutex, INFINITE);

        cout << "Печать завершена" << endl;

        ReleaseMutex(hMutex);
    }

    CloseHandle(hMutex);
    return 0;
}
