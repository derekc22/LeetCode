/*
#include <iostream>
#include <vector>
#include <string>
using std::string, std::vector, std::cout, std::endl;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {

        if (s.empty()){return false;}

        bool canBeSegmented = false;
        int pos;

        for (string word : wordDict){

            pos = s.find(word);

            if (pos != string::npos){
                while (pos != string::npos){
                    s.replace(pos, word.length(), "");
                    pos = s.find(word);
                }
            }
        }

        if (s.empty()){
            canBeSegmented = true;
        }

        return canBeSegmented;
        
    }
};
*/


/*
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using std::string, std::vector, std::cout, std::endl;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {

        if (s.empty()){return false;}

        bool canBeSegmented = false;
        int pos;
        vector<int> boolArr(s.length());

        for (string word : wordDict){

            pos = s.find(word);

            if (pos != string::npos){
                while (pos != string::npos){
                    std::fill(boolArr.begin() + pos, boolArr.begin() + pos + word.length(), 1);
                    pos = s.find(word, pos+1);
                }
            }
        }

        int sum = std::accumulate(boolArr.begin(), boolArr.end(), 0);
        cout << sum << endl;
        if (sum == s.length()){
            canBeSegmented = true;
        }

        return canBeSegmented; 
    }
};
*/





#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using std::string, std::vector, std::cout, std::endl;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {

        /**
            In the first solution, we simply replace found words with an empty string until no more words can be found
            In the second solution, we fill a boolean array with 1s for the positions of the found words and then check if the sum of the array equals the length of the string
            Solution 1 fails for Test 4, where the string "cars" can be segmented into "ca" and "rs", as the greedy approach does not consider this combination as it finds "car" first and immediately removes it, leaving "s" which cannot be segmented further
            This approach is "greedy" as it trie to find and remove words from the string as quickly as possible without considering all possible combinations
            Solution 2 fails for Test 5, where the string "catsandog" can NOT be segmented using the words in the dictionary, as even though the string "catsandog" contains the words "cats", "dog", "sand", "and", "cat", the string cannot be segmented (mutually exclusively) into these words
            This approach fails to identify this because, unlike the first solution which removes words from the string, ensuring that only mutually exclusive segments are considered, this approach leaves the string intact, making it possible to count segments that are not mutually exclusive

            The optimal solution is to use a dynamic programming approach, where a boolean array is used to keep track of whether the string can be segmented up to each index
            Each index in the boolean array represents whether the substring from the start of the string to that index can be segmented into words from the dictionary
        */

        // cout << s.length()+1 << endl;
        vector<bool> dp(s.length()+1);
        dp[0] = true;
        
        bool firstFound = true;

        auto max_it = std::max_element(wordDict.begin(), wordDict.end(),
                    [](const string& a, const string& b){
                        return a.length() < b.length();
                    });

        int maxLen;
        if (max_it != wordDict.end()){
            maxLen = (*max_it).length();
        }

        string c;

        for (int i=1; i <= s.length(); i++){
            string currSubstr;
            
            string currRange = s.substr(0, i);
            // cout << i << ", " << currRange << endl;
            auto rit = currRange.rbegin();
            auto rend = (i > maxLen) ? (rit + maxLen) : currRange.rend()-1;
            // cout << i << ", srt ptr: " << *(rit) << endl;
            // cout << i << ", end ptr: " << *(rend) << endl;

            for (; rit <= rend; rit++){
                // cout << i <<  ", boi" << endl;

                c = *rit;
                currSubstr.insert(0, c);
                // cout << i << ", substr: " << currSubstr << endl;

                auto foundIt = std::find(wordDict.begin(), wordDict.end(), currSubstr);
                if ( foundIt != wordDict.end() ){ //&& dp[i-1] == true ){
                    // cout<< "Found: " << currSubstr << endl;
                    if ( firstFound || dp[i-1] ){
                        firstFound = false;
                        dp[i] = true;
                        // cout <<  "yo: " << i << endl;
                        break;
                    }
                }

            }
            currSubstr.clear();
        }

        // cout << endl;
        // for (bool b : dp){
        //     cout << b << "";
        // }
        // cout << endl;

        return dp.back();

    }
};




int main(){

    Solution sol;

    string s;
    vector<string> wordDict;

    // Test 1
    // s = "bb";
    // wordDict = {"a","b","bbb","bbbb"};

    // Test 2
    // s = "applepenapple";
    // wordDict = {"apple","pen"};

    // Test 3
    // s = "leetcode";
    // wordDict = {"leet","code"};


    // Test 4
    // s = "cars";
    // wordDict = {"car","ca","rs"};

    // Test 5
    s = "catsandog";
    wordDict = {"cats","dog","sand","and","cat"};


    cout << sol.wordBreak(s, wordDict) << endl;


    return 0;
}