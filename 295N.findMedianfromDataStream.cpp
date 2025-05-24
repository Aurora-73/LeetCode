// Created: 2025-05-20
#include "MyUtils.h"

/*295. 数据流的中位数
中位数是有序整数列表中的中间值。如果列表的大小是偶数，则没有中间值，中位数是两个中间值的平均值。
例如 arr = [2,3,4] 的中位数是 3 。
例如 arr = [2,3] 的中位数是 (2 + 3) / 2 = 2.5 。
实现 MedianFinder 类:
MedianFinder() 初始化 MedianFinder 对象。
void addNum(int num) 将数据流中的整数 num 添加到数据结构中。
double findMedian() 返回到目前为止所有元素的中位数。与实际答案相差 10-5 以内的答案将被接受。*/

class MedianFinder {
public:
	MedianFinder() {}

	void addNum_old(int num) {
		if(large.size() == small.size()) {
			if(small.size() && num < small.top()) {
				small.push(num);
				large.push(small.top());
				small.pop();
			} else {
				large.push(num);
			}
		} else {
			if(large.size() && num > large.top()) {
				large.push(num);
				small.push(large.top());
				large.pop();
			} else {
				small.push(num);
			}
		}
	} // 优先让large更大

	void addNum(int num) {
		// 先把 num 推入 large（右半边），再把堆顶“最小的”放到 small
		large.push(num);
		small.push(large.top());
		large.pop();

		// 保证 large.size() >= small.size()
		if(small.size() > large.size()) {
			large.push(small.top());
			small.pop();
		}
	}

	double findMedian() {
		if(large.size() > small.size()) {
			return large.top();
		}
		return (static_cast<double>(large.top()) + small.top()) / 2;
	}

private:
	priority_queue<int, vector<int>, greater<int>> large; // 小根堆
	priority_queue<int> small; // 大根堆
};

int main() {
	MedianFinder *obj = new MedianFinder();
	vector<int> nums = {0, -1, 2, -3, 4, -5, 6, -7};
	for(auto &x : nums) {
		obj->addNum(x);
		cout << obj->findMedian() << " ";
	}
}