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

// LeetCode 144: Binary Tree Preorder Traversal
// Problem: Traverse binary tree in preorder (Root-Left-Right)
// Approach: DFS Recursive Traversal

class Solution {
public:
    // Helper function for recursive traversal
    void traverse(TreeNode* root, vector<int>& result) {
        if(root == nullptr) return;
        
        result.push_back(root->val);       // Visit root first
        traverse(root->left, result);      // Then visit left subtree
        traverse(root->right, result);     // Then visit right subtree
    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        traverse(root, result);
        return result;
    }
};

/*
Time Complexity: O(n)
- Visit each node exactly once
- n = number of nodes in tree

Space Complexity: O(h)
- h = height of tree (recursion call stack)
- Best case: O(log n) for balanced tree
- Worst case: O(n) for skewed tree

Algorithm (DFS Recursive Preorder):
1. Base case: if node is null, return
2. Recursive case:
   - Process current node (add to result)
   - Traverse left subtree
   - Traverse right subtree

Preorder Definition (Root-Left-Right):
- Process current node first
- Then process left subtree completely
- Then process right subtree completely

Example:
Tree:
       1
      / \
     2   3

Traversal Order:
- Process 1 → [1]
- Visit 1's left (2)
  - Process 2 → [1, 2]
  - 2 has no left
  - 2 has no right
- Visit 1's right (3)
  - Process 3 → [1, 2, 3]
  - 3 has no left
  - 3 has no right

Output: [1, 2, 3]

Another Example:
Tree:
       4
      / \
     2   6
    / \ / \
   1  3 5  7

Preorder Traversal:
- Process 4 → [4]
- Go to 2 (left of 4)
  - Process 2 → [4, 2]
  - Go to 1 (left of 2)
    - Process 1 → [4, 2, 1]
    - No children
  - Go to 3 (right of 2)
    - Process 3 → [4, 2, 1, 3]
    - No children
- Go to 6 (right of 4)
  - Process 6 → [4, 2, 1, 3, 6]
  - Go to 5 (left of 6)
    - Process 5 → [4, 2, 1, 3, 6, 5]
    - No children
  - Go to 7 (right of 6)
    - Process 7 → [4, 2, 1, 3, 6, 5, 7]
    - No children

Output: [4, 2, 1, 3, 6, 5, 7]

Use Case:
- Preorder is used to create a copy of the tree
- Preorder is used for prefix expressions in trees
- Useful for serialization (can reconstruct tree from preorder + inorder)

Edge Cases:
- Empty tree: returns empty vector
- Single node: returns [node->val]
- All left children: processes root, then all left children
- All right children: processes root, then all right children

Comparison with Other Traversals:
- Preorder (Root-Left-Right): [4, 2, 1, 3, 6, 5, 7]
- Inorder (Left-Root-Right): [1, 2, 3, 4, 5, 6, 7]
- Postorder (Left-Right-Root): [1, 3, 2, 5, 7, 6, 4]

Key Difference:
- Preorder: processes root before children
- Inorder: processes root between children
- Postorder: processes root after children
*/