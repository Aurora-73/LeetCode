// Created: 2025-12-27
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 无重复字符串的排列组合。
编写一种方法，计算某字符串的所有排列组合，字符串每个字符均不相同。
示例 1：
    输入：str = "qwe"
    输出：{"qwe", "qew", "wqe", "weq", "ewq", "eqw"}
示例 2：
    输入：str = "ab"
    输出：{"ab", "ba"}
提示：
	字符都是英文字母。
	字符串长度在{1, 9}之间。 */

class Solution1 {
public:
	vector<string> permutation(string &str) {
		n = str.size();
		curr = string(n, '-');
		res.clear();
		res.reserve(factorial());
		visited = vector<bool>(n, 0);
		dfs(0, str);
		return res;
	}

private:
	int n;
	string curr;
	vector<string> res;
	vector<bool> visited;
	void dfs(int cnt, string &str) {
		if(cnt == n) {
			res.push_back(curr);
			return;
		}
		for(int i = 0; i < n; ++i) {
			if(!visited[i]) {
				visited[i] = 1;
				curr[cnt] = str[i];
				dfs(cnt + 1, str);
				visited[i] = 0;
			}
		}
	}
	size_t factorial() {
		size_t res = 1;
		for(int i = 2; i <= n; ++i) res *= i;
		return res;
	}
};

class Solution {
public:
	vector<string> permutation(string &str) {
		ranges::sort(str);
		vector<string> res;
		res.push_back(str);
		while(nextPermutation(str)) {
			res.push_back(str);
		}
		return res;
	}

private:
	bool nextPermutation(string &nums) {
		int n = nums.size(), i;
		for(i = n - 2; i >= 0; --i) {
			if(nums[i] < nums[i + 1]) { // 在 removed 中找一个 严格大于 currVal 的最小元素
				std::reverse(nums.begin() + i + 1, nums.end());
				auto it = upper_bound(nums.begin() + i + 1, nums.end(), nums[i]);
				std::swap(nums[i], *it);
				return true;
			}
		}
		return false;
	}
}; // 首先使用排序获得第一个，然后不断调用 nextPermutation 函数，这里的函数和 31N.NextPermutation 一样

int main() {
	Solution sol;
	string str;
	str = "qwe";
	cout << sol.permutation(str) << endl;

	str = "ab";
	cout << sol.permutation(str) << endl;
}