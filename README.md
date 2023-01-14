# Coding interview preparation
## Build & running instructions.

I intentionally kept the build/running steps simple. I don't want to have to deal with cmake or make errors when I want to quickly revise something in this repo by reimplementing some of the code in this repo. It's also for this reason, I did not use ctest for the test cases.

The want the primary focus of this repository to be on highlight DS&A concepts. Not C++ best practises or build tricks.

Having said that, these are commands for building and running:
```
g++ --std=c++17 -g sorting.cpp -o sorting.out
./searching.out

g++ --std=c++17 -g searching.cpp -o searching.out
./searching.out

g++ --std=c++17 -g hashing.cpp -o hashing.out
./hashing.out
```

## Complexities of some other well known algorithms
### Graph algorithms

#### 1. BFS, Breadth first search
Cover all the nodes neighboring the starting node, then fan out and cover their neighbors, then their neighbors and so on.

**Time complexity** O(V + E) where V is the number of vertices, E is the number of edges. There could be cycles so the number of edges could be different from the number of vertices.  
**Space complexity** O(E) BFS needs a queue to keep track of what nodes to visit next. It also needs a set/list to keep track of nodes we have already visited, so we don't get stuck in a loop re-visiting already visited nodes.

#### 2. DFS, Depth first search
Basically you start with a node and move on to it's child and then it's child and so on till you hit a node with no children or a node whose children have all been covered. Then you back track and explore an unvisited child.

**Time complexity** Same as BFS  
**Space complexity** Same as BFS

#### 3. Dijkstra Algorithm

Djikstra's algorithm is used to find the shortest path from source node to all the nodes of a graph. We can do this using BFS/DFS too. With BFS/DFS we would visit a node and note down the distance of that node from the source node then explore it's children. If at any point we revisit that node and find out a new path to that node that is shorter than what we previously computed, we update the distance and re-explore/recalculate all of it's children.

Dijkstra's algorithm does a similar thing. It works excatly like BFS algorithm. But instead of using a regular queue, it uses a priority queue and picks a node that is the shortest distance from the source from the frontier. With Djikstra's algorithm we won't be in a situation where we have to re-explore a node again.

**Time complexity** O((|V| + |E|)logV) This is similar to the time complexity of BFS. But in BFS we use a regular queue. Poping and pushing from a regular queue takes O(1) time. For priority queues, the cost of poping and pushing is O(N) where N is the number of items in the queue. In Dijkstra's algorithm, each vertice will go into the queue as many times as it has an edge. There are E edges. In the worst case when the graph is a fully connected graph, E = V(V - 1) = V^2. For each edge we do a push. Cost of these pushes is O(logE) = O(logV^2) = O(2logV) = O(logV). Hence the total cost is O((V + E)logV)  
**Space complexity** O(V^2) The maximum number of items in the queue will be O(E) = O(V^2)  

#### 4 Bellman-Ford Algorithm

This essentially checks if there is a negative cycle in a graph and throws an exception. A graph can have negative weights and we could compute the shortest path for each source-vertex pair in that graph, but if the graph has a cycle where an edge has negative weight then everytime we go through that cycle the cost of connecting the vertices in that cycle to the source decreases. A graph with a negative cycle cannot have shortest paths. 
Bellman-ford detects cycles by going over all the edges V - 1 times

As to why we need to run this V - 1 times? In each iteration we relax atleast 1 node. I.e. we find the shortest path from source to that node. The source node is already relaxed to begin with as the distance from source to source is 0. So that leaves us with V - 1 nodes that need to be relaxed. 

**Time complexity** O(|V| * |E|)  
**Space complexity** O(|V|) to store the distances of each node from source.

#### 5 Floyd-Warshall Algorithm

This thing computes the shortest paths from every node to every other node in a graph. It does this by iterating over two nodes at a time and then checking all the other nodes to see using those nodes as an intermediatary node shortens the path between the two nodes that we are currently considering.

It's essentially this algorithm
```
for nodeA in nodes
  for nodeB in nodes
   for nodeC in nodes
     dist[A][B] = min(dist[A][B], dist[A][C] + dist[C][B])
```

**Time complexity** O(|V|^3)  
**Space complexity** O(|E|) 

