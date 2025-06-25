// Created: 2025-06-19
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 287. 寻找重复数
给定一个包含 n + 1 个整数的数组nums，其数字都在{1, n}范围内（包括 1 和 n），可知至少存在一个重复的整数。
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
// 注意区分比较 120ELCR

class Solution1 {
public:
	int findDuplicate(vector<int> &nums) {
		int n = nums.size();
		for(int i = 0; i < n; ++i) {
			while(nums[i] != i) {
				if(nums[i] == nums[nums[i]]) {
					return nums[i];
				}
				swap(nums[i], nums[nums[i]]);
			}
		}
		return -1;
	}
}; // 原地置换法，会修改数组，和 120ELCR 相同的解法

/* 原地置换法
我们把数组看作一个从「下标」到「值」的映射：
    下标范围是 0 … n-1
    值的取值范围也是 0…n-1（对于 LCR 120）或 1…n（对于 287）
当下标和值都在同一个区间时，就能把每个元素 “放到它该去的位置”——也就是把 A[i] 放到下标为 A[i] 的那个槽里。
    如果那个槽空着（恰好存的是它自己），就放进去；
    如果那个槽已经有一个相同的值了，就意味着这个值重复了，我们就可以直接返回它。


对于每一个下标 i：
    检查当前位置是否已就位
        如果 documents[i] == i，说明它已经在“正确位置”，跳过，继续下一个 i+1。

    尝试置换
        否则，看目标位置 j = documents[i] 上的值：
            若 documents[j] == documents[i]，说明“位置 j”上已经有了一个同样的文件 id，当前这个也是要放进来，故找到了重复，直接返回 documents[i]。
            否则，交换 documents[i] 和 documents[j]，把当前位置的值放到它“该在”的位置，让被换上来的值在下一个循环中重新检查。

    重复上述过程，直到遍历完所有 i 或者提前返回。
    
这样做的要点是，每次 swap 都是把一个 “未就位” 的元素向它正确的位置推进了一步，
最终要么所有元素都就位（这种情况下无重复，但按题意一定有重复，所以会在途中发现冲突），要么在赋值冲突时立刻返回。 */

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