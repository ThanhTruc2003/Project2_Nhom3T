#include<iostream>
#include<string>
#include<fstream>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
using namespace std;

void textColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void Gotoxy(int x, int y)
{
    COORD cPos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cPos);
}

class User
{
protected:
    string strUsername;
    string strPassword;
    string strName;
    string strAddress;
    string strPhone;
    string strEmail;
public:
    string getUsername()
    {
        return strUsername;
    }
    string getPassword()
    {
        return strPassword;
    }
    string getName()
    {
        return strName;
    }
    string getAddress()
    {
        return strAddress;
    }
    string getPhone()
    {
        return strPhone;
    }
    string getEmail()
    {
        return strEmail;
    }

    void setUsername(string _Username)
    {
        strUsername = _Username;
    }
    void setPassword(string _Password)
    {
        strPassword = _Password;
    }
    void setName(string _Name)
    {
        strName = _Name;
    }
    void setAddress(string _Address)
    {
        strAddress = _Address;
    }
    void setPhone(string _Phone)
    {
        strName = _Phone;
    }
    void setEmail(string _Email)
    {
        strName = _Email;
    }

    User(string _Username = "", string _Password = "111111", string _Name = "", string _Address = "", string _Phone = "", string _Email = "")
    {
        strUsername = _Username;
        strPassword = _Password;
        strName = _Name;
        strAddress = _Address;
        strPhone = _Phone;
        strEmail = _Email;
    }

    User(const User& u)
    {
        strUsername = u.strUsername;
        strPassword = u.strPassword;
        strName = u.strName;
        strAddress = u.strAddress;
        strPhone = u.strPhone;
        strEmail = u.strEmail;
    }
    ~User() {}

    virtual void readFile(ifstream& FileIn)
    {
        getline(FileIn, strUsername, ',');
        getline(FileIn, strPassword);
    }

    virtual void createFile(ofstream& FileOut, char*& FileName)
    {
        string str = (string)FileName;
        string FilePath = str + ".txt";
        FileName = new char[FilePath.length() + 1];
        strcpy(FileName, FilePath.c_str());
        if (FileName != NULL)
        {
            FileOut.open(FileName, ios_base::out);
        }
        delete[] FileName;
    }

    virtual void openFile(ifstream& FileIn, char*& FileName)
    {
        string str = (string)FileName;
        string FilePath = str + ".txt";
        FileName = new char[FilePath.length() + 1];
        strcpy(FileName, FilePath.c_str());
        if (FileName != NULL)
        {
            FileIn.open(FileName, ios_base::in);
        }
        delete[] FileName;
    }

    virtual void readInfomation(ifstream& FileIn)
    {
        getline(FileIn, strName);
        getline(FileIn, strAddress);
        getline(FileIn, strPhone);
        getline(FileIn, strEmail);
    }

    virtual void deleteFile(string FileName)
    {
        string FilePath = "\"del " + FileName + ".txt\"";
        char* pDelete = new char[FilePath.length() + 1];
        strcpy(pDelete, FilePath.c_str());
        system(pDelete);
    }

    virtual void Input()
    {
        cin.ignore();
        textColor(3);
        cout << "Nhap thong tin ca nhan " << endl;
        cout << "Ho ten: ";
        textColor(15);
        getline(cin, strName);
        textColor(3);
        cout << "Dia chi: ";
        textColor(15);
        getline(cin, strAddress);
        textColor(3);
        cout << "So dien thoai: ";
        textColor(15);
        getline(cin, strPhone);
        textColor(3);
        cout << "Email: ";
        textColor(15);
        getline(cin, strEmail);
    }
};

class Administrators : public User
{
public:
    void readFile(ifstream& FileIn)
    {
        User::readFile(FileIn);
    }
    void createFile(ofstream& FileOut, char* pFileName)
    {
        User::createFile(FileOut, pFileName);
    }
    bool operator == (Administrators a)
    {
        return a.getUsername() + a.getPassword() == getUsername() + getPassword();
    }
    Administrators(string _Username = "", string _Password = "111111", string _Name = "", string _Address = "", string _Phone = "", string _Email = "")
        :User(_Username, _Password, _Name, _Address, _Phone, _Password) {}
};

