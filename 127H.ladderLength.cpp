// Created: 2025-05-09
#include "MyUtils.hpp"

/*127. 单词接龙
字典 wordList 中从单词 beginWord 到 endWord 的 转换序列 是一个按下述规格形成的序列 beginWord -> s1 -> s2 -> ... -> sk：
每一对相邻的单词只差一个字母。
 对于 1 <= i <= k 时，每个 si 都在 wordList 中。注意， beginWord 不需要在 wordList 中。
sk == endWord
给你两个单词 beginWord 和 endWord 和一个字典 wordList ，返回 从 beginWord 到 endWord 的 最短转换序列 中的 单词数目 。如果不存在这样的转换序列，返回 0 。*/

class Solution1 {
public:
	bool onStep(string &a, string &b) {
		bool diff = false;
		for(size_t i = 0; i < a.size(); i++) {
			if(a[i] != b[i]) {
				if(diff) {
					return false;
				} else {
					diff = true;
				}
			}
		}
		return diff;
	}
	int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
		vector<bool> visited(wordList.size(), false);
		queue<string *> q;
		q.push(&beginWord);
		int step = 0;
		while(!q.empty()) {
			size_t size = q.size();
			++step;
			while(size--) {
				string &now = *q.front();
				q.pop();
				if(now == endWord) {
					return step;
				}
				for(int i = 0; i < wordList.size(); ++i) {
					if(!visited[i] && onStep(wordList[i], now)) {
						visited[i] = true;
						q.push(&wordList[i]);
					}
				}
			}
		}
		return 0;
	}
}; // 同433解法1，但是要注意长度等于变化次数+1  // 时间复杂度 O(n * n * wordLen) 空间复杂度O(n) 主要是指针的queue和visited

class Solution2 {
public:
	int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
		unordered_map<string, int> wordSet;
		for(int i = 0; i < wordList.size(); ++i) {
			wordSet[wordList[i]] = i;
		}
		queue<string *> q;
		q.push(&beginWord);
		int step = 0;
		while(!q.empty()) {
			size_t size = q.size();
			++step;
			while(size--) {
				string &now = *q.front();
				q.pop();
				if(now == endWord) {
					return step;
				}
				for(int i = 0; i < now.size(); i++) {
					string oneStep = now;
					for(int j = 0; j < 26; j++) {
						oneStep[i] = 'a' + j;
						auto it = wordSet.find(oneStep);
						if(it != wordSet.end()) {
							q.push(&wordList[it->second]);
							wordSet.erase(it);
						}
					}
				}
			}
		}
		return 0;
	}
}; // 将原始数据放入集合，每次查找不再是一一比较，而是对当前字符串的全部位进行替换
// 检查替换后的结果是否在map中，visited数组可以用从map中去除元素代替 每次查找的时间复杂度 O(n * 26 * wordLen)
// 整个程序的空间复杂度 O(n * wordLen)

class Solution3 {
public:
	// 哈希函数：对指针指向的 string 内容进行哈希
	struct StringPtrHash {
		size_t operator()(const string *s) const {
			return hash<string>()(*s); // 解引用并对内容哈希
		}
	};
	// 相等比较函数：基于指向内容的字符串比较
	struct StringPtrEqual {
		bool operator()(const string *lhs, const string *rhs) const {
			return *lhs == *rhs;
		}
	};
	int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
		unordered_set<string *, StringPtrHash, StringPtrEqual> wordSet;
		for(int i = 0; i < wordList.size(); ++i) {
			wordSet.insert(&wordList[i]);
		}
		queue<string *> q;
		q.push(&beginWord);
		int step = 0;
		while(!q.empty()) {
			size_t size = q.size();
			++step;
			while(size--) {
				string &now = *q.front();
				q.pop();
				if(now == endWord) {
					return step;
				}
				for(int i = 0; i < now.size(); i++) {
					string oneStep = now;
					for(int j = 0; j < 26; j++) {
						oneStep[i] = 'a' + j;
						auto it = wordSet.find(&oneStep);
						if(it != wordSet.end()) {
							q.push(*it);
							wordSet.erase(it);
						}
					}
				}
			}
		}
		return 0;
	}
}; // 自定义哈希函数，使得它对指针指向的字符串内容进行哈希，而不是对指针本身的地址进行哈希。
// 从而在map中只保存指针不保存真实值，由于指针可以直接指向wordList中的元素，因此不需要记录每个元素的下标了
// 整个程序的空间复杂度 O(n)主要是指针

int main() {
	Solution1 sol1;
	string beginWord = "hit";
	string endWord = "cog";
	vector<string> wordList = { "hot", "dot", "dog", "lot", "log", "cog" };
	cout << sol1.ladderLength(beginWord, endWord, wordList);
	beginWord = "hit";
	endWord = "cog";
	wordList = { "hot", "cog", "dot", "dog", "hit", "lot", "log" };
	cout << sol1.ladderLength(beginWord, endWord, wordList);
}
// hit -> hot -> cog