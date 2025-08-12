#include <iostream>
#include <vector>
#include <unordered_set>

using std::cout, std::endl, std::vector, std::unordered_set;

class UndirectedUnweightedGraph {

    private:
        vector< unordered_set<int> > adj;

        void validateNode(int node){
            if (node > numNodes-1 || node < 0){
                std::cerr << "ERROR: Node " << std::to_string(node) << " is out of range." << std::endl;
                exit(EXIT_FAILURE);
            } 
        }

        void validateNeighbor(int node, const unordered_set<int> &neighbors){
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

        void addAllToAdj(int node, const unordered_set<int> &neighbors){
            adj[node].insert(neighbors.begin(), neighbors.end());
        }

        void addToAdj(int node, int neighbor){
            adj[node].insert(neighbor);
        }

        void removeAllFromAdj(int node, const unordered_set<int> &neighbors){
            for (int neighbor : neighbors){
                removeFromAdj(node, neighbor);
            }
        }

        void removeFromAdj(int node, int neighbor){
            adj[node].erase(neighbor);
        }

    public:
        int numNodes;
        UndirectedUnweightedGraph(int numNodes) : adj(numNodes), numNodes(numNodes){}

        void addEdges(int node, const unordered_set<int> &neighbors){
            validateNode(node); validateNeighbor(node, neighbors);
            addAllToAdj(node, neighbors);
            for (int neighbor : neighbors){
                addToAdj(neighbor, node);
            }
        }

        void removeEdges(int node, const unordered_set<int> &neighbors){
            validateNode(node); validateNeighbor(node, neighbors);
            removeAllFromAdj(node, neighbors);
            for (int neighbor : neighbors){
                removeFromAdj(neighbor, node);
            }
        }

        int degree(int node){
            return adj[node].size();
        }

        bool hasEdge(int source, int dest){
            validateNode(source); validateNode(dest);
            return static_cast<bool>(adj[source].count(dest));
        }

        unordered_set<int> getNeighbors(int node){
            return adj[node];
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