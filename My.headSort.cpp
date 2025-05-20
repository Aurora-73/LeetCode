// Created: 2025-05-19
#include "MyUtils.h"

/* 大根堆
siftDown
siftUp
BuildHeap
HeapSort 
下标从 0 开始 最大为 n - 1，则
节点 i 的 left 为 2 * i + 1  right 为 2 * i + 2 
节点 i 的 父节点为  (i - 1) / 2 
最后一个非叶子结点为 n / 2 - 1  */

void siftDown(vector<int> &nums, int index, int size) {
	int temp = nums[index];
	while(index < size / 2) { // 需要包含最后一个非叶子节点
		int maxChild = 2 * index + 1;
		if(maxChild + 1 < size && nums[maxChild + 1] > nums[maxChild]) {
			++maxChild;
		}
		if(nums[maxChild] > temp) {
			nums[index] = nums[maxChild];
			index = maxChild;
		} else {
			break;
		}
	}
	nums[index] = temp;
} // 下滤

void siftUp(vector<int> &nums, int index) {
	int temp = nums[index];
	while(index > 0) { // 0 号节点没有父节点，不需要访问
		int parent = (index - 1) / 2;
		if(nums[parent] < temp) {
			nums[index] = nums[parent];
			index = parent;
		} else {
			break;
		}
	}
	nums[index] = temp;
} // 上浮

void buildHeap(vector<int> &nums) {
	int n = nums.size();
	for(int i = n / 2 - 1; i >= 0; --i) {
		siftDown(nums, i, n);
	}
}

void heapSort(vector<int> &nums) {
	buildHeap(nums);
	int n = nums.size();
	for(int i = n - 1; i > 0; --i) {
		swap(nums[0], nums[i]);
		siftDown(nums, 0, i);
	}
}

int main() {
	vector<int> nums = { 1, 2, 4, 3, 10, 9 };
	heapSort(nums);
	cout << nums;
}