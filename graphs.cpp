#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <iterator>

using namespace std;

class edge {
    public:
    int src, des;
    edge(int a, int b) {
        src = a;
        des = b;
    }
};

void levelOrder(vector<vector<edge> > &graph) { // Time Complexity- O(V+E)

    cout<<"BFS- ";
    vector<bool> vis(graph.size(), false); 
    queue<int> g;
    g.push(graph[0][0].src);

    while(!g.empty()) {
        int curr = g.front(); g.pop();

        if (vis[curr] == false) {
            vis[curr] = true;
            cout<<curr<<" ";
            
            for(int i = 0; i<graph[curr].size(); i++) {
                g.push(graph[curr][i].des);
            }
        }
    }
    cout<<endl;

    return;
}

void dfs(vector<vector<edge> > &graph, int curr, vector<bool> &vis) { // O(V+E)
    
    cout<<curr<<" ";
    vis[curr] = true;

    for(int i = 0; i<graph[curr].size(); i++) {
        if (vis[graph[curr][i].des] == false) {
            dfs(graph, graph[curr][i].des, vis);
        }
    }
    
    return;
}

void allPaths(vector<vector<edge> > &graph, vector<bool> &vis2, int curr, int tar, string p) { // O(V^V)
    if (curr == tar) {
        p += to_string(curr);
        cout<<p<<endl;
        return;
    }

    for(int i = 0; i<graph[curr].size(); i++) {
        if (vis2[curr] == false) {
            vis2[curr] = true; // so that the same node is not repeated in a single path
            allPaths(graph, vis2, graph[curr][i].des, tar, p + to_string(curr));
            vis2[curr] = false; // so that diff paths can contain the same node any number of times
        }
    }
    return;
}

bool isCycleUndirected(vector<vector<edge> > &graph, vector<bool> &vis, int curr, int par) { // O(E+V)
    vis[curr] = true;
    
    for(int i = 0; i<graph[curr].size(); i++) {
        if (vis[graph[curr][i].des] == true && graph[curr][i].des != par) {
            return true;
        } else if (!vis[graph[curr][i].des]) {
            if (isCycleUndirected(graph, vis, graph[curr][i].des, curr)) {
                return true; 
            }
        }
    }
    return false;
}

int main() {
    
    int v; cin>>v;
    int edges; cin>>edges;
    vector<vector<edge> > graph(v);
    // eg graph-        
                    //   1 -- 3
                    //  /     | \
                    // 0      |  5 -- 6
                    //  \     | /
                    //   2 -- 4

    int src, des;

//creating the graph using Adjancy List Method
    for(int i = 0; i<edges; i++) {
        cin>>src>>des;
        edge e1(src, des);
        edge e2(des, src);

        graph[src].push_back(e1);
        graph[des].push_back(e2);
    }

// Level Order traversal BFS

    levelOrder(graph);
    // If the graph is diconnected- make the visited array in the main function and call the levelOrder function 
    // for every node for which visited is false.

// DFS
    cout<<"DFS- ";
    vector<bool> vis(v);
    dfs(graph, graph[0][0].src, vis);
    cout<<endl;
    // If the graph is diconnected- make the visited array in the main function and call the dfs function 
    // for every node for which visited is false.

// All paths from a Source to a Target
    cout<<endl;
    vector<bool> vis2(v);
    int s, tar;
    cin>>s>>tar;
    string path = "";
    allPaths(graph, vis2, s, tar, path);

// Cycle Detection in Undirected graph using DFS approach
    cout<<endl;
    vector<bool> vis3(v);
    if (isCycleUndirected(graph, vis3, graph[0][0].src, -1)) {
        cout<<"YES"<<endl;
    } else {
        cout<<"NO"<<endl;
    }

    return 0;
}