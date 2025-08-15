#include <iostream>
#include <string>
#include <unordered_set>

using std::string, std::cout, std::endl, std::unordered_set, std::vector;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {

        /**
            Uses a hashing (hash set) approach

            Time Complexity: O(n)
            The worst case occurs when there are no duplicates
            In this worst case, we iterate through ALL nums until we reach the end (as there is no early return)

            Space Complexity: O(n) in the worst case
            The worst case occurs when there are no duplicates
            In this worst case, all n non-duplicates are added to the cache (as there is no early return)
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