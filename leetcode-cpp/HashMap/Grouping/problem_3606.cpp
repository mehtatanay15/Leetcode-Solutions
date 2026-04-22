// LeetCode 3606: Validate Coupons by Business Line
// Problem: Validate coupons based on activity status and group by business line
// Approach: HashMap Grouping + String Validation

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> validateCoupons(vector<string>& code, vector<string>& businessLine, vector<bool>& isActive) {
        int n = code.size();
        unordered_map<string, vector<string>> validd; 
        
        // Step 1: Validate and group coupons
        for(int i = 0; i < n; i++) {
            if(isActive[i]) {   
                string temp = code[i];
                if(temp.empty()) continue;
                
                // Check if code contains only alphanumeric characters and underscores
                bool valid = true;
                for(char c : temp) {
                    if(!isalnum(c) && c != '_') {
                        valid = false;
                        break;
                    }
                }

                // Group valid codes by business line
                if(valid) {
                    if (businessLine[i] == "electronics" || businessLine[i] == "grocery" || 
                        businessLine[i] == "pharmacy" || businessLine[i] == "restaurant") {
                        validd[businessLine[i]].push_back(temp);
                    }
                }
            }
        }

        // Step 2: Collect and sort results by category
        vector<string> ans;
        vector<string> categories = {"electronics", "grocery", "pharmacy", "restaurant"};
        
        for(const string& cat : categories) {
            if(validd.count(cat)) {
                sort(validd[cat].begin(), validd[cat].end());
                
                for(const string& validCode : validd[cat]) {
                    ans.push_back(validCode);
                }
            }
        }
        
        return ans;
    }
};

/*
Time Complexity: O(n * m + k log k)
- n: number of coupons
- m: average length of code strings
- k: number of valid coupons (sorting)

Space Complexity: O(n)
- HashMap to store valid coupons

Algorithm:
1. Iterate through each coupon
2. Check if coupon is active
3. Validate coupon code (only alphanumeric + underscore)
4. Group valid coupons by business line
5. Sort each category alphabetically
6. Return sorted coupons in category order

Constraints:
- Valid business lines: electronics, grocery, pharmacy, restaurant
- Valid code characters: a-z, A-Z, 0-9, _
- Empty codes are invalid

Example:
Input:
code = ["ABC123", "XYZ@789", "DEF_456"]
businessLine = ["electronics", "restaurant", "grocery"]
isActive = [true, true, true]

Processing:
- "ABC123": Valid (alphanumeric), active, electronics → add
- "XYZ@789": Invalid (@), skip
- "DEF_456": Valid (alphanumeric + _), active, grocery → add

Output sorted by category: ["ABC123", "DEF_456"]

Key Points:
- Must check isActive flag first
- @ character is invalid in code
- Results must be sorted alphabetically within each category
- Categories must be processed in fixed order
*/
