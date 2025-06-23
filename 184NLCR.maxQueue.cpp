// Created: 2025-06-23
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 184. 设计自助结算系统（最大队列）
请设计一个自助结账系统，该系统需要通过一个队列来模拟顾客通过购物车的结算过程，需要实现的功能有：
	get_max()：获取结算商品中的最高价格，如果队列为空，则返回 -1
	add(value)：将价格为 value 的商品加入待结算商品队列的尾部
	remove()：移除第一个待结算的商品价格，如果队列为空，则返回 -1
注意，为保证该系统运转高效性，以上函数的均摊时间复杂度均为 O(1)
示例 1：
	输入: 
	{"Checkout","add","add","get_max","remove","get_max"}
	{{},{4},{7},{},{},{}}
	输出: {null,null,null,7,4,7}
示例 2：
	输入: 
	{"Checkout","remove","get_max"}
	{{},{},{}}
	输出: {null,-1,-1}
提示：
	1 <= get_max, add, remove 的总操作数<= 10000
	1 <= value <= 10^5 */

class Checkout1 {
public:
	Checkout1() { }

	int get_max() {
		if(s.rbegin() != s.rend()) {
			return *(s.rbegin());
		} else {
			return -1;
		}
	}

	void add(int value) {
		s.insert(value);
		q.push(value);
	}

	int remove() {
		if(q.empty()) return -1;
		int val = q.front();
		q.pop(), s.erase(val);
		return val;
	}

private:
	queue<int> q;
	set<int> s;
};

class Checkout {
public:
	Checkout() { }

	int get_max() {
		if(maxs.empty()) return -1;
		return maxs.front();
	}

	void add(int value) {
		vals.push(value);
		while(!maxs.empty() && maxs.back() < value) maxs.pop_back();
		maxs.push_back(value);
	}

	int remove() {
		if(vals.empty()) return -1;
		int val = vals.front();
		vals.pop();
		if(val == maxs.front()) maxs.pop_front();
		return val;
	}

private:
	queue<int> vals;
	deque<int> maxs;
};
/* add(int value) - 入队操作
    步骤：
        将value加入vals队列。
        维护maxs：从maxs尾部开始，移除所有小于value的元素，然后将value加入maxs尾部。
    原理：
        新元素value加入后，队列中所有小于value的元素在value出队前不可能成为最大值（因为它们比value小且更早入队）。
        移除这些元素确保maxs严格递减，且队头是最大值。注意这里的相同值也要在队列里保存两遍
remove() - 出队操作
    步骤：
        若vals为空，返回-1。
        弹出vals队头元素val。
        检查最大值：若val等于maxs队头，说明当前最大值已出队，同步弹出maxs队头。
    原理：
        只有被移除的元素是当前最大值时，才更新maxs（因为maxs队头始终是当前最大值）。
        若移除的不是最大值，maxs无需修改。
        时间复杂度：O(1)。
get_max() - 获取最大值
    步骤：
        若maxs为空，返回-1（队列空）。
        直接返回maxs队头。
    原理：
        maxs队头始终是当前队列的最大值。
时间复杂度：O(1)。 */

int main() {
	Checkout checkout;
	// 示例1
	checkout.add(4);
	checkout.add(7);
	std::cout << checkout.get_max() << " ";       // 7
	std::cout << checkout.remove() << " ";        // 4
	std::cout << checkout.get_max() << std::endl; // 7

	// 示例2
	Checkout checkout2;
	std::cout << checkout2.remove() << " ";        // -1
	std::cout << checkout2.get_max() << std::endl; // -1

	// 更多测试
	checkout.add(2);
	checkout.add(5);
	checkout.add(3);
	std::cout << checkout.get_max() << " ";       // 7
	std::cout << checkout.remove() << " ";        // 7
	std::cout << checkout.get_max() << " ";       // 5
	std::cout << checkout.remove() << " ";        // 2
	std::cout << checkout.get_max() << " ";       // 5
	std::cout << checkout.remove() << " ";        // 5
	std::cout << checkout.get_max() << " ";       // 3
	std::cout << checkout.remove() << " ";        // 3
	std::cout << checkout.get_max() << std::endl; // -1

	return 0;
}