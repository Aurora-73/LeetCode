#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
#include"MyUtils.h"

using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        unordered_map<string, bool> map;
        int n1 = words.size(), n2 = words[0].size(), i = 0;
        for(auto word : words){
            map[word] = false;
        }
        while(s.size() - i > n1 * n2){
            for(int j = 0; j < n1; j++){
                string sub_str = s.substr(i + j * n2, n2);
                if(map.count(sub_str)){
                    map[sub_str] = true;
                }else{
                    break;
                }
            }
            bool is = true;
            for(auto &pair : map){ // pair不是指针，所以要用引用
                is &= pair.second;
                pair.second = false;
            }
            if(is){
                res.push_back(i);
            }
            i++;
        }
        return res;
    }
};

int main(){
    Solution sol;
    string s = "barfoothefoobarman";
    vector<string> words = {"foo","bar"};
    cout << sol.findSubstring(s, words) << endl;
}