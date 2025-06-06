// Created: 2025-05-15
#include "MyUtils.hpp"

/*33. 搜索旋转排序数组
整数数组 nums 按升序排列，数组中的值 互不相同 。
在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，
使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。
例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。
给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。
你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。
示例 1：
    输入：nums = [4,5,6,7,0,1,2], target = 0
    输出：4
示例 2：
    输入：nums = [4,5,6,7,0,1,2], target = 3
    输出：-1
示例 3：
    输入：nums = [1], target = 0
    输出：-1
提示：
    1 <= nums.length <= 5000
    -104 <= nums[i] <= 104
    nums 中的每个值都 独一无二
    题目数据保证 nums 在预先未知的某个下标上进行了旋转
    -104 <= target <= 104*/

class Solution1 {
public:
	int search(vector<int> &nums, int target) {
		int n = nums.size();
		if(target == nums[0]) return 0;
		if(target == nums[n - 1]) return n - 1;

		// 1. 找旋转点 k（最小值下标）
		int left = 0, right = n - 1, k = 0;
		while(left < right) {
			int mid = left + (right - left) / 2; // mid不一定是最小值，有可能最后一轮被跳过了
			if(nums[mid] < nums[right]) {
				right = mid;
			} else {
				left = mid + 1;
			}
		}
		k = left; // 最小值下标是 left 和 right

		// 2. 判断 target 在哪段区间，再二分
		if(target == nums[k]) return k;
		if(k > 0 && target == nums[k - 1]) return k - 1;

		if(k > 0 && nums[0] < target && nums[k - 1] > target) {
			return binarySearch(nums, 0, k - 1, target);
		} else if(nums[k] < target && nums[n - 1] > target) {
			return binarySearch(nums, k, n - 1, target);
		}
		return -1;
	}

	// 标准二分
	int binarySearch(const vector<int> &vec, int i, int j, const int &key) {
		while(i <= j) {
			int middle = i + (j - i) / 2;
			if(vec[middle] == key) {
				return middle;
			} else if(vec[middle] < key) {
				i = middle + 1;
			} else {
				j = middle - 1;
			}
		}
		return -1;
	}
};

class Solution2 {
public:
	int search(vector<int> &nums, int target) {
		int n = (int)nums.size();
		if(!n) {
			return -1;
		}
		if(n == 1) {
			return nums[0] == target ? 0 : -1;
		}
		int l = 0, r = n - 1;
		while(l <= r) {
			int mid = (l + r) / 2;
			if(nums[mid] == target) return mid;
			if(nums[0] <= nums[mid]) { // [l, mid - 1] 是有序数组
				if(nums[0] <= target && target < nums[mid]) {
					r = mid - 1;
				} else {
					l = mid + 1;
				} // target 的大小满足 [nums[l],nums[mid])，则我们应该将搜索范围缩小至 [l, mid - 1]，否则在 [mid + 1, r] 中寻找。
			} else { // [mid, r] 是有序数组
				if(nums[mid] < target && target <= nums[n - 1]) {
					l = mid + 1;
				} else {
					r = mid - 1;
				} // target 的大小满足 (nums[mid+1],nums[r]]，则我们应该将搜索范围缩小至 [mid + 1, r]，否则在 [l, mid - 1] 中寻找。
			}
		}
		return -1;
	}
};

int main() {
	Solution1 sol1;
}