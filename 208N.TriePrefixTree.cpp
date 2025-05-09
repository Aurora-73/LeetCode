// Created: 2025-05-10
#include "MyUtils.h"

/*208. 实现 Trie (前缀树)
Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。
这一数据结构有相当多的应用情景，例如自动补全和拼写检查。
请你实现 Trie 类：
Trie() 初始化前缀树对象。
void insert(String word) 向前缀树中插入字符串 word 。
boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，
返回 true ；否则，返回 false 。*/

class Trie {
private:
	struct TreeNode {
		bool isEnd = false;
		// 用 unique_ptr 管理子节点
		unique_ptr<TreeNode> children[26];
	};
	// 根节点也用 unique_ptr
	unique_ptr<TreeNode> root;

public:
	Trie() : root(make_unique<TreeNode>()) {}

	// 插入单词
	void insert(const string &word) {
		TreeNode *now = root.get();
		for(char c : word) {
			int idx = c - 'a';
			if(!now->children[idx]) {
				now->children[idx] = make_unique<TreeNode>();
			}
			now = now->children[idx].get();
		}
		now->isEnd = true;
	}

	// 完整匹配查询
	bool search(const string &word) const {
		TreeNode *now = root.get();
		for(char c : word) {
			int idx = c - 'a';
			if(!now->children[idx])
				return false;
			now = now->children[idx].get();
		}
		return now->isEnd;
	}

	// 前缀查询
	bool startsWith(const string &prefix) const {
		TreeNode *now = root.get();
		for(char c : prefix) {
			int idx = c - 'a';
			if(!now->children[idx])
				return false;
			now = now->children[idx].get();
		}
		return true;
	}
};

int main() {
	Trie trie;
	trie.insert("apple");
	trie.search("apple"); // 返回 True
	trie.search("app"); // 返回 False
	trie.startsWith("app"); // 返回 True
	trie.insert("app");
	trie.search("app"); // 返回 True
}