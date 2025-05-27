// Created: 2025-05-27
#include "MyUtils.h"

/* 740. 删除并获得点数
给你一个整数数组 nums ，你可以对它进行一些操作。
每次操作中，选择任意一个 nums[i] ，删除它并获得 nums[i] 的点数。之后，你必须删除 所有 等于 nums[i] - 1 和 nums[i] + 1 的元素。
开始你拥有 0 个点数。返回你能通过这些操作获得的最大点数。*/

class Solution1 {
public:
	int deleteAndEarn(vector<int> &nums) {
		map<int, int> count;
		for(auto &x : nums) {
			count[x]++;
		}
		iter_type begin = count.begin();
		return dfs(begin, count.end());
	}

private:
	int n;
	using iter_type = map<int, int>::iterator;
	int dfs(iter_type begin, iter_type end) {
		if(begin == end) {
			return 0;
		}
		iter_type next = std::next(begin);
		if(next == end) {
			return begin->first * begin->second;
		}
		int this_val = begin->first * begin->second, next_val = dfs(next, end);
		if(begin->first + 1 == next->first) {
			return max(this_val + dfs(std::next(next), end), next_val);
		} else {
			return this_val + next_val;
		}
	}
};

class Solution2 {
public:
	int deleteAndEarn(vector<int> &nums) {
		map<int, int> count;
		for(auto &x : nums) {
			count[x]++;
		}
		int n = count.size();
		vector<int> dp(n + 1);
		auto rb = count.rbegin(), pre = rb, it = std::next(rb);
		dp[n] = 0, dp[n - 1] = pre->first * pre->second;
		for(int i = n - 2; i >= 0; --i) {
			int val = it->first * it->second;
			if(pre->first == it->first + 1) {
				dp[i] = max(val + dp[i + 2], dp[i + 1]);
			} else {
				dp[i] = val + dp[i + 1];
			}
			pre = it++;
		}
		return dp[0];
	}
};

class Solution3 {
public:
	int deleteAndEarn(vector<int> &nums) {
		map<int, int> count;
		for(auto &x : nums) {
			count[x]++;
		}
		int n = count.size();
		int dp_2, dp_1, dp;
		auto rb = count.rbegin(), pre = rb, it = std::next(rb);
		dp_2 = 0, dp_1 = pre->first * pre->second;
		for(int i = n - 2; i >= 0; --i) {
			int val = it->first * it->second;
			if(pre->first == it->first + 1) {
				dp = max(val + dp_2, dp_1);
			} else {
				dp = val + dp_1;
			}
			dp_2 = dp_1;
			dp_1 = dp;
			pre = it++;
		}
		return dp;
	}
};

class Solution4 {
public:
	int deleteAndEarn(vector<int> &nums) {
		std::sort(nums.begin(), nums.end());
		int dp_2, dp_1, dp;
		auto get_val = [&](int begin, int &next) {
			next = begin - 1;
			while(next >= 0 && nums[begin] == nums[next]) --next;
			return (begin - next) * nums[begin];
		};
		int begin = nums.size() - 1, next, pre_index = begin;
		dp = get_val(begin, next), dp_1 = 0;
		begin = next;
		while(begin >= 0) {
			dp_2 = dp_1;
			dp_1 = dp;
			int val = get_val(begin, next);
			if(nums[begin] == nums[pre_index] - 1) {
				dp = max(val + dp_2, dp_1);
			} else {
				dp = val + dp_1;
			}
			pre_index = begin;
			begin = next;
		}
		return dp;
	}
};

class Solution {
public:
	int deleteAndEarn(vector<int> &nums) {
		std::sort(nums.begin(), nums.end());
		int n = nums.size(), currIndex = 0, preIndex, nextIndex; // 下标
		auto get_Earn = [&](int begin, int &next) {
			next = begin + 1;
			while(next < n && nums[begin] == nums[next]) ++next;
			return (next - begin) * nums[begin];
		};
		int prePreEarn, preEarn = 0; // dp 数组滚动优化
		int currEarn = get_Earn(currIndex, nextIndex);
		preIndex = currIndex;
		currIndex = nextIndex; // 初始化第 0 组
		while(currIndex < n) {
			prePreEarn = preEarn;
			preEarn = currEarn;
			int val = get_Earn(currIndex, nextIndex);
			if(nums[currIndex] == nums[preIndex] + 1) {
				currEarn = max(val + prePreEarn, preEarn);
			} else {
				currEarn = val + preEarn;
			}
			preIndex = currIndex;
			currIndex = nextIndex;
		}
		return currEarn;
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 2, 2, 3, 3, 3, 4 };
	cout << sol.deleteAndEarn(nums) << endl;
	nums = { 1 };
	cout << sol.deleteAndEarn(nums) << endl;
}