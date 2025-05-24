// Created: 2025-05-20
#include "MyUtils.h"

/*  198. 打家劫舍
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，
影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
1 <= nums.length <= 100
0 <= nums[i] <= 400   */

class Solution1 {
public:
	int rob(vector<int> &nums) {
		return dfs(nums, 0);
	}
	int dfs(vector<int> &nums, int begin) {
		if(begin >= nums.size())
			return 0;
		return max(nums[begin] + dfs(nums, begin + 2), dfs(nums, begin + 1));
	}
};
// 基础DFS，从当前开始打劫的最大金额分为两种可能：1、打劫当前的 + 从当前后面两个开始的 2、不打劫当前的 + 从当前下一个开始的

class Solution2 {
public:
	int rob(vector<int> &nums) {
		dp.resize(nums.size(), 0);
		return dfs(nums, 0);
	}

private:
	vector<int> dp;
	int dfs(vector<int> &nums, int begin) {
		if(begin >= nums.size())
			return 0;
		if(dp[begin] == 0) {
			dp[begin] = max(nums[begin] + dfs(nums, begin + 2), dfs(nums, begin + 1));
		}
		return dp[begin];
	}
};
// 记忆化存储，使用dp数组保存已经计算过的开始值，减少重复计算

class Solution3 {
public:
	int rob(vector<int> &nums) {
		vector<int> dp(nums.size() + 2, 0);
		for(int i = nums.size() - 1; i >= 0; --i) {
			dp[i] = max(nums[i] + dp[i + 2], dp[i + 1]);
		}
		return dp[0];
	}
};
// 记忆化存储，去掉递归，使用倒序计算

class Solution4 {
public:
	int rob(vector<int> &nums) {
		int now, pre = 0, prepre = 0;
		for(int i = nums.size() - 1; i >= 0; --i) {
			now = max(nums[i] + prepre, pre);
			prepre = pre;
			pre = now;
		}
		return now;
	}
};
// 记忆化存储，去掉dp数组，交替计算now pre prepre

int main() {
	Solution4 sol;
}