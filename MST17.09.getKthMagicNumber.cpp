// Created: 2026-01-05
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 将全部的 只含有 3,5,7 这三种素因子 的数排序，求其中的第k个数。
注意，不是必须同时有这些素因子，而是必须不包含其他的素因子。例如，前几个数按顺序应该是 1，3，5，7，9，15，21。
示例 1：
	输入：k = 5
	输出：9 */

// class Solution1 {
// public:
// 	int getKthMagicNumber(int k) {
// 		vector<int> vals;
// 		vals.reserve(k);
// 		vals.push_back(1);
// 		int id3 = 0, id5 = 0, id7 = 0;
// 		while(--k) {
// 			int t3 = vals[id3] * 3, t5 = vals[id5] * 5, t7 = vals[id7] * 7;
// 			if(t3 <= t5 && t3 <= t7) {
// 				vals.push_back(t3);
// 				++id3;
// 			} else if(t5 <= t3 && t5 <= t7) {
// 				vals.push_back(t5);
// 				++id5;
// 			} else if(t7 <= t3 && t7 <= t5) {
// 				vals.push_back(t7);
// 				++id7;
// 			}
// 		}
// 		return vals.back();
// 	}
// }; // 错误代码，因为t3 t5 t7中出现相等的最小元素的时候需要同时移动，否则会加入重复元素

class Solution1 {
public:
	int getKthMagicNumber(int k) {
		vector<int> vals;
		vals.reserve(k);
		vals.push_back(1);
		int id3 = 0, id5 = 0, id7 = 0;
		while(--k) {
			int t3 = vals[id3] * 3, t5 = vals[id5] * 5, t7 = vals[id7] * 7;
			vals.push_back(min({ t3, t5, t7 }));
			if(vals.back() == t3) ++id3;
			if(vals.back() == t5) ++id5;
			if(vals.back() == t7) ++id7;
		}
		return vals.back();
	}
}; // 注意由于t357可能相等，这时需要同时移动，因此不能用else if

class Solution {
public:
	int getKthMagicNumber(int k) {
		return nums[k];
	}

private:
	inline static constexpr int max_size = 652; // 652已经是最大的了，更大就不是int了，会报错
	inline static constexpr std::array<int, max_size + 1> nums = []() constexpr {
		std::array<int, max_size + 1> res { 0, 1 };
		int id3 = 1, id5 = 1, id7 = 1;
		for(int i = 2; i <= max_size; ++i) {
			int t3 = res[id3] * 3, t5 = res[id5] * 5, t7 = res[id7] * 7;
			res[i] = std::min({ t3, t5, t7 });
			if(res[i] == t3) ++id3;
			if(res[i] == t5) ++id5;
			if(res[i] == t7) ++id7;
		}
		return res;
	}();
};
/* 在运行期：
    int 溢出 = UB，但很多平台“看起来还能跑”
在 constexpr 编译期：
    标准要求：必须是严格合法的常量表达式
    一旦 UB → 编译器直接拒绝 */

int main() {
	Solution sol;
	int k;
	k = 5;
	cout << sol.getKthMagicNumber(k) << endl;

	k = 15;
	cout << sol.getKthMagicNumber(k) << endl;
}