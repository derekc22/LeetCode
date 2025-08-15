/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    /**
        Uses a recursive approach
        To use recursion for a data structure, follow this flow chart
        Step 1: Identify whether or not the data structure contains a sub-structures that, when applied recursively, result in the macro structure being generated
                In this case, each node with left and right children can be viewed as a mini binary tree itself
                Thus, that 3-node structure (parent, left child, right child) is the sub-structure
        
        Step 2: If yes, identify that sub-structure and describe the fundamental operation that needs to be performed in order to solve the problem ON THAT SUB-STRUCTURE (ie, don't concern yourself with thinking about the macro structure yet)
                In this case, fundamentally, to invert a 3-node binary tree, we simply need to swap the root's pointers to its left and right children
                That is, the root's left pointer should point to the right child, and the root's right pointer should point to the left child
                
                In code:
                invertTree(root){
                    TreeNode* temp = root->left;
                    root->left = root->right;
                    root->right = temp;
                }

        Step 3: Break down the pseudocode for the sub-structure operation into 'question' and 'answer' parts
                In this case, the 'questions' are:
                    1. Upon inversion, what is my new left child? root->left = ?
                    2. Upon inversion, what is my new right child? root->right = ?
                The 'answers' are:
                    1. The new left child is right child
                    2. The new right child is the left child


        Step 4: Analyze the functions's argument(s) and return type
        Once the fundamental sub-structure operation is identified, it will need to be applied recursively, such that each call to the function returns the answer to the prior call
        This means that the return statement in our function MUST return the answer to the prior call
        Now, in LeetCode problems, the function signature is often pre-defined, so we must work within that constraint
        However, this actually acts as a GREAT HINT, telling us BOTH what the return type should be AND what the argument type should be
                In this case, the function's argument is a TreeNode* and return type is a TreeNode*


        Step 5: Realize that in a recursive approach, the answers to those questions should be obtained by making recursive calls. 
                So, instead of
                    root->left = root->right;
                    root->right = temp;

                The solution might rhyme with:
                    root->left = invertTree(root->right);
                    root->right = invertTree(temp);

                Notice how none of our rules were broken:
                1. The function calls are still being passed a TreeNode* (root->right and temp are both TreeNode*)
                2. The function returns are still being stored in a TreeNode* (the return value of invertTree(...) is a TreeNode*)
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

                In tree problems, the base case is often when you reach a nullptr node (ie, you go off the tree)
                Thus, if the prior call passed in a nullptr node asking, "what is my new left child?" you must immediately return nullptr
                Technically, this does indeed truthfully answer the leaf node's question, as both the left and right children of that leaf node are nullptr, so we can technically say that we're swapping the left and right nullptr children
                Functionally, this base case is critical to stop the recursion from continuing as once we reach a nullptr node, there are no more nodes to process
                Correctly, the return type of this base case (nullptr) matches the function's return type (TreeNode*), so we are good
                
                Thus, we add the base case at the top of the function. Our pseudo-function now looks like this:
                
                invertTree(root){
                    if (!root) return nullptr;

                    TreeNode* temp = root->left;
                    root->left = invertTree(root->right);
                    root->right = invertTree(temp);
                }

            Step 6.2, Return Statement: In a recursive function, as we've already established, it is YOUR JOB to ensure that the function returns the correct answer to the prior call 
            This is done via a return statement at the end of the function
            In fact, the return statement cannot be placed anywhere else as, otherwise, any code after the return statement would be unreachable
            This provides a critical hint as, now, your only job is to engineer what the return statement should return, not where to place it

                Thus, our pseudo-function now looks like this:
                    invertTree(root){
                        if (!root) return nullptr;

                        TreeNode* temp = root->left;
                        root->left = invertTree(root->right);
                        root->right = invertTree(temp);
                        return ???;
                    }

            Now, what should we return? To determine this, we must think about what the prior call expects to receive as the answer to its question
            This is most easily determined by applying the function to the sub-structure identified in Step 1
            Moreover, it is important to understand that the first time in the call stack that this return statement is ever reached is IMMEDIATELY AFTER the base case is hit
            Thus, if there are a total of i calls in the call stack, the base case is hit in callstack(i), and the first time this return statement is reached is in callstack(i-1)
            That is, this return statement is first reached in callstack(i-1), and must return the correct answer to callstack(i-2)

                Consider a simple 3-node binary tree:
                    1
                   / \
                  2   3

                If we only consider the LHS branch, the call stack looks like this, with i=2:
                callstack(i=0):
                    invertTree(root=1)
                callstack(i=1): 
                    (root=1)->left = invertTree(root=3)
                callstack(i=2):
                    (root=3)->left = invertTree(root=nullptr)


                We have already established that invertTree(root=nullptr) hits the base case and returns nullptr as the answer to root=3's question, "what is my new left child?"
                
                Now, we must determine what invertTree(root=3) should return as the answer to root=1's question, "what is my new right child?"
                The answer is that invertTree(root=3) should return root=3 itself, as that would correctly answer root=1's question, "what is my new right child?" after the inversion

                Thus, our completed pseudo-function now looks like this:
                    invertTree(root){
                        if (!root) return nullptr;

                        TreeNode* temp = root->left;
                        root->left = invertTree(root->right);
                        root->right = invertTree(temp);
                        return root;
                    }

            Step 6.3, Order of Operations: In some recursive problems, the order in which operations are performed matters
            In this problem, the order does not really matter as we are simply swapping pointers, and it does not matter whether we set the left pointer first or the right pointer first, so long as we store one of the children in a temporary variable
            However, in other problems (eg, tree traversals), the order of operations is critical to ensure that the function behaves correctly
            Thus, always be mindful of the order of operations when designing recursive functions



        Time Complexity: O(n)
        We iterate through all n nodes

        Space Complexity: O(h)
        Where h is the tree height
        This space usage comes from the call stack in the recursion
        The deeper the, the more recursive calls need to be made
        In the worst case, all n nodes are in a single line, h = n
        In the best case, all n nodes are arranged in a balanced fashion, h = log(n)

        In the worst case (skewed tree), h = n, so space complexity is O(n)
        In the best/average case (balanced tree), h = log n, so space complexity is O(log n)

        Quick derivation:
        Draw out a balanced binary tree. Notice that at each level, the number of nodes at that level is double the number of nodes at the prior level
        We can say that ni = 2^hi
        That is, the number of nodes at height=i is follows a base 2 power function
        The total number of nodes is therefore, n = ∑ 2^hi, i=0 to h
        This is a geometric series that simplifies to, n = 2^(h+1) - 1
        Solving for h yields, h = log(n+1) - 1
        Asymptotically this yields, h = log n

    */

    TreeNode* invertTree(TreeNode* root) {
        
        // Handle base case once we go off the tree, so we do not continue deeper in the stack trying to invert a nullptr node
        if (!root) return nullptr; 

        // Swap left and right children
        TreeNode* temp = root->left;
        root->left = invertTree(root->right);
        root->right = invertTree(temp);
        return root;
    }
};