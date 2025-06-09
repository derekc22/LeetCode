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
            In the first solution (above), we simply replace found words with an empty string until no more words can be found
            In the second solution (above), we fill a boolean array with 1s for the positions of the found words and then check if the sum of the array equals the length of the string
            Solution 1 fails for Test 4, where the string "cars" can be segmented into "ca" and "rs", as the greedy approach does not consider this combination as it finds "car" first and immediately removes it, leaving "s" which cannot be segmented further
            This approach is "greedy" as it trie to find and remove words from the string as quickly as possible without considering all possible combinations
            Solution 2 fails for Test 5, where the string "catsandog" can NOT be segmented using the words in the dictionary, as even though the string "catsandog" contains the words "cats", "dog", "sand", "and", "cat", the string cannot be segmented (mutually exclusively) into these words
            This approach fails to identify this because, unlike the first solution which removes words from the string, ensuring that only mutually exclusive segments are considered, this approach leaves the string intact, making it possible to count segments that are not mutually exclusive

            https://www.youtube.com/watch?v=hK6Git1o42c
            The optimal solution is to use a dynamic programming approach, where a boolean array is used to keep track of whether the string can be segmented up to each index
            Each index in the boolean array represents whether the substring from the start of the string to that index can be segmented into words from the dictionary
            Its too complex to explain here, but the video above does a good job of explaining it
            Two key differences from the video and my approach are:

            1) The video uses a boolean array of size s.length() + 1, while I use a boolean array of size s.length()
            According th ChatGPT, my approach is still valid and achieves the same result as the video:
            " Your implementation works without the extra DP element because it manually accounts for the empty prefix
              Normally, dp[0] = true represents that the empty string can be segmented
              You replace that logic by checking if checkLen < 0
              When a word in the dictionary matches the beginning of the string, checkLen becomes negative
              Instead of needing dp[0] to confirm a valid start, you just allow it if the match starts at index 0 (i.e. if checkLen < 0) 
              This achieves the same effect as having dp[0] = true. Your DP array starts from the first character rather than before it
              The logic is baked into your conditionals rather than stored in an extra cell. This saves space but requires more careful checks
              Functionally, it mirrors the traditional setup using slightly different mechanics 
            "

            2) Although this doesn't seem to be explicitly mentioned in the video...
            Whenever a substring is found in the dictionary (meaning that that word can be used to segment that part of the string), the algorithm MUST check if the remaining substring in the string can ALSO be segmented, which is done by checking the dp array at the index just before the found word's starting index in the string
            The guy introduces this concept at 12:34 (https://youtu.be/hK6Git1o42c?t=754) for the very last element in the dp array, but it is actually a key part of the algorithm that must be applied to all substrings that are found in the dictionary
            The only exception is for substrings that start at the beginning of the string, as there is no previous substring to check
            THis particular logic is handled by the line 'if ( checkLen < 0 || ( checkLen >= 0 && dp[checkLen] ) )' in the code below
            The variable 'checkLen' is defined as the current index (i) minus the length of the current found substring (currSubstr.length())
            This gives the ending index of the previous substring just prior to the current found substring
            The if statement then checks if 'checkLen' is less than 0 (checkLen < 0)
            If so, this means that the current found substring starts at the beginning of the string. Thus, there is no previous substring to check in this case, so it simply proceeds without doing a dp array check
            Note that this is the exact logic that the video uses an extra element in the dp array to handle
            Anyway, if, alternatively, the index of the previous substring is greater than or equal to 0 (meaning that the current found substring does NOT start at the beginning of the string, ie there DOES exist a substring before it), the algorithm then checks if that previous substring is, itself, segmentable (by checking the cached/memoized value of dp[checkLen])

        */


        vector<bool> dp(s.length());
        
        auto max_it = std::max_element(wordDict.begin(), wordDict.end(),
                    [](const string& a, const string& b){
                        return a.length() < b.length();
                    });

        int maxLen;
        if (max_it != wordDict.end()){
            maxLen = static_cast<int>((*max_it).length());
        }

        int checkLen;

        string c;

        for (int i=0; i < s.length(); i++){
            string currSubstr;
            
            string currRange = s.substr(0, i+1);
            auto rit = currRange.rbegin();
            auto rend = (i > maxLen) ? (rit + maxLen) : currRange.rend()-1;

            for (; rit <= rend; rit++){
                c = *rit;
                currSubstr.insert(0, c);

                auto foundIt = std::find(wordDict.begin(), wordDict.end(), currSubstr);

                if ( foundIt != wordDict.end() ){ 
                    checkLen = i - static_cast<int>(currSubstr.length());
                    if ( checkLen < 0 || ( checkLen >= 0 && dp[checkLen] ) ){
                        dp[i] = true;
                        break;
                    }
                }
            }
            currSubstr.clear();
        }
        return dp.back();
    }
};








int main(){

    Solution sol;

    string s;
    vector<string> wordDict;

    // Test 1 (answer = true)
    s = "bb";
    wordDict = {"a","b","bbb","bbbb"};

    // Test 2 (answer = true)
    // s = "applepenapple";
    // wordDict = {"apple","pen"};

    // // Test 3 (answer = true)
    // s = "leetcode";
    // wordDict = {"leet","code"};


    // Test 4 (answer = true)
    // s = "cars";
    // wordDict = {"car","ca","rs"};

    // Test 5 (answer = false)
    // s = "catsandog";
    // wordDict = {"cats","dog","sand","and","cat"};

    // Test 6 (answer = true)
    // s = "goalspecial";
    // wordDict = {"go","goal","goals","special"};

    cout << sol.wordBreak(s, wordDict) << endl;


    return 0;
}