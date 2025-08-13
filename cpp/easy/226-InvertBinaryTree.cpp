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
    TreeNode* invertTree(TreeNode* root) {

    /**
        Uses a recursive approach

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

        if (!root) return nullptr;
        // Swap left and right children
        TreeNode* temp = root->left;
        root->left = invertTree(root->right);
        root->right = invertTree(temp);
        return root;
    }
};