// LeetCode 2937: Make Three Strings Equal (Decode Slant Text)
// Problem: Decode cipher text written in slant pattern (diagonals) in a matrix
// Approach: Fill matrix, read diagonals, trim trailing spaces

class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        if(rows == 0) return "";
        
        int n = encodedText.size();
        int cols = n / rows;  // Calculate columns from total length
        
        // Build matrix from encoded text (row-major order)
        vector<vector<char>> mat(rows, vector<char>(cols));
        
        int idx = 0;
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                mat[i][j] = encodedText[idx++];
            }
        }
        
        string ans = "";
        
        // Read diagonals from top-left moving down-right
        for(int j = 0; j < cols; j++) {
            int i = 0;            // Start at row 0
            int k = j;            // Start at column j
            
            // Traverse diagonal: move down (i++) and right (k++)
            while(i < rows && k < cols) {
                ans += mat[i][k];  // Add character on diagonal
                i++;
                k++;
            }
        }
        
        // Remove trailing spaces (padding artifact from encoding)
        while(!ans.empty() && ans.back() == ' ') {
            ans.pop_back();
        }
        
        return ans;
    }
};

/*
Time Complexity: O(n)
- Build matrix: O(n) to place all characters
- Read diagonals: O(n) to visit each cell once
- Trim spaces: O(m) where m is answer length
- Total: O(n)

Space Complexity: O(n)
- Matrix storage: O(rows * cols) = O(n)

Algorithm (Slant Diagonal Decoding):
1. Create matrix of size rows x cols where cols = len(encodedText) / rows
2. Fill matrix row-by-row with encoded text characters
3. Read matrix diagonally:
   a. For each starting column j (0 to cols-1):
      * Start position: (0, j) [top row, column j]
      * Move diagonally down-right: (i++, k++)
      * Collect all characters on this diagonal
4. Remove trailing spaces (padding from encoding)
5. Return decoded string

Key Insight - Diagonal Reading Pattern:
- Encoding arranges message diagonally in matrix
- Diagonals run from top-left to bottom-right
- Each diagonal starts from top row at different columns
- Reading all diagonals left-to-right recovers original message

Example 1:
Original Message: \"abcdefgh\"
Encoded with rows=2:
cols = 8/2 = 4
Matrix filling (row-major):
[a][b][c][d]\n[e][f][g][h]\n\nReading diagonals:\nj=0: (0,0)->a, (1,1)->f = \"af\"\nj=1: (0,1)->b, (1,2)->g = \"bg\"\nj=2: (0,2)->c, (1,3)->h = \"ch\"\nj=3: (0,3)->d = \"d\"\n\nDecoded Result: \"af\" + \"bg\" + \"ch\" + \"d\" = \"afbgchd\"\n\nNote: This shows diagonal reading, actual encoding/decoding may differ\n\nExample 2 (With Padding):\nOriginal: \"hi\" (2 characters)\nEncoded with rows=2:\nPadded to 4: \"hi  \" (2 spaces for matrix 2x2)\nMatrix:\n[h][i]\n[ ][ ]\n\nReading diagonals:\nj=0: (0,0)->h, (1,1)->(space) = \"h \"\nj=1: (0,1)->i = \"i\"\n\nResult before trim: \"h i\"\nResult after trim: \"h i\" (no trailing space here)\n\nExample 3 (Padding at End):\nOriginal: \"abc\"\nEncoded with rows=3:\nPadded to 6: \"abc   \"\nCols = 6/3 = 2\nMatrix:\n[a][b]\n[c][ ]\n[ ][ ]\n\nReading diagonals:\nj=0: (0,0)->a, (1,1)->(space), (2,2)->out of bounds = \"a \"\nj=1: (0,1)->b, (1,2)->out of bounds = \"b\"\n\nResult: \"a b\"\nLast char is 'b', no trailing space.\n\nActually if we had: \"abc   \" encoded with rows=3, cols=2\nBut (2,2) is out of bounds since cols=2 (indices 0,1)\nSo the space at position (2,1) is never visited.\n\nThe trailing spaces would be visited if they're reachable via diagonal.\n\nEdge Cases:\n- rows = 1: Each character is its own diagonal\n  * Result: same as input (single diagonal per column)\n- cols = 1: All characters form single diagonal\n  * Result: characters in column-major order (all rows same column)\n- Exact fit: No padding needed, no trailing spaces\n- With padding: Trailing spaces are removed after diagonal reading\n\nWhy Diagonal Pattern:\n- Encoding security: shuffles character positions\n- Simple pattern: easy to encode/decode mechanically\n- Matrix structure: organizes message in 2D\n- Reading order: critical for decoding\n\nWhy Trim Trailing Spaces:\n- Matrix must be rectangular (rows x cols)\n- If message length not multiple of rows:\n  * Padding with spaces to fill matrix\n  * Padding might be included in diagonal reading\n  * Trim removes encoding artifact\n- Restores original message exactly\n\nAlternative Diagonal Orders:\n- Current: starts from top-left corners, goes down-right\n- Could also: start from left-top corners, go down-right\n- Could also: read in reverse direction\n- Different encoding variations use different orders\n\nMatrix Indexing Notes:\n- mat[i][j]: i is row, j is column\n- Fill order: row-major (all of row 0, then all of row 1, etc.)\n- Read order: diagonal-major (all of diagonal 0, then diagonal 1, etc.)\n\nWhen this Pattern is Used:\n- Simple cipher/encryption problems\n- Message encoding variations\n- Matrix traversal interview questions\n- Array reorganization problems\n\n*/
