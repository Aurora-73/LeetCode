// Created: 2025-06-15
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 1432. 改变一个整数能得到的最大差值
给你一个整数num。
你可以对它进行以下步骤共计两次：
	选择一个数字x (0<= x <= 9).
	选择另一个数字y (0<= y <= 9)。数字y可以等于x。
	将 num中所有出现 x的数位都用 y替换。
令两次对 num的操作得到的结果分别为a和b。
请你返回a 和b的 最大差值。
注意，新的整数（a 或 b）必须不能 含有前导 0，并且 非 0。
示例 1：
	输入：num = 555
	输出：888
	解释：第一次选择 x = 5 且 y = 9，并把得到的新数字保存在 a 中。
	第二次选择 x = 5 且 y = 1，并把得到的新数字保存在 b 中。
	现在，我们有 a = 999 和 b = 111，最大差值为 888
示例 2：
	输入：num = 9
	输出：8
	解释：第一次选择 x = 9 且 y = 9，并把得到的新数字保存在 a 中。
	第二次选择 x = 9 且 y = 1，并把得到的新数字保存在 b 中。
	现在，我们有 a = 9 和 b = 1，最大差值为 8
示例 3：
	输入：num = 123456
	输出：820000
示例 4：
	输入：num = 10000
	输出：80000
示例 5：
	输入：num = 9288
	输出：8700
提示：
	1 <= num <= 10^8 */

class Solution {
public:
	int maxDiff(int num) {
		// 先算出最高位权值 n，以及最高位数字 first
		int n = 1, tmp = num;
		while(tmp >= 10) {
			tmp /= 10;
			n *= 10;
		}
		int first = num / n;

		// 找出构造最大值时要替换的数字 dmax（第一个不为 9 的数字）
		int dmax = -1;
		tmp = num;
		int nn = n;
		while(nn > 0) {
			int d = tmp / nn;
			if(d != 9) {
				dmax = d;
				break;
			}
			tmp %= nn;
			nn /= 10;
		}

		// 决定构造最小值时要替换的数字 minFrom 以及替换成的值 minTo
		int minFrom, minTo;
		if(first != 1) {
			// 如果最高位不是 1，就把所有最高位相同的数字替换成 1
			minFrom = first;
			minTo = 1;
		} else {
			// 否则，从左到右找到第一个 >1 的数字，把它替换成 0
			minFrom = -1;
			tmp = num;
			nn = n;
			while(nn > 0) {
				int d = tmp / nn;
				if(d > 1) {
					minFrom = d;
					break;
				}
				tmp %= nn;
				nn /= 10;
			}
			minTo = 0;
		}

		// 分别构造出 maxVal 和 minVal
		long maxVal = 0, minVal = 0;
		int pos = 0;
		while(num > 0) {
			int d = num % 10;
			long mul = 1;
			for(int i = 0; i < pos; ++i) mul *= 10;

			// 构造最大值：遇到 dmax 替换为 9
			maxVal += (d == dmax ? 9 : d) * mul;
			// 构造最小值：遇到 minFrom 替换为 minTo
			minVal += (d == minFrom ? minTo : d) * mul;

			num /= 10;
			++pos;
		}

		return int(maxVal - minVal);
	}
};

int main() {
	Solution sol;
	int num;
	num = 555;
	cout << sol.maxDiff(num) << endl; // 888
	num = 9;
	cout << sol.maxDiff(num) << endl; // 8
	num = 123456;
	cout << sol.maxDiff(num) << endl; // 820000
	num = 10000;
	cout << sol.maxDiff(num) << endl; // 80000
	num = 9288;
	cout << sol.maxDiff(num) << endl; // 8700
}