class Employees : public User
{
public:
    void readFile(ifstream& FileIn)
    {
        User::readFile(FileIn);
    }
    void Input()
    {
        User::Input();
    }
    void createFile(ofstream& FileOut, char* FileName)
    {
        User::createFile(FileOut, FileName);
    }
    void ReadInformation(ifstream& FileIn)
    {
        User::readInfomation(FileIn);
    }
    bool operator ==(Employees a)
    {
        return a.getUsername() + a.getPassword() == getUsername() + getPassword();
    }
    Employees(string _Username = "", string _Password = "111111", string _Name = "", string _Address = "", string _Phone = "", string _Email = "")
        :User(_Username, _Password, _Name, _Address, _Phone, _Password) {}
};

void loginAdmin()
{
    textColor(14);
    cout << "\t\t\t\t\t****************************" << endl;
    cout << "\t\t\t\t\t*    ";
    textColor(10);
    cout << "DANG NHAP ADMIN       ";
    textColor(14);
    cout << "*" << endl;
    cout << "\t\t\t\t\t****************************" << endl;
}

void loginEmployees()
{
    textColor(14);
    cout << "\t\t\t\t\t****************************" << endl;
    cout << "\t\t\t\t\t*    ";
    textColor(10);
    cout << "DANG NHAP EMPLOYEES   ";
    textColor(14);
    cout << "*" << endl;
    cout << "\t\t\t\t\t****************************" << endl;
}

void menuAdmin()
{
    textColor(14);
    cout << "\t\t\t\t\t****************MENU****************" << endl;
    cout << "\t\t\t\t\t    1. Them Employee                " << endl;
    cout << "\t\t\t\t\t    2. Xoa Employee                 " << endl;
    cout << "\t\t\t\t\t    3. Tim Employee                 " << endl;
    cout << "\t\t\t\t\t    4. Cap nhat Employee            " << endl;
    cout << "\t\t\t\t\t    5. Hien thi thong tin Employee  " << endl;
    cout << "\t\t\t\t\t    6. Thoat!                       " << endl;
    cout << "\t\t\t\t\t************************************" << endl;
}

void menuEmployee()
{
    textColor(14);
    cout << "\t\t\t\t\t***********MENU EMPLOYEE***********" << endl;
    cout << "\t\t\t\t\t     1. Xem thong tin tai khoan    " << endl;
    cout << "\t\t\t\t\t     2. Doi password               " << endl;
    cout << "\t\t\t\t\t     3. Thoat                      " << endl;
    cout << "\t\t\t\t\t***********************************" << endl;

}

void encryptPassword(char*& pMatKhau, char x, int size)
{
    x = 'a';
    size = 0;
    while (x != 13)
    {
        x = _getch();
        if (x == 13)
        {
            break;
        }
        if (pMatKhau[0] == '\0')
        {
            while (true)
            {
                x = _getch();
                if (x != 8) 
                {
                    break; 
                }
            }
        }
        if (x == 8)
        {
            if (size != 0)
            {
                pMatKhau[size] = '\0';
                size--;
                cout << "\b \b";
            }
        }
        else
        {
            cout << x;
            pMatKhau[size] = x;
            size++;
            Sleep(100);
            cout << "\b \b*";
        }
    }
    pMatKhau[size] = '\0';
}

void Login(string& TaiKhoan, char*& pMatKhau)
{
    textColor(3);
    cout << "\t\t\t\t\tUser:     " << endl;
    cout << "\t\t\t\t\tPin:     ";
    textColor(15);
    Gotoxy(46, 3);
    cin >> TaiKhoan;
    char x = 'l';
    int iSize = 0;
    cout << endl;
    textColor(3);
    Gotoxy(46, 4);
    textColor(15);
    encryptPassword(pMatKhau, x, iSize);
    cout << endl;
}

bool checkUsernameEmployee(User* x, string strUsername)
{
    ifstream FileIn;
    FileIn.open("Employees.txt", ios_base::in);
    while (!FileIn.eof())
    {
        x = new Employees();
        x->readFile(FileIn);
        if (strUsername == x->getUsername())
        {
            return false;
        }
    }
    FileIn.close();
    return true;
}

