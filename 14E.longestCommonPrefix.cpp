// Created: 2026-02-08
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 14. 最长公共前缀
编写一个函数来查找字符串数组中的最长公共前缀。
如果不存在公共前缀，返回空字符串""。
示例 1：
	输入：strs = {"flower","flow","flight"}
	输出："fl"
示例 2：
	输入：strs = {"dog","racecar","car"}
	输出：""
	解释：输入不存在公共前缀。
提示：
	1 <= strs.length <= 200
	0 <= strs{i}.length <= 200
	strs{i}如果非空，则仅由小写英文字母组成 */

class Solution {
public:
	string longestCommonPrefix(vector<string> &strs) {
		int n = strs.size(), min_len = INT_MAX;
		for(const auto &str : strs) {
			min_len = min<int>(min_len, str.size());
		}
		for(int i = 0; i < min_len; ++i) {
			char curr = strs[0][i];
			for(int j = 1; j < n; ++j) {
				if(curr != strs[j][i]) {
					return strs[0].substr(0, i);
				}
			}
		}
		return strs[0].substr(0, min_len);
	}
};

int main() {
	Solution sol;
	vector<string> strs;
	strs = { "flower", "flow", "flight" };
	cout << sol.longestCommonPrefix(strs) << endl;

	strs = { "dog", "racecar", "car" };
	cout << sol.longestCommonPrefix(strs) << endl;
}