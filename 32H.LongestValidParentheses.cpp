// Created: 2025-06-20
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 32. 最长有效括号
给你一个只包含 "("和 ")"的字符串，找出最长有效（格式正确且连续）括号子串的长度。
示例 1：
	输入：s = "(()"
	输出：2
	解释：最长有效括号子串是 "()"
示例 2：
	输入：s = ")()())"
	输出：4
	解释：最长有效括号子串是 "()()"
示例 3：
	输入：s = ""
	输出：0
提示：
	0 <= s.length <= 3 * 10^4
	s{i} 为 "(" 或 ")" */

class Solution1 {
public:
	int longestValidParentheses(string &s) {
		int n = s.size(), res = 0, count;
		for(int i = 0; i < n; ++i) {
			// 剪枝：如果后面剩余长度 <= 当前最大长度，直接break
			if(n - i <= res) break;
			if(s[i] == '(') {
				count = 1;
			} else {
				continue;
			}
			for(int j = i + 1; j < n; ++j) {
				count += (s[j] == '(' ? 1 : -1);
				if(count == 0) {
					res = max(res, j - i + 1);
				} else if(count < 0) {
					break;
				}
				// 剪枝：剩余字符不足以配平多余的左括号
				if(count > n - j - 1) {
					break;
				}
			}
		}
		return res;
	}
}; // 从每个左括号开始匹配
// 需要统计每个区间段的'('和')'的个数差，记录为左减右
// 若个数差为0，则说明匹配成功, 返回匹配成功的 最大起止下标差 + 1

class Solution2 {
public:
	int longestValidParentheses(string &s) {
		int n = s.size(), res = 0;
		vector<int> dp(n); // dp[i]表示以i为结尾的最长匹配长度
		for(int i = 1; i < n; ++i) {
			if(s[i] == '(') continue;
			int prev = i - dp[i - 1] - 1;
			if(prev >= 0 && s[prev] == '(') {
				dp[i] = dp[i - 1] + 2;
				if(prev - 1 >= 0) {
					dp[i] += dp[prev - 1];
				}
				res = max(dp[i], res);
			}
		}
		return res;
	}
};
/* 动态规划算法，如果当前元素是(，则肯定不匹配
   否则找到左侧最靠右的不匹配的元素，若该元素存在且为(，则将匹配长度 + 2
   如果扩展之后，左侧还有匹配成功的，则将他们串联起来  */

class Solution3 {
public:
	int longestValidParentheses(string &s) {
		stack<int> st;
		int n = s.size(), len = 0, max_len = 0;
		vector<bool> mask(n);
		for(int i = 0; i < n; ++i) {
			if(s[i] == '(') {
				st.push(i);
			} else {
				if(!st.empty()) {
					mask[i] = mask[st.top()] = 1;
					st.pop();
				}
			}
		}
		for(bool b : mask) {
			if(b) {
				++len;
			} else {
				max_len = max(max_len, len);
				len = 0;
			}
		}
		return max(max_len, len); // 防止漏掉最后一个，或者可以将数组长度设为 n + 1
	}
}; // 用栈进行括号匹配，匹配成功则将对应的mask标记为1，最后寻找最长连续的mask

class Solution4 {
public:
	int longestValidParentheses(string &s) {
		stack<int> st;
		st.push(-1); // （哨兵）在栈底先放一个“-1”
		int n = s.size(), len = 0, max_len = 0;
		for(int i = 0; i < n; ++i) {
			if(s[i] == '(') {
				// 遇到左括号，就把它的下标入栈
				st.push(i);
			} else {
				// 遇到右括号，先弹出栈顶对应的“匹配位置”
				st.pop();
				if(st.empty()) {
					// 如果栈空，说明当前右括号 i 没法匹配
					// 把 i 当作“新的参考起点”，压入栈底
					st.push(i);
				} else {
					// 栈不空，说明 i 能和栈顶对应位置“成对”
					// 有效长度 = 当前下标 i 减去 栈顶下标
					len = i - st.top();
					max_len = max(max_len, len);
				}
			}
		}
		return max_len;
	}
}; // 栈 + 哨兵
/* 1. 核心思路
用一个栈 st 来存储“可能匹配的下标”，包括
左括号 '(' 的下标；
    一个哨兵 -1 或者“最近一次未匹配右括号”的下标，作为长度计算的基准。
每遇到一个右括号 ')'：
    先尝试 pop() 栈顶（把它当作与之匹配的 “(” 或上一次未匹配 ')'`）。
    如果 pop 后栈空，说明这 次 ')' 没有配对，就把它的下标 i 作为新的起始基准入栈。
    如果 pop 后栈非空，则说明当前的 ')' 找到了一 对有效的括号，长度 = 当前下标 i - “栈顶下标”（栈顶此时是「这个有效区间的前一个位置」）。
    这样，任何时候栈顶都保持着“当前未匹配右括号的最后一个下标”或“最靠近有效子串左边界的下标”，计算长度时直接用 i - st.top() 即可取到从下标 st.top()+1 到 i 的最长连续有效区间。
2. 为什么要先 push(-1)？
        -1 作为哨兵（sentinel），保证即便一开始遇到一对 ()，也能正确算出长度。
    例如遇到第一个合法对 s = "()"，
    i=0 时遇 '(' → 栈 [-1, 0]；
    i=1 时遇 ')' → pop() 弹出 0 → 栈变 [-1] → 计算 len = 1 - (-1) = 2。
    若一开始不放 -1，第一次匹配后栈空，就没法做 i - st.top() 了。*/

class Solution {
public:
	int longestValidParentheses(string &s) {
		int max_len = 0, left = 0, right = 0, n = s.size();
		for(int i = 0; i < n; ++i) {
			left += (s[i] == '(');
			right += (s[i] == ')');
			if(left == right) {
				max_len = max(max_len, 2 * left);
			} else if(right > left) {
				left = right = 0;
			}
		}
		left = right = 0;
		for(int i = n - 1; i >= 0; --i) {
			left += (s[i] == '(');
			right += (s[i] == ')');
			if(left == right) {
				max_len = max(max_len, 2 * left);
			} else if(right < left) {
				left = right = 0;
			}
		}
		return max_len;
	}
};
/* 从左往右和从右往左各遍历一遍，
1、如果当前左右括号数相等，则更新最大值
2、如果当前已经不可能匹配成功，重置计数 
3、从左往右扫描会漏掉像 "(()" 这种，( 比 ) 多，right > left 从不成立，却因为最后 ( 无法匹配，left == right 也永远不会成立，得不到正确长度 2。
4、不能简单地在最后取 min(left, right) * 2 再更新一次 max_len，因为在扫描过程中可能出现“断开的段”——有多余的左括号或者右括号打断了有效区间*/

int main() {
	Solution sol;
	string s;
	s = "(()";
	cout << sol.longestValidParentheses(s) << endl; // 2
	s = ")()())";
	cout << sol.longestValidParentheses(s) << endl; // 4
	s = ")(";
	cout << sol.longestValidParentheses(s) << endl; // 0
}