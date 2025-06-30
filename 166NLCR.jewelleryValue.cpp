// Created: 2025-06-30
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 166. 珠宝的最高价值
现有一个记作二维矩阵 frame 的珠宝架，其中 frame{i}{j} 为该位置珠宝的价值。
拿取珠宝的规则为：
	只能从架子的左上角开始拿珠宝
	每次可以移动到右侧或下侧的相邻位置
	到达珠宝架子的右下角时，停止拿取
注意：珠宝的价值都是大于 0 的。除非这个架子上没有任何珠宝，比如 frame = {{0}}。
示例 1：
	输入：frame = {{1,3,1},{1,5,1},{4,2,1}}
	输出：12
	解释：路径 1→3→5→2→1 可以拿到最高价值的珠宝
提示：
	0 < frame.length <= 200
	0 < frame{0}.length <= 200 */

class Solution1 {
public:
	int jewelleryValue(vector<vector<int>> &frame) {
		int m = frame.size(), n = frame[0].size();
		vector<vector<int>> dp(m, vector<int>(n));
		dp.back().back() = frame.back().back();
		for(int i = m - 2; i >= 0; --i) {
			dp[i][n - 1] = dp[i + 1][n - 1] + frame[i][n - 1];
		}
		for(int j = n - 2; j >= 0; --j) {
			dp[m - 1][j] = dp[m - 1][j + 1] + frame[m - 1][j];
		}
		for(int i = m - 2; i >= 0; --i) {
			for(int j = n - 2; j >= 0; --j) {
				dp[i][j] = max(dp[i][j + 1], dp[i + 1][j]) + frame[i][j];
			}
		}
		return dp[0][0];
	}
};

class Solution {
public:
	int jewelleryValue(vector<vector<int>> &frame) {
		int m = frame.size(), n = frame[0].size();
		vector<int> dp = frame.back(); // 当前行，第二维
		for(int i = n - 2; i >= 0; --i) {
			dp[i] += dp[i + 1];
		}
		for(int i = m - 2; i >= 0; --i) {
			dp.back() += frame[i].back();
			for(int j = n - 2; j >= 0; --j) {
				dp[j] = max(dp[j + 1], dp[j]) + frame[i][j];
			}
		}
		return dp[0];
	}
};

int main() {
	Solution sol;
	vector<vector<int>> frame;
	frame = { { 1, 3, 1 }, { 1, 5, 1 }, { 4, 2, 1 } };
	cout << sol.jewelleryValue(frame) << endl; // 12
}