// Created: 2025-06-25
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 154. 寻找旋转排序数组中的最小值 II
已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次 旋转 后，得到输入数组。
例如，原数组 nums = {0,1,4,4,5,6,7} 在变化后可能得到：
	若旋转 4 次，则可以得到 {4,5,6,7,0,1,4}
	若旋转 7 次，则可以得到 {0,1,4,4,5,6,7}
注意，
数组 {a{0}, a{1}, a{2}, ..., a{n-1}} 旋转一次 的结果为数组 {a{n-1}, a{0}, a{1}, a{2}, ..., a{n-2}}。
给你一个可能存在 重复 元素值的数组 nums，它原来是一个升序排列的数组，
并按上述情形进行了多次旋转。请你找出并返回数组中的 最小元素。
你必须尽可能减少整个过程的操作步骤。
示例 1：
	输入：nums = {1,3,5}
	输出：1
示例 2：
	输入：nums = {2,2,2,0,1}
	输出：0
提示：
	n == nums.length
	1 <= n <= 5000
	-5000 <= nums{i} <= 5000
	nums 原来是一个升序排序的数组，并进行了 1 至 n 次旋转
进阶：这道题与 寻找旋转排序数组中的最小值 类似，但 nums 可能包含重复元素。
允许重复会影响算法的时间复杂度吗？会如何影响，为什么？ */
// 与 153N 不同，与 128ELCR 相同

class Solution1 {
public:
	int findMin(vector<int> &nums) {
		int i = 0, j = nums.size() - 1;
		while(i < j) {
			int m = (i + j) / 2;
			if(nums[m] > nums[j])
				i = m + 1;
			else if(nums[m] < nums[j])
				j = m;
			else {
				--j;
			}
		}
		return nums[i];
	}
}; // 寻找递增区间的起点

class Solution {
public:
	int findMin(vector<int> &nums) {
		int left = 0, right = nums.size() - 1; // 左闭右闭
		while(left < right) {
			int mid = left + (right - left) / 2;
			if(nums[mid] == nums[right]) {
				right--;
			} else if(nums[mid] < nums[right]) {
				right = mid;
			} else {
				left = mid + 1;
			}
		}
		return nums[left];
	}
};

class Solution {
public:
	int findMin(vector<int> &nums) {
		int n = nums.size();
		int l = 0, r = n; // [l, r) 初始为 [0, n)
		while(r > l) {
			// 取“偏左中点”，保证两元素时 mid==l
			int mid = l + (r - l - 1) / 2;
			// 比较 nums[mid] 和当前区间最后一个元素 nums[r-1]
			if(nums[mid] > nums[r - 1]) {
				// 最小值在右半区间 (mid, r-1] → [mid+1, r)
				l = mid + 1;
			} else if(nums[mid] < nums[r - 1]) {
				// 最小值在左半区间 [l, mid] → [l, mid+1)
				r = mid + 1;
			} else {
				// 相等时去掉冗余尾元素
				--r;
			}
		}
		return nums[l];
	}
};

class Solution {
public:
	int findMin(vector<int> &nums) {
		int i = 0, j = nums.size();
		while(i < j - 1 && nums[i] == nums.back()) ++i;
		while(i < j) {
			int mid = i + (j - i) / 2;
			if(nums[mid] > nums.back()) {
				i = mid + 1;
			} else {
				j = mid;
			}
		}
		return nums[i];
	}
}; // 先把左端点向右移动，跳过和尾部重复的元素

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 3, 1, 3 };
	cout << sol.findMin(nums) << endl;
	nums = { 3, 1 };
	cout << sol.findMin(nums) << endl;
	nums = { 3, 3 };
	cout << sol.findMin(nums) << endl;
	nums = { 3, 3, 3 };
	cout << sol.findMin(nums) << endl;
	nums = { 1, 3, 5 };
	cout << sol.findMin(nums) << endl;
	nums = { 2, 2, 2, 0, 1 };
	cout << sol.findMin(nums) << endl;
}