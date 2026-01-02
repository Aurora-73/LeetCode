#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
	int minSubArrayLen(int target, vector<int> &nums) {
		int i = 0, j = 0, sum = nums[0], len = numeric_limits<int>::max(); // len最初不为 0
		while(j < nums.size()) { // j < nums.size() - 1会缺少 i 的移动
			if(target <= sum) {
				len = min(len, j - i + 1);
			}
			if(sum < target) {
				j++;
				if(j < nums.size()) sum += nums[j];
			} else {
				sum -= nums[i];
				i++;
			}
		}
		return len == numeric_limits<int>::max() ? 0 : len;
	}
};