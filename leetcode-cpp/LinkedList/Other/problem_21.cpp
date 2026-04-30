// LeetCode 21: Merge Two Sorted Lists
// Problem: Merge two sorted linked lists into one sorted list
// Approach: Two-pointer merging with dummy node for simplification

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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // Dummy node simplifies edge cases (no need to handle the head separately)
        ListNode* dummy = new ListNode(-1);
        ListNode* tail = dummy;

        // Compare nodes from both lists and attach the smaller one
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } 
            else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        // Attach remaining nodes from whichever list has elements left
        if (list1 != nullptr) {
            tail->next = list1;
        } 
        else {
            tail->next = list2;
        }

        return dummy->next;
    }
};

/*
Time Complexity: O(n + m) - Single pass through both lists
  where n = length of list1, m = length of list2
Space Complexity: O(1) - Only using pointers, not creating new nodes

Algorithm:
1. Create a dummy node to simplify handling of the head node
2. Initialize a tail pointer pointing to the dummy
3. While both lists have remaining nodes:
   - Compare values at current nodes
   - Attach the smaller node to tail
   - Move the pointer of the list from which we took the node
   - Move tail pointer forward
4. After one list is exhausted, attach the remaining nodes from the other list
5. Return dummy->next (the actual head of merged list)

Key Insight:
- Dummy node eliminates special handling for the first node
- Both lists are already sorted, so we just compare and merge
- Linear time complexity since we process each node exactly once
- No extra space needed as we reuse existing nodes

Example:
List1: 1 → 2 → 4
List2: 1 → 3 → 4

Step by step:
- Compare 1 vs 1: take 1 from list1 → 1
- Compare 2 vs 1: take 1 from list2 → 1 → 1
- Compare 2 vs 3: take 2 from list1 → 1 → 1 → 2
- Compare 4 vs 3: take 3 from list2 → 1 → 1 → 2 → 3
- Compare 4 vs 4: take 4 from list1 → 1 → 1 → 2 → 3 → 4
- List1 exhausted, attach list2's 4 → 1 → 1 → 2 → 3 → 4 → 4

Result: 1 → 1 → 2 → 3 → 4 → 4
*/
