#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

/*给你一个整数数组 nums 和一个整数 k ，判断数组中是否存在两个 不同的索引 i 和 j ，
满足 nums[i] == nums[j] 且 abs(i - j) <= k 。如果存在，返回 true ；否则，返回 false 。
示例 1：
输入：nums = [1,2,3,1], k = 3
输出：true
示例 2：
输入：nums = [1,0,1,1], k = 1
输出：true
示例 3：
输入：nums = [1,2,3,1,2,3], k = 2
输出：false*/

class Solution {
public:
	bool containsNearbyDuplicate(vector<int> &nums, int k) {
		unordered_map<int, int> map;
		for(int i = 0; i < nums.size(); i++) {
			if(map.contains(nums[i])) {
				if(i - map[nums[i]] <= k) {
					return true;
				}
			}
			map[nums[i]] = i;
		}
		return false;
	}
};

int main() {
	Solution sol;
	vector<int> nums = {1, 2, 3, 1, 2, 3};
	int k = 3;
	cout << sol.containsNearbyDuplicate(nums, k);
	return 0;
}