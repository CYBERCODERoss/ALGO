# Social Network Analysis Project - User Guide

## Table of Contents
1. [System Requirements](#system-requirements)
2. [Project Setup](#project-setup)
3. [Building the Project](#building-the-project)
4. [Running the Program](#running-the-program)
5. [Input Format](#input-format)
6. [Understanding Output](#understanding-output)
7. [Troubleshooting](#troubleshooting)

## System Requirements
- C++ compiler with C++17 support (g++ recommended)
- Make build system
- Minimum 4GB RAM (recommended for large graphs)
- Linux/Unix environment (WSL for Windows users)

## Project Setup

### Directory Structure
```
project_root/
├── data/
│   ├── social-network-proj-graph.txt
│   ├── social-network-proj-Influences.txt
│   ├── social-network-proj-LABELS.txt
│   └── DATA-DESCRIPTION.txt
├── social_network.hpp
├── main.cpp
└── Makefile
```

### Required Files
1. **Source Files**:
   - `social_network.hpp`: Contains graph and algorithm implementations
   - `main.cpp`: Contains the main program logic
   - `Makefile`: Build configuration

2. **Data Files** (must be in `data/` directory):
   - `social-network-proj-graph.txt`: Network connections data
   - `social-network-proj-Influences.txt`: User influence scores
   - `social-network-proj-LABELS.txt`: User names and IDs

## Building the Project

1. **Clean Build**:
   ```bash
   make clean
   ```

2. **Compile**:
   ```bash
   make
   ```

3. **Clean and Build in One Step**:
   ```bash
   make clean && make
   ```

## Running the Program

1. **Execute**:
   ```bash
   ./social_network
   ```

2. **Input Requirements**:
   - When prompted, enter two node numbers:
     ```
     Enter Starting Node: [enter a number]
     Enter Ending Node: [enter a number]
     ```
   - Valid node numbers are between 0 and 40000

## Input Format

### Valid Input Examples
```
Enter Starting Node: 523
Enter Ending Node: 5229
```

### Sample Node Pairs for Testing
- Test Case 1: 523 → 5229 (Original test case)
- Test Case 2: 223 → 5229 (Alternative path)
- Test Case 3: 1000 → 2000 (Custom test)

## Understanding Output

### 1. Part 1: Shortest Path Results
```
Dijkstra's Algorithm:
Shortest Distance: 115
Path: [
523 (Carlos Gamble) → 18631 (Virginia Miller) → ...
]
Time taken: 42ms

A* Algorithm:
Shortest Distance: 116
Path: [
523 (Carlos Gamble) → 18631 (Virginia Miller) → ...
]
```

### 2. Part 2: Longest Influence Chain
```
Longest Chain Length: 18
User Sequence: [
6595 (Trevor Jones) → 14063 (Lorraine Hopkins) → ...
]
```

### Output Elements
- Node ID: Numerical identifier
- User Name: In parentheses (e.g., "Carlos Gamble")
- Path Arrows: → indicates connection between nodes
- Distance: Total path weight
- Time taken: Processing time in milliseconds

## Troubleshooting

### Common Issues and Solutions

1. **Compilation Errors**:
   - Error: "C++ version not supported"
     - Solution: Update g++ or use: `g++ -std=c++17`
   - Error: "File not found"
     - Solution: Check data/ directory structure

2. **Runtime Errors**:
   - Error: "Could not open file"
     - Solution: Verify data files exist in data/ directory
   - Error: "Invalid input"
     - Solution: Enter only numeric values for node IDs

3. **Performance Issues**:
   - Long processing time
     - Normal for large graphs
     - Longest chain computation takes ~20 seconds

### Data File Requirements

1. **Graph File Format**:
   ```
   node1 node2 weight
   ```

2. **Influences File Format**:
   ```
   nodeID influence_score
   ```

3. **Labels File Format**:
   ```
   nodeID firstName lastName
   ```

## Additional Notes

- The program automatically loads all required data files
- Both shortest path algorithms run automatically
- The longest influence chain is computed for the entire network
- All times are measured and displayed in milliseconds
- User names are displayed alongside node IDs for better readability

## Support

For additional help or to report issues:
1. Check the troubleshooting section
2. Verify file formats and permissions
3. Ensure all data files are present in the correct location 