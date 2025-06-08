#include <iostream>
#include <string>


using std::string;
using std::cout, std::endl;

class Solution {
public:
    int countSubstrings(string s) {

        /**
            This is literally just '5-LongestPalindromicSubstring.cpp' but instead of returning the longest palindromic substring, we return the number of palindromic substrings
            We do this by simply incrementing a counter every time we find a palindromic substring (which occurs every time the left and right bounds of the current substring match)
            See '5-LongestPalindromicSubstring.cpp' for more information
         */


        int iOdd; // left bound
        int jOdd; // right bound
        int iEven; // left bound
        int jEven; // right bound
        int nPalindromes = s.length();
        bool flag;

        int pI;
        int pJ;
        
        for (int q = 0; q < s.length(); q++){

            flag = true;

            int iOdd = q-1;
            int jOdd = q+1;
            int iEven = q;
            int jEven = q+1;


            while ( flag ) {    

                flag = false;
    
                if ( iOdd >= 0 && jOdd < s.length() ){
                    char slOdd = s[iOdd];
                    char srOdd = s[jOdd];
                    if (slOdd == srOdd){
                        flag = true;
                        iOdd--;
                        jOdd++;
                        nPalindromes++;
                    } 
                }

                if ( iEven >= 0 && jEven < s.length() ){
                    char slEven = s[iEven];
                    char srEven = s[jEven];
                    if (slEven == srEven){
                        flag = true;
                        iEven--;
                        jEven++;
                        nPalindromes++;

                    } 
                }
            }
        }

        return nPalindromes;
        
    }
};



