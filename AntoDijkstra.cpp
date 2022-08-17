#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <climits>
//AntoDijkstra
#define INF INT_MAX
#define WEIGHT 25
using namespace std;

struct Edge
{
    int to;
    int weight;
    int weight2 = {}; //dinamically added weight
    Edge() {}
    Edge(int to, int weight) : to(to), weight(weight) {}
    void read() {
        cin >> to >> weight;
    }
};
struct QueueVertex
{
    int number;
    int dist;
    QueueVertex(int number, int dist) : number(number), dist(dist) {}
};
bool operator<(const QueueVertex& v1, const QueueVertex& v2) {
    return v1.dist > v2.dist;
}
class Graph
{
    vector<vector<Edge>> link;
public:
    Graph(int vertex_count) :
        link(vertex_count) {}
    void add_edge_u(int from, int to, int weight) { //unoriented
        link[from].push_back(Edge(to, weight));
        link[to].push_back(Edge(from, weight));
    }
    void add_edge_o(int from, int to, int weight) { //oriented
        link[from].push_back(Edge(to, weight));
    }
    int vertex_count() const {
        return link.size();
    }
    void turn(int weight = 1) {
        for (auto i = 0; i < link.size(); i++)
            for (auto j = 0; j < link[i].size();j++) {
                link[i][j].weight2 -= weight*((link[i][j].weight2-weight)>0);
            }
    }
    int dijkstra(int start, int finish) {
        vector <int> dist;
        vector<int> parent = {};
        dist.resize(vertex_count(), INF);
        dist[start] = 0;
        parent.resize(vertex_count(), -1);
        priority_queue <QueueVertex> q;
        q.push(QueueVertex(start, 0));
        while (!q.empty()) {
            int current = q.top().number;
            int current_dist = q.top().dist;
            q.pop();
            if (current_dist > dist[current]) {
                continue;
            }
            for (auto edge : link[current]) {
                if (dist[current] + (edge.weight+edge.weight2) < dist[edge.to]) {
                    dist[edge.to] = dist[current] + (edge.weight+edge.weight2);
                    parent[edge.to] = current;
                    q.push(QueueVertex(edge.to,dist[edge.to]));
                }
            }
        }
        path(parent, start, finish);
        inc_wpath(parent, start, finish);
        return dist[finish];
    }
    void path(vector<int> parent, int start, int finish) {
        deque<int> path;
        while (finish != -1) {
            path.push_front(finish);
            finish = (finish == start) ? -1 : parent[finish];
        }
        cout << "path" << endl;
        for (int node : path) cout << (node) << ' ';
        cout << endl;
    }
    void inc_wpath(vector<int> parent, int start, int finish) {
        deque<int> path;
        while (finish != -1) {
            path.push_front(finish);
            finish = (finish == start) ? -1 : parent[finish];
        }
        for (auto i = 0; i < link.size(); i++) {
            for (auto j = 0; j < link[i].size(); j++) {
                for (auto k = 0; k < path.size()-1; k++) {
                    if (path[k + 1] == link[i][j].to && i == path[k]) {
                        link[i][j].weight2 += WEIGHT;
                    }
                }
            }
        }
    }
    void show_graph() {
        for (auto i=0;i<link.size();i++)
            for (auto j : link[i]) {
                cout << i << ' ' << j.to << ' ' << j.weight+j.weight2 << endl;
            }
        cout << endl;
    }
};


int main()
{
    /*int n = 4, m = 4, start = 2, finish = 1;
    Graph gr(n);
    gr.add_edge_o(0, 1, 1);
    gr.add_edge_o(1, 2, 2);
    gr.add_edge_o(2, 3, 5);
    gr.add_edge_o(3, 0, 4);
    
    /*int n, m; //number of nodes, number of edges
    cin >> n >> m;
    int start, finish;
    cin >> start >> finish;
    start--; finish--;
    Graph gr(n);
    /*for (auto i = 0; i < m; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        from--; to--;
        gr.add_edge_o(from, to, weight);
    }*/
    Graph gr(7);
    int start = 0, finish = 6;
    gr.add_edge_o(0, 1, 1);
    gr.add_edge_o(0, 2, 3);
    gr.add_edge_o(2, 4, 2);
    gr.add_edge_o(2, 5, 4);
    gr.add_edge_o(1, 3, 7);
    gr.add_edge_o(3, 6, 10);
    gr.add_edge_o(4, 6, 1);
    gr.add_edge_o(5, 0, 6);
    gr.add_edge_o(6, 5, 3);
    //gr.inc_all_weights();
    gr.show_graph();
    int dist = gr.dijkstra(start,finish);
    cout << dist << endl;
    gr.show_graph();
    gr.turn(20);
    gr.show_graph();
    dist = gr.dijkstra(0, 5);
    cout << dist << endl;
    gr.show_graph();
    return 0;
}