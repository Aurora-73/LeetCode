// Created: 2025-05-11
#include "MyUtils.h"

/*17. 电话号码的字母组合
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
提示：0 <= digits.length <= 4
digits[i] 是范围 ['2', '9'] 的一个数字。*/

class Solution {
public:
	vector<string> letterCombinations(string digits) {
		if(!digits.size())
			return {};
		end = digits.end();
		string combian;
		dfs(digits.begin(), combian);
		return std::move(res);
	}

private:
	void dfs(string::iterator it, string &combian) {
		if(it == end) {
			res.push_back(combian);
			return;
		}
		for(auto c : phoneMap[*it - '0']) {
			combian.push_back(c);
			dfs(it + 1, combian);
			combian.pop_back(); // 范围下一个之前将当前值加入，访问之后将当前值删除，这样不用复制很多份了
		}
	}
	vector<string> phoneMap { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
	vector<string> res;
	string::iterator end;
};

int main() {
	Solution sol;
	cout << sol.letterCombinations("23") << endl;
	cout << sol.letterCombinations("24587") << endl;
}
