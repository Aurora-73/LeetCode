// Created: 2025-06-17
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 152. 乘积最大子数组
给你一个整数数组 nums，请你找出数组中乘积最大的非空连续 子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。
测试用例的答案是一个32位的整数。
示例 1:
	输入: nums = {2,3,-2,4}
	输出: 6
	解释:子数组 {2,3} 有最大乘积 6。
示例 2:
	输入: nums = {-2,0,-1}
	输出: 0
	解释:结果不能为 2, 因为 {-2,-1} 不是子数组。
提示:
	1 <= nums.length <= 2 * 10^4
	-10 <= nums{i} <= 10
	nums 的任何子数组的乘积都 保证是一个 32位 整数 */

class SolutionMy {
public:
	int maxProduct(vector<int> &nums) {
		int n = nums.size();
		vector<int> ZeroIndex { -1 };
		for(int i = 0; i < n; ++i) {
			if(!nums[i]) {
				ZeroIndex.push_back(i);
			}
		}
		ZeroIndex.push_back(n);
		if(ZeroIndex.size() - 2 == nums.size()) return 0;
		vector<int> suff(n); // 前缀积，包含本格的
		for(int i = 0; i < n; ++i) {
			if(i != 0 && suff[i - 1] != 0) {
				suff[i] = suff[i - 1] * nums[i];
			} else {
				suff[i] = nums[i];
			}
		}
		int m = ZeroIndex.size(), maxP = (m - 2) ? 0 : numeric_limits<int>::min();
		for(int i = 0; i < m - 1; ++i) {
			int left = ZeroIndex[i] + 1, right = ZeroIndex[i + 1]; // 左闭右开
			int maxNeg = 1;                                        // 最小正前缀和最大负前缀
			while(left < right) {
				if(suff[left] > 0) {
					maxP = max(maxP, suff[left]);
				} else {
					maxP = max(maxP, suff[left] / maxNeg);
					if(maxNeg == 1 || suff[left] > maxNeg) {
						maxNeg = suff[left];
					}
				}
				++left;
			}
		}
		return maxP;
	}
};
// 以0为分割，求前缀积，对于每个子数组，正数的最大积就是其本身(最小的正数前缀是1)
// 负数的最大前缀积需要除以之前的最大负数（分母绝对值尽可能小）

class Solution1 {
public:
	int maxProduct(const vector<int> &nums) {
		int n = nums.size();
		// 初始化结果为第一个元素
		int res = nums[0];
		// imax：以 i 结尾的最大子数组乘积
		// imin：以 i 结尾的最小子数组乘积
		int imax = nums[0], imin = nums[0];

		// 从第二个元素开始，依次更新 imax/imin 和 全局最优 res
		for(int i = 1; i < n; ++i) {
			int x = nums[i];

			// 如果当前元素为负，需要先交换 imax 和 imin
			// 因为负数会把最大值变最小，把最小值变最大
			if(x < 0) {
				std::swap(imax, imin);
			}

			// 更新以 i 结尾的最大乘积：
			// 要么就是从头重新开始 x，要么就是接在之前的 imax 之后 imax * x
			imax = std::max(x, imax * x);
			// 同理更新以 i 结尾的最小乘积
			imin = std::min(x, imin * x);

			// 更新全局答案
			res = std::max(res, imax);
		}

		return res;
	}
};
/* 推荐的「动态规划 + 贪心」经典解法
      思路非常直观：我们只需一次遍历，维护到当前位置为止的「最大乘积结尾值」(imax) 和「最小乘积结尾值」(imin)，并随时更新全局最大值 res 即可。
   为什么要维护两个值？
      因为遇到负数时，当前的最大乘积可能来源于之前的最小乘积（负×负=正），同样最小乘积也可能来源于之前的最大乘积。*/

class Solution {
public:
	int maxProduct(vector<int> &nums) {
		int ans = numeric_limits<int>::min(); // 注意答案可能是负数
		int f_max = 1, f_min = 1;
		for(int x : nums) {
			int mx = f_max;
			f_max = max({ f_max * x, f_min * x, x });
			f_min = min({ mx * x, f_min * x, x });
			ans = max(ans, f_max);
		}
		return ans;
	}
}; // 空间优化

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 3, -1, 4 };
	cout << sol.maxProduct(nums) << endl; // 4
	nums = { -2 };
	cout << sol.maxProduct(nums) << endl; // -2
	nums = { 2, 3, -2, 4 };
	cout << sol.maxProduct(nums) << endl; // 6
	nums = { -2, 0, -1 };
	cout << sol.maxProduct(nums) << endl; // 0
}