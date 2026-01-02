// Created: 2026-01-01
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给你一个整数数组nums，将它重新排列成nums{0} < nums{1} > nums{2} < nums{3}...的顺序。
你可以假设所有输入数组都可以得到满足题目要求的结果。
示例 1：
	输入：nums = {1,5,1,1,6,4}
	输出：{1,6,1,5,1,4}
	解释：{1,4,1,5,1,6} 同样是符合题目要求的结果，可以被判题程序接受。
示例 2：
	输入：nums = {1,3,2,2,3,1}
	输出：{2,3,1,3,1,2}
提示：
	1 <= nums.length <= 5 * 10^4
	0 <= nums{i} <= 5000
	题目数据保证，对于给定的输入 nums，总能产生满足题目要求的结果
	进阶：你能用O(n) 时间复杂度和 / 或原地 O(1) 额外空间来实现吗？ */

class Solution {
public:
	void wiggleSort(vector<int> &nums) {
		int n = nums.size(), l = 0, r = n - 1, mid = (n - 1) / 2, eq, la;
		while(l < r) {
			auto re = partition(nums, l, r);
			eq = re.first, la = re.second;
			if(eq <= mid && la > mid) {
				break;
			} else if(eq > mid) {
				r = eq - 1;
			} else {
				l = la;
			}
		}
		int pivot = nums[mid];
		// 虚拟索引映射：把线性索引 0..n-1 映射为 1,3,5,...,0,2,4,...
		auto idx = [n](int i) {
			return (1 + 2 * i) % (n / 2 * 2 + 1);
		};
		int i = 0, j = 0, t = n - 1;
		while(j <= t) {
			int ij = idx(j);
			if(nums[ij] > pivot) {
				swap(nums[idx(i)], nums[ij]);
				++i, ++j;
			} else if(nums[ij] < pivot) {
				swap(nums[ij], nums[idx(t)]);
				--t;
			} else {
				++j;
			}
		}
	}

private:
	pair<int, int> partition(vector<int> &nums, int l, int r) {
		int pivot = nums[l + (r - l) / 2]; // 选中间位置作为 pivot 更稳健
		int lt = l, i = l, gt = r;
		while(i <= gt) {
			if(nums[i] < pivot) {
				swap(nums[lt++], nums[i++]);
			} else if(nums[i] > pivot) {
				swap(nums[i], nums[gt--]);
			} else {
				++i;
			}
		}
		return { lt, i }; // 等于段为 [lt, i)
	} // [  <  |lt|  =  |i|    ?     |gt|  >  ]
};

class Solution1 {
public:
	void wiggleSort(vector<int> &nums) {
		int n = nums.size();
		vector<int> nums2 = nums;
		sort(nums2.begin(), nums2.end());
		int l = (n + 1) / 2 - 1, r = n - 1;
		for(int i = 0; i < n; ++i) {
			if(i & 1) {
				nums[i] = nums2[r--];
			} else {
				nums[i] = nums2[l--];
			}
		}
	}
}; /*排序 → 前半倒序放偶数位（谷）  
    排序 → 后半倒序放奇数位（峰）  
    确保重复元素不相邻 → 保证严格 < >*/

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 4, 5, 5, 6 };
	sol.wiggleSort(nums);
	cout << nums << endl;

	nums = { 1, 3, 2, 2, 3, 1, 4, 5 };
	sol.wiggleSort(nums);
	cout << nums << endl;

	nums = { 1, 5, 1, 1, 6, 4, 8 };
	sol.wiggleSort(nums);
	cout << nums << endl;

	nums = { 1, 3, 2, 2, 3, 1 };
	sol.wiggleSort(nums);
	cout << nums << endl;
}