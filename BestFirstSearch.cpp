#include<iostream>
#include<stdlib.h>
#include <list>
#include <map>
#include<vector>
#include <algorithm>
#include <stack>
#include<queue>
using namespace std;

int graph[100][100];
list <int> path={}, final_path={}, best_path={};
int cost=0, len, num_vertices, num_edges, node1, node2, start, end_node;
int visited[100], graph_cost;

// Define your heuristic function here
int calculateHeuristic(int current_node, int destination_node) {
    // Replace this with your actual heuristic calculation
    return abs(current_node - destination_node); // Example heuristic
}

void BestFirstSearch(int start, int end_node) {
    priority_queue<pair<int, int>> pq; // Priority queue based on heuristic value
    vector<int> current_path;
    vector<vector<int>> all_paths;
    int current_cost = 0;

    pq.push({calculateHeuristic(start, end_node), start});

    while (!pq.empty()) {
        int current_node = pq.top().second;
        pq.pop();

        current_path.push_back(current_node);

        if (current_node == end_node) {
            all_paths.push_back(current_path);
            break;
        }

        bool has_unvisited_neighbors = false;

        for (int k = 1; k <= num_vertices; k++) {
            if (graph[current_node][k] > 0) {
                int heuristic = calculateHeuristic(k, end_node);
                pq.push({heuristic, k});
                has_unvisited_neighbors = true;
            }
        }

        if (!has_unvisited_neighbors) {
            if (!current_path.empty()) {
                current_path.pop_back();
            }
        }
    }

    int cost = 0;
    if (all_paths.empty()) {
        cout << "No Path"; // No path found
    } else {
        cout << "Order of nodes visited:\n";
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

    cout << "Enter edges of a graph and cost (Eg: node1 node2 cost): ";
    for (int k = 0; k < num_edges; k++) {
        cin >> node1 >> node2 >> len;
        graph[node1][node2] = len;
    }

    BestFirstSearch(start, end_node);

    return 0;
}
