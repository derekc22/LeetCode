#include <iostream>
#include <vector>
#include <unordered_set>


using std::vector;
using std::cout; using std::endl;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

        /**
            https://www.youtube.com/watch?v=P6RZZMu_maU
            In this solution, we use a set to store the unique numbers from the input vector
            In the LeetCode test cases, duplicate numbers were not counted in the sequence, thus whenever you encounter a problem where duplicates are not counted, it may be wise to use a set (at least as a starting point)
            We then iterate through the set, and for each number, we check if it has an immediate predecessor (num-1)
            If a number does not have an immediate predecessor, that means that it is the start of a new sequence
            If a number does have an immediate predecessor, that means that it is not the start of a new sequence, and we skip it
            Once we've identified the start of a sequence, we check each subsequent number in the proposed sequence (num+n) to see if it exists in the set
            If it does, we increment n until we reach a number that does not exist in the set
            Finally, we compare the length of the current sequence (n) with the longest sequence found so far
            If the current sequence is longer, we update the longest sequence length to the current sequence length
         */

        std::unordered_set<int> numSet;

        for (const auto& num : nums){
            numSet.insert(num);
        }

        // for (const auto& num : numSet){
        //     cout << num << " ";
        // }
        // cout << endl;

        int longestN;

        int n;
        n = (nums.size() > 0) ? 1 : 0;
        longestN = n;

        
        for (int elem : numSet){
            vector<int> list = {elem-1, elem+1};
            checkSurrounding(elem, list, numSet, n);

            if (n > longestN){
                longestN = n;
                // cout << n << endl;
            }
            n = 1;
        }

        return longestN;
        
    }


    void checkSurrounding(int key, vector<int>& surrounding, std::unordered_set<int>& numSet, int& n){
        numSet.erase(key);
        for (auto& surround : surrounding){
            if (numSet.find(surround) != numSet.end()){
                n++;
                vector<int> newList = {surround-1, surround+1};
                checkSurrounding(surround, newList, numSet, n);
            }
        }
        
    }

};


int main(){

    // vector<int> vec = {100, 4, 200, 1, 3, 2};
    vector<int> vec = {9,1,4,7,3,-1,0,5,8,-1,6};
   
    Solution sol;

    cout << sol.longestConsecutive(vec) << endl;

    return 0;
}