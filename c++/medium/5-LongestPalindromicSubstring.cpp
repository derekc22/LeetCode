#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout, std::endl;

class Solution {
public:
    string longestPalindrome(string s) {

        /**
            https://chatgpt.com/c/683bd18b-f53c-8000-803d-b81bb1721e72
            https://chatgpt.com/share/68451ef1-fa4c-8000-ab0d-af6c384f19f2 <- public link

            This one really sucked to "solve"
            Anyway, the solution considers two types of palindromes:
            1. Odd-length palindromes, where the center is a single character
            2. Even-length palindromes, where the center is between two characters


            In the odd case, the left bound is the character before the center (q-1), and the right bound is the character after the center (q+1)
            In the even case, the left bound is the center character (q), and the right bound is the character after the center (q+1)
            The algorithm iterates through each character in the string, checking for odd and even palindromes centered on that qth character
            
            In the odd case, if the left and right bounds are equal, the bounds are expanded outwards (iOdd--, jOdd++) and the palindrome length is increased by 2 (since two new characters are added to the palindrome)
            In the even case, if the left and right bounds are equal, the bounds are expanded outwards (iEven--, jEven++) and the palindrome length is increased by 2 (since two new characters are added to the palindrome)

            The odd palindrome length is initialized with a value of 1, signifying the center character being a valid palindrome of length 1
            The even palindrome length is initialized with a value of 0, as the space between two characters is not a palindrome by itself

            The outward expansion of a given palindrome will continues until the bounds go out of range of the string
            If both palindromes go out of range, the 'flag' variable will remain false, and the while loop checking for palindromes centered on the qth character will end
            Note that, if only one of the palindromes goes out of range, both palindromes will continue being checked (however, only the one that is still in range will continue having its bounds expanded)
            This may be seen as inefficient, but I'm too lazy to optimize it further right now

            Once 'flag' is false, the algorithm checks which of the two palindromes is longer
            Then, the longest palindrome of the two is compared with the longest palindrome found overall so far
            If the current longest palindrome is longer than the previous longest palindrome, the indices of the left and right bounds of the current longest palindrome are saved
            Else, the indices of the previous longest palindrome are kept

            The algorithm then moves onto the next qth character in the string, repeating the process of checking for both odd and even palindromes centered on that qth character
            This continues until all characters in the string have been checked
            Voila!
        */


        int iOdd; // left bound
        int jOdd; // right bound
        int iEven; // left bound
        int jEven; // right bound
        int nOdd; // current palindrome length
        int nEven; // current palindrome length
        int longestN = 0; // longest palindrome length
        string palindrome = "";
        bool flag;

        int pI;
        int pJ;
        
        for (int q = 0; q < s.length(); q++){

            flag = true;
            
            nOdd = 1;
            nEven = 0;

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
                        nOdd+=2;
                        iOdd--;
                        jOdd++;
                    } 
                }

                if ( iEven >= 0 && jEven < s.length() ){
                    char slEven = s[iEven];
                    char srEven = s[jEven];

                    if (slEven == srEven){
                        flag = true;
                        nEven+=2;
                        iEven--;
                        jEven++;
                    } 
                }
            }
        
            int longer = std::max(nOdd, nEven);
            if (longer > longestN) {
                pI = (longer == nOdd) ? iOdd : iEven;
                pJ = (longer == nOdd) ? jOdd : jEven;
                longestN = longer;
            }
        }

        palindrome.clear();
        for ( int r=pI+1; r<=pJ-1; r++ ){
            palindrome.push_back(s[r]);
        }
        return palindrome;
        
    }
};



int main(){

    Solution sol;

    // string s = "ccc";
    // string s = "xbby";
    // string s = "aaaa";
    // string pal = sol.longestPalindrome(s);
    // cout << "longest palindrome: " << pal << endl;
    

    string ss[] = {"traxradarblin", "zupmadamdeifiedlox", "grindreferrotorsap", 
        "noobnooncivicdrop", "fleekpeepdeedbang", "laxstatsrevivertru", 
        "moklevelmadamspur", "vexttenetnoonplex", "glarddeedpeepmadamtox", 
        "zortredderrotorglim", "braxwowcivicstatslin", "jupdeifiedmoxklem", 
        "vulkreviverreferdeedquab", "nockmadamwowzonk", "cleepeepcivicnoontrak"};
    for (string s : ss){
        string pal = sol.longestPalindrome(s);
        cout << "longest palindrome " << pal << endl;
    }

    return 0;
}