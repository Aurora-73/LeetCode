#include "MyUtils.hpp"

/* 155. 最小栈
设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。
实现 MinStack 类:
	MinStack() 初始化堆栈对象。
	void push(int val) 将元素val推入堆栈。
	void pop() 删除堆栈顶部的元素。
	int top() 获取堆栈顶部的元素。
	int getMin() 获取堆栈中的最小元素。
提示：
	-2^31<= val <= 231- 1
	pop、top 和 getMin 操作总是在 非空栈 上调用
	push,pop,top, andgetMin最多被调用3 * 10^4次 */

class MinStack1 {
private:
	stack<int> vals;
	stack<int> Mins;

public:
	MinStack1() { }

	void push(int val) {
		vals.push(val);
		if(!Mins.empty()) {
			Mins.push(min(val, Mins.top()));
		} else {
			Mins.push(val);
		} // 如果初始化的时候直接在MinStake中压入一个numeric_limits<int>::max() 并且不会对空栈弹出，则不需要判断
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

class MinStack2 {
public:
	MinStack2() {
		mins.push(INT_MAX);
	}

	void push(int val) {
		vals.push(val);
		if(val <= mins.top()) {
			mins.push(val);
		}
	}

	void pop() {
		if(vals.top() == mins.top()) {
			mins.pop();
		}
		vals.pop();
	}

	int top() {
		return vals.top();
	}

	int getMin() {
		return mins.top();
	}

private:
	stack<int> vals, mins;
}; // min_stack使用惰性栈，并用INT_MAX作为哨兵

class MinStack {
private:
	stack<long long> st; // 存 diff
	long long curMin;

public:
	MinStack() { }

	void push(int val) {
		if(st.empty()) {
			curMin = val;
			st.push(0); // diff = val - curMin = 0
		} else {
			long long diff = (long long)val - curMin;
			st.push(diff);
			if(diff < 0) {
				// val 成为新的最小值
				curMin = val;
			}
		}
	}

	void pop() {
		long long diff = st.top();
		st.pop();

		if(diff < 0) {
			// 说明 pop 的是“当时的最小值”
			// 需要恢复之前的最小值
			curMin = curMin - diff;
		}
	}

	int top() {
		long long diff = st.top();
		if(diff >= 0) {
			return curMin + diff;
		} else {
			// diff < 0 ⇒ 当前元素就是最小值
			return curMin;
		}
	}

	int getMin() {
		return curMin;
	}
}; /* 单个栈版
栈里不存原值，而是存：
	diff = val - 当前最小值
并且维护一个变量：
	curMin = 当前栈内最小值
关键：
	diff < 0 ⇒ 说明这个 val 成为了新的最小值
	利用这个负数，可以在 pop() 时把旧的最小值“还原”出来*/