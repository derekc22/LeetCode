#include <iostream>
#include <vector>
#include <unordered_set>
#include "../data-structures/graph.h"

using std::cout, std::endl, std::vector, std::unordered_set;


vector<int> dfs(UndirectedUnweightedGraph &G, int source){

    vector<int> edgeTo(G.numNodes, -1);
    vector<int> marked(G.numNodes);

    std::function<void(int)> traverse;

    traverse = [&](int curr) {
        cout << curr << endl;
        marked[curr] = 1;
        for (int neighbor : G.getNeighbors(curr)){
            if (!marked[neighbor]){
                edgeTo[neighbor] = curr;
                traverse(neighbor);
            }
        }
    };

    traverse(source);
    return edgeTo;
}


int main(){
    UndirectedUnweightedGraph G(9);
    G.addEdges(0, unordered_set<int>{1});
    G.addEdges(1, unordered_set<int>{0, 2, 4});
    G.addEdges(2, unordered_set<int>{1, 5});
    G.addEdges(3, unordered_set<int>{4});
    G.addEdges(4, unordered_set<int>{1, 5});
    G.addEdges(5, unordered_set<int>{2, 4, 6, 8});
    G.addEdges(6, unordered_set<int>{5, 7});
    G.addEdges(7, unordered_set<int>{6});
    G.printGraph();

    auto edgeTo = dfs(G, 0);
    for (int edge : edgeTo){
        cout << edge << ", ";
    }
    cout << endl;

    return 0;
}