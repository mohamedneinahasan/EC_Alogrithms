#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;

const int MAX_VERTICES = 100;
int graph[MAX_VERTICES][MAX_VERTICES];
bool visited[MAX_VERTICES];
int num_vertices, num_edges, start, end_node;

struct Node {
    int vertex;
    int cost;
    int lowerBound;

    bool operator<(const Node& other) const {
        return lowerBound > other.lowerBound;
    }
};

int calculateHeuristicCost(int node) {
    // Replace this with your heuristic calculation for the given node
    // For simplicity, we assume heuristic cost is zero in this example
    return 0;
}

int calculateLowerBound(const vector<int>& path) {
    int lowerBound = 0;
    int lastNode = start;

    for (int node : path) {
        lowerBound += graph[lastNode][node];
        lowerBound += calculateHeuristicCost(node);
        lastNode = node;
    }

    return lowerBound;
}

void BranchAndBoundHeuristics(int start) {
    priority_queue<Node> pq;
    vector<int> initial_path = { start };
    int bestCost = numeric_limits<int>::max();
    vector<int> bestPath;

    visited[start] = true;
    Node initialNode = { start, 0, calculateLowerBound(initial_path) };
    pq.push(initialNode);

    while (!pq.empty()) {
        Node currentNode = pq.top();
        pq.pop();
        int currentVertex = currentNode.vertex;
        int currentCost = currentNode.cost;

        if (currentVertex == end_node) {
            if (currentCost < bestCost) {
                bestCost = currentCost;
                bestPath = initial_path;
            }
        }

        for (int neighbor = 1; neighbor <= num_vertices; ++neighbor) {
            if (graph[currentVertex][neighbor] > 0 && !visited[neighbor]) {
                visited[neighbor] = true;
                vector<int> newPath = initial_path;
                newPath.push_back(neighbor);
                int newPathCost = currentCost + graph[currentVertex][neighbor];
                int newPathLowerBound = calculateLowerBound(newPath);

                if (newPathLowerBound < bestCost) {
                    Node newNode = { neighbor, newPathCost, newPathLowerBound };
                    pq.push(newNode);
                }

                visited[neighbor] = false;
            }
        }
    }

    if (bestPath.empty()) {
        cout << "No path found from " << start << " to " << end_node << endl;
    } else {
        cout << "Best Path: ";
        for (int node : bestPath) {
            cout << node << " -> ";
        }
        cout << "Cost: " << bestCost << endl;
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

    BranchAndBoundHeuristics(start);

    return 0;
}
