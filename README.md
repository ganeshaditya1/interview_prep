# Coding interview preparation
## Build & running instructions.

I intentionally kept the build/running steps simple. The primary focus of this repo is to help me quickly revise the fundamental algorithms. As a part of my interview preparation I am going to clone this repo and re-implement some of the algorithms or experiment with their implementation to make sure I understand the underlaying concepts thoroughly. I also want to be able to do this quickly. Because of this I felt that using cmake/meson/make/ctest would add unnecessary complexity. If I am troubleshooting my implementation that I don't want to be in a position where I have to guess if my changes are breaking because of the build system/ctest or if my changes are genuinely broken.

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
![Graph of Asymptotic notations. Taken from USTC website.](http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/25_a.gif)

Graph of Asymptotic notations. [Taken from USTC website.](http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap02.htm)

[Big-oh vs small-oh](https://stackoverflow.com/a/1364491/2340452)
### Graph algorithms

#### 1. BFS, Breadth first search
Cover all the nodes neighboring of the starting node first, then fan out and cover their neighbors, then their neighbors and so on.

**Time complexity** O(V + E) where V is the number of vertices, E is the number of edges. There could be cycles so the number of edges could be different from the number of vertices.  
**Space complexity** O(E) BFS needs a queue to keep track of what nodes to visit next. It also needs a set/list to keep track of nodes we have already visited, so we don't get stuck in a loop re-visiting already visited nodes.

#### 2. DFS, Depth first search
Basically you start with a node and move on to it's child and then it's child and so on till you hit a node with no children or a node whose children have all been covered. Then you back track and explore an unvisited child of the previous node.

**Time complexity** Same as BFS  
**Space complexity** Same as BFS

#### 3. Dijkstra Algorithm

Djikstra's algorithm is used to find the shortest path from source node to all the nodes of a graph. We can do this using BFS/DFS too. With BFS/DFS we would visit a node and note down the distance of that node from the source node then explore it's children. If at any point we revisit that node and find out a new path to that node that is shorter than what we previously computed, we update the distance and re-explore/recalculate all of it's children.

Dijkstra's algorithm does a similar thing. It works excatly like BFS algorithm. But instead of using a regular queue, it uses a priority queue and picks a node that is the shortest distance from the source from the frontier. With Djikstra's algorithm we won't be in a situation where we have to re-explore a node again.

**Time complexity** O((|V| + |E|)logV) This is similar to the time complexity of BFS. But in BFS we use a regular queue. Poping and pushing from a regular queue takes O(1) time. For priority queues, the cost of poping and pushing is O(logN) where N is the number of items in the queue. In Dijkstra's algorithm, each vertice will go into the queue as many times as it has an edge. There are E edges. In the worst case when the graph is a fully connected graph, E = V(V - 1) = V^2. For each edge we do a push. Cost of these pushes is O(logE) = O(logV^2) = O(2logV) = O(logV). Hence the total cost is O((V + E)logV)  
**Space complexity** O(V^2) The maximum number of items in the queue will be O(E) = O(V^2)  

#### 4 Bellman-Ford Algorithm

This essentially checks if there is a negative cycle in a graph and throws an exception. A graph can have negative weights and we could compute the shortest path for each source-vertex pair in that graph, but if the graph has a cycle where an edge has negative weight then everytime we go through that cycle the cost of connecting the vertices in that cycle to the source decreases. A graph with a negative cycle cannot have shortest paths. 
Bellman-ford detects cycles by going over all the edges V - 1 times

As to why we need to run this V - 1 times? In each iteration we relax atleast 1 node. I.e. we find the shortest path from source to that node. The source node is already relaxed to begin with as the distance from source to source is 0. So that leaves us with V - 1 nodes that need to be relaxed. 

Algorithm:
```
// Step 2: relax edges repeatedly
    repeat |V|−1 times:
        for each edge (u, v) with weight w in edges do
            if distance[u] + w < distance[v] then
                distance[v] := distance[u] + w
                predecessor[v] := u
```
[Source for the above algorithm](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm#Algorithm)

**Time complexity** O(|V| * |E|)  
**Space complexity** O(|V|) to store the distances of each node from source.

#### 5 Floyd-Warshall Algorithm

This algorithm computes the shortest paths from every node to every other node in a graph. It does this by iterating over two nodes at a time and then checking all the other nodes to see using those nodes as an intermediatary node shortens the path between the two nodes that we are currently considering.

It's essentially this algorithm
```
for nodeA in nodes
  for nodeB in nodes
   for nodeC in nodes
     dist[A][B] = min(dist[A][B], dist[A][C] + dist[C][B])
```

**Time complexity** O(|V|^3)  
**Space complexity** O(|E|) 

#### 6.1 Minimum spanning tree Algorithms - Prim's Algorithm

Minimum spanning tree algorithm concerns with picking a subset of edges in a graph, so that the overall connectivity of the graph doesn't change and also, if you add up all the edge weights, the sum you obtain is the minimum of all such subset of edges you can pick.


Prim's algorithm is same as Dijkstra's algorithm. You maintain a frontier set of nodes and explore all the neighbors of these nodes. At each step you pick a node whose weight from a node in the frontier set is the lowest. To do this picking we can use a Priority queue. 


**Time complexity** Same as Dijkstra's  
**Space complexity** Same as Dijkstra's 

#### 6.2 Minimum spanning tree Algorithms - Kruskal's Algorithm

In Kruskal's algorithm, we sort all the edges in the graph. Then we pick one edge at a time, add that edge to the forest we have. If adding an edge causes a cycle, i.e. it connects two nodes that are already connected than we don't add that edge. Once we have added V - 1 edges to our forest, our forest would have essentially become a minimum spanning tree. For checking if two vertices are already connected we will use a Dijoint-set data structure. Also, Kruskal's algorithm can be parallelized unlike Prim's algorithm

**Time complexity** O(ElogV) The cost of sorting edges = O(ElogE) = O(ElogV^2) = O(2ElogV) = O(ElogV) in case of a fully connected graph, which is the worst case. The cost of checking for cycles and adding a new edge into our graph is O(E\*ack(V)). Where ack is the inverse ackerman function. O(ElogV + E*ack(V)) = O(ElogV)  
**Space complexity** O(|E| + |V|)

#### 7.1 Topological sort - Kahn's algorithm

A topological sorting of a graph is a way of visiting every node in the graph such that before visiting a node v we visit every node u, that has a directed node like incident on v like this: u -> v

In Kahn's algorithm, we go over all the edges in the graph and calculate the indegree of every node. Then we add all nodes with an indegree of 0 into a queue. Then we keep popping elements off from the queue and each time we pop an element off of the queue we do two things. First, we add it to the result list and then we go through all of it's neighbors and decrease their indegree by 1. If any of these neighbors reach an indegree of 0, we add those to the queue as well. Once the queue is empty we stop.

**Time complexity** O(|E| + |V|)  
**Space complexity** O(|V|)

#### 7.2 Topological sort - DFS algorithm

Start from a node, do a DFS on the node. After visiting all the children of a node, right before returning add the current node to the head of the result list. 

**Time complexity** Same as DFS  
**Space complexity** Same as DFS

#### 8. Disjoint-set Algorithm or Union-Find Algorithm

This datastructure is a way to quickly check if two nodes belong to the same graph/tree/have the same parent. This datastructure has basically two operations. **Find** and **Union**. Find takes a node as input and returns it's parent. Union takes two nodes and merges them together such that they both have the same parent. Union under the hood uses Find calls to find the parents of the two nodes that need to be merged. Find call operates in a recursive way. i.e. if a node has a long chain of parents ex: a->b->c->d->e then find traverses this chain and finds the ultimate parent of the given node. find(a) in that example would return e. Also initially when a node is not merged into any other node, calling find on that node will return that node itself. I.e. intially each node is it's own parent.

There are generally two famous optimizations made when implementing the DSU datastructure.
1. **Path compression** when dealing with a long parent chain for example a->b->c->d->e each time we have to find the parent of a, we have to visit 5 different nodes. So an optimization we can do is to change a's parent to have it directly point to e whenever a find(a) call is made. We also do this for every node in the parent chain of a, so that all of these calls find(a), find(b), find(c), find(d), find(e) return e.
2. When merging two parents, we make the parent with fewer nodes the child of the parent with more number of children nodes. This is because once a parent becomes a child of another parent all of it's node's parent chain increase by 1. So we rather have fewer node's parent chain changed than having a lot of node's parent chain changed.

With these optimization in place, this is the time complexity of various operations of this datastructure.

**Find**  
**Time complexity** O(ack(N)) where ack is the reverse ackermann function or log*(n)

**Union**  
**Time complexity** O(ack(N))

**Space complexity**
O(N)

### String algorithms

#### 1. Trie datastructure

Given a set of words, this datastructure makes it easy to see if a given word is a member of that set. Also given a prefix, this datastructure can be used to find all words in the original set that have this prefix.

**Time complexity**  
For creating a Trie it is O(N).   
For checking if a prefix is member of the Trie it is O(N).  
For inserting into a trie it is O(N)  
For deleting a word it is O(N) as well.  
**Space complexity** O(N)

#### 2. KMP Algorithm

```
int strStr(string haystack, string needle) {
        vector<int> lps(needle.length(), 0);
        int len = 0, i = 1;
        while(i < needle.length()) {
            if(needle[i] == needle[len]) {
                lps[i] = ++len;
                i++;
            } else if(len > 0) {
                len = lps[len - 1];
            } else {
                i++;
            }
        }

        i = 0;
        int j = 0;
        while(i < haystack.length()) {
            if(haystack[i] == needle[j]) {
                j++;
                i++;
                if(j == needle.length()) {
                    return i - needle.length();
                }
            } else if(j > 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
        return -1;
    }
```

KMP checks if a pattern occurs in a given string quickly. It does this by preprocessing the pattern and creating a table called LPS or Longest proper prefix suffix. It's a table that shows what is the longest suffix upto an index that is also a proper prefix. A proper prefix of a string is a substring of the original string that is not the same as the original string. It needs to be atleast 1 character shorter than the original string. We use this table for doing the pattern matching on the input string. Basically when there is a mismatch between the pattern and the input string at a position, instead of going back to index 0 of the pattern, we use the prefix table or the failure table to back track to an earlier position of the pattern and attempt to match the input string from there.

**Time complexity** O(N) for matching, where N is the length of the input string. O(M) for pre-processing the input pattern where M is the length of the pattern.  
**Space complexity** O(M) for the LPS table. 
