#include <stdio.h>
#include <stdlib.h>
#define MAX 200

struct matrix{
    int *vex;//顶点信息
    int **adjmatrix;//边信息
    int vexnum,arcnum;//顶点，边个数
};

typedef struct matrix Matrix;

struct arcnode
{
    int adjvex;//节点在头数组中下标
    struct arcnode *nextarc;
};
typedef struct arcnode ArcNode;

struct vnode
{
    int date;
    ArcNode *firstarc;
};

typedef struct vnode Vnode;

struct stack
{
    int node;
    struct stack *next;
};
typedef struct stack STACK;

struct string
{
    int node[MAX];
    int front,last;
};
typedef struct string STRING;


void InitGraph(Vnode *Graph);
void InitMatrix(Matrix MAP);

void InputGraphvex(Vnode *Graph);
void InPutGrapharc(Vnode *Graph);
void Add(int n,ArcNode *string);
int IsEmpty(ArcNode *string);
void Change1(Vnode *Graph,Matrix MAP);
//void Change2(Vnode *Graph,Matrix MAP);
void DFSGTravers(Vnode *Graph,int *DFScount);
void DFSG(Vnode *Graph,int root,int *visited,FILE *fp,int *DFScount,int count);

int v;//点
int a;//边

int main()
{
    Vnode *Graph;
    Matrix MAP;
    int i;
    //Graph
    int *DFSGcount;//递归深度优先编号
    int *NDFSGv;//非递归深度优先序列
    int *NDFSGcount;//非递归深度优先编号
    //MAP
    int *DFSMcount;//递归深度优先编号
    int *NDFSMv;//非递归深度优先序列
    int *NDFSMcount;//非递归深度优先编号
    //Graph BFS
    int *BFSGv;
    int *BFSGcount;
    //MAP BFS
    int *BFSMv;
    int *BFSMcount;


    printf("the number of vexnum is:");
    scanf("%d",&v);
    printf("the number of arcnum is:");
    scanf("%d",&a);

    InitGraph(Graph);
    InputGraphvex(Graph);

    InPutGrapharc(Graph);

    InitMatrix(MAP);
    //DFS
    InitSave(DFSGcount);
    InitSave(NDFSGcount);
    InitSave(NDFSGv);

    InitSave(DFSMcount);
    InitSave(NDFSMcount);
    InitSave(NDFSMv);

    DFSGTravers(Graph,DFSGcount);

    //BFS
    InitSave(BFSGcount);
    InitSave(BFSGv);

    InitSave(BFSMcount);
    InitSave(BFSMv);





    return 0;
}

void InitGraph(Vnode *Graph)
{
    Graph = (Vode *)malloc(v*sizeof(Vnode));
    for(int i=0;i<v;i++)
    {
        Graph[i].date=-1;
        Graph[i].firstarc=NULL;
    }//初始化
}

void InitMatrix(Matrix MAP)
{
    MAP.vexnum=v;
    MAP.arcnum=a;
    MAP.vex=(int *)malloc(v*sizeof(int));
    MAP.adjmatrix=(int **)malloc(v*sizeof(MAP.vex));
    for(int i=0;i<v;i++){
        MAP.vex[i]=-1;
    }
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            MAP.adjmatrix[i][j]=0;
        }
    }
}
void InputGraphvex(Vnode *Graph)
{
    FILE *fp;
    int i=0;
    fp = fopen("vex information.txt","r+");
    if(fp==NULL){
        printf("open error...\n");
        exit(0);
    }
    while(1==fscanf(fp,"%d ",&Graph[i].date))
    {
        i++;
    }
    fclose(fp);
}

void InPutGrapharc(Vnode *Graph)
{
    FILE *fp;
    int m,n;
    fp = fopen("arc information.txt","r+");
    if(fp==NULL){
        printf("open error...\n");
        exit(0);
    }
    while(2==fscanf(fp,"(%d,%d) ",&m,&n))
    {
        for(int i=0;i<v;i++){
            if(Graph[i].date==m){
                n=SearchVnode(n,Graph);
                if(n!=-1)
                    Add(n,Graph[i].firstarc);
            }
        }
    }
    fclose(fp);
}

int SearchVnode(int n,Vnode *Graph)
{
    for(int i=0;i<v;i++)
    {
        if(Graph[i].date==n)
            return(i);
    }
    printf("Not Found!\n");
    return(-1);
}

