// Created: 2025-06-02
#include "MyUtils.h"
#include <cstring>

/*1027. 最长等差数列
给你一个整数数组 nums，返回 nums 中最长等差子序列的长度。
回想一下，nums 的子序列是一个列表 nums[i1], nums[i2], ..., nums[ik] ，
且 0 <= i1 < i2 < ... < ik <= nums.length - 1。
并且如果 seq[i+1] - seq[i]( 0 <= i < seq.length - 1) 的值都相同，那么序列 seq 是等差的。
提示：
    2 <= nums.length <= 1000
    0 <= nums[i] <= 500*/

class Solution {
public:
	int longestArithSeqLength(vector<int> &arr) {
		int n = arr.size(), res = 1, maxVal = INT_MIN, minVal = INT_MAX;
		for(auto &a : arr) {
			maxVal = max(a, maxVal);
			minVal = min(a, minVal);
		}
		int len = maxVal - minVal + 1;
		auto dp = make_unique<int[]>(len);
		for(int diff = 1 - len; diff < len; ++diff) {
			memset(dp.get(), 0, sizeof(int) * len);
			for(int i = 0; i < n; ++i) {
				int index = arr[i] - minVal, next = index - diff;
				bool vaild = (next >= 0 && next < len);
				dp[index] = max((vaild ? dp[next] : 0) + 1, dp[index]);
				res = max(res, dp[index]);
			}
		}
		return res;
	}
}; // 值域dp 枚举公差
/*  这是因为 std::unique_ptr 针对数组类型做了一个偏特化（specialization），
其中专门提供了 operator[] 的重载。具体来说：unique_ptr 对数组的偏特化 */

class Solution {
public:
	int longestArithSeqLength(vector<int> &a) {
		int ans = 0, n = a.size(), f[n][1001];
		memset(f, 0, sizeof(f));
		for(int i = 1; i < n; ++i)
			for(int j = i - 1; j >= 0; --j) {
				int d = a[i] - a[j] + 500; // +500 防止出现负数
				if(f[i][d] == 0) {
					f[i][d] = f[j][d] + 1; // 默认的 1 在下面返回时加上
					ans = max(ans, f[i][d]);
				}
			}
		return ans + 1;
	}
}; // 子序列最后两项之差为公差

int main() {
	Solution sol;
}