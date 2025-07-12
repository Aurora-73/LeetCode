// Created: 2025-07-11
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 1268. 搜索推荐系统
给你一个产品数组products和一个字符串searchWord，products 数组中每个产品都是一个字符串。
请你设计一个推荐系统，在依次输入单词searchWord 的每一个字母后，
推荐products 数组中前缀与searchWord 相同的最多三个产品。如果前缀相同的可推荐产品超过三个，请按字典序返回最小的三个。
请你以二维列表的形式，返回在输入searchWord每个字母后相应的推荐产品的列表。
示例 1：
	输入：products = {"mobile","mouse","moneypot","monitor","mousepad"}, searchWord = "mouse"
	输出：{
	{"mobile","moneypot","monitor"},
	{"mobile","moneypot","monitor"},
	{"mouse","mousepad"},
	{"mouse","mousepad"},
	{"mouse","mousepad"}
	}
	解释：按字典序排序后的产品列表是 {"mobile","moneypot","monitor","mouse","mousepad"}
	输入 m 和 mo，由于所有产品的前缀都相同，
	所以系统返回字典序最小的三个产品 {"mobile","moneypot","monitor"}
	输入 mou， mous 和 mouse 后系统都返回 {"mouse","mousepad"}
示例 2：
	输入：products = {"havana"}, searchWord = "havana"
	输出：{{"havana"},{"havana"},{"havana"},{"havana"},{"havana"},{"havana"}}
示例 3：
	输入：products = {"bags","baggage","banner","box","cloths"}, searchWord = "bags"
	输出：{{"baggage","bags","banner"},{"baggage","bags","banner"},{"baggage","bags"},{"bags"}}
示例 4：
	输入：products = {"havana"}, searchWord = "tatiana"
	输出：{{},{},{},{},{},{},{}}
提示：
	1 <= products.length <= 1000
	1 <= Σ products{i}.length <= 2 * 10^4
	products{i}中所有的字符都是小写英文字母。
	1 <= searchWord.length <= 1000
	searchWord中所有字符都是小写英文字母。 */

class TireNode {
public:
	int id = -1;
	array<unique_ptr<TireNode>, 26> chirds {};
};

class Solution1 {
public:
	vector<vector<string>> suggestedProducts(vector<string> &products, string &searchWord) {
		TireNode root, *now = &root;
		for(unsigned i = 0; i < products.size(); ++i) {
			buildTireNode(products[i], &root, i);
		}
		int n = searchWord.size();
		vector<vector<string>> res(n);
		for(int i = 0; i < n; ++i) {
			if(now->chirds[searchWord[i] - 'a']) {
				int num = 3;
				now = now->chirds[searchWord[i] - 'a'].get();
				findNear(products, now, res[i], num);
			} else {
				return res;
			}
		}
		return res;
	}

private:
	void buildTireNode(string &product, TireNode *now, int id) {
		for(auto c : product) {
			if(!now->chirds[c - 'a']) {
				now->chirds[c - 'a'] = make_unique<TireNode>();
			}
			now = now->chirds[c - 'a'].get();
		}
		now->id = id;
	}
	void findNear(vector<string> &products, TireNode *root, vector<string> &now, int &num) {
		if(root->id != -1) {
			now.push_back(products[root->id]);
			--num;
		}
		for(auto &chird : root->chirds) {
			if(num == 0) {
				return;
			}
			if(chird) {
				findNear(products, chird.get(), now, num);
			}
		}
	}
};

class Solution {
public:
	vector<vector<string>> suggestedProducts(vector<string> &products, string &searchWord) {
		sort(products.begin(), products.end());
		int n = searchWord.size();
		vector<vector<string>> ans(n);
		constexpr char bigger = 'z' + 1;
		string prefix;
		prefix.reserve(n + 1);
		prefix.push_back(bigger);
		for(int i = 0; i < n; ++i) {
			prefix.back() = searchWord[i];
			auto beg = lower_bound(products.begin(), products.end(), prefix);
			prefix.push_back(bigger);
			auto end = lower_bound(products.begin(), products.end(), prefix);
			for(int k = 0; k < 3 && beg + k != end; ++k) {
				ans[i].push_back(beg[k]);
			}
		}
		return ans;
	}
}; // 先对产品进行排序，然后寻找当前前缀的上下限，从上限开始取至多 3 个元素

int main() {
	Solution sol;
	vector<string> products;
	string searchWord;
	products = { "mobile", "mouse", "moneypot", "monitor", "mousepad" }, searchWord = "mouse";
	cout << sol.suggestedProducts(products, searchWord) << endl;
	// { {"mobile","moneypot","monitor"}, {"mobile","moneypot","monitor"}, {"mouse","mousepad"}, {"mouse","mousepad"},{"mouse","mousepad"}}

	products = { "havana" }, searchWord = "havana";
	cout << sol.suggestedProducts(products, searchWord) << endl;
	// {{"havana"},{"havana"},{"havana"},{"havana"},{"havana"},{"havana"}}

	products = { "bags", "baggage", "banner", "box", "cloths" }, searchWord = "bags";
	cout << sol.suggestedProducts(products, searchWord) << endl;
	// {{"baggage","bags","banner"},{"baggage","bags","banner"},{"baggage","bags"},{"bags"}}

	products = { "havana" }, searchWord = "tatiana";
	cout << sol.suggestedProducts(products, searchWord) << endl;
	// {{},{},{},{},{},{},{}}
}