// Created: 2025-06-29
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 159. 库存管理 III
仓库管理员以数组 stock 形式记录商品库存表，其中 stock{i} 表示对应商品库存余量。
请返回库存余量最少的 cnt 个商品余量，返回顺序不限。
示例 1：
	输入：stock = {2,5,7,4}, cnt = 1
	输出：{2}
示例 2：
	输入：stock = {0,2,3,6}, cnt = 2
	输出：{0,2} 或 {2,0}
提示：
	0 <= cnt <= stock.length <= 10000
	0 <= stock{i} <= 10000 */

class Solution {
public:
	vector<int> inventoryManagement(vector<int> &stock, int cnt) {
		if(cnt == 0) return {};
		priority_queue<int> pq;
		for(int i = 0; i < cnt; ++i) {
			pq.push(stock[i]);
		}
		int n = stock.size();
		for(int i = cnt; i < n; ++i) {
			if(stock[i] < pq.top()) {
				pq.pop();
				pq.push(stock[i]);
			}
		}
		vector<int> res;
		res.reserve(cnt);
		while(!pq.empty()) {
			res.push_back(pq.top());
			pq.pop();
		}
		return res;
	}
}; // 时间复杂度 O(n * log k)

class Solution {
public:
	vector<int> inventoryManagement(vector<int> &stock, int cnt) {
		srand((unsigned)time(NULL));
		randomized_selected(stock, 0, (int)stock.size() - 1, cnt);
		vector<int> vec;
		for(int i = 0; i < cnt; ++i) {
			vec.push_back(stock[i]);
		}
		return vec;
	}

private:
	int partition(vector<int> &nums, int l, int r) {
		int pivot = nums[r];
		int i = l - 1;
		for(int j = l; j <= r - 1; ++j) {
			if(nums[j] <= pivot) {
				i = i + 1;
				swap(nums[i], nums[j]);
			}
		}
		swap(nums[i + 1], nums[r]);
		return i + 1;
	}

	// 基于随机的划分
	int randomized_partition(vector<int> &nums, int l, int r) {
		int i = rand() % (r - l + 1) + l;
		swap(nums[r], nums[i]);
		return partition(nums, l, r);
	}

	void randomized_selected(vector<int> &stock, int l, int r, int cnt) {
		if(l >= r) {
			return;
		}
		int pos = randomized_partition(stock, l, r);
		int num = pos - l + 1;
		if(cnt == num) {
			return;
		} else if(cnt < num) {
			randomized_selected(stock, l, pos - 1, cnt);
		} else {
			randomized_selected(stock, pos + 1, r, cnt - num);
		}
	}
}; // 使用快排的partition算法，不断对数组进行划分，直到当前枢轴就是cnt - 1位，期望时间复杂度O(n)

int main() {
	Solution sol;
	vector<int> stock;
	int cnt;
	stock = { 2, 5, 7, 4 }, cnt = 1;
	cout << sol.inventoryManagement(stock, cnt) << endl; // {2}
	stock = { 0, 2, 3, 6 }, cnt = 2;
	cout << sol.inventoryManagement(stock, cnt) << endl; // {0, 2}
}