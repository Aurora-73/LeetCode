// Created: 2025-06-01
#include "MyUtils.h"

/*646. 最长数对链
给你一个由 n 个数对组成的数对数组 pairs ，其中 pairs[i] = [lefti, righti] 且 lefti < righti。
现在，我们定义一种 跟随 关系，当且仅当 b < c 时，数对 p2 = [c, d] 才可以跟在 p1 = [a, b] 后面。
我们用这种形式来构造数对链 。
找出并返回能够形成的最长数对链的长度 。
你不需要用到所有的数对，你可以以任何顺序选择其中的一些数对来构造。*/

class Solution1 {
public:
	int findLongestChain(vector<vector<int>> &pairs) {
		int n = pairs.size();
		sort(pairs.begin(), pairs.end());
		vector<int> dp(n, 1);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < i; j++) {
				if(pairs[i][0] > pairs[j][1]) {
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}
		}
		return dp[n - 1];
	}
};

class Solution2 {
public:
	int findLongestChain(vector<vector<int>> &pairs) {
		sort(pairs.begin(), pairs.end());
		vector<int> arr;
		for(auto p : pairs) {
			int x = p[0], y = p[1];
			if(arr.size() == 0 || x > arr.back()) {
				arr.emplace_back(y);
			} else {
				int idx = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
				arr[idx] = min(arr[idx], y);
			}
		}
		return arr.size();
	}
};

class Solution {
public:
	int findLongestChain(vector<vector<int>> &pairs) {
		int curr = INT_MIN, res = 0;
		sort(pairs.begin(), pairs.end(), [](const vector<int> &a, const vector<int> &b) {
			return a[1] < b[1];
		});
		for(auto &p : pairs) {
			if(curr < p[0]) {
				curr = p[1];
				res++;
			}
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<vector<int>> pairs = { { 9, 10 },
		{ 9, 10 },
		{ 4, 5 },
		{ -9, -3 },
		{ -9, 1 },
		{ 0, 3 },
		{ 6, 10 },
		{ -5, -4 },
		{ -7, -6 } };
	sol.findLongestChain(pairs);
}