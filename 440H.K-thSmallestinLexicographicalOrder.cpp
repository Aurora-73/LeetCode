// Created: 2025-06-09
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 440. 字典序的第K小数字
给定整数n和k，返回{1, n}中字典序第k小的数字。
示例 1:
    输入: n = 13, k = 2
    输出: 10
    解释: 字典序的排列是 {1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9}，
    所以第二小的数字是 10。
示例 2:
输入: n = 1, k = 1
输出: 1
提示:
	1 <= k <= n <= 10 ^ 9 */

class Solution1 {
public:
	int findKthNumber(int n, int k) {
		int now = 1;
		for(int i = 1; i < k; ++i) {
			if(static_cast<long long>(now) * 10 <= n) {
				now *= 10;
			} else if(now + 1 <= n && now % 10 != 9) {
				now += 1;
			} else {
				while(now + 1 > n || now % 10 == 9) {
					now /= 10;
				}
				++now;
			}
		}
		return now;
	}
};

class Solution {
public:
	int findKthNumber(int n, int k) {
		int node = 1;
		k--; // 访问节点 node
		while(k > 0) {
			int size = subTreeCount(node, n);
			if(size <= k) { // 向右，跳过 node 子树
				node++;     // 访问 node 右侧兄弟节点
				k -= size;  // 访问子树中的每个节点，以及新的 node 节点
			} else {        // 向下，深入 node 子树
				node *= 10; // 访问 node 的第一个儿子
				k--;        // 访问新的 node 节点
			}
		}
		return node;
	}

private:
	int subTreeCount(int node, int n) {
		// 子树大小不会超过 n，所以 size 用 int 类型
		// 但计算过程中的 left 和 right 会超过 int，所以用 long long 类型
		int size = 0;
		long long left = node, right = node + 1;
		while(left <= n) {
			// 这一层的最小值是 left，最大值是 min(right, n + 1) - 1
			size += min(right, n + 1LL) - left;
			left *= 10; // 继续，计算下一层
			right *= 10;
		}
		return size;
	}
};

int main() {
	Solution sol;
	int n, k;
	n = 130, k = 67;
	cout << sol.findKthNumber(n, k) << endl;
	n = 1, k = 1;
	cout << sol.findKthNumber(n, k) << endl;
}