#include <iostream>

using namespace std;

class Node
{
private:
    int data;
    Node *left;
    Node *right;

public:
    Node(int data) : data(data), left(nullptr), right(nullptr) {}

    int getData() const { return data; }
    Node *getLeft() const { return left; }
    Node *getRight() const { return right; }

    void setLeft(Node *node) { left = node; }
    void setRight(Node *node) { right = node; }
};

class OBST
{
private:
    Node *root;

public:
    OBST() : root(nullptr) {}

    Node *getRoot() const { return root; }

    void calculateWeight(double *p, double *q, int n, int *input);
    Node *createTree(int i, int j, double **r, int *input);
    void inorderTraversal(Node *curr);
};

void OBST::calculateWeight(double *p, double *q, int n, int *input)
{
    double **w = new double *[n + 1];
    double **c = new double *[n + 1];
    double **r = new double *[n + 1];

    for (int i = 0; i < n + 1; ++i)
    {
        w[i] = new double[n + 1];
        c[i] = new double[n + 1];
        r[i] = new double[n + 1];
    }

    for (int i = 0; i < n; ++i)
    {
        w[i][i] = q[i];
        r[i][i] = c[i][i] = 0;

        w[i][i + 1] = q[i] + q[i + 1] + p[i];
        r[i][i + 1] = i + 1;
        c[i][i + 1] = w[i][i + 1];
    }

    w[n][n] = q[n];
    r[n][n] = c[n][n] = 0;

    for (int m = 2; m <= n; ++m)
    {
        for (int i = 0; i <= n - m; ++i)
        {
            double Min = 999;
            int j = i + m;
            int k = 0;
            w[i][j] = w[i][j - 1] + p[j - 1] + q[j];

            for (int x = i + 1; x <= j; ++x)
            {
                double sum = c[i][x - 1] + c[x][j];
                if (sum < Min)
                {
                    Min = sum;
                    k = x;
                }
            }

            c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
            r[i][j] = k;
        }
    }

    this->root = createTree(0, n, r, input);
}

Node *OBST::createTree(int i, int j, double **r, int *input)
{
    if (i != j)
    {
        int k = r[i][j];
        Node *t = new Node(input[k]);
        t->setLeft(createTree(i, k - 1, r, input));
        t->setRight(createTree(k, j, r, input));
        return t;
    }
    else
    {
        return nullptr;
    }
}

void OBST::inorderTraversal(Node *curr)
{
    if (curr != nullptr)
    {
        inorderTraversal(curr->getLeft());
        cout << curr->getData() << " ";
        inorderTraversal(curr->getRight());
    }
}

int main()
{
    OBST ST;
    int choice = -1;
    int temp = 0;

    cout << "# Implementation of OBST\n";

    while (choice)
    {
        cout << "\n---------- MENU ----------\n"
             << "1. Input identifiers\n"
             << "2. Inorder Traversal\n"
             << "0. Exit"
             << "\n--------------------------" << endl;
        cout << "Enter choice = ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "Enter no. of identifiers = ";
            cin >> temp;
            int *input = new int[temp + 1];
            double *p = new double[temp];
            double *q = new double[temp + 1];
            cout << "Enter identifiers = " << endl;

            input[0] = 0;
            for (int i = 0; i < temp; ++i)
            {
                cout << "Enter identifier " << i + 1 << " = ";
                cin >> input[i + 1];
            }
            cout << "Enter probabilities of successful search = " << endl;
            for (int i = 0; i < temp; ++i)
            {
                cout << "Enter probability " << i + 1 << " = ";
                cin >> p[i];
            }
            cout << "Enter probabilities of unsuccessful search = " << endl;
            for (int i = 0; i < temp + 1; ++i)
            {
                cout << "Enter probability " << i + 1 << " = ";
                cin >> q[i];
            }
            ST.calculateWeight(p, q, temp, input);
            break;
        }

        case 2:
        {
            cout << "Inorder Traversal = " << endl;
            ST.inorderTraversal(ST.getRoot());
            break;
        }

        case 0:
        {
            cout << "Thank you :)" << endl;
            break;
        }

        default:
        {
            cout << "# Forced exit due to error" << endl;
            exit(0);
        }
        }
    }

    return 0;
}
