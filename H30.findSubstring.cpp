#include<iostream>
#include<vector>
#include<unordered_map>
#include<map>
#include<string>
#include"MyUtils.h"

using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        if (words.empty() || s.empty()) return res;

        int word_len = words[0].size();
        int word_num = words.size();
        int window_len = word_len * word_num;

        if (s.size() < window_len) return res;

        unordered_map<string, int> word_count;
        for (auto& word : words) word_count[word]++;

        for (int i = 0; i < word_len; i++) {  // 分组滑动
            unordered_map<string, int> window_words;
            int left = i, right = i, count = 0;

            while (right + word_len <= s.size()) {
                string word = s.substr(right, word_len);
                right += word_len;

                if (word_count.count(word)) {
                    window_words[word]++;
                    count++;

                    // 如果当前单词出现次数超过目标，则缩小窗口
                    while (window_words[word] > word_count[word]) {
                        string left_word = s.substr(left, word_len);
                        window_words[left_word]--;
                        left += word_len;
                        count--;
                    }

                    // 匹配成功
                    if (count == word_num) res.push_back(left);
                } else {
                    // 单词不在 words 中，重置窗口
                    window_words.clear();
                    count = 0;
                    left = right;
                }
            }
        }

        return res;
    }
}; // 官方解法
    
class Solution2 {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        unordered_map<string, int> smap;
        int word_num = words.size(), word_len = words[0].size();
        for(auto word : words){
            smap[word]++;
        }
        for(int k = 0; k < word_len; k++){
            int i = k, j = k - word_len, count = 0;
            unordered_map<string, int> m;
            while(j + word_len <= int(s.size())){
                if(count < word_num){
                    j += word_len;
                    if(j + word_len > int(s.size()))   break;
                    string sub = s.substr(j, word_len);
                    m[sub]++; 
                    count++;
                    while(m[sub] > smap[sub]){
                        string subi = s.substr(i, word_len);
                        m[subi]--;
                        i += word_len;
                        count--;
                    }
                }else if(count == word_num){
                    res.push_back(i);
                    m[s.substr(i, word_len)]--;
                    i += word_len;
                    count--;
                }
            }
        }
        return res;
    }
}; // 1.缺少剪枝 2、边界判断混乱

class Solution1 {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        unordered_multimap<string, bool> map;
        int n1 = words.size(), n2 = words[0].size(), i = 0;
        for(auto word : words){
            map.insert({word,false});
        }
        while(s.size() - i >= n1 * n2){ // 有等号，因为是大小之间的比较，并没有下标
            for(int j = 0; j < n1; j++){
                string sub_str = s.substr(i + j * n2, n2);
                if(map.count(sub_str)){
                    bool done = false;
                    auto find = map.equal_range(sub_str);
                    for(auto p = find.first; p != find.second; p++){
                        if(p->second == false){
                            p->second = true;
                            done = true;
                            break;
                        }
                    }
                    if(!done) break;
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
}; // unordered_multimap<string, bool>
class Solution2 {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        unordered_map<string, int> map;
        int n1 = words.size(), n2 = words[0].size(), i = 0;
        for(auto word : words){
            map[word]++;
        }
        while(s.size() - i >= n1 * n2){
            unordered_map<string, int> s_map;
            for(int j = 0; j < n1; j++){
                string sub_str = s.substr(i + j * n2, n2);
                if(map.count(sub_str)){
                    s_map[sub_str]++;
                }else{
                    break;
                }
            }
            bool is = true;
            for(auto &pair : map){
                if(s_map[pair.first] != pair.second){
                    is = false;
                }
            }
            if(is){
                res.push_back(i);
            }
            i++;
        }
        return res;
    }
}; // unordered_map<string, int>

int main(){
    Solution1 sol;
    string s = "barfoothefoobarman";
    vector<string> words = {"foo","bar"};
    cout << sol.findSubstring(s, words) << endl;
    s = "wordgoodgoodgoodbestword";
    cout << s.size() << endl;
    words = {"word","good","best","good"};
    cout << sol.findSubstring(s, words) << endl;
}