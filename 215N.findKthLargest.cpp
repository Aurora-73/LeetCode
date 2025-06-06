// Created: 2025-05-19
#include "MyUtils.hpp"

/*  */

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

class Solution4 {
public:
	int quickselect(vector<int> &nums, int l, int r, int k) {
		if(l == r) return nums[l];

		// 三数取中法选 pivot
		int mid = l + (r - l) / 2;
		int a = nums[l], b = nums[mid], c = nums[r];
		int pivot = (a < b ? (b < c ? b : (a < c ? c : a)) : (c < b ? b : (c < a ? c : a)));

		int i = l, j = r;
		// 外层用 i<=j 保证所有元素都被检查
		while(i <= j) {
			// 找到第一个 >= pivot 的 i
			while(i <= j && nums[i] < pivot) ++i;
			// 找到第一个 <= pivot 的 j
			while(i <= j && nums[j] > pivot) --j;
			if(i < j) {
				swap(nums[i], nums[j]);
				++i; // 交换后推进，避免死循环
				--j;
			}
		}

		if(k <= j)
			return quickselect(nums, l, j, k);
		else /* k >= i */
			return quickselect(nums, i, r, k);
	}

	int findKthLargest(vector<int> &nums, int k) {
		int n = nums.size();
		return quickselect(nums, 0, n - 1, n - k);
	}
};

int main() {
	Solution4 sol1;
	vector<int> nums = { 3, 2, 1, 5, 6, 4 };
	int k = 2;
	cout << sol1.findKthLargest(nums, k);
}