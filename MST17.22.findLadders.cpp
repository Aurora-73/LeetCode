// Created: 2026-01-08
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定字典中的两个词，长度相等。
写一个方法，把一个词转换成另一个词， 但是一次只能改变一个字符。每一步得到的新词都必须能在字典中找到。
编写一个程序，返回一个可能的转换序列。如有多个可能的转换序列，返回最短的序列！！！！！
示例 1：
	输入：
	beginWord = "hit",
	endWord = "cog",
	wordList = {"hot","dot","dog","lot","log","cog"}
	输出：
	{"hit","hot","dot","lot","log","cog"}
示例 2：
	输入：
	beginWord = "hit"
	endWord = "cog"
	wordList = {"hot","dot","dog","lot","log"}
	输出：{}
	解释：endWord "cog" 不在字典中，所以不存在符合要求的转换序列。 */

class Solution1 {
public:
	vector<string> findLadders(string &beginWord, string &endWord, vector<string> &wordList) {
		int n = wordList.size(), endid = -1;
		for(int i = 0; i < n; ++i) {
			if(endWord == wordList[i]) {
				endid = i;
				break;
			}
		}
		if(endid == -1) return {};
		vector<bool> visited(n, 0);
		queue<pair<int, vector<int>>> que;
		for(int i = 0; i < n; ++i) {
			if(isOneStep(beginWord, wordList[i])) {
				que.emplace(i, vector<int> { i });
				visited[i] = 1;
				if(i == endid) {
					return { beginWord, endWord };
				}
			}
		}
		while(!que.empty()) {
			int size = que.size();
			for(int k = 0; k < size; ++k) {
				auto &[i, path] = que.front();
				for(int j = 0; j < n; ++j) {
					if(!visited[j] && isOneStep(wordList[i], wordList[j])) {
						path.push_back(j);
						que.emplace(j, path);
						visited[j] = 1;
						if(j == endid) {
							vector<string> res { beginWord };
							res.reserve(path.size() + 1);
							for(auto id : path) {
								res.emplace_back(std::move(wordList[id]));
							}
							return res;
						}
						path.pop_back();
					}
				}
				que.pop();
			}
		}
		return {};
	}

private:
	bool isOneStep(string &s1, string &s2) {
		bool changed = false;
		for(unsigned i = 0; i < s1.size(); ++i) {
			if(s1[i] != s2[i]) {
				if(!changed) {
					changed = true;
				} else {
					return false;
				}
			}
		}
		return changed;
	}
}; // BFS搜索，在queue中保存路径

class Solution2 {
public:
	vector<string> findLadders(string &beginWord, string &endWord, vector<string> &wordList) {
		int n = wordList.size(), endid = -1, nw = beginWord.size();
		for(int i = 0; i < n; ++i) {
			if(endWord == wordList[i]) {
				endid = i;
				break;
			}
		}
		if(endid == -1) return {};
		vector<bool> visited(n, 0);
		unordered_map<string, vector<int>> pattern;
		pattern.reserve((size_t)n * (size_t)max(1, nw));
		for(int i = 0; i < n; ++i) {
			if(wordList[i] == beginWord) continue;
			for(int j = 0; j < nw; ++j) {
				char c = wordList[i][j];
				wordList[i][j] = '*';
				pattern[wordList[i]].push_back(i);
				wordList[i][j] = c;
			}
		} // 先计算出模式
		queue<pair<int, vector<int>>> que;
		for(int j = 0; j < nw; ++j) {
			char c = beginWord[j];
			beginWord[j] = '*';
			auto it = pattern.find(beginWord);
			beginWord[j] = c;
			if(it != pattern.end()) {
				for(auto i : it->second) {
					que.emplace(i, vector<int> { i });
					visited[i] = 1;
					if(i == endid) {
						return { beginWord, endWord };
					}
				}
			}
		}
		while(!que.empty()) {
			int size = que.size();
			for(int m = 0; m < size; ++m) {
				auto &[i, path] = que.front();
				for(int j = 0; j < nw; ++j) {
					char c = wordList[i][j];
					wordList[i][j] = '*';
					auto it = pattern.find(wordList[i]);
					wordList[i][j] = c;
					if(it != pattern.end()) {
						for(auto k : it->second)
							if(!visited[k]) {
								path.push_back(k);
								que.emplace(k, path);
								visited[k] = 1;
								if(k == endid) {
									vector<string> res { beginWord };
									res.reserve(path.size() + 1);
									for(auto id : path) {
										res.emplace_back(std::move(wordList[id]));
									}
									return res;
								}
								path.pop_back();
							}
						pattern.erase(it);
					}
				}
				que.pop();
			}
		}
		return {};
	}
}; // BFS搜索，提前构造换一个字符为'*'的pattern快速匹配，在queue中保存路径

class Solution {
public:
	vector<string> findLadders(string &beginWord, string &endWord, vector<string> &wordList) {
		int n = wordList.size(), endid = -1, nw = beginWord.size();
		for(int i = 0; i < n; ++i) {
			if(endWord == wordList[i]) {
				endid = i;
				break;
			}
		}
		if(endid == -1) return {};
		unordered_map<string, vector<int>> pattern;
		pattern.reserve((size_t)n * (size_t)max(1, nw));
		for(int i = 0; i < n; ++i) {
			if(wordList[i] == beginWord) continue;
			for(int j = 0; j < nw; ++j) {
				char c = wordList[i][j];
				wordList[i][j] = '*';
				pattern[wordList[i]].push_back(i);
				wordList[i][j] = c;
			}
		} // 先计算出模式
		vector<int> prev(n, -1); // 同时起到记录上一个节点和visited的功能
		queue<int> que;
		for(int j = 0; j < nw; ++j) {
			char c = beginWord[j];
			beginWord[j] = '*';
			auto it = pattern.find(beginWord);
			beginWord[j] = c;
			if(it != pattern.end()) {
				for(auto i : it->second) {
					que.emplace(i);
					prev[i] = n; // 逻辑上wordList[n]为beginWord
					if(i == endid) {
						return { beginWord, endWord };
					}
				}
				pattern.erase(it); // 减少访问量
			}
		}
		while(!que.empty()) {
			int size = que.size();
			for(int m = 0; m < size; ++m) {
				int i = que.front();
				que.pop();
				for(int j = 0; j < nw; ++j) {
					char c = wordList[i][j];
					wordList[i][j] = '*';
					auto it = pattern.find(wordList[i]);
					wordList[i][j] = c;
					if(it != pattern.end()) {
						for(auto k : it->second)
							if(prev[k] < 0) {
								que.emplace(k);
								prev[k] = i;
								if(k == endid) {
									break;
								}
							}
						pattern.erase(it); // 减少访问量
					}
				}
			}
		}
		if(prev[endid] < 0) return {};
		deque<int> path;
		while(endid != n) {
			path.push_front(endid);
			endid = prev[endid];
		}
		vector<string> res { beginWord };
		res.reserve(path.size() + 1);
		for(auto id : path) {
			res.emplace_back(std::move(wordList[id]));
		}
		return res;
	}
}; // 不在queue中保存路径，而是用一个数组path记录每个节点的上一个节点

int main() {
	Solution sol;
	string beginWord, endWord;
	vector<string> wordList;
	beginWord = "hit", endWord = "cog", wordList = { "hot", "dot", "dog", "lot", "log", "cog" };
	cout << sol.findLadders(beginWord, endWord, wordList) << endl;
	beginWord = "hit", endWord = "cog", wordList = { "hot", "dot", "dog", "lot", "log" };
	cout << sol.findLadders(beginWord, endWord, wordList) << endl;
}