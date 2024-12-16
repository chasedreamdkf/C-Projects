#include <iostream>
using namespace std;

typedef struct {
	/**顾客
	 * num(int): 顾客编号
	 * time(int): 顾客结账所花时间
	 */
	int num;
	int time;
} Client;

typedef struct counter {
	/** 收银台
	 * clinet(Client): 来该收银台结账的顾客
	 * next(Counter*): 指向链队列的下一个元素
	 */
	Client clinet;
	struct counter* next;
} Counter;

typedef struct {
	/**存放队列的头指针front，尾指针rear */
	Counter* front;
	Counter* rear;
} Queue;

void QueueInit(Queue& Q) { /*链队列初始化 */
	Q.front = Q.rear = new Counter;
	Q.front->next = NULL;
}

void EnQueue(Queue& Q, Client client) { /*链队列入队 */
	Counter* p = new Counter;
	p->clinet = client;
	p->next = Q.rear->next;
	Q.rear = p;
}

int DeQueue(Queue& Q, Client& client) { /*链队列出队 */
	cout << "0";
	if (Q.front == Q.rear) {
		return 0;
	}
	else {
		Counter* p = new Counter;
		cout << "1";
		p = Q.front->next;
		cout << "2";
		client = p->clinet;
		cout << "3";
		Q.front->next = p->next;
		cout << "4";
		if (p == Q.rear)
			Q.rear = Q.front;
		delete p;
	}
	return 1;
}

int main() {
	int n; /*顾客数量*/
	Client client;
	Queue counter1, counter2;
	int time1 = 0, time2 = 0;
	QueueInit(counter1);
	QueueInit(counter2);
	cin >> n;
	// cin >> client.num >> client.time;
	// time1 += client.time;
	// EnQueue(counter1, client);
	// cin >> client.num >> client.time;
	// time2 += client.time;
	// EnQueue(counter2, client);
	for (int i = 1; i <= n; i++) {
		if (time1 > time2) {
			time1 -= time2;
			time2 -= time2;
		}
		else if (time1 < time2) {
			time2 -= time1;
			time1 -= time1;
		}
		cin >> client.num >> client.time;
		if (time1 == 0) {
			time1 += client.time;
			EnQueue(counter1, client);
		}
		else if (time2 == 0) {
			time2 += client.time;
			EnQueue(counter2, client);
		}
	}
	cout << "counter1:" << endl;
	int t = 0;
	while (DeQueue(counter1, client)) {
		cout << client.num << " " << client.time << " " << t << endl;
		t += client.time;
	}
	return 0;
}
