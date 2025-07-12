// Created: 2025-07-12
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 901. 股票价格跨度
设计一个算法收集某些股票的每日报价，并返回该股票当日价格的 跨度。
当日股票价格的 跨度 被定义为股票价格小于或等于今天价格的最大连续日数（从今天开始往回数，包括今天）。
	例如，如果未来 7 天股票的价格是 {100,80,60,70,60,75,85}，
那么股票跨度将是 {1,1,1,2,1,4,6}。
实现 StockSpanner 类：
	StockSpanner() 初始化类对象。
	int next(int price) 给出今天的股价 price，返回该股票当日价格的 跨度。
示例：
    输入：
        {"StockSpanner", "next", "next", "next", "next", "next", "next", "next"}
        {{}, {100}, {80}, {60}, {70}, {60}, {75}, {85}}
    输出：
        {null, 1, 1, 1, 2, 1, 4, 6}
    解释：
        StockSpanner stockSpanner = new StockSpanner();
        stockSpanner.next(100); // 返回 1
        stockSpanner.next(80);  // 返回 1
        stockSpanner.next(60);  // 返回 1
        stockSpanner.next(70);  // 返回 2
        stockSpanner.next(60);  // 返回 1
        stockSpanner.next(75);  // 返回 4，
        因为截至今天的最后 4 个股价 (包括今天的股价 75) 都小于或等于今天的股价。
        stockSpanner.next(85);  // 返回 6
提示：
	1 <= price <= 10^5
	最多调用 next 方法 10^4 次 */

class StockSpanner1 {
public:
	StockSpanner1() { }

	int next(int price) {
		int res = 1;
		while(!st.empty() && st.top().first <= price) {
			res += st.top().second;
			st.pop();
		}
		st.emplace(price, res);
		return res;
	}

private:
	stack<pair<int, int>> st;
}; // 后进先出，比当前小的都出栈，单调递减栈，同时记录当前的跨度

class StockSpanner {
public:
	StockSpanner() {
		prices.reserve(5000);
		spans.reserve(5000);
	}

	int next(int price) {
		int span = 1;
		while(!prices.empty() && prices.back() <= price) {
			span += spans.back();
			prices.pop_back();
			spans.pop_back();
		}
		prices.push_back(price);
		spans.push_back(span);
		return span;
	}

private:
	vector<int> prices;
	vector<int> spans;
};

int main() {
	StockSpanner ss;
	cout << ss.next(100) << endl;
	cout << ss.next(80) << endl;
	cout << ss.next(60) << endl;
	cout << ss.next(70) << endl;
	cout << ss.next(60) << endl;
	cout << ss.next(75) << endl;
	cout << ss.next(85) << endl;
}