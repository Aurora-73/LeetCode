// Created: 2026-01-07
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 随机产生数字并传递给一个方法。
你能否完成这个方法，在每次产生新值时，寻找当前所有值的中间值（中位数）并保存。
中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。
例如，
    {2,3,4}的中位数是 3
    {2,3} 的中位数是 (2 + 3) / 2 = 2.5
设计一个支持以下两种操作的数据结构：
	void addNum(int num) - 从数据流中添加一个整数到数据结构中。
	double findMedian() - 返回目前所有元素的中位数。
示例：
    addNum(1)
    addNum(2)
    findMedian() -> 1.5
    addNum(3) 
    findMedian() -> 2 */

class MedianFinder1 {
	multiset<int> nums;
	multiset<int>::iterator left, right;

public:
	MedianFinder1() : left(nums.end()), right(nums.end()) { }

	void addNum(int num) {
		const size_t n = nums.size();

		nums.insert(num);
		if(!n) {
			left = right = nums.begin();
		} else if(n & 1) {
			if(num < *left) {
				left--;
			} else {
				right++;
			}
		} else {
			if(num > *left && num < *right) {
				left++;
				right--;
			} else if(num >= *right) {
				left++;
			} else {
				right--;
				left = right;
			}
		}
	}

	double findMedian() {
		return (*left + *right) / 2.0;
	}
};

class MedianFinder {
public:
	/** initialize your data structure here. */
	MedianFinder() { }

	void addNum(int num) {
		if(large.size() == small.size()) {
			// num希望放到small里面
			if(!large.empty() && num > large.top()) {
				small.push(large.top());
				large.pop();
				large.push(num);
			} else {
				small.push(num);
			}
		} else {
			// num希望放到large里面
			if(!small.empty() && num < small.top()) {
				large.push(small.top());
				small.pop();
				small.push(num);
			} else {
				large.push(num);
			}
		}
	}

	double findMedian() {
		if(large.size() == small.size()) {
			return (large.top() + small.top()) / 2.0;
		} else {
			return small.top();
		}
	}

private:
	priority_queue<int> small;
	priority_queue<int, vector<int>, greater<int>> large;
};

int main() {
	MedianFinder mf;
	for(int i = 0; i < 15; ++i) {
		mf.addNum(i);
		cout << mf.findMedian() << endl;
	}
}