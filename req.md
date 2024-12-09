

**Dataset:**

For your Design and Analysis of Algorithm course project, you have to
use a dataset on Social Networks from '/data' use all the files to solve the problem

You need to follow these guidelines:
1. Code must be in c++
2. You need to use the graph data structure to solve the problem
3. You need to use the dynamic programming approach to solve the problem
Test Cases (35 Marks): Full marks will be awarded if all test cases are passed. 
Understanding (50 Marks): Marks will be given if students demonstrate a complete understanding of the code, are able to modify the code during the demo, and pass at least one test case.
Time Complexity (10 Marks): Marks will be awarded if a proper and detailed time complexity analysis is included in the report. Marks are only applicable if pass at least one test case.
Pseudo-Code (5 Marks): Marks will be given if a proper and detailed pseudo-code is added to the report. Marks are only applicable if pass at least one test case.
Part 2 (No marks If not solved with DP)
Test Cases (35 Marks): Full marks will be awarded if all test cases are passed. 
Understanding (50 Marks): Marks will be given if students demonstrate a complete understanding of the code, are able to modify the code during the demo, and pass at least one test case.
Time Complexity (10 Marks): Marks will be awarded if a proper and detailed time complexity analysis is included in the report. Marks are only applicable if pass at least one test case.
Pseudo-Code (5 Marks): Marks will be given if a proper and detailed pseudo-code is added to the report. Marks are only applicable if pass at least one test case.


Testcases:
Starting Node: 523 
Ending Node:   5229

Dijkstra's Algorithm:
Shortest Distance: 115
Path: [523, 18631, 28318, 38056, 30570, 30312, 21052, 1185, 32946, 25234, 39811, 13076, 35687, 39727, 5229]

 A* Algorithm:

Shortest Distance: 116
Path: [523, 18631, 18158, 39300, 38482, 10851, 25687, 37791, 29925, 34632, 13077, 5229]

Longest Chain of Influence: (This is for the whole graph)

Longest Chain Length: 18

User Sequence: [6595, 14063, 3243, 21070, 1389, 1392, 21445, 26187, 9799, 212, 28661, 11490, 20021, 35737, 21394, 9318, 20614, 1860]

will be like this

**Part** **1:** **Graph-Based**

This dataset contains information about connections (e.g., frequency of
interaction, intensity, or relevance) among multiple users in a social
network. In this project, you need to find the most significant
connections in this social network. To do this, you have to create a
graph of the given dataset. In your graph, the **Node** represents a
user and the **Edges** between them indicate their connection. The
**weight** on the edges shows the distance between two users. The
shorter the distance, the stronger the connection.

Your tasks are as follows:

> 1\. Create an undirected graph from the file which has 3 columns: the
> first two columns represent users and the third represents the weight
> of the link between them.
>
> 2\. Implement **Dijkstra** **algorithm** or **A\*** **algorithm** to
> find the shortest path from the graph created in (1).
>
> For A\* algorithm, use the following heuristic function h(n): The
> number of direct connections a user has.
>
> For a node n, h(n) equals the total number of neighbours connected to
> n. Implement efficiently by combining actual cost g(n) and the
> heuristic h(n).
>
> Please note implementing with A\* algorithm contains bonus points as
> it is a more efficient method of finding the shortest path.

**Part** **2:** **Dynamic** **Programming** **on** **Graph**

In a social network, each user can influence their direct connections.
The level of influence for each user is given in the Influences file
where the first column represents the user and the second column
represents the influence score of the user. You need to find the longest
chain of influence in the network such that the influence score of a
user in the chain is strictly greater than the previous user.

Task:

> 1\. Implement a **dynamic** **programming** **algorithm** to find the
> longest increasing path in terms of influence scores in the graph.
>
> 2\. Return the maximum length of the chain and the sequence of users
> in the chain.
