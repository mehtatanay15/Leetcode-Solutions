// LeetCode 100: Same Tree
// Problem: Determine if two binary trees are identical (same structure and values)
// Approach: Recursive DFS comparison

#include <bits/stdc++.h>
using namespace std;

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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Base case: both nodes are NULL
        if (p == NULL && q == NULL) return true;

        // If one is NULL and other is not, or values don't match
        if(p == NULL || q == NULL || p->val != q->val) return false;

        // Recursively check left and right subtrees
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

/*
Time Complexity: O(min(m, n)) where m and n are number of nodes in each tree
- In worst case, we visit all nodes of the smaller tree
- If trees have different structures, we stop early

Space Complexity: O(min(h1, h2)) where h1 and h2 are heights of trees
- Recursion stack depth is limited by the height of the smaller tree

Algorithm:
1. Base case: If both nodes are NULL, trees are identical (return true)
2. If one is NULL or values don't match, return false
3. Recursively check if left subtrees are identical AND right subtrees are identical
4. Return the combined result

Example 1:
Input: p = [1,2,3], q = [1,2,3]
Output: true

Tree p:     Tree q:
    1           1
   / \         / \
  2   3       2   3

Explanation: Both trees have identical structure and values

Example 2:
Input: p = [1,2], q = [1,null,2]
Output: false

Tree p:     Tree q:
    1           1
   /             \
  2               2

Explanation: Structures are different

Example 3:
Input: p = [1,2,1], q = [1,1,2]
Output: false

Tree p:     Tree q:
    1           1
   / \         / \
  2   1       1   2

Explanation: Values in subtrees don't match

Key Points:
- Check node existence first (NULL check)
- Check value equality
- Recursively verify subtrees
- Early termination if any check fails
*/
