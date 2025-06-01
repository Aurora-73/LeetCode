// Created: 2025-06-01
#include "MyUtils.h"

/*354. 俄罗斯套娃信封问题
给你一个二维整数数组 envelopes ，其中 envelopes[i] = [wi, hi] ，表示第 i 个信封的宽度和高度。
当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。
请计算 最多能有多少个 信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。
注意：不允许旋转信封。*/

class Solution1 {
public:
	int maxEnvelopes(vector<vector<int>> &envelopes) {
		sort(envelopes.begin(), envelopes.end(), [](const vector<int> &a, const vector<int> &b) {
			return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]); // 第二位逆序防止出现宽相等的假套娃
		});
		vector<int> minTails;
		int n = envelopes.size();
		for(int i = 0; i < n; ++i) {
			int &now = envelopes[i][1];
			auto it = lower_bound(minTails.begin(), minTails.end(), now);
			// lower_bound 严格递增，upper_bound 不严格递增
			if(it == minTails.end()) {
				minTails.push_back(now);
			} else {
				*it = now;
			}
		}
		return minTails.size();
	}
};

class Solution {
public:
	int maxEnvelopes(vector<vector<int>> &envelopes) {
		sort(envelopes.begin(), envelopes.end(), [](const vector<int> &a, const vector<int> &b) {
			return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]); // 第二位逆序防止出现宽相等的假套娃
		});
		vector<int> minTails { envelopes[0][1] };
		int n = envelopes.size();
		minTails.reserve(n);
		for(int i = 1; i < n; ++i) {
			int &now = envelopes[i][1];
			if(now > minTails.back()) {
				minTails.push_back(now);
			} else {
				*lower_bound(minTails.begin(), minTails.end(), now) = now;
			}
		}
		return minTails.size();
	}
};
// 对宽进行排序，然后在高上（用分层DAG）求最长递增子串

int main() {
	Solution sol;
}