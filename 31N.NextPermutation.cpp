// Created: 2025-06-20
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 31. 下一个排列
整数数组的一个 排列 就是将其所有成员以序列或线性顺序排列。
	例如，arr = {1, 2, 3}，
以下这些都可以视作 arr 的排列：{1, 2, 3}、{1, 3, 2}、{3, 1, 2}、{2, 3, 1}。
整数数组的 下一个排列 是指其整数的下一个字典序更大的排列。更正式地，如果数组的所有排列根据其字典顺序从小到大排列在一个容器中，
那么数组的 下一个排列 就是在这个有序容器中排在它后面的那个排列。如果不存在下一个更大的排列，那么这个数组必须重排为字典序最小的排列（即，其元素按升序排列）。
	例如，arr = {1, 2, 3} 的下一个排列是 {1, 3, 2}。
	类似地，arr = {2, 3, 1} 的下一个排列是 {3, 1, 2}。
	而 arr = {3, 2, 1} 的下一个排列是 {1, 2, 3}，因为 {3, 2, 1} 不存在一个字典序更大的排列。
给你一个整数数组 nums，找出 nums 的下一个排列。
必须 原地 修改，只允许使用额外常数空间。
示例 1：
	输入：nums = {1, 2, 3}
	输出：{1, 3, 2}
示例 2：
	输入：nums = {3, 2, 1}
	输出：{1, 2, 3}
示例 3：
	输入：nums = {1, 1, 5}
	输出：{1, 5, 1}
提示：
	1 <= nums.length <= 100
	0 <= nums{i} <= 100 */

class Solution1 {
public:
	void nextPermutation(vector<int> &nums) {
		multiset<int> removed; // removed：保存从右往左“移除”的元素，也就是当前位置右边的所有元素
		int n = nums.size(), i;
		for(i = n - 1; i >= 0; --i) {
			int currVal = nums[i];
			removed.insert(currVal);
			auto it = removed.upper_bound(currVal);
			if(it != removed.end()) { // 在 removed 中找一个 严格大于 currVal 的最小元素
				nums[i] = *it;
				removed.erase(it);
				break;
			}
		}
		for(int val : removed) {
			nums[++i] = val;
		} // 把后缀重排成最小字典序
	}
};

class Solution2 {
public:
	void nextPermutation(vector<int> &nums) {
		int n = nums.size();
		int i = n - 2;
		// 1. 从后往前找到第一个升序对（nums[i] < nums[i+1]）
		while(i >= 0 && nums[i] >= nums[i + 1]) --i;
		if(i >= 0) {
			// 2. 从后往前找到第一个比 nums[i] 大的数
			int j = n - 1;
			while(nums[j] <= nums[i]) {
				--j;
			}
			// 3. 交换 nums[i] 和 nums[j]
			swap(nums[i], nums[j]);
		}
		// 4. 反转 i+1 及其后面的部分
		reverse(nums.begin() + i + 1, nums.end());
	}
};

class Solution3 {
public:
	void nextPermutation(vector<int> &nums) {
		int n = nums.size(), keep = n - 2, bigger = n - 1;
		while(keep >= 0 && nums[keep] >= nums[keep + 1]) --keep;
		if(keep != -1) {
			while(bigger >= 0 && nums[bigger] <= nums[keep]) --bigger;
			swap(nums[bigger], nums[keep]);
		}
		reverse(nums.begin() + keep + 1, nums.end());
	}
};
/*  1、从右向左找到第一个不满足非递增的元素 nums[keep]，即 nums[keep] < nums[keep + 1] 的位置
        → 说明右侧存在比该元素更大的数，该位置是“变大的起点”，该位置之前保持不变

    2、从右向左找到第一个比 nums[keep] 更大的数 nums[bigger]
        → 因为右侧是非升序，所以第一个满足条件的一定是“最小的大数”，用于替换 keep

    3、交换 nums[keep] 与 nums[bigger]，使得前缀尽可能小，且变大

    4、翻转 keep+1 到末尾的部分，原是最大排列（非升序），反转后变成最小排列（升序）
        → 确保整体排列为“刚好比原来的大”  */

class Solution {
public:
	void nextPermutation(vector<int> &nums) {
		int n = nums.size(), i = n - 2;
		while(i >= 0 && nums[i] >= nums[i + 1]) --i;
		if(i >= 0) {
			int id = myUpper_bound(nums, i + 1, n, nums[i]);
			std::swap(nums[i], nums[id]);
		}
		std::reverse(nums.begin() + i + 1, nums.end());
	}

private:
	int myUpper_bound(vector<int> &nums, int l, int n, int val) {
		int r = n; // 左闭右开
		while(l < r) {
			int mid = l + (r - l) / 2;
			if(nums[mid] > val) {
				int next = mid + 1;
				if(next == n || nums[next] <= val) {
					// 额外判断是不是最后一个
					return mid;
				} else {
					// 如果不是可以放心的去掉
					l = mid + 1;
				}
			} else {
				r = mid;
			}
		}
		return l;
	} // 从递减的数组中找上界下标
}; // 注意upper_bound的前提是数组是升序的，但是这里的[i + 1, end]是递减的，自己写一个二分查找的反向Upper_bound

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 1, 2, 3 };
	sol.nextPermutation(nums);
	cout << nums << endl; // {1, 3, 2}
	nums = { 1, 3, 2 };
	sol.nextPermutation(nums);
	cout << nums << endl; // {2, 1, 3}
	nums = { 3, 2, 1 };
	sol.nextPermutation(nums);
	cout << nums << endl; // {1, 2, 3}
	nums = { 1, 1, 5 };
	sol.nextPermutation(nums);
	cout << nums << endl; // {1, 5, 1}
	nums = { 1, 5, 1 };
	sol.nextPermutation(nums);
	cout << nums << endl; // {5, 1, 1}
	nums = { 1, 1 };
	sol.nextPermutation(nums);
	cout << nums << endl; // {1, 1}
}