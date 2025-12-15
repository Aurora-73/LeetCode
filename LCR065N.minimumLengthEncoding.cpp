// Created: 2025-12-10
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 单词数组words 的 有效编码 由任意助记字符串 s 和下标数组 indices 组成，且满足：
	words.length == indices.length
	助记字符串 s 以 "#" 字符结尾
	对于每个下标 indices{i}，
s 的一个从 indices{i} 开始、到下一个 "#" 字符结束（但不包括 "#"）的 子字符串 恰好与 words{i} 相等
给定一个单词数组words，返回成功对 words 进行编码的最小助记字符串 s 的长度。
示例 1：
	输入：words = {"time", "me", "bell"}
	输出：10
	解释：一组有效编码为 s = "time#bell#" 和 indices = {0, 2, 5}。
	words{0} = "time"，s 开始于 indices{0} = 0 到下一个 "#" 结束的子字符串，
	如加粗部分所示 "time#bell#"
	words{1} = "me"，s 开始于 indices{1} = 2 到下一个 "#" 结束的子字符串，
	如加粗部分所示 "time#bell#"
	words{2} = "bell"，s 开始于 indices{2} = 5 到下一个 "#" 结束的子字符串，
	如加粗部分所示 "time#bell#"
示例 2：
	输入：words = {"t"}
	输出：2
	解释：一组有效编码为 s = "t#" 和 indices = {0}。
提示：
	1 <= words.length <= 2000
	1 <= words{i}.length <= 7
	words{i} 仅由小写字母组成 */

class Solution {
public:
	int minimumLengthEncoding(const vector<string> &words) {
		TrieNode *root = new TrieNode;
		for(auto &str : words) {
			TrieNode *p = root;
			int n = str.size();
			for(int i = n - 1; i >= 0; --i) {
				if(!p->chirds[str[i] - 'a']) {
					p->chirds[str[i] - 'a'] = new TrieNode;
				}
				p = p->chirds[str[i] - 'a'];
			}
		}
		return DFS(root, 1);
	}

private:
	struct TrieNode {
		array<TrieNode *, 26> chirds {};
	};
	int DFS(TrieNode *node, int deepth) {
		int cnt = 0;
		for(auto chird : node->chirds) {
			if(chird) {
				cnt += DFS(chird, deepth + 1);
			}
		}
		return cnt > 0 ? cnt : deepth;
	}
}; // 从后向前构建Trie，统计最终树的全部叶子结点的高度(+1)之和

int main() {
	Solution sol;
	cout << sol.minimumLengthEncoding({ "time", "me", "bell" }) << endl;
}