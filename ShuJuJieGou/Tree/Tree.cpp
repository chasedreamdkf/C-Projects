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
    /*����������������*/
    if (T) {
        PostTree(T->lchild);
        PostTree(T->rchild);
        cout << T->data;
    }
}

void InorderTree(Tree* T){
    /*�������������*/
    if (T) {
        InorderTree(T->lchild);
        cout << T->data;
        InorderTree(T->rchild);
    }
}


/*�������룬ÿ����һ�ö�������������ʽ��ǰ��������������У�
-+a##*b##-c##d##/e##f##
Ԥ������������ŵ���׺��ʽ�ı��ʽ��
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


/*�������룬ÿ����һ�ö�������������ʽ��ǰ��������������У�
-+a##*b##-c##d##/e##f##
Ԥ������������ŵ���׺��ʽ�ı��ʽ��
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
�ú�������ķ���ʵ�ּ�����ʽֵ���㷨
�������룬ÿ����һ�ñ�ʾ���ʽ�Ķ�������������ʽ��ǰ��������������У�
+1##*2##+3##4##
Ԥ���������Ӧ���ʽ��ֵ��
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