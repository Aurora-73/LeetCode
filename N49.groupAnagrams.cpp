#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<unordered_set>
#include<map>
#include<set>
using namespace std;

/*
给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。
字母异位词 是由重新排列源单词的所有字母得到的一个新单词。
示例 1:
输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
示例 2:
输入: strs = [""]
输出: [[""]]
示例 3:
输入: strs = ["a"]
输出: [["a"]]
提示：
1 <= strs.length <= 10^4
0 <= strs[i].length <= 100
strs[i] 仅包含小写字母*/

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string , int> map_res; // str2num 2 index
        vector<vector<string>> res;
        for(auto &str : strs){
            string str_copy = str;
            sort(str_copy.begin(), str_copy.end());
            if(map_res.count(str_copy)){
                res[map_res[str_copy]].push_back(str);
            }else{
                map_res[str_copy] = res.size();
                res.push_back({str});
            }
        }
        return res;
    }
};

class Solution2 {
public:
    const vector<double> alpha = {2,  3,  5,  7,  11, 13, 17, 19, 23,
        29, 31, 37, 41, 43, 47, 53, 59, 61,
        67, 71, 73, 79, 83, 89, 97, 101}; // 质数之积相等 这些质数一定相等
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<double , int> map_res; // str2num 2 index
        vector<vector<string>> res;
        for(auto &str : strs){
            double hash_str = 1;
            for(auto c : str){
                hash_str *= alpha[c - 'a'];
            }
            if(map_res.count(hash_str)){
                res[map_res[hash_str]].push_back(str);
            }else{
                map_res[hash_str] = res.size();
                res.push_back({str});
            }
        }
        return res;
    }
}; //hash_str 极限为 101 ^ 100, int 和 long long都存不下

int main(){

}