// Created: 2025-06-20
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 75. 颜色分类
给定一个包含红色、白色和蓝色、共n 个元素的数组nums，
原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
我们使用整数 0、1 和 2 分别表示红色、白色和蓝色。
必须在不使用库内置的 sort 函数的情况下解决这个问题。
示例 1：
	输入：nums = {2,0,2,1,1,0}
	输出：{0,0,1,1,2,2}
示例 2：
	输入：nums = {2,0,1}
	输出：{0,1,2}
提示：
	n == nums.length
	1 <= n <= 300
	nums{i} 为 0、1 或 2
进阶：
	你能想出一个仅使用常数空间的一趟扫描算法吗？ */

class Solution {
public:
	void sortColors(vector<int> &nums) {
		int p0 = 0, p2 = nums.size() - 1, i = 0;
		while(i <= p2) {
			if(nums[i] == 0) {
				swap(nums[i], nums[p0]);
				++i, ++p0;
			} else if(nums[i] == 2) {
				swap(nums[i], nums[p2]);
				--p2;
			} else {
				++i;
			}
		}
	}
};
/* 用三个指针 p0、p2 和 i，将数组分为四段：
    [0, p0 - 1]：全是 0
    [p0, i - 1]：全是 1
    [p2 + 1, n - 1]：全是 2
    [i, p2]：待处理区域
遍历数组：
    如果当前元素是 0，和 p0 位置交换，p0 和 i 都加 1
    如果当前元素是 2，和 p2 位置交换，p2 减 1，i 不变（因为换过来的数还没判断）
    如果当前元素是 1，i 加 1
    这样只需一趟遍历，就能把 0、1、2 分别放到正确的位置，实现原地排序。*/

class Solution {
public:
	void sortColors(vector<int> &nums) {
		int p0 = 0, p1 = 0, n = nums.size();
		for(int i = 0; i < n; ++i) {
			int val = nums[i];
			nums[i] = 2; // 将 nums[i] 改为 2
			if(val < 2) {
				nums[p1++] = 1;
			} // 右移 1 的边界
			if(val == 0) {
				nums[p0++] = 0;
			} // 右移 0 的边界
		}
	}
};
/* 相当于把 i 的元素插入已经有序的部分：
    1、如果 i 为 2，不需要处理（则将 nums[i] 改为 2 ）
    2、如果 i 为 1，则将 nums[i] 改为 2，然后将 1 的右边界向右扩展一个
    3、如果 i 为 0，则将 nums[i] 改为 2，然后将 0 和 1 的右边界都向右扩展一个 */

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 2, 0, 2, 1, 1, 0 };
	sol.sortColors(nums);
	cout << nums << endl;
	nums = { 2, 0, 1 };
	sol.sortColors(nums);
	cout << nums << endl;
}