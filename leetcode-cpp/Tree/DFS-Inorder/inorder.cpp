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

// LeetCode 94: Binary Tree Inorder Traversal
// Problem: Traverse binary tree in inorder (Left-Root-Right)
// Approach: DFS Recursive Traversal

class Solution {
public:
    // Helper function for recursive traversal
    void traverse(TreeNode* root, vector<int>& result) {
        if(root == nullptr) return;
       
        traverse(root->left, result);      // Visit left subtree
        result.push_back(root->val);       // Visit root
        traverse(root->right, result);     // Visit right subtree
    }

    vector<int> inorderTraversal(TreeNode* root) {
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

Algorithm (DFS Recursive Inorder):
1. Base case: if node is null, return
2. Recursive case:
   - Traverse left subtree
   - Process current node (add to result)
   - Traverse right subtree

Inorder Definition (Left-Root-Right):
- Process left subtree completely
- Then process current node
- Then process right subtree

Example:
Tree:
       1
      / \
     2   3

Traversal Order:
- Visit 1 (go left)
- Visit 2 (go left) 
- Node 2 has no left, process 2
- 2 has no right
- Back to 1, process 1
- Visit 1's right (3)
- Node 3 has no left, process 3
- 3 has no right

Output: [2, 1, 3]

Another Example:
Tree:
       4
      / \
     2   6
    / \ / \
   1  3 5  7

Inorder Traversal:
- Go to 2 (left of 4)
  - Go to 1 (left of 2)
    - No left, process 1 → [1]
    - No right
  - Process 2 → [1, 2]
  - Go to 3 (right of 2)
    - No left, process 3 → [1, 2, 3]
    - No right
- Process 4 → [1, 2, 3, 4]
- Go to 6 (right of 4)
  - Go to 5 (left of 6)
    - No left, process 5 → [1, 2, 3, 4, 5]
    - No right
  - Process 6 → [1, 2, 3, 4, 5, 6]
  - Go to 7 (right of 6)
    - No left, process 7 → [1, 2, 3, 4, 5, 6, 7]
    - No right

Output: [1, 2, 3, 4, 5, 6, 7] (sorted for BST)

Special Property for BST:
- Inorder traversal of BST gives sorted order
- Useful for validating BST property

Edge Cases:
- Empty tree: returns empty vector
- Single node: returns [node->val]
- All left children: returns in sorted ascending order from leaves to root
- All right children: returns values from root to deepest leaf

Comparison with Other Traversals:
- Preorder (Root-Left-Right): [4, 2, 1, 3, 6, 5, 7]
- Postorder (Left-Right-Root): [1, 3, 2, 5, 7, 6, 4]
- Inorder (Left-Root-Right): [1, 2, 3, 4, 5, 6, 7]

Alternative Iterative Approach:
Could use stack with explicit tracking of visited nodes
- Time: O(n), Space: O(h)
- More complex but avoids recursion overhead
*/