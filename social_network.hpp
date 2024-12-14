#pragma once
#include <list>
#include <set>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

class Graph {
private:
    unordered_map<int, list<pair<int, int>>> adjacencyList; // Adjacency list to store graph edges and weights
    unordered_map<int, int> influenceScores; // Stores influence scores for each node
    unordered_map<int, int> nodeConnections; // Stores the number of connections for each node
    unordered_map<int, string> userLabels; // Maps node IDs to user labels

public:
    // Adds an edge between nodes u and v with a given weight
    void addEdge(int u, int v, int weight) {
        adjacencyList[u].push_back({v, weight});
        adjacencyList[v].push_back({u, weight});
        nodeConnections[u]++;
        nodeConnections[v]++;
    }

    // Sets the influence score for a given node
    void addInfluenceScore(int node, int score) {
        influenceScores[node] = score;
    }

    // Associates a user label with a node
    void addUserLabel(int node, const string& name) {
        userLabels[node] = name;
    }

    // Retrieves the user label for a node, or a default label if not found
    string getUserLabel(int node) const {
        auto it = userLabels.find(node);
        if (it != userLabels.end()) {
            return it->second;
        }
        return "User " + to_string(node);
    }

    // Implements Dijkstra's algorithm to find the shortest path from start to end
    pair<int, list<int>> dijkstra(int start, int end) {
        unordered_map<int, int> distance; // Stores shortest distance from start to each node
        unordered_map<int, int> parent; // Stores the parent of each node in the path
        set<pair<int, int>> pq; // Priority queue to select the node with the smallest distance

        // Initialize distances to infinity
        for (const auto& pair : adjacencyList) {
            distance[pair.first] = numeric_limits<int>::max();
        }
        distance[start] = 0;
        pq.insert({0, start});

        while (!pq.empty()) {
            int u = pq.begin()->second;
            pq.erase(pq.begin());

            if (u == end) break; // Stop if the end node is reached

            // Relaxation step for each neighbor
            for (const auto& neighbor : adjacencyList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (distance[u] + weight < distance[v]) {
                    pq.erase({distance[v], v});
                    distance[v] = distance[u] + weight;
                    parent[v] = u;
                    pq.insert({distance[v], v});
                }
            }
        }

        // Reconstruct the path from start to end
        list<int> path;
        if (distance[end] == numeric_limits<int>::max()) {
            return {-1, path}; // Return -1 if no path exists
        }

        for (int at = end; at != start; at = parent[at]) {
            path.push_front(at);
        }
        path.push_front(start);

        return {distance[end], path};
    }

    // Implements A* algorithm to find the shortest path from start to end
    pair<int, list<int>> astar(int start, int end) {
        unordered_map<int, int> gScore; // Cost from start to each node
        unordered_map<int, int> fScore; // Estimated total cost from start to end through each node
        unordered_map<int, int> parent; // Stores the parent of each node in the path
        set<pair<int, int>> openSet; // Open set to track nodes to be evaluated

        // Initialize scores to infinity
        for (const auto& pair : adjacencyList) {
            gScore[pair.first] = numeric_limits<int>::max();
            fScore[pair.first] = numeric_limits<int>::max();
        }

        gScore[start] = 0;
        fScore[start] = nodeConnections[start]; // Heuristic based on node connections
        openSet.insert({fScore[start], start});

        while (!openSet.empty()) {
            int current = openSet.begin()->second;
            if (current == end) {
                list<int> path;
                for (int at = end; at != start; at = parent[at]) {
                    path.push_front(at);
                }
                path.push_front(start);
                return {gScore[end], path};
            }

            openSet.erase(openSet.begin());

            // Evaluate each neighbor
            for (const auto& neighbor : adjacencyList[current]) {
                int next = neighbor.first;
                int weight = neighbor.second;
                int tentative_gScore = gScore[current] + weight;

                if (tentative_gScore < gScore[next]) {
                    parent[next] = current;
                    gScore[next] = tentative_gScore;
                    fScore[next] = gScore[next] + nodeConnections[next];
                    openSet.insert({fScore[next], next});
                }
            }
        }

        return {-1, list<int>()}; // Return -1 if no path exists
    }

    // Finds the longest chain of influence based on influence scores
    pair<int, list<int>> longestInfluenceChain() {
        set<pair<int, int>> nodes; // Set of nodes sorted by influence score
        for (const auto& pair : influenceScores) {
            nodes.insert({pair.second, pair.first});
        }

        unordered_map<int, int> dp; // Dynamic programming table for longest chain length
        unordered_map<int, int> prev; // Stores the previous node in the chain
        int maxLen = 1; // Maximum length of the influence chain
        int endNode = nodes.begin()->second; // End node of the longest chain

        // Dynamic programming to find the longest chain
        for (const auto& current : nodes) {
            int currentNode = current.second;
            dp[currentNode] = 1;
            prev[currentNode] = -1;

            for (const auto& previous : nodes) {
                int prevNode = previous.second;
                if (previous.first < current.first && 
                    isConnected(currentNode, prevNode) && 
                    dp[prevNode] + 1 > dp[currentNode]) {
                    dp[currentNode] = dp[prevNode] + 1;
                    prev[currentNode] = prevNode;
                    if (dp[currentNode] > maxLen) {
                        maxLen = dp[currentNode];
                        endNode = currentNode;
                    }
                }
            }
        }

        // Reconstruct the longest influence chain
        list<int> chain;
        for (int at = endNode; at != -1; at = prev[at]) {
            chain.push_front(at);
        }

        return {maxLen, chain};
    }

private:
    // Checks if there is a direct connection between nodes u and v
    bool isConnected(int u, int v) {
        for (const auto& neighbor : adjacencyList[u]) {
            if (neighbor.first == v) return true;
        }
        return false;
    }
}; 