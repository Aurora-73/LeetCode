// Created: 2025-07-01
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 185. 统计结果概率
你选择掷出 num 个色子，请返回所有点数总和的概率。
你需要用一个浮点数数组返回答案，其中第 i 个元素代表这 num 个骰子所能掷出的点数集合中第 i 小的那个的概率。
示例 1：
	输入：num = 3
	输出：{0.00463,0.01389,0.02778,0.04630,0.06944,0.09722,0.11574,0.12500,0.12500,0.11574,0.09722,0.06944,0.04630,0.02778,0.01389,0.00463}
示例2：
	输入：num = 5
	输出: {0.00013,0.00064,0.00193,0.00450,0.00900,0.01620,0.02636,0.03922,0.05401,0.06944,0.08372,0.09452,0.10031,0.10031,0.09452,0.08372,0.06944,0.05401,0.03922,0.02636,0.01620,0.00900,0.00450,0.00193,0.00064,0.00013}
提示：
	1 <= num <= 11 */

class Solution1 {
public:
	vector<double> statisticsProbability(int num) {
		vector<double> now(6, 1.0 / 6), prev;
		for(int i = 2; i <= num; ++i) {
			prev = std::move(now);
			now.resize(5 * i + 1);
			for(int j = i; j < 6 * i + 1; ++j) {
				double p = 0;
				for(int k = 1; k < 7; ++k) {
					int index = j - k - i + 1;
					if(index >= 0 && index < prev.size()) {
						p += prev[index] / 6;
					}
				}
				now[j - i] = p;
			}
		}
		return now;
	}
};

class Solution2 {
public:
	vector<double> statisticsProbability(int num) {
		vector<double> all(7, 1.0 / 6);
		all.resize(num * 6 + 1); // 值与下标对应，无偏移
		for(int i = 2; i <= num; ++i) {
			for(int j = 6 * i; j >= i; --j) { // 逆序赋值，防止覆盖
				all[j] = 0;
				int l = max(1, j - 6 * i + 6), r = min(6, j + 1 - i);
				for(int k = l; k <= r; ++k) {
					all[j] += all[j - k] / 6;
				}
			}
		}
		return { all.begin() + num, all.end() };
	}
};

class Solution {
public:
	vector<double> statisticsProbability(int num) {
		vector<double> dp(6, 1.0 / 6.0);
		for(int i = 2; i <= num; i++) {
			vector<double> tmp(5 * i + 1, 0);
			for(int j = 0; j < dp.size(); j++) {
				for(int k = 0; k < 6; k++) {
					tmp[j + k] += dp[j] / 6.0;
				}
			}
			dp = std::move(tmp);
		}
		return dp;
	}
}; // 不要用减法，用加法，概率累积，这样就没有复杂的下标转换了

int main() {
	Solution sol;
	int num;
	num = 3;
	cout << boolalpha;
	cout << sol.statisticsProbability(num) << endl;
	num = 5;
	cout << sol.statisticsProbability(num) << endl;
}