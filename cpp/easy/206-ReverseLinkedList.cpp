/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode* next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

/**
class Solution {
public:
        /**
            Uses a recursive approach
            To use recursion for a data structure, follow this flow chart
            Step 1: Identify whether or not the data structure contains a sub-structures that, when applied recursively, result in the macro structure being generated
                    Unlike a binary tree, a linked list does not have an obvious branching or places to 'place the cut'
                    In a binary tree, its natural - a head and two children. Thus, we can cleanly place a cut below the two children and call that 3-node structure the sub-structure
                    Of course, we could technically place the cut anywhere in the binary tree to form sub-structures of various sizes (1 node, 3 nodes, 7 nodes, etc), but the natural choice is to place the cut just below the children of the root node

                    However, in a linked list, do we place the cut after the first node? After the second node? After the third node? 
                    The answer is less clear, so we simply choose the most straightforward approach: placing the cut after the head node
                    Thus, the linked list substructure can be viewed as a head node pointing to a sub-list (the rest of the linked list)
                    Thus, that head + sub-list structure is the sub-structure
            
            Step 2: If yes, identify that sub-structure and describe the fundamental operation that needs to be performed in order to solve the problem ON THAT SUB-STRUCTURE (ie, don't concern yourself with thinking about the macro structure yet)
                    In this case, fundamentally, to reverse a linked list substructure, we need to do the following three things:
                    We will use the following linked list as an example: head -> A -> B -> C
                    1. Reverse the sub-list (the rest of the linked list after head):                              (C -> B -> A)
                    2. Whatever node head was originally pointing at, point that node at head:                     (A -> head)
                    3. Point head to nullptr:                                                                      (head -> nullptr)
                    Thus, the resulting reversed linked list is:                                                   C -> B -> A -> head -> nullptr

                    In code:
                    reverseList(head){
                        ListNode* newHead = reverseList(head->next); // reverse the rest
                        head->next->next = head;                     // whatever node head was originally pointing at, point that node at head
                        head->next = nullptr;                        // point head to nullptr 
                    }

            Step 3: Break down the pseudocode for the sub-structure operation into 'question' and 'answer' parts
                    In this case, the 'question' is:
                        Upon reversal, what is the new head of the linked list? 
                    The 'answer' is:
                        The new head is the reversed sub-list
                        Abstractly, we can think of this reversed sub-list as a compound node, (C -> B -> A), that functions as a single node
                        This compound node is what we will treat as the 'new head' of the reversed linked list
                        The LeetCode problem explicitly asks us to return the new head of the reversed linked list, hence why we store it in a variable named newHead
                        What we do with this newHead variable is determined in Step 6


            Step 4: Analyze the functions's argument(s) and return type
            Once the fundamental sub-structure operation is identified, it will need to be applied recursively, such that each call to the function returns the answer to the prior call
            This means that the return statement in our function MUST return the answer to the prior call
            Now, in LeetCode problems, the function signature is often pre-defined, so we must work within that constraint
            However, this actually acts as a GREAT HINT, telling us BOTH what the return type should be AND what the argument type should be
                    In this case, the function's argument is a ListNode* and return type is a ListNode*
            
            Step 5: Realize that in a recursive approach, the answers to those questions should be obtained by making recursive calls. 

                    In our above pseudocode, we have already done this:
                        ListNode* newHead = reverseList(head->next); // reverse the rest

                    Notice how none of our rules were broken:
                    1. The function call is still being passed a ListNode* (head->next is a ListNode*)
                    2. The function return is still being stored in a ListNode* (the return value of reverseList(...) is a ListNode*)
                    3. The answers to the questions are now set up to be returned by recursive calls. However, it is YOUR JOB to engineer that the recursive calls to return the correct answers to the questions

            Step 6: Engineer the function such that the recursive calls actually return the correct answers to the questions
            This is the trickiest part, and it often requires you to think about three things: the base case(s), the return statement, and the order of operations
            
                Step 6.1, Base Case(s): In a recursive function, you must always have base case(s) that stop the recursion from continuing infinitely
                Typically, the base case is placed at the top of the function, allowing the function to exit before any subsequent operations are performed
                Moreover, the return type of the base case(s) MUST ABSOLUTELY match the function's return type, just like any other return statement in the function
                
                As a rule of thumb, ask yourself:
                What is the last possible node in the data structure that is capable of providing a valid answer to the question asked by the prior node
                If a node cannot provide a valid answer to the prior node's question, it cannot be the terminal node for the base case
                Once identified, ensure that, upon reaching that terminal node, the function (a) stops recursing further and (b) returns the correct answer to the penultimate node's question
                Note: The terminal node may (inverting a binary tree) or may not (reversing a linked list) be the nullptr node

                    Now, the base case in this problem is more complex than in inverting a binary tree
                    In a binary tree, the terminal nodes ARE the nullptr node children of the leaf nodes
                    Ex: The terminal node asks the question, "what is my new left child?" - in which case we can simply return nullptr as this would indeed correctly answer the question

                    However, in a linked list, our terminal node CANNOT be the nullptr node
                    Why? Take the linked list: head -> A -> B -> C -> nullptr 
                    The nullptr node cannot answer the question being asked by node C
                    Node C asks the question, "what is the new head of the reversed linked list?"
                    In order to answer that question, the nullptr node would have to return a reversed sub-list - but the nullptr node cannot do that as THERE IS NO subsequent sub-list after nullptr to reverse
                    Thus, it is incapable of providing a valid answer to node C's question
                    If that's confusing, think of it this way: you CAN reverse an list of length 1, but you CANNOT technically reverse an list of length 0 (ie, nullptr)

                    Instead, the base case must terminate at the last actual node in the linked list (node C), NOT at a nullptr node (like we did in the binary tree problem)
                    If our recursion terminates here, the penultimate node expects an answer to the question, "what is the new head of the reversed linked list?"
                    The correct answer is the terminal node itself, as when you reverse a linked list, the terminal node indeed becomes the head of the reversed linked list
                    Thus, our base case check looks like this:
                        if (!head->next) return head;
                    
                    However, we must also consider the edge case where the linked list is empty (ie, head == nullptr)
                    In this case, there are no nodes in the linked list
                    Thus, there is nothing to reverse, so we can simply return nullptr
                    This is more of an edge case than a true base case, but it must still be handled
                    Handling this edge case might look like this:
                        if (!head) return nullptr;

                    However, if you look closely, you'll see that both base cases can be combined into a single check
                    The base case clearly returns head while the edge case is technically also returning head (as head is nullptr in that case)
                    Thus, our combined base case looks like this:
                        if (!head || !head->next) return head;

                Step 6.2, Return Statement: In a recursive function, as we've already established, it is YOUR JOB to ensure that the function returns the correct answer to the prior call 
                This is done via a return statement at the end of the function
                In fact, the return statement cannot be placed anywhere else as, otherwise, any code after the return statement would be unreachable
                This provides a critical hint as, now, your only job is to engineer what the return statement should return, not where to place it

                    Thus, our pseudo-function now looks like this:
                        reverseList(head){
                            if (!head || !head->next) return head;

                            ListNode* newHead = reverseList(head->next);
                            head->next->next = head;
                            head->next = nullptr;
                            return ???;
                        }

                Now, what should we return? To determine this, we must think about what the prior call expects to receive as the answer to its question
                This is most easily determined by applying the function to the sub-structure identified in Step 1
                Moreover, it is important to understand that the first time in the call stack that this return statement is ever reached is IMMEDIATELY AFTER the base case is hit
                Thus, if there are a total of n calls in the call stack, the base case is hit in callstack(n), and the first time this return statement is reached is in callstack(n-1)
                That is, this return statement is first reached in callstack(n-1), and must return the correct answer to callstack(n-2)

                    Consider a simple 3-node linked list:
                        head -> A -> B
                    Reversed, this becomes:
                        B -> A -> head

                    The call stack looks like this, with n=2:
                    callstack(n=0):
                        reverseList(head)
                    callstack(n=1): 
                        reverseList(head->next)  // head->next = A
                    callstack(n=2):
                        reverseList(A->next)     // A->next = B

                    We have already established that reverseList(A->next = B) hits the base case and returns B as the answer to head=A's question, "what is the new head of the reversed linked list?"
                    
                    Now, we must determine what reverseList(head->next = A) should return as the answer to head's question, "what is the new head of the reversed linked list?"
                    Well, the whole point of the recursive approach is that, by the time we reach the base case, we will have found the the answer to that question
                    That is, the new head of the reversed linked list is B, which we found when we reached the base case and was returned to the reverseList(head->next = A) call in the form of the variable newHead
                    Thus, reverseList(head->next = A) should return newHead as the answer to head's question, "what is the new head of the reversed linked list?"

                    Thus, our completed pseudo-function now looks like this:
                        reverseList(head){
                            if (!head || !head->next) return head;

                            ListNode* newHead = reverseList(head->next);
                            head->next->next = head;
                            head->next = nullptr;
                            return newHead;
                        }

                Step 6.3, Order of Operations: In some recursive problems, the order in which operations are performed matters
                    In this problem, the order DEEPLY matters
                    If we placed ListNode* newHead = reverseList(head->next); after the two lines that manipulate the pointers, we would essentially be corrupting the sub-list before we have a chance to reverse it
                    Thus, it is CRITICAL that we first make the recursive call to reverse the sub-list, and only AFTER that do we manipulate the pointers to append head to the end of the reversed sub-list
            

            Time Complexity: O(n)
            We must visit each node in the linked list exactly once to reverse the linked list

            Space Complexity: O(n)
            Each recursive call adds a new layer to the call stack
            Thus, the space complexity is O(n) due to the call stack
         /

    ListNode* reverseList(ListNode* head) {

        if (!head || !head->next) return head;          // base case

        ListNode* newHead = reverseList(head->next);     // reverse the rest
        head->next->next = head;                         // put head at the end
        head->next = nullptr;                            // break the old link
        return newHead;
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
    ListNode* reverseList(ListNode* head) {

    /**
        Uses a iterative approach

        This was my first attempt at the problem using an iterative approach
        
        My first approach involved trying to do everything at once
        For each node, I tried to switch both the pointers:
            right->next = curr;
            curr->next = left;
        This would be more complex to implement, so I settled for a simpler approach 

        My new approach simply points the current node to the left node, curr->next = left;
        This is in contrast to my initial approach, which simultaneously tried to point the right node to the current node and the current node to the left node

        To implement this, we use three pointers:
        left - points to the left node
        curr - points to the current node
        right - points to the right node

        Note: I initially named these pointers prev, curr, and next, respectively
        However, I struggled to understand the logic with this naming scheme
        After renaming them to left, curr, and right, I found it INSTANTLY easier to understand the logic
        It was literally magical how much easier it was to understand the logic just by renaming the variables - I'm not even exaggerating
        This goes to show how important variable naming is in programming - good variable names can make code much easier to understand
        Thus, whenever solving linked list problems, use left, curr, and right as your pointer variable names

        In our main loop, we do the following:
        1. Store the right node: right = curr->next;
        We do this because we are about to rewire curr->next to point to the left node 
        Thus, we must first store the original right node so we know which node to jump to in the next iteration

        2. Point the current node to the left node: curr->next = left;
        This is the core operation that reverses the linked list
        By making the current node point to the left node, we are effectively reversing the direction of the link between these two nodes

        3. Increment the left and curr pointers
            left = curr;
            curr = right;
        This simply advances our pointers, moving us down the linked list
        We continue this process until curr is nullptr, meaning that the node to the left of curr was the final node in the original linked list
        Thus, at this point, we can simply return left, as the final node in a linked list is always the head of the reversed linked list

        Some housekeeping notes:
        We initialize left to nullptr, as the curr = head will need to point to the nullptr in the first iteration
        Moreover, if the linked list is empty (ie, curr = head, where head = nullptr), the while loop is never entered, and we simply return left.
        Thus, left better be equal to nullptr at the start for this edge case to be handled correctly

        And that's it! Much simpler than the recursive approach (at least once the variable names were changed)
        

        Time Complexity: O(n)
        We iterate through all n nodes

        Space Complexity: O(1)
        We only use a constant amount of extra space for the three pointers
        Notice how this is better than the recursive approach, which has O(n) space complexity due to the call stack

     */

        ListNode* left = nullptr;       
        ListNode* curr = head;          
        ListNode* right;

        while (curr != nullptr){

            right = curr->next; // store the right node

            curr->next = left; // core operation - point curr to left

            // increment pointers
            left = curr;
            curr = right;
        }

        return left;
    }
};







int main(){
    ListNode n5(5);
    ListNode n4(4, &n5);
    ListNode n3(3, &n4);
    ListNode n2(2, &n3);
    ListNode n1(1, &n2);

    Solution sol;
    sol.reverseList(&n1);

    return 0;
}