#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector, std::unordered_map;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        /**
            https://www.youtube.com/watch?v=KLlXCFG5TnA
            In this solution, each number is visited. The number needed to reach the target calculated and then checked for in the hash map
            If the number is found, the indices of both the current number and the needed number are returned
            If the number is not found, the current number (key) and its index (value) are inserted into the hash map 
            We must use a map (instead of a set) because the question asks us to return the INDICIES of the solution pair - not the solution pair itself
            The time complexity is O(n) - we only traverse the array once
            The space complexity is O(n) - we store the numbers in a hash map
            The access time for the hash map is O(1) on average
        */

        unordered_map<int, int> numMap;

        for (int i=0; i < nums.size(); i++){
            // Visit each number in the array

            int curr = nums[i];
            int need = target - curr;
            // Calculate the number needed to reach the target

            if ( numMap.find(need) != numMap.end() ){
                vector<int> sol = {i, numMap[need]};
                return sol;
                // If the number needed is found in the hash table, return the indices of both numbers

            } else {
                numMap.insert({curr, i});
                // Otherwise, insert the current number and its index into the hash table
            }
        }

        return {};
        
    }
};




int main(){
    vector<int> arr = {3, 3};
    int target = 6;

    Solution solution;
    vector<int> sol = solution.twoSum(arr, target);
    
    for (int elem : sol){
        std::cout << elem << " ";
    }
}