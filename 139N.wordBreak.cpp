// Created: 2025-05-22
#include "MyUtils.hpp"

/*  139. 单词拆分
给你一个字符串 s 和一个字符串列表 wordDict 作为字典。如果可以利用字典中出现的一个或多个单词拼接出 s
则返回 true。 注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。 */

class Solution1 {
public:
	bool wordBreak(string &s, vector<string> &wordDict) {
		return dfs(s, wordDict, 0);
	}
	bool dfs(const string &s, const vector<string> &wordDict, size_t begin) {
		if(begin == s.size()) {
			return true;
		}
		bool res = false;
		for(auto &word : wordDict) {
			if(begin_with(s, word, begin)) {
				res |= dfs(s, wordDict, begin + word.size());
				if(res) break;
			}
		}
		return res;
	}
	bool begin_with(const string &s, const string &word, int begin) {
		for(int i = 0; i < word.size(); ++i) {
			if(s[begin + i] != word[i]) {
				return false;
			}
		}
		return true;
	}
};
// 递归暴力搜索，每次尝试所有单词，判断能否从当前位置拆分到末尾。

class Solution2 {
public:
	bool wordBreak(string &s, vector<string> &wordDict) {
		canToEnd.resize(s.size());
		visited.resize(s.size(), false);
		return dfs(s, wordDict, 0);
	}
	bool dfs(const string &s, const vector<string> &wordDict, size_t begin) {
		if(begin == s.size()) {
			return true;
		}
		if(visited[begin]) {
			return canToEnd[begin];
		}
		bool res = false;
		for(auto &word : wordDict) {
			if(begin_with(s, word, begin)) {
				res |= dfs(s, wordDict, begin + word.size());
				if(res) break;
			}
		}
		visited[begin] = true;
		canToEnd[begin] = res;
		return res;
	}
	bool begin_with(const string &s, const string &word, int begin) {
		for(int i = 0; i < word.size(); ++i) {
			if(s[begin + i] != word[i]) {
				return false;
			}
		}
		return true;
	}

private:
	vector<bool> canToEnd, visited;
};
// 递归+记忆化搜索（带 visited 和 canToEnd 数组），避免重复计算，效率高

class Solution3 {
public:
	bool wordBreak(string &s, vector<string> &wordDict) {
		int n = s.size(), wn;
		vector<bool> canToEnd(n + 1, false);
		canToEnd.back() = true;

		for(int i = n - 1; i >= 0; --i) {
			for(auto &word : wordDict) {
				wn = word.size();
				if(wn + i <= n && canToEnd[wn + i] && equal(s, word, i)) {
					canToEnd[i] = true;
					break;
				}
			}
		}
		return canToEnd[0];
	}
	inline bool equal(const string &s, const string &word, int begin) {
		for(int i = 0; i < word.size(); ++i) {
			if(word[i] != s[begin + i]) {
				return false;
			}
		}
		return true;
	}
}; // 动态规划，从后往前填表，canToEnd[i] 表示从 i 能否拆分到末尾。

class Solution4 {
public:
	bool wordBreak(string &s, vector<string> &wordDict) {
		int n = s.size();
		unordered_set<string> dict(wordDict.begin(), wordDict.end());
		vector<bool> canToEnd(n + 1, false);
		canToEnd[n] = true;
		// 预处理字典中最短和最长单词长度，减少无效遍历
		int minLen = INT_MAX, maxLen = 0;
		for(auto &w : wordDict) {
			minLen = min(minLen, (int)w.size());
			maxLen = max(maxLen, (int)w.size());
		}
		for(int i = n - 1; i >= 0; --i) {
			for(int len = minLen; len <= maxLen && i + len <= n; ++len) {
				if(canToEnd[i + len] && dict.count(s.substr(i, len))) {
					canToEnd[i] = true;
					break;
				}
			}
		}
		return canToEnd[0];
	}
}; // 时间换空间 用哈希表（unordered_set）替换遍历字典，提升查找效率。
// 时间复杂度O(n * L^2) 空间复杂度O(n + m * l)

int main() {
	Solution sol;
}