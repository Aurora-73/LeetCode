// Created: 2025-05-19
#include "MyUtils.hpp"

/* 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。
示例 1:
	输入: {3,2,1,5,6,4}, k = 2
	输出: 5
示例2:
	输入: {3,2,3,1,2,4,5,5,6}, k = 4
	输出: 4
提示： 
	1 <= k <= nums.length <= 10^5
	-10^4<= nums{i} <= 10^4 */

class Solution1 {
public:
	int findKthLargest(vector<int> &nums, int k) {
		priority_queue<int, vector<int>, greater<int>> q(nums.begin(), nums.begin() + k);
		for(size_t i = k; i < nums.size(); ++i) {
			if(q.top() < nums[i]) {
				q.pop();
				q.push(nums[i]);
			}
		}
		return q.top();
	}
};
/*  如果要用lamda表达式作比较，则
auto cmp = [](int a, int b) { return a > b; };
std::priority_queue<int, std::vector<int>, decltype(cmp)> q(cmp);
// 标准仿函数有默认构造函数，可以不用传对象。
// lambda没有默认构造函数，必须传对象给构造函数。   */

class Solution2 {
public:
	int findKthLargest(vector<int> &nums, int k) {
		vector<int> heap(nums.begin(), nums.begin() + k);
		for(int i = k / 2 - 1; i >= 0; --i) {
			siftDown(heap, i, k);
		}
		int n = nums.size();
		for(int i = k; i < n; ++i) {
			if(heap[0] < nums[i]) {
				heap[0] = nums[i];
				siftDown(heap, 0, k);
			}
		}
		return heap[0];
	}
	void siftDown(vector<int> &nums, int index, int size) {
		int temp = nums[index];
		while(index < size / 2) { // 需要包含最后一个非叶子节点
			int minChild = 2 * index + 1;
			if(minChild + 1 < size && nums[minChild + 1] < nums[minChild]) {
				++minChild;
			}
			if(nums[minChild] < temp) { // 小根堆
				nums[index] = nums[minChild];
				index = minChild;
			} else {
				break;
			}
		}
		nums[index] = temp;
	} // 下滤
};

class Solution3 {
public:
	int findKthLargest(vector<int> &nums, int k) {
		// nth_element 会把第 (k-1) 小的位置放到 nums[k-1]，
		// 同时左边都 <= 它，右边都 >= 它
		nth_element(nums.begin(), nums.begin() + k - 1, nums.end(), greater<int>());
		return nums[k - 1];
	}
};

class Solution {
public:
	int findKthLargest(vector<int> &nums, int k) {
		int l = 0, r = nums.size() - 1;
		k = nums.size() - k;
		while(true) {
			auto [eq, gt] = partition(nums, l, r);
			if(eq <= k && gt >= k) {
				return nums[k];
			} else if(eq > k) {
				r = eq - 1;
			} else {
				l = gt + 1;
			}
		}
	}

private:
	pair<int, int> partition(vector<int> &nums, int l, int r) {
		int mid = l + (r - l) / 2;
		int a = nums[l], b = nums[mid], c = nums[r]; // 三数取中法选 pivot
		int pivot = a + b + c - max({ a, b, c }) - min({ a, b, c });
		int eq = l, gt = r, i = l;
		while(i <= gt) {
			if(nums[i] == pivot) {
				++i;
			} else if(nums[i] < pivot) {
				swap(nums[i], nums[eq]);
				++i, ++eq;
			} else {
				swap(nums[i], nums[gt]);
				--gt;
			}
		}
		return { eq, gt };
	}
};

int main() {
	Solution sol;
	vector<int> nums = { 3, 2, 1, 5, 6, 4 };
	int k = 2;
	cout << sol.findKthLargest(nums, k);
}