bool successfulLogin(User* x, char* pFilePath, string& SaveUsername)
{
    ifstream FileIn;
    FileIn.open(pFilePath, ios_base::in);
    string TaiKhoan;
    const int maxSize = 20;
    char* pMatKhau = new char[maxSize];
    Login(TaiKhoan, pMatKhau);
    while (!FileIn.eof())
    {
        x = new User();
        x->readFile(FileIn);
        if (x->getUsername() + x->getPassword() == TaiKhoan + " " + pMatKhau)
        {
            SaveUsername = TaiKhoan;
            return true;
        }
    }
    FileIn.close();
    return false;
}

void addEmployee(User* x)
{
    string strUsername;
    textColor(3);
    cout << "Nhap Username muon them: ";
    textColor(15);
    cin >> strUsername;
    if (checkUsernameEmployee(x, strUsername))
    {
        textColor(3);
        textColor(15);
        char* FilePath = new char[strUsername.length() + 1];
        strcpy(FilePath, strUsername.c_str());
        ofstream FileOut;
        Employees* Emp = new Employees();
        FileOut.open("Employees.txt", ios_base::app);
        FileOut << endl << strUsername << ", " << "111111";
        FileOut.close();
        Emp->createFile(FileOut, FilePath);
        Emp->Input();
        FileOut << Emp->getName() << endl << Emp->getAddress() << endl << Emp->getPhone() << endl << Emp->getEmail();
        FileOut.close();
        textColor(12);
        cout << "Them thanh cong!" << endl;
    }
    else
    {
        textColor(12);
        cout << "Username da ton tai!" << "\n";
    }
}

void deleteEmployee(User* x, string strUsername)
{
    ifstream FileIn;
    FileIn.open("Employees.txt", ios_base::in);
    ofstream FileOut;
    FileOut.open("EmployeesCopy.txt", ios_base::out);
    int iCount = 0;
    while (!FileIn.eof())
    {
        x = new Employees();
        x->readFile(FileIn);
        if (x->getUsername() != strUsername)
        {
            FileOut << x->getUsername() << "," << x->getPassword() << endl;
        }
        iCount++;
    }
    FileIn.close();
    FileOut.close();
    system("del Employees.txt");
    char* c = (char*)"Employees";
    x->createFile(FileOut, c);
    FileOut.close();
    FileIn.open("EmployeesCopy.txt", ios_base::in);
    FileOut.open("Employees.txt", ios_base::out);
    while (iCount > 1) {
        x = new Employees();
        x->readFile(FileIn);
        if (iCount == 2)
        {
            FileOut << x->getUsername() << "," << x->getPassword();
            break;
        }
        FileOut << x->getUsername() << "," << x->getPassword() << endl;
        iCount--;
    }
    FileIn.close();
    FileOut.close();
    x->deleteFile(strUsername);
    textColor(12);
    cout << "Xoa thanh cong!" << endl;
    system("del EmployeesCopy.txt");
}

void findEmployee(User* x, string strUsername)
{
    ifstream FileIn;
    char* pFileName = new char[strUsername.length() + 1];
    strcpy(pFileName, strUsername.c_str());
    x = new Employees();
    x->openFile(FileIn, pFileName);
    x->readInfomation(FileIn);
    textColor(12);
    cout << "Thong tin Username can tim: " << endl;
    textColor(11);
    cout << "Ho ten: " << x->getName() << endl;
    cout << "Dia chi: " << x->getAddress() << endl;
    cout << "So dien thoai: " << x->getPhone() << endl;
    cout << "Email: " << x->getEmail();
    FileIn.close();
}

void viewUserInformation(User* x, string strUsername)
{
    ifstream FileIn;
    char* pFileName = new char[strUsername.length() + 1];
    strcpy(pFileName, strUsername.c_str());
    x = new Employees();
    x->openFile(FileIn, pFileName);
    x->readInfomation(FileIn);
    textColor(12);
    cout << "Thong tin tai khoan" << endl;
    textColor(11);
    cout << "Ho ten: " << x->getName() << endl;
    cout << "Dia chi: " << x->getAddress() << endl;
    cout << "So dien thoai: " << x->getPhone() << endl;
    cout << "Email: " << x->getEmail();
    FileIn.close();
}

