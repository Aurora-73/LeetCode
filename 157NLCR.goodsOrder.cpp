// Created: 2025-06-28
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 157. 套餐内商品的排列顺序
某店铺将用于组成套餐的商品记作字符串 goods，其中 goods{i} 表示对应商品。
请返回该套餐内所含商品的 全部排列方式。
返回结果 无顺序要求，但不能含有重复的元素。
示例 1：
	输入：goods = "agew"
	输出：{"aegw","aewg","agew","agwe","aweg","awge","eagw","eawg","egaw","egwa","ewag","ewga","gaew","gawe","geaw","gewa","gwae","gwea","waeg","wage","weag","wega","wgae","wgea"}
提示：
	1 <= goods.length <= 8 
    goods 中可能包含重复元素，且仅包含小写字母 */

class Solution1 {
public:
	vector<string> goodsOrder(string &goods) {
		res.clear(), now.clear();
		n = goods.size(), count = 0, visited.resize(n, 0);
		ranges::sort(goods);
		dfs(goods);
		return res;
	}

private:
	int n, count;
	string now;
	vector<bool> visited;
	vector<string> res;
	void dfs(string &goods) {
		if(count == n) {
			res.push_back(now);
			return;
		}
		for(int i = 0; i < n; ++i) {
			if(!visited[i] && (i == 0 || goods[i] != goods[i - 1] || visited[i - 1])) {
				now.push_back(goods[i]);
				visited[i] = 1;
				++count;
				dfs(goods);
				--count;
				visited[i] = 0;
				now.pop_back();
			}
		}
	}
}; // 用「排序＋同层跳过相同字符」的剪枝，确保同一层只选一个相同的字符

class Solution2 {
public:
	vector<string> goodsOrder(string goods) {
		count = vector<int>(26);
		result.clear(), now.clear();
		for(auto c : goods) {
			count[c - 'a']++;
		}
		size = goods.size();
		pailie();
		return result;
	}

private:
	vector<int> count;     // 记录每个字符的剩余可用次数
	string now;            // 当前正在构建的排列
	int size;              // 剩余需要填充的位置数
	vector<string> result; // 存储所有排列结果
	void pailie() {
		if(size == 0) {
			result.push_back(now);
			return;
		}
		for(int i = 0; i < 26; ++i) {
			if(count[i] >= 1) {
				now.push_back(i + 'a');
				size--;
				count[i]--;
				pailie();
				now.erase(now.size() - 1);
				count[i]++;
				size++;
			}
		}
	}
}; // 用「频次数组」直接当作多重集合来做 DFS／回溯，根本上把重复元素合并成一个选项，天然不会重复。

class Solution {
public:
	vector<string> goodsOrder(string &goods) {
		res.clear(), now.clear();
		n = goods.size(), count = 0, visited.resize(n, 0);
		dfs(goods);
		return res;
	}

private:
	int n, count;
	string now;
	vector<bool> visited;
	vector<string> res;
	void dfs(string &goods) {
		if(count == n) {
			res.push_back(now);
			return;
		}
		bitset<26> lv;
		for(int i = 0; i < n; ++i) {
			if(!visited[i] && !lv[goods[i] - 'a']) {
				lv[goods[i] - 'a'] = 1;
				now.push_back(goods[i]);
				visited[i] = 1;
				++count;
				dfs(goods);
				--count;
				visited[i] = 0;
				now.pop_back();
			}
		}
	}
}; // 用「遍历集合」保证每次遍历每个字母最多用一次

// 重点：当前节点的每个位置相同的元素至多便利一次

int main() {
	Solution sol;
	string goods;
	goods = "aab";
	cout << sol.goodsOrder(goods) << endl;
	goods = "abc";
	cout << sol.goodsOrder(goods) << endl;
	goods = "agew";
	cout << sol.goodsOrder(goods) << endl;
}