// Created: 2025-06-07
#include "MyUtils.hpp"

/*  279. 完全平方数
给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。
完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。
例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。*/

class Solution1 {
public:
	int numSquares(int n) {
		memo.resize(n + 1, -1);
		return dfs(n);
	}

private:
	vector<int> memo;
	int dfs(int n) {
		if(n < 0) {
			return INT_MAX >> 2;
		}
		if(n == 0 || n == 1) {
			return n;
		}
		if(memo[n] != -1) {
			return memo[n];
		}
		int maxSq = static_cast<int>(std::sqrt(n));
		if(maxSq * maxSq == n) {
			memo[n] = 1;
			return 1;
		}
		int minTimes = INT_MAX >> 2;
		for(int i = maxSq; i > 0; --i) {
			minTimes = min(minTimes, dfs(n - i * i) + 1);
		}
		memo[n] = minTimes;
		return minTimes;
	}
};

class Solution2 {
public:
	int numSquares(int n) {
		vector<int> dp(n + 1, INT_MAX);
		for(int i = 1; i * i <= n; ++i) {
			dp[i * i] = 1;
		}
		if(dp.back() != INT_MAX) {
			return dp.back();
		}
		dp[0] = 0;
		for(int i = 1; i <= n; ++i) {
			if(dp[i] == INT_MAX) {
				for(int j = 1; j * j <= i; --j) {
					dp[i] = min(dp[i], 1 + dp[i - j * j]);
				}
			}
		}
		return dp.back();
	}
};

int RES[10001];

int a = []() {
	RES[0] = 0;
	for(int i = 1; i <= 10000; ++i) {
		int minn = INT_MAX;
		for(int j = 1; j * j <= i; ++j) {
			minn = min(minn, RES[i - j * j] + 1);
		}
		RES[i] = minn;
	}
	return 0;
}(); // 全局区，只运行一次

class Solution {
public:
	int numSquares(int n) {
		return RES[n];
	}
};

/* 
class Solution {
public:
	int numSquares(int n) {
		return Squares[n];
	}

private:
	inline static constexpr array<int, 10001> Squares = []() constexpr {
		array<int, 10001> arr {};
		arr[0] = 0;
		for(int i = 1; i <= 10000; ++i) {
			int minn = INT_MAX;
			for(int j = 1; j * j <= i; ++j) {
				minn = minn < (arr[i - j * j] + 1) ? minn : (arr[i - j * j] + 1);
			}
			arr[i] = minn;
		}
		return arr;
	}(); // 编译期运行
}; 

表达式必须含有常量值C/C++(28)
279N.PerfectSquares.cpp(92, 54): 表达式未折叠为常量，因为 constexpr 函数调用过于复杂 */

int main() {
	Solution sol;
}