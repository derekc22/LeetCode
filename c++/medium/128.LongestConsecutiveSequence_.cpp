#include <iostream>
#include <vector>
#include <map>

using std::vector;
using std::cout; using std::endl;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

        std::map< int, vector<int> > numMap;

        for (const auto& num : nums){
            vector<int> surrounding = {num-1, num+1};

            numMap[num] = surrounding;
        }

        int longestN;

        int n;
        n = (nums.size() > 0) ? 1 : 0;
        longestN = n;

        
        for (int elem : nums){
            vector<int> list = numMap[elem];
            checkSurrounding(elem, list, numMap, n);

            if (n > longestN){
                longestN = n;
            }
            n = 1;
        }


        return longestN;
        
    }


    void checkSurrounding(int key, vector<int> surrounding, std::map<int, vector<int>>& numMap, int& n){
        numMap.erase(key);
        for (auto& surround : surrounding){
            if (numMap.find(surround) != numMap.end()){
                n++;
                checkSurrounding(surround, numMap[surround], numMap, n);
            }
        }
        
    }

};


int main(){

    vector<int> vec = {9,1,4,7,3,-1,0,5,8,-1,6};

    Solution sol;

    cout << sol.longestConsecutive(vec) << endl;

    return 0;
}