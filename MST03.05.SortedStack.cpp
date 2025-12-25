// Created: 2025-12-25
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 面试题 03.05. 栈排序
栈排序。 编写程序，对栈进行排序使最小元素位于栈顶。最多只能使用一个其他的临时栈存放数据，但不得将元素复制到别的数据结构（如数组）中。
该栈支持如下操作：push、pop、peek 和 isEmpty。当栈为空时，peek 返回 -1。
示例 1：
	 输入：
	{"SortedStack", "push", "push", "peek", "pop", "peek"}
	{{}, {1}, {2}, {}, {}, {}}
	 输出：
	{null,null,null,1,null,2}
示例 2：
	 输入： 
	{"SortedStack", "pop", "pop", "push", "pop", "isEmpty"}
	{{}, {}, {}, {1}, {}, {}}
	 输出：
	{null,null,null,null,null,true}
提示：
	栈中的元素数目在{0, 5000}范围内。 */

class SortedStack1 {
public:
	SortedStack1() { }

	void push(int val) {
		while(!stack.empty() && stack.top() < val) {
			temp.push(stack.top());
			stack.pop();
		}
		stack.push(val);
		while(!temp.empty()) {
			stack.push(temp.top());
			temp.pop();
		}
	}

	void pop() {
		if(!stack.empty()) {
			stack.pop();
		}
	}

	int peek() {
		if(!stack.empty()) {
			return stack.top();
		}
		return -1;
	}

	bool isEmpty() {
		return stack.empty();
	}

private:
	stack<int> stack, temp;
}; // 设置一个辅助栈，插入时先把小于val的元素移动到temp中，然后插入元素到stack，最后将其他元素重新移动回stack

class SortedStack {
public:
	SortedStack() { }

	void push(int val) {
		while(!stack.empty() && stack.top() < val) {
			temp.push(stack.top());
			stack.pop();
		}
		while(!temp.empty() && temp.top() > val) {
			stack.push(temp.top());
			temp.pop();
		}
		stack.push(val);
	}

	void pop() {
		while(!temp.empty()) {
			stack.push(temp.top());
			temp.pop();
		}
		if(!stack.empty()) {
			stack.pop();
		}
	}

	int peek() {
		while(!temp.empty()) {
			stack.push(temp.top());
			temp.pop();
		}
		if(!stack.empty()) {
			return stack.top();
		}
		return -1;
	}

	bool isEmpty() {
		return stack.empty() && temp.empty();
	}

private:
	stack<int> stack, temp;
}; // 前一个做法有一个问题，如果连续插入接近的值，需要重复移动很多元素，因此push后不主动将其余元素移动回stack，而是保留在temp中
// 当pop或peek的时候，将temp的元素全部移动回stack中，再进行pop或peek，加快了push的平均速度

int main() { }