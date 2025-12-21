// Created: 2025-12-20
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个未排序的整数数组 nums，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
示例 1：
	输入：nums = {100,4,200,1,3,2}
	输出：4
	解释：最长数字连续序列是 {1, 2, 3, 4}。它的长度为 4。
示例 2：
	输入：nums = {0,3,7,2,5,8,4,6,0,1}
	输出：9
提示：
	0 <= nums.length <= 10^4
	-10^9 <= nums{i} <= 10^9
	进阶：可以设计并实现时间复杂度为O(n) 的解决方案吗？ */

class Solution1 {
public:
	int longestConsecutive(vector<int> &nums) {
		set<int> s;
		for(auto num : nums) {
			s.insert(num);
		}
		int res = 0, curr = 1;
		for(auto it = s.begin(); it != s.end(); ++it) {
			if(next(it) != s.end() && *it + 1 == *next(it)) {
				++curr;
			} else {
				res = max(res, curr);
				curr = 1;
			}
		}
		return res;
	}
};

class Solution {
public:
	int longestConsecutive(vector<int> &nums) {
		unordered_set<int> num_set(nums.begin(), nums.end());
		int res = 0;
		for(auto num : num_set) { // 这里应该遍历num_set而不是nums，因为后者可能存在大量重复元素
			if(num_set.count(num - 1)) continue;
			int curr = 1;
			while(num_set.count(num + curr)) {
				++curr;
			}
			res = max(res, curr);
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 100, 4, 200, 1, 3, 2 };
	cout << sol.longestConsecutive(nums) << endl;

	nums = { 0, 3, 7, 2, 5, 8, 4, 6, 0, 1 };
	cout << sol.longestConsecutive(nums) << endl;
}