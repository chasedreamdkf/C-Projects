#include <iostream>
#include <cmath>
using namespace std;

// 多项式的每一项
typedef struct Poly{
    float c;                            // 多项式每一项的系数
    float e;                            // 多项式每一项的指数
    struct Poly* next;                  // 多项式的下一项
} Poly;

// 多项式
typedef struct Polys{
    int length;                         // 多项式长度
    Poly *head;                         // 多项式头节点
} Polys;

// 初始化多项式
void InitPolys(Polys &P){
    P.length = 0;
    P.head = new Poly;
    P.head->next = NULL;
}

// 建立多项式(尾插法)
void CreatePolys(Polys &P){
    static int count = 1;
    Poly* rear = P.head;
    cout << "请输入多项式" << "P" << count << "的项数: ";
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
        if(p->c == -1) cout << "-";
        else if(p->c != 1) cout << p->c;
        if(p->e != 0){
            cout << "x";
            if(p->e != 1) cout << "^" << p->e;
        }
        else if(!p->e) cout << p->c;
        p = p->next;
    }
    cout << endl;
}

// 按指数e降序对多项式排序(冒泡)
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

    // 计数器，判定是否到达多项式尾部(不知为什么创建多项式时会多处一项，c、e超出范围)
    int count1 = 0, count2 = 0;

    Poly *p1 = P1.head->next;
    Poly *p2 = P2.head->next;

    // if P1 == 0
    if(!p1) return P2;
    // if P2 == 0
    if(!p2) return P1;

    Polys newP;
    InitPolys(newP);

    // 尾指针
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
        // 谁指数大, 谁在前面入链表
        else if(p1->e > p2->e){
            p->c = p1->c + 0;                   // 此时，与p1.e相等的p2.e的系数c=0
            p->e = p1->e;
            count1++;
            p1 = p1->next;
        }
        else if(p1->e < p2->e){
            p->c = p2->c + 0;                   // 此时，与p2.e相等的p1.e的系数c=0
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

// 多项式减法
Polys SubPolys(Polys P1, Polys P2){
    SortPolys(P1);
    SortPolys(P2);

    // 计数器，判定是否到达多项式尾部(不知为什么创建多项式时会多处一项，c、e超出范围)
    int count1 = 0, count2 = 0;

    Poly *p1 = P1.head->next;
    Poly *p2 = P2.head->next;

    Polys newP;
    InitPolys(newP);

    // 尾指针
    Poly *newp = newP.head;

    // if P1 == 0
    if(!p1){
        // P1 = 0时，对P2的系数取相反数
        while(count2 < P2.length){
            Poly* p = new Poly;
            // 取相反数
            p->c = -p2->c;
            p->e = p2->e;
            p->next = NULL;

            newp->next = p;
            newp = p;
            newP.length++;
            
            count2++;
            p2 = p2->next;
        }
        return newP;
    }
    // if P2 == 0
    if(!p2) return P1;

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
        // 谁指数大, 谁在前面入链表
        else if(p1->e > p2->e){
            p->c = p1->c - 0;                       // 此时，与p1.e相等的p2.e的系数c=0
            p->e = p1->e;
            count1++;
            p1 = p1->next;
        }
        else if(p1->e < p2->e){
            p->c = 0 - p2->c;                      // 此时，与p2.e相等的p1.e的系数c=0
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
        while(count2 < P2.length){
            Poly* p = new Poly;
            // 取相反数
            p->c = -p2->c;
            p->e = p2->e;
            p->next = NULL;

            newp->next = p;
            newp = p;
            
            count2++;
            p2 = p2->next;
        }
    }
    return newP;
}

// 多项式在x处的值
float Polys_Val_In_X(Polys P){
    float X, sum = 0;
    cout << "请输入X的值: ";
    cin >> X;
    Poly* p = P.head->next;
    for(int i = 1; i <= P.length; i++, p = p->next){
        sum += p->c * pow(X, p->e);
    }
    return sum;
}

// 求多项式P的导数P’
Polys Polys_Derivative(Polys P){
    Polys newP;
    InitPolys(newP);

    // 尾指针
    Poly* newp = newP.head;
    Poly* p = P.head->next;

    for(int i = 1; i <= P.length; i++, p = p->next){
        if(p->e == 0) continue;         // 常数项, 导数为零, 跳到下一项

        Poly* t = new Poly;
        t->c = p->c * p->e;
        t->e = p->e - 1;
        t->next = NULL;
        newP.length++;
        
        newp->next = t;
        newp = t;
    }
    return newP;
}

// 两个多项式相乘
Polys MultiPolys(Polys P1, Polys P2){
    SortPolys(P1);
    SortPolys(P2);

    Polys LastP;
    InitPolys(LastP);

    // if P1 == 0 Or P2 == 0
    if(!P1.length || !P2.length) return LastP;
    // if P1 != 0 And P2 != 0
    Poly* p1 = P1.head->next;
    for(int i = 1; i <= P1.length; i++){
        Polys TP;
        InitPolys(TP);
        Poly* rear = TP.head;

        Poly* p2 = P2.head->next;
        for(int j = 1; j <= P2.length; j++){
            Poly* t = new Poly;
            t->c = p1->c * p2->c;
            t->e = p1->e + p2->e;
            t->next = NULL;

            rear->next = t;
            rear = t;

            TP.length++;

            p2 = p2->next;
        }

        LastP = AddPolys(LastP, TP);

        p1 = p1->next;
    }

    return LastP;
}

int main(){
    Polys P1;
    InitPolys(P1);
    CreatePolys(P1);

    Polys P2;
    InitPolys(P2);
    CreatePolys(P2);

    Polys P3 = MultiPolys(P1, P2);
    cout << "P1 X P2 = ";
    OutPutPolys(P3);

    return 0;
}
