// Created: 2025-06-06
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* Q1. 数组元素相等转换
给你一个大小为 n 的整数数组 nums，其中只包含 1 和 -1，以及一个整数 k。
你可以最多进行 k 次以下操作：
选择一个下标 i（0 <= i < n - 1），然后将 nums[i] 和 nums[i + 1] 同时 乘以 -1。
注意：你可以在 不同 的操作中多次选择相同的下标 i。
如果在最多 k 次操作后可以使数组的所有元素相等，则返回 true；否则，返回 false。 */

class Solution1 {
public:
	bool canMakeEqual(vector<int> &nums, int k) {
		int n = nums.size();
		string state = encode(nums);
		unordered_map<string, unordered_map<int, bool>> memo;
		return dfs(state, k, n, memo);
	}

private:
	// 将数组编码为字符串
	string encode(const vector<int> &nums) {
		string s;
		for(int x : nums) s += (x == 1 ? '1' : '0');
		return s;
	}
	// 将字符串解码为数组
	vector<int> decode(const string &s) {
		vector<int> nums;
		for(char c : s) nums.push_back(c == '1' ? 1 : -1);
		return nums;
	}
	// 判断所有元素是否相等
	bool allEqual(const string &s) {
		for(char c : s)
			if(c != s[0]) return false;
		return true;
	}

	bool dfs(string &state, int k, int n, unordered_map<string, unordered_map<int, bool>> &memo) {
		if(allEqual(state)) return true;
		if(k == 0) return false;
		if(memo.count(state) && memo[state].count(k)) return memo[state][k];

		for(int i = 0; i < n - 1; ++i) {
			// 翻转 i 和 i+1
			state[i] = (state[i] == '1' ? '0' : '1');
			state[i + 1] = (state[i + 1] == '1' ? '0' : '1');
			if(dfs(state, k - 1, n, memo)) {
				// 回溯
				state[i] = (state[i] == '1' ? '0' : '1');
				state[i + 1] = (state[i + 1] == '1' ? '0' : '1');
				return memo[state][k] = true;
			}
			// 回溯
			state[i] = (state[i] == '1' ? '0' : '1');
			state[i + 1] = (state[i + 1] == '1' ? '0' : '1');
		}
		return memo[state][k] = false;
	}
};

class Solution {
public:
	bool canMakeEqual(vector<int> &nums, int k) {
		int n = nums.size();
		if(n <= 1) return true;

		int cnt_neg = 0, cnt_pos = 0;
		for(int x : nums) {
			if(x == -1)
				++cnt_neg;
			else
				++cnt_pos;
		}

		bool can_to_1 = (cnt_neg % 2 == 0);
		bool can_to_n1 = (cnt_pos % 2 == 0);
		if(!can_to_1 && !can_to_n1) return false;

		int best = INT_MAX;
		if(can_to_1) best = min(best, steps_to(nums, 1));
		if(can_to_n1) best = min(best, steps_to(nums, -1));

		return best <= k;
	}

private:
	int steps_to(const vector<int> &orig, int target) {
		int n = orig.size();
		vector<int> a = orig;
		int cnt = 0;
		for(int i = 0; i < n - 1; ++i) {
			if(a[i] != target) {

				a[i] *= -1;
				a[i + 1] *= -1;
				++cnt;
			}
		}
		for(int x : a) {
			if(x != target) return INT_MAX;
		}
		return cnt;
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	int k;
	nums = { 1, -1, 1, -1, 1 }, k = 3;
	cout << Solution().canMakeEqual(nums, k) << endl; // 输出: true
	nums = { -1, -1, -1, 1, 1, 1 }, k = 5;
	cout << Solution().canMakeEqual(nums, k) << endl; // 输出: fasle
	nums = { -1, 1, 1, 1, -1, -1, -1, 1, 1 }, k = 4;
	cout << Solution().canMakeEqual(nums, k) << endl; // 输出: fasle
	for(int i = 0; i < 100; ++i) {
		nums = randomIntVector(30, -1, 1, 0, 0);
		for(auto &n : nums) {
			if(n == 0) {
				n = 1; // 确保只有 1 和 -1
			}
		}
		cout << boolalpha
		     << (Solution().canMakeEqual(nums, 10) == Solution1().canMakeEqual(nums, 10))
		     << endl; // 输出: true 或 false，取决于随机数组q
	}
}
