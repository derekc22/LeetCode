#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout, std::endl;

class Solution {
public:
    string longestPalindrome(string s) {


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

            cout << "___________________" << endl;
            cout << "primary" << endl;

            while ( flag ) {    

                flag = false;
    
                if ( iOdd >= 0 && jOdd < s.length() ){
                    char slOdd = s[iOdd];
                    char srOdd = s[jOdd];
                    // cout << "odd: " << iOdd << ", " << jOdd << endl;
                    // cout << slOdd << ", " << srOdd << endl;
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
                    cout << "even: " << iEven << ", " << jEven << endl;
                    cout << slEven << ", " << srEven << endl;
                    if (slEven == srEven){
                        flag = true;
                        nEven+=2;
                        iEven--;
                        jEven++;
                        cout << "nEven: " << nEven << endl;
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

        cout << pI << ", " << pJ << endl;
        palindrome.clear();
        for ( int r=pI+1; r<=pJ-1; r++ ){
            cout << "yo" << endl;
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