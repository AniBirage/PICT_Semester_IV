#include <iostream>
using namespace std;
class Node
{
    int data;
    Node *left;
    Node *right;

public:
    Node(int x = 0)
    {
        data = x;
        left = NULL;
        right = NULL;
    }
    friend class AVLT;
};
class AVLT
{
public:
    Node *root;
    AVLT()
    {
        root = NULL;
    }
    int height(Node *);
    int difference(Node *);
    Node *ll_rotat(Node *);
    Node *rr_rotat(Node *);
    Node *lr_rotat(Node *);
    Node *rl_rotat(Node *);
    Node *balance(Node *);
    Node *insert(Node *r, int v);
    void inorder(Node *);
};
int AVLT::height(Node *t)
{
    int h = 0;
    if (t != NULL)
    {
        int l_height = height(t->left);
        int r_height = height(t->right);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
int AVLT::difference(Node *t)
{
    int l_height = height(t->left);
    int r_height = height(t->right);
    int b_factor = l_height - r_height;
    return b_factor;
}
Node *AVLT::ll_rotat(Node *parent)
{
    Node *temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    cout<<"LL"<<endl;
    return temp;
}
Node *AVLT::rr_rotat(Node *parent)
{
    Node *temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    cout<<"RR"<<endl;
    return temp;
}
Node *AVLT::lr_rotat(Node *parent)
{
    parent->left = rr_rotat(parent->left);
    cout<<"LR"<<endl;
    return ll_rotat(parent);
}
Node *AVLT::rl_rotat(Node *parent)
{
    parent->right=ll_rotat(parent->right);
    cout<<"RL"<<endl;
    return rr_rotat(parent);
}
Node *AVLT::balance(Node *t)
{
    int balance_factor = difference(t);
    if (balance_factor > 1)
    {
        if (difference(t->left) > 0)
        {
            t = ll_rotat(t);
        }
        else
        {
            t = lr_rotat(t);
        }
    }
    else if (balance_factor < -1)
    {
        if (difference(t->right) > 0)
        {
            t = rl_rotat(t);
        }
        else
        {
            t = rr_rotat(t);
        }
    }
    return t;
}
Node *AVLT::insert(Node *r, int v)
{
    if (r == NULL)
    {
        r = new Node(v);
    }
    else if (v < r->data)
    {
        r->left = insert(r->left, v);
        r = balance(r);
    }
    else if (v > r->data)
    {
        r->right = insert(r->right, v);
        r = balance(r);
    }
    return r;
}
void AVLT::inorder(Node *temp)
{
    if (temp != NULL)
    {
        inorder(temp->left);
        cout << temp->data << " ";
        inorder(temp->right);
    }
}
int main()
{
    AVLT a;
    int ch, value;
    while (1 > 0)
    {
        cout << "\n*****MENU*****" << endl;
        cout << "1.Insert Elements" << endl;
        cout << "2.InOrder Traversal" << endl;
        cout << "3.Exit" << endl;
        cout << "Enter Your Choice:";
        cin >> ch;
        if (ch == 1)
        {
            cout << "Enter Value to Insert:";
            cin >> value;
            a.root = a.insert(a.root, value);
            cout << "Value Inserted";
        }
        else if (ch == 2)
        {
            cout << "InOrder Traversal:" << endl;
            a.inorder(a.root);
        }
        else if (ch == 3)
        {
            cout << "!!THANK YOU!!";
            break;
        }
        else
        {
            cout << "Wrong Choice";
        }
    }
    return 0;
}