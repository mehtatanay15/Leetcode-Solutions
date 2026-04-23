// LeetCode 191: Number of 1 Bits (Hamming Weight)
// Problem: Count the number of '1' bits in the binary representation of a number\n// Approach: Bit Manipulation (Brian Kernighan's Algorithm)

class Solution {
public:
    int hammingWeight(int n) {
        int count = 0;

        while(n) {
            n = n & (n - 1);  // Removes one rightmost '1' bit from n
            count++;
        }

        return count;
    }
};

/*
Time Complexity: O(k)
- k = number of set bits (1s) in the number
- Best case: O(1) if no 1 bits
- Worst case: O(32) for 32-bit integer with all 1s

Space Complexity: O(1)
- Only using count variable

Algorithm (Brian Kernighan's Algorithm):
1. Initialize count = 0
2. While n is not zero:
   a. Perform: n = n & (n - 1)
      - This removes the rightmost '1' bit from n
   b. Increment count
3. Return count

Key Insight - How n & (n-1) Works:
- n & (n-1) clears the rightmost set bit
- Example: 
  * n = 6 (binary: 110)
  * n-1 = 5 (binary: 101)
  * n & (n-1) = 110 & 101 = 100 (binary, which is 4)
  * One '1' bit removed

Why It Works:\n- Subtracting 1 from n flips all bits after the rightmost 1
- ANDing with original n clears that rightmost 1 and all flipped bits
- Pattern repeats: each iteration removes exactly one '1' bit
- Number of iterations = number of '1' bits

Example 1:\nInput: n = 11 (binary: 1011)

Iteration 1:
- n = 11 (1011), count = 0
- n = 11 & 10 = 1011 & 1010 = 1010 (10 in decimal)
- count = 1

Iteration 2:
- n = 10 (1010), count = 1
- n = 10 & 9 = 1010 & 1001 = 1000 (8 in decimal)
- count = 2

Iteration 3:
- n = 8 (1000), count = 2
- n = 8 & 7 = 1000 & 0111 = 0000 (0 in decimal)
- count = 3

Iteration 4:
- n = 0, loop ends
- return count = 3

Output: 3 (three 1-bits in 1011)

Example 2:\nInput: n = 128 (binary: 10000000)

Iteration 1:
- n = 128 (10000000), count = 0
- n = 128 & 127 = 10000000 & 01111111 = 00000000
- count = 1

Loop ends, return 1

Output: 1 (one 1-bit in 10000000)

Example 3:\nInput: n = 0 (binary: 00000000)

- n = 0, loop condition false
- return count = 0

Output: 0 (no 1-bits)

Alternative Approaches:
1. Naive approach:
   - Check each bit using right shift
   - Time: O(32) for 32-bit int (always check all 32 bits)
   - Space: O(1)
   - Less efficient if few set bits

2. Another bit method:
   - Use i = 1 and check (n & i) for each position
   - Time: O(32) for 32-bit int
   - Space: O(1)

3. Using __builtin_popcount():
   - Built-in function in C++
   - Time: O(1) optimized by compiler
   - Space: O(1)
   - Not showing algorithm knowledge

Why Brian Kernighan's Algorithm is Better:
- Only counts set bits (doesn't check zero bits)
- Much faster when set bits are few
- O(k) where k is number of 1s
- Elegant and shows good bit manipulation knowledge

Bit Manipulation Tricks Used:
- n & (n-1): Clears rightmost set bit
- n & 1: Checks if rightmost bit is 1
- n >> 1: Right shifts (divides by 2)
- n << 1: Left shifts (multiplies by 2)
- n ^ (n-1): All bits from rightmost 1 become 1

Edge Cases:
- n = 0: return 0
- n = 2^31 - 1 (INT_MAX): all bits except sign = 31 bits
- Single bit set: return 1
- All bits set: return bit length

Note on Integer Sign:
- Input guaranteed to be non-negative or unsigned
- If signed, need careful handling of sign bit
- For unsigned int, above algorithm works perfectly
*/