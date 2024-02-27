#include <iostream>

using namespace std;

void heapify(int arr[], int n, int root)
{
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != root)
    {
        swap(arr[root], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int deleteElement(int arr[], int &n, int key)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        if (arr[i] == key)
            break;
    }

    if (i == n)
    {
        cout << "Element Not Present" << endl;
        return n;
    }

    arr[i] = arr[n - 1];
    n--;

    for (int j = (n / 2) - 1; j >= 0; j--)
        heapify(arr, n, j);

    return n;
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    int arr[100];
    int ch;
    int n;
    cout<<"Enter the Number of Elements:";
    cin>>n;
    while(1>0)
    {
        cout<<"\n*****MENU*****"<<endl;
        cout<<"1. Insert Elements"<<endl;
        cout<<"2. Sort the Elements"<<endl;
        cout<<"3. Delete Element"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Enter Your Choice:";
        cin>>ch;
        if(ch==1)
        {
            cout<<"Enter the Elements:"<<endl;
            for(int i=0;i<n;i++)
            {
                cin>>arr[i];
            }
        }
        else if(ch==2)
        {
            heapSort(arr,n);
            cout<<"Sorted Elements:"<<endl;
            printArray(arr,n);
        }
        else if(ch==3)
        {
            int key;
            cout<<"Enter the Element to be Deleted:";
            cin>>key;
            deleteElement(arr,n,key);
            cout<<"Element Deleted";
        }
        else if(ch==4)
        {
            cout<<"!!THANK YOU!!";
            break;
        }
        else
        {
            cout<<"Wrong Choice";
        }
    }
    return 0;
}
