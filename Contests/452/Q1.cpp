// Created: 2025-06-06
#include "MyDateGen.h"
#include "MyUtils.hpp"

/*Q1. 等积子集的划分方案
给你一个整数数组 nums，其中包含的正整数 互不相同 ，另给你一个整数 target。
请判断是否可以将 nums 分成两个非空、互不相交的子集 ，并且每个元素必须恰好属于一个子集，使得这两个子集中元素的乘积都等于 target。
如果存在这样的划分，返回 true；否则，返回 false。
子集 是数组中元素的一个选择集合。
示例 1：
	输入： nums = [3,1,6,8,4], target = 24
	输出： true
	解释：子集 [3, 8] 和 [1, 6, 4] 的乘积均为 24。因此，输出为 true 。
示例 2：
	输入： nums = [2,5,3,7], target = 15
	输出： false
	解释：无法将 nums 划分为两个非空的互不相交子集，使得它们的乘积均为 15。因此，输出为 false。
提示：
	3 <= nums.length <= 12
	1 <= target <= 1015
	1 <= nums[i] <= 100
	nums 中的所有元素互不相同。*/

class Solution {
public:
	bool checkEqualPartitions(vector<int> &nums, long long target) {
		// 两个非空
		if(target == 1) {
			for(auto x : nums) {
				if(x != 1) {
					return false;
				}
			}
			return true;
		}
		res = false;
		n = nums.size();
		dfs(nums, target, 1, 1, 0);
		return res;
	}

private:
	int n;
	bool res;
	void dfs(vector<int> &nums, long long target, long long left, long long right, int i) {
		if(res) return;
		if(i >= n) {
			if(left == target && right == target) {
				res = true;
			}
			return;
		}
		if(left <= target) {
			dfs(nums, target, left * nums[i], right, i + 1);
		}
		if(right <= target) {
			dfs(nums, target, left, right * nums[i], i + 1);
		}
	}
};

int main() {
	Solution sol;
	vector<int> nums { 3, 1, 6, 8, 4 };
	// cout << sol.checkEqualPartitions(nums, 24) << endl;
	// nums = { 2, 5, 3, 7 };
	// cout << sol.checkEqualPartitions(nums, 15) << endl;
	nums = { 10, 2, 20, 1 };
	cout << sol.checkEqualPartitions(nums, 20) << endl;
}
