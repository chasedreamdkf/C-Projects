#include <iostream>
#include <cmath>
using namespace std;

// ����ʽ��ÿһ��
typedef struct Poly{
    float c;                            // ����ʽÿһ���ϵ��
    float e;                            // ����ʽÿһ���ָ��
    struct Poly* next;                  // ����ʽ����һ��
} Poly;

// ����ʽ
typedef struct Polys{
    int num;                            // ����ʽ���
    int length;                         // ����ʽ����
    Poly *head;                         // ����ʽͷ�ڵ�
} Polys;

// ��ʼ������ʽ
void InitPolys(Polys &P){
    static int num = 1;
    P.num = num;
    P.length = 0;                       // ����ʽ��ʼ����Ϊ0
    P.head = new Poly;
    P.head->next = NULL;                // ��ʼ����ʽ����Ϊ��
    num++;
}

// ��ָ��e����Զ���ʽ����(����)
void SortPolys(Polys &P){
    Poly* p = P.head->next;
    for(int i = 0; i < P.length; i++){
        Poly* q = p->next;
        for(int j = i + 1; j < P.length; j++){
            if(q->e > p->e){            // ��������
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

// ��(�ϲ�ͬ����)����ʽ
void SimplifyPolys(Polys &P){
    SortPolys(P);                       // �ȶԶ���ʽ����
    Poly *p = P.head->next;
    for(int i = 1; i < P.length; i++){
        if(p->e == p->next->e){         // �����ڵ���ϲ�������ʽ���ȼ�1
            p->c += p->next->c;
            Poly* q = p->next;
            p->next = q->next;
            delete q;
            --P.length;
        }
        p = p->next;
    }
}

// ��������ʽ(β�巨)
void CreatePolys(Polys &P){
    Poly* rear = P.head;
    cout << "���������ʽ" << "P" << P.num << "������: ";
    cin >> P.length;
    for(int i = 1; i <= P.length; i++){
        Poly* p = new Poly;
        cout << "�������" << i << "���ϵ��(������)��ָ��(������): ";
        cin >> p->c >> p->e;
        p->next = rear->next;
        rear->next = p;
        rear = p;
    }
    SimplifyPolys(P);
}

// �������ʽ
void OutPutPolys(Polys P, bool line_feed = true){
    /**line_feed: ��������Ƿ��У�Ĭ��Ϊtrue */
    Poly *p = P.head->next;
    if(p == NULL){
        cout << 0;
        if(line_feed) cout << endl;
        return;
    }
    for(int i = 0; i < P.length; i++){
        if(i && p->c > 0) cout << "+";
        if(p->c == -1 && p->e) cout << "-";
        else if(p->c == 1 && !p->e) cout << p->c;
        else if(p->c != 1) cout << p->c;
        if(p->e != 0){
            cout << "x";
            if(p->e != 1) cout << "^" << p->e;
        }
        
        p = p->next;
    }
    if(line_feed)
        cout << endl;
}

// ����ʽ�ӷ�
Polys AddPolys(Polys P1, Polys P2){
    // ���������ж��Ƿ񵽴����ʽβ��(��֪Ϊʲô��������ʽʱ��ദһ�c��e������Χ)
    int count1 = 0, count2 = 0;

    Poly *p1 = P1.head->next;
    Poly *p2 = P2.head->next;

    // if P1 == 0, P1 + P2 = P2
    if(!p1) return P2;
    // if P2 == 0, P1 + P2 = P1
    if(!p2) return P1;

    Polys newP;
    InitPolys(newP);

    // βָ��
    Poly *newp = newP.head;

    // ����ʽ����(ָ������)�ӷ�
    while(count1 < P1.length && count2 < P2.length){
        Poly* p = new Poly;
        // ָ����ͬ, ϵ�����
        if(p1->e == p2->e){
            p->e = p1->e;
            p->c = p1->c + p2->c;
            if(!p->c) p = NULL;
            p1 = p1->next;
            p2 = p2->next;
            count1++;
            count2++;
        }
        // ˭ָ����, ˭��ǰ��������
        else if(p1->e > p2->e){
            p->c = p1->c + 0;                   // ��ʱ����p1.e��ȵ�p2.e��ϵ��c=0
            p->e = p1->e;
            count1++;
            p1 = p1->next;
        }
        else if(p1->e < p2->e){
            p->c = p2->c + 0;                   // ��ʱ����p2.e��ȵ�p1.e��ϵ��c=0
            p->e = p2->e;
            count2++;
            p2 = p2->next;
        }
        // β��
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

// ����ʽ����
Polys SubPolys(Polys P1, Polys P2){
    // ���������ж��Ƿ񵽴����ʽβ��(��֪Ϊʲô��������ʽʱ��ദһ�c��e������Χ)
    int count1 = 0, count2 = 0;

    Poly *p1 = P1.head->next;
    Poly *p2 = P2.head->next;

    Polys newP;
    InitPolys(newP);

    // βָ��
    Poly *newp = newP.head;

    // if P1 == 0, P1 - P2 = -P2
    if(!p1){
        // P1 == 0ʱ����P2��ϵ��ȡ�෴��
        while(count2 < P2.length){
            Poly* p = new Poly;
            // ȡ�෴��
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
    // if P2 == 0, P1 - P2 = P1
    if(!p2) return P1;

    while(count1 < P1.length && count2 < P2.length){
        Poly* p = new Poly;
        // ָ����ͬ, ϵ�����
        if(p1->e == p2->e){
            p->e = p1->e;
            p->c = p1->c - p2->c;
            if(!p->c) p = NULL;
            p1 = p1->next;
            p2 = p2->next;
            count1++;
            count2++;
        }
        // ˭ָ����, ˭��ǰ��������
        else if(p1->e > p2->e){
            p->c = p1->c - 0;                       // ��ʱ����p1.e��ȵ�p2.e��ϵ��c=0
            p->e = p1->e;
            count1++;
            p1 = p1->next;
        }
        else if(p1->e < p2->e){
            p->c = 0 - p2->c;                      // ��ʱ����p2.e��ȵ�p1.e��ϵ��c=0
            p->e = p2->e;
            count2++;
            p2 = p2->next;
        }
        // β��
        if(p){
            p->next = NULL;
            newp->next = p;
            newp = p;
            newP.length++;
        }
    }
    // ʣ�ಿ�ֽ���������ʽ����
    // P1��ʣ�ֱ࣬�ӽ���
    if(count1 < P1.length){
        newP.length += P1.length - count1;
        newp->next = p1;
    }
    // P2��ʣ�࣬��P2��ϵ��ȡ�෴������
    else if(count2 < P2.length){
        newP.length += P2.length - count2;
        while(count2 < P2.length){
            Poly* p = new Poly;
            // ȡ�෴��
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

// ����ʽ��x����ֵ
float Polys_Val_In_X(Polys P){
    float X, sum = 0;
    cout << "������X��ֵ: ";
    cin >> X;
    Poly* p = P.head->next;
    for(int i = 1; i <= P.length; i++, p = p->next){
        sum += p->c * pow(X, p->e);
    }
    return sum;
}

// �����ʽP�ĵ���P��
Polys Polys_Derivative(Polys P){
    Polys newP;
    InitPolys(newP);

    // βָ��
    Poly* newp = newP.head;
    Poly* p = P.head->next;

    for(int i = 1; i <= P.length; i++, p = p->next){
        if(p->e == 0) continue;         // ������, ����Ϊ��, ������һ��

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

// ��������ʽ���
Polys MultiPolys(Polys P1, Polys P2){
    Polys LastP;                            // �������ʽ
    InitPolys(LastP);

    // if P1 == 0 Or P2 == 0, P1 X P2 = 0
    if(!P1.length || !P2.length) return LastP;
    // if P1 != 0 And P2 != 0
    Poly* p1 = P1.head->next;
    for(int i = 1; i <= P1.length; i++){
        Polys TP;
        InitPolys(TP);
        Poly* rear = TP.head;

        // ��P1�ĵ�i����P2��ˣ���������TP��
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

        // ��TP����LastP��
        LastP = AddPolys(LastP, TP);

        p1 = p1->next;
    }

    return LastP;
}

// �˵�
void menu(){
    cout << "|===============����ʽ����===============|" << endl;
    cout << "|--------------1.����ʽ�ӷ�--------------|" << endl;
    cout << "|--------------2.����ʽ����--------------|" << endl;
    cout << "|--------------3.����ʽ��--------------|" << endl;
    cout << "|-----------4.����ʽ��X����ֵ------------|" << endl;
    cout << "|--------------5.����ʽ�˷�--------------|" << endl;
    cout << "|������������ѡ����, ���������˳�: ";
}

// �˳�����
void quit(){
    //system("clear");     // ����Linux������ʹ��
    //system("cls");          // ����Windows������ʹ��
    cout << "��лʹ��ϡ�����ʽ��������\n�ټ���" << endl;
}

// �û�����
void UserGraph(){
    int flag = 0;
    do{
        menu();
        cin >> flag;
        switch (flag){
            case 1:{
                Polys P1, P2;
                InitPolys(P1);
                CreatePolys(P1);
                InitPolys(P2);
                CreatePolys(P2);
                Polys P3 = AddPolys(P1, P2);
                cout << '(';
                OutPutPolys(P1, false);
                cout << ") + (";
                OutPutPolys(P2, false);
                cout << ") = ";
                OutPutPolys(P3);

                P3 = AddPolys(P2, P1);
                cout << '(';
                OutPutPolys(P2, false);
                cout << ") + (";
                OutPutPolys(P1, false);
                cout << ") = ";
                OutPutPolys(P3);
            }; break;
            case 2: {
                Polys P1, P2;
                InitPolys(P1);
                CreatePolys(P1);
                InitPolys(P2);
                CreatePolys(P2);

                Polys P3 = SubPolys(P1, P2);
                cout << '(';
                OutPutPolys(P1, false);
                cout << ") - (";
                OutPutPolys(P2, false);
                cout << ") = ";
                OutPutPolys(P3);

                P3 = SubPolys(P2, P1);
                cout << '(';
                OutPutPolys(P2, false);
                cout << ") - (";
                OutPutPolys(P1, false);
                cout << ") = ";
                OutPutPolys(P3);
            }; break;
            case 3: {
                Polys P1;
                InitPolys(P1);
                CreatePolys(P1);
                Polys P3 = Polys_Derivative(P1);
                cout << "P" << P1.num << "' = ";
                OutPutPolys(P3);
            }; break;
            case 4: {
                Polys P1;
                InitPolys(P1);
                CreatePolys(P1);
                float sum = Polys_Val_In_X(P1);
                OutPutPolys(P1, false);
                cout << " = " << sum << endl;
            }; break;
            case 5: {
                Polys P1, P2;
                InitPolys(P1);
                CreatePolys(P1);
                InitPolys(P2);
                CreatePolys(P2);

                Polys P3 = MultiPolys(P1, P2);
                cout << '(';
                OutPutPolys(P1, false);
                cout << ") X (";
                OutPutPolys(P2, false);
                cout << ") = ";
                OutPutPolys(P3);

                P3 = MultiPolys(P2, P1);
                cout << '(';
                OutPutPolys(P2, false);
                cout << ") X (";
                OutPutPolys(P1, false);
                cout << ") = ";
                OutPutPolys(P3);
            }; break;
            
            default: {
                flag = 0;
                quit();
            } ;break;
        }
        //������������Windows������ʹ��
        system("pause");
        system("cls");
        
    }while(flag);
}

int main(){
    UserGraph();
    return 0;
}
