struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

#include <set>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    bool hasCycle(ListNode* head) {

        /**
            This solution uses a set to store the addresses of the nodes in the linked list that have already been visited
            At each node, we check the set to see if the address of the current node is in the set
            If it is, this means that we have already visited this node, and therefore there is a cycle in the linked list
            If it is not, we add the address of the current node to the set and continue to the next node
            If we reach the end of the linked list without finding a cycle, the 'cycle' boolean will remain false and we return false
            Time complexity: O(n), Space complexity: O(n)

            This is good, but there is a better solution with Time complexity: O(n) and Space complexity: O(1)
            This solution uses fast and slow pointers to detect a cycle in the linked list
         */

        std::set<ListNode*> addressSet;

        bool cycle =  false;
        ListNode* currNodePtr = head;

        while (!cycle && currNodePtr!=nullptr){
            if ( addressSet.find(currNodePtr) != addressSet.end() ){
                cycle = true;
            } else {
                addressSet.insert(currNodePtr);
                currNodePtr = currNodePtr -> next;
            }
        }   
    
        return cycle;
    }
};


class Solution {
public:
    bool hasCycle(ListNode* head) {
        /**
            https://www.youtube.com/watch?v=gBTe7lFR3vc
            As introduced above, this solution uses fast and slow pointers to detect a cycle in the linked list
            The slow pointer moves one step at a time, while the fast pointer moves two steps at a time
            If a cycle exists in the linked list, the fast pointer will get stuck in the cycle until the slow pointer eventually catches up to it and they land on the same node
            If there is no cycle, the fast pointer will reach the end of the linked list (i.e the nullptr) before the slow pointer at which point we return false
            Time complexity: O(n), Space complexity: O(1)
            This is the optimal solution for this problem

            Note that, prior to each iteration of the while loop, we check both the fast pointer and the fast pointer's next pointer and compare them to the nullptr
            
            This is important because if the fast pointer is the nullptr, we cannot access its next pointer, which would lead to a segmentation fault
            More importantly, by checking the fast pointer against nullptr, we cover the base case where the linked list is empty (i.e 'head' is nullptr) and we can return false immediately
            
            We also check to see if the fast pointer's next pointer the nullptr
            This is important because, if the fast pointer's next pointer is the nullptr, it means that, if we proceed to the next iteration, the fast pointer will reach the end of the linked list (signalling that there is no cycle)
            Therefore, we can break the loop and return false in this case as well
            
            Note that, by checking if the fast pointer's next pointer the nullptr, we can always guarantee that 'fastPtr' will never be set to the nullptr (unless the linked list is initially empty (i.e 'head' is nullptr))
            That is, (unless the linked list is initially empty) 'fastPtr' will NEVER be set to the nullptr as we always check, before stepping, whether the next fast pointer will result in a nullptr
            If it does result in a nullptr, we break the loop and return false immediately - without advancing 'fastPtr' to that nullptr
            Thus, I want to emphasize again that the 'fastPtr != nullptr' check is ONLY necessary to check the base case where the linked list is empty (i.e 'head' is nullptr)...
            This check is redundant in any other case as, in all other cases, fastPtr will NEVER actually be set to the nullptr - we will break out of the loop if we calculate that this will end up happening

        */

        ListNode* slowPtr = head;
        ListNode* fastPtr = head;

        bool cycle = false;

        while ( !cycle && fastPtr != nullptr && fastPtr->next != nullptr){

            slowPtr = (slowPtr->next);
            fastPtr = (fastPtr->next)->next;

            if (slowPtr == fastPtr){
                cycle = true;
            }
        }
        return cycle;
    }
};