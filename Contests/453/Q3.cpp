// Created: 2025-06-06
#include "MyDateGen.h"
#include "MyUtils.hpp"

/* Q3. 统计极差最大为 K 的分割方式数
给你一个整数数组 nums 和一个整数 k。你的任务是将 nums 分割成一个或多个 非空 的连续子段，
使得每个子段的 最大值 与 最小值 之间的差值 不超过 k。
返回在此条件下将 nums 分割的总方法数。
由于答案可能非常大，返回结果需要对 109 + 7 取余数。
示例 1：
	输入： nums = {9,4,1,3,7}, k = 4
	输出： 6
	解释：
	共有 6 种有效的分割方式，使得每个子段中的最大值与最小值之差不超过 k = 4：
	{{9}, {4}, {1}, {3}, {7}}
	{{9}, {4}, {1}, {3, 7}}
	{{9}, {4}, {1, 3}, {7}}
	{{9}, {4, 1}, {3}, {7}}
	{{9}, {4, 1}, {3, 7}}
	{{9}, {4, 1, 3}, {7}}
示例 2：
	输入： nums = {3,3,4}, k = 0
	输出： 2
	解释：
	共有 2 种有效的分割方式，满足给定条件：
	{{3}, {3}, {4}}
	{{3, 3}, {4}}
提示：
	2 <= nums.length <= 5 * 104
	1 <= nums{i} <= 109
	0 <= k <= 109 */

class Solution {
public:
	int countPartitions(vector<int> &nums, int k) {
		const int MOD = 1e9 + 7;
		int n = nums.size();
		vector<long long> ways(n + 1, 0), prefixSum(n + 1, 0);
		ways[0] = 1;
		prefixSum[0] = 1;

		deque<int> maxQueue, minQueue;
		int left = 0;

		for(int i = 1; i <= n; ++i) {
			int currentVal = nums[i - 1];

			while(!maxQueue.empty() && nums[maxQueue.back()] <= currentVal) maxQueue.pop_back();
			while(!minQueue.empty() && nums[minQueue.back()] >= currentVal) minQueue.pop_back();
			maxQueue.push_back(i - 1);
			minQueue.push_back(i - 1);

			while(nums[maxQueue.front()] - nums[minQueue.front()] > k) {
				++left;
				if(maxQueue.front() < left) maxQueue.pop_front();
				if(minQueue.front() < left) minQueue.pop_front();
			}

			ways[i] = (prefixSum[i - 1] - (left > 0 ? prefixSum[left - 1] : 0) + MOD) % MOD;
			prefixSum[i] = (prefixSum[i - 1] + ways[i]) % MOD;
		}

		return ways[n];
	}
};

int main() {
	Solution sol;
	vector<int> nums = randomIntVector(10, 1, 100, false, true);
	int k;
	nums = { 9, 4, 1, 3, 7 }, k = 4;
	cout << sol.countPartitions(nums, k) << endl; // 输出: 6
	nums = { 3, 3, 4 }, k = 0;
	cout << sol.countPartitions(nums, k) << endl; // 输出: 2
}