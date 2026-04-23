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

// LeetCode 543: Diameter of Binary Tree
// Problem: Find the diameter (longest path between any two nodes) of a binary tree
// Approach: DFS Post-order Traversal + Height Calculation

class Solution {
    int max_diameter = 0;

    // Helper function to calculate height and track maximum diameter
    int height(TreeNode* root) {
        if(!root) return 0;

        // Recursively calculate heights of left and right subtrees
        int lh = height(root->left);
        int rh = height(root->right);

        // Update maximum diameter: sum of left and right heights at current node
        // (This represents the longest path passing through current node)
        max_diameter = max(lh + rh, max_diameter);

        // Return height of current subtree
        return 1 + max(lh, rh);
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        height(root);
        return max_diameter;
    }
};

/*
Time Complexity: O(n)
- Visit each node exactly once
- At each node: O(1) operations (height comparison, max calculation)

Space Complexity: O(h)
- h: height of tree (recursion call stack)
- Best case O(log n) for balanced tree
- Worst case O(n) for skewed tree

Algorithm (Post-order DFS):
1. Base case: if node is null, return height 0
2. Recursively get heights of left subtree (lh)
3. Recursively get heights of right subtree (rh)
4. Update max_diameter with lh + rh (longest path through current node)
5. Return current node's height: 1 + max(lh, rh)

Key Insight:
- Diameter at a node = left_height + right_height
- The longest path between two nodes either:
  * Goes through current node (left_height + right_height)
  * Is entirely in left subtree or right subtree
- We track maximum across all nodes

Example:
Tree:
       1
      / \
     2   3
    / \
   4   5

Traversal:
- Node 4: height=1, diameter=0
- Node 5: height=1, diameter=0
- Node 2: height=2, diameter=1+1=2
- Node 3: height=1, diameter=0
- Node 1: height=3, diameter=2+1=3

Answer: 3 (path: 4 → 2 → 1 → 3)

Edge Cases:
- Single node: diameter = 0
- Linear tree (skewed): diameter = n-1
- Empty tree: diameter = 0
*/
