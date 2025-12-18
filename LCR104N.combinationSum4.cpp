// Created: 2025-12-18
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个由 不同正整数组成的数组 nums，和一个目标整数 target。
请从 nums 中找出并返回总和为 target 的元素组合的个数。
数组中的数字可以在一次排列中出现任意次，但是顺序不同的序列被视作不同的组合。
题目数据保证答案符合 32 位整数范围。
示例 1：
	输入：nums = {1,2,3}, target = 4
	输出：7
	解释：
	所有可能的组合为：
	(1, 1, 1, 1)
	(1, 1, 2)
	(1, 2, 1)
	(1, 3)
	(2, 1, 1)
	(2, 2)
	(3, 1)
	请注意，顺序不同的序列被视作不同的组合。
示例 2：
	输入：nums = {9}, target = 3
	输出：0
提示：
	1 <= nums.length <= 200
	1 <= nums{i} <= 1000
	nums 中的所有元素 互不相同
	1 <= target <= 1000
	进阶：如果给定的数组中含有负数会发生什么？问题会产生何种变化？如果允许负数出现，需要向题目中添加哪些限制条件？ */

class Solution1 {
public:
	int combinationSum4(vector<int> &nums, int target) {
		return dfs(nums, target);
	}

private:
	int dfs(vector<int> &nums, int target) {
		if(target == 0) return 1; // 正好凑出target，一种组合
		if(target < 0) return 0;  // 超过target，不合法
		int res = 0;
		for(int num : nums) {
			res += dfs(nums, target - num);
		} // 选择num后继续凑剩余的target-num
		return res;
	}
}; // 深度优先遍历，假设存在一个虚拟的根节点，子节点表示后续加和的值，因为是在树上搜索，树上每条路径都不相同，因此不会有重复的组合
/*target=4
    ├─ choose 1 → target=3
    │   ├─ choose 1 → target=2
    │   │   ├─ choose 1 → target=1
    │   │   │   ├─ choose 1 → target=0  ✅ (1,1,1,1)
    │   │   │   ├─ choose 2 → target=-1 ❌
    │   │   │   └─ choose 3 → target=-2 ❌
    │   │   ├─ choose 2 → target=0  ✅ (1,1,2)
    │   │   └─ choose 3 → target=-1 ❌
    │   ├─ choose 2 → target=1
    │   │   ├─ choose 1 → target=0 ✅ (1,2,1)
    │   │   ├─ choose 2 → target=-1 ❌
    │   │   └─ choose 3 → target=-2 ❌
    │   └─ choose 3 → target=0 ✅ (1,3)
    ├─ choose 2 → target=2
    │   ├─ choose 1 → target=1
    │   │   ├─ choose 1 → target=0 ✅ (2,1,1)
    │   │   ├─ choose 2 → target=-1 ❌
    │   │   └─ choose 3 → target=-2 ❌
    │   └─ choose 2 → target=0 ✅ (2,2)
    │   └─ choose 3 → target=-1 ❌
    └─ choose 3 → target=1
        ├─ choose 1 → target=0 ✅ (3,1)
        ├─ choose 2 → target=-1 ❌
        └─ choose 3 → target=-2 ❌  */

class Solution {
public:
	int combinationSum4(vector<int> &nums, int target) {
		vector<int> dp(target + 1, 0);
		dp[0] = 1;
		for(int i = 1; i < target + 1; ++i) {
			for(int num : nums) {
				if(num <= i) dp[i] += min(INT_MAX - dp[i], dp[i - num]);
			}
		}
		return dp.back();
	}
}; // 动态规划，dp[i]表示和为target的组合总数

int main() {
	Solution sol;
	vector<int> nums;
	int target;
	nums = { 1, 2, 3 }, target = 4;
	cout << sol.combinationSum4(nums, target) << endl;
	nums = { 9 }, target = 3;
	cout << sol.combinationSum4(nums, target) << endl;
}
