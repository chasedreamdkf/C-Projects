#include <iostream>
using namespace std;

// 多项式的每一项
typedef struct Poly{
    float c;                          // 多项式每一项的系数
    float e;                          // 多项式每一项的指数
    struct Poly* next;              // 多项式的下一项
} Poly;

// 多项式
typedef struct Polys{
    int length;                     // 多项式长度
    Poly *head;                     // 多项式头节点
} Polys;

// 初始化多项式头节点
void InitPoly(Poly* &head){
    head = new Poly;
    head->next = NULL;
}

// 初始化多项式
void InitPolys(Polys &P){
    P.length = 0;
    InitPoly(P.head);
}

// 建立多项式(尾插法)
void CreatePolys(Polys &P){
    static int count = 1;
    Poly* rear = P.head;
    cout << "请输入第" << count << "个多项式项数: ";
    cin >> P.length;
    for(int i = 1; i <= P.length; i++){
        Poly* p = new Poly;
        cout << "请输入第" << i << "项的系数(带符号): ";
        cin >> p->c;
        cout << "请输入第" << i << "项的指数(带符号): ";
        cin >> p->e;
        p->next = rear->next;
        rear->next = p;
        rear = p;
    }
    count++;
}

// 输出多项式
void OutPutPolys(Polys P){
    Poly *p = P.head->next;
    if(p == NULL){
        cout << 0 <<endl;
        return;
    }
    for(int i = 0; i < P.length; i++){
        if(i && p->c > 0) cout << "+";
        if(p->c != 1) cout << p->c;
        else if(p->c == -1) cout << "-";
        if(p->e != 0){
            cout << "x";
            if(p->e != 1) cout << "^" << p->e;
        }
        // else if(p->e)
        p = p->next;
    }
    cout << endl;
}

// 按指数e降序对多项式排序
void SortPolys(Polys &P){
    Poly* p = P.head->next;
    for(int i = 0; i < P.length; i++){
        Poly* q = p->next;
        for(int j = i + 1; j < P.length; j++){
            if(q->e > p->e){
                float c_t = q->c, e_t = q->e;
                
                q->c = p->c;
                q->e = p->e;
                
                p->c = c_t;
                p->e = e_t;
            }
            q = q->next;
        }
        p = p->next;
    }
}

// 多项式加法
Polys AddPolys(Polys P1, Polys P2){
    SortPolys(P1);
    SortPolys(P2);
    Polys newP;
    InitPolys(newP);
    int count1 = 0, count2 = 0;;
    Poly *p1 = P1.head->next;
    Poly *p2 = P2.head->next;
    Poly *newp = newP.head;
    while(count1 < P1.length && count2 < P2.length){
        Poly* p = new Poly;
        // 指数相同, 系数相加
        if(p1->e == p2->e){
            p->e = p1->e;
            p->c = p1->c + p2->c;
            if(!p->c) p = NULL;
            p1 = p1->next;
            p2 = p2->next;
            count1++;
            count2++;
        }
        // 谁指数小, 谁在前面入链表
        else if(p1->e < p2->e){
            p->c = p1->c;
            p->e = p1->e;
            count1++;
            p1 = p1->next;
        }
        else if(p1->e > p2->e){
            p->c = p2->c;
            p->e = p2->e;
            count2++;
            p2 = p2->next;
        }
        // 尾插
        if(p){
            p->next = NULL;
            newp->next = p;
            newp = p;
            newP.length++;
        }
    }
    if(count1 < P1.length){
        newP.length += P1.length - count1;
        newp->next = p1;
    }
    else if(count2 < P2.length){
        newP.length += P2.length - count2;
        newp->next = p2;
    }
    return newP;
}

Polys SubPolys(Polys P1, Polys P2){
    SortPolys(P1);
    SortPolys(P2);
    Polys newP;
    InitPolys(newP);
    int count1 = 0, count2 = 0;;
    Poly *p1 = P1.head->next;
    Poly *p2 = P2.head->next;
    Poly *newp = newP.head;
    while(count1 < P1.length && count2 < P2.length){
        Poly* p = new Poly;
        // 指数相同, 系数相减
        if(p1->e == p2->e){
            p->e = p1->e;
            p->c = p1->c - p2->c;
            if(!p->c) p = NULL;
            p1 = p1->next;
            p2 = p2->next;
            count1++;
            count2++;
        }
        // 谁指数小, 谁在前面入链表
        else if(p1->e < p2->e){
            p->c = p1->c;
            p->e = p1->e;
            count1++;
            p1 = p1->next;
        }
        else if(p1->e > p2->e){
            p->c = p2->c;
            p->e = p2->e;
            count2++;
            p2 = p2->next;
        }
        // 尾插
        if(p){
            p->next = NULL;
            newp->next = p;
            newp = p;
            newP.length++;
        }
    }
    if(count1 < P1.length){
        newP.length += P1.length - count1;
        newp->next = p1;
    }
    else if(count2 < P2.length){
        newP.length += P2.length - count2;
        newp->next = p2;
    }
    return newP;
}

int main(){
    Polys P1, P2;
    InitPolys(P1);
    CreatePolys(P1);

    InitPolys(P2);
    CreatePolys(P2);

    Polys PA = AddPolys(P1, P2);
    cout << "P1 + P2:  ";
    OutPutPolys(PA);

    PA = AddPolys(P2, P1);
    cout << "P2 + P1:  ";
    OutPutPolys(PA);

    Polys PS = SubPolys(P1, P2);
    cout << "P1 - P2:  ";
    OutPutPolys(PS);

    PS = SubPolys(P2, P1);
    cout << "P2 - P1:  ";
    OutPutPolys(PS);

    return 0;
}
