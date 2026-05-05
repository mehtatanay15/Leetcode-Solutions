// LeetCode 61: Rotate List
// Problem: Rotate a linked list to the right by k places
// Example: [1,2,3,4,5] rotated by 2 becomes [4,5,1,2,3]
// Approach: Circular rotation - convert to circular list, find new head, break cycle

#include <bits/stdc++.h>
using namespace std;

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

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        // Edge cases: empty list, single node, or no rotation
        if (!head || !head->next || k == 0) return head;

        // Step 1: Find the length of the list and get last node
        ListNode* temp = head;
        int length = 1;
        while (temp->next != nullptr) {
            temp = temp->next;
            length++;
        }

        // Step 2: Create a circular list by connecting last node to head
        temp->next = head;

        // Step 3: Optimize k to avoid unnecessary rotations
        // Rotating by length brings us back to original position
        k = k % length;
        
        // Step 4: Find the new tail (which is length - k steps from current tail)
        // We need to move (length - k) steps to find where to break the circle
        int stepsToNewTail = length - k;
        while (stepsToNewTail--) {
            temp = temp->next;
        }

        // Step 5: Break the circle and set new head
        head = temp->next;  // New head is next node
        temp->next = nullptr;  // Break the cycle

        return head;
    }
};

/*
Time Complexity: O(n) - Two passes through the list
  - First pass: Find length and get last node (O(n))
  - Second pass: Move to new tail position (O(n))
Space Complexity: O(1) - Only using constant extra space (no additional data structures)

Algorithm Explanation:

Step 1: Find List Length
- Traverse to the end to count nodes
- Also keeps pointer at last node

Step 2: Create Circular List
- Connect last node back to head
- This makes rotation easier to handle

Step 3: Optimize k
- k = k % length (avoid unnecessary full rotations)
- If k = 0 after modulo, we return original head

Step 4: Find New Tail
- After rotating right by k, the new tail is at position (length - k)
- Walk (length - k) steps to reach it

Step 5: Extract New List
- New head is temp->next
- Break cycle by setting temp->next = nullptr

Example 1:
Input: head = [1,2,3,4,5], k = 2
Length = 5

After creating circular list: 1→2→3→4→5→1→2→3→...
Steps to new tail = 5 - 2 = 3

Start at last node (5), move 3 steps:
5 → 1 → 2 → 3 (new tail)

New head = 3->next = 4
Break at 3: 3->next = nullptr

Result: 4→5→1→2→3

Example 2:
Input: head = [0,1,2], k = 4
Length = 3
k = 4 % 3 = 1

After circular list: 0→1→2→0→1→2→...
Steps to new tail = 3 - 1 = 2

Start at last node (2), move 2 steps:
2 → 0 → 1 (new tail)

New head = 1->next = 2
Result: 2→0→1

Key Insights:
- Rotating by length returns to original (so use modulo)
- Circular list trick simplifies finding new head/tail
- The new tail is always at position (original_length - k_rotations)
- Only need to traverse the list twice total

Edge Cases Handled:
- Empty list: return nullptr
- Single node: already handled (head->next is nullptr)
- k = 0: return head unchanged
- k > length: handled with modulo operation
- k = length: modulo makes it 0, returns original head
*/
