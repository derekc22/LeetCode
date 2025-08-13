#include <iostream>
using std::string, std::cout, std::endl;

class Solution {
public:

    std::string formatString(const std::string& input) {
        std::string result;
        for (char ch : input) {
            if (std::isalnum(ch)) {
                result.push_back(std::tolower(ch));
            }
        }
        return result;
    }
    
/*
    bool isPalindrome(string s) {
         /**
         * This was my initial attempt at an algorithm that checks if a given string is a palindrome
         * This is a classic two-pointer problem as the structure of a palindrome is such that the first and last characters must match, no matter how many characters are in between
         * Thus, if any pair of characters at the two pointers do not match, the string is automatically not a palindrome 
        *
    
        s = formatString(s);
        cout << s << endl;

        int left = 0;
        int right = s.length()-1;
        char leftChar;
        char rightChar;
        bool isPal = true;

        while ( right - left > 0 && isPal){

            leftChar = s[left];
            rightChar = s[right];

            if (leftChar == rightChar){
                left++;
            } else {
                isPal = false;
            }
        }
        return isPal;   
    } 
*/


    bool isPalindrome(string s) {

        /**
            Uses a two-pointer approach

            This was my second attempt at 125-ValidPalindrome (without peeking). In my opinion, this solution is much cleaner (at least syntax-wise)

            Time Complexity: O(n)
            We iterate through half of the string
            
            Space Complexity: O(1)
            If you ignore the creation of the formatted string, we only create two pointers: O(1)
            If you include the creation of the formatted string, it is clearly O(n)
         */

        string formatted = formatString(s);
        auto left = formatted.begin();
        auto right = formatted.end()-1;

        while (left <= right){
            if (*left != *right){
                return false;
            }
            left++;
            right--;
        }

        return true;
    }

};


int main(){

    string s;
    s = "A man, a plan, a canal: Panama";

    Solution sol;
    cout << sol.isPalindrome(s) << endl;

    return 0;
}