void updateEmployee(User* x)
{
    ifstream FileIn;
    ofstream FileOut;
    textColor(3);
    cout << "Nhap Username: ";
    string strUsername;
    textColor(15);
    cin >> strUsername;
    if (!checkUsernameEmployee(x, strUsername))
    {
        while (true)
        {
            textColor(10);
            cout << "Chon muc ban muon cap nhat: " << endl;
            cout << "1. Ho ten " << endl;
            cout << "2. Dia chi " << endl;
            cout << "3. So dien thoai " << endl;
            cout << "4. strEmail " << endl;
            int iOptions;
            textColor(15);
            cin >> iOptions;
            char* FileName = new char[strUsername.length() + 1];
            strcpy(FileName, strUsername.c_str());
            x = new Employees();
            string Edit;
            if (iOptions == 1)
            {
                textColor(3);
                cout << "Nhap ho ten thay doi: ";
                cin.ignore();
                textColor(15);
                getline(cin, Edit);
                x->openFile(FileIn, FileName);
                x->readInfomation(FileIn);
                FileOut.open("NoName.txt", ios_base::out);
                FileOut << Edit << endl << x->getAddress() << endl << x->getPhone() << endl << x->getEmail();
                FileIn.close();
                FileOut.close();
                x->deleteFile(strUsername);

                char* pFileName = new char[strUsername.length() + 1];
                strcpy(pFileName, strUsername.c_str());
                FileIn.open("NoName.txt", ios_base::in);
                x = new Employees();
                x->readInfomation(FileIn);
                x->createFile(FileOut, pFileName);
                FileOut << x->getName() << endl << x->getAddress() << endl << x->getPhone() << endl << x->getEmail();
                FileIn.close();
                FileOut.close();
                textColor(12);
                cout << "Cap nhat ho ten thanh cong!" << endl;
                x->deleteFile("NoName");
            }
            else if (iOptions == 2)
            {
                textColor(13);
                cout << "Nhap dia chi thay doi: ";
                cin.ignore();
                textColor(15);
                getline(cin, Edit);
                x->openFile(FileIn, FileName);
                x->readInfomation(FileIn);
                FileOut.open("NoName.txt", ios_base::out);
                FileOut << x->getName() << endl << Edit << endl << x->getPhone() << endl << x->getEmail();
                FileIn.close();
                FileOut.close();
                x->deleteFile(strUsername);

                char* pFileName = new char[strUsername.length() + 1];
                strcpy(pFileName, strUsername.c_str());
                FileIn.open("NoName.txt", ios_base::in);
                x = new Employees();
                x->readInfomation(FileIn);
                x->createFile(FileOut, pFileName);
                FileOut << x->getName() << endl << x->getAddress() << endl << x->getPhone() << endl << x->getEmail();
                FileIn.close();
                FileOut.close();
                textColor(12);
                cout << "Cap nhat dia chi thanh cong!" << endl;
                x->deleteFile("NoName");
            }
            else if (iOptions == 3)
            {
                textColor(3);
                cout << "Nhap so dien thoai thay doi: ";
                cin.ignore();
                textColor(15);
                getline(cin, Edit);
                x->openFile(FileIn, FileName);
                x->readInfomation(FileIn);
                FileOut.open("NoName.txt", ios_base::out);
                FileOut << x->getName() << endl << x->getAddress() << endl << Edit << endl << x->getEmail();
                FileIn.close();
                FileOut.close();
                x->deleteFile(strUsername);

                char* pFileName = new char[strUsername.length() + 1];
                strcpy(pFileName, strUsername.c_str());
                FileIn.open("NoName.txt", ios_base::in);
                x = new Employees();
                x->readInfomation(FileIn);
                x->createFile(FileOut, pFileName);
                FileOut << x->getName() << endl << x->getAddress() << endl << x->getPhone() << endl << x->getEmail();
                FileIn.close();
                FileOut.close();
                textColor(12);
                cout << "Cap nhat so dien thoai thanh cong!" << endl;
                x->deleteFile("NoName");
            }
            else if (iOptions == 4)
            {
                textColor(3);
                cout << "Nhap email thay doi: ";
                cin.ignore();
                textColor(15);
                getline(cin, Edit);
                x->openFile(FileIn, FileName);
                x->readInfomation(FileIn);
                FileOut.open("NoName.txt", ios_base::out);
                FileOut << x->getName() << endl << x->getAddress() << endl << x->getPhone() << endl << Edit;
                FileIn.close();
                FileOut.close();
                x->deleteFile(strUsername);

                char* pFileName = new char[strUsername.length() + 1];
                strcpy(pFileName, strUsername.c_str());
                FileIn.open("NoName.txt", ios_base::in);
                x = new Employees();
                x->readInfomation(FileIn);
                x->createFile(FileOut, pFileName);
                FileOut << x->getName() << endl << x->getAddress() << endl << x->getPhone() << endl << x->getEmail();
                FileIn.close();
                FileOut.close();
                textColor(12);
                cout << "Cap nhat email thanh cong!" << endl;
                x->deleteFile("NoName");
            }
            textColor(12);
            cout << "Ban co muon tiep tuc khong? (co/khong)" << endl;
            string c;
            textColor(15);
            cin >> c;
            if (c == "khong")
            {
                break;
            }
            else
            {
                system("cls");
            }
        }
    }
    else
    {
        textColor(12);
        cout << "Username khong ton tai! " << endl;
    }
}

