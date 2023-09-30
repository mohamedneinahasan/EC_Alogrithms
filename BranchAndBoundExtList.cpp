#include<iostream>
#include<stack>
#include<list>
#include<vector>
#include<climits>
#include <queue>
using namespace std;

int graph[100][100];
int visited[100];
int num_vertices, num_edges, start, end_node;

struct Node {
    int vertex;
    int cost;
    vector<int> path;
};

bool operator<(const Node& a, const Node& b) {
    return a.cost > b.cost; // Min priority queue based on cost
}

void BranchAndBoundExtList(int start) {
    priority_queue<Node> pq;
    Node start_node;
    start_node.vertex = start;
    start_node.cost = 0;
    start_node.path.push_back(start);
    pq.push(start_node);

    while (!pq.empty()) {
        Node current_node = pq.top();
        pq.pop();

        int current_vertex = current_node.vertex;
        visited[current_vertex] = 1;

        if (current_vertex == end_node) {
            cout << "Branch and Bound with Extended List Path: ";
            for (int v : current_node.path) {
                cout << v << " -> ";
            }
            cout << "End (Destination node " << end_node << " reached)" << endl;
            return;
        }

        for (int k = 1; k <= num_vertices; k++) {
            if (graph[current_vertex][k] > 0 && !visited[k]) {
                Node new_node;
                new_node.vertex = k;
                new_node.cost = current_node.cost + graph[current_vertex][k];
                new_node.path = current_node.path;
                new_node.path.push_back(k);
                pq.push(new_node);
            }
        }
    }
    cout << "Branch and Bound with Extended List: No path to destination node " << end_node << endl;
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

    BranchAndBoundExtList(start);

    return 0;
}
