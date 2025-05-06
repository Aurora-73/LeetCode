#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int> &nums, int target) {
		unordered_map<int, int> map; // save needed_val to index
		for(int i = 0; i < nums.size(); i++) {
			auto need = map.find(target - nums[i]);
			if(need != map.end()) {
				return {need->second, i};
			} else {
				map[nums[i]] = i;
			}
		}
		return {};
	}
};
