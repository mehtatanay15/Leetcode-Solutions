/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

// LeetCode 206: Reverse Linked List
// Problem: Reverse a singly linked list
// Approach: Recursive Reversal (reverse tail first, then fix pointers)

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // Base case: empty list or single node
        if (!head) {
            return nullptr;
        }

        // Recursively reverse the rest of the list
        ListNode* newHead = head;
        if (head->next) {
            newHead = reverseList(head->next);  // Reverse tail, get new head
            head->next->next = head;  // Make next node point back to current
        }
        head->next = nullptr;  // Current node's next becomes null (it's the new tail)

        return newHead;
    }
};

/*
Time Complexity: O(n)
- Visit each node exactly once
- n = number of nodes in the list

Space Complexity: O(n)
- Recursion call stack depth = n (length of list)
- In-place pointer manipulation, but recursive stack uses O(n) space

Algorithm (Recursive Reversal):
1. Base case: if head is null, return null
2. Recursive case:
   - Recursively reverse head->next
   - Get the new head from recursion
   - Point head->next->next back to head (reverse the edge)
   - Set head->next to null (current becomes new tail)
   - Return the new head

How It Works:
- Example: 1 → 2 → 3 → null
- Recursion goes deep: reverseList(1) → reverseList(2) → reverseList(3) → reverseList(null)
- At reverseList(3): newHead = 3, no next, return 3
- At reverseList(2): 
  * newHead = 3 (from recursion)
  * 2->next->next = 2 → 3->next = 2
  * 2->next = null
  * return 3
- At reverseList(1):
  * newHead = 3 (from recursion)
  * 1->next->next = 1 → 2->next = 1
  * 1->next = null
  * return 3
- Final: 3 → 2 → 1 → null

Example:
Input: 1 → 2 → 3 → null

Step 1: Call reverseList(1)
Step 2: Call reverseList(2) from within reverseList(1)
Step 3: Call reverseList(3) from within reverseList(2)
Step 4: Call reverseList(null) from within reverseList(3) → returns null
Step 5: Back in reverseList(3): no next, return node 3
Step 6: Back in reverseList(2):
   - newHead = 3
   - 2->next->next = 2 (3 now points to 2)
   - 2->next = null
   - return 3
Step 7: Back in reverseList(1):
   - newHead = 3
   - 1->next->next = 1 (2 now points to 1)
   - 1->next = null
   - return 3
Final: 3 → 2 → 1 → null

Output: 3 → 2 → 1 → null

Edge Cases:
- Empty list: returns null
- Single node: returns that node (no next to reverse)
- Two nodes: 1 → 2 becomes 2 → 1

Alternative Approach (Iterative):
Could also use iterative approach with three pointers (prev, curr, next):
- Time: O(n), Space: O(1)
- But recursive is more elegant and equally efficient for this problem
*/