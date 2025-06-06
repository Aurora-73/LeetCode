#include "MyUtils.hpp"

class Solution {
public:
	vector<int> twoSum(vector<int> &nums, int target) {
		unordered_map<int, int> map; // save needed_val to index
		for(int i = 0; i < nums.size(); i++) {
			auto need = map.find(target - nums[i]);
			if(need != map.end()) {
				return { need->second, i };
			} else {
				map[nums[i]] = i;
			}
		}
		return {};
	}
};

int main() {
	Solution solution;
	vector<int> nums = { 2, 7, 11, 15 };
	int target = 9;
	auto result = solution.twoSum(nums, target);
	cout << result << endl;
	return 0;
}
