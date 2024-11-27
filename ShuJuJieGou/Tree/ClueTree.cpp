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

Tree *pre;

void TreeCreatePrelude(Tree* &T) {
    /*先序遍历创建二叉树*/
    char c;
    cin >> c;
    if (c != '#') {
        T = new Tree;
        T->data = c;
        TreeCreatePrelude(T->lchild);
        TreeCreatePrelude(T->rchild);
    }
    else {
        T = NULL;
    }
}

void PreludeTreeOut(Tree* T) {
    /*先序遍历输出二叉树*/
    if (T) {
        cout << T->data;
        PreludeTreeOut(T->lchild);
        PreludeTreeOut(T->rchild);
    }
}

void PostTreeOut(Tree* T) {
    /*后序遍历输出二叉树*/
    if (T) {
        PostTreeOut(T->lchild);
        PostTreeOut(T->rchild);
        cout << T->data;
    }
}

void InorderTreeOut(Tree* T) {
    /*中序遍历输出二叉树*/
    if (T) {
        InorderTreeOut(T->lchild);
        cout << T->data;
        InorderTreeOut(T->rchild);
    }
}

void TreeClueInorder(Tree* p){
    /*中序遍历线索化二叉树*/
    TreeClueInorder(p->lchild);     /*左子树递归线索化*/
    if(!p->lchild){                 /*p 没有左孩子*/
        p->ltag = 1;                /*给p加上左线索*/
        p->lchild = pre;            /*p的左孩子指针指向pre(前驱)*/
    }
    else p->ltag = 0;
    if(!pre->rchild){               /*pre 没有右孩子*/
        pre->rtag = 1;              /*给pre加上右线索*/
        pre->rchild = p;            /*pre的右孩子指针指向p(后继)*/
    }
    else pre->rtag = 0;
    pre = p;                        /*保持前驱指针pre指向p*/
    TreeClueInorder(p->rchild);     /*右子树递归线索化*/
}

int main() {
    Tree* T;
    TreeCreatePrelude(T);
    char c;
    InorderTreeOut(T);
    cout << endl;
    TreeClueInorder(T);
    /*输出中序线索化二叉树*/
    return 0;
}