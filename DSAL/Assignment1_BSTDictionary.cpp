#include <iostream>
#include <string>
using namespace std;
class Node
{
    string word;
    string mean;
    Node *lchild;
    Node *rchild;

public:
    Node(string w = "", string m = "")
    {
        word = w;
        mean = m;
        lchild = NULL;
        rchild = NULL;
    }
    friend class BST;
};
class BST
{
    Node *root;

public:
    BST()
    {
        root = NULL;
    }
    void Insert(string, string);
    void ADisplay(Node *);
    void DDisplay(Node *);
    bool Search(string, Node *);
    void Update(string, string);
    void Delete(string);
    void Comparisons(Node *, string);
    Node *getRoot()
    {
        return root;
    }
};
void BST::Delete(string w)
{
    Node *parent, *child, *current;
    if (!Search(w, root))
    {
        cout << "\nWord is not present\n";
        return;
    }
    parent = NULL;
    current = root;
    while (current->word != w)
    {
        if (current->word > w)
        {
            parent = current;
            current = current->lchild;
        }
        else if (current->word < w)
        {
            parent = current;
            current = current->rchild;
        }
    }
    if (current->lchild == NULL && current->rchild == NULL)
    {
        if (parent != NULL)
        {
            if (parent->rchild == current)
            {
                parent->rchild = NULL;
            }
            else
            {
                parent->lchild = NULL;
            }
        }
        else
        {
            root = NULL;
        }
        delete current;
    }
    else if (current->lchild == NULL && current->rchild != NULL)
    {
        child = current->rchild;
        if (current != root)
        {
            if (parent->rchild == current)
            {
                parent->rchild = child;
                current->rchild = NULL;
            }
            else
            {
                parent->lchild = child;
                current->rchild = NULL;
            }
        }
        else
        {
            root = child;
            current->rchild = NULL;
        }
        delete current;
    }
    else if (current->lchild != NULL && current->rchild == NULL)
    {
        child = current->lchild;
        if (current != root)
        {
            if (parent->rchild == current)
            {
                parent->rchild = child;
                current->lchild = NULL;
            }
            else
            {
                parent->lchild = child;
                current->lchild = NULL;
            }
        }
        else
        {
            root = child;
            current->lchild = NULL;
        }
        delete current;
    }
    else
    {
        Node *temp = current->rchild;
        Node *temp_trail;
        if (current != root)
        {
            while (temp->lchild != NULL)
            {
                temp_trail = temp;
                temp = temp->lchild;
            }
            current->word = temp->word;
            current->mean = temp->mean;
            if (temp->rchild != NULL)
            {
                Node *temp2 = temp->rchild;
                temp_trail->lchild = temp2;
                temp->rchild = NULL;
            }
            else
            {
                temp_trail->lchild = NULL;
            }
        }
        else
        {
            root = current->lchild;
            root->rchild = current->rchild;
            current->rchild = NULL;
            current->lchild = NULL;
        }
        delete temp;
    }
}
bool BST::Search(string x, Node *temp)
{
    if (root == NULL)
    {
        return false;
    }
    else if (temp->word == x)
    {
        return true;
    }
    else if (x > temp->word)
    {
        temp = temp->rchild;
        return Search(x, temp);
    }
    else if (x < temp->word)
    {
        temp = temp->lchild;
        return Search(x, temp);
    }
    return false;
}
void BST::Update(string old_w, string m)
{
    if (!Search(old_w, root))
    {
        cout << "Not Found";
        return;
    }
    else
    {

        Node *temp = root;
        while (old_w != temp->word)
        {
            if (old_w > temp->word)
            {
                temp = temp->rchild;
            }
            else if (old_w < temp->word)
            {
                temp = temp->lchild;
            }
        }
        temp->mean = m;
    }
}
void BST::Insert(string w, string m)
{
    if (root == NULL)
    {
        Node *n = new Node(w, m);
        root = n;
    }
    else
    {
        Node *parent = NULL;
        Node *current = root;
        Node *n = new Node(w, m);
        while (current != NULL)
        {
            if (w > current->word)
            {
                parent = current;
                current = current->rchild;
            }
            else if (w < current->word)
            {
                parent = current;
                current = current->lchild;
            }
        }
        if (w > parent->word)
        {
            parent->rchild = n;
        }
        else
        {
            parent->lchild = n;
        }
    }
}
void BST::ADisplay(Node *temp)
{
    if (temp != NULL)
    {
        ADisplay(temp->lchild);
        cout << temp->word << ":" << temp->mean << "  ";
        ADisplay(temp->rchild);
    }
}
void BST::DDisplay(Node *temp)
{
    if (temp != NULL)
    {
        DDisplay(temp->rchild);
        cout << temp->word << ":" << temp->mean << "  ";
        DDisplay(temp->lchild);
    }
}
void BST::Comparisons(Node *temp, string wc)
{
    int count = 0;
    while (temp != NULL)
    {
        if (wc < temp->word)
        {
            count++;
            temp = temp->lchild;
        }
        else if (wc > temp->word)
        {
            count++;
            temp = temp->rchild;
        }
        else if (wc == temp->word)
        {
            count++;
            cout << "Number of Comparisons to Find Word:" << count;
            return;
        }
    }
    cout << "\nWord Not Found";
}
int main()
{
    BST b;
    int ch;
    while (1 > 0)
    {
        cout << "\n*****MENU*****" << endl;
        cout << "1.Insert" << endl;
        cout << "2.Delete" << endl;
        cout << "3.Update" << endl;
        cout << "4.Display in Ascending Order" << endl;
        cout << "5.Display in Descending Order" << endl;
        cout << "6.Comparisons" << endl;
        cout << "7.Exit" << endl;
        cout << "Enter Your Choice:";
        cin >> ch;
        if (ch == 1)
        {
            int n;
            string w1, m1;
            cout << "Enter the Number of Elements:";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "Enter Word:";
                cin >> w1;
                cout << "Enter Meaning:";
                cin >> m1;
                b.Insert(w1, m1);
            }
        }
        else if (ch == 2)
        {
            string td;
            cout << "Enter the Word to be Deleted:";
            cin >> td;
            b.Delete(td);
        }
        else if (ch == 3)
        {
            string oldwd, nmn;
            cout << "Enter the Word whose Meaning you want to Change:";
            cin >> oldwd;
            cout << "Enter the New Meaning:";
            cin >> nmn;
            b.Update(oldwd, nmn);
        }
        else if (ch == 4)
        {
            b.ADisplay(b.getRoot());
        }
        else if (ch == 5)
        {
            b.DDisplay(b.getRoot());
        }
        else if (ch == 6)
        {
            string wc1;
            cout << "Enter the Word to Find Comparisons:";
            cin >> wc1;
            b.Comparisons(b.getRoot(), wc1);
        }
        else if (ch == 7)
        {
            cout << "!!THANK YOU!!";
            break;
        }
    }
    return 0;
}
