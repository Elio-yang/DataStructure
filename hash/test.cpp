#include <iostream>
#define MAX 100
#define MAXQ 50
using namespace std;

struct edgeNode
{
        int no;                //边端的序号
        int info;             //边端的名称
        struct edgeNode *next; //下一个
};

struct vexNode
{
        int info;             //节点名称
        struct edgeNode *link; //与之相连的端点
};

//存储节点信息
vexNode adjlist[MAX];
//循环队列
int queue[MAXQ];
//访问标志
bool visited[MAX];
//存储从指定点到每一个点的路径
int parent[MAX];

//建立邻接表存储,返回节点个数
int createGraph(vexNode *adjlist)
{
        int n, e;
        cout << "请输入节点数：";
        cin >> n;
        cout << "请输入边数：";
        cin >> e;
        int i;
        for (i = 1; i <= n; i++)
        {
                adjlist[i].info=i;
                adjlist[i].link = NULL;
        }
        edgeNode *p1, *p2;
        int v1, v2;
        for (i = 1; i <= e; i++)
        {
                cout << "请输入边" << i << "的二端的节点序号：";
                cin >> v1 >> v2;
                p1 = (edgeNode *)malloc(sizeof(edgeNode));
                p2 = (edgeNode *)malloc(sizeof(edgeNode));
                p1->no = v1;
                p1->info = adjlist[v1].info;
                p1->next = adjlist[v2].link;
                adjlist[v2].link = p1;
                p2->no = v2;
                p2->info = adjlist[v2].info;
                p2->next = adjlist[v1].link;
                adjlist[v1].link = p2;
        }
        return n;
}

//广度优先搜索无向无权图,返回起始点
int BFS(vexNode *adjlist, int *queue, bool *visited, int *parent)
{
        int front, rear, v1;
        cout << "请输入从哪个序号的点开始搜索：";
        cin >> v1;
        front = 0;
        rear = 1;
        queue[rear] = v1;
        int i;
        //访问标志清空
        for (i = 1; i < MAX; i++)
                visited[i] = false;
        visited[v1] = true;
        cout << "广度优先搜索次序为：" << endl;
        cout << "节点" << v1 << ",名称" << adjlist[v1].info << endl;
        int vx;
        edgeNode *p;
        while (front != rear)
        {
                front = (front + 1) % MAXQ;
                vx = queue[front];
                p = adjlist[vx].link;
                while (p != NULL)
                {
                        if (!visited[p->no])
                        {
                                visited[p->no] = true;
                                cout << "节点" << p->no << ",名称" << adjlist[p->no].info << endl;
                                rear = (rear + 1) % MAXQ;
                                queue[rear] = p->no;
                                parent[p->no] = vx;
                        }
                        p = p->next;
                }
        }
        return v1;
}

//打印起始点到目标节点的最少边数目的路径（最短路径）
//v是目标节点
void print_line(vexNode *adjlist, int *parent, int v)
{
        int j = v;
        if (parent[j] != 0)
                print_line(adjlist, parent, parent[j]);
        cout << adjlist[j].info << "  ";
}

int main(int argc, char *argv[])
{
        
        //创建邻接表
        int n = createGraph(adjlist);
        //广度优先搜索
        int v1 = BFS(adjlist, queue, visited, parent);
        //起始节点没有前驱节点
        parent[v1] = 0;
        int v;
        cout << "请输入目标节点：";
        cin >> v;
        //打印起始点到目标节点的最少边数目的路径（最短路径）
        cout << "从起始节点" << adjlist[v1].info << "到" << adjlist[v].info << "节点的最短路径为：" << endl;
        print_line(adjlist, parent, v);
        cout << endl;
        
        system("pause");
        return 0;
}