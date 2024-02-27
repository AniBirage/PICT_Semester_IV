/*
Beginning with an empty binary tree, Construct binary tree by inserting the values in the
order given. After constructing a binary tree perform following operations on it- Perform
inorder / preorder and post order traversal,Change a tree so that the roles of the left and
right pointers are swapped at every node, Find the height of tree,Copy this tree to another
[operator=], Count number of leaves, number of internal nodes. Erase all nodes in a binary tree.
(implement both recursive and non-recursive methods)
*/

#include <iostream>
using namespace std;
class Node
{
    int data;
    Node *l;
    Node *r;

public:
    Node()
    {
        data = 0;
        l = nullptr;
        r = nullptr;
    }
    Node(int data)
    {
        this->data = data;
        l = nullptr;
        r = nullptr;
    }
    friend class Queue;
    friend class BT;
    friend class Stack;
};
class Queue
{
    Node *q[50];
    int front;
    int rear;

public:
    Queue()
    {
        front = -1;
        rear = -1;
    }
    bool isempty()
    {
        if ((front == -1) || (front > rear))
        {
            return true;
        }
        return false;
    }
    bool isfull()
    {
        if (rear >= 49)
        {
            return true;
        }
        return false;
    }
    void push(Node *t)
    {
        if (!isfull())
        {
            front++;
            q[front] = t;
        }
        else
        {
            cout << "Stack Overflow" << endl;
        }
    }
    Node *pop()
    {
        if (!isempty())
        {
            Node *n = q[front];
            front++;
            return n;
        }
        return nullptr;
    }
    friend class BT;
};
class Stack
{
    Node *s[50];
    int top;

public:
    Stack()
    {
        top = -1;
    }
    bool isempty()
    {
        if (top == -1)
        {
            return true;
        }
        return false;
    }
    bool isfull()
    {
        if (top == 49)
        {
            return true;
        }
        return false;
    }
    void push(Node *t)
    {
        if (!isfull())
        {
            top++;
            s[top] = t;
        }
        else
        {
            cout << "Stack Overflow";
        }
    }
    Node *pop()
    {
        if (!isempty())
        {
            Node *n = s[top];
            top--;
            return n;
        }
        return nullptr;
    }
    friend class BT;
};
class BT
{
    Node *root;
    Queue q;

public:
    BT()
    {
        root = nullptr;
    }
    void create();
    void insert(Node *t, Node *n);
    Node *setroot();
    void inorder_r(Node *t);
    void preorder_r(Node *t);
    void postorder_r(Node *t);
    void inorder(Node *t);
    void preorder(Node *t);
    void postorder(Node *t);
    void Mirror(Node *t);
    int heighttree(Node *t);
    void operator=(BT &t);
    Node *copytree(Node *t);
    int count(Node *t);
    int leafnodes(Node *t);
    int internalnodes(Node *t);
    void DeleteTree(Node *t);
};
void BT::create()
{
    int a;
    cout << "Enter the Data you Want to Enter :" << endl;
    cin >> a;
    Node *n = new Node(a);
    if (root == nullptr)
    {
        root = n;
    }
    else
    {
        insert(root, n);
    }
}
void BT::insert(Node *t, Node *n)
{
    cout << "Where do you want to Insert the Node of " << t->data << " (R/L)" << endl;
    char c;
    cin >> c;
    if (c == 'R' || c == 'r')
    {
        if (t->r == nullptr)
        {
            t->r = n;
        }
        else
        {
            insert(t->r, n);
        }
    }
    else
    {
        if (t->l == nullptr)
        {
            t->l = n;
        }
        else
        {
            insert(t->l, n);
        }
    }
}
void BT::inorder_r(Node *t)
{

    if (t != nullptr)
    {
        inorder_r(t->l);
        cout << t->data << " ";
        inorder_r(t->r);
    }
}
void BT::preorder_r(Node *t)
{

    if (t != nullptr)
    {
        cout << t->data << " ";
        preorder_r(t->l);
        preorder_r(t->r);
    }
}
void BT::postorder_r(Node *t)
{

    if (t != nullptr)
    {
        postorder_r(t->l);
        postorder_r(t->r);
        cout << t->data << " ";
    }
}
void BT::inorder(Node *t)
{
    Stack s;
    while (t != nullptr)
    {
        s.push(t);
        t = t->l;
    }
    while (!s.isempty())
    {
        Node *t = s.pop();
        cout << t->data << " ";
        t = t->r;
        while (t != nullptr)
        {
            s.push(t);
            t = t->l;
        }
    }
}
void BT::preorder(Node *t)
{
    Stack s;
    s.push(t);
    while (!s.isempty())
    {
        t = s.pop();
        cout << t->data << " ";
        if (t->r != nullptr)
        {
            s.push(t->r);
        }
        if (t->l != nullptr)
        {
            s.push(t->l);
        }
    }
}
void BT::postorder(Node *t)
{
    Stack s1, s2;
    s1.push(t);
    while (!s1.isempty())
    {
        t = s1.pop();
        s2.push(t);
        if (t->l != nullptr)
        {
            s1.push(t->l);
        }
        if (t->r != nullptr)
        {
            s1.push(t->r);
        }
    }
    while (!s2.isempty())
    {
        t = s2.pop();
        cout << t->data << " ";
    }
}
void BT::Mirror(Node *t)
{
    if (t == nullptr)
    {
        return;
    }
    Mirror(t->l);
    Mirror(t->r);
    Node *t1 = t->l;
    t->l = t->r;
    t->r = t1;
}
int BT::heighttree(Node *t)
{
    int lheight, rheight;
    if (root == nullptr)
    {
        return 0;
    }
    else if (t->l == nullptr && t->r == nullptr)
    {
        return 1;
    }
    else
    {
        lheight = heighttree(t->l);
        rheight = heighttree(t->r);
        if (lheight > rheight)
        {
            return lheight + 1;
        }
        return rheight + 1;
    }
}
void BT::operator=(BT &t)
{
    Node *rot = copytree(t.root);
}
Node *BT::copytree(Node *t)
{
    Node *rot;
    if (t == nullptr)
    {
        return nullptr;
    }
    else
    {
        rot = new Node();
        rot->data = t->data;
        rot->l = copytree(t->l);
        rot->r = copytree(t->r);
    }
    return rot;
}
int BT::count(Node *t)
{
    int m,n;
    if(t!=nullptr)
    {
        m=count(t->l);
        n=count(t->r);
        return m+n+1;
    }
    return 0;
}
int BT::leafnodes(Node *t)
{
    // int counter = 0;
    // if (t->l == nullptr && t->r == nullptr)
    // {
    //     counter++;
    // }
    // if (t->l != nullptr)
    // {
    //     leafnodes(t->l);
    // }
    // if (t->r != nullptr)
    // {
    //     leafnodes(t->r);
    // }
    // return counter;
    int x=0,y=0;
    static int z=0;
    if(t!=nullptr)
    {
        x=leafnodes(t->l);
        y=leafnodes(t->r);
        if((t->l==nullptr)&&(t->r==nullptr))
        {
            z+=x+y+1;
        }
        return z;
    }
    return 0;
}
int BT::internalnodes(Node *t)
{
    // int count = 0;
    // if (t->l != nullptr || t->r != nullptr)
    // {
    //     count++;
    // }
    // if (t->l != nullptr)
    // {
    //     internalnodes(t->l);
    // }
    // if (t->r != nullptr)
    // {
    //     internalnodes(t->r);
    // }
    // return count;
    int x,y,z;
    x=count(t);
    y=leafnodes(t);
    z=x-y-1;
    return z;
}
void BT::DeleteTree(Node *t)
{
    DeleteTree(t->l);
    DeleteTree(t->r);
    delete t;
}
Node *BT::setroot()
{
    Node *n = root;
    return n;
}
int main()
{
    BT t;
    int ch;
    Node *p;
    while (1 > 0)
    {
        cout << "*****MENU*****" << endl;
        cout << "1.Create " << endl;
        cout << "2.Traversal" << endl;
        cout << "3.Mirror" << endl;
        cout << "4.Height" << endl;
        cout << "5.Copy Tree" << endl;
        cout << "6.Leaf Nodes" << endl;
        cout << "7.Internal Nodes" << endl;
        cout << "8.Delete" << endl;
        cout << "9.Exit" << endl;
        cout << "Enter Your Choice:";
        cin >> ch;
        if (ch == 1)
        {
            int n;
            cout << "Enter Total Number of Nodes ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                t.create();
            }
        }
        else if (ch == 2)
        {
            p = t.setroot();
            cout << "Preorder Traversal:";
            t.preorder(p);
            cout << endl;
            cout << "Inorder Traversal:";
            t.inorder(p);
            cout << endl;
            cout << "Postorder Traversal:";
            t.postorder(p);
            cout << endl;
            cout << "Preorder(Recursive)Traversal:";
            t.preorder_r(p);
            cout << endl;
            cout << "Inorder(Recursive)Traversal:";
            t.inorder_r(p);
            cout << endl;
            cout << "Postorder(Recursive)Traversal:";
            t.postorder_r(p);
            cout << endl;
        }
        else if(ch==3)
        {
            
        }
        else if (ch == 4)
        {
            p = t.setroot();
            cout << "Height of Tree Is:" << t.heighttree(p) << endl;
        }
        else if (ch == 5)
        {
            p = t.setroot();
            cout << "Orignal Address of Tree is" << endl;
            cout << p;
            cout << endl;
            t.inorder(p);
            Node *q = t.copytree(p);
            cout << "New Address of Tree is" << endl;
            cout << q;
            cout << endl;
            t.inorder(q);
        }
        else if (ch == 6)
        {
            p = t.setroot();
            cout << "Number of Leaf Node(s):" << t.leafnodes(p) << endl;
        }
        else if (ch == 7)
        {
            p = t.setroot();
            cout << "Number of Internal Node(s):" << t.internalnodes(p) << endl;
        }
        else if (ch == 8)
        {
            p = t.setroot();
            t.DeleteTree(p);
            cout << "Tree Deleted" << endl;
        }
        else if (ch == 9)
        {
            cout << "!!THANK YOU!!";
            break;
        }
        else
        {
            cout << "Invalid Input";
        }
    }
    return 0;
}
