// Created: 2025-05-19
#include "MyUtils.h"

/*373. 查找和最小的 K 对数字
给定两个以 非递减顺序排列 的整数数组 nums1 和 nums2 , 以及一个整数 k 。
定义一对值 (u,v)，其中第一个元素来自 nums1，第二个元素来自 nums2 。
请找到和最小的 k 个数对 (u1,v1),  (u2,v2)  ...  (uk,vk) 。*/

class Solution1 {
public:
	vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k) {
		if(nums1.empty() || nums2.empty() || k <= 0) return {};

		auto comp = [&](const pair<int, int> &a, const pair<int, int> &b) {
			return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
		};

		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> q(comp);
		set<pair<int, int>> visited;
		vector<vector<int>> res;

		q.push({ 0, 0 });
		visited.insert({ 0, 0 });

		while(!q.empty() && res.size() < k) {
			auto [a, b] = q.top();
			q.pop();
			res.push_back({ nums1[a], nums2[b] });

			// 尝试添加下一个可能的候选
			if(a + 1 < nums1.size() && !visited.count({ a + 1, b })) {
				q.push({ a + 1, b });
				visited.insert({ a + 1, b });
			}

			if(b + 1 < nums2.size() && !visited.count({ a, b + 1 })) {
				q.push({ a, b + 1 });
				visited.insert({ a, b + 1 });
			}
		}

		return res;
	}
}; // 使用 set 防重复

class Solution2 {
public:
	vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k) {
		auto comp = [&](pair<int, int> a, pair<int, int> b) {
			return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
		};
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> q(comp);
		vector<vector<int>> res;
		int n1 = nums1.size(), n2 = nums2.size();
		for(int i = 0; i < n1; ++i) {
			q.push({ i, 0 });
		}
		while(res.size() < k && !q.empty()) {
			auto [a, b] = q.top();
			q.pop();
			res.push_back({ nums1[a], nums2[b] });
			if(b + 1 < n2) {
				q.push({ a, b + 1 });
			}
		}
		return res;
	}
}; // 只允许行扩展，初始时入队第一列的全部元素，从而防止重复
/*
(0,0) → (0,1) → (0,2)

(1,0) → (1,1) → (1,2)

(2,0) → (2,1) → (2,2)
*/

class Solution3 {
public:
	vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k) {
		auto comp = [&](pair<int, int> a, pair<int, int> b) {
			return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
		};
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> q(comp);
		vector<vector<int>> res;
		int n1 = nums1.size(), n2 = nums2.size();
		q.push({ 0, 0 });
		while(res.size() < k && !q.empty()) {
			auto [a, b] = q.top();
			q.pop();
			res.push_back({ nums1[a], nums2[b] });
			if(b == 0 && a + 1 < n1) {
				q.push({ a + 1, b });
			}
			if(b + 1 < n2) {
				q.push({ a, b + 1 });
			}
		}
		return res;
	}
}; // 初始时不在入队第一列的全部元素，只入队第一个元素，但是行扩展只在列为0的时候允许，从而避免重复
/*
(0,0) → (0,1) → (0,2)
↓
(1,0) → (1,1) → (1,2)
↓
(2,0) → (2,1) → (2,2)
*/

int main() {
	Solution3 sol;
}