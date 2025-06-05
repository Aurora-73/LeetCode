// Created: 2025-06-03
#include "MyUtils.h"

/*1298. 你能从盒子里获得的最大糖果数
给你 n 个盒子，每个盒子的格式为 [status, candies, keys, containedBoxes]，其中：
状态字 status[i]：整数，如果 box[i] 是开的，那么是 1，否则是 0。
糖果数 candies[i]: 整数，表示 box[i] 中糖果的数目。
钥匙 keys[i]：数组，表示你打开 box[i] 后，可以得到一些盒子的钥匙，每个元素分别为该钥匙对应盒子的下标。
内含的盒子 containedBoxes[i]：整数，表示放在 box[i] 里的盒子所对应的下标。
给你一个 initialBoxes 数组，表示你现在得到的盒子，你可以获得里面的糖果，也可以用盒子里的钥匙打开新的盒子，还可以继续探索从这个盒子里找到的其他盒子。
请你按照上述规则，返回可以获得糖果的 最大数目。*/

class Solution {
public:
	int maxCandies(vector<int> &status,
	    vector<int> &candies,
	    vector<vector<int>> &keys,
	    vector<vector<int>> &containedBoxes,
	    vector<int> &initialBoxes) {
		int res = 0;
		unordered_set<int> outButClose; // status: openButInside
		queue<int> canVisit;
		for(auto x : initialBoxes) {
			if(status[x]) {
				canVisit.push(x);
				status[x] = 0;
			} else {
				outButClose.insert(x);
			}
		}
		while(!canVisit.empty()) {
			int now = canVisit.front();
			canVisit.pop();
			res += candies[now];
			for(auto x : keys[now]) {
				status[x] = 1;
			}
			for(auto x : containedBoxes[now]) {
				if(status[x]) {
					canVisit.push(x);
					status[x] = 0;
				} else {
					outButClose.insert(x);
				}
			}
			vector<int> shouldErase;
			for(auto x : outButClose) {
				if(status[x]) {
					canVisit.push(x);
					shouldErase.push_back(x);
					status[x] = 0;
				}
			}
			for(auto x : shouldErase) {
				outButClose.erase(x);
			}
		}
		return res;
	}
}; // 类拓扑排序

class Solution {
public:
	int maxCandies(vector<int> &status,
	    vector<int> &candies,
	    vector<vector<int>> &keys,
	    vector<vector<int>> &containedBoxes,
	    vector<int> &initialBoxes) {
		int ans = 0;
		auto &has_key = status; // 把开着的盒子当作有钥匙
		vector<uint8_t> has_box(status.size());
		for(int x : initialBoxes) {
			has_box[x] = true;
		}

		std::function<void(int)> dfs = [&](int x) {
			ans += candies[x];
			has_box[x] = false;

			for(int y : keys[x]) {
				has_key[y] = true;
				if(has_box[y]) {
					dfs(y); // 调用自己需要用仿函数包装
				}
			}

			for(int y : containedBoxes[x]) {
				has_box[y] = true;
				if(has_key[y]) {
					dfs(y);
				}
			}
		};

		for(int x : initialBoxes) {
			if(has_key[x] && has_box[x]) {
				dfs(x);
			}
		}

		return ans;
	}
};

int main() {
	Solution sol;
	vector<int> status, candies, initialBoxes;
	vector<vector<int>> keys, containedBoxes;
	status = { 1, 0, 0, 0, 0, 0 };
	candies = { 1, 1, 1, 1, 1, 1 };
	keys = { { 1, 2, 3, 4, 5 }, {}, {}, {}, {}, {} };
	containedBoxes = { { 1, 2, 3, 4, 5 }, {}, {}, {}, {}, {} };
	initialBoxes = { 0 };
	cout << sol.maxCandies(status, candies, keys, containedBoxes, initialBoxes) << endl;
}