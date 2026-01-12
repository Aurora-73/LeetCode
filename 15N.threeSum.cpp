// Created: 2026-01-12
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 15. 三数之和
给你一个整数数组 nums，
判断是否存在三元组 {nums{i}, nums{j}, nums{k}} 满足 i != j、i != k 且 j != k，
同时还满足 nums{i} + nums{j} + nums{k} == 0。请你返回所有和为 0 且不重复的三元组。
注意：答案中不可以包含重复的三元组。
示例 1：
	输入：nums = {-1,0,1,2,-1,-4}
	输出：{{-1,-1,2},{-1,0,1}}
	解释：
	nums{0} + nums{1} + nums{2} = (-1) + 0 + 1 = 0。
	nums{1} + nums{2} + nums{4} = 0 + 1 + (-1) = 0。
	nums{0} + nums{3} + nums{4} = (-1) + 2 + (-1) = 0。
	不同的三元组是 {-1,0,1} 和 {-1,-1,2}。
示例 2：
	输入：nums = {0,1,1}
	输出：{}
	解释：唯一可能的三元组和不为 0。
示例 3：
	输入：nums = {0,0,0}
	输出：{{0,0,0}}
	解释：唯一可能的三元组和为 0。
注意，输出的顺序和三元组的顺序并不重要。*/

class Solution2 {
public:
	vector<vector<int>> threeSum(vector<int> &nums) {
		int n = nums.size();
		vector<vector<int>> res;
		std::sort(nums.begin(), nums.end());
		int index = 0, num = 0;
		while(index < n && nums[index] < 0) index++;
		while(index + num < n && nums[index + num] == 0) num++;
		if(num >= 3) {
			res.push_back({ 0, 0, 0 });
		}
		int numsi = numeric_limits<int>::max();
		for(int i = 0; i < index; i++) {
			while(i < index && numsi == nums[i]) i++;
			if(i >= index) break;
			int numsj = numeric_limits<int>::max();
			for(int j = index; j < nums.size(); j++) {
				while(j < (int)nums.size() && numsj == nums[j]) j++;
				if(j >= (int)nums.size()) break;
				int numsk = numeric_limits<int>::min();
				for(int k = i + 1; k < j; k++) {
					while(k < j && numsk == nums[k]) k++;
					if(k >= j) break;
					if(nums[i] + nums[j] + nums[k] == 0) {
						numsi = nums[i];
						numsj = nums[j];
						numsk = nums[k];
						res.push_back({ nums[i], nums[j], nums[k] });
					}
				}
			}
		}
		return res;
	}
};

class Solution {
public:
	vector<vector<int>> threeSum(vector<int> &nums) {
		vector<vector<int>> res;
		int n = nums.size();
		sort(nums.begin(), nums.end());

		for(int i = 0; i < n - 2; ++i) {
			if(i > 0 && nums[i] == nums[i - 1]) continue;                    // 去重
			if(nums[i] > 0) break;                                           // 剪枝
			if((long long)nums[i] + nums[n - 2] + nums[n - 1] < 0) continue; // 太靠左
			if((long long)nums[i] + nums[i + 1] + nums[i + 2] > 0) break;    // 太靠右

			int l = i + 1, r = n - 1;
			long long need = -(long long)nums[i];
			while(l < r) {
				long long s = (long long)nums[l] + nums[r];
				if(s == need) {
					res.push_back({ nums[i], nums[l], nums[r] });
					++l, --r;
					while(l < r && nums[l] == nums[l - 1]) ++l; // 跳过重复
					while(l < r && nums[r] == nums[r + 1]) --r; // 跳过重复
					// break;                                   // 不能break，因为要找全部的两数之和
				} else if(s < need) {
					++l;
				} else {
					--r;
				}
			}
		}
		return res;
	}
}; // 排序之后枚举第一个数，然后对另外两个数作两数之和最简单，因为这样可以很容易去重

int main() {
	Solution sol;
	vector<int> nums;
	nums = { -1, 0, 1, 2, -1, -4 }; //{{-1,-1,2},{-1,0,1}}
	cout << sol.threeSum(nums) << endl;
	nums = { 0, 1, 1 }; // {}
	cout << sol.threeSum(nums) << endl;

	nums = { 0, 0, 0, 0 }; // {0, 0, 0}
	cout << sol.threeSum(nums) << endl;

	nums = {
		-4, -2, -2, -2, 0, 1, 2, 2, 2, 3, 3, 4, 4, 6, 6
	}; // {{-4,-2,6},{-4,0,4},{-4,1,3},{-4,2,2},{-2,-2,4},{-2,0,2}}
	cout << sol.threeSum(nums) << endl;

	nums = { -2, 0, 1, 1, 2 }; //{{-2,0,2},{-2,1,1}}
	cout << sol.threeSum(nums) << endl;
}