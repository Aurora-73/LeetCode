// Created: 2025-06-05
#include "MyUtils.hpp"

/*1035. 不相交的线
在两条独立的水平线上按给定的顺序写下 nums1 和 nums2 中的整数。
现在，可以绘制一些连接两个数字 nums1[i] 和 nums2[j] 的直线，这些直线需要同时满足：
nums1[i] == nums2[j]
且绘制的直线不与任何其他连线（非水平线）相交。
请注意，连线即使在端点也不能相交：每个数字只能属于一条连线。
以这种方法绘制线条，并返回可以绘制的最大连线数。*/

class Solution1 {
public:
	int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2) {
		if(nums1.size() < nums2.size()) {
			swap(nums1, nums2);
		}
		int n1 = nums1.size(), n2 = nums2.size();
		vector<int> dp(n2 + 1, 0);
		for(int i = n1 - 1; i >= 0; --i) {
			int prev = 0; // 代表 dp[j+1] 的上一轮值（即左上角）
			for(int j = n2 - 1; j >= 0; --j) {
				int temp = dp[j]; // 记录当前 dp[j]，用于下一个 j 的 prev
				if(nums1[i] == nums2[j]) {
					dp[j] = prev + 1;
				} else {
					dp[j] = max(dp[j], dp[j + 1]);
				}
				prev = temp;
			}
		}
		return dp[0];
	}
}; // 和 1143.最长公共子序列 完全一样

#define LCS_NAME longestCommonSubsequence
class Solution {
public:
	template <typename Seq1, typename Seq2>
	int LCS_NAME(Seq1 &a, Seq2 &b) {
		if(a.size() < b.size()) {
			swap(a, b);
		}
		int n1 = a.size(), n2 = b.size();
		std::vector<int> dp(n2 + 1, 0);
		for(int i = n1 - 1; i >= 0; --i) {
			int prev = 0;
			for(int j = n2 - 1; j >= 0; --j) {
				int temp = dp[j];
				if(a[i] == b[j]) {
					dp[j] = prev + 1;
				} else {
					dp[j] = std::max(dp[j], dp[j + 1]);
				}
				prev = temp;
			}
		}
		return dp[0];
	}
};
#undef LCS_NAME // 两个题通用的模版

int main() {
	Solution sol;
}