//
// Created by abirm on 11/6/2018.
//

#include <bits/stdc++.h>
#define  NULL_VALUE 99999

template <typename T> class Vector
{
    unsigned int _size;
    unsigned int _capacity;
    unsigned int Log;
    T* buffer;
public:
    Vector():_size(0),_capacity(0),Log(0) {}
    unsigned int size() const {
        return _size;
    }
    ~Vector() {
        //try{delete[] buffer;} catch (const std::exception& e) {cout<<e.what()<<endl;}
    }
    void reserve(unsigned int capacity) {
        T * newBuffer = (T*) malloc(capacity*8* sizeof(T));

        for (unsigned int i = 0; i < _size; i++)
            newBuffer[i] = buffer[i];

        _capacity = capacity;
        //try{delete[] buffer;} catch (const std::exception& e) {cout<<e.what()<<endl;}

        buffer = newBuffer;
    }
    void resize(unsigned int size) {
        Log = ceil(log((double) size) / log(2.0));
        reserve(1 << Log);
        _size = size;
    }
    T& operator[](unsigned int index) {
        return buffer[index];
    }
    void push_back(const T & v) {
        if (_size >= _capacity) {
            reserve(1 << Log);
            Log++;
        }
        buffer [_size++] = v;
    }
    Vector<T>& operator = (const Vector<T> & v) {
        //try{delete[] buffer;} catch (const std::exception& e) {cout<<e.what()<<endl;}
        _size = v._size;
        Log = v.Log;
        _capacity = v._capacity;
        buffer = (T*) calloc(_capacity, sizeof(T));
        for (unsigned int i = 0; i < _size; i++)
            buffer[i] = v.buffer[i];
        return *this;
    }

};
using namespace std;
class Edge
{
    unsigned int from,to;
    int cost;
public:
    Edge(unsigned int from, unsigned int to, int cost) : from(from), to(to), cost(cost) {}

    unsigned int getFrom() const {
        return from;
    }

    unsigned int getTo() const {
        return to;
    }

    int getCost() const {
        return cost;
    }

    bool operator<(const Edge &rhs) const {
        return cost < rhs.cost;
    }
};

class BellMan_Ford
{
    unsigned int nNodes;
    int source;
    Vector<int> distance;
    Vector<int>parent;
    Vector<Edge> *adList;
    bool negative_cycle;

public:

    explicit BellMan_Ford(unsigned int nodes):nNodes(nodes)
    {
        distance.resize(nodes);
        parent.resize(nodes);
        initializeAdList(nodes);
        source=-1;
        negative_cycle=false;
    }
    void initializeAdList(unsigned int nodes)
    {
        adList=new Vector<Edge>[nodes];
    }
    bool addEdge(unsigned int u, unsigned int v, int cost)
    {
        if(u>nNodes||v>nNodes)
            return false;
        //u--,v--;
        adList[u].push_back(Edge(u,v,cost));
        //adList[v].push_back(v,u,cost);
    }

    bool run(unsigned int source)
    {
        this->source=source;
        for (int j = 0; j <nNodes ; ++j) {
            distance[j]=NULL_VALUE;
            parent[j]=-1;
        }

        negative_cycle=false;
        distance[source]=0;
        for (int k = 0; k < nNodes; ++k)
        {
            int par=k;
            for (int i = 0; i < nNodes; ++i)
            {
                for (int j = 0; j < adList[i].size(); ++j) {
                    int v=adList[i][j].getTo();
                    if(distance[v]>distance[i]+adList[i][j].getCost())
                    {
                        distance[v] = distance[i] + adList[i][j].getCost();
                        parent[v]=i;
                        if(k+1==nNodes)
                            negative_cycle=true;
                    }
                }
            }
        }
        return negative_cycle;
    }

    bool print_distance()
    {
        if(negative_cycle)
        {
            cout << "The Graph has a negative cycle ."<<endl<<"So vertex distances reachable from negative cycle are not accurate" << endl;
        }

        for (int i = 0; i <nNodes ; ++i) {
            cout<<"distance of : "<<i<<" = "<<distance[i]<<endl;
        }
        cout<<endl;
        return !negative_cycle;
    }
    bool print_path( unsigned int u,unsigned int v)
    {
        if(u>nNodes||v>nNodes||distance[v]==INT_MAX||negative_cycle)
            return false;
        if(source!=u)
            run(u);
        int par=v;

        Vector<int> path;
        while (par>=0)
        {
            path.push_back(par);
            par=parent[par];
        }
        /*for (auto i=path.end();i!=path.begin();i--) {
            cout<<*i<<" -> ";
        }*/
        for (int i = (int)path.size()-1; i >=0; --i) {
            cout<<path[i]<<" -> ";
        }
        cout<<endl;
    }

};

int main()
{
    freopen("bellMan-ford-list-input.txt","r",stdin);
    unsigned int u,v,nodes,edges;
    int cost;
    cin>>nodes>>edges;
    BellMan_Ford bf(nodes);
    for (int i = 0; i < edges; ++i)
    {
        cin>>u>>v>>cost;
        bf.addEdge(u,v,cost);
    }

    if(bf.run(0))
        cout<<"Negative cycle Detected\n";
    bf.print_distance();
    for(unsigned int i=0;i<nodes;i++)
        bf.print_path(0,i);

    return 0;
}
