// Created: 2025-05-15
#include "MyUtils.h"

/*162. 寻找峰值
峰值元素是指其值严格大于左右相邻值的元素。
给你一个整数数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。
你可以假设 nums[-1] = nums[n] = -∞ 。
你必须实现时间复杂度为 O(log n) 的算法来解决此问题。
示例 1：
输入：nums = [1,2,3,1]
输出：2
解释：3 是峰值元素，你的函数应该返回其索引 2。
示例 2：
输入：nums = [1,2,1,3,5,6,4]
输出：1 或 5 
解释：你的函数可以返回索引 1，其峰值元素为 2；
     或者返回索引 5， 其峰值元素为 6。
提示：
1 <= nums.length <= 1000
-231 <= nums[i] <= 231 - 1
对于所有有效的 i 都有 nums[i] != nums[i + 1]*/

class Solution {
public:
	int findPeakElement(vector<int> &nums) {
		int max_val = INT_MIN, index = -1, n = nums.size();
		for(int i = 0; i < n; ++i) {
			if(nums[i] >= max_val) {
				max_val = nums[i];
				index = i;
			}
		}
		return index;
	}
}; // 直接找最大值也是对的，但是 O(n)

class Solution1 {
public:
	int findPeakElement(vector<int> &nums) {
		int n = nums.size(), left = -1, right = n; // 左开又开
		auto get_val = [&](int i) -> long long {
			try {
				return nums.at(i);
			} catch(const std::exception &e) {
				return std::numeric_limits<long long>::lowest();
			}
		};
		while(left + 1 < right) {
			int mid = left + (right - left) / 2;
			if(get_val(mid) > get_val(mid - 1) && get_val(mid) > get_val(mid + 1)) {
				return mid;
			} else if(get_val(mid) < get_val(mid - 1) && get_val(mid) < get_val(mid + 1)) {
				right = mid;
			} else if(get_val(mid) > get_val(mid - 1)) {
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
		if(n == 1 || nums[1] < nums[0]) {
			return 0;
		}
		if(nums[n - 2] < nums[n - 1]) {
			return n - 1;
		} // 先处理边界，这样就不需要考虑负无穷的事了
		int left = 1, right = n - 2;
		while(left <= right) {
			int mid = left + (right - left) / 2;
			if(nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) {
				return mid;
			}
			if(nums[mid] > nums[mid - 1]) {
				// 上坡，峰值在右边
				left = mid + 1;
			} else {
				// 下坡，峰值在左边
				right = mid - 1;
			}
		}
		// 最终 left > right，left 即为一个合法峰值的位置
		return left;
	}
};

int main() {
	Solution sol;
	vector<int> nums = { -2147483648, -2147483647 };
	cout << sol.findPeakElement(nums);
}