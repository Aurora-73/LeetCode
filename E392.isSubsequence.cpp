#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

/*给定字符串 s 和 t ，判断 s 是否为 t 的子序列。
字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。
进阶：
如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >= 10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？
*/

class Solution {
public:
	bool isSubsequence(string s, string t) {
		int index = 0;
		for(int i = 0; i < t.size(); i++) {
			if(t[i] == s[index]) {
				index++;
			}
		}
		return index == s.size();
	}
};
// 直接从左往右即可，不需要考虑 i 的回溯，因为即使后面即使有可行的开头，第一个开头也是可用的开头

int main() {
	string s = "abc", t = "ahbgdc";
	Solution sol;
	cout << sol.isSubsequence(s, t);
}
