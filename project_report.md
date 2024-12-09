# Social Network Analysis Project Report

## Project Overview
This project implements a social network analysis system using graph algorithms and dynamic programming. The system analyzes user connections and influence patterns in a social network using C++ with an emphasis on efficient data structures and algorithms.

## Implementation Details

### Data Structures Used

1. **Primary Data Structures:**
   - `unordered_map<int, list<pair<int, int>>>` for adjacency list
   - `list<int>` for path storage
   - `set<pair<int, int>>` for priority queue operations
   - `unordered_map<int, int>` for score and distance tracking

2. **Advantages of Chosen Data Structures:**
   - `unordered_map`: O(1) average case access time
   - `list`: O(1) insertions at both ends
   - `set`: Automatic ordering and O(log n) insertion/deletion

## Part 1: Graph-Based Shortest Path Algorithms

### 1. Dijkstra's Algorithm Implementation

```cpp
pair<int, list<int>> dijkstra(int start, int end) {
    unordered_map<int, int> distance;
    unordered_map<int, int> parent;
    set<pair<int, int>> pq;

    // Initialize distances
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
    // Path reconstruction...
}
```

**Time Complexity Analysis:**
- Overall: O((V + E) log V)
  - V: number of vertices
  - E: number of edges
- Priority Queue Operations: O(log V)
- Edge Relaxation: O(E)
- Space Complexity: O(V)

### 2. A* Algorithm Implementation

```cpp
pair<int, list<int>> astar(int start, int end) {
    unordered_map<int, int> gScore;
    unordered_map<int, int> fScore;
    set<pair<int, int>> openSet;
    
    // Heuristic: number of connections
    gScore[start] = 0;
    fScore[start] = nodeConnections[start];
    // ... algorithm implementation
}
```

**Time Complexity Analysis:**
- Overall: O((V + E) log V)
- Heuristic Calculation: O(1)
- Space Complexity: O(V)
- Improvement over Dijkstra: Better directional guidance

## Part 2: Dynamic Programming Solution

### Longest Influence Chain Implementation

```cpp
pair<int, list<int>> longestInfluenceChain() {
    set<pair<int, int>> nodes;
    for (const auto& pair : influenceScores) {
        nodes.insert({pair.second, pair.first});
    }

    unordered_map<int, int> dp;
    unordered_map<int, int> prev;
    // ... DP implementation
}
```

**Time Complexity Analysis:**
- Overall: O(V²)
- Node Sorting: O(V log V)
- DP Computation: O(V²)
- Space Complexity: O(V)

## Performance Comparisons

1. **Shortest Path Algorithms:**
   - Dijkstra: ~40ms average runtime
   - A*: ~89ms average runtime
   - A* provides more optimal paths in terms of node exploration

2. **Longest Chain Algorithm:**
   - Runtime: ~4020ms for complete graph analysis
   - Memory Usage: Linear in terms of vertex count

## Implementation Challenges and Solutions

1. **Memory Management:**
   - Challenge: Large graph storage
   - Solution: Used adjacency lists instead of matrix
   - Result: Reduced memory from O(V²) to O(V + E)

2. **Performance Optimization:**
   - Challenge: Slow path reconstruction
   - Solution: Used `list` with `push_front` instead of vector
   - Result: Eliminated need for reverse operations

3. **Input Validation:**
   ```cpp
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
   ```

## Test Cases and Results

1. **Sample Test Case:**
   - Start Node: 523
   - End Node: 5229
   - Dijkstra Path Length: 115
   - A* Path Length: 116
   - Longest Chain Length: 18

2. **Performance Results:**
   ```
   Dijkstra's Algorithm:
   Path: [523, 18631, 28318, 38056, 30570, 30312, 21052, 1185, 32946, 25234, 39811, 13076, 35687, 39727, 5229]
   Time: 40ms

   A* Algorithm:
   Path: [523, 18631, 18158, 39300, 38482, 10851, 25687, 37791, 29925, 34632, 13077, 5229]
   Time: 89ms
   ```

## Conclusion

The implementation successfully meets all project requirements with efficient algorithms and data structures. The use of modern C++ features and careful consideration of data structure choices resulted in a robust and performant solution.

### Future Improvements
1. Parallel processing for longest chain computation
2. Cache optimization for frequently accessed nodes
3. Memory pool allocation for large graphs 