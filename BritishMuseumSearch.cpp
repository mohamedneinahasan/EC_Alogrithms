#include<iostream>
#include <list>
#include <queue>
using namespace std;

int graph[100][100];
int visited[100];
int num_vertices, num_edges, start, end_node;

void BritishMuseumSearch(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = 1;

    cout << "British Museum Search Path: ";
    while (!q.empty()) {
        int current_node = q.front();
        q.pop();
        cout << current_node << " -> ";

        if (current_node == end_node) {
            cout << "Reached the destination node " << end_node << endl;
            return;
        }

        for (int k = 1; k <= num_vertices; k++) {
            if (graph[current_node][k] > 0 && !visited[k]) {
                q.push(k);
                visited[k] = 1;
            }
        }
    }
    cout << "End (Destination node not reached)" << endl;
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

    BritishMuseumSearch(start);

    return 0;
}
