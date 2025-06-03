// Created: 2025-06-03
#include "MyUtils.h"
#include <chrono>
using namespace std::chrono;
/*1964. 找出到每个位置为止最长的有效障碍赛跑路线
你打算构建一些障碍赛跑路线。给你一个 下标从 0 开始 的整数数组 obstacles ，数组长度为 n ，其中 obstacles[i] 表示第 i 个障碍的高度。
对于每个介于 0 和 n - 1 之间（包含 0 和 n - 1）的下标  i ，在满足下述条件的前提下，请你找出 obstacles 能构成的最长障碍路线的长度：
    你可以选择下标介于 0 到 i 之间（包含 0 和 i）的任意个障碍。
    在这条路线中，必须包含第 i 个障碍。
    你必须按障碍在 obstacles 中的 出现顺序 布置这些障碍。
    除第一个障碍外，路线中每个障碍的高度都必须和前一个障碍 相同 或者 更高 。
    返回长度为 n 的答案数组 ans ，其中 ans[i] 是上面所述的下标 i 对应的最长障碍赛跑路线的长度。*/

class Solution1 {
public:
	vector<int> longestObstacleCourseAtEachPosition(vector<int> &obstacles) {
		int n = obstacles.size();
		vector<int> dp(n);
		for(int i = 0; i < n; ++i) {
			int maxSubLen = 0;
			for(int j = i - 1; j >= 0; --j) {
				if(obstacles[j] <= obstacles[i] && dp[j] > maxSubLen) {
					maxSubLen = dp[j];
				}
			}
			dp[i] = maxSubLen + 1;
		}
		return dp;
	}
}; // 寻找每个元素结尾的最长非严格递增子序列的长度

class Solution {
public:
	vector<int> longestObstacleCourseAtEachPosition(vector<int> &obstacles) {
		int n = obstacles.size();
		vector<int> dp(n), minTails { INT_MIN }; // 加一个初始值可以防止空数组取 back 和 dp + 1
		minTails.reserve(n);
		for(int i = 0; i < n; ++i) {
			if(obstacles[i] >= minTails.back()) {
				dp[i] = minTails.size();
				minTails.push_back(obstacles[i]);
			} else {
				auto it = upper_bound(minTails.begin(), minTails.end(), obstacles[i]);
				dp[i] = it - minTails.begin();
				*it = obstacles[i];
			}
		}
		return dp;
	}
};

int main() {
	Solution sol;
	Solution1 sol1;
	vector<int> obstacles { 3,
		1,
		5,
		6,
		4,
		2,
		892,
		3722,
		39,
		032,
		890,
		451,
		578,
		345,
		783,
		458,
		342,
		656,
		75678,
		43,
		6573,
		476,
		5732,
		56763,
		21567236,
		78456,
		78452,
		67567,
		3467567,
		34265,
		736565,
		346254,
		56724,
		376287,
		909,
		62,
		576,
		875,
		42,
		689,
		245,
		67258,
		682,
		5476,
		254768,
		542967,
		52486,
		187,
		655,
		27,
		469,
		823,
		75,
		6923,
		1,
		5,
		6,
		4,
		2,
		892,
		3722,
		39,
		032,
		890,
		451,
		578,
		345,
		783,
		458,
		342,
		656,
		75678,
		43,
		6573,
		476,
		5732,
		56763,
		21567236,
		78456,
		78452,
		67567,
		3467567,
		34265,
		736565,
		346254,
		56724,
		376287,
		909,
		62,
		576,
		875,
		42,
		689,
		245,
		67258,
		682,
		5476,
		254768,
		542967,
		52486,
		187,
		655,
		27,
		469,
		823,
		75,
		692 };
	auto a = high_resolution_clock::now();
	auto res = sol.longestObstacleCourseAtEachPosition(obstacles);
	auto b = high_resolution_clock::now();
	auto res1 = sol1.longestObstacleCourseAtEachPosition(obstacles);
	auto c = high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = b - a;
	std::cout << "Solution result: " << res << ", time: " << elapsed.count() << " ms\n";
	std::chrono::duration<double, std::milli> elapsed1 = c - b;
	std::cout << "Solution1 result: " << res1 << ", time: " << elapsed1.count() << " ms\n";
}