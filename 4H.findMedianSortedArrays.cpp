// Created: 2025-05-17
#include "MyUtils.hpp"

/* 4. 寻找两个正序数组的中位数
给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数。
算法的时间复杂度应该为 O(log (m+n))。
示例 1：
	输入：nums1 = {1,3}, nums2 = {2}
	输出：2.00000
	解释：合并数组 = {1,2,3}，中位数 2
示例 2：
	输入：nums1 = {1,2}, nums2 = {3,4}
	输出：2.50000
	解释：合并数组 = {1,2,3,4}，中位数 (2 + 3) / 2 = 2.5  */

class Solution1 {
public:
	double findMedianSortedArrays(const vector<int> &nums1, const vector<int> &nums2) {
		int n1 = nums1.size(), n2 = nums2.size();
		int total = n1 + n2;
		int i = 0, j = 0;
		int prev = 0, curr = 0;

		// 合并走 total / 2 步
		for(int k = 0; k <= total / 2; ++k) {
			prev = curr;
			// 从 nums1/nums2 中选 较小者 或 可行者 推进
			if(i < n1 && (j >= n2 || nums1[i] < nums2[j])) {
				curr = nums1[i++];
			} else {
				curr = nums2[j++];
			}
		}

		// 如果总长度是奇数，直接返回 curr
		if(total % 2) {
			return curr;
		}
		// 否则取 prev 和 curr 的平均
		return (prev + curr) / 2.0;
	}
};
// 奇数 t = 2m + 1 ：分为   m   | 1 |   m  ，中位数前面有 m = (t - 1) / 2 = [t / 2] 个元素
// 偶数 t = 2m     ：分为 (m-1) | 2 | (m-1)，第 2 个中位数下标 m，前面也有 m = t / 2 个元素

// 找中位数的过程可以转化为找一个分割线，使得分割线左侧元素均小于等于右侧元素，且分割线左侧元素最少和右侧元素数相等，最多比右侧元素数多一
// 此时，如果元素个数为奇数，这分割线左侧元素即为中位数，如果元素个数为偶数，则分割线左右两侧元素均值即为中位数
// 对于两个有序数组的情况，我们可以在两个数组中都寻找一个分割线，使得两个分割线左右元素之和满足性质，记分割线为i j 则 i + j = (n1 + n2 + 1) / 2，因此只需要控制 i 即可
// 如果我们直接控制 i + j = (n1 + n2 + 1) / 2，则我们只需要找到满足分割线左侧元素均小于等于右侧元素的 i 即可
// 分割线左侧的最大元素是 max(nums1[i - 1], nums2[j - 1]) 右侧最小元素是 min(nums[i], nums[j])，则只需要满足 max(nums1[i - 1], nums2[j - 1]) <=  min(nums[i], nums[j])
// 又由于单个数组内部是单调的，可以简化的为 nums1[i - 1] <= nums[j]; nums2[j - 1] <= nums[i]
// 结束时，如果是奇数返回 max(nums1[i - 1], nums2[j - 1])，偶数返回 (max(nums1[i - 1], nums2[j - 1]) + min(nums[i], nums[j])) / 2
// 为了避免第二个数组越界，我们对长度较小的数组进行二分查找，我们将-1下标定为 numeric_limits<int>::min(), size 下标定为numeric_limits<int>::max()
// 对较短的数组进行分割时可以保证另一个数组的分割位置始终是合法的
// 分割到较短的数组的尽头时 其实就已经找到了中位数了。因此对较短的数组进行分割
class Solution {
public:
	double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
		// 保证 nums1 是较短的数组
		if(nums1.size() > nums2.size()) {
			return findMedianSortedArrays(nums2, nums1);
		}
		if(!nums2.size()) return 0.0;

		int shortLen = nums1.size();
		int longLen = nums2.size();
		// 分界线左半部分应该包含的元素个数
		int halfLen = (shortLen + longLen + 1) / 2;

		int left = 0, right = shortLen; // 左闭右开
		while(true) {                   // 虽然左闭右开，但是不一定是在nums1中找到元素，所以不能退出
			// 在 nums1 上二分划分点
			int partitionShort = left + (right - left) / 2;
			int partitionLong = halfLen - partitionShort;

			// nums1 左/右两侧的临界值
			int shortPartitionLeft
			    = (partitionShort == 0 ? numeric_limits<int>::min() : nums1[partitionShort - 1]);
			int shortPartitionRight
			    = (partitionShort == shortLen ? numeric_limits<int>::max() : nums1[partitionShort]);
			// nums2 左/右两侧的临界值
			int longPartitionLeft
			    = (partitionLong == 0 ? numeric_limits<int>::min() : nums2[partitionLong - 1]);
			int longPartitionRight
			    = (partitionLong == longLen ? numeric_limits<int>::max() : nums2[partitionLong]);

			// 找到满足「左侧最大 ≤ 右侧最小」的划分
			if(shortPartitionLeft <= longPartitionRight
			    && longPartitionLeft <= shortPartitionRight) {
				// 总长度为奇数时，中位数是左半部分最大值
				if((shortLen + longLen) % 2 == 1) {
					return static_cast<double>(max(shortPartitionLeft, longPartitionLeft));
				}
				// 总长度为偶数时，中位数是左右两侧贴近中点的两个数的平均
				return (static_cast<double>(max(shortPartitionLeft, longPartitionLeft)
				           + min(shortPartitionRight, longPartitionRight)))
				    / 2.0;
			}
			// 如果 nums1 左侧最大比 nums2 右侧最小还大，说明 partitionShort 太靠右
			else if(shortPartitionLeft > longPartitionRight) {
				right = partitionShort - 1;
			}
			// 否则 partitionShort 太小
			else {
				left = partitionShort + 1;
			}
		}
	}
};

int main() {
	Solution sol;
}