void displayEmployeeInformation(User* x)
{
    ifstream FileIn;
    x = new Employees();
    FileIn.open("Employees.txt", ios_base::in);
    string strUser[100];
    int n = 0;
    while (!FileIn.eof())
    {
        x->readFile(FileIn);
        strUser[n] = x->getUsername();
        n++;
    }
    FileIn.close();
    for (int i = 0; i < n; i++)
    {
        textColor(12);
        cout << "Thong tin " << strUser[i] << ": " << endl;
        string s = strUser[i];
        char* pFileName = new char[s.length() + 1];
        strcpy(pFileName, s.c_str());
        x->openFile(FileIn, pFileName);
        x->readInfomation(FileIn);
        textColor(11);
        cout << "Ho ten: " << x->getName() << endl;
        cout << "Dia chi: " << x->getAddress() << endl;
        cout << "So dien thoai: " << x->getPhone() << endl;
        cout << "Email: " << x->getEmail() << endl;
        cout << endl;
        FileIn.close();
    }
}

void performChangePassword(User* x, string CurrentPass, string NewPass, string SaveUsername)
{
    ifstream FileIn;
    ofstream FileOut;
    string s = "NoName";
    char* pFileName = new char[s.length() + 1];
    strcpy(pFileName, s.c_str());
    x->createFile(FileOut, pFileName);
    FileIn.open("Employees.txt", ios_base::in);
    int count = 0;
    while (!FileIn.eof())
    {
        x->readFile(FileIn);
        count++;
    }
    FileIn.close();
    int tmp = count;
    FileIn.open("Employees.txt", ios_base::in);
    while (count > 0)
    {
        x->readFile(FileIn);
        if (count == 1)
        {
            FileOut << x->getUsername() << "," << x->getPassword();
            break;
        }
        FileOut << x->getUsername() << "," << x->getPassword() << endl;
        count--;
    }
    FileIn.close();
    FileOut.close();
    x->deleteFile("Employees");
    string s2 = "NoName";
    char* pFileName2 = new char[s2.length() + 1];
    strcpy(pFileName2, s2.c_str());
    x->openFile(FileIn, pFileName2);
    FileOut.open("Employees.txt", ios_base::out);
    while (tmp > 0)
    {
        x->readFile(FileIn);
        if (SaveUsername == x->getUsername() && " " + CurrentPass == x->getPassword() && tmp == 1)
        {
            FileOut << x->getUsername() << ", " << NewPass;
            break;
        }
        else if (SaveUsername == x->getUsername() && " " + CurrentPass == x->getPassword())
        {
            FileOut << x->getUsername() << ", " << NewPass << endl;
        }
        else
        {
            if (tmp == 1)
            {
                FileOut << x->getUsername() << "," << x->getPassword();
                break;
            }
            else if (tmp != 1)
            {
                FileOut << x->getUsername() << "," << x->getPassword() << endl;
            }
            else
            {
                break;
            }
        }
        tmp--;
    }
    textColor(12);
    cout << "\nDoi mat khau thanh cong!";
    FileIn.close();
    FileOut.close();
    x->deleteFile("NoName");
}

