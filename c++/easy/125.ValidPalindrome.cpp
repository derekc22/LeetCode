#include <iostream>
#include <cctype>
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