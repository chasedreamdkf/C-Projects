/*线索二叉树*/
#include <iostream>
using namespace std;

typedef struct tree {
    char data;
    int ltag;
    int rtag;
    struct tree* lchild;
    struct tree* rchild;
} Tree;

Tree *pre, *next;

void TreeCreatePrelude(Tree* &T) {
    /*先序遍历创建二叉树*/
    char c;
    cin >> c;
    if (c != '#') {
        T = new Tree;
        T->data = c;
        T->ltag = T->rtag = 0;
        TreeCreatePrelude(T->lchild);
        TreeCreatePrelude(T->rchild);
    }
    else {
        T = NULL;
    }
}

void PreludeTree(Tree* T) {
    /*先序遍历输出二叉树*/
    if (T) {
        cout << T->data;
        PreludeTree(T->lchild);
        PreludeTree(T->rchild);
    }
}

void PostTree(Tree* T) {
    /*后序遍历输出二叉树*/
    if (T) {
        PostTree(T->lchild);
        PostTree(T->rchild);
        cout << T->data;
    }
}

void InorderTree(Tree* T, char &c) {
    /*中序遍历二叉树*/
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
    TreeCreatePrelude(T);
    /*PreludeTree(T);
    cout << endl;*/
    /*PostTree(T);
    cout << endl;*/
    char c;
    InorderTree(T, c);
    return 0;
}