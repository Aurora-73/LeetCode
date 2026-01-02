// Created: 2025-12-30
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 假设你正在读取一串整数。
每隔一段时间，你希望能找出数字 x 的秩(小于或等于 x 的值的个数)。请实现数据结构和算法来支持这些操作，也就是说：
实现 track(int x)方法，每读入一个数字都会调用该方法；
实现 getRankOfNumber(int x) 方法，返回小于或等于 x 的值的个数。
注意：本题相对原题稍作改动
	示例：
	输入：
	{"StreamRank", "getRankOfNumber", "track", "getRankOfNumber"}
	{{}, {1}, {0}, {0}}
	输出：
	{null,0,null,1}
提示：
	x <= 50000
	track和getRankOfNumber 方法的调用次数均不超过 2000 次 */

class StreamRank1 {
public:
	StreamRank1() { }

	void track(int x) {
		se.insert(x);
	}

	int getRankOfNumber(int x) {
		if(se.empty()) return 0;
		auto at = se.upper_bound(x); // 注意是小于等于
		int res = 0;
		for(auto it = se.begin(); it != at; ++it) {
			++res;
		}
		return res;
	}

private:
	multiset<int> se;
};

class StreamRank2 {
public:
	StreamRank2() { }

	void track(int x) {
		se.insert(x);
	}

	int getRankOfNumber(int x) {
		if(se.empty()) return 0;
		// 不如直接模拟
		int res = 0;
		for(auto at = se.begin(); at != se.end() && *at <= x; ++at, ++res);
		return res;
	}

private:
	multiset<int> se;
};

class StreamRank {
private:
	static const int MAXX = 50001;
	vector<int> bit;

	int lowbit(int x) {
		return x & (-x);
	}

	void add(int idx, int val) {
		while(idx <= MAXX) {
			bit[idx] += val;
			idx += lowbit(idx);
		}
	}

	int sum(int idx) {
		int res = 0;
		while(idx > 0) {
			res += bit[idx];
			idx -= lowbit(idx);
		}
		return res;
	}

public:
	StreamRank() : bit(MAXX + 1, 0) { }

	void track(int x) {
		add(x + 1, 1); // +1 防止 x = 0
	}

	int getRankOfNumber(int x) {
		return sum(x + 1);
	}
}; // 树状数组

int main() { }