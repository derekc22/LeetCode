#include <iostream>
#include <vector>

using std::vector;

/*
class Solution {
public:
    int maxProfit(vector<int>& prices) {

    /**
        Uses a two-pointer approach
        
        Whereas most two-pointer problems that we've covered thus far involve the two pointers starting at opposite ends of the array, this problem shows that this need not always be the case
        It is quite similar to '11-ContainerWithMostWater.cpp' in that we need to satisfy a 'max' criteria using two elements in the array
        In '11-ContainerWithMostWater.cpp', we explicitly state that
        "The general criteria for a question to fit the two-pointer approach is:
        The problem involves finding two or more elements in a sorted or unsorted array that (when combined in some way) meets a certain condition"
        This criteria quite closely matches the problem description

        In '11-ContainerWithMostWater.cpp' we initialize the pointers at opposite ends of the array, although I believe that we could start with them next to each other as we do here
        By contrast, in '121-BestTimeToBuyAndSellStock.cpp', I believe we have no choice but to start the pointers adjacent to one another at the beginning of the array
        Let us see why by considering the case where we initialize buy = prices.begin() and sell = prices.end()-1
        Now, if *buy > *sell like in example 1 (prices = {7, 1, 5, 3, 6, 4}), our code will first calculate a negative spread, resulting in maxMoney = 0 
        Then, our code will perform the comparison (*buy > *sell) which will trigger buy = sell;
        Since 'buy' must ALWAYS be left of 'sell' (you can ONLY sell after you buy), we will be stuck because buy has already skipped to the last day (prices.end()-1)

        Thus, our code will be useless
        Again, the core mechanics that cause this are the that facts that (a) 'buy' must ALWAYS be left of 'sell' and (b) 'buy' SKIPS to 'sell' whenever (*buy > *sell) is detected
        The result is that the algorithm will be prematurely halted if our pointers are not properly initialized adjacently at the start of the array

        But why do we even have this mechanism?
        It's because, this mechanism guarantees that, at any given time, our current buy price is guaranteed to be the lowest that we have traversed thus far
        Recall, our buy price only moves if a negative spread is detected. In other words, our buy price will only ever move if we detect that there is a price lower than our current buy price
        If it helps understanding, replace the word 'sell' with 'curr' (as in 'curr' price today) and this should make some more sense (if it doesn't already)
        
        This ties into why we can't place 'sell' at the end - our algorithm just works too well
        Again, in example 1 where *buy > *sell, prices = {7, 1, 5, 3, 6, 4}, placing 'sell' at $4 initially will cause 'buy' to jump to $4 as well
        And, technically, this mechanism is doing EXACTLY its job - by jumping, it's guaranteeing that our current buy price is the lowest THAT WE HAVE TRAVERSED THUS FAR (i.e 4)
        The shortcoming thus comes from the fact that, because we did not start with 'sell' at the beginning, we fail to traverse any of the other more optimal solutions that come earlier in the array

        Sidenote: There is no backtracking allowed in this problem because, as we've said multiple times, 'buy' must ALWAYS be left of 'sell'
        Thus, when our algorithm skips to the lowest 'buy' price, we do not need to concern ourselves with the now inaccessible 'sell' prices that are now in the past (i.e. to the left of the current 'buy' price)
        Again, this is because we cant go back into the past to sell
                                     b  s
                                     v  v
        For example, in prices = {7, 1, 5, 3, 6, 4}, our algorithm quickly finds the global minimum buy price of $1
        Now, although it would be nice to go back into the past and sell at $7 instead of $5, we obviously cant do this because that would require going into the past to sell before we buy
        The point is, once the 'buy' pointer is moved, we DO NOT have have to check any of the combinations that are now in the past

        Time Complexity: O(n)
        We iterate through n-1 prices

        Space Complexity: O(1)
        No data structures are required
    *

        if (prices.size() == 1) return 0; // If there's only 1 day, return 0

        auto buy = prices.begin();
        auto sell = prices.begin()+1;
        int maxMoney = 0;
        int spread;

        while (sell != prices.end()){
            spread = *sell - *buy;
            if (spread > maxMoney) maxMoney = spread;
            if (spread < 0) buy = sell;
            // If a negative spread is detected (i.e. we detect that there is a future price that is lower than our current buy price)...
            // We jump to that buy price

            sell++;
        }

        return maxMoney;
    }
};
*/


#include <vector>
#include <algorithm>

class Solution {
public:
    int maxProfit(const std::vector<int>& prices) {
        
        /**
            Uses a ? approach

            Although the above two-pointer approach does work, this is conceptually simpler despite using the same core mechanism
            That core mechanism is that we always store and use the best found 'buy' price
            The only difference is that, before, we cached this minimum seen price by jumping/skipping the 'buy' pointer
            But here, we simply cache the minimum seen price in an independent variable
            Otherwise, the mechanisms are essentially identical

            The simplicity of this solution over the prior one is that, in the prior solution, we had to be very careful where to place our two pointers
            By contrast, here, it is INTUITIVE that we begin our traversal at prices[1], 'for (int i = 1; i < prices.size(); i++)'
            With this method, IT DOES NOT EVEN CROSS OUR MIND to begin the for loop at the end and iterate backwards, 'for (int i = prices.size()-1; i >= 0; i--)'
            This type of setup would be ridiculous to even conceptualize given the for loop approach!

            However, because it is STANDARD in two-pointer problems to initialize the pointers at opposite ends of the array...
            If we don't think critically about pointer placement, we risk mindlessly doing this and falling into the trap that is thoroughly discussed in the prior solution

            Thus, because the below approach absolves us of having to do all of that extra thinking, this solution may be better
            Keep in mind, though, that this solution does not really fall into any of the established patterns (that I have learned thus far)
            Thus, the two-pointer approach, while conceptually harder to implement, may still come to you first since if fits into one of the patterns (that I have learned thus far) more cleanly

            Time Complexity: O(n)
            We iterate through n-1 prices

            Space Complexity: O(1)
            No data structures are required

         */

        if (prices.size() < 2) return 0;

        int maxMoney = 0;
        int spread = 0;
        int minPrice = prices[0];

        for (int i = 1; i < prices.size(); i++){
            int price = prices[i];
            spread = price - minPrice;
            if (spread > maxMoney) maxMoney = spread;
            if (spread < 0) minPrice = price;
            // If a negative spread is detected (i.e. we detect that there is a future price that is lower than our current buy price)...
            // We cache that buy price
        }

        return maxMoney;
    }
};



int main(){

    Solution sol;

    vector<int> prices = {7, 1, 5, 3, 6, 4};
    std::cout << sol.maxProfit(prices) << std::endl;


    return 0;
}