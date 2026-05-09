// LeetCode 1914: Rotate Matrix IV (or Rotate the Matrix by k)
// Problem: Rotate each concentric layer of the matrix by k positions
// Each layer rotates independently, elements move along the perimeter
// Approach: Layer extraction, circular rotation via modulo, layer rewriting

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();      // number of rows
        int n = grid[0].size();   // number of columns
        int numLayers = min(m, n) / 2;  // number of concentric layers

        // Process each layer independently
        for (int layer = 0; layer < numLayers; ++layer) {
            vector<int> elements;
            
            // Step 1: Extract elements from current layer in order (clockwise)
            // Top row (left to right)
            for (int j = layer; j < n - 1 - layer; ++j) 
                elements.push_back(grid[layer][j]);
            
            // Right column (top to bottom)
            for (int i = layer; i < m - 1 - layer; ++i) 
                elements.push_back(grid[i][n - 1 - layer]);
            
            // Bottom row (right to left)
            for (int j = n - 1 - layer; j > layer; --j) 
                elements.push_back(grid[m - 1 - layer][j]);
            
            // Left column (bottom to top)
            for (int i = m - 1 - layer; i > layer; --i) 
                elements.push_back(grid[i][layer]);

            // Step 2: Rotate the extracted elements by k positions
            int L = elements.size();
            int netRotation = k % L;  // Optimize: k might be larger than layer size
            
            // Start index after rotation (elements shift by k positions)
            int idx = netRotation;
            
            // Step 3: Write rotated elements back to the layer
            // Top row (left to right)
            for (int j = layer; j < n - 1 - layer; ++j) 
                grid[layer][j] = elements[idx++ % L];
            
            // Right column (top to bottom)
            for (int i = layer; i < m - 1 - layer; ++i) 
                grid[i][n - 1 - layer] = elements[idx++ % L];
            
            // Bottom row (right to left)
            for (int j = n - 1 - layer; j > layer; --j) 
                grid[m - 1 - layer][j] = elements[idx++ % L];
            
            // Left column (bottom to top)
            for (int i = m - 1 - layer; i > layer; --i) 
                grid[i][layer] = elements[idx++ % L];
        }

        return grid;
    }
};

/*
Time Complexity: O(m * n) - Visit every element exactly twice
  - Extraction: O(m*n) total across all layers
  - Rotation: O(m*n) total across all layers
  - Rewriting: O(m*n) total across all layers
Space Complexity: O(m * n) - Storing extracted elements for all layers

Algorithm Explanation:

Key Concept - Layer Processing:
- A matrix has min(m,n)/2 concentric layers
- Each layer rotates independently
- Elements move along the perimeter of their layer

Step 1 - Extract Layer Elements (Clockwise Order):
Starting from top-left of layer, traverse clockwise:
1. Top row: left to right
2. Right column: top to bottom
3. Bottom row: right to left
4. Left column: bottom to top

Step 2 - Rotate Elements:
- Elements form a circular array on the layer perimeter
- Rotating by k = shift start index by k positions
- Use modulo to handle k > layer_size
- netRotation = k % L ensures we get minimal equivalent rotation

Step 3 - Write Back:
- Traverse the same path (clockwise)
- Write elements from rotated array
- Use modulo arithmetic to wrap around the circular array

Coordinate System for Layer:
For layer L in m×n matrix:
- Top row: grid[L][L] to grid[L][n-1-L]
- Right column: grid[L][n-1-L] to grid[m-1-L][n-1-L]
- Bottom row: grid[m-1-L][n-1-L] to grid[m-1-L][L]
- Left column: grid[m-1-L][L] to grid[L][L]

Example 1:
Input: grid = [[40,10],[30,20]], k = 1

Layer 0 (only one layer):
Extract (clockwise): [40, 10, 20, 30]
L = 4, netRotation = 1 % 4 = 1
Start from index 1: [10, 20, 30, 40]

Write back:
Top: grid[0][0]=10, grid[0][1]=20
Right: grid[1][1]=30
Bottom: grid[1][0]=40

Result: [[10,20],[40,30]]

Example 2:
Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 2

Layer 0 (outer ring):
Extract: [1, 2, 3, 6, 9, 8, 7, 4]
L = 8, netRotation = 2 % 8 = 2
Start from index 2: [3, 6, 9, 8, 7, 4, 1, 2]

Layer 1 (center):
Only element is 5, stays unchanged

Result after layer 0 rotation:
[[3,2,1],[6,5,4],[9,8,7]]

Wait, let me recalculate layer 0:
Top row indices: [0][0] to [0][2]
Right column indices: [0][2] to [2][2] 
Bottom row indices: [2][2] to [2][0]
Left column indices: [2][0] to [0][0]

Actually, let me be more careful:
- Top (layer=0, j from 0 to 2 exclusive): [1,2,3] indices (0,0), (0,1), (0,2)
- Right (layer=0, i from 0 to 2 exclusive): [6,9] indices (1,2), (2,2)
- Bottom (layer=0, j from 2 to 0 exclusive going backwards): [8,7] indices (2,2), (2,1), (2,0)
- Left (layer=0, i from 2 to 0 exclusive going backwards): [4] indices (1,0)

Extract: [1, 2, 3, 6, 9, 8, 7, 4]
k=2, rotate by 2: [8, 7, 4, 1, 2, 3, 6, 9]

Hmm, that's not matching. Let me think about rotation direction.

When we rotate by k, elements move k positions clockwise.
So element at index 0 goes to index k.
Element at index i goes to index (i+k)%L.

If we're reading from position (i+k)%L to fill position i in the output:
- For output position 0: read from (0+k)%L = k
- For output position 1: read from (1+k)%L = k+1
- etc.

So idx starts at k, and we read idx, idx+1, idx+2, ... with modulo.

Extract: [1, 2, 3, 6, 9, 8, 7, 4] (indices 0-7)
k=2:
- Position 0 gets elements[2] = 3
- Position 1 gets elements[3] = 6
- Position 2 gets elements[4] = 9
- Position 3 gets elements[5] = 8
- Position 4 gets elements[6] = 7
- Position 5 gets elements[7] = 4
- Position 6 gets elements[0] = 1
- Position 7 gets elements[1] = 2

New layer: [3, 6, 9, 8, 7, 4, 1, 2]

Write back (same clockwise order):
Top: grid[0][0]=3, grid[0][1]=6, grid[0][2]=9
Right: grid[1][2]=8, grid[2][2]=7
Bottom: grid[2][1]=4, grid[2][0]=1
Left: grid[1][0]=2

Result:
[[3, 6, 9],
 [2, 5, 8],
 [1, 4, 7]]

Key Insights:
- Each layer is independent, can rotate in parallel (conceptually)
- Modulo optimization prevents unnecessary full rotations
- Clockwise extraction and writing ensures correct mapping
- Single pass through matrix after preprocessing

Edge Cases:
- Single element: no layers to rotate
- Single row: 1 layer, processes as top row
- Single column: 1 layer, processes as columns
- k > layer size: modulo handles correctly
- k = 0: layers don't change
- Even dimensions vs odd dimensions: center element(s) in odd case are unaffected
*/
