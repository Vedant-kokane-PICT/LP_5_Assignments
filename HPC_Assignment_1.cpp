// Vedant Kokane
// 41429

#include <queue>
#include <iostream>
#include <omp.h>
#include <stack>

using namespace std;


class Graph{
    int vertices;
    vector<vector<int>> adjList;
public:
    Graph(int v){
        vertices = v;
        adjList.resize(vertices);
    }
    
    void addEdge(int u,int v){
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    
    
    void printGraph()
    {
        for (int i = 0; i < vertices; i++)
        {
            cout << i << " -> ";
            for (int j = 0; j < adjList[i].size(); j++)
            {
                cout << adjList[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    
    void BFS(int startNode){
        queue<int> q1;
        q1.push(startNode);
        vector<bool> vis(vertices);
        
        vis[startNode] = 1;
        
        while(!q1.empty()){
            int node;
            #pragma omp parallel shared(q1, vis)
            {
                #pragma omp single
                {
                    node = q1.front();
                    q1.pop();
                    cout<<"Thread - "<<omp_get_thread_num()<<", visited node "<<node<<endl;
                }
                
                #pragma omp for
                for(auto x:adjList[node]){
                    if(!vis[x]){
                        #pragma omp critical
                        {
                            q1.push(x);
                            vis[x] = 1;
                        }
                    }
                }
            }
        }
    }
    
    
    void DFS(int startNode){
        vector<bool> vis(vertices);
        DFSHelper(startNode,vis);
    }
    
    void DFSHelper(int node,vector<bool> &vis){
        
        #pragma omp critical
        {
            vis[node] = 1;
            cout<<"Thread - "<<omp_get_thread_num()<<", visited node "<<node<<endl;
        }
        #pragma omp for
        for(auto x:adjList[node]){
            if(!vis[x]){
                DFSHelper(x,vis);   
            }
        }
        
    }
};



int main(){
    Graph g(8);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 4);
    g.addEdge(1, 5);
    g.addEdge(2, 6);
    g.addEdge(2, 7);
    
    // g.BFS(0);
    g.DFS(0);
    return 0;
}
