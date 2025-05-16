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

class Solution1 {
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

class Solution2 {
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

class Solution3 {
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

class Solution4 { // 左闭右开
public:
	int findPeakElement(vector<int> &nums) {
		int left = 0, right = nums.size() - 1; // 虽然是左闭右开但是 right = nums.size() - 1
		while(left < right) {
			int mid = left + (right - left) / 2;
			// 与右边比较，决定搜索方向
			if(nums[mid] > nums[mid + 1]) {
				// 峰值在左边（包含mid）
				right = mid;
			} else {
				// 峰值在右边
				left = mid + 1;
			}
		}
		return left; // 或 return right 都可以，最终 left == right
	}
}; // 寻找第一个满足 nums[mid] > nums[mid + 1]的元素，也就是说之前的元素均递增，之后递减，由于两侧边界都是负无穷，因此总体上满足find_first的二分要求

class Solution5 {
public:
	int findPeakElement(vector<int> &nums) {
		auto cond = [&](vector<int>::iterator &mid) { return *mid > *(mid + 1); };
		return my_find_first(nums.begin(), nums.end() - 1, cond) - nums.begin();
	}
};
/*我们来分析：
给定数组满足 nums[-1] = nums[n] = -∞；
如果当前 nums[mid] > nums[mid + 1]，说明我们在一个“下降趋势”的右边，峰值可能就在 mid 或它左边；
如果 nums[mid] < nums[mid + 1]，说明我们在“上升趋势”，峰值一定在右边（根据题设一定存在峰值）；
于是你会发现：这正是典型的“左边都不满足，右边都满足”的结构 —— 也就是你模板 find_first 的使用场景。*/

int main() {
	Solution5 sol;
	vector<int> nums = { -2147483648, -2147483647 };
	cout << sol.findPeakElement(nums);
}