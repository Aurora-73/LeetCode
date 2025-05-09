// Created: 2025-05-10
#include "MyUtils.h"

/*211. 添加与搜索单词 - 数据结构设计
请你设计一个数据结构，支持 添加新单词 和 查找字符串是否与任何先前添加的字符串匹配 。
实现词典类 WordDictionary ：
WordDictionary() 初始化词典对象
void addWord(word) 将 word 添加到数据结构中，之后可以对它进行匹配
bool search(word) 如果数据结构中存在字符串与 word 匹配，则返回 true ；
否则，返回  false 。word 中可能包含一些 '.' ，每个 . 都可以表示任何一个字母。
addWord 中的 word 由小写英文字母组成
search 中的 word 由 '.' 或小写英文字母组成*/

class WordDictionary {
	struct TreeNode {
		bool isEnd = false;
		unique_ptr<TreeNode> children[26]; // 输入不会有 .
	};
	unique_ptr<TreeNode> root;

public:
	WordDictionary() : root(make_unique<TreeNode>()) {}

	void addWord(const string &word) {
		TreeNode *now = root.get();
		for(auto c : word) {
			int index = c - 'a';
			if(!now->children[index]) { // 智能指针的判空行为都和原始指针一致，都是在检查底层的裸指针是否为 nullptr。
				now->children[index] = make_unique<TreeNode>();
			}
			now = now->children[index].get();
		}
		now->isEnd = true;
	}
	bool search(const string &word) {
		return BFSSearch(word, 0, root.get());
	}
	bool BFSSearch(const string &word, int n, TreeNode *now) { // word 用引用
		if(n == word.size()) { // 不是和 word.size()-1 比较
			return now->isEnd;
		}
		if(word[n] == '.') {
			for(auto &child : now->children) {
				if(child && BFSSearch(word, n + 1, child.get())) { // 先判断child是否为空，进行剪枝
					return true;
				}
			}
		} else {
			auto child = now->children[word[n] - 'a'].get();
			return child && BFSSearch(word, n + 1, child);
		}
		return false;
	}
};

int main() {}

/*
`make_unique<TreeNode>()` 是 C++14 提供的一个工厂函数，它的作用是：
1. 分配内存并构造对象
   auto p = make_unique<TreeNode>();
   等价于
   auto p = unique_ptr<TreeNode>(new TreeNode());
   但比直接 `new` + `unique_ptr` 更安全，因为它在构造过程中抛异常也不会泄漏内存（具有异常安全）。
2. 返回 `unique_ptr<TreeNode>`
   也就是说，`p` 就是一个智能指针，自动管理这块堆区内存。

智能指针的默认值
* `unique_ptr<T>` 和 `shared_ptr<T>` 默认构造时都是空指针，等价于 `nullptr`。
  unique_ptr<TreeNode> p1;     // p1.get() == nullptr
  shared_ptr<TreeNode> p2;     // p2.get() == nullptr
* 当你写 `children[26]` 这样的数组，如果没有显式赋值，每个元素都会按默认构造，也就是 `nullptr`。
  struct Node {
      unique_ptr<Node> children[26];  // 每个 children[i] 默认都是 nullptr
  };
---
小结
 `make_unique<T>()`：创建并返回一个管理新分配 `T` 对象的 `unique_ptr<T>`；
 智能指针（`unique_ptr` / `shared_ptr`）默认值都是 `nullptr`，表示“当前不管理任何对象”。
*/