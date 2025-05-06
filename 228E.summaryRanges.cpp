#include <iostream>
#include <vector>

using namespace std;

/*给定一个  无重复元素 的 有序 整数数组 nums 。
返回 恰好覆盖数组中所有数字 的 最小有序 区间范围列表 。
也就是说，nums 的每个元素都恰好被某个区间范围所覆盖，并且不存在属于某个范围但不属于 nums 的数字 x 。
列表中的每个区间范围 [a,b] 应该按如下格式输出：
"a->b" ，如果 a != b
"a" ，如果 a == b
示例 1：
输入：nums = [0,1,2,4,5,7]
输出：["0->2","4->5","7"]
解释：区间范围是：
[0,2] --> "0->2"
[4,5] --> "4->5"
[7,7] --> "7"

0 <= nums.length <= 20
-231 <= nums[i] <= 231 - 1
nums 中的所有值都 互不相同
nums 按升序排列
*/

class Solution {
public:
	vector<string> summaryRanges(const vector<int> &nums) {
		vector<string> res;
		string now;
		for(int i = 0; i < nums.size();) {
			int j = i + 1;
			now += std::to_string(nums[i]); // 对于负数和大于9的数不可以用 char(nums[i] + '0')，
			while(j < nums.size() && (static_cast<long long>(nums[j]) - nums[j - 1]) == 1)
				j++; // 指向第一个不满足的
			if(j != i + 1) {
				now += "->";
				now += std::to_string(nums[j - 1]);
				// 不能用 now += "->" + char(nums[j - 1] + '0'); 原因见易错点
			}
			res.push_back(now);
			now = "";
			i = j;
		}
		return res;
	}
};

int main() {
	Solution sol;
	auto res = sol.summaryRanges({0, 1, 2, 4, 6, 7});
	for(auto str : res) {
		cout << str << endl;
	}
	cout << "------------" << endl;
	res = sol.summaryRanges({199});
	for(auto str : res) {
		cout << str << endl;
	}
	cout << "------------" << endl;
	res = sol.summaryRanges({-1});
	for(auto str : res) {
		cout << str << endl;
	}
	cout << "------------" << endl;
	res = sol.summaryRanges({-1});
	for(auto str : res) {
		cout << str << endl;
	}
	cout << "------------" << endl;
	res = sol.summaryRanges({-2147483648, 0, 2, 3, 4, 6, 8, 9});
	for(auto str : res) {
		cout << str << endl;
	}
	return 0;
}