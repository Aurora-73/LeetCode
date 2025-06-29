// Created: 2025-06-28
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 152. 验证二叉搜索树的后序遍历序列
请实现一个函数来判断整数数组 postorder 是否为二叉搜索树的后序遍历结果。
示例 1：
	输入: postorder = {4,9,6,5,8}
	输出: false 
	解释：从上图可以看出这不是一颗二叉搜索树
示例 2：
	输入: postorder = {4,6,5,9,8}
	输出: true 
	解释：可构建的二叉搜索树如上图
提示：
	数组长度 <= 1000
	postorder 中无重复数字 */

class Solution {
public:
	bool verifyTreeOrder(vector<int> &postorder) {
		return verify(postorder, 0, postorder.size() - 1);
	}

private:
	bool verify(vector<int> &postorder, int i, int j) {
		if(i >= j) return true;
		int d = j - 1;
		while(d >= i && postorder[d] > postorder[j]) --d;
		for(int k = i; k < d; ++k) {
			if(postorder[k] > postorder[j]) {
				return false;
			}
		}
		if(!verify(postorder, i, d)) {
			return false;
		}
		if(!verify(postorder, d + 1, j - 1)) {
			return false;
		}
		return true;
	}
};

int main() {
	Solution sol;
	vector<int> postorder;
	postorder = { 4, 9, 6, 5, 8 };
	cout << sol.verifyTreeOrder(postorder) << endl; // false
	postorder = { 4, 6, 5, 9, 8 };
	cout << sol.verifyTreeOrder(postorder) << endl; // true
}