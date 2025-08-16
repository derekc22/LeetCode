/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

/*
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

        /**
            Uses a two-pointer approach

            This was my first attempt at solving 21-MergeTwoSortedLists using a two-pointer approach

            The core mechanism is to use two pointers, curr1 and curr2, to traverse the two linked lists
            At each step, we compare the values at curr1 and curr2

            Is curr1's value less than curr2's value?
                If yes, is curr2's value <= right1's value (curr1's right neighbor)?

                    If yes, we know that curr2 is the next smallest node in the merged linked list (greater than curr1, but less than or equal to right1)
                    Thus, curr1 should point to curr2, rather than continuing to point to right1
                    We thus advance curr1 to right1 so that in the next iteration, we can compare curr2 with the next node in list1

                        Note: sometimes right1 may be nullptr (ie, curr1 is at the end of list1)
                        In that case, attempting to check right1->val would be invalid, as right1 has no val member
                        Thus, we must first check if right1 is nullptr to avoid attempting to dereference a nullptr
                        Hence why we check 'if (!right1 || curr2->val <= right1->val)' rather than simply 'if (curr2->val <= right1->val)'
                        This reads: 'if right1 is nullptr' we can immediately proceed with curr1->curr2 (as there are no subsequent nodes in list1 to consider)
                        However, 'if right1 is not nullptr', we must check curr2's value against right1's value as normal

                    If no, we cannot yet point curr1 to curr2, as there may be smaller nodes in list1 that must come before curr2
                    In this case, we still advance curr1 to right1, so that that in the next iteration, we can compare curr2 with the next node in list1

                    Finally, the very first time we assign curr1->next = curr2, we must also store head = curr1
                    This is because we know that curr1 is the smallest node in the entire merged linked list

                    Finally, finally, we update the pointer called 'end' to point to the last node in the merged linked list so far
                    This is because, in the case where curr1->val == curr2->val, we need to know which of curr1 or curr2 was most recently added to the merged linked list
                    One of these nodes will be the last node of the merged linked list so far, while the 'other' node will still be attached to its original list
                    Thus, it is critical that we only point the 'end' node to the 'other' node, rather than the other way around
                    If we were to point the 'other' node to the 'end' node, we would now have two nodes in the merged linked list pointing to the end node (a) the true penultimate node in the merged linked list, and (b) the 'other' node that we just added
                    Anyway, once we safely point end->next = other, we then update end to point to the newly added node (as that node is now the last node in the merged linked list)


            If no, either curr2's value is less than curr1's value, or they are equal
            If curr2's value is less than curr1's value, we can apply the exact same logic as above, but with the roles of curr1 and curr2 swapped

            If curr1->val == curr2->val, we must determine which of curr1 or curr2 was most recently added to the merged linked list
            This is where the 'end' pointer comes in handy, as it always points to the last node in the merged linked list so far
            Thus, if end == curr1, we know that curr1 was most recently added to the merged linked list
            Therefore, we can safely point curr1->next = curr2
            Conversely, if end == curr2, we know that curr2 was most recently added to the merged linked list
            Therefore, we can safely point curr2->next = curr1


            Time Complexity: O(n + m) in the worst case
            The worst case occurs when the nodes in list1 and list2 are perfectly interleaved

            Space Complexity: O(1)
            No additional data structures are required


        /

        ListNode* curr1 = list1;
        ListNode* curr2 = list2;
        ListNode* right1;
        ListNode* right2;
        ListNode* head = nullptr;
        ListNode* end = curr1;

        if (!curr1) return curr2;
        if (!curr2) return curr1;


        while (curr1 && curr2){
            right1 = curr1->next; // Store curr1 right
            right2 = curr2->next; // Store curr2 right

            if (curr1->val < curr2->val){
                if (!right1 || curr2->val <= right1->val){
                    curr1->next = curr2; // Reassign curr1->next
                    end = curr2;
                }
                if (!head) head = curr1; // Store head
                curr1 = right1; // Advance curr1

            } else if (curr2->val < curr1->val) {
                if (!right2 || curr1->val <= right2->val){
                    curr2->next = curr1; // Reassign curr2->next
                    end = curr1; 
                }
                if (!head) head = curr2; // Store head
                curr2 = right2; // Advance curr2

            } else {

                if (curr1 == end){
                    curr1->next = curr2;
                    end = curr2;
                    if (!head) head = curr1; // Store head
                    curr1 = right1;

                } else if (curr2 == end) {
                    curr2->next = curr1;
                    end = curr1;
                    if (!head) head = curr2; // Store head
                    curr2 = right2;

                }
            }
        }
        return head;
    }
};
*/



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

        /**
            Uses an iterative approach
            Unlike my initial attempt, which is quite convoluted, and significantly more difficult to understand, this solution is much cleaner and easier to follow
            The core difference is that the prior solution was attemptted after solving '206-ReverseLinkedList', which explicitly involves manipulating the list nodes in-place using left, curr, and right pointers
            As a result, I was primed and in the mindset of using multiple pointers to solve this problem, despite that not being strictly necessary

            To be clear, 'in-place' manipulation refers to the fact that we are not creating any new nodes, but rather simply re-assigning the next pointers of existing nodes
            This is essentially like performing intricate pointer surgery, where you're splicing, sewing, and re-routing the connections between nodes, without the luxury of creating any new nodes to help facilitate the process
            In 206-ReverseLinkedList, this approach yields the optimal solution, as we must reverse the entire linked list in-place
            Now, it's one thing to attempt such pointer surgery when the task involves only a single linked list, but its an entirely different beast when trying to merge two, separately linked lists - hence the complexity of my initial solution

            In this refined solution, we ditch the intricate pointer manipulation and opt for a more straightforward 'out-of-place' approach that involves expliclty creating a new node to serve as the base of an entirely new (merged) linked list
            This is not only simpler, but also inherently 'out-of-place', as we are taking nodes from the two input lists and popping them onto a brand new header node
            
            The solution begins by instantiating a node called 'dummy' with a placeholder value
            This node serves as the faux head of the merged linked list, so we signify this by giving it a value of -99999, to exaggerate the fact the this node is (1) not part of the merged linked list, and (2) at the very front of the merged linked list (since the merged linked list is sorted)
            We also create a pointer called 'end' that points to dummy
            The purpose of 'end' is to always point to the last node in the merged linked list, so that when we want to add a new node to the merged linked list, we can simply do end->next = newNode (to append newNode to the end of the merged linked list) and then update end = newNode (to update end to point to the new last node in the merged linked list)
            Next, we create two pointers, curr1 and curr2, that point to the heads of list1 and list2 respectively
            These pointers will be used to traverse the two input linked lists, though note that they are not strictly necessary, as we could simply use list1 and list2 directly. I think using curr1 and curr2 improves code readability, so I opted to use them
    
            Similar to my initial solution, we then enter a while loop that continues as long as both curr1 and curr2 are not nullptr
            Inside the loop, we compare the values at curr1 and curr2, again, just like in my initial solution
            If curr1 <= curr2, we know that curr1 is the next smallest node to be added to the merged linked list
            Thus, we do end->next = curr1 to append curr1 to the merged linked list, just like we explained above
            We then update end = curr1 to update end to point to the new last node in the merged linked list, again, just like we explained above
            Finally, we advance curr1 = curr1->next such that in the next iteration, we are using the next node in list1 for comparison

            We follow the exact same logic if curr2 < curr1, but with the roles of curr1 and curr2 swapped

            Once we exit the while loop, it means that at least one of curr1 or curr2 is nullptr
            This means that we have fully traversed one of the input linked lists, but there may still be remaining nodes in the other linked list that need to be appended to the merged linked list
            Fortunately, since both input linked lists are sorted, and since all nodes in the merged linked list so far are less than or equal to all remaining nodes in the non-exhausted linked list, we can simply point end->next to the non-nullptr pointer (either curr1 or curr2)
            This effectively appends all remaining nodes from the non-exhausted linked list to the end of the merged linked list in one fell swoop (since those remaining nodes remain unchanged and are still linked together in their original order)

            Finally, we return dummy.next as the head of the merged linked list
            This is because dummy itself (with value -99999) is just the placeholder head node, while the actual head of the merged linked list was built starting from dummy->next
            And that's it!
            Overall, this solution is much cleaner and easier to understand than my initial attempt
            Again, this primarily stems from the fact, in my initial attempt, we tried to weave the two input linked lists together in-place using intricate pointer manipulation (as inspired by 206-ReverseLinkedList)
            Whereas in this refined solution, we simply build a new merged linked list from scratch using a dummy head node and straightforward pointer appends
            Moral of the story: be careful of blindly trying to apply solutions from prior problems without first considering simpler alternatives

            Time Complexity: O(n + m) in the worst case
            The worst case occurs when the nodes in list1 and list2 are perfectly interleaved

            Space Complexity: O(1)
            No additional data structures are required

        */

        ListNode dummy(-99999);
        ListNode* end = &dummy;
        ListNode* curr1 = list1;
        ListNode* curr2 = list2;

        while (curr1 && curr2) {
            if (curr1->val <= curr2->val) {
                end->next = curr1;
                end = curr1;
                curr1 = curr1->next;
            } else {
                end->next = curr2;
                end = curr2;
                curr2 = curr2->next;
            }
        }
        end->next = curr1 ? curr1 : curr2;
        return dummy.next;
        
    }
};



int main(){
    // ListNode x5(5);
    // ListNode x4(4, &x5);
    // ListNode x3(3, &x4);
    // ListNode x2(2, &x3);
    // ListNode x1(1, &x2);

    ListNode x1(10);

    ListNode y5(5);
    ListNode y4(4, &y5);
    ListNode y3(3, &y4);
    ListNode y2(2, &y3);
    ListNode y1(1, &y2);

    Solution sol;
    // cout << sol.mergeTwoLists(&x1, &y1) << endl;

    ListNode* mergedHead = sol.mergeTwoLists(&x1, &y1);
    while (mergedHead != nullptr){
        cout << mergedHead->val << " -> ";
        mergedHead = mergedHead->next;
    }
    cout << "nullptr" << endl;


    return 0;
}