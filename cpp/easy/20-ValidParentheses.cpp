/*
#include <iostream>
#include <string>
#include <unordered_map>

using std::string, std::cout, std::endl, std::unordered_map;

class Solution {
public:
    bool isValid(string s) {

        /**
            This was my first unsuccessful attempt at 20-ValidParentheses
            I attempted to use a two-pointer-style pattern. However, my assumptions, approach, and implementation were flawed
            Particularly, I attempt to use symmetry to solve the problem, like you would in a palindrome question
            However, a valid set of parentheses need not be symmetrical, unlike a palindrome. Thus, my incorrect reliance on this symmetry assumption caused this solution to fail
            
            My approach is as follows:
            For each bracket, check the adjacent bracket (adjR). If the adjacent bracket is a closing bracket of the same type, you're good to go and you can skip forward by 2 to the next opening bracket
            If they're not equal, NAIVELY use symmetry to assume that the ONLY other possible valid configuration for the closing bracket is at the mirror index (oppR) 
            However, this assumption is flawed.

            For example, in "([{}]{})", the opening bracket '[' at leftPtr=1 does not have an adjacent closing bracket ']'
            Thus, we check the mirror index at rightPtr = (size-1)-leftPtr = (8-1)-1 = 6
            However, we can clearly see that, at this index, there is a '}' NOT a ']'
            Thus, both if-statements are entered and our algorithm will return false

            Of course, this is the WRONG answer, since "([{}]{})" is a perfectly valid string of parentheses
            But, because our algorithm assumes that there are only ever two valid configurations: (a) opening and closing brackets adjacent or (b) opening and closing brackets at mirror indices like a palindrome...
            Our algorithm fails to catch perfectly valid patterns like "([{}]{})"
         *

        size_t size = s.size();
        if (size % 2 != 0) return false;

        unordered_map<char, char> pairs = {
            {'(', ')'},
            {'{', '}'},
            {'[', ']'},
        };

        int leftPtr = 0;
        bool valid = true;

        while (leftPtr <= size-2){
            char L = pairs[s[leftPtr]];
            char adjR = s[leftPtr+1];
            char oppR = s[(size-1)-leftPtr];
            cout <<  s[leftPtr] << ", " << L << ", " << adjR << ", " << oppR << endl;

            if (L != adjR){
                if (leftPtr < size/2 && L != oppR){
                    return false;
                } else {
                    leftPtr++;
                    continue;
                }
            }
            leftPtr += 2;
        }

        return valid;
        
    }
};
*/

/*
#include <iostream>
#include <string>
#include <unordered_map>

using std::string, std::cout, std::endl, std::unordered_map;

class Solution {
public:
    bool isValid(string s) {

        /**
            This was my second unsuccessful attempt at 20-ValidParentheses
            I attempted to use a hashing (hash table) approach pattern. However, my assumptions, approach, and implementation were flawed

            Instead of using the overly-restrictive hypothesis from my two-pointer-style approach (which incorrectly excluded valid configurations):
            There are only ever two valid configurations for bracket pairs: (a) opening and closing brackets adjacent or (b) opening and closing brackets at mirror indices like a palindrome...

            I came up with the following hypothesis that I thought was more general and not as restrictive:
            Any string of parentheses is valid so long as the number of opening brackets of a given parenthesis type is equal to the number of closing brackets of that same type
            
            However, this hypothesis was too general as it only considered counts and not order
            Thus, because the counts of '(', ')' and '[', ']' are equal, respectively, our algorithm would incorrectly consider the following string valid,  "([)]"
         *

        if (s.size() % 2 != 0) return false;

        unordered_map<char, int> counts;
        unordered_map<char, char> pairs = {
            {'(', ')'},
            {'{', '}'},
            {'[', ']'},
        };
        
        for (const char c : s){
            counts[c]++;
        }

        for (const auto& p : pairs){
            if (counts[p.first] != counts[p.second]){
                return false;
            };
        }

        return true;
        
    }
};
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>

using std::string, std::cout, std::endl, std::unordered_map, std::stack;

class Solution {
public:
    bool isValid(string s) {

        /**

         */

        size_t size = s.size();
        if (size % 2 != 0) return false;

        unordered_map<char, char> pairs = {
            {'(', ')'},
            {'{', '}'},
            {'[', ']'},
        };
        stack<char> stack;


        for (char c : s){

            if (pairs.contains(c)){
                stack.push(c);
                continue;
            }
            if (c != pairs[stack.top()]){
                return false;
            } 
            stack.pop();
        }

        return true;
    }  

};

int main(){


    Solution sol;

    // Example 1
    // string s = "([{[]}]{})"; // Answer is true

    // Example 2
    // string s = "([{}][])"; // Answer is true

    // Example 3
    // string s = "()[]{}"; // Answer is true

    // Example 4
    string s = "()[](]"; // Answer is false

    cout << sol.isValid(s) << endl;

    return 0;

}