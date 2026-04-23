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

// LeetCode 145: Binary Tree Postorder Traversal
// Problem: Traverse binary tree in postorder (Left-Right-Root)
// Approach: DFS Recursive Traversal

class Solution {
public:
    // Helper function for recursive traversal
    void traverse(TreeNode* root, vector<int>& result) {
        if(root == nullptr) return;
       
        traverse(root->left, result);      // Visit left subtree
        traverse(root->right, result);     // Visit right subtree
        result.push_back(root->val);       // Visit root last
    }

    vector<int> postorderTraversal(TreeNode* root) {
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

Algorithm (DFS Recursive Postorder):
1. Base case: if node is null, return
2. Recursive case:
   - Traverse left subtree
   - Traverse right subtree
   - Process current node (add to result)

Postorder Definition (Left-Right-Root):
- Process left subtree completely
- Process right subtree completely
- Then process current node

Example:
Tree:
       1
      / \
     2   3

Traversal Order:
- Visit 1 (go left)
- Visit 2 (go left)
  - No left, go right
  - No right, process 2 → [2]
- Back to 1, go right
- Visit 3 (go left)
  - No left, go right
  - No right, process 3 → [2, 3]
- Process 1 → [2, 3, 1]

Output: [2, 3, 1]

Another Example:
Tree:
       4
      / \
     2   6
    / \ / \
   1  3 5  7

Postorder Traversal:
- Go to 2 (left of 4)
  - Go to 1 (left of 2)
    - No left, no right, process 1 → [1]
  - Go to 3 (right of 2)
    - No left, no right, process 3 → [1, 3]
  - Process 2 → [1, 3, 2]
- Go to 6 (right of 4)
  - Go to 5 (left of 6)
    - No left, no right, process 5 → [1, 3, 2, 5]
  - Go to 7 (right of 6)
    - No left, no right, process 7 → [1, 3, 2, 5, 7]
  - Process 6 → [1, 3, 2, 5, 7, 6]
- Process 4 → [1, 3, 2, 5, 7, 6, 4]

Output: [1, 3, 2, 5, 7, 6, 4]

Use Cases:
- Postorder is used to delete a tree (delete children before parent)
- Postorder is used for expression evaluation (operands before operator)
- Useful for calculating tree properties (height, size) bottom-up

Edge Cases:
- Empty tree: returns empty vector
- Single node: returns [node->val]
- All left children: processes all left children, then root
- All right children: processes all right children, then root

Comparison with Other Traversals:
- Preorder (Root-Left-Right): [4, 2, 1, 3, 6, 5, 7]
- Inorder (Left-Root-Right): [1, 2, 3, 4, 5, 6, 7]
- Postorder (Left-Right-Root): [1, 3, 2, 5, 7, 6, 4]

Why Postorder for Deletion:
- If you delete parent first, you lose reference to children
- With postorder, you delete children first, then parent
- Prevents memory leaks and null pointer issues

Alternative Iterative Approach:
Could use two stacks or special flag for visited nodes
- Time: O(n), Space: O(h)
- More complex but avoids recursion overhead
*/