void changePassword(User* x)
{
    ifstream FileIn;
    ofstream FileOut;
    char* pCurrentPass = new char[50];
    char* pNewPass = new char[50];
    char* pConfirmPass = new char[50];
    char c = '\0';
    int size = 0;
    string strUsername;
    textColor(3);
    cout << "Nhap username hien tai: ";
    textColor(15);
    cin >> strUsername;
    textColor(3);
    cout << "Nhap password hien tai: ";
    textColor(15);
    encryptPassword(pCurrentPass, c, size);
    textColor(3);
    cout << "\nNhap password moi: ";
    textColor(15);
    encryptPassword(pNewPass, c, size);
    textColor(3);
    cout << "\nNhap lai password moi: ";
    textColor(15);
    encryptPassword(pConfirmPass, c, size);
    FileIn.open("Employees.txt", ios_base::in);
    bool bConfirm = false;
    while (!FileIn.eof())
    {
        x = new Employees();
        x->readFile(FileIn);
        if (" " + (string)pCurrentPass == x->getPassword() && (string)pNewPass == (string)pConfirmPass)
        {
            bConfirm = true;
            break;
        }
    }
    FileIn.close();
    if (bConfirm == false)
    {
        textColor(12);
        cout << "\nThong tin ban nhap khong chinh xac. Vui long kiem tra lai!" << endl;
    }
    else
    {
        performChangePassword(x, pCurrentPass, pNewPass, strUsername);
    }
}

