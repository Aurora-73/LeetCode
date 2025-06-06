// Created: 2025-04-25
#include "MyUtils.hpp"

/*150. 逆波兰表达式求值
中等
相关标签
相关企业
给你一个字符串数组 tokens ，表示一个根据 逆波兰表示法 表示的算术表达式。
请你计算该表达式。返回一个表示表达式值的整数。
注意：
有效的算符为 '+'、'-'、'*' 和 '/' 。
每个操作数（运算对象）都可以是一个整数或者另一个表达式。
两个整数之间的除法总是 向零截断 。
表达式中不含除零运算。
输入是一个根据逆波兰表示法表示的算术表达式。
答案及所有中间计算结果可以用 32 位 整数表示。*/

class Solution {
	const unordered_map<string, int> operators {
		make_pair("+", 0), make_pair("-", 1), make_pair("*", 2), make_pair("/", 3)
	};

public:
	int evalRPN(vector<string> &tokens) {
		stack<int> vals;
		for(auto &token : tokens) { // 引用
			auto find = operators.find(token);
			if(find != operators.end()) {
				int right = vals.top();
				vals.pop();
				int left = vals.top();
				vals.pop();
				switch(find->second) {
				case 0: vals.push(left + right); break;
				case 1: vals.push(left - right); break;
				case 2: vals.push(left * right); break;
				case 3: vals.push(left / right); break;
				}
			} else {
				vals.push(std::stoi(token)); // string 转 int的函数
			}
		}
		return vals.top();
	}
};

class Solution1 {
	inline bool isOperator(const string &s) {
		return s == "+" || s == "-" || s == "*" || s == "/";
	}

public:
	int evalRPN(vector<string> &tokens) {
		stack<int> vals;
		for(auto &token : tokens) { // 引用
			if(isOperator(token)) { // 自动内联，比哈希表快
				int right = vals.top();
				vals.pop();
				int left = vals.top();
				vals.pop();
				switch(token[0]) { // 不直接用token去选择，switch只能用于整数或枚举类型
				case '+': vals.push(left + right); break;
				case '-': vals.push(left - right); break;
				case '*': vals.push(left * right); break;
				case '/': vals.push(left / right); break;
				}
			} else {
				vals.push(std::stoi(token));
			}
		}
		return vals.top();
	}
};

// string 转为 数字: stoi stol stoll stoul stof stod stold
// 处理不以数字开头的字符串或空字符串会抛出异常 std::invalid_argument？
// 处理合法数字开头包含非法字符（包括空格）的字符串时只会转换非法字符之前的内容
// 自动删除前后空格，但是遇到中间的空格会停止转换
// 可以自动处理负号、科学计数法
// 非十进制可以用std::stoi("010", nullptr, 8); std::stoi("0x10", nullptr, 16); 非该进制的字符也是非法字符
// 第二个参数是指向 std::size_t 的指针，调用时可以用来接收转换过程中第一个未被转换的字符的位置（即，非数字部分）。如果你不需要这个信息，通常可以传入 nullptr。

int main() {
	Solution sol;
}
