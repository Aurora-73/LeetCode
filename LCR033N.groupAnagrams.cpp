// Created: 2025-12-04
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个字符串数组 strs，将变位词组合在一起。
 可以按任意顺序返回结果列表。
注意：若两个字符串中每个字符出现的次数都相同，则称它们互为变位词。
示例 1：
	输入: strs = {"eat", "tea", "tan", "ate", "nat", "bat"}
	输出: {{"bat"},{"nat","tan"},{"ate","eat","tea"}}
示例 2：
	输入: strs = {""}
	输出: {{""}}
示例 3：
	输入: strs = {"a"}
	输出: {{"a"}}
提示：
	1 <= strs.length <= 10^4
	0 <= strs{i}.length <= 100
	strs{i}仅包含小写字母
注意：本题与主站 49题相同： */

class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string> &strs) {
		vector<vector<string>> res;
		map<array<int, 26>, int> index;
		for(auto &str : strs) {
			array<int, 26> cnt {};
			for(auto c : str) {
				cnt[c - 'a']++;
			}
			auto it = index.find(cnt);
			if(it == index.end()) {
				res.push_back({ str });
				index[cnt] = res.size() - 1;
			} else {
				res[it->second].push_back(str);
			}
		}
		return res;
	}
}; // 对长为k的字符串排序的时间复杂度为klogk，大于统计的k

struct Array26Hash {
	size_t operator()(array<int, 26> const &a) const noexcept {
		size_t h = 0;
		// 使用一个质数作为混合因子
		for(int x : a) {
			h = h * 1315423911u + std::hash<int>()(x);
		}
		return h;
	}
};

class Solution2 {
public:
	vector<vector<string>> groupAnagrams(vector<string> &strs) {
		vector<vector<string>> res;
		unordered_map<array<int, 26>, int, Array26Hash> index;
		for(auto &str : strs) {
			array<int, 26> cnt {};
			for(auto c : str) {
				cnt[c - 'a']++;
			}
			auto it = index.find(cnt);
			if(it == index.end()) {
				res.push_back({ str });
				index[cnt] = res.size() - 1;
			} else {
				res[it->second].push_back(str);
			}
		}
		return res;
	}
}; // 使用unordered_map需要自定义哈希表

class Solution3 {
public:
	vector<vector<string>> groupAnagrams(vector<string> &strs) {
		vector<vector<string>> res;
		unordered_map<string, int> index;
		for(auto &str : strs) {
			string cnt(26, 0);
			for(auto c : str) {
				cnt[c - 'a']++;
			}
			auto it = index.find(cnt);
			if(it == index.end()) {
				res.push_back({ str });
				index[cnt] = res.size() - 1;
			} else {
				res[it->second].push_back(str);
			}
		}
		return res;
	}
}; // 由于数组长度小于100，因此直接用长为26的字符串存储词频即可，字符串有默认哈希函数

int main() {
	Solution sol;
	vector<string> strs;
	strs = { "eat", "tea", "tan", "ate", "nat", "bat" };
	cout << sol.groupAnagrams(strs) << endl;
}