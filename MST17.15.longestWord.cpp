// Created: 2026-01-07
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一组单词words，编写一个程序，找出其中的最长单词，且该单词由这组单词中的其他单词组合而成。
若有多个长度相同的结果，返回其中字典序最小的一项，若没有符合要求的单词则返回空字符串。
示例：
输入： {"cat","banana","dog","nana","walk","walker","dogwalker"}
输出： "dogwalker"
解释： "dogwalker"可由"dog"和"walker"组成。
提示：
	0 <= len(words) <= 200
	1 <= len(words{i}) <= 100 
    你可以认为words中仅包含小写字母 */

class Solution {
public:
	string longestWord(vector<string> &words) {
		int n = words.size(), res = -1, max_size = 0;
		vector<TrieTree> nodes(1);
		nodes.reserve(1000);
		for(int i = 0; i < n; ++i) {
			insert(words[i], nodes, i);
		}
		for(int i = 0; i < n; ++i) {
			memo.clear();
			if(dfs(words[i], nodes, 0, i)) {
				if((int)words[i].size() > max_size) {
					max_size = words[i].size();
					res = i;
				} else if((int)words[i].size() == max_size) {
					if(words[res] > words[i]) {
						max_size = words[i].size();
						res = i;
					}
				}
			}
		}
		return max_size ? words[res] : "";
	}

private:
	unordered_map<int, bool> memo;
	struct TrieTree {
		int endid = -1;
		array<int, 26> children;
		TrieTree() {
			children.fill(-1);
		}
	};
	void insert(string &word, vector<TrieTree> &nodes, int id) {
		int root = 0;
		for(auto c : word) {
			if(nodes[root].children[c - 'a'] != -1) {
				root = nodes[root].children[c - 'a'];
			} else {
				nodes[root].children[c - 'a'] = nodes.size();
				root = nodes.size();
				nodes.emplace_back();
			}
		}
		nodes[root].endid = id;
	}
	bool dfs(string &word, vector<TrieTree> &nodes, int i, int id) {
		auto it = memo.find(i);
		if(it != memo.end()) return it->second;
		bool res = false;
		int n = word.size(), init_i = i, root = 0;
		while(!res && i < n) {
			if(root != 0 && nodes[root].endid != -1) {
				res |= dfs(word, nodes, i, id);
			}
			if(nodes[root].children[word[i] - 'a'] != -1) {
				root = nodes[root].children[word[i] - 'a'];
				++i;
			} else {
				break;
			}
		}
		if(i == n && nodes[root].endid != id && nodes[root].endid != -1) {
			res = true;
		}
		memo[init_i] = res;
		return res;
	}
};

int main() {
	Solution sol;
	vector<string> words
	    = { "cat", "banana", "dog", "nana", "walk", "walker", "dogwalker", "aaaaaaaaaaaaa" };
	cout << sol.longestWord(words) << endl;
}