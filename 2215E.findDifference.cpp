// Created: 2025-07-05
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 2215. 找出两数组的不同
给你两个下标从 0 开始的整数数组 nums1 和 nums2，请你返回一个长度为 2 的列表 answer，其中：
	answer{0} 是 nums1 中所有 不 存在于 nums2 中的 不同 整数组成的列表。
	answer{1} 是 nums2 中所有 不 存在于 nums1 中的 不同 整数组成的列表。
注意：列表中的整数可以按 任意 顺序返回。
示例 1：
	输入：nums1 = {1,2,3}, nums2 = {2,4,6}
	输出：{{1,3},{4,6}}
	解释：
	对于 nums1，nums1{1} = 2 出现在 nums2 中下标 0 处，
	然而 nums1{0} = 1 和 nums1{2} = 3 没有出现在 nums2 中。因此，answer{0} = {1,3}。
	对于 nums2，nums2{0} = 2 出现在 nums1 中下标 1 处，
	然而 nums2{1} = 4 和 nums2{2} = 6 没有出现在 nums2 中。因此，answer{1} = {4,6}。
示例 2：
	输入：nums1 = {1,2,3,3}, nums2 = {1,1,2,2}
	输出：
	解释：
	对于 nums1，nums1{2} 和 nums1{3} 没有出现在 nums2 中。由于 nums1{2} == nums1{3}，
	二者的值只需要在 answer{0} 中出现一次，故 answer{0} = {3}。
	nums2 中的每个整数都在 nums1 中出现，因此，answer{1} = {}。 
提示：
	1 <= nums1.length, nums2.length <= 1000
	-1000 <= nums1{i}, nums2{i} <= 1000 */

class Solution1 {
public:
	vector<vector<int>> findDifference(vector<int> &nums1, vector<int> &nums2) {
		vector<vector<int>> res(2);
		unordered_map<int, int> map;
		for(auto num1 : nums1) {
			map[num1] = 1;
		}
		for(auto num2 : nums2) {
			auto it = map.find(num2);
			if(it == map.end()) {
				map[num2] = 2;
			} else {
				if(it->second == 1) {
					it->second = 0;
				}
			}
		}
		for(auto [num, flag] : map) {
			if(flag == 1) res[0].push_back(num);
			if(flag == 2) res[1].push_back(num);
		}
		return res;
	}
};

class Solution2 {
public:
	vector<vector<int>> findDifference(vector<int> &nums1, vector<int> &nums2) {
		ranges::sort(nums1), ranges::sort(nums2);
		vector<vector<int>> res(2);
		int n1 = nums1.size(), n2 = nums2.size(), i = 0, j = 0;
		while(i < n1 && j < n2) {
			if(nums1[i] < nums2[j]) {
				res[0].push_back(nums1[i]), ++i;
				while(i < n1 && nums1[i] == nums1[i - 1]) ++i;
			} else if(nums1[i] > nums2[j]) {
				res[1].push_back(nums2[j]), ++j;
				while(j < n2 && nums2[j] == nums2[j - 1]) ++j;
			} else {
				++i, ++j;
				while(i < n1 && nums1[i] == nums1[i - 1]) ++i;
				while(j < n2 && nums2[j] == nums2[j - 1]) ++j;
			}
		}
		while(i < n1) {
			res[0].push_back(nums1[i++]);
			while(i < n1 && nums1[i] == nums1[i - 1]) ++i;
		}
		while(j < n2) {
			res[1].push_back(nums2[j++]);
			while(j < n2 && nums2[j] == nums2[j - 1]) ++j;
		}
		return res;
	}
};

class Solution {
public:
	vector<vector<int>> findDifference(vector<int> &nums1, vector<int> &nums2) {
		ranges::sort(nums1), ranges::sort(nums2);
		vector<vector<int>> res(2);
		int n1 = nums1.size(), n2 = nums2.size(), i = 0, j = 0;
		while(i < n1) {
			if(nums1[i] != nums1[j]) {
				nums1[++j] = nums1[i];
			}
			++i;
		}
		n1 = j + 1, i = j = 0;
		while(i < n2) {
			if(nums2[i] != nums2[j]) {
				nums2[++j] = nums2[i];
			}
			++i;
		}
		n2 = j + 1, i = j = 0;
		while(i < n1 && j < n2) {
			if(nums1[i] < nums2[j]) {
				res[0].push_back(nums1[i]), ++i;
			} else if(nums1[i] > nums2[j]) {
				res[1].push_back(nums2[j]), ++j;
			} else {
				++i, ++j;
			}
		}
		while(i < n1) {
			res[0].push_back(nums1[i++]);
		}
		while(j < n2) {
			res[1].push_back(nums2[j++]);
		}
		return res;
	}
}; // 先排序，然后去重，最后找不同

int main() {
	Solution sol;
	vector<int> nums1, nums2;
	nums1 = { 1, 2, 3 }, nums2 = { 2, 4, 6 };
	cout << sol.findDifference(nums1, nums2) << endl; // {{1,3},{4,6}}
	nums1 = { 1, 2, 3, 3 }, nums2 = { 1, 1, 2, 2 };
	cout << sol.findDifference(nums1, nums2) << endl; // {{3},{}}
	nums1 = { -80, -15, -81, -28, -61, 63, 14, -45, -35, -10 },
	nums2 = { -1, -40, -44, 41, 10, -43, 69, 10, 2 };
	cout << sol.findDifference(nums1, nums2) << endl;
	// { { -80, -28, -81, -61, -35, 63, -15, -45, 14, -10 }, { 69, -43, 10, 41, 2, -44, -1, -40 } }
}