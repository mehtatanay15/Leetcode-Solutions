// LeetCode 110: Balanced Binary Tree
// Problem: Check if binary tree is height-balanced (height difference of subtrees <= 1)
// Approach: DFS post-order with height calculation and early termination

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

    int checkHeight(TreeNode* root)
    {
        // Returns -1 if unbalanced, otherwise returns height
        if( root == NULL) return 0;

        // Check left subtree
        int left = checkHeight (root->left);
        if (left == -1 )return -1;  // Early termination if left unbalanced
        
        // Check right subtree
        int right = checkHeight (root->right);
        if (right == -1 )return -1;  // Early termination if right unbalanced

        // Check if current node is balanced
        if(abs(left - right) > 1) return -1;  // Height difference too large

        // Return height of current subtree
        return max(left,right) + 1;
    }

    bool isBalanced(TreeNode* root) {
        return checkHeight(root) != -1;
    }
};

/*
Time Complexity: O(n)
- Each node visited exactly once
- n: total number of nodes in tree
- Early termination can save some work in highly unbalanced trees

Space Complexity: O(h)
- h: height of tree (recursion stack depth)
- Best case: O(log n) for completely balanced tree
- Worst case: O(n) for completely skewed tree (linked list)

Algorithm (DFS Post-order with Height Tracking):
1. For each node, recursively check left and right subtrees
2. If either subtree is unbalanced (returns -1), immediately return -1 (early termination)
3. If both subtrees balanced, check current node:
   a. Calculate height difference: |left_height - right_height|
   b. If difference > 1, tree is unbalanced, return -1
   c. Else, return height of current subtree = 1 + max(left_height, right_height)
4. isBalanced() checks if root returns -1 (unbalanced) or valid height

Key Insight - Marker Value for Unbalanced:
- Use -1 as sentinel value to mark unbalanced subtree
- When -1 encountered, immediately propagate up (early termination)
- Avoids unnecessary computation on unbalanced subtrees
- More efficient than separate boolean flag

Definition of Balanced Binary Tree:
- Empty tree is balanced (height 0)
- Non-empty tree is balanced if and only if:
  * Left subtree is balanced
  * Right subtree is balanced
  * |height(left) - height(right)| <= 1

Height Definition:
- Height of empty tree = 0
- Height of non-empty tree = 1 + max(height(left), height(right))

Example 1:
Tree:     3
         / \
        9  20
          / \
        15   7

DFS Traversal (Post-order):
- Node 9: no children, height=1
  Return: 1

- Node 15: no children
  Return: 1

- Node 7: no children
  Return: 1

- Node 20:
  left_height = 1, right_height = 1
  |1 - 1| = 0 <= 1? Yes ✓
  height = 1 + max(1, 1) = 2
  Return: 2

- Node 3:
  left_height = 1 (from node 9)
  right_height = 2 (from node 20)
  |1 - 2| = 1 <= 1? Yes ✓
  height = 1 + max(1, 2) = 3
  Return: 3

Root returns 3 (not -1), so isBalanced = true ✓

Output: true

Example 2:
Tree:     1
         / \
        2   2
       / \
      3   3
     /
    4

DFS Traversal:
- Node 4: height = 1
- Node 3 (left of parent 3): height = 1
- Node 3 (parent):
  left_height = 1 (from node 4)
  right_height = 0 (null)
  |1 - 0| = 1 <= 1? Yes ✓
  height = 2
- Node 3 (right of parent 2): height = 1
- Node 2 (left of root):
  left_height = 2 (from left-3)
  right_height = 1 (from right-3)
  |2 - 1| = 1 <= 1? Yes ✓
  height = 3
- Node 2 (right of root): height = 1
- Node 1 (root):
  left_height = 3 (from left-2)
  right_height = 1 (from right-2)
  |3 - 1| = 2 > 1? Yes, UNBALANCED!
  Return: -1

Root returns -1, so isBalanced = false ✓

Output: false

Example 3 (Balanced):
Tree:   1
       / \
      2   3

DFS:
- Node 2: height = 1
- Node 3: height = 1
- Node 1:
  left_height = 1, right_height = 1
  |1 - 1| = 0 <= 1? Yes ✓
  height = 2

Root returns 2, isBalanced = true

Output: true

Edge Cases:
- Empty tree (root = NULL): height = 0, isBalanced = true
- Single node: height = 1, isBalanced = true
- Two nodes (left child only): heights 1 and 0, diff = 1, balanced
- Three nodes in line: heights differ by 2, unbalanced

Early Termination Example:
Tree:      1
          / \
         2   3
        / \
       4   5
      /
     6

When checking node 4:
- left_height (from 6) = 1
- right_height (null) = 0
- |1 - 0| = 1 ✓
- height = 2

When checking node 2:
- left_height = 2 (from node 4)
- right_height = 1 (from node 5)
- |2 - 1| = 1 ✓
- height = 3

When checking node 1:
- left_height = 3
- right_height = 1
- |3 - 1| = 2 > 1? Yes, UNBALANCED!
- Return -1 immediately
- No further processing needed

Sentinel Value Pattern:
- -1 indicates unbalanced state
- All valid heights are >= 0
- No ambiguity between valid height and sentinel
- Clean early termination pattern

Comparison with Alternative Approach:

Alternative (less efficient):
int height(TreeNode* root) {
    if(!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

bool isBalanced(TreeNode* root) {
    if(!root) return true;
    int left_h = height(root->left);    // O(n) call
    int right_h = height(root->right);  // O(n) call
    if(abs(left_h - right_h) > 1) return false;
    return isBalanced(root->left) && isBalanced(root->right);
}

Problems:
- height() called multiple times on same nodes
- Time complexity: O(n²) in worst case
- Redundant calculations

Why Current Approach is Better:
- Single DFS pass: O(n)
- Height and balance checked simultaneously
- Early termination on unbalanced subtree
- Efficient marker value pattern

Recursion Pattern - Post-order:
- Visit left subtree
- Visit right subtree
- Process current node (check heights)
- This is post-order DFS
- Parent processes results from children
- Natural fit for this problem

Monotonic Property:
- Each unbalanced check is independent
- Height increases from leaves to root
- Early return prevents further recursion
- Can save significant time on unbalanced trees

Space Complexity Details:
- Recursion stack uses O(h) space
- h determined by tree structure
- No additional data structures
- Very memory efficient
*/
