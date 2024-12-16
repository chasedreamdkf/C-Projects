#include <iostream>
using namespace std;

typedef struct tree {
    char data;
    struct tree* lchild;
    struct tree* rchild;
} Tree;

void TreeCreate(Tree* &T) {
    /*先序遍历创建二叉树*/
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

void InorderTree(Tree* T){
    /*中序遍历二叉树*/
    if (T) {
        InorderTree(T->lchild);
        cout << T->data;
        InorderTree(T->rchild);
    }
}


/*测试输入，每行是一棵二叉树的特殊形式的前序序遍历编码序列：
-+a##*b##-c##d##/e##f##
预期输出加了括号的中缀形式的表达式：
((a+(b*(c-d)))-(e/f))
*/
void InorderTree2(Tree* T){
    if(T){
        if(T->data == '-'){
            cout << "(";
            InorderTree2(T->lchild);
            cout << T->data;
            InorderTree2(T->rchild);
            cout << ")";
        }
        else{
            InorderTree2(T->lchild);
            cout << T->data;
            InorderTree2(T->rchild);
        }
    }
}


/*测试输入，每行是一棵二叉树的特殊形式的前序序遍历编码序列：
-+a##*b##-c##d##/e##f##
预期输出加了括号的中缀形式的表达式：
a+b*(c-d)-e/f
*/
void InorderTree3(Tree* T){
    static int depth = 0;
    if(T){
        if(T->data == '*' || T->data == '/') depth = 1;
        if((T->data == '-' || T->data == '+') && depth){
            cout << "(";
            InorderTree3(T->lchild);
            cout << T->data;
            InorderTree3(T->rchild);
            cout << ")";
            depth = 0;
        }
        else{
            InorderTree3(T->lchild);
            cout << T->data;
            InorderTree3(T->rchild);
        }
    }
}


/*
用后序遍历的方法实现计算表达式值的算法
测试输入，每行是一棵表示表达式的二叉树的特殊形式的前序序遍历编码序列：
+1##*2##+3##4##
预期输出是相应表达式的值：
15
*/
int Evaluate(Tree* T){
    if(T){
        int left = Evaluate(T->lchild);
        int right = Evaluate(T->rchild);
        if(T->data == '+'){
            return left + right;
        }
        else if(T->data == '-'){
            return left - right;
        }
        else if(T->data == '*'){
            return left * right;
        }
        else if(T->data == '/'){
            return left / right;
        }
        return T->data - 48;
    }
}

int main() {
    Tree* T;
    TreeCreate(T);
    // PreludeTree(T);
    // PostTree(T);
    // InorderTree2(T);
    // cout << Evaluate(T);
    InorderTree3(T);
    return 0;
}

/*************************end***************************/