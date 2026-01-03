// Created: 2026-01-03
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 你有两个字符串，即pattern和value。
 pattern字符串由字母"a"和"b"组成，用于描述字符串中的模式。例如，字符串"catcatgocatgo"匹配模式"aabab"（其中"cat"是"a"，"go"是"b"），
该字符串也匹配像"a"、"ab"和"b"这样的模式。但需注意"a"和"b"不能同时表示相同的字符串。编写一个方法判断value字符串是否匹配pattern字符串。
示例 1：
	输入： pattern = "abba", value = "dogcatcatdog"
	输出： true
示例 2：
	输入： pattern = "abba", value = "dogcatcatfish"
	输出： false
示例 3：
	输入： pattern = "aaaa", value = "dogcatcatdog"
	输出： false
示例 4：
	输入： pattern = "abba", value = "dogdogdogdog"
	输出： true
	解释： "a"="dogdog",b=""，反之也符合规则
提示：
	1 <= len(pattern) <= 1000
	0 <= len(value) <= 1000
	你可以假设pattern只包含字母"a"和"b"，value仅包含小写字母。 */

class Solution {
public:
	bool patternMatching(string &pattern, string &value) {
		array<int, 2> cnt { 0, 0 };
		for(auto c : pattern) {
			++cnt[c - 'a'];
		}
		if(value.empty()) return cnt[0] * cnt[1] == 0;
		int n = value.size();
		if(cnt[1] == 0) return (n % cnt[0] == 0) && check(pattern, { n / cnt[0], 0 }, value);
		for(int i = 0; i <= n; ++i) { // 注意i既可以取0，又可以取n
			if((n - i * cnt[0]) % cnt[1]) continue;
			int j = (n - i * cnt[0]) / cnt[1];
			if(j >= 0 && check(pattern, { i, j }, value)) {
				return true;
			}
		}
		return false;
	}

private:
	bool check(const string &pattern, const array<int, 2> &len, const string &value) {
		array<string_view, 2> substr {};
		int i = 0;
		for(auto c : pattern) {
			int index = c - 'a';
			if(substr[index].empty()) {
				substr[index] = string_view(value.data() + i, len[index]);
				if(substr[index].size() && substr[0] == substr[1]) return false;
			} else {
				if(substr[index] != string_view(value.data() + i, len[index])) {
					return false;
				}
			}
			i += len[index];
		}
		return substr[0] != substr[1];
	}
};

int main() {
	Solution sol;
	string pattern, value;
	pattern = "aaaaab", value = "xahnxdxyaahnxdxyaahnxdxyaahnxdxyaauxuhuo";
	cout << sol.patternMatching(pattern, value) << endl;

	pattern = "abbaa", value = "dogdogdogdogdog";
	cout << sol.patternMatching(pattern, value) << endl;

	pattern = "abba", value = "dogcatcatdog";
	cout << sol.patternMatching(pattern, value) << endl;

	pattern = "abba", value = "dogcatcatfish";
	cout << sol.patternMatching(pattern, value) << endl;

	pattern = "aaaa", value = "dogcatcatdog";
	cout << sol.patternMatching(pattern, value) << endl;

	pattern = "abba", value = "dogdogdogdog";
	cout << sol.patternMatching(pattern, value) << endl;
}
