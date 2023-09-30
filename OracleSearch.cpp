#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int graph[100][100];
int visited[100];
int num_vertices, num_edges, start, end_node;

void OracleSearch(int start) {
    queue<vector<int>> paths;
    vector<int> initial_path = {start};
    vector<vector<int>> all_paths;

    paths.push(initial_path);

    while (!paths.empty()) {
        vector<int> current_path = paths.front();
        paths.pop();

        int current_node = current_path.back();

        if (current_node == end_node) {
            all_paths.push_back(current_path);
            continue;
        }

        visited[current_node] = true;

        for (int k = 1; k <= num_vertices; k++) {
            if (graph[current_node][k] > 0 && !visited[k]) {
                vector<int> new_path = current_path;
                new_path.push_back(k);
                paths.push(new_path);
            }
        }
    }

    if (all_paths.empty()) {
        cout << "No path found from node " << start << " to node " << end_node << endl;
    } else {
        cout << "Oracle Search Path from node " << start << " to node " << end_node << ":" << endl;
        for (const vector<int>& path : all_paths) {
            for (size_t i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i < path.size() - 1) {
                    cout << " -> ";
                }
            }
            cout << endl;
        }
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

    OracleSearch(start);

    return 0;
}
