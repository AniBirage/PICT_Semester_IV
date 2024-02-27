#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
    fstream MyFile;
    int ch;
    while (1 > 0)
    {
        cout << "\n*****MENU*****" << endl;
        cout << "1.Insert Information of Student" << endl;
        cout << "2.Display Information of Particular Student" << endl;
        cout << "3.Delete File" << endl;
        cout << "4.Exit" << endl;
        cout << "Enter You Choice:";
        cin >> ch;
        if (ch == 1)
        {
            int n;
            string name, rollno, division, address;
            MyFile.open("test.txt", ios::app);
            if (!MyFile)
            {
                cout << "Error Opening File" << endl;
            }
            else
            {
                cout << "File Opened Succesfully" << endl;
                cout << "Enter the Number of Students : ";
                cin >> n;
                cout << "Enter the Details of Student(s)" << endl;
                for (int i = 0; i < n; i++)
                {
                    cout << "Name : ";
                    cin >> name;
                    cout << "Roll Number : ";
                    cin >> rollno;
                    cout << "Division : ";
                    cin >> division;
                    cout << "Address : ";
                    cin >> address;
                    cout<<endl;
                    MyFile << name << " " << rollno << " " << division << " " << address << endl;
                }
            }
            MyFile.close();
        }
        else if (ch == 2)
        {
            string displayName, record;
            cout << "Enter Name of Student whose Information You Want: ";
            cin >> displayName;
            MyFile.open("test.txt", ios::in);
            if (!MyFile)
            {
                cout << "Error Opening File" << endl;
            }
            else
            {
                cout << "File Opened Succesfully" << endl;
                while (getline(MyFile, record))
                {
                    if (record.substr(0, displayName.length()) == displayName)
                    {
                        cout << "Information Of Student" << endl;
                        cout << record;
                        break;
                    }
                    else
                    {
                        cout << "No Record Found" << endl;
                        break;
                    }
                }
                MyFile.close();
            }
        }
        else if (ch == 3)
        {
            remove("test.txt");
            cout << "File Deleted Successfully" << endl;
        }
        else if (ch == 4)
        {
            cout << "!!THANK YOU!!";
            break;
        }
        else
        {
            cout << "Wrong Choice" << endl;
        }
    }
    return 0;
}