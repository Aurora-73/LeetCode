// Created: 2025-06-08
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 474. 一和零
给你一个二进制字符串数组 strs 和两个整数 m 和 n。
请你找出并返回 strs 的最大子集的长度，该子集中 最多 有 m 个 0 和 n 个 1。
如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集。
示例 1：
	输入：strs = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
	输出：4
	解释：最多有 5 个 0 和 3 个 1 的最大子集是 {"10","0001","1","0"}，因此答案是 4。
	其他满足题意但较小的子集包括 {"0001","1"} 和 {"10","1","0"}。
	{"111001"} 不满足题意，因为它含 4 个 1，大于 n 的值 3。
示例 2：
	输入：strs = {"10", "0", "1"}, m = 1, n = 1
	输出：2
	解释：最大的子集是 {"0", "1"}，所以答案是 2。
提示：
	1 <= strs.length <= 600
	1 <= strs{i}.length <= 100
	strs{i}仅由"0" 和"1" 组成
	1 <= m, n <= 100 */

class Solution1 {
public:
	int findMaxForm(vector<string> &strs, int m, int n) {
		size = strs.size();
		count.resize(size);
		for(int i = 0; i < size; ++i) {
			int zero = 0;
			for(auto c : strs[i]) {
				if(c == '0') {
					++zero;
				}
			}
			count[i][0] = zero;
			count[i][1] = strs[i].size() - zero;
		}
		memo.assign(
		    m + 1, vector<vector<int>>(n + 1, vector<int>(size, numeric_limits<int>::max())));
		return dfs(m, n, 0);
	}

private:
	int size;
	vector<array<int, 2>> count;
	vector<vector<vector<int>>> memo;
	int dfs(int m, int n, int i) {
		if(i >= size || (m <= 0 && n <= 0)) {
			return 0;
		}
		if(memo[m][n][i] != numeric_limits<int>::max()) {
			return memo[m][n][i];
		}
		int res = dfs(m, n, i + 1);
		if(count[i][0] <= m && count[i][1] <= n) {
			res = max(res, dfs(m - count[i][0], n - count[i][1], i + 1) + 1);
		}
		memo[m][n][i] = res;
		return res;
	}
};

class Solution2 {
public:
	int findMaxForm(vector<string> &strs, int m, int n) {
		int size = strs.size();
		vector<array<int, 2>> count(size);
		for(int i = 0; i < size; ++i) {
			int zero = 0;
			for(auto c : strs[i]) {
				if(c == '0') {
					++zero;
				}
			}
			count[i][0] = zero;
			count[i][1] = strs[i].size() - zero;
		}
		vector<vector<vector<int>>> dp(size + 1, vector<vector<int>>(m + 1, vector<int>(n + 1)));
		for(int i = size - 1; i >= 0; --i) {
			for(int j = 0; j <= m; ++j) {
				for(int k = 0; k <= n; ++k) {
					dp[i][j][k] = dp[i + 1][j][k];
					if(j >= count[i][0] && k >= count[i][1]) {
						dp[i][j][k]
						    = max(dp[i][j][k], dp[i + 1][j - count[i][0]][k - count[i][1]] + 1);
					}
				}
			}
		}
		return dp[0][m][n];
	}
};

class Solution3 {
public:
	int findMaxForm(vector<string> &strs, int m, int n) {
		int size = strs.size();
		vector<vector<int>> curr(m + 1, vector<int>(n + 1));
		vector<vector<int>> prev(m + 1, vector<int>(n + 1));
		for(int i = size - 1; i >= 0; --i) {
			int zero = 0;
			for(auto c : strs[i])
				if(c == '0') ++zero;
			int one = strs[i].size() - zero;
			swap(curr, prev);
			for(int j = 0; j <= m; ++j) {
				for(int k = 0; k <= n; ++k) {
					curr[j][k] = prev[j][k];
					if(j >= zero && k >= one) {
						curr[j][k] = max(curr[j][k], prev[j - zero][k - one] + 1);
					}
				}
			}
		}
		return curr[m][n];
	}
};

class Solution {
public:
	int findMaxForm(vector<string> &strs, int m, int n) {
		static int dp[101][101];
		for(int i = 0; i <= m; ++i)
			for(int j = 0; j <= n; ++j) dp[i][j] = 0;
		for(auto &str : strs) {
			int zeroNum = 0, oneNum = 0;
			for(char c : str)
				if(c == '0') ++zeroNum;
			oneNum = str.size() - zeroNum;
			for(int i = m; i >= zeroNum; --i) {
				for(int j = n; j >= oneNum; --j) {
					int cand = dp[i - zeroNum][j - oneNum] + 1;
					if(cand > dp[i][j]) dp[i][j] = cand;
				}
			}
		}
		return dp[m][n];
	}
};

int main() {
	Solution sol;
	vector<string> strs;
	int m, n;
	strs = { "10", "0001", "111001", "1", "0" }, m = 5, n = 3;
	cout << sol.findMaxForm(strs, m, n) << endl; // 输出：4
	strs = { "10", "0", "1" }, m = 1, n = 1;
	cout << sol.findMaxForm(strs, m, n) << endl; // 输出：2
}