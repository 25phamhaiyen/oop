#include "BuilFunction.h"
#include "SignIn.h"
int main()
{
    int choice;
    do
    {
        cout << "Chon chuc nang: " << endl;
        cout << "1. Dang nhap | Dang ky." << endl;
        cout << "2. Nhap thong tin giay to." << endl;
        cout << "3. Tim kiem." << endl;
        cout << "4. Sap xep." << endl;
        cout << "5. Them chuyen bay." << endl;
        cout << "6. Huy chuyen bay." << endl;
        cout << "7. Xem lich su dat ve." << endl;
        cout << "8. Thoat." << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            SignIn si;
            cout << "Ban dang nhap voi tu cach nao?" << endl;
            cout << "1.Quan ly \n2.Khach hang" << endl
                 << endl;
            int signInChoice;
            do
            {
                cout << "Enter your choice:  ";
                cin >> signInChoice;
                if (signInChoice != 1 && signInChoice != 2)
                    cout << "\nMust enter 1 or 2. Please re-enter\n\n";
            } while (signInChoice != 1 && signInChoice != 2);
            cin.ignore();
            if (signInChoice == 1)
            {
                cout << "\n-----------------Sign In---------------------\n";
                si.sign_in(1);
                cout << "\n---------------------------------------------\n";
            }
            else
            {
                int signChoice;
                cout << "\nBan da co tai khoan chua?" << endl;
                cout << "1.Da co tai khoan \n2.Chua co tai khoan" << endl
                     << endl;
                do
                {
                    cout << "Enter your choice:  ";
                    cin >> signChoice;
                    if (signChoice != 1 && signChoice != 2)
                        cout << "\nMust enter 1 or 2. Please re-enter\n\n";
                } while (signChoice != 1 && signChoice != 2);
                cin.ignore();
                if (signChoice == 1)
                {
                    cout << "\n-----------------Sign In---------------------\n";
                    si.sign_in(2);
                    cout << "\n---------------------------------------------\n";
                }
                else
                {
                    cout << "\n-----------------Sign Up---------------------\n";
                    si.sign_up();
                    cout << "\n---------------------------------------------\n";

                    cout << "\n-----------------Sign In---------------------\n";
                    si.sign_in(2);
                    cout << "\n---------------------------------------------\n";
                }
            }
            break;
        // case 2:
        //     break;
        // case 3:
        //     break;
        // case 4:
        //     break;
        // case 5:
        //     break;
        // case 6:
        //     break;
        // case 7:
        //     break;
        // case 8:
        //     break;
        // default:
        //     cout << "Invalid choice. Please try again." << endl;
        //     break;
        }
    } while (1);
}