#include "../data-structures/graph.h"

int main(){

    int numNodes = 5;
    UndirectedUnweightedGraph graph(numNodes);

    graph.addEdges(0, unordered_set<int>{1, 2, 3});
    graph.addEdges(1, unordered_set<int>{0, 2, 3});
    graph.addEdges(2, unordered_set<int>{0, 1, 3});
    graph.removeEdges(1, unordered_set<int>{2, 3});

    graph.printGraph();
    cout << std::boolalpha << graph.hasEdge(0, 2) << endl;


    return 0;
}