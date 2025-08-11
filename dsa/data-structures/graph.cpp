#include <iostream>
#include <vector>
#include <unordered_set>

using std::cout, std::endl, std::vector, std::unordered_set;

class UndirectedUnweightedGraph {

    private:
        int numNodes;
        vector< unordered_set<int> > adj;

        bool validateInput(int node, const vector<int> &neighbors){
            for (const auto &neighbor : neighbors){
                if (neighbor > numNodes-1 || neighbor < 0){
                    std::cerr << "ERROR: Neighbor " << std::to_string(neighbor) << " is out of range." << std::endl;
                    exit(EXIT_FAILURE);
                } else if (neighbor == node){
                    std::cerr << "ERROR: Neighbor " << std::to_string(neighbor) << " results in a self-connection." << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

        void addAllToAdj(int node, const vector<int> &neighbors){
            adj[node].insert(neighbors.begin(), neighbors.end());
        }

        void addToAdj(int node, int neighbor){
            adj[node].insert(neighbor);
        }

        void removeAllFromAdj(int node, const vector<int> &neighbors){
            for (int neighbor : neighbors){
                removeFromAdj(node, neighbor);
            }
        }

        void removeFromAdj(int node, int neighbor){
            adj[node].erase(neighbor);
        }

    public:
        UndirectedUnweightedGraph(int numNodes) : numNodes(numNodes), adj(numNodes) {}

        void addEdges(int node, const vector<int> &neighbors){
            validateInput(node, neighbors);
            addAllToAdj(node, neighbors);
            for (int neighbor : neighbors){
                addToAdj(neighbor, node);
            }
        }

        void removeEdges(int node, const vector<int> &neighbors){
            validateInput(node, neighbors);
            removeAllFromAdj(node, neighbors);
            for (int neighbor : neighbors){
                removeFromAdj(neighbor, node);
            }
        }


        void printGraph(){
            int n = 0;
            for (const auto &nodeAdj : adj){
                cout << n << ": [ ";
                for (const int &neighbor : nodeAdj){
                    cout << neighbor << ", ";
                }
                cout << "]" << endl;
                n++;
            }
        }
};




int main(){

    int numNodes = 5;
    UndirectedUnweightedGraph graph(numNodes);

    graph.addEdges(0, vector<int>{1, 2, 3});

    graph.addEdges(1, vector<int>{0, 2, 3});

    graph.addEdges(2, vector<int>{0, 1, 3});

    graph.removeEdges(1, vector<int>{2, 3});

    graph.printGraph();

    return 0;
}