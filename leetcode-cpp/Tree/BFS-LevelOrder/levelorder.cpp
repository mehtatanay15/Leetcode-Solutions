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

// LeetCode 102: Binary Tree Level Order Traversal
// Problem: Traverse binary tree level by level (BFS)
// Approach: BFS using Queue

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == NULL) return ans;
        
        queue<TreeNode*> q;
        q.push(root);
        
        // Process each level
        while(!q.empty()) {
            int size = q.size();  // Number of nodes at current level
            vector<int> level;
            
            // Process all nodes at current level
            for(int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                // Add children to queue for next level
                if(node->left != NULL) q.push(node->left);
                if(node->right != NULL) q.push(node->right);
                
                // Add current node value to current level
                level.push_back(node->val);
            }
            
            ans.push_back(level);
        }
        
        return ans;
    }
};

/*
Time Complexity: O(n)
- Visit each node exactly once
- n = number of nodes in tree

Space Complexity: O(w)
- w = maximum width of tree (most nodes at any level)
- For a complete binary tree: w ≈ n/2 (last level)
- Best case: O(1) for single node
- Worst case: O(n) for unbalanced tree

Algorithm (BFS Level Order):
1. Initialize queue with root node
2. While queue is not empty:
   a. Get current level size (number of nodes at this level)
   b. For each node at this level:
      - Dequeue node
      - Add its children to queue (for next level)
      - Add node's value to current level result
   c. Add current level to final answer

Key Concept:
- Uses queue (FIFO) to process nodes level by level
- All nodes of current level are added before next level's nodes
- Queue size at start of each iteration = nodes at that level

Example:
Tree:
       3
      / \
     9  20
       /  \
      15   7

Step 1: Queue = [3]
- Level 0: process 3
  - Add children: 9, 20
  - Level = [3]
  - ans = [[3]]
  - Queue = [9, 20]

Step 2: Queue = [9, 20], size = 2
- Level 1: process 9 and 20
  - Process 9: no children, Level = [9]
  - Process 20: add 15, 7, Level = [9, 20]
  - ans = [[3], [9, 20]]
  - Queue = [15, 7]

Step 3: Queue = [15, 7], size = 2
- Level 2: process 15 and 7
  - Process 15: no children, Level = [15]
  - Process 7: no children, Level = [15, 7]
  - ans = [[3], [9, 20], [15, 7]]
  - Queue = []

Output: [[3], [9, 20], [15, 7]]

Why Size Snapshot is Important:
- If we don't capture size at start of loop:
  * Queue grows as we add children
  * We might process nodes from next level in current iteration
  * Results would be mixed up

Another Example:
Tree (unbalanced):
     1
    /
   2
  /
 3

Level 0: [1]
Level 1: [2]
Level 2: [3]

Output: [[1], [2], [3]]

Edge Cases:
- Empty tree: returns empty vector
- Single node: returns [[node->val]]
- All left children: each level has one node
- All right children: each level has one node
- Complete binary tree: levels fill from left to right

Comparison:
- Level Order (BFS): processes one level at a time
- Depth First (DFS): processes along depth, uses recursion/stack
- Level Order better for: finding level height, level-wise problems
- DFS better for: finding paths, postorder processing

Alternative: Use deque for slight optimization
- Time same, but deque access is sometimes faster

Use Cases:
- Finding height of tree
- Finding nodes at specific level
- Finding rightmost node at each level
- Binary tree right side view
- Zigzag traversal
*/