// Created: 2026-01-05
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 设计一个算法，找出数组中最小的k个数。
以任意顺序返回这k个数均可。
示例：
输入： arr = {1,3,5,7,2,4,6,8}, k = 4
输出： {1,2,3,4}
提示：
	0 <= len(arr) <= 100000
	0 <= k <= min(100000, len(arr)) */

class Solution1 {
public:
	vector<int> smallestK(vector<int> &arr, int k) {
		priority_queue<int> pq;
		for(int a : arr) {
			if(pq.size() < k)
				pq.push(a);
			else {
				if(pq.top() > a) {
					pq.pop();
					if(pq.size() < k) pq.push(a);
				}
			}
		}
		vector<int> res;
		res.reserve(k);
		while(!pq.empty()) {
			res.push_back(pq.top());
			pq.pop();
		}
		return res;
	}
}; // priority_queue

class Solution {
public:
	vector<int> smallestK(vector<int> &arr, int k) {
		if(k == 0 || arr.empty()) return {};
		int l = 0, r = arr.size() - 1;
		while(l <= r) {
			auto [pl, pr] = partition(arr, l, r);
			if(k < pl) {
				r = pl - 1;
			} else if(k > pr) {
				l = pr + 1;
			} else {
				break;
			}
		}
		return vector<int>(arr.begin(), arr.begin() + k);
	}

private:
	pair<int, int> partition(vector<int> &arr, int l, int r) {
		int pivot = arr[l], lt = l, gt = r;
		for(int i = l + 1; i <= gt; ++i) {
			if(arr[i] < pivot) {
				arr[lt] = arr[i];
				arr[i] = pivot;
				++lt;
			} else if(arr[i] > pivot) {
				swap(arr[i], arr[gt]);
				--gt, --i;
			}
		}
		return { lt, gt };
	}
}; // partition

int main() {
	Solution sol;
	vector<int> arr;
	int k;
	arr = { 1, 3, 5, 7, 2, 4, 6, 8 }, k = 4;
	cout << sol.smallestK(arr, k) << endl;
}