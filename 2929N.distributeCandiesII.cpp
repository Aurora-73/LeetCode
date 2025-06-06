// Created: 2025-06-01
#include "MyUtils.hpp"

/*2929. 给小朋友们分糖果 II
给你两个正整数 n 和 limit 。
请你将 n 颗糖果分给 3 位小朋友，确保没有任何小朋友得到超过 limit 颗糖果，请你返回满足此条件下的 总方案数 。*/

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
}; // 不需要用dfs dp

class Solution {
public:
	long long cal(int x) {
		if(x < 0) {
			return 0;
		}
		return (long)x * (x - 1) / 2;
	}

	long long distributeCandies(int n, int limit) {
		return cal(n + 2) - 3 * cal(n - limit + 1) + 3 * cal(n - (limit + 1) * 2 + 2)
		    - cal(n - 3 * (limit + 1) + 2);
	}
};

int main() {
	Solution sol;
	cout << sol.distributeCandies(5, 2);
}