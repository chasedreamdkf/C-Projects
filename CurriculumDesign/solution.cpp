#include <iostream>
using namespace std;

// 多项式的每一项
typedef struct Poly{
    char sign;                      // 多项式每一项的正负符号
    int c;                          // 多项式每一项的系数
    int e;                          // 多项式每一项的指数
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
    int n;
    cout << "请输入多项式项数: ";
    cin >> n;
    P.length = n;
    InitPoly(P.head);
}

// 建立多项式(尾插法)
void CreatePolys(Polys &P){
    Poly* rear = P.head;
    for(int i = 1; i <= P.length; i++){
        Poly* p = new Poly;
        cout << "请输入第" << i << "项的符号: ";
        cin >> p->sign;
        if(p->sign != '+' || p->sign != '+'){
            cout << "输入错误, 请重新输入: ";
            cin >> p->sign;
        }
        cout << "请输入第" << i << "项的系数: ";
        cin >> p->c;
        cout << "请输入第" << i << "项的指数: ";
        cin >> p->e;
        p->next = rear->next;
        rear->next = p;
        rear = p;
    }
}

// 输出多项式
void OutPutPolys(Polys P){
    Poly *p = P.head->next;
    if(p == NULL) cout << '0' <<endl;
    for(int i = 0; i < P.length; i++){
        // if(!i && p->sign == '+')
        cout << p->sign;
        cout << p->c;
        cout << "x^";
        cout << p->e;
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
                char sign_t = q->sign;
                int c_t = q->c, e_t = q->e;
                
                q->sign = p->sign;
                q->c = p->c;
                q->e = p->e;
                
                p->sign =sign_t;
                p->c = c_t;
                p->e = e_t;
            }
            q = q->next;
        }
        p = p->next;
    }
}

// // 多项式加法
// Polys AddPolys(Polys P1, Polys P2){
//     Polys newP;
//     InitPolys(newP);
//     int count1 = 1, count2 = 1;;
//     Poly *p1 = P1.head->next;
//     Poly *p2 = P2.head->next;
//     Poly *newp = newP.head;
//     while(count1 < P1.length && count2 < P2.length){
        
//     }
// }

int main(){
    Polys P1;
    InitPolys(P1);
    CreatePolys(P1);
    OutPutPolys(P1);
    SortPolys(P1);
    cout << "排序后:" << endl;
    OutPutPolys(P1);
    return 0;
}
