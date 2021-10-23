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

//****************Dynamic ArrayList class based************************
class ArrayList
{
    int * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new int[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item )
            return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length )
        return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE )
        return ; //nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length)
        return NULL_VALUE ;
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)
        return true;
    else
        return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list)
        delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  * adjList ;
    int *color;
    int *distance;
    int *parent;
    int time;
    int *startTime;
    int *endTime;
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
    void bfs(int source); //will run bfs in the graph
    void dfs(int source);
    void dfsVisit(int i); //will run dfs in the graph
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    directed = dir ;
    color=0;
    distance=0;
    parent=0;
    startTime=0;
    endTime=0; //set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0)
        delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    if(!directed)
        adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return;
    this->nEdges--;
    if(this->isEdge(u,v))
    {
        adjList[u].removeItem(v);
        if(!directed)
            adjList[v].removeItem(u);
    }
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;
    if(adjList[u].searchItem(v)!=NULL_VALUE)
    {
        //cout << "Edge exists" << endl;
        return true;
    }
    else
    {
        //cout << "Edge does not exist" << endl;
        return false;
    }
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    int x;
    if(directed==false)
    {
        x=adjList[u].getLength();

    }
    else
    {
        int od=adjList[u].getLength();
        int id=0;
        for(int i=0; i<nVertices; i++)
        {
            if(adjList[i].searchItem(u)!=NULL_VALUE)
                id++;
        }

        x=id+od;
    }

    return x;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(directed==false)
    {
        int x=adjList[u].getLength(), y=adjList[v].getLength();
        int *arr1=new int[x];
        int *arr2=new int[y];
        for(int i=0; i<x; i++)
        {
            arr1[i]=adjList[u].getItem(i);
        }

        for(int i=0; i<y; i++)
        {
            arr2[i]=adjList[v].getItem(i);
        }

        for(int i=0; i<x; i++)
        {
            for(int j=0; j<y; j++)
            {
                if(arr1[i]==arr2[j])
                    return true;
            }
        }

        return false;
    }
    else
    {
        for(int i=0 ; i <nVertices; i++)
        {
            if(adjList[u].searchItem(i)>=0 && adjList[v].searchItem(i)>=0)
                return true;
            else if(adjList[u].searchItem(i)>=0 && adjList[i].searchItem(v)>=0)
                return true;
            else if(adjList[i].searchItem(u)>=0 && adjList[v].searchItem(i)>=0)
                return true;
            else if(adjList[i].searchItem(u)>=0 && adjList[i].searchItem(v)>=0)
                return true;
        }
    }

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
        for(int i=0; i<adjList[u].getLength(); i++)
        {
            v=adjList[u].getItem(i);
            if(color[v]==WHITE)
            {
                color[v]=GREY;
                distance[v]=distance[u]+1;
                parent[v]=u;
                q.enqueue(v);
            }
        }
        color[u]=BLACK;
    }
}



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
    for(int i=0; i<adjList[u].getLength(); i++)
    {
        int v = adjList[u].getItem(i);
        if(color[v] == WHITE)
        {
            parent[v] = u;
            dfsVisit(v);
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
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    if(adjList!=0)
        delete[] adjList ;
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
    adjList = 0;
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
                cout << "They have common Adjacent vertices" << endl;
            else
                cout << "Do not have common Adjacent vertices" << endl;
        }
        else if(ch==6)
        {
            int u,v;
            cin >> u >> v;
            int x=g.getDist(u,v);
            if(x==INFINITY)
                cout << "They are not connected" << endl;
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
