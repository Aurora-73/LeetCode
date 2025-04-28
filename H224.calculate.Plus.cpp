#include "MyUtils.h"

using namespace std;

class Solution {
public:
	double calculate(const string &s) {
		return EvaluateExpression(preprocess(s));
	}

private:
	int precedence(char op) {
		if(op == '+' || op == '-')
			return 1;
		if(op == '*' || op == '/')
			return 2;
		return 0;
	}

	double apply(double a, double b, char op) {
		switch(op) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			if(fabs(b) < numeric_limits<double>::epsilon())
				throw runtime_error("除零错误");
			return a / b;
		default:
			throw runtime_error(string("未知运算符: ") + op);
		}
	}

	void compute(stack<double> &nums, stack<char> &ops) {
		if(nums.size() < 2 || ops.empty())
			throw runtime_error("表达式不合法：操作数数量不匹配");
		double b = nums.top();
		nums.pop();
		double a = nums.top();
		nums.pop();
		char op = ops.top();
		ops.pop();
		nums.push(apply(a, b, op));
	}

	double EvaluateExpression(const string &expr) {
		stack<double> nums;
		stack<char> ops;
		int n = expr.length();

		for(int i = 0; i < n;) {
			if(isspace(expr[i])) {
				++i;
				continue;
			}

			if(isdigit(expr[i]) || expr[i] == '.') {
				double num = 0;
				double frac = 0.1;
				bool has_dot = false;
				while(i < n && (isdigit(expr[i]) || expr[i] == '.')) {
					if(expr[i] == '.') {
						if(has_dot)
							throw runtime_error("非法数字格式");
						has_dot = true;
					} else if(!has_dot) {
						num = num * 10 + (expr[i] - '0');
					} else {
						num += (expr[i] - '0') * frac;
						frac *= 0.1;
					}
					++i;
				}
				nums.push(num);
			} else if(expr[i] == '(') {
				ops.push(expr[i++]);
			} else if(expr[i] == ')') {
				while(!ops.empty() && ops.top() != '(')
					compute(nums, ops);
				if(ops.empty())
					throw runtime_error("括号不匹配");
				ops.pop(); // 弹出 '('
				++i;
			} else { // 运算符
				while(!ops.empty() && precedence(ops.top()) >= precedence(expr[i]))
					compute(nums, ops);
				ops.push(expr[i++]);
			}
		}

		while(!ops.empty())
			compute(nums, ops);
		if(nums.size() != 1)
			throw runtime_error("表达式不合法：多余的操作数");
		return nums.top();
	}

	string preprocess(const string &s) {
		string res;
		for(int i = 0; i < s.size(); ++i) {
			if(s[i] == '+' || s[i] == '-') {
				int j = i - 1;
				while(j >= 0 && isspace(s[j]))
					--j;
				if(j < 0 || s[j] == '(')
					res += '0';
			}
			res += s[i];
		}
		return res;
	}
};

int main() {
	Solution sol;
	string s;
	getline(cin, s); // 支持带空格的输入
	try {
		cout << sol.calculate(s) << endl;
	} catch(const exception &e) {
		cerr << "错误: " << e.what() << endl;
	}
	return 0;
}

/*1+((2-3) + 5 )* 6
-1+(-2)*(-3)+(-4)
1+((2-3) * 5 )* (-6)
-1+(-2 / -3)*(-3)+(-4)
-1+((-2) / (-3))*(-3)+(-4)*/