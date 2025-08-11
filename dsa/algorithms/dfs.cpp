#include <iostream>
#include <vector>
#include <unordered_set>
#include "../data-structures/graph.h"
#include <tuple>
#include <algorithm>
#include <deque>

using std::cout, std::endl, std::vector, std::unordered_set, std::tuple, std::find, std::deque;


vector<int> dfs(UndirectedUnweightedGraph &G, int source){

    deque<int> queue;
    vector<int> edgeTo(G.numNodes, -1);
    vector<int> marked(G.numNodes);
    marked[source] = 1;

    unordered_set<int> currNeighbors;

    std::function<int(int)> traverse;

    traverse = [&traverse, &G, &marked, &edgeTo](int curr) {
        marked[curr] = 1;
        for (int neighbor : G.getNeighbors(curr)){
            if (!marked[neighbor]){
                edgeTo[neighbor] = curr;
                traverse(neighbor);
            }
        }
        return 0;
    };

    traverse(source);
    return edgeTo;
}


int main(){
    UndirectedUnweightedGraph G(9);
    G.addEdges(0, vector<int>{1});
    G.addEdges(1, vector<int>{0, 2, 4});
    G.addEdges(2, vector<int>{1, 5});
    G.addEdges(3, vector<int>{4});
    G.addEdges(4, vector<int>{1, 5});
    G.addEdges(5, vector<int>{2, 4, 6, 8});
    G.addEdges(6, vector<int>{5, 7});
    G.addEdges(7, vector<int>{6});
    G.printGraph();

    auto edgeTo = dfs(G, 0);
    for (int edge : edgeTo){
        cout << edge << ", ";
    }
    cout << endl;

    return 0;
}