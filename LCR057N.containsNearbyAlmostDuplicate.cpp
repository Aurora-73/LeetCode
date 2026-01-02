// Created: 2025-12-09
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给你一个整数数组 nums 和两个整数k 和 t。
请你判断是否存在 两个不同下标 i 和 j，使得abs(nums{i} - nums{j}) <= t，
同时又满足 abs(i - j) <= k。
如果存在则返回 true，不存在返回 false。
示例1：
输入：nums = {1,2,3,1}, k = 3, t = 0
输出：true
示例 2：
	输入：nums = {1,0,1,1}, k = 1, t = 2
	输出：true
示例 3：
	输入：nums = {1,5,9,1,5,9}, k = 2, t = 3
	输出：false
提示：
	0 <= nums.length <= 2 * 10^4
	-2^31 <= nums{i} <= 231 - 1
	0 <= k <= 10^4
	0 <= t <= 231 - 1 */

class Solution1 {
public:
	bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
		set<int> st;
		for(int i = 0; i < nums.size(); ++i) {
			// int lowerLimit = max(long(nums[i]) - t, long(numeric_limits<int>::min())); // 下界不能小于numeric_limits<int>::min()
			int lowerLimit = max(nums[i], numeric_limits<int>::min() + t)
			    - t; // 下界不能小于numeric_limits<int>::min()
			auto it = st.lower_bound(lowerLimit);
			if(it != st.end() && long(*it) - nums[i] <= t) {
				return true;
			}
			st.insert(nums[i]);
			if(i >= k) {
				st.erase(nums[i - k]);
			}
		}
		return false;
	}
}; // 滑动窗口 + set + lower_bound，不需要考虑同一个窗口中存在两个元素会不会多删除一次，因为这时一定为true
// 不需要用两次 lower_bound，因为一旦找到it后，第一个大于it的值就是最可能满足条件的值，若它也不满足条件，则不存在满足条件的

class Solution {
public:
	bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
		unordered_map<int, int> bucket;
		int n = nums.size();
		for(int i = 0; i < n; ++i) {
			int id = getID(nums[i], t);
			if(!bucket.insert({ id, nums[i] }).second) {
				return true;
			} // 该桶已经存在，则说明存在满足条件的值
			auto it = bucket.find(id - 1);
			if(it != bucket.end() && long(nums[i]) - it->second <= t) {
				return true;
			}
			it = bucket.find(id + 1);
			if(it != bucket.end() && long(it->second) - nums[i] <= t) {
				return true;
			}
			if(i >= k) {
				id = getID(nums[i - k], t);
				bucket.erase(id);
			}
		}
		return false;
	}

private:
	int getID(long x, long t) {
		if(x >= 0) return x / (t + 1);
		// 负数处理：保证例如 -1 在 w=5 时落入 -1，而不是 0
		return (x + 1) / (t + 1) - 1;
	} // 参数需要设置为 long 类型，否则 + 1 可能溢出
};

int main() {
	Solution sol;
	vector<int> nums;
	int k;
	int t;
	nums = { 1, 2, 3, 1 }, k = 3, t = 0;
	cout << sol.containsNearbyAlmostDuplicate(nums, k, t) << endl;
}