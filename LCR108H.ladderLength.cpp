// Created: 2025-12-22
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 在字典（单词列表）wordList 中，从单词 beginWord和 endWord 的 转换序列 是一个按下述规格形成的序列：
	序列中第一个单词是 beginWord。
	序列中最后一个单词是 endWord。
	每次转换只能改变一个字母。
	转换过程中的中间单词必须是字典wordList 中的单词。
给定两个长度相同但内容不同的单词 beginWord和 endWord 和一个字典 wordList，
找到从beginWord 到endWord 的 最短转换序列 中的 单词数目。如果不存在这样的转换序列，返回 0。
示例 1：
	输入：beginWord = "hit", endWord = "cog", wordList = {"hot","dot","dog","lot","log","cog"}
	输出：5
	解释：一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog", 返回它的长度 5。
示例 2：
	输入：beginWord = "hit", endWord = "cog", wordList = {"hot","dot","dog","lot","log"}
	输出：0
	解释：endWord "cog" 不在字典中，所以无法进行转换。
提示：
	1 <= beginWord.length <= 10
	endWord.length == beginWord.length
	1 <= wordList.length <= 5000
	wordList{i}.length == beginWord.length
	beginWord、endWord 和 wordList{i} 由小写英文字母组成
	beginWord != endWord
	wordList 中的所有字符串 互不相同 */

class Solution1 {
public:
	int ladderLength(string &beginWord, string &endWord, vector<string> &wordList) {
		int endId = -1, wn = wordList.size(), n = wn + 1;
		for(int i = 0; i < wn; ++i) {
			if(wordList[i] == endWord) {
				endId = i;
				break;
			}
		}
		if(endId == -1) return 0;
		// 最后一位是beginWord，即matrix[wn]
		vector<vector<bool>> matrix(n, vector<bool>(wn));
		for(int i = 0; i < wn; ++i) {
			if(isConnect(beginWord, wordList[i])) {
				matrix[wn][i] = 1;
			}
		}
		for(int i = 0; i < wn; ++i) {
			for(int j = 0; j < wn; ++j) {
				if(isConnect(wordList[i], wordList[j])) {
					matrix[i][j] = matrix[j][i] = 1;
				}
			}
		}
		// 广度优先遍历
		int res = 0;
		vector<bool> visited(wn, 0);
		queue<int> que;
		que.push(wn);
		while(!que.empty()) {
			int size = que.size();
			for(int i = 0; i < size; ++i) {
				int curr = que.front();
				que.pop();
				if(curr == endId) {
					return res + 1; // 返回的是长度，不是转换次数
				}
				for(int j = 0; j < wn; ++j) {
					if(matrix[curr][j] && !visited[j]) {
						visited[j] = true;
						que.push(j);
					}
				}
			}
			++res;
		}
		return 0;
	}

private:
	bool isConnect(string &l, string &r) {
		bool diff = false;
		for(unsigned i = 0; i < l.size(); ++i) {
			if(l[i] != r[i]) {
				if(diff) return false;
				diff = true;
			}
		}
		return diff;
	}
}; // 先建立邻接矩阵，然后查询，很慢，因为有很多判断是无效的

class Solution2 {
public:
	int ladderLength(string &beginWord, string &endWord, vector<string> &wordList) {
		int endId = -1, wn = wordList.size();
		for(int i = 0; i < wn; ++i) {
			if(wordList[i] == endWord) {
				endId = i;
				break;
			}
		}
		if(endId == -1) return 0;
		vector<bool> visited(wn, 0);
		queue<int> que;
		for(int j = 0; j < wn; ++j) {
			if(isConnect(beginWord, wordList[j])) {
				visited[j] = true;
				que.push(j);
			}
		}
		int res = 1;
		while(!que.empty()) {
			int size = que.size();
			for(int i = 0; i < size; ++i) {
				int curr = que.front();
				que.pop();
				if(curr == endId) {
					return res + 1; // 返回的是长度，不是转换次数
				}
				for(int j = 0; j < wn; ++j) {
					if(!visited[j]
					    && isConnect(wordList[curr], wordList[j])) { // 把visited[j]放前面更快
						visited[j] = true;
						que.push(j);
					}
				}
			}
			++res;
		}
		return 0;
	}

private:
	bool isConnect(string &l, string &r) {
		bool diff = false;
		for(unsigned i = 0; i < l.size(); ++i) {
			if(l[i] != r[i]) {
				if(diff) return false;
				diff = true;
			}
		}
		return diff;
	}
}; // 不建立邻接矩阵，需要用到的时候再判断

class Solution {
public:
	int ladderLength(string &beginWord, string &endWord, vector<string> &wordList) {
		int endId = -1, wn = wordList.size(), wordLen = beginWord.size();
		for(int i = 0; i < wn; ++i) {
			if(wordList[i] == endWord) {
				endId = i;
				break;
			}
		}
		if(endId == -1) return 0;
		unordered_map<string, vector<int>> patterns;
		for(int i = 0; i < wn; ++i) {
			string &str = wordList[i];
			for(int j = 0; j < wordLen; ++j) {
				char c = str[j];
				str[j] = '*';
				patterns[str].push_back(i);
				str[j] = c;
			}
		}
		vector<bool> visited(wn, 0);
		queue<int> que;
		for(int i = 0; i < wordLen; ++i) {
			char c = beginWord[i];
			beginWord[i] = '*';
			auto it = patterns.find(beginWord);
			if(it != patterns.end()) {
				vector<int> &vec = it->second;
				for(auto j : vec) {
					if(!visited[j]) {
						visited[j] = true;
						que.push(j);
					}
				}
				vec.clear(); // 防止后续再次遍历，加速
			}
			beginWord[i] = c;
		}
		int res = 1;
		while(!que.empty()) {
			int size = que.size();
			for(int k = 0; k < size; ++k) {
				int curr = que.front();
				que.pop();
				if(curr == endId) {
					return res + 1; // 返回的是长度，不是转换次数
				}
				string &str = wordList[curr];
				for(int i = 0; i < wordLen; ++i) {
					char c = str[i];
					str[i] = '*';
					auto it = patterns.find(str);
					if(it != patterns.end()) {
						vector<int> &vec = it->second;
						for(auto j : vec) {
							if(!visited[j]) {
								visited[j] = true;
								que.push(j);
							}
						}
						vec.clear(); // 防止后续再次遍历，加速
					}
					str[i] = c;
				}
			}
			++res;
		}
		return 0;
	}
}; // 将wordList中字符串的任何一位换成'*'，然后将匹配模式与id保存下来，加速搜索

int main() {
	Solution sol;
	string beginWord, endWord;
	vector<string> wordList;
	beginWord = "hit", endWord = "cog", wordList = { "hot", "dot", "dog", "lot", "log", "cog" };
	cout << sol.ladderLength(beginWord, endWord, wordList) << endl;

	beginWord = "hit", endWord = "cog", wordList = { "hot", "dot", "dog", "lot", "log" };
	cout << sol.ladderLength(beginWord, endWord, wordList) << endl;
}