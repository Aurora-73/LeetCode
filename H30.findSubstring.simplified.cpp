#include"MyUtils.h"

/*
vector<int> s, vector<int>& words
查找s中等于words任意排列的子数组的开头
*/
// {1, 2, 0, 1, 3, 2, 1, 1, 2, 0, 1, 3, 2};
class Solution1 {
public:
    vector<int> findSubstring(vector<int> s, vector<int>& words) {
        vector<int> vec;
        int word_num = words.size(), i = 0, j = -1, count = 0;
        unordered_map<int, int> smap;
        for(auto w : words) smap[w]++;
        unordered_map<int, int> m;
        while(j < int(s.size())){ // int 会被转为size_t 然后 -1 就是最大值
            if(count < word_num){
                j++;
                if(j >= s.size())   break;
                m[s[j]]++;
                count++;
                while(m[s[j]] > smap[s[j]]){
                    m[s[i]]--;
                    i++;
                    count--;
                }
            }else if(count == words.size()){
                vec.push_back(i);
                m[s[i]]--;
                i++;
                count--;
            }
        }
        return vec;
    }
};

class Solution2 {
public:
    vector<int> findSubstring(vector<int> s, vector<int>& words) {
        vector<int> vec;
        int word_num = words.size(), i = 0, j = 0, count = 0;
        unordered_map<int, int> words_map;
        for(auto w : words) words_map[w]++;
        unordered_map<int, int> window_words;

        while(j < s.size()){
            if(words_map.count(s[j])){
                window_words[s[j]]++;
                count++;

                while(window_words[s[j]] > words_map[s[j]]){
                    window_words[s[i]]--;
                    i++;
                    count--;
                }

                if(count == word_num) vec.push_back(i);
            }else{
                window_words.clear();
                count = 0;
                i = j + 1;
            }
            j++;
        }
        return vec;
    }
}; // batter

class Solution3 {
public:
    vector<int> findSubstring(vector<int> s, vector<int>& words) {
        vector<int> vec;
        int word_num = words.size(), i = 0, j = 0, count = 0;
        unordered_map<int, int> words_map;
        for(auto w : words) words_map[w]++;
        unordered_map<int, int> window_words;
        
        while(j < s.size()){
            int now = s[j];
            j++;
            if(words_map.count(now)){
                window_words[now]++;
                count++;

                while(window_words[now] > words_map[now]){
                    window_words[s[i]]--;
                    i++;
                    count--;
                }

                if(count == word_num) vec.push_back(i);
            }else{
                window_words.clear();
                count = 0;
                i = j;
            }
        }
        return vec;
    }
}; // best

int main(){
    Solution1 sol1;
    Solution2 sol2;
    vector<int> words = {1, 2, 3};
    vector<int> s = {1, 2, 0, 1, 3, 2, 1, 1, 2, 0, 1, 3, 2};
    cout << sol1.findSubstring(s, words) << endl;
    cout << sol2.findSubstring(s, words) << endl;
}