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
    unordered_map<int, list<pair<int, int>>> adjacencyList;
    unordered_map<int, int> influenceScores;
    unordered_map<int, int> nodeConnections;
    unordered_map<int, string> userLabels;

public:
    void addEdge(int u, int v, int weight) {
        adjacencyList[u].push_back({v, weight});
        adjacencyList[v].push_back({u, weight});
        nodeConnections[u]++;
        nodeConnections[v]++;
    }

    void addInfluenceScore(int node, int score) {
        influenceScores[node] = score;
    }

    void addUserLabel(int node, const string& name) {
        userLabels[node] = name;
    }

    string getUserLabel(int node) const {
        auto it = userLabels.find(node);
        if (it != userLabels.end()) {
            return it->second;
        }
        return "User " + to_string(node);
    }

    pair<int, list<int>> dijkstra(int start, int end) {
        unordered_map<int, int> distance;
        unordered_map<int, int> parent;
        set<pair<int, int>> pq;

        for (const auto& pair : adjacencyList) {
            distance[pair.first] = numeric_limits<int>::max();
        }
        distance[start] = 0;
        pq.insert({0, start});

        while (!pq.empty()) {
            int u = pq.begin()->second;
            pq.erase(pq.begin());

            if (u == end) break;

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

        list<int> path;
        if (distance[end] == numeric_limits<int>::max()) {
            return {-1, path};
        }

        for (int at = end; at != start; at = parent[at]) {
            path.push_front(at);
        }
        path.push_front(start);

        return {distance[end], path};
    }

    pair<int, list<int>> astar(int start, int end) {
        unordered_map<int, int> gScore;
        unordered_map<int, int> fScore;
        unordered_map<int, int> parent;
        set<pair<int, int>> openSet;

        for (const auto& pair : adjacencyList) {
            gScore[pair.first] = numeric_limits<int>::max();
            fScore[pair.first] = numeric_limits<int>::max();
        }

        gScore[start] = 0;
        fScore[start] = nodeConnections[start];
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

        return {-1, list<int>()};
    }

    pair<int, list<int>> longestInfluenceChain() {
        set<pair<int, int>> nodes;
        for (const auto& pair : influenceScores) {
            nodes.insert({pair.second, pair.first});
        }

        unordered_map<int, int> dp;
        unordered_map<int, int> prev;
        int maxLen = 1;
        int endNode = nodes.begin()->second;

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

        list<int> chain;
        for (int at = endNode; at != -1; at = prev[at]) {
            chain.push_front(at);
        }

        return {maxLen, chain};
    }

private:
    bool isConnected(int u, int v) {
        for (const auto& neighbor : adjacencyList[u]) {
            if (neighbor.first == v) return true;
        }
        return false;
    }
}; 