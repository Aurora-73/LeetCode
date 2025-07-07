// Created: 2025-07-07
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 2336. 无限集中的最小数字
现有一个包含所有正整数的集合 {1, 2, 3, 4, 5, ...}。
实现 SmallestInfiniteSet 类：
	SmallestInfiniteSet() 初始化 SmallestInfiniteSet 对象以包含 所有 正整数。
	int popSmallest() 移除 并返回该无限集中的最小整数。
	void addBack(int num) 如果正整数 num 不 存在于无限集中，则将一个 num 添加 到该无限集中。
示例：
    输入
        {"SmallestInfiniteSet", "addBack", "popSmallest", "popSmallest", "popSmallest", "addBack", "popSmallest", "popSmallest", "popSmallest"}
        {{}, {2}, {}, {}, {}, {1}, {}, {}, {}}
        输出
        {null, null, 1, 2, 3, null, 1, 4, 5}
    解释
        SmallestInfiniteSet smallestInfiniteSet = new SmallestInfiniteSet();
        smallestInfiniteSet.addBack(2);    // 2 已经在集合中，所以不做任何变更。
        smallestInfiniteSet.popSmallest(); // 返回 1，因为 1 是最小的整数，并将其从集合中移除。
        smallestInfiniteSet.popSmallest(); // 返回 2，并将其从集合中移除。
        smallestInfiniteSet.popSmallest(); // 返回 3，并将其从集合中移除。
        smallestInfiniteSet.addBack(1);    // 将 1 添加到该集合中。
        smallestInfiniteSet.popSmallest(); // 返回 1，因为 1 在上一步中被添加到集合中，
                                        // 且 1 是最小的整数，并将其从集合中移除。
        smallestInfiniteSet.popSmallest(); // 返回 4，并将其从集合中移除。
        smallestInfiniteSet.popSmallest(); // 返回 5，并将其从集合中移除。
    提示：
        1 <= num <= 1000
        最多调用 popSmallest 和 addBack 方法 共计 1000 次 */

class SmallestInfiniteSet1 {
public:
	SmallestInfiniteSet1() {
		pq.push(1);
	}

	int popSmallest() {
		int res = pq.top();
		pq.pop();
		while(visited.count(res)) {
			res = pq.top();
			pq.pop();
		}
		visited.insert(res);
		if(!visited.count(res + 1)) {
			pq.push(res + 1);
		}
		return res;
	}

	void addBack(int num) {
		if(visited.erase(num)) {
			pq.push(num);
		}
	}

private:
	unordered_set<int> visited;
	priority_queue<int, vector<int>, greater<int>> pq;
};

class SmallestInfiniteSet2 {
public:
	SmallestInfiniteSet2() {
		now = 1;
		set.insert(1);
	}

	int popSmallest() {
		int res = *set.begin();
		set.erase(set.begin());
		if(now == res) {
			++now;
			set.insert(res + 1);
		}
		return res;
	}

	void addBack(int num) {
		set.insert(num);
	}

private:
	int now;
	set<int> set;
};
/*  用一个 std::set<int> st 来维护当前还在集合里的所有候选数字。
    再用一个整数 now 记录「从 1 开始，下一个从未被取过的自然数」。初始 now=1，且把 1 插入 st。
popSmallest()：
    取 *st.begin() 作为最小值 res，并 erase 之；
    如果这个 res 恰好等于 now，说明这是「第一次被弹出」的那条最小未生成数，
    则要把 now+1 插到 st 里，并 now++，保证集合中始终包含「下一个全新值」。
addBack(num)：
    直接 st.insert(num)——如果 num 已经在集合里或 num>=now，set 会自动去重或忽略。*/

class SmallestInfiniteSet {
public:
	SmallestInfiniteSet() { }

	int popSmallest() {
		if(s.empty()) {
			int ans = thres;
			++thres;
			return ans;
		}
		int ans = *s.begin();
		s.erase(s.begin());
		return ans;
	}

	void addBack(int num) {
		if(num < thres) {
			s.insert(num);
		}
	}

private:
	int thres = 1;
	set<int> s; // 小于thres，且可以使用的元素
};
/*  用 int thres 记录「从未被弹出过、当前最小的的自然数」。初始化 thres=1。
    用 set<int> s 只存那些「曾经被弹出过、但后来 addBack 放回来的数字」。
popSmallest()：
    如果 s 不空，说明有放回来的小于 thres 的数字，取 *s.begin()；
    否则，就返回并 thres++，向外生成一个新的最小正整数。
addBack(num)：
    仅当 num < thres 且不在 s 中时，s.insert(num)，保证 s 里只存“放回来的”且比当前阈值小的数字。 */

int main() {
	SmallestInfiniteSet sset;
	sset.addBack(2);
	cout << sset.popSmallest() << endl;
	cout << sset.popSmallest() << endl;
	cout << sset.popSmallest() << endl;
	sset.addBack(1);
	cout << sset.popSmallest() << endl;
	cout << sset.popSmallest() << endl;
	cout << sset.popSmallest() << endl;
}