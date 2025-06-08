// Created: 2025-06-08
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 386. 字典序排数
给你一个整数 n，按字典序返回范围 {1, n} 内所有整数。
你必须设计一个时间复杂度为 O(n) 且使用 O(1) 额外空间的算法。
示例 1：
	输入：n = 13
	输出：{1,10,11,12,13,2,3,4,5,6,7,8,9}
示例 2：
	输入：n = 2
	输出：{1,2}
提示：
	1 <= n <= 5 * 10 ^ 4 */

class Solution1 {
public:
	vector<int> lexicalOrder(int n) {
		vector<int> res;
		res.reserve(n); // 预分配空间以提高效率
		int current_num = 1;
		for(int i = 0; i < n; ++i) {
			res.push_back(current_num);

			// 尝试深入：current_num * 10
			// 使用 current_num <= n / 10 来防止 current_num * 10 溢出
			if(current_num <= n / 10) {
				current_num *= 10;
			} else {
				// 不能再深入，尝试移动到下一个兄弟节点或回溯
				// 如果 current_num 以 9 结尾，或者 current_num + 1 > n，则需要回溯
				while(current_num % 10 == 9 || current_num + 1 > n) {
					current_num /= 10; // 回溯到父节点
				}
				current_num += 1; // 移动到父节点的下一个兄弟节点
			}
		}
		return res;
	}
};
/*  对于一个整数 number，它的下一个字典序整数对应下面的规则：
1、尝试在 number 后面附加一个零，即 number × 10，
	如果 number × 10 ≤ n，那么说明 number × 10 是下一个字典序整数；
2、如果 number mod 10 = 9 或 number + 1 > n，那么说明末尾的数位已经搜索完成，
	退回上一位，即 number \= 10，然后继续判断直到 number mod10 != 9 且 number + 1 ≤ n 为止，那么 number + 1 是下一个字典序整数。
字典序最小的整数为 number=1，我们从它开始，然后依次获取下一个字典序整数，加入结果中，结束条件为已经获取到 n 个整数。 */

class Solution {
public:
	vector<int> lexicalOrder(int n) {
		string s = to_string(n);
		int cur = 1;
		vector<int> res;
		res.push_back(cur);
		for(int i = 0; i < n - 1; i++) {
			// 尝试添加末尾
			if(cur * 10 <= n) {
				cur *= 10;
			} else if(((cur % 10) < 9) && cur + 1 <= n) { // 尝试变化末尾
				cur++;
			} else { // 进位
				while((cur % 10) == 9 || cur >= n) {
					cur /= 10;
				}
				cur++;
			}
			res.push_back(cur);
		}
		return res;
	}
};

/*
 思路：把当前数字 cur 看作十进制字符串，不断对它“模拟进位”操作，
 每次产生字典序中的下一个最小数字。分三种情况：
  1. 下探一层：在末尾补 ‘0’（相当于字符串后面加一个字符 '0'）
  2. 同层右移：末尾数字 +1（如果不是 9 且不超过 n）
  3. 回溯进位：末尾是 9 或 +1 会越界，则去掉最低位，再尝试 +1
  重复以上步骤，直到生成 n 个数字。
 时间 O(n)，额外空间 O(1)。
*/
class Solution {
public:
	vector<int> lexicalOrder(int n) {
		vector<int> res;
		res.reserve(n);
		int cur = 1; // 当前值，初始为 1
		res.push_back(cur);
		// 依次生成剩余 n-1 个数字
		for(int i = 1; i < n; ++i) {
			// 1. 下探一层：在末尾补 ‘0’（cur*10 ≤ n 时最优先）
			if(cur * 10 <= n) {
				cur *= 10;
			}
			// 2. 同层右移：末尾不是 9 且 +1 ≤ n
			else if((cur % 10) < 9 && cur + 1 <= n) {
				++cur;
			}
			// 3. 回溯进位：末尾是 9 或者 +1 会超过 n
			else {
				// 不断去掉最低位（模拟向高位进位），
				// 直到能做一次 +1 且不超过 n
				while(cur % 10 == 9 || cur + 1 > n) {
					cur /= 10; // 去掉末尾一位
				}
				++cur; // 在新的末尾做 +1
			}

			res.push_back(cur);
		}

		return res;
	}
};

int main() {
	Solution sol;
	cout << sol.lexicalOrder(12) << endl;
}