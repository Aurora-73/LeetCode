// Created: 2025-07-25
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 034. 验证外星语词典
某种外星语也使用英文小写字母，但可能顺序 order 不同。
字母表的顺序（order）是一些小写字母的排列。
给定一组用外星语书写的单词 words，以及其字母表的顺序 order，
只有当给定的单词在这种外星语中按字典序排列时，返回 true；否则，返回 false。
示例 1：
	输入：words = {"hello","leetcode"}, order = "hlabcdefgijkmnopqrstuvwxyz"
	输出：true
	解释：在该语言的字母表中，"h" 位于 "l" 之前，所以单词序列是按字典序排列的。
示例 2：
	输入：words = {"word","world","row"}, order = "worldabcefghijkmnpqstuvxyz"
	输出：false
	解释：在该语言的字母表中，"d" 位于 "l" 之后，那么 words{0} > words{1}，因此单词序列不是按字典序排列的。
示例 3：
	输入：words = {"apple","app"}, order = "abcdefghijklmnopqrstuvwxyz"
	输出：false
	解释：当前三个字符 "app" 匹配时，第二个字符串相对短一些，然后根据词典编纂规则 "apple" > "app"，
	因为 "l" > "∅"，其中 "∅" 是空白字符，定义为比任何其他字符都小（更多信息）。
提示：
	1 <= words.length <= 100
	1 <= words{i}.length <= 20
	order.length == 26
	在words{i}和order中的所有字符都是英文小写字母。
 */

class Solution {
public:
	bool isAlienSorted(vector<string> &words, string &order) {
		array<int, 26> order_map;
		for(int i = 0; i < 26; ++i) {
			order_map[order[i] - 'a'] = i;
		}
		int n = words.size();
		for(int i = 1; i < n; ++i) {
			if(!isBigger(words[i - 1], words[i], order_map)) {
				return false;
			}
		}
		return true;
	}

private:
	bool isBigger(string &left, string &right, array<int, 26> &order_map) {
		int n = min(left.size(), right.size());
		for(int i = 0; i < n; ++i) {
			if(order_map[left[i] - 'a'] > order_map[right[i] - 'a']) {
				return false;
			} else if(order_map[left[i] - 'a'] < order_map[right[i] - 'a']) {
				return true;
			}
		}
		return left.size() <= right.size();
	}
};

int main() {
	Solution sol;
	vector<string> words;
	string order;
	words = { "hello", "leetcode" }, order = "hlabcdefgijkmnopqrstuvwxyz"; // true
	cout << sol.isAlienSorted(words, order) << endl;
	words = { "word", "world", "row" }, order = "worldabcefghijkmnpqstuvxyz"; // false
	cout << sol.isAlienSorted(words, order) << endl;
	words = { "apple", "app" }, order = "abcdefghijklmnopqrstuvwxyz"; // false
	cout << sol.isAlienSorted(words, order) << endl;
}