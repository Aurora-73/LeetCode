// Created: 2025-06-01
#include "MyUtils.hpp"

/*2928. 给小朋友们分糖果 I
给你两个正整数 n 和 limit 。
请你将 n 颗糖果分给 3 位小朋友，确保没有任何小朋友得到超过 limit 颗糖果，请你返回满足此条件下的 总方案数 。*/

class Solution1 {
public:
	long long distributeCandies(int n, int limit) {
		this->limit = limit;
		dfs(0, n);
		return count;
	}

private:
	long long count = 0;
	int limit;
	void dfs(int index, int n) {
		int min_val = max(n - (2 - index) * limit, 0);
		if(min_val > limit) {
			return;
		}
		if(index == 3) {
			count += (n == 0);
			return;
		}
		int max_val = min(limit, n);
		for(int i = min_val; i <= max_val; ++i) {
			dfs(index + 1, n - i);
		}
	}
}; // dfs 很慢，没有必要，应该用于任意个数小朋友的情况

class Solution {
public:
	long long distributeCandies(int n, int limit) {
		int first_max = min(n, limit), first_min = max(n - limit * 2, 0);
		long long res = 0;
		for(int i = first_min; i <= first_max; ++i) {
			int second_max = min(n - i, limit), second_min = max(n - i - limit, 0);
			res += max(second_max - second_min + 1, 0);
		}
		return res;
	}
};

int main() {
	Solution sol;
}