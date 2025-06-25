// Created: 2025-06-25
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 169. 招式拆解 II
某套连招动作记作仅由小写字母组成的序列 arr，其中 arr{i} 第 i 个招式的名字。
请返回第一个只出现一次的招式名称，如不存在请返回空格。
示例 1：
	输入：arr = "abbccdeff"
	输出："a"
示例 2：
	输入：arr = "ccdd"
	输出：" "
限制：
	0 <= arr.length<= 50000 */

class Solution {
public:
	char dismantlingAction(string &arr) {
		vector<int> count(26), order(26, -1);
		int n = arr.size(), min_index = n;
		for(int i = 0; i < n; ++i) {
			int index = arr[i] - 'a';
			++count[index];
			if(order[index] == -1) {
				order[index] = i;
			}
		}
		for(int i = 0; i < 26; ++i) {
			if(count[i] == 1) {
				min_index = min(min_index, order[i]);
			}
		}
		return min_index == n ? ' ' : arr[min_index];
	}
};

int main() {
	Solution sol;
	string arr;
	arr = "abbccdeff";
	cout << sol.dismantlingAction(arr) << boolalpha << endl;
	arr = "ccdd";
	cout << (sol.dismantlingAction(arr) == ' ') << endl;
}