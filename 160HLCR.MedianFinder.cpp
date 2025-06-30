// Created: 2025-06-30
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 160. 数据流中的中位数
中位数是有序整数列表中的中间值。
如果列表的大小是偶数，则没有中间值，中位数是两个中间值的平均值。
例如，
{2,3,4} 的中位数是 3
{2,3} 的中位数是 (2 + 3) / 2 = 2.5
设计一个支持以下两种操作的数据结构：
	void addNum(int num) - 从数据流中添加一个整数到数据结构中。
	double findMedian() - 返回目前所有元素的中位数。
示例 1：
	输入：
	{"MedianFinder","addNum","addNum","findMedian","addNum","findMedian"}
	{{},{1},{2},{},{3},{}}
	输出：{null,null,null,1.50000,null,2.00000}
示例 2：
	输入：
	{"MedianFinder","addNum","findMedian","addNum","findMedian"}
	{{},{2},{},{3},{}}
	输出：{null,null,2.00000,null,2.50000}
提示：
	最多会对addNum、findMedian 进行50000次调用。 */

class MedianFinder {
public:
	/** initialize your data structure here. */
	MedianFinder() { }

	void addNum(int num) {
		if(bigger.size() < smaller.size()) {
			smaller.push(num);
			bigger.push(smaller.top());
			smaller.pop();
		} else {
			bigger.push(num);
			smaller.push(bigger.top());
			bigger.pop();
		}
	}

	double findMedian() {
		if(bigger.size() == smaller.size()) {
			return (bigger.top() + smaller.top()) / 2.0;
		} else {
			return smaller.top();
		}
	}

private:
	priority_queue<int> smaller; // 至多比bigger多一个
	priority_queue<int, vector<int>, greater<int>> bigger;
};

int main() { }