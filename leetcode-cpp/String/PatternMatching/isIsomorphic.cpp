class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int mapST[256];
        int mapTS[256];

        for(int i = 0; i < 256; i++) {
            mapST[i] = -1;
            mapTS[i] = -1;
        }

        for(int i = 0; i < s.length(); i++) {
            char c1 = s[i];
            char c2 = t[i];

            if(mapST[c1] == -1 && mapTS[c2] == -1) {
                mapST[c1] = c2;
                mapTS[c2] = c1;
            }
            else {
                if(mapST[c1] != c2 || mapTS[c2] != c1) {
                    return false;
                }
            }
        }

        return true;
    }
};
