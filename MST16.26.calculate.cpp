// Created: 2026-01-05
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个包含正整数、加(+)、减(-)、乘(*)、除(/)的算数表达式(括号除外)，计算其结果。
表达式仅包含非负整数，+， -，*，/ 四种运算符和空格。 整数除法仅保留整数部分。
示例 1：
	输入："3+2*2"
	输出：7
示例 2：
	输入：" 3/2 "
	输出：1
示例 3：
	输入：" 3+5 / 2 "
	输出：5
说明：
	你可以假设所给定的表达式都是有效的。
	请不要使用内置的库函数 eval。 */

class Solution1 {
public:
	int calculate(string &s) {
		int n = s.size(), i = 0;
		stack<int> num;
		stack<short> op; // + 0, - 1, * 2, / 3
		array<short, 4> priority { 0, 0, 1, 1 };
		array<short, 6> c2i { 2, 0, -1, 1, -1, 3 };
		while(i < n) {
			if(isdigit(s[i])) {
				int val = s[i++] - '0';
				while(i < n && isdigit(s[i])) {
					val *= 10;
					val += s[i++] - '0';
				}
				num.push(val);
			} else if(s[i] == ' ') {
				++i;
			} else {
				int curr = c2i[s[i++] - '*'];
				while(!op.empty() && priority[curr] <= priority[op.top()]) {
					oneOperate(num, op);
				}
				op.push(curr);
			}
		}
		while(!op.empty()) {
			oneOperate(num, op);
		}
		return num.top();
	}

private:
	void oneOperate(stack<int> &num, stack<short> &op) {
		int r = num.top();
		num.pop();
		int l = num.top();
		num.pop();
		switch(op.top()) {
		case 0: num.push(l + r); break;
		case 1: num.push(l - r); break;
		case 2: num.push(l * r); break;
		case 3: num.push(l / r); break;
		default: break;
		}
		op.pop();
	}
}; // 标准的双栈实现

class Solution {
public:
	// 优化版基础计算器：消除栈操作，直接累计结果
	// 通过两个变量管理计算状态，避免额外的内存开销和遍历操作
	// 返回值：表达式计算的整数结果
	int calculate(string s) {
		// 边界条件：空字符串返回"0"
		if(s.empty()) return 0;

		// 累计最终结果的变量，存储所有加减法运算的结果
		int accumulatedResult = 0;

		// 待处理的操作数，用于立即执行乘除法运算
		int pendingOperand = 0;

		// 当前解析的数字，支持多位数构建
		int currentNumber = 0;

		// 前一个运算符，初始化为'+'简化首个数字处理逻辑
		char lastOperator = '+';

		// 优化的单次遍历算法，减少重复条件检查
		for(int i = 0; i <= s.length(); i++) {
			// 当前字符，字符串结束时使用特殊标记触发最后一次计算
			char currentChar = (i == s.length()) ? '+' : s[i];

			// 数字字符处理：构建完整的多位数
			if(isdigit(currentChar)) {
				currentNumber = currentNumber * 10 + (currentChar - '0');
				continue;
			}

			// 跳过空格字符，避免无效处理
			if(currentChar == ' ') continue;

			// 运算符处理：根据前一个运算符类型执行对应运算
			switch(lastOperator) {
			case '+':
				// 加法：将之前的待处理操作数加入结果，当前数字成为新的待处理操作数
				accumulatedResult += pendingOperand;
				pendingOperand = currentNumber;
				break;
			case '-':
				// 减法：将之前的待处理操作数加入结果，当前数字取负值成为新的待处理操作数
				accumulatedResult += pendingOperand;
				pendingOperand = -currentNumber;
				break;
			case '*':
				// 乘法：立即与待处理操作数相乘，体现运算符优先级
				pendingOperand *= currentNumber;
				break;
			case '/':
				// 除法：立即与待处理操作数相除，整数除法自动截断
				pendingOperand /= currentNumber;
				break;
			}

			// 状态更新：记录当前运算符，重置数字累加器
			lastOperator = currentChar;
			currentNumber = 0;
		}

		// 最终结果：累计结果加上最后的待处理操作数
		return accumulatedResult + pendingOperand;
	}
}; // 因为没有扩号，因此最多有一个未处理符号，不需要栈

int main() {
	Solution sol;
	string s;
	s = "3+2*2";
	cout << sol.calculate(s) << endl;

	s = " 3/2 ";
	cout << sol.calculate(s) << endl;

	s = " 3+5 / 2 ";
	cout << sol.calculate(s) << endl;
}