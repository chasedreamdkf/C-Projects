#include <iostream>
#include <cmath>
using namespace std;

// 多项式的每一项
typedef struct Poly{
    float c;                            // 多项式每一项的系数
    float e;                            // 多项式每一项的指数
    struct Poly* next;                  // 多项式的下一项
} Poly;

class Polys{
    int num;                            // 多项式编号
    int length;                         // 多项式长度
    Poly *head;                         // 多项式头节点
};

