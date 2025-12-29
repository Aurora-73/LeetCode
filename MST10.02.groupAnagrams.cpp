// Created: 2025-12-29
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 编写一种方法，对字符串数组进行排序，将所有变位词组合在一起。
变位词是指字母相同，但排列不同的字符串。
注意：本题相对原题稍作修改
示例：
	输入：{"eat", "tea", "tan", "ate", "nat", "bat"},
	输出：
	{
	  {"ate","eat","tea"},
	  {"nat","tan"},
	  {"bat"}
	}
	说明：
	所有输入均为小写字母。
	不考虑答案输出的顺序。 */

class Solution1 {
public:
	vector<vector<string>> groupAnagrams(vector<string> &strs) {
		unordered_map<string, vector<string>> mapp(strs.size());
		for(auto &str : strs) {
			string key = str;
			sort(key.begin(), key.end());
			mapp[key].emplace_back(std::move(str));
		}
		vector<vector<string>> res;
		res.reserve(mapp.size());
		for(auto &pair : mapp) {
			res.emplace_back(std::move(pair.second));
		}
		return res;
	}
};

class Solution2 {
public:
	vector<vector<string>> groupAnagrams(vector<string> &strs) {
		unordered_map<array<unsigned, 26>, vector<string>, ArrayHash> mapp(strs.size());
		for(auto &str : strs) {
			array<unsigned, 26> key {};
			for(auto c : str) {
				++key[c - 'a'];
			}
			mapp[key].emplace_back(std::move(str));
		}
		vector<vector<string>> res;
		res.reserve(mapp.size());
		for(auto &pair : mapp) {
			res.emplace_back(std::move(pair.second));
		}
		return res;
	}

private:
	struct ArrayHash {
		size_t operator()(const array<unsigned, 26> &a) const noexcept {
			size_t res = 0;
			for(int x : a) {
				res = (res * 3141) ^ (x * 5926);
			}
			return res;
		}
	};
};

class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string> &strs) {
		unordered_map<string, vector<string>> mapp;
		for(auto &str : strs) {
			string key(26, CHAR_MIN);
			for(auto c : str) {
				++key[c - 'a'];
			}
			mapp[key].emplace_back(std::move(str));
		}
		vector<vector<string>> res;
		res.reserve(mapp.size());
		for(auto &pair : mapp) {
			res.emplace_back(std::move(pair.second));
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<string> strs;
	strs = { "eat", "tea", "tan", "ate", "nat", "bat" };
	cout << sol.groupAnagrams(strs) << endl;
}