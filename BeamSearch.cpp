#include<iostream>
#include<queue>
#include<list>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;

int graph[100][100];
int visited[100];
int num_vertices, num_edges, start, end_node, beam_width;

void BeamSearch(int start, int beam_width) {
    queue<vector<int>> paths;
    vector<int> initial_path = { start };
    vector<vector<int>> all_paths;

    paths.push(initial_path);

    while (!paths.empty()) {
        vector<int> current_path = paths.front();
        paths.pop();

        int current_node = current_path.back();

        visited[current_node] = 1;

        bool has_unvisited_neighbors = false;

        for (int k = 1; k <= num_vertices; k++) {
            if (graph[current_node][k] > 0 && !visited[k]) {
                vector<int> new_path = current_path;
                new_path.push_back(k);
                paths.push(new_path);
                has_unvisited_neighbors = true;
            }
        }

        if (!has_unvisited_neighbors) {
            all_paths.push_back(current_path);
        }
    }

    int pathcost = 0;
    cout << "Beam Search Paths Explored:" << endl;
    for (const vector<int>& path : all_paths) {
        pathcost = 0;
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " -> ";
            }
            if (i != 0) {
                pathcost += graph[path[i - 1]][path[i]];
            }
        }
        cout << "   Cost: " << pathcost;
        cout << endl;
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
    cout << "Enter beam width: ";
    cin >> beam_width;

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

    BeamSearch(start, beam_width);

    return 0;
}
