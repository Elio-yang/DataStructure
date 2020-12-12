/*
 * @Author: alone_yue
 * @Date: 2020-11-26 08:13:49
 */
/*
 * @Author: alone_yue
 * @Date: 2020-11-24 11:07:40
 */
#include<iostream>
#include<stdlib.h>
using namespace std;

const int MaxVertex=310;//最大顶点个数
const int inf=0x3fffffff;//当边权为1000 代表没有边
#define DataType int 

class Astack {
public:
	DataType* stackArray;
	int top; int tail; //tail是末尾元素下表 top存放首元素下一个位置
public:
	Astack(int n=MaxVertex){
		stackArray = new DataType[n];
		top=0; tail=0;
	}
    // void Creat(int n){
    //     stackArray = new DataType[n];
	// 	top=0; tail=0;
    // }
	void topPush(DataType item){stackArray[top++] = item;}
	void topPop(){top--;}
	void tailPush(DataType item){stackArray[--tail]=item;}
	void tailPop(){tail++;}
	DataType intop(){return stackArray[top-1];}
	DataType intail(){return stackArray[tail];}
	int count(){return top-tail;}
	bool Isempty(){
		if(tail==top) return true;
		else return false;
	}
};

//边节点↓
class Edge{
friend class Graph_List;
private:
    int VerAdj;//顶点序号0.1,2...
    int cost;//边权
    Edge* next;//指向下一个边节点
};

//顶点表↓
class Vertex{
friend class Graph_List;
public:
    Vertex():VerName(-1),EdgeHead(nullptr){};
    //为了保证插入顶点,边的一致性初始化为nullptr
    //VerName=-1代表没有这个顶点
private:
    int VerName;//顶点名称0,1,2...
    Edge* EdgeHead;//指向边链表的第一个节点
};

//邻接表↓
class Graph_List{
private:
   
    Vertex* VertexArray;//指向顶点链表第一个节点
    int inDegree[MaxVertex]={0};//记录一个顶点的入度 初始化为0条入边 (用于拓扑排序)
   
    int NumVertex;//当前顶点数
    int NumEdge;//目前边数 v1->v2 v2->v1 算两条边
public:
    Graph_List();
    void Creat(int nvertex,int nedge);//创造nvertex个顶点 nedge条边1
    void InsertVertex1(int v);//新增顶点v 顶点的编号为v （一般是按顺序的没有说总共三个顶点 v=10的情况）
    void InsertEdge1(int v1,int v2,int value);//边链表头查 新增v1->v2一条边 边权为value v1v2已经存在只是加一条边
    void topoSort();
   
    //void Show()const;
};
Graph_List::Graph_List(){
    this->NumVertex=0;
    this->NumEdge=0;
    this->VertexArray=new Vertex[MaxVertex];
    //1this->topoOrder.Creat(MaxVertex);
}

void Graph_List::Creat(int nvertex,int nedge){
    //输入顶点
    for(int i=0;i<nvertex;i++){
        //int v; cin>>v;
        this->InsertVertex1(i);
    }
    //输入边
    for(int i=0;i<nedge;i++){
        int v1; int v2;   cin>>v1>>v2;
        int c; cin>>c;
        this->InsertEdge1(v1,v2,c);
    }
}
void Graph_List::InsertVertex1(int v){
    this->VertexArray[NumVertex++].VerName=v;
}
void Graph_List::InsertEdge1(int v1,int v2,int value){
    this->inDegree[v2]++;
    Edge* p=new Edge;
    p->VerAdj=v2; p->cost=value; p->next=nullptr;

    Edge* t0=nullptr;
    Edge* t1=this->VertexArray[v1].EdgeHead;
    while(t1!=nullptr&&t1->VerAdj<p->VerAdj){
        t0=t1;
        t1=t1->next;
    }

    if(t0==nullptr&&t1==nullptr){
        this->VertexArray[v1].EdgeHead=p;
        p->next=nullptr;
    }
    if(t0!=nullptr&&t1==nullptr){
        p->next=nullptr;
        t0->next=p;
    }
    if(t0==nullptr&&t1!=nullptr){
        p->next=this->VertexArray[v1].EdgeHead;
        this->VertexArray[v1].EdgeHead=p;
    }
    if(t0!=nullptr&&t1!=nullptr){
        p->next=t1;
        t0->next=p;
    }
    this->NumEdge++;
}
void Graph_List::topoSort(){
    //记录加入拓扑序列的个数 当一个顶点出队才代表加入拓扑序列
    int num=0; Astack q;
    Astack temp;
    //先将所有入度为零的都进队列 
    //这个操作只进行一次也就是只将最初的图的第一层入队
    for(int i=0;i<this->NumVertex;i++){
        if(this->inDegree[i]==0){
            q.topPush(i);
        } 
    }
    //循环找出拓扑序列
    while(!q.Isempty()){
        int u=q.intail(); q.tailPop(); //this->topoOrder.topPush(u); 
        cout<<u<<" "; num++;

        //将u所有能直接到达的顶点入度都减一 剪完能入队的入队 并且把整个边链表都删除了
        Edge* p=this->VertexArray[u].EdgeHead;
        while(p!=nullptr){
            this->inDegree[p->VerAdj]--;
            if(this->inDegree[p->VerAdj]==0){
                while(!q.Isempty()&&p->VerAdj<q.intop()){
                    temp.tailPush(q.intop()); q.topPop();
                }
                q.topPush(p->VerAdj);
                while(!temp.Isempty()){
                    q.topPush(temp.intop()); temp.topPop();
                }
            }
            p=p->next;
        }
    
    }
    cout<<endl;
}

int main(){
    int n,e; cin>>n>>e;
    Graph_List G; G.Creat(n,e);
    
    G.topoSort();
    system("pause");
    return 0;

}
/*
9 12
0 3 
0 4 
0 5 
1 5 
2 3 
2 8 
3 6 
3 7 
4 8 
5 7 
5 8 
6 7 
*/