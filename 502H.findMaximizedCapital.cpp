// Created: 2025-05-21
#include "MyUtils.h"

/*    502. IPO
假设 力扣（LeetCode）即将开始 IPO 。为了以更高的价格将股票卖给风险投资公司，力扣 希望在 IPO
之前开展一些项目以增加其资本。 由于资源有限，它只能在 IPO 之前完成最多 k 个不同的项目。帮助 力扣
设计完成最多 k 个不同项目后得到最大总资本的方式。 给你 n 个项目。对于每个项目 i ，它都有一个纯利润
profits[i] ，和启动该项目需要的最小资本 capital[i] 。 最初，你的资本为 w
。当你完成一个项目时，你将获得纯利润，且利润将被添加到你的总资本中。 总而言之，从给定项目中选择 最多
k 个不同项目的列表，以 最大化最终资本 ，并输出最终可获得的最多资本。 答案保证在 32
位有符号整数范围内。  */

class Solution1 {
public:
	int findMaximizedCapital(int k, int w, const vector<int> &profits, const vector<int> &capital) {
		auto comp1 = [&](const int &__x, const int &__y) {
			return capital[__x] > capital[__y];
		};
		// 保存还不能做的全部项目中需要最少的资本 下标
		priority_queue<int, vector<int>, decltype(comp1)> notCanDo(comp1);

		auto comp2 = [&](const int &__x, const int &__y) {
			return profits[__x] < profits[__y];
		};
		// 保存可以做的全部项目中收益最高的资本 下标
		priority_queue<int, vector<int>, decltype(comp2)> canDo(comp2);
		int n = profits.size();
		for(int i = 0; i < n; ++i) {
			if(capital[i] <= w) {
				canDo.push(i);
			} else {
				notCanDo.push(i);
			}
		}
		while(k-- && !canDo.empty()) {
			int now = canDo.top();
			canDo.pop();
			w += profits[now];
			while(!notCanDo.empty() && capital[notCanDo.top()] <= w) {
				canDo.push(notCanDo.top());
				notCanDo.pop();
			}
		}
		return w;
	}
};
/*
优先队列管理项目：
    notCanDo：按所需资本从小到大排序，保存当前还不能做的项目下标。
    canDo：按利润从大到小排序，保存当前可以做的项目下标。
初始化：
    遍历所有项目，把能做的项目放入 canDo，不能做的放入 notCanDo。
每次选择：
    从 canDo 里选利润最大的项目做，资本增加。
    检查 notCanDo 里有没有因为资本增加而现在可以做的项目，有就转移到 canDo。
    循环 k 次或直到没有可做项目。
    返回最终资本。
*/

class Solution2 {
public:
	// 寻找完成最多k个项目后可获得的最大资本
	int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital) {
		int n = profits.size();
		// 优化：如果初始资本已足够做所有项目，直接取利润最大的k个项目
		if(w >= *std::max_element(capital.begin(), capital.end())) {
			sort(profits.begin(), profits.end(), greater<int>());
			for(int i = 0; i < k && i < n; ++i) {
				w += profits[i];
			}
			return w;
		}
		// 按所需资本和利润组成项目对，并按资本升序排序
		vector<pair<int, int>> projects;
		for(int i = 0; i < n; ++i) {
			projects.emplace_back(capital[i], profits[i]);
		}
		sort(projects.begin(),
		    projects.end()); // 先比较第一个元素（first），如果相等再比较第二个元素（second）。

		// 最大堆，保存当前可做项目的利润
		priority_queue<int> maxProfitHeap;
		int curr = 0;
		for(int i = 0; i < k; ++i) {
			// 将所有当前资本可做的项目利润加入堆
			while(curr < n && projects[curr].first <= w) {
				maxProfitHeap.push(projects[curr].second);
				++curr;
			}
			// 如果有可做项目，选择利润最大的做
			if(!maxProfitHeap.empty()) {
				w += maxProfitHeap.top();
				maxProfitHeap.pop();
			} else {
				// 没有可做项目，提前结束
				break;
			}
		}
		return w;
	}
};

int main() {
	Solution2 sol;
	int k = 2, w = 0;
	vector<int> profits = { 1, 2, 3 }, capital = { 0, 1, 1 };
	cout << sol.findMaximizedCapital(k, w, profits, capital) << endl;
}