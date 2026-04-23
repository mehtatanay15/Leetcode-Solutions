// LeetCode 104: Maximum Depth of Binary Tree
// Problem: Find the maximum depth of binary tree (longest root-to-leaf path)
// Approach: Recursive DFS post-order traversal

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
    int maxDepth(TreeNode* root) {
        // Base case: empty tree has depth 0
        if (root == NULL) return 0; 

        // Recursively find max depth of left subtree
        int maxLeft = maxDepth(root -> left);

        // Recursively find max depth of right subtree
        int maxRight = maxDepth(root -> right);

        // Current depth = 1 + max(left, right)
        return max(maxLeft, maxRight) + 1;
    }
};

/*
Time Complexity: O(n)
- Visit each node exactly once
- n: total number of nodes in tree

Space Complexity: O(h)
- h: height of tree (recursion call stack)
- Best case: O(log n) for balanced tree
- Worst case: O(n) for skewed tree (linked list shape)

Algorithm (Recursive Post-order DFS):
1. Base case: if node is NULL, return depth 0
2. Recursively get max depth of left subtree
3. Recursively get max depth of right subtree
4. Return 1 + max(left_depth, right_depth)

Key Insight - Post-order Traversal:
- Process children before processing parent
- Combine results from both subtrees
- Natural for tree height/depth problems

Example 1:
Tree:     3
         / \
        9  20
          / \
        15   7

DFS Traversal:
- maxDepth(9): no children, return 1
- maxDepth(15): no children, return 1
- maxDepth(7): no children, return 1
- maxDepth(20):
  * left=1, right=1
  * return 1 + max(1,1) = 2
- maxDepth(3):
  * left=1 (from 9)
  * right=2 (from 20)
  * return 1 + max(1,2) = 3

Output: 3 (longest path has 3 nodes)

Example 2:
Tree: 2
       \
        3

DFS:
- maxDepth(3): no children, return 1
- maxDepth(2):
  * left=0 (NULL)
  * right=1 (from 3)
  * return 1 + max(0,1) = 2

Output: 2

Example 3:
Tree (single node): 1

maxDepth(1):
- left=0, right=0
- return 1 + max(0,0) = 1

Output: 1

Edge Cases:
- Empty tree: return 0
- Single node: return 1
- Completely skewed: depth = number of nodes
- Balanced: depth = log2(n) + 1

Definition:
- Depth = number of nodes on longest path from root to leaf
- Both root and leaf are counted
- Single node tree has depth 1
- Empty tree has depth 0

Comparison with Height:
- Height of node = distance to deepest leaf
- Depth of node = distance from root
- Max depth of tree = height of root

Iterative Alternative (BFS Level-order):

int maxDepth(TreeNode* root) {
    if(!root) return 0;
    queue<TreeNode*> q;
    q.push(root);
    int depth = 0;
    while(!q.empty()) {
        int size = q.size();
        depth++;
        for(int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
    }
    return depth;
}

Recursive vs Iterative:
- Recursive: simpler, cleaner code, uses call stack
- Iterative: explicit queue, better control, avoid stack overflow risk
- Both O(n) time, different space complexity patterns

Why Recursion Works Here:
- Tree problem naturally recursive
- Base case clear (NULL node)
- Subproblems independent (left and right subtrees)
- Combine results from children

Common Pattern for Tree Problems:
- DFS + recursion for depth/height/path problems
- BFS + queue for level-order/shortest-path problems
- Post-order for problems requiring child info first
- Pre-order for problems requiring parent info first
*/
