#include <iostream>
using namespace std;

typedef struct tree {
    char data;
    struct tree* lchild;
    struct tree* rchild;
} Tree;

void TreeCreate(Tree* &T) {
    /*�����������������*/
    char c;
    cin >> c;
    if (c != '#') {
        T = new Tree;
        T->data = c;
        TreeCreate(T->lchild);
        TreeCreate(T->rchild);
    }
    else {
        T = NULL;
    }
}

void PreludeTree(Tree* T) {
    /*����������������*/
    if (T) {
        cout << T->data;
        PreludeTree(T->lchild);
        PreludeTree(T->rchild);
    }
}

void PostTree(Tree* T) {
    if (T) {
        PostTree(T->lchild);
        PostTree(T->rchild);
        cout << T->data;
    }
}

void InorderTree(Tree* T, char &c) {
    /*�������������*/
    if (T) {
        c = T->data;
        char a, b;
        InorderTree(T->lchild, a);
        /*if(T->data != '+' && T->data != '-' && T->data != '*' && T->data != '/')
            cout << "(";*/
        cout << c;
        InorderTree(T->rchild, b);
        
    }
}

int main() {
    Tree* T;
    TreeCreate(T);
    /*PreludeTree(T);
    cout << endl;*/
    /*PostTree(T);
    cout << endl;*/
    char c;
    InorderTree(T, c);
    return 0;
}