int main() {
    while (true)
    {
        system("cls");
        textColor(12);
        cout << "\t\t\t--------------------------" << "\t\t" << "--------------------------" << endl;
        cout << "\t\t\t| 1. Dang Nhap ADMIN     |" << "\t\t" << "| 2. Dang Nhap EMPLOYEES |" << endl;
        cout << "\t\t\t--------------------------" << "\t\t" << "--------------------------" << endl;
        textColor(9);
        cout << "Nhap lua chon cua ban: " << endl;
        int iOptions;
        textColor(15);
        cin >> iOptions;
        int iFunctions;
        string SaveUsername;
        if (iOptions == 1)
        {
            while (true)
            {
                system("cls");
                loginAdmin();
                ifstream FileIn;
                ofstream FileOut;
                User* x = NULL;
                bool bExit = false;
                if (successfulLogin(x, (char*)"Administrators.txt", SaveUsername))
                {
                    while (true)
                    {
                        system("cls");
                        menuAdmin();
                        textColor(3);
                        cout << "Moi ban chon chuc nang: ";
                        textColor(15);
                        cin >> iFunctions;
                        if (iFunctions == 1)
                        {
                            addEmployee(x);
                            _getch();
                        }
                        else if (iFunctions == 2)
                        {
                            string strUsername;
                            textColor(3);
                            cout << "Nhap Username muon xoa: ";
                            textColor(15);
                            cin >> strUsername;
                            FileIn.open("Employees.txt", ios_base::in);
                            bool bFind = false; 
                            while (!FileIn.eof())
                            {
                                x = new Employees();
                                x->readFile(FileIn);
                                if (x->getUsername() == strUsername)
                                {
                                    bFind = true;
                                    break;
                                }
                            }
                            FileIn.close();
                            if (bFind == false)
                            {
                                textColor(12);
                                cout << "Khong tim thay Username de xoa!" << endl;
                                _getch();
                            }
                            else
                            {
                                deleteEmployee(x, strUsername);
                                _getch();
                            }
                            FileOut.close();
                        }
                        else if (iFunctions == 3)
                        {
                            string strUsername;
                            textColor(3);
                            cout << "Nhap Username muon tim: ";
                            textColor(15);
                            cin >> strUsername;
                            FileIn.open("Employees.txt", ios_base::in);
                            bool bFind = false;
                            while (!FileIn.eof())
                            {
                                x = new Employees();
                                x->readFile(FileIn);
                                if (x->getUsername() == strUsername)
                                {
                                    bFind = true;
                                    break;
                                }
                            }
                            FileIn.close();
                            if (bFind == false)
                            {
                                textColor(12);
                                cout << "Khong tim thay Username!" << endl;
                                _getch();
                            }
                            else
                            {
                                findEmployee(x, strUsername);
                                _getch();
                            }
                        }
                        else if (iFunctions == 4)
                        {
                            updateEmployee(x);
                            _getch();
                        }
                        else if (iFunctions == 5)
                        {
                            displayEmployeeInformation(x);
                            _getch();
                        }
                        else if (iFunctions == 6)
                        {
                            bExit = true;
                            break;
                        }
                        else
                        {
                            textColor(12);
                            cout << "Lua chon khong hop le. Vui long chon lai!" << endl;
                            _getch();
                        }
                    }
                    if (bExit == true) break;
                }
                else
                {
                    textColor(12);
                    cout << "Sai tai khoan hoac mat khau!" << endl;
                    _getch();
                }
            }
        }
        else if (iOptions == 2)
        {
            int iCount = 0;
            bool bExit = false;
            while (true)
            {
                system("cls");
                loginEmployees();
                ifstream FileIn;
                User* x = NULL;
                int n = 0;
                if (successfulLogin(x, (char*)"Employees.txt", SaveUsername))
                {
                    textColor(12);
                    cout << "Dang nhap thanh cong!" << endl;
                    char* CurrentPass = new char[50];
                    char* NewPass = new char[50];
                    char c = 'a';
                    int size = 0;
                    bool bConfirm = false;
                    ifstream FileIn;
                    ofstream FileOut;
                    textColor(3);
                    cout << "Vui long doi mat khau truoc khi su dung chuong trinh!" << endl;
                    _getch();
                    while (true)
                    {
                        system("cls");
                        textColor(3);
                        cout << "Nhap mat khau hien tai: ";
                        textColor(15);
                        encryptPassword(CurrentPass, c, size);

                        FileIn.open("Employees.txt", ios_base::in);
                        while (!FileIn.eof())
                        {
                            x = new Employees();
                            x->readFile(FileIn);
                            if (" " + (string)CurrentPass == x->getPassword())
                            {
                                bConfirm = true;
                                break;
                            }
                        }
                        FileIn.close();
                        if (bConfirm == false)
                        {
                            textColor(12);
                            cout << "\nMat khau hien tai khong chinh xac! " << endl;
                            _getch();
                        }
                        else if (bConfirm == true)
                        {
                            textColor(3);
                            cout << "\nNhap mat khau moi: ";
                            textColor(15);
                            encryptPassword(NewPass, c, size);
                            if ((string)CurrentPass == (string)NewPass)
                            {
                                textColor(12);
                                cout << "\nTrung mat khau. Vui long nhap lai!" << endl;
                                _getch();
                            }
                            else
                            {
                                performChangePassword(x, (string)CurrentPass, (string)NewPass, SaveUsername);
                                _getch();
                                break;
                            }
                        }
                    }
                    while (true)
                    {
                        system("cls");
                        menuEmployee();
                        textColor(3);
                        cout << "Moi ban chon chuc nang: ";
                        textColor(15);
                        cin >> iFunctions;
                        if (iFunctions == 1)
                        {
                            viewUserInformation(x, SaveUsername);
                            _getch();
                        }
                        else if (iFunctions == 2)
                        {
                            changePassword(x);
                            _getch();
                        }
                        else if (iFunctions == 3)
                        {
                            bExit = true;
                            break;
                        }
                        else
                        {
                            textColor(12);
                            cout << "Lua chon khong hop le. Vui long chon lai!" << endl;
                            _getch();
                        }
                    }
                }
                else
                {
                    iCount++;
                    textColor(12);
                    cout << "Sai tai khoan hoac mat khau!" << endl;
                }
                if (iCount == 3)
                {
                    exit(0);
                }
                if (bExit == true)
                {
                    break;
                }
                _getch();
            }
        }
        else
        {
            textColor(12);
            cout << "Lua chon khong hop le!" << endl;
            _getch();
        }
    }
    system("pause");
}