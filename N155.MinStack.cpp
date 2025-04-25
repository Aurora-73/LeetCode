#include "MyUtils.h"
/*155. 最小栈
中等
相关标签
相关企业
提示
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
实现 MinStack 类:
MinStack() 初始化堆栈对象。
void push(int val) 将元素val推入堆栈。
void pop() 删除堆栈顶部的元素。
int top() 获取堆栈顶部的元素。
int getMin() 获取堆栈中的最小元素。
-2^31 <= val <= 2^31 - 1
pop、top 和 getMin 操作总是在 非空栈 上调用
push, pop, top, and getMin最多被调用 3 * 104 次
*/

class MinStack {
private:
	stack<int> st;
	unordered_multiset<int> se;
	std::priority_queue<int, std::vector<int>, std::greater<int>> p; // 默认是大顶堆
public:
	MinStack() { }

	void push(int val) {
		st.push(val);
		se.insert(val);
		p.push(val);
	}

	void pop() {
		int top = st.top();
		st.pop();
		auto find = se.find(top);
		se.erase(find); // 直接se.erase(top)是删除所有值等于top的元素
	}

	int top() {
		return st.top();
	}

	int getMin() {
		int val = p.top();
		while(!se.count(val)) {
			p.pop();
			val = p.top();
		}
		return val;
	}
};
// 常数时间最小的元素 -> 用堆
// 但是堆删除栈的top的元素很复杂
// 不删除堆中的元素，如果堆中弹出的元素已经被删除，就继续弹出
// 用set记录目前还在栈中的元素

class MinStack {
private:
	stack<int> vals;
	stack<int> Mins;

public:
	MinStack() { }

	void push(int val) {
		vals.push(val);
		if(!Mins.empty()) {
			Mins.push(min(val, Mins.top()));
		} else {
			Mins.push(val);
		} // 如果初始化的时候直接在MinStake中压入一个INT_MAX 并且不会对空栈弹出，则不需要判断
	}

	void pop() {
		vals.pop();
		Mins.pop();
	}

	int top() {
		return vals.top();
	}

	int getMin() {
		return Mins.top();
	}
};
// 栈的性质是先进后出，因此每一时刻的最小值都是可以提前计算出来的，将其保存到MinStack中