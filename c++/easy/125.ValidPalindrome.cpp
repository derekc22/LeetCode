#include <iostream>
using std::string, std::cout, std::endl;

class Solution {
public:
    bool isPalindrome(string s) {
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
                right--;
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