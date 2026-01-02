// Created: 2025-12-31
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 在一个整数数组中，“峰”是大于或等于相邻整数的元素，相应地，“谷”是小于或等于相邻整数的元素。
例如，在数组{5, 8, 4, 2, 3, 4, 6}中，{8, 6}是峰，
 {5, 2}是谷。现在给定一个整数数组，将该数组按峰与谷的交替顺序排序。
输入：
    {5, 3, 1, 2, 3}
输出：
    {5, 1, 3, 2, 3}
提示：
	nums.length <= 10000 */

class Solution1 {
public:
	void wiggleSort(vector<int> &nums) {
		std::sort(nums.begin(), nums.end());
		int l = 0, r = (nums.size() / 2) * 2 - 1;
		for(; l < r; l += 2, r -= 2) {
			swap(nums[l], nums[r]);
		}
	}
}; // 先排序，然后把奇数位旋转
//      1, 2, 3, 4, 5, 6
// ->   5, 2, 3, 4, 1, 6

// 或者也可以直接截成两半，后半部分任意插入前半部分
// -> 1, 2, 3 ||  4, 5, 6
// -> 1, 4, 2, 5, 3, 6
// 其实这里也不需要真的要求有序，只需要后半部分大于前半部分(或者相反)即可 (partition)
// 插入的时候可以将单独的偶数位交换，快速实现穿插

class Solution2 {
public:
	void wiggleSort(vector<int> &nums) {
		int n = nums.size(), l = 0, r = n - 1;
		while(l < r) {
			int pid = partition(nums, l, r);
			if(pid == n / 2) {
				break;
			} else if(pid > n / 2) {
				r = pid - 1;
			} else {
				l = pid + 1;
			}
		}
		vector<int> temp = std::move(nums);
		nums.reserve(n);
		int small = 0, large = (n + 1) / 2;
		for(int i = 0; i < n; ++i) {
			if(i % 2) {
				nums.push_back(temp[large]);
				++large;
			} else {
				nums.push_back(temp[small]);
				++small;
			}
		}
	}

private:
	int partition(vector<int> &nums, int l, int r) {
		int povit = nums[l];
		while(l < r) {
			while(l < r && nums[r] >= povit) --r;
			if(l < r) nums[l] = nums[r];
			while(l < r && nums[l] <= povit) ++l;
			if(l < r) nums[r] = nums[l];
		}
		nums[l] = povit;
		return l;
	}
}; // 划分之后交叉放置大于和小于的元素

class Solution {
public:
	void wiggleSort(vector<int> &nums) {
		int n = nums.size();
		for(int i = 1; i < n; ++i) {
			if((i & 1) == 1) {
				// 奇数位：nums[i] >= nums[i-1]
				if(nums[i] < nums[i - 1]) {
					swap(nums[i], nums[i - 1]);
				}
			} else {
				// 偶数位：nums[i] <= nums[i-1]
				if(nums[i] > nums[i - 1]) {
					swap(nums[i], nums[i - 1]);
				}
			}
		}
	}
};
// 贪心算法，奇数位是「峰」，偶数位是「谷」，那就只需要 和前一个比，不满足就 swap
/* 一、我们先把问题说“精确”
    算法是：
        for i = 1..n-1:
            if i 是奇数:
                要求 nums[i] >= nums[i-1]
                若不满足 -> swap(nums[i], nums[i-1])
            else:
                要求 nums[i] <= nums[i-1]
                若不满足 -> swap(nums[i], nums[i-1])

    你质疑的是这一点：
        交换 nums[i] 和 nums[i-1]，
        为什么不会破坏 nums[i-2] 和 nums[i-1] 之间原本已经成立的摆动关系？

二、分情况严格证明（核心）

我们来分奇偶 i证明。

情况 1：i 是奇数

    目标关系：

        nums[i-1] <= nums[i]   （i 是峰）

    进入循环前，不变式告诉我们：
        nums[i-2] >= nums[i-1]   （因为 i-1 是偶数，是谷）

    现在发生交换的条件是：
        nums[i] < nums[i-1]


    也就是说：
        nums[i] < nums[i-1] <= nums[i-2]


    交换后：
        nums[i-1] = 原 nums[i]
        nums[i-2] >= 原 nums[i]


所以交换后仍然有：
    nums[i-2] >= nums[i-1]

旧关系没被破坏
    情况 2：i 是偶数（完全对称）

目标关系：
    nums[i-1] >= nums[i]


不变式保证：
    nums[i-2] <= nums[i-1]   （i-1 是奇数，是峰）


触发交换条件：
    nums[i] > nums[i-1]


即：
    nums[i] > nums[i-1] >= nums[i-2]


交换后：
    nums[i-1] = 原 nums[i]
    nums[i-2] <= 原 nums[i]


仍然满足：
    nums[i-2] <= nums[i-1]

三、结论（关键一句）
    发生交换的前提，恰恰保证了
    被交换进 nums[i-1] 的那个数
    “比它的左邻居更极端”，
    因此不会破坏旧的摆动关系

这是 280 能用「局部 swap」的根本原因。 */

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 5, 3, 1, 2, 3 };
	sol.wiggleSort(nums);
	cout << nums << endl;

	nums = { 3, 5, 2, 1, 6, 4 };
	sol.wiggleSort(nums);
	cout << nums << endl;
}