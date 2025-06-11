// Created: 2025-06-11
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 239. 滑动窗口最大值
给你一个整数数组 nums，有一个大小为k的滑动窗口从数组的最左侧移动到数组的最右侧。
你只可以看到在滑动窗口内的 k个数字。滑动窗口每次只向右移动一位。
返回 滑动窗口中的最大值。
示例 1：
	输入：nums = {1,3,-1,-3,5,3,6,7}, k = 3
	输出：{3,3,5,5,6,7}
	解释：
	滑动窗口的位置                最大值
	---------------               -----
	{1  3  -1} -3  5  3  6  7       3
	 1 {3  -1  -3} 5  3  6  7       3
	 1  3 {-1  -3  5} 3  6  7       5
	 1  3  -1 {-3  5  3} 6  7       5
	 1  3  -1  -3 {5  3  6} 7       6
	 1  3  -1  -3  5 {3  6  7}      7
示例 2：
	输入：nums = {1}, k = 1
	输出：{1}
提示：
	1 <= nums.length <= 10^5
	-10^4<= nums{i} <= 10^4
	1 <= k <= nums.length */

class Solution1 {
public:
	vector<int> maxSlidingWindow(vector<int> &nums, int k) {
		int n = nums.size(), rn = n - k + 1;
		vector<int> res;
		res.reserve(rn);
		multiset<int> s;
		for(int i = 0; i < k; ++i) {
			s.insert(nums[i]);
		}
		res.push_back(*(s.rbegin()));
		for(int i = 1; i < rn; ++i) {
			int a = nums[i - 1], b = nums[i - 1 + k];
			if(a != b) {
				auto it = s.find(a);
				s.erase(it);
				s.insert(b);
			}
			res.push_back(*(s.rbegin()));
		}
		return res;
	}
}; // 保存最大值需要 1、随时获取最大值 2、可以删除和插入任意元素

class Solution2 {
public:
	vector<int> maxSlidingWindow(vector<int> &nums, int k) {
		int n = nums.size(), rn = n - k + 1;
		vector<int> res;
		res.reserve(rn);
		map<int, unsigned> s;
		for(int i = 0; i < k; ++i) {
			++s[nums[i]];
		}
		res.push_back(s.rbegin()->first);
		for(int i = 1; i < rn; ++i) {
			int a = nums[i - 1], b = nums[i - 1 + k];
			if(a != b) {
				auto it = s.find(a);
				if(it->second == 1) {
					s.erase(it);
				} else {
					--it->second;
				}
				++s[b];
			}
			res.push_back(s.rbegin()->first);
		}
		return res;
	}
};

class Solution3 {
public:
	vector<int> maxSlidingWindow(vector<int> &nums, int k) {
		int n = nums.size(), rn = n - k + 1;
		vector<int> res;
		res.reserve(rn);
		priority_queue<pair<int, int>> pq;
		for(int i = 0; i < k; ++i) {
			pq.emplace(nums[i], i);
		}
		res.push_back(pq.top().first);
		for(int i = k; i < n; ++i) {
			pq.emplace(nums[i], i);
			auto [val, index] = pq.top();
			while(i - index >= k) {
				pq.pop();
				val = pq.top().first;
				index = pq.top().second;
			}
			res.push_back(val);
		}
		return res;
	}
}; // 一个同时保存值和下表的 priority_queue，如果top不在窗口内，就一直弹出元素

class Solution {
public:
	vector<int> maxSlidingWindow(vector<int> &nums, int k) {
		int n = nums.size(), rn = n - k + 1;
		vector<int> res;
		res.reserve(rn);
		deque<int> dq;
		for(int i = 0; i < n; ++i) {
			while(!dq.empty() && dq.back() < nums[i]) { // 不能用小于等于，需要保留重复值
				dq.pop_back();
			}
			dq.push_back(nums[i]);
			int top = dq.front();
			if(i >= k - 1) {
				res.push_back(top);
				if(top == nums[i - k + 1]) {
					dq.pop_front();
				}
			}
		}
		return res;
	}
}; // 单调栈：新元素更大，则删掉原本的全部，新元素更小，则添加到尾部

class Solution {
public:
	vector<int> maxSlidingWindow(const vector<int> &nums, int k) {
		int n = nums.size();
		vector<int> res;
		res.reserve(n - k + 1);

		deque<int> dq; // 存放下标，保持 nums[dq] 单调递减
		for(int i = 0; i < n; ++i) {
			// 1. 把队尾所有比 nums[i] 小的下标弹出
			while(!dq.empty() && nums[dq.back()] < nums[i]) {
				dq.pop_back();
			}
			// 2. 把当前下标入队
			dq.push_back(i);

			// 3. 如果队首下标过期（出窗口了），就弹出
			if(dq.front() <= i - k) {
				dq.pop_front();
			}

			// 4. 记录窗口最大值
			if(i >= k - 1) {
				res.push_back(nums[dq.front()]);
			}
		}
		return res;
	}
};
/*  单调栈（更准确地说是“单调双端队列”）的核心思路就是：
在滑动窗口过程中，我们需要能够 快速地（O(1)）拿到当前窗口的最大值，同时 动态维护 随着左右边界移动进出窗口的元素。
要做到这两点，就把窗口里的元素按 下标 存放到一个双端队列 dq 里，并保持队列对应的值 nums[dq[0]], nums[dq[1]], … 单调递减。这样：
队首 dq.front() 对应的就是当前窗口的最大值。
插入新元素时，只要它大于队尾对应的值，就把队尾一个一个弹出，保证单调性。
当窗口左边界右移导致某个下标过期时，检查它是不是在 dq.front()，如果是就弹出；否则它在队列中间，不影响最大值，也无需额外操作。*/

int main() {
	Solution sol;
	vector<int> nums;
	int k;
	nums = { 1, 3, -1, -3, 5, 3, 6, 7 }, k = 3;
	cout << sol.maxSlidingWindow(nums, k) << endl; // { 3, 3, 5, 5, 6, 7 }

	nums = { 1 }, k = 1;
	cout << sol.maxSlidingWindow(nums, k) << endl; // { 1 }

	nums = { -7, -8, 7, 5, 7, 1, 6, 0 }, k = 4;
	cout << sol.maxSlidingWindow(nums, k) << endl; // { 7, 7, 7, 7, 7 }

	nums = { 1, -1 }, k = 1;
	cout << sol.maxSlidingWindow(nums, k) << endl; // { 1, -1 }
}