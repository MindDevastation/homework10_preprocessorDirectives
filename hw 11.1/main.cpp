#include <iostream>
#ifdef _WIN64
#include <windows.h>
#include <conio.h>
#elif __linux
#include <termios.h>
#endif
using std::cout;
using std::string;
using std::flush;
using std::cin;


void processes(string& inputString, const string& compString) {
#ifdef _WIN64
    system("CLS");
#elif __linux
    system("clear");
#endif
    inputString.clear();
    cout << "��� ��������� �������� ����� �������� ������ esc\n";
    char   qt;   // ��� ������ �� ����� ����� ������������ �������
#ifdef _WIN64
    bool run = true;
    while (run) {
        if (_kbhit()) {
            qt = _getch();
            for (int i = 0; i < compString.length(); i++) {
                if (qt == compString[i]) {
                    qt = ' ';
                }
                else if (qt == 13) {
                    qt = '\n';
                }
                else if (qt == 27) {
                    run = false;
                    qt = ' ';
                    break;
                }
            }
            inputString += qt;
            cout << qt;
        }
    }
    cout << "\n�� ����� �����:\n" << inputString << "\n\n" << flush;


#elif __linux

    struct termios Old, New;
    tcgetattr(0, &Old);
    New = Old;
    New.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &New);
    qt = getchar();
    while ((qt = getchar()) != 27) {
        for (int i = 0; i < compString.length(); i++) {
            if (qt == compString[i]) {
                qt = ' ';
            }
        }
        inputString += qt;
        cout << qt;
    }
    tcsetattr(0, TCSANOW, &Old);
    cout << "\n�� ����� �����:\n" << inputString << "\n\n" << flush;

#endif


}

void menu(bool menu_run) {
    string Ukr = "���������������������������������������������������������޴�������";
    string Eng = "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM";
    string Num = "0123456789";
    string Symb = "`~!@#$%^&*()_+}{|\":<>?/.,\\';][=-�";
    int    choice = 0;

    string InputText;

    while (menu_run)
    {
        cout << "�������� 1 ��� ����� ���� ��������\n"
            << "�������� 2 ��� ����� ��������� ����� ��������\n"
            << "�������� 3 ��� ����� ���������� ���� ��������\n"
            << "�������� 4 ��� ����� ���������� ���� ��������\n" << flush;
        cin >> choice;
        switch (choice) {
        case 1:
            processes(InputText, Num);
            break;
        case 2:
            processes(InputText, Symb);
            break;
        case 3:
            processes(InputText, Eng);
            break;
        case 4:
            processes(InputText, Ukr);
            break;
        default:
            menu_run = false;
            break;
        }
    }
}

int main()
// ������� ����� ��� ���� ������
{

#ifdef _WIN32
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
#endif
    bool menu_run = true;

    string text;
    menu(menu_run);
}
