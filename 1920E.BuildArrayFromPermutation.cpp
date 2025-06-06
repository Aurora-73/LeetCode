// Created: 2025-05-06
#include "MyUtils.hpp"

/*1920. 基于排列构建数组
给你一个 从 0 开始的排列 nums（下标也从 0 开始）。请你构建一个 同样长度 的数组 ans ，
其中，对于每个 i（0 <= i < nums.length），都满足 ans[i] = nums[nums[i]] 。返回构建好的数组 ans。
从 0 开始的排列 nums 是一个由 0 到 nums.length - 1（0 和 nums.length - 1 也包含在内）的不同整数组成的数组。*/

class Solution1 {
public:
	void buildArray(vector<int> &nums) {
		int n = nums.size();
		for(int i = 0; i < nums.size(); ++i) {
			int real = nums[i] % n;
			nums[i] = nums[i] + real * n;
		}
		for(int i = 0; i < nums.size(); ++i) {
			int index = (nums[i] / n) % n;
			int real = nums[index] % n;
			nums[i] = nums[i] + real * n * n;
		}
		for(int i = 0; i < nums.size(); ++i) {
			nums[i] = nums[i] / n / n;
		}
	}
};
class Solution2 {
public:
	void buildArray(vector<int> &nums) {
		int n = nums.size();
		for(int i = 0; i < nums.size(); ++i) {
			int real = nums[nums[i] % n] % n;
			nums[i] = nums[i] + real * n;
		}
		for(int i = 0; i < nums.size(); ++i) {
			nums[i] = nums[i] / n;
		}
	}
};

int main() {
	Solution1 sol1;
	vector<int> nums;
	nums = { 0, 2, 1, 5, 3, 4 };
	sol1.buildArray(nums);
	cout << nums << endl;
	Solution2 sol2;
	nums = { 0, 2, 1, 5, 3, 4 };
	sol2.buildArray(nums);
	cout << nums << endl;
	nums = { 5, 0, 1, 2, 3, 4 };
	sol1.buildArray(nums);
	cout << nums << endl;
	nums = { 5, 0, 1, 2, 3, 4 };
	sol2.buildArray(nums);
	cout << nums << endl;
}