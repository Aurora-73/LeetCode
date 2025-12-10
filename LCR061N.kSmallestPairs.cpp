// Created: 2025-12-10
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定两个以升序排列的整数数组 nums1 和 nums2,以及一个整数 k。
定义一对值(u,v)，其中第一个元素来自nums1，第二个元素来自 nums2。
请找到和最小的 k个数对(u1,v1), (u2,v2) ... (uk,vk)。
示例 1：
	输入: nums1 = {1,7,11}, nums2 = {2,4,6}, k = 3
	输出: {1,2},{1,4},{1,6}
	解释: 返回序列中的前 3 对数：
	    {1,2},{1,4},{1,6},{7,2},{7,4},{11,2},{7,6},{11,4},{11,6}
示例 2：
	输入: nums1 = {1,1,2}, nums2 = {1,2,3}, k = 2
	输出: {1,1},{1,1}
	解释: 返回序列中的前 2 对数：
	    {1,1},{1,1},{1,2},{2,1},{1,2},{2,2},{1,3},{1,3},{2,3}
示例 3：
	输入: nums1 = {1,2}, nums2 = {3}, k = 3 
	输出: {1,3},{2,3}
	解释: 也可能序列中所有的数对都被返回:{1,3},{2,3}
提示：
	1 <= nums1.length, nums2.length <= 10^4
	-10^9 <= nums1{i}, nums2{i} <= 10^9
	nums1, nums2 均为升序排列
	1 <= k <= 1000 */

class Solution1 {
public:
	vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k) {
		auto cmp = [](const pair<int, int> &a, const pair<int, int> &b) {
			return a.first + a.second < b.first + b.second;
		};
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp); // 大根堆
		int in = min(k, int(nums1.size())), jn = min(k, int(nums2.size()));
		for(int i = 0; i < in; ++i) {
			for(int j = 0; j < jn; ++j) {
				if(pq.size() < k) {
					pq.emplace(nums1[i], nums2[j]);
				} else if(pq.top().first + pq.top().second > nums1[i] + nums2[j]) {
					pq.pop();
					pq.emplace(nums1[i], nums2[j]);
				}
			}
		}
		vector<vector<int>> res(pq.size(), vector<int>(2));
		for(int i = pq.size() - 1; i >= 0; --i) {
			res[i][0] = pq.top().first;
			res[i][1] = pq.top().second;
			pq.pop();
		}
		return res;
	}
}; // 使用堆的暴力解法，大规模会超时

class Solution2 {
public:
	vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k) {
		auto cmp = [&nums1, &nums2](const pair<int, int> &left, const pair<int, int> &right) {
			return nums1[left.first] + nums2[left.second]
			    > nums1[right.first] + nums2[right.second];
		}; // 小根堆
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
		for(int i = 0; i < min(int(nums1.size()), k); ++i) {
			pq.emplace(i, 0);
		}
		vector<vector<int>> res;
		while(k-- && !pq.empty()) {
			auto [i, j] = pq.top();
			pq.pop();
			res.push_back({ nums1[i], nums2[j] });
			if(++j < nums2.size()) {
				pq.emplace(i, j);
			}
		}
		return res;
	}
}; // 由于两个数组都是递增的，因此下一个最小的元素一定是已经出现过的元素的下标加1后的结果，且最小的元素一定是(0, 0)
// 因此可以先让(0, 0)入队，然后每次出队(i, j)后将(i + 1, j)和(i ,j + 1)入队
// 但是这样会产生重复的元素，因为一个元素有多种可达的路径
// 因此一开始将全部的(i, 0)入队，出队的时仅允许j + 1，这样就避免得了重复
/*
(0,0) → (0,1) → (0,2)

(1,0) → (1,1) → (1,2)

(2,0) → (2,1) → (2,2)
*/

class Solution {
public:
	vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k) {
		auto cmp = [&nums1, &nums2](const pair<int, int> &left, const pair<int, int> &right) {
			return nums1[left.first] + nums2[left.second]
			    > nums1[right.first] + nums2[right.second];
		}; // 小根堆
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
		pq.emplace(0, 0);
		vector<vector<int>> res;
		while(k-- && !pq.empty()) {
			auto [i, j] = pq.top();
			pq.pop();
			res.push_back({ nums1[i], nums2[j] });
			if(j + 1 < nums2.size()) {
				pq.emplace(i, j + 1);
			}
			if(j == 0 && i + 1 < nums1.size()) {
				pq.emplace(i + 1, 0);
			}
		}
		return res;
	}
}; // 允许双向扩展，但是横向的扩展仅在第一行允许，这样每个点只有一条路径可达
/*
(0,0) → (0,1) → (0,2)
↓
(1,0) → (1,1) → (1,2)
↓
(2,0) → (2,1) → (2,2)
*/

int main() {
	Solution sol;
	vector<int> nums1, nums2;
	int k;
	nums1 = { 1, 7, 11 }, nums2 = { 2, 4, 6 }, k = 3;
	cout << sol.kSmallestPairs(nums1, nums2, k) << endl;

	nums1 = { 1, 1, 2 }, nums2 = { 1, 2, 3 }, k = 2;
	cout << sol.kSmallestPairs(nums1, nums2, k) << endl;

	nums1 = { 1, 2 }, nums2 = { 3 }, k = 3;
	cout << sol.kSmallestPairs(nums1, nums2, k) << endl;

	nums1 = { 1, 2, 4, 5, 6 }, nums2 = { 3, 5, 7, 9 }, k = 3;
	cout << sol.kSmallestPairs(nums1, nums2, k) << endl;
}