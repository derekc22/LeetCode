#include <iostream>
#include <string>
#include <unordered_map>

using std::string, std::cout, std::endl, std::unordered_map;

class Solution {
public:
    bool isAnagram(string s, string t) {

        if (s.size() != t.size()) return false;
        // If s and t are different sizes, they CAN NOT be anagrams. Thus, return early

        unordered_map<char, int> cache;

        for (char c : s){
            cache[c]++;
            // Recall the behavior of maps in C++. See 33-Maps.cpp for more
            // Accessing cache[c] default-initializes the value to 0 if it didn't already exist in the map
            // ++ then increments that value
        }

        for (char c : t){
            cache[c]--;
        }

        for (const auto &pair : cache){
            if (pair.second != 0){
                return false;
            }
        }

        return true;
        
    }
};