// Created: 2025-05-16
#include "MyUtils.hpp"

/*35. 搜索插入位置
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
请必须使用时间复杂度为 O(log n) 的算法。*/

class Solution {
public:
	int searchInsert(vector<int> &nums, int target) {
		return lower_bound(nums.begin(), nums.end(), target) - nums.begin();
	}
};

class Solution {
public:
	int searchInsert(vector<int> &nums, int target) {
		int left = 0, right = nums.size(); // 左闭右开
		while(left < right) {
			int mid = left + (right - left) / 2;
			if(nums[mid] < target) {
				left = mid + 1; // mid 不满足，要舍弃
			} else {
				right = mid;
				// mid 满足，不舍弃（虽然在左闭右开的形式中舍弃了，但是返回时left = right其实没有舍弃，只是以后不在检查这个元素了）
			}
		}
		return left;
	}
}; // lower_bound 寻找第一个大于等于的元素

int main() {
	Solution sol;
}