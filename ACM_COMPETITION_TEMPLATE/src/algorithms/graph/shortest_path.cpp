#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

const int INF = numeric_limits<int>::max();

class Graph {
public:
    Graph(int vertices);
    void addEdge(int u, int v, int weight);
    vector<int> dijkstra(int start);

private:
    int vertices;
    vector<vector<pair<int, int>>> adj; // adjacency list
};

Graph::Graph(int vertices) : vertices(vertices) {
    adj.resize(vertices);
}

void Graph::addEdge(int u, int v, int weight) {
    adj[u].emplace_back(v, weight);
    adj[v].emplace_back(u, weight); // For undirected graph
}

vector<int> Graph::dijkstra(int start) {
    vector<int> dist(vertices, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }

    return dist;
}

int main() {
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 4, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 0, 7);
    g.addEdge(4, 1, 3);
    g.addEdge(4, 2, 9);
    g.addEdge(4, 3, 2);

    vector<int> distances = g.dijkstra(0);

    for (int i = 0; i < distances.size(); ++i) {
        cout << "Distance from 0 to " << i << " is " << distances[i] << endl;
    }

    return 0;
}