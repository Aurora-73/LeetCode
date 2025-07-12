// Created: 2025-06-23
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 181. 字符串中的单词反转
你在与一位习惯从右往左阅读的朋友发消息，他发出的文字顺序都与正常相反但单词内容正确，
为了和他顺利交流你决定写一个转换程序，把他所发的消息 message 转换为正常语序。
注意：输入字符串 message 中可能会存在前导空格、尾随空格或者单词间的多个空格。
	返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。
示例 1：
	输入: message = "the sky is blue"
	输出:"blue is sky the"
示例 2：
	输入: message = " hello world! "
	输出:"world! hello"
	解释: 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
示例 3：
	输入: message = "a good  example"
	输出:"example good a"
	解释: 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。
提示：
	0 <= message.length <= 10^4
	message 中包含英文大小写字母、空格和数字 */

class Solution {
public:
	string reverseMessage(string &msg) {
		int n = msg.size(), i = n - 1, j = n - 1;
		string res;
		res.reserve(n);
		while(i >= 0) {
			while(j >= 0 && msg[j] == ' ') --j;
			if(j < 0) break;
			i = j;
			while(i >= 0 && msg[i] != ' ') --i;
			if(!res.empty()) res += ' ';
			// res += string_view(msg.begin() + i + 1, msg.begin() + j + 1);
			res.append(msg.begin() + i + 1, msg.begin() + j + 1);
			j = i;
		}
		return res;
	}
}; // 逆序寻找，然后拼接

class Solution1 {
public:
	string reverseMessage(string &msg) {
		int n = msg.size(), i = 0, j = 0;
		while(j < n) {
			while(msg[j] == ' ') {
				++j;
			}
			if(i != 0 && j < n) {
				msg[i] = ' ';
				++i;
			}
			while(j < n && msg[j] != ' ') {
				msg[i] = msg[j];
				++i, ++j;
			}
		}
		msg.resize(i);
		std::reverse(msg.begin(), msg.end());
		n = i, i = 0, j = 0;
		while(j < n) {
			while(j < n && msg[j] != ' ') ++j;
			std::reverse(msg.begin() + i, msg.begin() + j);
			++j;
			i = j;
		}
		return msg;
	}
}; // 去掉空格，然后整体翻转，每个单词再反转

int main() {
	Solution sol;
	string message;
	message = "the sky is blue";
	cout << '|' << sol.reverseMessage(message) << '|' << endl; // "blue is sky the"
	message = " hello world! ";
	cout << '|' << sol.reverseMessage(message) << '|' << endl; // "world! hello"
	message = " a  good  example";
	cout << '|' << sol.reverseMessage(message) << '|' << endl; // "example good a"
}