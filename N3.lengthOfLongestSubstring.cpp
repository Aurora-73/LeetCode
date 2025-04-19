#include<iostream>
#include<vector>
#include<unordered_set>
#include<string>

using namespace std;

class Solution {
    public:
        int lengthOfLongestSubstring(string s) {
            if(s.size() == 0)   return 0;
            unordered_set<char> sett{s[0]};
            int i = 0, j = 0, len = 1;
            while(j < s.size()){
                j++;
                if(j < s.size()){
                    while(sett.count(s[j])){
                        sett.erase(s[i]);
                        i++;
                    }
                    sett.insert(s[j]);
                }
                len = max(len, int(sett.size()));
            }
            return len;
        }
    };

int main(){
    Solution sol;
    cout << sol.lengthOfLongestSubstring("au");
}