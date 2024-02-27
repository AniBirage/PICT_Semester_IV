#include <iostream>
#include <cstring>
using namespace std;
class DataItem
{
    string name;
    long telnum;
    friend class hashTable;
};
class hashTable
{
    DataItem D[10];
    void insert(long num, string client_name)
    {
        int key = num % 10;
        if (D[key].telnum == -1)
        {
            D[key].telnum = num;
            D[key].name = client_name;
        }
        else
        {
            int i = key + 1;
            while (D[i].telnum != -1)
            {
                if (i == key)
                {
                    cout << "Hash Table full!" << endl;
                }
                else
                {
                    i = (i + 1) % 10;
                }
            }
            D[i].telnum = num;
            D[i].name = client_name;
        }
    }
    void insert_with_replacement(long num, string client_name)
    {
        int key = num % 10;
        if (D[key].telnum == -1)
        {
            D[key].telnum = num;
            D[key].name = client_name;
        }
        else if ((D[key].telnum) % 10 != key)
        {
            DataItem temp;
            temp.telnum = D[key].telnum;
            temp.name = D[key].name;
            D[key].telnum = num;
            D[key].name = client_name;
            int i = key + 1;
            while (D[i].telnum != -1)
            {
                if (i == key)
                {
                    cout << "Hash Table full!" << endl;
                }
                else
                {
                    i = (i + 1) % 10;
                }
            }
            D[i].telnum = temp.telnum;
            D[i].name = temp.name;
        }
        else
        {
            int i = key + 1;
            while (D[i].telnum != -1)
            {
                i = (i + 1) % 10;
            }
            D[i].telnum = num;
            D[i].name = client_name;
        }
    }
    void search(long num)
    {
        int comparisons = 1;
        int key = num % 10;
        if (D[key].telnum == num)
        {
            cout << "Number present!" << endl;
        }
        else
        {
            comparisons++;
            int i = key + 1;
            while (D[i].telnum != num && D[i].telnum != -1)
            {
                i = (i + 1) % 10;
                comparisons++;
            }
            if (i == key)
            {
                cout << "Number not present!" << endl;
            }
            else if (D[i].telnum == -1)
            {
                cout << "Number not present!" << endl;
            }
            else
            {
                cout << "Number present!" << endl;
            }
        }
        cout << "Number of comparisons made: " << endl;
        cout << comparisons << endl;
    }
    void display(hashTable HTWR)
    {
        for (int i = 0; i < 10; i++)
        {
            cout << D[i].name << "\t\t" << HTWR.D[i].name << endl;
            cout << D[i].telnum << "\t" << HTWR.D[i].telnum << endl;
            cout << endl;
        }
    }

public:
    hashTable()
    {
        for (int i = 0; i < 10; i++)
        {
            D[i].telnum = -1;
            D[i].name = " ";
        }
    }
    void menu()
    {
        int choice;
        hashTable table2;
        while (true)
        {
            cout << "1) Insert." << endl;
            cout << "2) Search for a number." << endl;
            cout << "4) Display telephone book." << endl;
            cout << "5) Stop." << endl;
            cout << "Enter choice: " << endl;
            cin >> choice;
            if (choice == 1)
            {
                long ele;
                string n;
                cout << "Enter client name: " << endl;
                cin >> n;
                cout << "Enter telephone number: " << endl;
                cin >> ele;
                insert(ele, n);
                table2.insert_with_replacement(ele, n);
            }
            else if (choice == 2)
            {
                long ele;
                cout << "Enter number to be searched for: " << endl;
                cin >> ele;
                cout << "For linear probing without replacement: " << endl;
                search(ele);
                cout << endl;
                cout << "For linear probing with replacement: " << endl;
                table2.search(ele);
            }
            else if (choice == 3)
            {
                display(table2);
            }
            else if (choice == 4)
            {
                cout << "Thank You!" << endl;
                break;
            }
            else
            {
                cout << "Wrong Choice!" << endl;
            }
        }
    }
};
int main()
{
    hashTable table1;
    table1.menu();
    return 0;
}
