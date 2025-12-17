// Created: 2025-12-17
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 一个专业的小偷，计划偷窃一个环形街道上沿街的房屋，每间房内都藏有一定的现金。
这个地方所有的房屋都 围成一圈，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，
相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
给定一个代表每个房屋存放金额的非负整数数组 nums，请计算在不触动警报装置的情况下，今晚能够偷窃到的最高金额。
示例1：
输入：nums = {2,3,2}
输出：3
解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。
示例 2：
	输入：nums = {1,2,3,1}
	输出：4
	解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
	    偷窃到的最高金额 = 1 + 3 = 4。
示例 3：
	输入：nums = {0}
	输出：0
提示：
	1 <= nums.length <= 100
	0 <= nums{i} <= 1000 */

class Solution {
public:
	int rob(vector<int> &nums) {
		if(nums.size() < 3) {
			return ranges::max(nums);
		}
		int n = nums.size(), prev1 = 0, curr1 = 0;
		for(int i = 0; i < n - 1; ++i) {
			int next1 = max(curr1, prev1 + nums[i]);
			prev1 = curr1;
			curr1 = next1;
		}
		int prev2 = 0, curr2 = 0;
		for(int i = 1; i < n; ++i) {
			int next2 = max(curr2, prev2 + nums[i]);
			prev2 = curr2;
			curr2 = next2;
		}
		return max(curr1, curr2);
	}
};
// 由于首位相连，因此对于少于3个房子的情况只能盗窃最多的那个房子;
// 对于更多的情况，如果盗窃了第一件房子，则不能盗窃最后一间房子，因此此时盗窃范围是[0, n  - 2];
// 同理，盗窃最后一间房子则不能盗窃第一间，此时盗窃范围是[1, n - 1];

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 2, 3, 2 };
	cout << sol.rob(nums) << endl;
	nums = { 1, 2, 3, 1 };
	cout << sol.rob(nums) << endl;
}