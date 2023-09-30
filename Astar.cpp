#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

const int INF = 1e9; // Infinity value for initialization

int graph[100][100];
int num_vertices, num_edges, start, end_node;

struct Node {
    int vertex;
    int cost;
    bool operator>(const Node& other) const {
        // Define the priority queue ordering
        return cost > other.cost;
    }
};

int AStar(int start, int end_node) {
    vector<int> distance(num_vertices + 1, INF); // Initialize distances with infinity
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    distance[start] = 0; // Distance from start to start is 0
    pq.push({start, 0});

    while (!pq.empty()) {
        int u = pq.top().vertex;
        int cost = pq.top().cost;
        pq.pop();

        if (u == end_node) {
            return distance[end_node];
        }

        for (int v = 1; v <= num_vertices; v++) {
            if (graph[u][v] > 0) {
                int new_cost = distance[u] + graph[u][v];

                if (new_cost < distance[v]) {
                    distance[v] = new_cost;
                    pq.push({v, new_cost});
                }
            }
        }
    }

    return -1; // If no path is found
}

int main() {
    cout << "Enter number of vertices: ";
    cin >> num_vertices;
    cout << "Enter number of edges: ";
    cin >> num_edges;
    cout << "Enter source vertex: ";
    cin >> start;
    cout << "Enter destination vertex: ";
    cin >> end_node;

    for (int i = 0; i <= num_vertices; i++) {
        for (int j = 0; j <= num_vertices; j++) {
            graph[i][j] = 0;
        }
    }

    cout << "Enter edges of the graph and their weights (e.g., node1 node2 weight):" << endl;
    for (int k = 0; k < num_edges; k++) {
        int node1, node2, weight;
        cin >> node1 >> node2 >> weight;
        graph[node1][node2] = weight;
    }

    int shortest_distance = AStar(start, end_node);
    if (shortest_distance == -1) {
        cout << "No path found from node " << start << " to node " << end_node << endl;
    } else {
        cout << "Shortest distance from node " << start << " to node " << end_node << " is: " << shortest_distance << endl;
    }

    return 0;
}
