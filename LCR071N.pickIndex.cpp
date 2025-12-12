// Created: 2025-12-11
#include "MyUtils.hpp"
#include <algorithm>
// #ifdef MY_UTILS_H

/* LCR 071. 按权重随机选择
给定一个正整数数组 w，其中 w{i} 代表下标 i 的权重（下标从 0 开始），
请写一个函数 pickIndex，它可以随机地获取下标 i，选取下标 i 的概率与 w{i} 成正比。
例如，对于 w = {1, 3}，挑选下标 0 的概率为 1 / (1 + 3) = 0.25 （即，
25%），而选取下标 1 的概率为 3 / (1 + 3) = 0.75（即，75%）。
也就是说，选取下标 i 的概率为 w{i} / sum(w)。
示例 1：
	输入：
	inputs = {"Solution","pickIndex"}
	inputs = {{{1}},{}}
	输出：
	{null,0}
	解释：
	Solution solution = new Solution({1});
	solution.pickIndex(); // 返回 0，因为数组中只有一个元素，所以唯一的选择是返回下标 0。
示例 2：
	输入：
	inputs = {"Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"}
	inputs = {{{1,3}},{},{},{},{},{}}
	输出：
	{null,1,1,1,1,0}
	解释：
	Solution solution = new Solution({1, 3});
	solution.pickIndex(); // 返回 1，返回下标 1，返回该下标概率为 3/4。
	solution.pickIndex(); // 返回 1
	solution.pickIndex(); // 返回 1
	solution.pickIndex(); // 返回 1
	solution.pickIndex(); // 返回 0，返回下标 0，返回该下标概率为 1/4。
	由于这是一个随机问题，允许多个答案，因此下列输出都可以被认为是正确的:
	{null,1,1,1,1,0}
	{null,1,1,1,1,1}
	{null,1,1,1,0,0}
	{null,1,1,1,0,1}
	{null,1,0,1,0,0}
	......
	诸若此类。
提示：
	1 <= w.length <= 10000
	1 <= w{i} <= 10^5
	pickIndex 将被调用不超过 10000 次 */

class Solution1 {
public:
	Solution1(const vector<int> &w) : mt(random_device {}()) {
		prefix.reserve(w.size() + 1);
		for(auto val : w) {
			sum += val;
			prefix.push_back(sum);
		}
		uf = uniform_int_distribution<int>(1, sum);
	}

	int pickIndex() {
		int val = uf(mt), l = 0, r = prefix.size();
		// 寻找第一个大于等于val的值的下标
		while(l < r) {
			int mid = l + (r - l) / 2;
			if(prefix[mid] >= val) {
				r = mid;
			} else {
				l = mid + 1;
			}
		}
		return l;
	}

private:
	int sum = 0;
	vector<int> prefix;
	mt19937 mt;
	uniform_int_distribution<int> uf;
};
/*
1、C++生成随机数的方式包含三个部分：
    random_deviced是一个生成真随机数的生成器类，重载了函数调用运算符，调用后生成一个真随机数，类型是无符号整型。（比较慢）
    mt19937 是一个伪随机数引擎，构造时传入的无符号整数用于初始化状态，从而决定未来伪随机序列的全部取值。
    uniform_int_distribution<>是一个数值转换器，将取到的随机数按照符合要求的概率分布进行映射，构造函数的参数是最大最小值，调用的参数是一个为随机数引擎。
2、前缀和解法，将全部元素之和sum视为一个区间，将每个元素分配一定的长度，随机取一个[0, sum]的数，寻找其所在的下标，实际上就是在一个递增数组寻找不大于这个数的下标
*/

class Solution {
private:
	mt19937 gen;
	uniform_int_distribution<int> dis;
	vector<int> pre;

public:
	Solution(const vector<int> &w) :
	    gen(random_device {}()), dis(1, accumulate(w.begin(), w.end(), 0)) {
		partial_sum(w.begin(), w.end(), back_inserter(pre));
	}

	int pickIndex() {
		int x = dis(gen);
		return lower_bound(pre.begin(), pre.end(), x) - pre.begin();
	}
};

int main() {
	Solution sol({ 3, 4, 1, 2 });
	for(int i = 0; i < 10; ++i) {
		cout << sol.pickIndex() << endl;
	}
}