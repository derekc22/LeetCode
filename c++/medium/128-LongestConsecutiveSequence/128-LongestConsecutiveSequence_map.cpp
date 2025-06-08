#include <iostream>
#include <vector>
#include <set>

using std::vector;
using std::cout; using std::endl;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

        /**
            Same as '128-LongestConsecutiveSequence_set.cpp', but uses a map (less space efficient) instead of a set
        */

        std::set<int> numSet;

        for (int num : nums){
            numSet.insert(num);
        }


        int n = (nums.size() > 0) ? 1 : 0;
        int longestSequence = n;

        for (int num : numSet){

            if (numSet.find(num-1) == numSet.end()){

                n = 1;

                while (numSet.find(num+n) != numSet.end()){
                    n++;
                };

                if (n > longestSequence){
                    longestSequence = n;
                };
            
            };

            

        };

        return longestSequence;

    };
};



int main(){

    vector<int> vec = {9,1,4,7,3,-1,0,5,8,-1,6};

    Solution sol;

    cout << sol.longestConsecutive(vec) << endl;

    return 0;
} 