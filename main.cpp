#include "social_network.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>
using namespace std;

void loadGraphData(Graph& graph, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }
    int u, v, weight;
    while (file >> u >> v >> weight) {
        graph.addEdge(u, v, weight);
    }
}

void loadInfluenceData(Graph& graph, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }
    int node, score;
    while (file >> node >> score) {
        graph.addInfluenceScore(node, score);
    }
}

void loadUserLabels(Graph& graph, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }
    
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int node;
        string firstName, lastName;
        
        if (iss >> node >> firstName >> lastName) {
            graph.addUserLabel(node, firstName + " " + lastName);
        }
    }
}

template<typename Container>
void printPath(const Graph& graph, const Container& path, int distance) {
    cout << "Shortest Distance: " << distance << endl;
    cout << "Path: [\n";
    bool first = true;
    for (const auto& node : path) {
        if (!first) cout << " → ";
        cout << node << " (" << graph.getUserLabel(node) << ")";
        if (first) first = false;
    }
    cout << "\n]\n";
}

void printUserSequence(const Graph& graph, const list<int>& chain) {
    cout << "User Sequence: [\n";
    bool first = true;
    for (const auto& node : chain) {
        if (!first) cout << " → ";
        cout << node << " (" << graph.getUserLabel(node) << ")";
        if (first) first = false;
    }
    cout << "\n]\n";
}

int getValidInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number.\n";
    }
}

int main() {
    Graph graph;
    
    // Load data
    cout << "Loading graph data...\n";
    loadGraphData(graph, "data/social-network-proj-graph.txt");
    
    cout << "Loading influence data...\n";
    loadInfluenceData(graph, "data/social-network-proj-Influences.txt");
    
    cout << "Loading user labels...\n";
    loadUserLabels(graph, "data/social-network-proj-LABELS.txt");
    
    // Get user input
    int startNode = getValidInput("Enter Starting Node: ");
    cout << "Selected start node: " << graph.getUserLabel(startNode) << endl;
    
    int endNode = getValidInput("Enter Ending Node: ");
    cout << "Selected end node: " << graph.getUserLabel(endNode) << endl;
    
    cout << "\nPart 1: Graph-Based Shortest Path\n";
    cout << string(50, '=') << "\n";
    
    // Dijkstra's Algorithm
    cout << "\nDijkstra's Algorithm:\n";
    auto start = chrono::high_resolution_clock::now();
    auto [dijkstra_dist, dijkstra_path] = graph.dijkstra(startNode, endNode);
    auto end = chrono::high_resolution_clock::now();
    printPath(graph, dijkstra_path, dijkstra_dist);
    cout << "Time taken: " 
              << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
              << "ms\n";
    
    // A* Algorithm
    cout << "\nA* Algorithm:\n";
    start = chrono::high_resolution_clock::now();
    auto [astar_dist, astar_path] = graph.astar(startNode, endNode);
    end = chrono::high_resolution_clock::now();
    printPath(graph, astar_path, astar_dist);
    cout << "Time taken: " 
              << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
              << "ms\n";
    
    // Part 2: Longest Influence Chain
    cout << "\nPart 2: Dynamic Programming - Longest Chain of Influence\n";
    cout << string(50, '=') << "\n";
    start = chrono::high_resolution_clock::now();
    auto [chain_length, chain] = graph.longestInfluenceChain();
    end = chrono::high_resolution_clock::now();
    
    cout << "Longest Chain Length: " << chain_length << endl;
    printUserSequence(graph, chain);
    cout << "Time taken: " 
              << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
              << "ms\n";
    
    return 0;
} 