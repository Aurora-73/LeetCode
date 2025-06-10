// Created: 2025-06-10
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 790. 多米诺和托米诺平铺
有两种形状的瓷砖：一种是2 x 1 的多米诺形，另一种是形如"L" 的托米诺形。
两种形状都可以旋转。
给定整数 n，返回可以平铺2 x n 的面板的方法的数量。返回对10^9+ 7取模的值。
平铺指的是每个正方形都必须有瓷砖覆盖。两个平铺不同，
当且仅当面板上有四个方向上的相邻单元中的两个，使得恰好有一个平铺有一个瓷砖占据两个正方形。
示例 1:
	输入: n = 3
	输出: 5
	解释: 五种不同的方法如上所示。
示例 2:
	输入: n = 1
	输出: 1
提示：
	1 <= n <= 1000 */

class Solution1 {
public:
	int numTilings(int n) {
		const long long mod = 1e9 + 7;
		vector<array<int, 4>> dp(n + 1);
		dp[0][3] = 1;
		for(int i = 1; i <= n; ++i) {
			dp[i][0] = dp[i - 1][3];
			dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % mod;
			dp[i][2] = (dp[i - 1][0] + dp[i - 1][1]) % mod;
			dp[i][3]
			    = ((dp[i - 1][0] + dp[i - 1][1]) % mod + (dp[i - 1][2] + dp[i - 1][3]) % mod) % mod;
		}
		return dp.back().back();
	}
};
// 假设第 i 列右侧的元素都已经铺满，则第i列存在 {00, 01, 10, 11} 四种情况
// 设形成第 i 列右侧铺满，第 i 列为 state 的平铺方式个数为dp[i][state]
// 则结果是要求 dp[n][3] 或 dp[n + 1][0]
// 然后考虑dp的递推:
// dp[i][0] 就是 dp[i - 1][3]
// dp[i][1] 有两种可能 1、dp[i - 1][0] 补充一个托米诺     2、dp[i - 1][2] 补充一个多米诺
// dp[i][2] 有两种可能 1、dp[i - 1][0] 补充一个托米诺     2、dp[i - 1][1] 补充一个多米诺
// dp[i][3] 有种四可能 1、dp[i - 1][0] 补充两个托米诺     2、dp[i - 1][1] 补充一个多米诺
//                    3、dp[i - 1][2] 补充一个多米诺     4、dp[i - 1][3] 补充一个托米诺

class Solution2 {
public:
	int numTilings(int n) {
		const long long mod = 1e9 + 7;
		array<int, 4> curr { 0, 0, 0, 1 }, prev;
		for(int i = 1; i <= n; ++i) {
			std::swap(curr, prev);
			curr[0] = prev[3];
			curr[1] = (prev[0] + prev[2]) % mod;
			curr[2] = (prev[0] + prev[1]) % mod;
			curr[3] = ((prev[0] + prev[1]) % mod + (prev[2] + prev[3]) % mod) % mod;
		}
		return curr.back();
	}
};

int res[1001];
int get_res = []() {
	const long long mod = 1e9 + 7;
	res[0] = 1;
	array<int, 3> curr { 0, 0, 0 }, prev;
	for(int i = 1; i <= 1000; ++i) {
		std::swap(curr, prev);
		curr[0] = res[i - 1];
		curr[1] = (prev[0] + prev[2]) % mod;
		curr[2] = (prev[0] + prev[1]) % mod;
		res[i] = ((prev[0] + prev[1]) % mod + (prev[2] + res[i - 1]) % mod) % mod;
	}
	return 1;
}();

class Solution3 {
public:
	int numTilings(int n) {
		return res[n];
	}
}; // 可以在进入 solution 之前打表

// 矩阵快速幂，有上面的递推公式可知：
// curr = [[0, 0, 0, 1], [1, 0, 1, 0], [1, 1, 0, 0], [1, 1, 1, 1]] * prev
// curr = ([[0, 0, 0, 1], [1, 0, 1, 0], [1, 1, 0, 0], [1, 1, 1, 1]]) ^ n * [0, 0, 0, 1]
class Solution {
public:
	int numTilings(int n) {
		vector<vector<long long>> mat, matn;
		mat = { { 0, 0, 0, 1 }, { 1, 0, 1, 0 }, { 1, 1, 0, 0 }, { 1, 1, 1, 1 } };
		matn = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
		while(n) {
			if(n & 1) {
				matn = mulMatrix(matn, mat);
			}
			mat = mulMatrix(mat, mat);
			n >>= 1;
		}
		return matn[3][3];
	}

private:
	const long long mod = 1e9 + 7;
	vector<vector<long long>> mulMatrix(
	    const vector<vector<long long>> &m1, const vector<vector<long long>> &m2) {
		int n1 = m1.size(), n2 = m2.size(), n3 = m2[0].size();
		vector<vector<long long>> res(n1, vector<long long>(n3));
		for(int i = 0; i < n1; i++) {
			for(int k = 0; k < n3; k++) {
				for(int j = 0; j < n2; j++) {
					res[i][k] = (res[i][k] + m1[i][j] * m2[j][k]) % mod;
				}
			}
		}
		return res;
	}
};

int main() {
	Solution sol;
	cout << sol.numTilings(3) << endl; // 5
	cout << sol.numTilings(1) << endl; // 1
}