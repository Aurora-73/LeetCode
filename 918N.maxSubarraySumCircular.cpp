// Created: 2025-05-14
#include "MyUtils.hpp"

/*918. 环形子数组的最大和
给定一个长度为 n 的环形整数数组 nums ，返回 nums 的非空 子数组 的最大可能和 。
环形数组 意味着数组的末端将会与开头相连呈环状。形式上， nums[i] 的下一个元素是 nums[(i + 1) % n] ， nums[i] 的前一个元素是 nums[(i - 1 + n) % n] 。
子数组 最多只能包含固定缓冲区 nums 中的每个元素一次。形式上，对于子数组 nums[i], nums[i + 1], ..., nums[j] ，不存在 i <= k1, k2 <= j 其中 k1 % n == k2 % n 。
n == nums.length, 1 <= n <= 3 * 10 ^ 4, -3 * 104 <= nums[i] <= 3 * 10 ^4 ​​​​​​​*/

class Solution1 { //0 ms 42.7 MB
public:
	int maxSubarraySumCircular(vector<int> &nums) {
		int sum_all = 0, current_min = 0, current_max = 0;
		int best_min = numeric_limits<int>::max(),
		    best_max = numeric_limits<int>::min(); // 至少包含一个元素
		for(int &x : nums) {
			// Kadane for max
			current_max = max(current_max, 0) + x; // 注意这里要加 x ，否则该元素无法加入当前前缀和
			best_max = max(best_max, current_max);

			// Kadane for min
			current_min = min(current_min, 0) + x;
			best_min = min(best_min, current_min);

			sum_all += x;
		}

		// 全负时只能取 best_max，否则比较 “不环绕” vs “环绕”
		if(best_max < 0) {
			return best_max;
			// best_max 小于零说明全部值均为负数，这时 sum_all - best_min 会是一个元素都不包含的值，因为 best_min 包含了全部值，应该直接返回 best_max
		} else {
			return max(best_max, sum_all - best_min);
		}
	}
}; // 分为两种情况，第一种情况是在数组中间取到，另一种情况是在两边取到，在两边取到相当于先找最小子数组，然后用整个数组减去最小子数组，注意最小子数组是原数组的情况

class Solution2 { // 0 ms 44.5 MB
public:
	int maxSubarraySumCircular(vector<int> &nums) {
		int current_max = 0, best_max = numeric_limits<int>::min(), n = nums.size(), prefix_sum = 0;
		vector<int> max_prefix(n);
		for(int i = 0; i < n; ++i) {
			int &x = nums[i];
			prefix_sum += x;
			max_prefix[i] = (i == 0 ? prefix_sum : max(max_prefix[i - 1], prefix_sum));
			current_max = max(current_max, 0) + x; // 注意这里要加 x ，否则该元素无法加入当前前缀和
			best_max = max(best_max, current_max);
		}
		int sum_right = 0, max_cross = numeric_limits<int>::min();
		for(int j = n - 1; j > 0; --j) {
			sum_right += nums[j];
			max_cross = max(max_cross, sum_right + max_prefix[j - 1]);
		}
		return max(best_max, max_cross);
	}
}; // 分为两种情况，第一种情况是在数组中间取到，另一种情况是在两边取到，这时可以记为sum(nums[0:i]) + sum(num[j:n])，可以固定 j 求 [0:j] 的最大前缀和( max_prefix[j-1] )，第一次便利时直接保存即可

class Solution {
public:
	int maxSubarraySumCircular(vector<int> &nums) { }
};

int main() {
	Solution sol;
}