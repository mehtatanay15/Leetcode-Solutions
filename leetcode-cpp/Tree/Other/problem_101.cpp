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

// LeetCode 101: Symmetric Tree
// Problem: Check if a binary tree is a mirror of itself (symmetric)
// Approach: Recursive DFS comparing left and right subtrees

class Solution {
public:
    // Helper function: check if two trees are mirror images of each other
    bool isMirror(TreeNode* p, TreeNode* q) {
        // Both nodes are null - symmetric
        if(!p && !q) return true;
        
        // One node is null, other is not - not symmetric
        if(!p || !q) return false;

        // Nodes must have same value AND
        // p's left must mirror q's right AND
        // p's right must mirror q's left
        return (p->val == q->val) && isMirror(p->left, q->right) && 
               isMirror(p->right, q->left);
    }

    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        
        // Check if left and right subtrees are mirrors of each other
        return isMirror(root->left, root->right);
    }
};

/*
Time Complexity: O(n)
- Visit each node exactly once
- At each node: O(1) operations (value comparison)
- Total: O(n) where n is number of nodes

Space Complexity: O(h)
- h: height of tree (recursion call stack)
- Best case O(log n) for balanced tree
- Worst case O(n) for skewed tree

Algorithm (Recursive DFS):
1. Base cases:
   - Both nodes are null → symmetric (return true)
   - One node is null → not symmetric (return false)
2. Recursive case:
   - Check if values match
   - Recursively check if p->left mirrors q->right
   - Recursively check if p->right mirrors q->left
3. Main function calls isMirror on left and right subtrees

Key Insight:
- A tree is symmetric if:
  * Its left subtree is a mirror of its right subtree
  * Mirror means: values match AND left's left = right's right AND left's right = right's left

Example 1:
Tree:
       1
      / \
     2   2
    / \ / \
   3  4 4  3

Process:
- isMirror(left_2, right_2):
  - values match (2==2)
  - isMirror(3, 3) → true
  - isMirror(4, 4) → true
  - returns true
- Result: Symmetric

Example 2:
Tree:
       1
      / \
     2   2
      \   \
       3   3

Process:
- isMirror(left_2, right_2):
  - values match (2==2)
  - isMirror(null, 3) → false (one null, one not)
  - returns false
- Result: Not symmetric

Edge Cases:
- Null tree: symmetric (empty tree is symmetric)
- Single node: symmetric
- Linear tree: only symmetric if all nodes have same value arranged perfectly
*/
