#include <iostream>
using namespace std;

#define MVNum 100							//最大顶点数
typedef char VerTexType;					//假设顶点的数据类型为字符型 
#define MAXQSIZE 100						//最大队列长度.
typedef int ArcType;                  		//假设边的权值类型为整型

//-------------图的邻接表---------------------
typedef struct ArcNode{                		//边结点 
    int adjvex;                          	//该边所指向的顶点的位置 
    struct ArcNode *nextarc;          		//指向下一条边的指针 
}ArcNode; 

typedef struct VNode{ 
    VerTexType data;                    	//顶点信息
    ArcNode *firstarc;                		//指向第一条依附该顶点的边的指针 
}VNode, AdjList[MVNum];               		//AdjList表示邻接表类型 

typedef struct{
    AdjList vertices;                 		//邻接表 
    int vexnum, arcnum;              		//图的当前顶点数和边数 
}ALGraph;

bool visited[MVNum];           				//访问标志数组，其初值为"false" 

//----队列的定义及操作--------  用于邻接表的广度优先搜索遍历
typedef struct{
	ArcType *base;							//初始化的动态分配存储空间
	int front;								//头指针，若队列不空，指向队头元素
	int rear;								//尾指针，若队列不空，指向队尾元素的下一个位置
}sqQueue;

void InitQueue(sqQueue &Q){
	//构造一个空队列Q
	Q.base = new ArcType[MAXQSIZE];
	if(!Q.base)     exit(1);				//存储分配失败
	Q.front = Q.rear = 0;
}//InitQueue

void EnQueue(sqQueue &Q, ArcType e){
	//插入元素e为Q的新的队尾元素
	if((Q.rear + 1) % MAXQSIZE == Q.front)
		return;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
}//EnQueue

bool QueueEmpty(sqQueue Q){
	//判断是否为空队
	if(Q.rear == Q.front)
		return true;
	return false;
}//QueueEmpty

void DeQueue(sqQueue &Q, ArcType &u){
	//队头元素出队并置为u 
	u = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
}//DeQueue

int LocateVex(ALGraph G , VerTexType v){
	//确定点v在G中的位置
	for(int i = 0; i < G.vexnum; ++i)
		if(G.vertices[i].data == v)
			return i;
		return -1;
}//LocateVex

void CreateUDG(ALGraph &G){ 
	//采用邻接表表示法，创建无向图G
	int i , k;
	cin >> G.vexnum >> G.arcnum;				//输入总顶点数，总边数

	for(i = 0; i < G.vexnum; ++i){          	//输入各点，构造表头结点表
		//cout << "请输入第" << (i+1) << "个点的名称:";
		cin >> G.vertices[i].data;           	//输入顶点值 
		G.vertices[i].firstarc=NULL;			//初始化表头结点的指针域为NULL 
    }

	for(k = 0; k < G.arcnum;++k){        		//输入各边，构造邻接表
		VerTexType v1 , v2;
		int i , j;
		cin >> v1 >> v2;                 		//输入一条边依附的两个顶点
		i = LocateVex(G, v1);  j = LocateVex(G, v2);
		//确定v1和v2在G中位置，即顶点在G.vertices中的序号 
		
		ArcNode *p1=new ArcNode;               	//生成一个新的边结点*p1 
		p1->adjvex=j;                   		//邻接点序号为j 
		p1->nextarc= G.vertices[i].firstarc;  G.vertices[i].firstarc=p1;  
		//将新结点*p1插入顶点vi的边表头部
		
		ArcNode *p2=new ArcNode;                //生成另一个对称的新的边结点*p2 
		p2->adjvex=i;                   		//邻接点序号为i 
		p2->nextarc= G.vertices[j].firstarc;  G.vertices[j].firstarc=p2;  
		//将新结点*p2插入顶点vj的边表头部 
    }//for 
}//CreateUDG

void DFS(ALGraph G, int v){        				//采用邻接表表示图的深度度优先搜索遍历
	cout << G.vertices[v].data << " ";  
	visited[v] = true;    						//访问第v个顶点，并置访问标志数组相应分量值为true 
	ArcNode *p = G.vertices[v].firstarc;		//p指向v的边链表的第一个边结点 
	while(p != NULL){              				//边结点非空 
		int w = p->adjvex;               		//表示w是v的邻接点 
		if(!visited[w])  DFS(G, w);   			//如果w未访问，则递归调用DFS 
		p = p->nextarc;                			//p指向下一个边结点 
	} 
}//DFS

void BFS(ALGraph G, int v){     //采用邻接表表示图的广度优先搜索遍历
    sqQueue Q;
    InitQueue(Q);
    EnQueue(Q, v);
    visited[v] = true;
    while(!QueueEmpty(Q)){
        ArcType u;
        DeQueue(Q, u);
        cout << G.vertices[u].data << " ";
        ArcNode *p = G.vertices[u].firstarc;
        while(p != NULL){
            int w = p->adjvex;
            if(!visited[w]){
                EnQueue(Q, w);
                visited[w] = true;
            }
            p = p->nextarc;
        }
    }
}
// 以邻接表表示无向图，实现判断无向图中两个顶点是否连通的算法。连通: connected。未连通: disconnected.
bool isConnected(ALGraph G, VerTexType v1, VerTexType v2){
    int v1_index = LocateVex(G, v1);
    int v2_index = LocateVex(G, v2);
    
    for(int i = 0; i < G.vexnum; ++i){
        visited[i] = false;
    }
    
    DFS(G, v1_index);
    
    return visited[v2_index];
}

int main(){
	ALGraph G;
	CreateUDG(G);
	VerTexType c;
	cin >> c;
	
	int i;
	for(i = 0 ; i < G.vexnum ; ++i){
		if(c == G.vertices[i].data)
			break;
	}
    VerTexType a, b;
    cin >> a >> b;
    if(isConnected(G, a, b))
        cout << "connected" << endl;
    else
        cout << "disconnected" << endl;
	return 0;
}