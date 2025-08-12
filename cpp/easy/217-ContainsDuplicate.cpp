#include <iostream>
#include <string>
#include <unordered_set>

using std::string, std::cout, std::endl, std::unordered_set, std::vector;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {

        /**
            Uses a hashset approach
            Time Complexity: O(n) in the worst case 
            We iterate through all nums, checking the cache at each step
            The worst case occurs when there are no duplicates

            Space Complexity: O(n) in the worst case
            We iterate through all nums, adding to the cache at each step
            The worst case occurs when there are no duplicates
         */

        unordered_set<int> cache;

        // Iterate through all nums
        for (int num : nums){

            // cache.insert() returns std::pair<iterator, bool>, see 35-Sets.cpp for more
            // If 'bool' is false, the insertion was unsuccessful. That is, a duplicate exists, so we return true
            if ( !cache.insert(num).second ){
                return true;
            } 
        }

        return false;
        
    }
};