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
    
    bool isPalindrome(string s) {

        /** 
         * This algorithm checks if a given string is a palindrome
         * This is a classic two-pointer problem as the structure of a palindrome is such that the first and last characters must match, no matter how many characters are in between
         * Thus, if any pair of characters at the two pointers do not match, the string is automatically not a palindrome 
        */
    

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
};


int main(){

    string s;
    s = "aabca";

    Solution sol;
    cout << sol.isPalindrome(s) << endl;

    return 0;
}