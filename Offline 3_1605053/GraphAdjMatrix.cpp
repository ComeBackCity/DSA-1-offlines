#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>

using namespace std;

#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0)
        return true ;
    else
        return false ;
}


int Queue::dequeue()
{
    if(length == 0)
        return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data)
        delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** matrix ;
    int *color;
    int *distance;
    int *parent;
    int time;
    int *startTime;
    int *endTime;
    //adjacency matrix to store the graph
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source);
    void dfs(int source);
    void dfsVisit(int i); //will run bfs in the graph
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    matrix = 0 ;
    directed = dir ;
    color=0;
    distance=0;
    parent=0;
    time=0;
    startTime=0;
    endTime=0; //set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;

    //allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return;
    matrix[u][v] = 1;
    if(!directed)
        matrix[v][u] = 1;

}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return;
    //write this function
    matrix[u][v] = 0;
    if(!directed)
        matrix[v][u] = 0;
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return false;
    if(matrix[u][v])
        return true;
    else
        return false;
}

int Graph::getDegree(int u)
{
    int x=0;
    if(directed==false)
    {
        for(int i=0; i<nVertices; i++)
        {
            if(matrix[u][i])
                x++;
        }
    }
    else
    {
        int od=0,id=0;
        for(int i=0; i<nVertices; i++)
        {
            if(matrix[u][i])
                od++;
        }
        for(int i=0; i<nVertices; i++)
        {
            if(matrix[i][u])
                id++;
        }
        x=id+od;
    }

    return x;
    //returns the degree of vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(directed==false)
    {
        for(int i=0 ; i <nVertices; i++)
        {
            if(matrix[u][i]==1 && matrix[v][i]==1)
                return true;
        }
    }
    else
    {
        for(int i=0 ; i <nVertices; i++)
        {
            if(matrix[u][i]==1 && matrix[v][i]==1)
                return true;
            else if(matrix[u][i]==1 && matrix[i][v]==1)
                return true;
            else if(matrix[i][u]==1 && matrix[v][i]==1)
                return true;
            else if(matrix[i][u]==1 && matrix[i][v]==1)
                return true;
        }

    }

    return false;//returns true if vertices u and v have common adjacent vertices

}



void Graph::bfs(int source)
{
    int u,v;//complete this function
    color= new int[nVertices];
    parent= new int[nVertices];
    distance= new int[nVertices];
    //initialize BFS variables
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        distance[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    distance[source] = 0 ;
    parent[source]=-1;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        u=q.dequeue();
        for(int i=0; i<nVertices; i++)
        {
            if(matrix[u][i]==1)
            {
                v=i;
                if(color[v]==WHITE)
                {
                    color[v]=GREY;
                    distance[v]=distance[u]+1;
                    parent[v]=u;
                    q.enqueue(v);
                }
            }
        }
        color[u]=BLACK;
    }
}

/*void Graph::dfs(int source)
{
    int u,v,time;
    color= new int[nVertices];
    parent= new int[nVertices];
    distance= new int[nVertices];
    startTime=new int[nVertices];
    endTime=new int[nVertices];

    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        distance[i] = INFINITY ;
    }

    time=0;
    for(int i=0; i<nVertices; i++)
    {
        int x=(i+source)%nVertices;
        if(color[x]==WHITE)
            dfsVisit(x);
    }

    //write this function


}

void Graph::dfsVisit(int i)
{
    time++;
    startTime[i]=time;
    color[i]=GREY;
    for(int k=0; k<nVertices; k++)
    {
        if(matrix[i][k]==1)
        {
            int v=k;
            if(color[v]==WHITE)
            {
                parent[v]=i;
                dfsVisit(v);
            }
            color[i]=BLACK;
            time++;
            endTime[i]==time;
        }
    }
}*/

void Graph::dfs(int source)
{
    //write this function
    color= new int[nVertices];
    parent= new int[nVertices];
    distance= new int[nVertices];
    startTime=new int[nVertices];
    endTime=new int[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE;
        parent[i] = -1;
        distance[i] = 0;
    }
    time = 0;
    for(int i=0; i<nVertices; i++)
    {
        int x=(i+source)%nVertices;
        if(color[x] == WHITE)
        {
            dfsVisit(x);
        }
    }
    cout << "End of DFS" << endl;
    for(int i=0; i<nVertices; i++)
    {
        cout << "Starting time of vertex " << i << " is " << startTime[i] << " and end time is " << endTime[i] << "." << endl;
    }
}

void Graph::dfsVisit(int u)
{
    time++;
    startTime[u] = time;
    color[u] = GREY;
    for(int i=0; i<nVertices; i++)
    {
        if(matrix[u][i]==1)
        {
            int v=i;
            if(color[v] == WHITE)
            {
                parent[v] = u;
                dfsVisit(v);
            }
        }
    }
    color[u] = BLACK;
    time++;
    endTime[u] = time;
}



int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return INFINITY;
    this->bfs(u);
    int x= distance[v];
    return x ;
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here



    for(int i=0; i<nVertices && matrix!=0; i++)
    {
        delete []matrix[i];
    }
    if(matrix!=0)
        delete[] matrix ;
    if(color!=0)
        delete[] color ;
    if(parent!=0)
        delete[] parent ;
    if(distance!=0)
        delete[] distance ;
    if(startTime!=0)
        delete[] startTime ;
    if(endTime!=0)
        delete[] endTime ;
    matrix = 0;
    color = 0;
    parent = 0;
    distance = 0;
    startTime = 0;
    endTime = 0;


}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    Graph g(false);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. \n");
        printf("2. Remove Edge. 3. IsEdge  4.Get Degree.\n");
        cout << "5. Has Common Adjacent Vertices " << endl;
        cout << "6. Shortest path from u to v " << endl;
        cout << "7. DFS demo 8. Print 9.Exit" << endl;

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u,v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u, v);
        }
        else if(ch==3)
        {
            int u,v;
            scanf("%d%d", &u, &v);
            if(g.isEdge(u,v))
                cout << "Edge exists" << endl;
            else
                cout << "Edge does not exist"  << endl;

        }
        else if(ch==4)
        {
            int u;
            cin >> u;
            cout << "The degree of vertex " << u << " is " << g.getDegree(u) << endl;
        }
        else if(ch==5)
        {
            int u,v;
            cin >> u >> v;
            if(g.hasCommonAdjacent(u,v))
                cout << "They have common Adjacent vertice(s)" << endl;
            else
                cout << "Do not have common Adjacent vertice(s)" << endl;
        }
        else if(ch==6)
        {
            int u,v;
            cin >> u >> v;
            int x=g.getDist(u,v);
            if(x==INFINITY)
                cout << "There is no direct path from vertex " << u << " to " << v << endl;
            else
                cout << "The shortest distance between vertex " << u << " and " << v << " is " << x << endl;

        }
        else if(ch==7)
        {
            int x;
            cin >> x;
            g.dfs(x);
        }
        else if(ch==8)
        {
            g.printGraph();
        }
        else if(ch==9)
        {
            break;
        }
    }

}
