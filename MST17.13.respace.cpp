// Created: 2026-01-07
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 哦，不！你不小心把一个长篇文章中的空格、标点都删掉了，并且大写也弄成了小写。
像句子"I reset the computer. It still didn’t boot!"已经变成了"iresetthecomputeritstilldidntboot"。在处理标点符号和大小写之前，
你得先把它断成词语。当然了，你有一本厚厚的词典dictionary，不过，有些词没在词典里。假设文章用sentence表示，设计一个算法，把文章断开，要求未识别的字符最少，返回未识别的字符数。
注意：本题相对原题稍作改动，只需返回未识别的字符数
	示例：
	输入：
	dictionary = {"looked","just","like","her","brother"}
	sentence = "jesslookedjustliketimherbrother"
	输出： 7
	解释： 断句后为"jess looked just like tim her brother"，共7个未识别字符。
提示：
	0 <= len(sentence) <= 1000
	dictionary中总字符数不超过 150000。
	你可以认为dictionary和sentence中只包含小写字母。 */

class Solution1 {
public:
	int respace(vector<string> &dictionary, string &sentence) {
		int n = sentence.size();
		vector<int> dp(n + 1); // dp[i].first: 从i开始的子串的最少未识别字符数
		for(int i = n - 1; i >= 0; --i) {
			int val = INT_MAX;
			for(auto &dic : dictionary) {
				if(isSubStr(sentence, i, dic)) {
					val = min(val, dp[i + dic.size()]);
				}
			}
			for(int j = 1; j <= n - i && j < val; ++j) {
				val = min(val, j + dp[i + j]);
			}
			dp[i] = val;
		}
		return dp.front();
	}

private:
	inline bool isSubStr(string &sentence, int i, string &dic) {
		if(sentence.size() - i < dic.size()) return false;
		return string_view(sentence.data() + i, dic.size()) == string_view(dic.data());
	}
}; // 动态规划，分为两种情况：1、开头与某一个字典匹配成功  2、开头与字典匹配失败

class Solution2 {
public:
	int respace(vector<string> &dictionary, string &sentence) {
		// build trie
		TrieNode *root = new TrieNode();
		int maxLen = 0;
		for(const auto &w : dictionary) {
			insert(root, w);
			if((int)w.size() > maxLen) maxLen = (int)w.size();
		}

		int n = (int)sentence.size();
		vector<int> dp(n + 1, 0);
		dp[n] = 0;
		for(int i = n - 1; i >= 0; --i) {
			dp[i] = 1 + dp[i + 1]; // 把当前字符当作未识别字符
			TrieNode *p = root;
			for(int j = i; j < n && j - i < maxLen; ++j) {
				int idx = sentence[j] - 'a';
				if(p->children[idx] == nullptr) break;
				p = p->children[idx];
				if(p->isEnd) {
					dp[i] = min(dp[i], dp[j + 1]);
					if(dp[i] == 0) break; // 最优剪枝
				}
			}
		}

		return dp[0];
	}

private:
	struct TrieNode {
		bool isEnd = false;
		TrieNode *children[26];
		TrieNode() : isEnd(false) {
			for(int i = 0; i < 26; ++i) children[i] = nullptr;
		}
	};

	void insert(TrieNode *root, const string &s) {
		TrieNode *p = root;
		for(char ch : s) {
			int idx = ch - 'a';
			if(p->children[idx] == nullptr) p->children[idx] = new TrieNode();
			p = p->children[idx];
		}
		p->isEnd = true;
	}
}; // 使用TrieTree进行优化，快速实现匹配

class Solution {
public:
	int respace(vector<string> &dictionary, string &sentence) {
		buildTrie(dictionary);
		int n = (int)sentence.size();
		vector<int> dp(n + 1, 0);
		dp[n] = 0;

		for(int i = n - 1; i >= 0; --i) {
			// 基线：把当前字符当作未识别字符
			dp[i] = 1 + dp[i + 1];

			int node = 0; // 从根开始
			// 最长只需扫描到 maxLen 个字符
			for(int j = i; j < n && j - i < maxLen; ++j) {
				int c = sentence[j] - 'a';
				int nxt = nodes[node].children[c];
				if(nxt == -1) break; // 无法匹配下去了
				node = nxt;
				if(nodes[node].isEnd) {
					dp[i] = min(dp[i], dp[j + 1]);
					if(dp[i] == 0) break; // 已达最优，剪枝
				}
			}
		}
		return dp[0];
	}

private:
	struct Node {
		array<int, 26> children;
		bool isEnd;
		Node() {
			children.fill(-1);
			isEnd = false;
		}
	};
	vector<Node> nodes;
	int maxLen = 0;

	void buildTrie(const vector<string> &dict) {
		nodes.clear();
		nodes.emplace_back(); // root
		maxLen = 0;

		size_t totalChars = 0;
		for(const auto &w : dict) {
			maxLen = max(maxLen, (int)w.size());
			totalChars += w.size();
		}
		nodes.reserve(min<size_t>(totalChars + 1, 200000)); // 预留减少重分配

		for(const auto &w : dict) {
			int node = 0;
			for(char ch : w) {
				int idx = ch - 'a';
				if(nodes[node].children[idx] == -1) {
					nodes[node].children[idx] = (int)nodes.size();
					nodes.emplace_back();
				}
				node = nodes[node].children[idx];
			}
			nodes[node].isEnd = true;
		}
	}
}; // 使用数组优化TrieTree

int main() {
	Solution sol;
	vector<string> dictionary;
	string sentence;
	dictionary = { "looked", "just", "like", "her", "brother" };
	sentence = "jesslookedjustliketimherbrother";
	cout << sol.respace(dictionary, sentence) << endl;
}