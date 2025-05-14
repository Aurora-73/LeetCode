// Created: 2025-05-14
#include "MyUtils.h"

/*53. 最大子数组和
给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
子数组是数组中的一个连续部分。*/

class Solution1 {
public:
	int maxSubArray(vector<int> &nums) {
		int max_sum = INT_MIN, pre_now = 0;
		for(auto &x : nums) {
			pre_now = max(pre_now + x, x);
			max_sum = max(max_sum, pre_now);
		}
		return max_sum;
	}
};

class Solution2 {
public:
	struct Status {
		int lSum, rSum, mSum, iSum;
	};

	Status pushUp(Status l, Status r) {
		int iSum = l.iSum + r.iSum;
		int lSum = max(l.lSum, l.iSum + r.lSum);
		int rSum = max(r.rSum, r.iSum + l.rSum);
		int mSum = max(max(l.mSum, r.mSum), l.rSum + r.lSum);
		return (Status) { lSum, rSum, mSum, iSum };
	};

	Status get(vector<int> &a, int l, int r) {
		if(l == r) {
			return (Status) { a[l], a[l], a[l], a[l] };
		}
		int m = (l + r) >> 1;
		Status lSub = get(a, l, m);
		Status rSub = get(a, m + 1, r);
		return pushUp(lSub, rSub);
	}

	int maxSubArray(vector<int> &nums) {
		return get(nums, 0, nums.size() - 1).mSum;
	}
}; // 线段树

int main() {
	Solution1 sol1;
}