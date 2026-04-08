class Solution {
public:
    string frequencySort(string s) {
        unordered_map <char,int> mpp;

        for(int i =0; i<s.length(); i++)
        {
            mpp[s[i]]++;
        }
        vector<pair<char, int>> arr(mpp.begin(), mpp.end());

        sort(arr.begin(), arr.end(), [](auto &a, auto &b){
            return a.second > b.second;
        });

        string result = "";

        for(auto &p : arr)
        {
            result += string(p.second, p.first);
        }

        return result;
    }
};