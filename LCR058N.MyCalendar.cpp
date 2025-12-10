// Created: 2025-12-10
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 请实现一个 MyCalendar 类来存放你的日程安排。
如果要添加的时间内没有其他安排，则可以存储这个新的日程安排。
MyCalendar 有一个 book(int start, int end)方法。它意味着在 start 到 end 时间内增加一个日程安排，
注意，这里的时间是半开区间，即 {start, end), 实数x 的范围为， start <= x < end。
当两个日程安排有一些时间上的交叉时（例如两个日程安排都在同一时间内），就会产生重复预订。
每次调用 MyCalendar.book方法时，如果可以将日程安排成功添加到日历中而不会导致重复预订，
返回 true。否则，返回 false并且不要将该日程安排添加到日历中。
请按照以下步骤调用 MyCalendar 类: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)
示例 1：
	输入:
	{"MyCalendar","book","book","book"}
	{{},{10,20},{15,25},{20,30}}
	输出: {null,true,false,true}
	解释: 
	MyCalendar myCalendar = new MyCalendar();
	MyCalendar.book(10, 20); // returns true 
	MyCalendar.book(15, 25); // returns false，
	第二个日程安排不能添加到日历中，因为时间 15 已经被第一个日程安排预定了
	MyCalendar.book(20, 30); // returns true，
	第三个日程安排可以添加到日历中，因为第一个日程安排并不包含时间 20 
提示：
	每个测试用例，调用MyCalendar.book函数最多不超过1000次。
	0 <= start < end <= 10^9 */

class MyCalendar1 {
public:
	MyCalendar1() { }

	bool book(int start, int end) {
		pair<int, int> now { start, end };
		// 找第一个first >= start的元素，也就是第一个开始晚于该元素的元素
		auto it = calendar.lower_bound(now);
		// 情况2：下一个日程在end之前就开始 -> 冲突
		if(it != calendar.end() && it->first < end) {
			return false;
		}
		// 情况1：上一个日程在start之后还没结束 -> 冲突
		if(it != calendar.begin() && prev(it)->second > start) {
			return false;
		}
		calendar.insert(now);
		return true;
	}

private:
	set<pair<int, int>> calendar;
}; // 冲突的两种情况：1、该日程开始时上一个日程还没结束 2、该日程还没结束，下一个日程就开始了

class MyCalendar {
public:
	bool book(int start, int end) {
		// 寻找如果能成功插入时，插入位置后一个元素，该元素一定不冲突，且插入成功之后就在新插入元素之后
		auto it = booked.lower_bound({ end, 0 });
		// 仅需要判断it的前一个元素是否冲突，如果不冲突，将新元素插入在两者之间即可
		if(it == booked.begin() || (--it)->second <= start) {
			booked.emplace(start, end);
			return true;
		}
		return false;
	}

private:
	set<pair<int, int>> booked;
};

int main() {
	MyCalendar1 mc;
	cout << boolalpha << mc.book(10, 20) << endl;
	cout << boolalpha << mc.book(15, 25) << endl;
	cout << boolalpha << mc.book(20, 30) << endl;
}