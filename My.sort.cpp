// Created: 2025-05-17
#include "MyUtils.hpp"
using namespace std;

/*常见的排序算法*/

class InsertionSort {
public:
	// vector<int> 版本
	static void sort(std::vector<int> &vec) {
		int n = vec.size();
		for(int i = 1; i < n; ++i) {
			int temp = vec[i];
			int j = i;
			while(j > 0 && vec[j - 1] > temp) {
				vec[j] = vec[j - 1];
				--j;
			}
			vec[j] = temp;
		}
	}

	// 泛型迭代器版本（双向迭代器）
	template <typename BidirectionalIterator>
	static void sort(BidirectionalIterator begin, BidirectionalIterator end) {
		using ValueType = typename std::iterator_traits<BidirectionalIterator>::value_type;

		for(auto it = std::next(begin); it != end; ++it) {
			ValueType temp = std::move(*it);
			auto insertPos = it;

			while(insertPos != begin && *(std::prev(insertPos)) > temp) {
				*insertPos = std::move(*(std::prev(insertPos)));
				--insertPos;
			}
			*insertPos = std::move(temp);
		}
	}
};

class SelectionSort {
public:
	// vector<int> 版本
	static void sort(std::vector<int> &vec) {
		int n = vec.size();
		for(int i = 0; i < n; ++i) {
			int min_index = i;
			for(int j = i + 1; j < n; ++j) {
				if(vec[j] < vec[min_index]) {
					min_index = j;
				}
			}
			if(min_index != i) {
				std::swap(vec[i], vec[min_index]);
			}
		}
	}

	// 泛型迭代器版本（前向迭代器即可）
	template <typename ForwardIterator>
	static void sort(ForwardIterator begin, ForwardIterator end) {
		for(auto it1 = begin; it1 != end; ++it1) {
			ForwardIterator minIt = it1;
			for(auto it2 = std::next(it1); it2 != end; ++it2) {
				if(*it2 < *minIt) {
					minIt = it2;
				}
			}
			if(minIt != it1) {
				std::swap(*it1, *minIt);
			}
		}
	}
};

class HeapSort {
public:
	vector<int> sortArray(vector<int> &nums) {
		int n = nums.size();
		if(n <= 1) return nums;

		// 建大根堆
		for(int i = (n - 2) / 2; i >= 0; --i) {
			adjustHeap(nums, n, i);
		}

		// 依次取堆顶
		for(int i = n - 1; i > 0; --i) {
			swap(nums[0], nums[i]);
			adjustHeap(nums, i, 0);
		}
		return nums;
	}

private:
	void adjustHeap(vector<int> &nums, int n, int parent) {
		int pivot = nums[parent];
		int child = parent * 2 + 1; // 左孩子, nums[i] 的孩子是nums[i * 2 + 1]和nums[i * 2 + 2]

		while(child < n) {
			// 选更大的孩子
			if(child + 1 < n && nums[child + 1] > nums[child]) {
				++child;
			}
			if(nums[child] > pivot) {
				nums[parent] = nums[child];
				parent = child;
				child = parent * 2 + 1;
			} else {
				break;
			}
		}
		nums[parent] = pivot;
	} // 对节点k进行下滤操作
}; // 堆排序

// MergeSort
class MergeSort {
public:
	vector<int> sortArray(vector<int> &nums) {
		vector<int> temp(nums.size());
		mergeSort(nums, temp, 0, nums.size() - 1);
		return nums;
	}

private:
	void mergeSort(vector<int> &nums, vector<int> &temp, int left, int right) {
		if(right <= left) return;
		int mid = left + (right - left) / 2;
		mergeSort(nums, temp, left, mid);
		mergeSort(nums, temp, mid + 1, right);
		if(nums[mid] <= nums[mid + 1]) return; // 已经有序
		merge(nums, temp, left, mid, right);
	}

	void merge(vector<int> &nums, vector<int> &temp, int left, int mid, int right) {
		int a = left, b = mid + 1, c = left;
		while(a <= mid && b <= right) {
			if(nums[a] <= nums[b]) { // 等于号才能保证稳定性
				temp[c++] = nums[a++];
			} else {
				temp[c++] = nums[b++];
			}
		}
		while(a <= mid) temp[c++] = nums[a++];
		while(b <= right) temp[c++] = nums[b++];
		for(; left <= right; ++left) nums[left] = temp[left];
	}
};

// QuickSort
class QuickSort {
public:
	vector<int> sortArray(vector<int> &nums) {
		quickSort(nums, 0, nums.size() - 1);
		return nums;
	}

private:
	void quickSort(vector<int> &nums, int l, int r) {
		if(r - l < 1) return;
		auto [eq, gt] = partition(nums, l, r);
		quickSort(nums, l, eq - 1);
		quickSort(nums, gt + 1, r);
	}
	pair<int, int> partition(vector<int> &nums, int l, int r) {
		int a = nums[l], b = nums[(r - l) / 2 + l], c = nums[r];
		int pivot = (long long)a - max({ a, b, c }) + b - min({ a, b, c }) + c; // 或用小函数求中位
		int eq = l, gt = r, k = l;
		while(k <= gt) {
			if(nums[k] == pivot) {
				++k;
			} else if(nums[k] > pivot) {
				swap(nums[k], nums[gt]);
				--gt;
			} else {
				swap(nums[k], nums[eq]);
				++eq, ++k;
			}
		}
		return { eq, gt };
	}
};

int main() { }