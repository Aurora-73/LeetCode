// Created: 2026-01-25
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给你两个 版本号字符串version1 和 version2，请你比较它们。
版本号由被点"." 分开的修订号组成。修订号的值 是它 转换为整数 并忽略前导零。
比较版本号时，请按 从左到右的顺序 依次比较它们的修订号。如果其中一个版本字符串的修订号较少，则将缺失的修订号视为 0。
返回规则如下：
	如果version1<version2 返回 -1，
	如果version1>version2返回1，
	除此之外返回 0。
示例 1：
	输入：version1 = "1.2", version2 = "1.10"
	输出：-1
	解释：
	version1 的第二个修订号为"2"，version2 的第二个修订号为 "10"：2 < 10，
	所以 version1 < version2。
示例 2：
	输入：version1 = "1.01", version2 = "1.001"
	输出：0
	解释：
	忽略前导零，"01" 和 "001" 都代表相同的整数 "1"。
示例 3：
	输入：version1 = "1.0", version2 = "1.0.0.0"
	输出：0
	解释：
	version1 有更少的修订号，每个缺失的修订号按 "0" 处理。
提示：
	1 <= version1.length, version2.length <= 500
	version1 和 version2 仅包含数字和 "."
	version1 和 version2 都是 有效版本号
	version1 和 version2 的所有修订号都可以存储在 32 位整数 中 */

class Solution1 {
public:
	int compareVersion(string &version1, string &version2) {
		int n1 = version1.size(), n2 = version2.size(), i = 0, j = 0;
		while(i < n1 || j < n2) { // 不能用 &&
			// 移除前导0
			while(i < n1 && version1[i] == '0') ++i;
			while(j < n2 && version2[j] == '0') ++j;
			// 先计算长度
			int begi = i, begj = j;
			while(i < n1 && version1[i] != '.') ++i;
			while(j < n2 && version2[j] != '.') ++j;
			// 长度不同长的更大
			if(i - begi != j - begj) return i - begi < j - begj ? -1 : 1;
			// 长度相同逐位比较
			while(begi < i && begj < j) {
				int diff = version1[begi] - version2[begj];
				if(diff != 0) {
					return diff < 0 ? -1 : 1;
				}
				++begi, ++begj;
			}
			++i, ++j;
		}
		return 0;
	}
}; // 不能转换为int，会溢出

class Solution {
public:
	int compareVersion(string &version1, string &version2) {
		int n1 = version1.size(), n2 = version2.size();
		int i = 0, j = 0;

		while(i < n1 || j < n2) {
			// 1. 读 version1 的一段，去前导0
			int start1 = i;
			while(start1 < n1 && version1[start1] == '0') ++start1;
			int end1 = start1;
			while(end1 < n1 && version1[end1] != '.') ++end1;

			// 2. 读 version2 的一段，去前导0
			int start2 = j;
			while(start2 < n2 && version2[start2] == '0') ++start2;
			int end2 = start2;
			while(end2 < n2 && version2[end2] != '.') ++end2;

			int len1 = end1 - start1;
			int len2 = end2 - start2;

			// 3. 先比长度
			if(len1 != len2) {
				return len1 < len2 ? -1 : 1;
			}

			// 4. 再逐位比
			for(int k = 0; k < len1; ++k) {
				if(version1[start1 + k] != version2[start2 + k]) {
					return version1[start1 + k] < version2[start2 + k] ? -1 : 1;
				}
			}

			// 5. 跳过当前段和 '.'
			i = end1 + 1;
			j = end2 + 1;
		}

		return 0;
	}
};

int main() {
	Solution sol;
	string version1, version2;
	version1 = "7.5.2.4", version2 = "7.5.3";
	cout << sol.compareVersion(version1, version2) << endl;

	version1 = "1.2", version2 = "1.10";
	cout << sol.compareVersion(version1, version2) << endl;

	version1 = "1.01", version2 = "1.001";
	cout << sol.compareVersion(version1, version2) << endl;

	version1 = "1.0", version2 = "1.0.0.0";
	cout << sol.compareVersion(version1, version2) << endl;
}