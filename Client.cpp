#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "-- КЛИЕНТ --" << endl;

    HANDLE hMutex = OpenMutex(SYNCHRONIZE, FALSE, L"printer");
    if (!hMutex) {
        cout << "Принтер не найден. Ошибка: " << GetLastError() << endl;
        return GetLastError();
    }

    cout << "Принтер обнаружен" << endl;

    while (true)
{
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
}

    CloseHandle(hMutex);
    return 0;
}
