// Created: 2026-01-04
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 在老式手机上，用户通过数字键盘输入，手机将提供与这些数字相匹配的单词列表。
每个数字映射到0至4个字母。给定一个数字序列，实现一个算法来返回匹配单词的列表。你会得到一张含有有效单词的列表。映射如下图所示：
示例 1：
	输入：num = "8733", words = {"tree", "used"}
	输出：{"tree", "used"}
示例 2：
	输入：num = "2", words = {"a", "b", "c", "d"}
	输出：{"a", "b", "c"}
提示：
	num.length <= 1000
	words.length <= 500
	words{i}.length == num.length
	num中不会出现 0, 1 这两个数字 */

class Solution {
public:
	vector<string> getValidT9Words(const string &num, vector<string> &words) {
		static constexpr array<char, 26> mapChar { '2',
			'2',
			'2',
			'3',
			'3',
			'3',
			'4',
			'4',
			'4',
			'5',
			'5',
			'5',
			'6',
			'6',
			'6',
			'7',
			'7',
			'7',
			'7',
			'8',
			'8',
			'8',
			'9',
			'9',
			'9',
			'9' };
		vector<string> res;
		res.reserve(words.size());
		for(auto &word : words) {
			int ok = 1, n = num.size();
			for(int j = 0; j < n; ++j) {
				if(mapChar[word[j] - 'a'] != num[j]) {
					ok = 0;
					break;
				}
			}
			if(ok) res.emplace_back(std::move(word));
		}
		return res;
	}
};

int main() {
	Solution sol;
	string num;
	vector<string> words;
	num = "8733", words = { "tree", "used" };
	cout << sol.getValidT9Words(num, words) << endl;

	num = "2", words = { "a", "b", "c", "d" };
	cout << sol.getValidT9Words(num, words) << endl;
}