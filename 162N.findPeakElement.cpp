// Created: 2025-05-15
#include "MyUtils.hpp"

/* 162. 寻找峰值
峰值元素是指其值严格大于左右相邻值的元素。
给你一个整数数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。
你可以假设 nums{-1} = nums{n} = -∞。
你必须实现时间复杂度为 O(log n) 的算法来解决此问题。
示例 1：
	输入：nums = {1,2,3,1}
	输出：2
	解释：3 是峰值元素，你的函数应该返回其索引 2。
示例 2：
	输入：nums = {1,2,1,3,5,6,4}
	输出：1 或 5 
	解释：你的函数可以返回索引 1，其峰值元素为 2；
	     或者返回索引 5， 其峰值元素为 6。
提示：
	1 <= nums.length <= 1000
	-231 <= nums{i} <= 231 - 1
	对于所有有效的 i 都有 nums{i} != nums{i + 1}*/

class Solution1 {
public:
	int findPeakElement(vector<int> &nums) {
		int n = nums.size(), left = -1, right = n; // 左开又开
		auto get_val = [&](int i) -> long long {
			if(i >= 0 && i < n) {
				return nums[i];
			} else {
				return std::numeric_limits<long long>::lowest();
			}
		};
		while(left + 1 < right) {
			int mid = left + (right - left) / 2;
			long long mid_val = get_val(mid), prev_val = get_val(mid - 1),
			          next_val = get_val(mid + 1);
			if(mid_val > prev_val && mid_val > next_val) {
				return mid;
			} else if(mid_val < prev_val && mid_val < next_val) {
				right = mid;
			} else if(mid_val > prev_val) {
				left = mid;
			} else {
				right = mid;
			}
		}
		return right;
	}
}; // 使用不在int范围内的更小的值表示负无穷

class Solution2 {
public:
	int findPeakElement(vector<int> &nums) {
		int n = nums.size();
		if(n < 2 || nums[1] < nums[0]) {
			return 0;
		}
		if(nums[n - 2] < nums[n - 1]) {
			return n - 1;
		}
		int left = 1, right = n - 1; // 左闭右开
		while(left < right) {
			int mid = left + (right - left) / 2;
			if(nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) {
				return mid;
			} else if(nums[mid] < nums[mid + 1]) {
				// 上升， left移动
				left = mid + 1;
			} else {
				right = mid; // 左闭右开
				             // mid小于两边则两边各有一个峰值
			}
		}
		return -1; // 不可能发生这种情况
	}
};

class Solution {
public:
	int findPeakElement(vector<int> &nums) {
		int n = nums.size(), l = 0, r = n;
		auto cond = [&](int id) {
			if(id == n - 1) return true;
			if(id == -1) return false;
			return nums[id] > nums[id + 1];
		};
		while(l < r) {
			int mid = l + (r - l) / 2, prev = mid - 1;
			if(cond(mid)) {
				if(!cond(prev)) {
					return mid;
				} else {
					r = mid;
				}
			} else {
				l = mid + 1;
			}
		}
		return l;
	}
}; // 在左右两侧都是负无穷的情况下，寻找第一个满足 nums[mid] > nums[mid + 1]的元素
// 也就是说之前的元素均递增，之后递减，由于两侧边界都是负无穷，因此总体上满足find_first的二分要求
/* 我们来分析：给定数组满足 nums[-1] = nums[n] = -∞；
如果当前 nums[mid] > nums[mid + 1]，说明我们在一个“下降趋势”的右边，峰值 就是mid 或 在它左边；
如果 nums[mid] < nums[mid + 1]，说明我们在“上升趋势”，峰值一定在右边（根据题设一定存在峰值）；
于是你会发现：这正是典型的“左边都不满足，右边都满足”的结构 */

int main() {
	Solution sol;
	vector<int> nums;

	nums = { -2147483648, -2147483647 };
	cout << sol.findPeakElement(nums);
}