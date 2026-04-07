class Solution {
public:
    string reverseWords(string s) {
        int n = s.length();

        // Step 1: replace spaces with '#'
        for(int i = 0; i < n; i++) {
            if(s[i] == ' ') {
                s[i] = '#';
            }
        }

        vector<string> words;

        int i = n - 1;

        while(i >= 0) {
            // skip '#'
            if(s[i] == '#') {
                i--;
                continue;
            }

            int r = i;

            // move left to find word start
            while(i >= 0 && s[i] != '#') {
                i--;
            }

            int l = i + 1;

            // extract word
            words.push_back(s.substr(l, r - l + 1));
        }

        // join words with single space
        string result = "";
        for(int i = 0; i < words.size(); i++) {
            if(i > 0) result += " ";
            result += words[i];
        }

        return result;
    }
};