// Created: 2025-07-03
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/*151. 反转字符串中的单词
给你一个字符串 s，请你反转字符串中 单词 的顺序。
单词 是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词 分隔开。
返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。
注意：输入字符串 s中可能会存在前导空格、尾随空格或者单词间的多个空格。
	返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。
示例 1：
	输入：s = "the sky is blue"
	输出："blue is sky the"
示例 2：
	输入：s = " hello world "
	输出："world hello"
	解释：反转后的字符串中不能存在前导空格和尾随空格。
示例 3：
	输入：s = "a good  example"
	输出："example good a"
	解释：如果两个单词间有多余的空格，反转后的字符串需要将单词间的空格减少到仅有一个。
提示：
	1 <= s.length <= 10^4
	s 包含英文大小写字母、数字和空格 " "
	s 中 至少存在一个 单词
	进阶：如果字符串在你使用的编程语言中是一种可变数据类型，请尝试使用O(1) 额外空间复杂度的 原地 解法。 */

class Solution1 {
public:
	string reverseWords(string s) {
		stringstream input(s);
		string result, temp;
		while(input >> temp) {
			if(result.length() != 0)
				result = temp + " " + result;
			else
				result = temp;
		}
		return result;
	} // 时空均为 O(n)
};

class Solution2 {
public:
	string reverseWords(string s) {
		// 1、移除多余的空格
		int j = 0, i = 0, n = s.size();
		for(; i < n; i++) {
			if(s[i] != ' ' || (j > 0 && s[j - 1] != ' ')) s[j++] = s[i];
		} // 每个单词之后都会保留一个空格，无法删除最后的空格
		if(j > 0 && s[j - 1] == ' ') j--; // 删除最后的空格
		s.resize(n = j);

		// 2、整体反转
		reverse(s.begin(), s.end());

		// 3、每个单词反转
		for(i = 0; i < n; i++) {
			if(s[i] != ' ') {
				j = i;
				while(j < n && s[j] != ' ') j++;
				reverse(s.begin() + i, s.begin() + j);
				i = j - 1;
			}
		}
		return s;
	}
};

class Solution {
public:
	string reverseWords(string &s) {
		// 先去掉s中多余的空格
		int i = 0, j = 0, n = s.size();
		while(j < n) {
			// 跳过空格
			while(j < n && s[j] == ' ') ++j;
			// 单词
			while(j < n && s[j] != ' ') s[i++] = s[j++];
			// 单词后补一个空格
			if(j < n) s[i++] = ' ';
		}
		if(i > 0 && s[i - 1] == ' ') --i;
		s.resize(n = i);

		// 然后s整体翻转
		std::reverse(s.begin(), s.end());
		// 最后每个单词单独翻转
		i = 0, j = 0;
		while(j < n) {
			while(j < n && s[j] != ' ') ++j;
			std::reverse(s.begin() + i, s.begin() + j);
			j = i = j + 1;
		}
		return s;
	}
};

int main() {
	Solution1 sol1;
	Solution2 sol2;
	Solution sol3;
	string s;
	s = " a good   example";
	cout << "|" << sol1.reverseWords(s) << "|" << endl;
	cout << "|" << sol2.reverseWords(s) << "|" << endl;
	cout << "|" << sol3.reverseWords(s) << "|" << endl;

	s = "   hello  world   ";
	cout << "|" << sol1.reverseWords(s) << "|" << endl;
	cout << "|" << sol2.reverseWords(s) << "|" << endl;
	cout << "|" << sol3.reverseWords(s) << "|" << endl;
}