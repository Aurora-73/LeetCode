// Created: 2025-06-24
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 183. 望远镜中最高的海拔
科技馆内有一台虚拟观景望远镜，它可以用来观测特定纬度地区的地形情况。
该纬度的海拔数据记于数组 heights，其中 heights{i} 表示对应位置的海拔高度。
请找出并返回望远镜视野范围 limit 内，可以观测到的最高海拔值。
示例 1：
	输入：heights = {14,2,27,-5,28,13,39}, limit = 3
	输出：{27,27,28,28,39}
	解释：
	  滑动窗口的位置                最大值
	---------------               -----
	{14 2 27} -5 28 13 39          27
	14 {2 27 -5} 28 13 39          27
	14 2 {27 -5 28} 13 39          28
	14 2 27 {-5 28 13} 39          28
	14 2 27 -5 {28 13 39}          39
提示：
	你可以假设输入总是有效的，在输入数组不为空的情况下：
	1 <= limit <= heights.length
	-10000 <= heights{i} <= 10000 */

class Solution {
public:
	vector<int> maxAltitude(vector<int> &heights, int limit) {
		int n = heights.size();
		vector<int> res;
		res.reserve(n - limit + 1);
		deque<int> maxs; // maxs内部是递减的
		for(int i = 0; i < n; ++i) {
			while(!maxs.empty() && maxs.back() < heights[i]) {
				maxs.pop_back();
			}
			maxs.push_back(heights[i]);
			if(i >= limit - 1) {
				res.push_back(maxs.front());
				if(maxs.front() == heights[i - limit + 1]) {
					maxs.pop_front();
				}
			}
		}
		return res;
	}
};

/* 在常见的「维护序列中某种极值／单调性」的问题里，我们大致可以把套路分成两大类：
单调栈（Monotonic Stack）场景
单调双端队列（Monotonic Deque／Queue）场景
一、什么时候用单调栈（Stack）
	关注「元素之间的前后关系」，但「窗口大小可变或不明确」。
	通常用于“对于序列中每个元素，
	找到它左边／右边第一个比它大（或小）的元素”、“求每个元素盖过多少房子”这类「Next Greater Element」、「柱状图最大矩形」等问题。
	不需要固定窗口，只用一次遍历＋栈顶比较，遇到不满足单调性就 pop。
	实现要点
	用一个栈保存下标或值，栈内保持严格单调（增／减）
	遍历元素时：
	当新元素破坏单调性，就 pop 栈顶并处理「弹出值←→新值」的关系。
	然后把新元素 push 进栈。
	典型操作都是 push、pop、peek，没有「从队头删除超出范围」的需求。
	典型题型
	「下一个更大元素」（Next Greater Element I/II）
	「柱状图中最大的矩形」
	「直方图雨水收集」
	「每日温度」
	「132 模式检测」
二、什么时候用单调双端队列（Deque）
	关注「滑动窗口」这类固定大小或可变大小范围内的极值维护。
	典型场景：给定窗口大小 k，每次窗口往右滑一格，要快速获取当前窗口的最大/最小值。
	需要在窗口右端入元素，同时在窗口左端可能出元素。
	实现要点
	用一个双端队列 dq 存放下标，并保持对应值的单调（通常是 严格递减 来维护最大值）。
	遍历到 i：
	尾部维护单调：while dq 不空 且 heights[dq.back()] < heights[i]，pop_back()
	push_back(i)
	头部清理过期：如果 dq.front() <= i - k，pop_front()
	当 i >= k-1 时，res.push_back( heights[dq.front()] )
	这样既能 O(1) 出队过期元素，又能 O(1) 获取当前极值。
总结
	需求场景	用 什么？	备注
	「Next Greater／Next Smaller」	单调 栈	只关心相对前后元素的关系；不限制窗口大小
	「滑动窗口固定大小 k」	单调 **双端队列（Deque）」	既要尾入，也要头出；队头存极值
	「BFS／层序遍历／动态窗口大小」	普通队列 + （可选）单调队列	普通队列控制访问顺序，单调队列维护极值
牢记：
	Stack → 保持单调，只 push/pop 栈顶，用于相对位置关系；
	Deque → 头尾都能操作，用于滑动窗口里维护过期和单调极值；
	Queue → FIFO 结构，用于层序、滑窗顺序入出，必要时可配合单调队列一起用。 */

int main() {
	Solution sol;
	vector<int> heights;
	int limit;
	heights = { 14, 2, 27, -5, 28, 13, 39 }, limit = 3;
	cout << sol.maxAltitude(heights, limit) << endl; // {27,27,28,28,39}
	heights = { 1, 3, 1, 2, 0, 5 }, limit = 3;
	cout << sol.maxAltitude(heights, limit) << endl; // {3,3,2,5}
}