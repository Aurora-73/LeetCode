// Created: 2025-04-26
#include "MyUtils.h"

/*70. 爬楼梯
简单
相关标签
相关企业
提示
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？*/

class Solution {
public:
	int climbStairs(int n) {
		if(n == 1 || n == 2) {
			return n;
		}
		return climbStairs(n - 1) + climbStairs(n - 2);
	}
}; // 深度优先遍历

class Solution {
public:
	int climbStairs(int n) {
		if(n == 1)
			return 1;
		unique_ptr<int[]> dfs(new int[n + 1]);
		dfs[1] = 1, dfs[2] = 2;
		for(int i = 3; i <= n; ++i) {
			dfs[i] = dfs[i - 1] + dfs[i - 2];
		}
		return dfs[n];
	}
};

class Solution {
public:
	int climbStairs(int n) {
		if(n < 3)
			return n;
		int fn = 2, fn_1 = 1, fn_2 = 1;
		for(int i = 3; i <= n; ++i) {
			int temp = fn;
			fn = fn_1 + fn_2;
			fn_1 = temp;
			fn_2 = fn_1;
		}
		return fn;
	}
};

int main() {
	Solution sol;
}