void Add(int n,ArcNode *string)
{
    ArcNode *p,*s;
    s=string;
    if(!IsEmpty(string))
    {
        p=(ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex=n;//下标
        p->nextarc=s;
        string=p;
    }
    else{
        s = (ArcNode *)malloc(sizeof(ArcNode));
        s>adjvex=n;
        s->nextarc=NULL;
    }
}

int IsEmpty(ArcNode *string)
{
    if(string==NULL)
        return(1);
    return(0);
}

void Change1(Vnode *Graph,Matrix MAP)
{
    int i=0;
    ArcNode *p;
    for(;i<v;i++)
    {//点集合
        MAP.vex[i]=Graph[i].date;
    }
    for(;i<v;i++){
            p=Graph[i].firstarc;
            while(!IsEmpty(p))
                {
                    for(int j=0;j<v;j++){
                        if(j=p->adjvex)
                        {
                            MAP.adjmatrix[i][j]=1;
                            break;
                        }
                    }
                    p=p->nextarc;
                }
        }
}

/*
void Change2(Vnode *Graph,Matrix MAP)
{
    int i=0;
    for(;i<v;i++){
        Graph[i].date=MAP.vex[i];
        for(int j=0;j<v;j++){
            if(MAP.adjmatrix[i][j]==1){
                Add(j,Graph[i].firstarc);
            }
        }
    }
}

*/
void InitSave(int *A)
{
    A =(int *)malloc(v*sizeof(int));
}

void DFSGTravers(Vnode *Graph,int *DFSGcount)
{
    //递归深度优先邻接表
    int *visited;
    int count=0;
    FILE *fp;
    visited = (int *)malloc(v*sizeof(int));
    fp=fopen("DFS_Graph.txt","w+");
    if(fp==NULL)
    {
        printf("open error...\n");
        exit(0);
    }
    for(int i=0;i<v;i++)
        visited[i]=0;
    for(int i=0;i<v;i++)
    {
        if(visited[i]==0)
            DFSG(Graph,i,visited,fp,DFScount,count);
    }
    free(visited);
    fclose(fp);
}

void DFSG(Vnode *Graph,int root,int *visited,FILE *fp,int *DFSGcount,int count)
{
    ArcNode *p;

    visited[root]=1;
    DFSGcount[root]=count;
    count++;
    fprintf(fp,"%d",Graph[root].date);
    for(p=Graph[root].firstarc;p!=NULL;p=p->nextarc)
    {
        if(visited[p->adjvex]==0) DFSG(Graph,p->adjvex,visited,fp,DFSGcount,count);
    }
}

void NDFSG(Vnode *Graph,int *NDFSGv,int *NDFSGcount)
{
    STACK *S;//建立一个辅助栈
	int i,count=0;//节点的标号
	int *visited;
	ArcNode *p;
    visited = (int *)malloc(v*sizeof(int));
    S=(STACK *)malloc(sizeof(STACK));
    S->next=NULL;
	for (i = 0; i < v; i++) {
		visited[i] = 0;
	}
	i = 0;

	visited[i] = 1;
	NDFSGv[count]=Graph[i].date;
	NDFSGcount[i]=count;
	count++;

	for (p = Graph[i].firstarc;p!=NULL;p=p->nextarc)
		Push(p->adjvex, S);//将根节点的所有邻接点压栈
	while (!IsEmpty_s(S))
	{
		i = Top(S);
		if (visited[i] == 0) {
			NDFSGv[count]=Graph[i].date;
            NDFSGcount[i]=count;
            count++;
			visited[i] = 1;
			Pop(S);
			for (p = Graph[i].firstarc;p!=NULL;p=p->nextarc)
				Push(p->adjvex, S);//将该节点的所有邻接点压栈
		}
		if(visited[i]==1)
			Pop(S);

	}
}
void Push(int x,STACK *S)
{
    STACK *p,*q;
    p=S;
    q=(STACK *)malloc(sizeof(STACK));
    if(p->next==NULL)
    {
        p->next = q;
        q->node = x;
        q->next=NULL;
    }
    else{
     q->next = p->next;
     q->node = x;
     p->next=q;
    }
}

void Pop(STACK *S)
{
    STACK *p,*q;
    p=S;
    if(p->next==NULL)
    {
        printf("stack is empty\n");
        return NULL;
    }
    else{
       q = p->next;
       p->next = q->next;
       free(q);

    }
}

int IsEmpty_s(STACK *S)
{
    if(S->next==NULL) return(1);
    return(0);
}

int Top(STACK *S)
{
    if(IsEmpty_s(S))
    {
        printf("stack is empty\n");
        exit(0);
    }
    return(S->next->node);

}

void DFSMTravers(Matrix MAP,int *DFSMcount)
{
    int *visited;
    int count=0;
    FILE *fp;
    visited = (int *)malloc(v*sizeof(int));
    fp=fopen("DFS_MAP.txt","w+");
    if(fp==NULL)
    {
        printf("open error...\n");
        exit(0);
    }
    for(int i=0;i<v;i++)
        visited[i]=0;
    for(int i=0;i<v;i++)
    {
        if(visited[i]==0)
            DFSM(MAP,i,visited,fp,DFSMcount,count);
    }
    free(visited);
    fclose(fp);
}

void DFSM(Matrix MAP,int root,int *visited,FILE *fp,int *DFSMcount,int count)
{
    visited[root]=1;
    DFSMcount[root]=count;
    count++;
    fprintf(fp,"%d",MAP.vex[root]);
    for(int i=0;i<v;i++)
    {
        if(visited[i]==0 && MAP.adjmatrix[root][i]==1) DFSM(MAP,j,visited,fp,DFSMcount,count);
    }
}
void NDFSM(Matrix MAP,int *NDFSMv,int *NDFSMcount)
{
    STACK *S;//建立一个队列，因为用
	int w,i,count=0;//节点的标号
	int *visited;
	ArcNode *p;
    visited = (int *)malloc(v*sizeof(int));
    S=(STACK *)malloc(sizeof(STACK));
    S->next=NULL;
	for (i = 0; i < v; i++) {
		visited[i] = 0;
	}
	i = 0;

	visited[i] = 1;
	NDFSMv[count]=MAP.vex[i];
	NDFSMcount[i]=count;
	count++;

	for (w=v-1;w>=0;w--)
    {
        if(MAP.adjmatrix[i][w]==1)
        Push(w, S);//将根节点的所有邻接点压栈,因为栈是先进后出，所以倒着压栈，
    }

	while (!IsEmpty_s(S))
	{
		i = Top(S);
		if (visited[i] == 0) {
			NDFSMv[count]=MAP.vex[i];
            NDFSMcount[i]=count;
            count++;
			visited[i] = 1;
			Pop(S);
			for (w=v-1;w>=0;w--)
            {
                if(MAP.adjmatrix[i][w]==1)
                Push(w, S);//将该节点的所有邻接点压栈
            }

		}
		if(visited[i]==1)
			Pop(S);

	}
}

void BFSG(Vnode *Graph,int *BFSGv,int *BFSGcount)
{
    STRING Q;//队列
	int *visited;
	int i=0,count=0,w;
	ArcNode *p;
	visited = (int *)malloc(v*sizeof(int));
	for(;i<v;i++)
    {
        visited[i]=0;
    }
    InitQueue(Q);
    for(i=0;i<v;i++)
    {
        if(!visited[i])
        {
            BFSGv[count]=Graph[i].date;
            BFSGcount[i]=count;
            count++;
            visited[i]=1;
            EnQuene(i,Q);
            while(!QueueEmpty(Q))
            {
                w=DeQueue(Q);
                for(p=Graph[i].firstarc;p!=NULL;p=p->nextarc)
                {
                    if(!visited[p->adjvex])
                    {
                        visited[p->adjvex]=1;
                        BFSGv[count]=Graph[p->adjvex].date;
                        BFSGcount[p->adjvex]=count;
                        count++;
                        EnQuene(p->adjvex,Q);
                    }
                }

            }
        }
    }
}



void InitQueue(STRING Q)
{
    Q.front=MAX;
    Q.last=MAX-1;
}

int QueueEmpty(STRING Q)
{
    if(Q.front=Q.last+1) return(1)
    return(0);
}

void EnQueue(STRING Q,int x)
{
    if(Q.front==0)
    {
        printf("FULL\n");
        exit(0);
    }
    Q.front--;
    Q.node[Q.front]=x;
}

int DeQueue(STRING Q)
{
    int w;
    if(QueueEmpty(Q))
    {
        printf("empty\n");
        exit(0);
    }
    w=Q.node[Q.last];
    Q.last--;
    return(w);
}
void BFSM(Matrix MAP,int *BFSMv,int *BFSMcount)
{
	STRING Q;//队列
	int *visited;
	int i=0,count=0,w,j;
	visited = (int *)malloc(v*sizeof(int));
	for(;i<v;i++)
    {
        visited[i]=0;
    }
    InitQueue(Q);
    for(i=0;i<v;i++)
    {
        if(!visited[i])
        {
            BFSMv[count]=MAP.vex[i];
            BFSMcount[i]=count;
            count++;
            visited[i]=1;
            EnQuene(i,Q);
            while(!QueueEmpty(Q))
            {
                w=DeQueue(Q);
                for(j=0;j<v;j++)
                {
                    if(!visited[j] && MAP.adjmatrix[w][j]==1)
                    {
                        visited[j]=1;
                        BFSGv[count]=MAP.vex[j];
                        BFSGcount[j]=count;
                        count++;
                        EnQuene(j,Q);
                    }
                }

            }
        }
    }
}


