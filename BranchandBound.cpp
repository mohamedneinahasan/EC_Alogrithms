#include<iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = 1e9;

int graph[100][100];
int visited[100];
int num_vertices, num_edges, start, end_node;

struct Node {
    int current_node;
    int cost;
    vector<int> path;
};

bool operator<(const Node& a, const Node& b) {
    return a.cost > b.cost;
}

vector<int> BranchAndBound(int start, int& best_path_cost) {
    priority_queue<Node> pq;
    vector<int> best_path;
    int best_cost = INF;

    pq.push({start, 0, {start}});
    
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int current_node = current.current_node;
        int current_cost = current.cost;
        vector<int> current_path = current.path;

        if (current_node == end_node && current_cost < best_cost) {
            best_cost = current_cost;
            best_path = current_path;
            best_path_cost = best_cost;
        }

        for (int k = 1; k <= num_vertices; k++) {
            if (graph[current_node][k] > 0 && !visited[k]) {
                visited[k] = 1;
                vector<int> new_path = current_path;
                new_path.push_back(k);
                int new_cost = current_cost + graph[current_node][k];

                if (new_cost < best_cost) {
                    pq.push({k, new_cost, new_path});
                }
            }
        }
    }
    
    return best_path;
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

    int best_path_cost = 0;
    vector<int> best_path = BranchAndBound(start, best_path_cost);

    if (!best_path.empty()) {
        cout << "Branch and Bound Path: ";
        for (int node : best_path) {
            cout << node << " -> ";
        }
        cout << "End (Cost: " << best_path_cost << ")" << endl;
    } else {
        cout << "No path found from " << start << " to " << end_node << endl;
    }

    return 0;
}
