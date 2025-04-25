// Created: 2025-04-25
#include "MyUtils.h"

/*  224. 基本计算器
给你一个字符串表达式 s ，请你实现一个基本计算器来计算并返回它的值。
示例 1：
输入：s = "1 + 1"
输出：2
示例 2：
输入：s = " 2-1 + 2 "
输出：3
示例 3：
输入：s = "(1+(4+5+2)-3)+(6+8)"
输出：23
提示：
1 <= s.length <= 3 * 105
s 由数字、'+'、'-'、'('、')'、和 ' ' 组成
s 表示一个有效的表达式
'+' 不能用作一元运算(例如， "+1" 和 "+(2 + 3)" 无效)
'-' 可以用作一元运算(即 "-1" 和 "-(2 + 3)" 是有效的)
输入中不存在两个连续的操作符
每个数字和运行的计算将适合于一个有符号的 32位 整数*/

class Solution {
	bool isOperator(char c) {
		return c == '+' || c == '-' || c == '(' || c == ')';
	}

public:
	int calculate(string s) {
		stack<char> operators;
		stack<int> numbers;
		for(auto c : s) {
			if(c == ' ')
				continue;
			if(isOperator(c)) {
				switch(c) {
				case '+':
					break;
				case '-':
					break;
				case '(':
					break;
				case ')':
					break;
				}
			} else {
				numbers.push(c);
			}
		}
	}
};

int main() {
	Solution sol;
}