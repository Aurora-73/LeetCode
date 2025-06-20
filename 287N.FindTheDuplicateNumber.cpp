// Created: 2025-06-19
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 287. 寻找重复数
给定一个包含n + 1 个整数的数组nums，其数字都在{1, n}范围内（包括 1 和 n），可知至少存在一个重复的整数。
假设 nums 只有 一个重复的整数，返回这个重复的数。
你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1) 的额外空间。
示例 1：
	输入：nums = {1,3,4,2,2}
	输出：2
示例 2：
	输入：nums = {3,1,3,4,2}
	输出：3
示例 3 :
	输入：nums = {3,3,3,3,3}
	输出：3
提示：
	1 <= n <= 10^5
	nums.length == n + 1
	1 <= nums{i} <= n
	nums 中 只有一个整数 出现 两次或多次，其余整数均只出现 一次
	进阶：
	如何证明 nums 中至少存在一个重复的数字?
	你可以设计一个线性级时间复杂度 O(n) 的解决方案吗？ */

class Solution {
public:
	int findDuplicate(vector<int> &nums) {
		int fast = nums[0], slow = nums[0];
		// 初始化成 0 或者 nums[0] 都可以，只要和后面的重新指向头结点一样就行了
		do {
			fast = nums[nums[fast]];
			slow = nums[slow];
		} while(fast != slow);

		slow = nums[0]; // 要和上面的对应
		while(slow != fast) {
			fast = nums[fast];
			slow = nums[slow];
		}
		return slow;
	}
};
// 将数组看做链表，链表节点 i 指向 nums[i]，则有重复元素等价于有环，
// 找重复元素就是找两次被指向的元素，也就是环的入口
// 但从不同起点出发，可能进的是“重复值形成的环”（我们要找的环）或“独立小环”（由循环指向产生的环）。
// 为什么只有从 0 出发，一定进入“重复值环”？
// 0 无入度：由于所有 nums[i] ≥ 1，没人指向 0，所以 0 不在任何环内。
// 必经过程：从 0 开始，路径只能是 0→nums[0]→nums[nums[0]]→…，一直往前走，最终必进入某个环。
// 排除独立小环：那些“独立小环”一定是环内各结点互相指向，若起点不在环内就永远进不去。
// 由于 0 不在任何独立小环中，它只能进“重复值环”——唯一的、由某个值被两个不同下标同时指向所形成的环。
// 起点若非 0，就可能误入“独立小环”
// 比如从某个环内结点启动，就会在那个环内循环，却和重复值无关。
// 因此，只有从“无入度”的 0 开始，才能保证第一圈必定是沿着「进入重复值所产生的那个环」而不是其他环。

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 1, 3, 4, 2, 2 };
	cout << sol.findDuplicate(nums) << endl; // 2
	nums = { 3, 1, 3, 4, 2 };
	cout << sol.findDuplicate(nums) << endl; // 3
	nums = { 3, 3, 3, 3, 3 };
	cout << sol.findDuplicate(nums) << endl; // 3
}