#include <iostream>
#include <vector>
#include <unordered_set>
#include "../data-structures/graph.h"
#include <tuple>
#include <deque>

using std::cout, std::endl, std::vector, std::unordered_set, std::tuple, std::deque;


std::tuple<vector<int>, vector<int>> bfs(UndirectedUnweightedGraph &G, int source){

    deque<int> queue;
    vector<int> marked(G.numNodes);
    vector<int> edgeTo(G.numNodes, -1);
    vector<int> distTo(G.numNodes);

    marked[source] = 1;
    int curr = source;
    unordered_set<int> currNeighbors;
    bool truncated = false;

    while (!truncated){
        currNeighbors = G.getNeighbors(curr);
        for (int neighbor : currNeighbors){
            if (!marked[neighbor]){
                queue.push_back(neighbor);
                distTo[neighbor] = distTo[curr]+1;
                edgeTo[neighbor] = curr;
                marked[neighbor] = 1;
            }
        }

        if (queue.empty()){
            truncated = true;
        } else {
            curr = queue[0];
            queue.pop_front();
        }
    }

    return std::make_tuple(edgeTo, distTo);

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

    auto [edgeTo, distTo] = bfs(G, 0);
    for (int edge : edgeTo){
        cout << edge << ", ";
    }
    cout << endl;
    for (int dist : distTo){
        cout << dist << ", ";
    }
    cout << endl;


    return 0;
}