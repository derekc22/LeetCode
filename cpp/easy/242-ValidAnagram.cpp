#include <iostream>
#include <string>
#include <unordered_map>

using std::string, std::cout, std::endl, std::unordered_map;

class Solution {
public:
    bool isAnagram(string s, string t) {

        /**
            Uses a hashing (hash table) approach

            Time Complexity: O(n)
            We iterate through both s and t to increment and decrement, respectively, the character counts 

            Space Complexity: O(k)
            'counts' is initialized with k elements, where k in the number of unique chars in s
         */


        if (s.size() != t.size()) return false;
        // If s and t are different sizes, they CAN NOT be anagrams. Thus, return early

        unordered_map<char, int> counts;

        for (char c : s){
            counts[c]++;
            // Recall the behavior of maps in C++. See 33-Maps.cpp for more
            // Accessing counts[c] default-initializes the value to 0 if it didn't already exist in the map
            // ++ then increments that value
        }

        for (char c : t){
            counts[c]--;
        }

        for (const auto &pair : counts){
            if (pair.second != 0){
                return false;
            }
        }

        return true;
        
    }
};