// Created: 2025-06-30
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 167. 招式拆解 I
某套连招动作记作序列 arr，其中 arr{i} 为第 i 个招式的名字。
请返回 arr 中最多可以出连续不重复的多少个招式。
示例 1：
	输入：arr = "dbascDdad"
	输出：6
	解释：因为连续且最长的招式序列是 "dbascD" 或 "bascDd"，所以其长度为 6。
示例 2：
	输入：arr = "KKK"
	输出：1
	解释：因为无重复字符的最长子串是 "K"，所以其长度为 1。
示例 3：
	输入：arr = "pwwkew"
	输出：3
	解释：因为连续且最长的招式序列是 "wke"，所以其长度为 3。    
	请注意区分 子串 与 子序列 的概念：你的答案必须是 连续招式 的长度，
	也就是 子串。而 "pwke" 是一个非连续的 子序列，不是 子串。
提示：
	0 <= arr.length <= 40000
	arr 由英文字母、数字、符号和空格组成。 */

class Solution {
public:
	int dismantlingAction(string &arr) {
		bitset<128> exit; // ASCII码定义的字符一定在 0 - 128
		int max_len = 0, n = arr.size();
		int j = 0;
		for(int i = 0; i < n; ++i) {
			while(exit[arr[i]]) {
				exit[arr[j]] = 0;
				++j;
			}
			exit[arr[i]] = 1;
			max_len = max(max_len, i - j + 1);
		}
		return max_len;
	}
};

int main() {
	Solution sol;
	string arr;
	arr = "dbascDdad";
	cout << sol.dismantlingAction(arr) << endl; // 6
	arr = "KKK";
	cout << sol.dismantlingAction(arr) << endl; // 1
	arr = "pwwkew";
	cout << sol.dismantlingAction(arr) << endl; // 3
}