#include<iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int MAX_VERTICES = 100;

int graph[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];
int num_vertices, num_edges, start, end_node;

struct Node {
    int vertex;
    int g;  // Cost from start to current node
    int h;  // Heuristic estimate from current node to end
    int f;  // Total estimated cost (f = g + h)

    Node(int v, int g_val, int h_val) : vertex(v), g(g_val), h(h_val) {
        f = g + h;
    }

    bool operator<(const Node& other) const {
        return f > other.f;  // Priority queue uses the smallest f value
    }
};

int calculateHeuristicCost(int node) {
    // Implement your heuristic calculation here
    // For example, you can use the Euclidean distance between node and end_node
    return 0;  // Replace with your heuristic calculation
}

void AOStar(int start, int end_node) {
    priority_queue<Node> pq;
    vector<vector<int>> all_paths;
    vector<int> current_path;
    int best_cost = INT_MAX;

    pq.push(Node(start, 0, calculateHeuristicCost(start)));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int current_node = current.vertex;
        current_path.push_back(current_node);

        if (current_node == end_node) {
            all_paths.push_back(current_path);
            best_cost = current.g;
            continue;
        }

        if (current.g + current.h >= best_cost) {
            // Prune this branch if it can't lead to a better solution
            continue;
        }

        for (int k = 1; k <= num_vertices; k++) {
            if (graph[current_node][k] > 0 && !visited[k]) {
                int cost_to_neighbor = graph[current_node][k];
                int neighbor_g = current.g + cost_to_neighbor;
                int neighbor_h = calculateHeuristicCost(k);

                pq.push(Node(k, neighbor_g, neighbor_h));
            }
        }
    }

    int cost = 0;
    if (all_paths.empty()) {
        cout << "No Path";  // No path found
    } else {
        cout << "Order of nodes visited:" << endl;
        for (int i = 0; i < all_paths[0].size(); i++) {
            cout << all_paths[0][i] << ", ";
            if (i != 0) {
                for (int j = 0; j < i; j++) {
                    if (graph[all_paths[0][j]][all_paths[0][i]] > 0) {
                        cost += graph[all_paths[0][j]][all_paths[0][i]];
                        break;
                    }
                }
            }
        }

        cout << "\nCost of the Best Path: " << cost;
    }
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

    AOStar(start, end_node);

    return 0;
}
