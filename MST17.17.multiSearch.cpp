// Created: 2026-01-07
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个较长字符串big和一个包含较短字符串的数组smalls，
设计一个方法，根据smalls中的每一个较短字符串，对big进行搜索。
输出smalls中的字符串在big里出现的所有位置positions，
其中positions{i}为smalls{i}出现的所有位置。
输入：
    big = "mississippi"
    smalls = {"is","ppi","hi","sis","i","ssippi"}
输出： {{1,4},{8},{},{3},{1,4,7,10},{5}}
提示：
	0 <= len(big) <= 1000
	0 <= len(smalls{i}) <= 1000
	smalls的总字符数不会超过 10^6。
	你可以认为smalls中没有重复字符串。
	所有出现的字符均为英文小写字母。 */

class Solution1 {
public:
	vector<vector<int>> multiSearch(string &big, vector<string> &smalls) {
		int nb = big.size(), ns = smalls.size(), max_ns = 0;
		unordered_set<int> smallsSizes;
		for(auto &sm : smalls) {
			smallsSizes.insert(sm.size());
			max_ns = max<int>(max_ns, sm.size());
		}
		vector<TreeNode> nodes(1);
		nodes.reserve(min({ nb * (nb + 1) / 2, nb * max_ns, 20000 }));
		for(int i = 0; i < nb; ++i) {
			int root = 0;
			for(int j = 0; i + j < nb && j < max_ns; ++j) {
				int index = big[i + j] - 'a';
				if(nodes[root].children[index] == -1) {
					nodes[root].children[index] = nodes.size();
					nodes.emplace_back();
				}
				root = nodes[root].children[index];
				if(smallsSizes.contains(j + 1)) nodes[root].begins.push_back(i);
			}
		}
		vector<vector<int>> res;
		res.reserve(ns);
		for(int i = 0; i < ns; ++i) {
			int root = 0, find = 1;
			for(int j = 0; j < (int)smalls[i].size(); ++j) {
				int index = smalls[i][j] - 'a';
				if(nodes[root].children[index] == -1) {
					find = 0;
					break;
				}
				root = nodes[root].children[index];
			}
			if(find) {
				res.emplace_back(nodes[root].begins);
			} else {
				res.emplace_back();
			}
		}
		return res;
	}

private:
	struct TreeNode {
		vector<int> begins;
		array<int, 26> children;
		TreeNode() {
			children.fill(-1);
		}
	};
}; // 对big的每个位置开始都构造一次TrieTree，在路径中的任何一个节点的begins添加这个开始的标记。很慢，主要是因为在路径中的每个可能点都要存放一次begin

class Solution {
public:
	vector<vector<int>> multiSearch(string &big, vector<string> &smalls) {
		int nb = big.size(), ns = smalls.size(), all_size = 0;
		for(auto &sm : smalls) {
			all_size += sm.size();
		}
		vector<TreeNode> nodes(1);
		nodes.reserve(min({ all_size, 20000 }));
		for(int i = 0; i < ns; ++i) {
			int root = 0;
			for(int j = 0; j < (int)smalls[i].size(); ++j) {
				int index = smalls[i][j] - 'a';
				if(nodes[root].children[index] == -1) {
					nodes[root].children[index] = nodes.size();
					nodes.emplace_back();
				}
				root = nodes[root].children[index];
			}
			nodes[root].smid = i; // 你可以认为smalls中没有重复字符串。
		}
		vector<vector<int>> res(ns);
		for(int i = 0; i < nb; ++i) {
			int root = 0;
			for(int j = 0; i + j < nb; ++j) {
				int index = big[i + j] - 'a';
				if(nodes[root].children[index] == -1) {
					break;
				}
				root = nodes[root].children[index];
				if(nodes[root].smid != -1) {
					res[nodes[root].smid].push_back(i);
				}
			}
		}
		return res;
	}

private:
	struct TreeNode {
		int smid = -1;
		array<int, 26> children;
		TreeNode() {
			children.fill(-1);
		}
	};
}; // 反过来，用smalls建立tree，在结尾处保存对应的id，然后用big的每个位置扫描，将开始位置添加到结果，时间复杂度O(nb * max_ns)

int main() {
	Solution sol;
	string big;
	vector<string> smalls;
	big = "mississippi";
	smalls = { "is", "ppi", "hi", "sis", "i", "ssippi" };
	cout << sol.multiSearch(big, smalls) << endl;
}