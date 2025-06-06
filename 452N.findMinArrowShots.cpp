#include "MyUtils.hpp"

/*452. 用最少数量的箭引爆气球
有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 points
， 其中points[i] = [xstart, xend] 表示水平直径在 xstart 和
xend之间的气球。你不知道气球的确切 y 坐标。 一支弓箭可以沿着 x 轴从不同点
完全垂直 地射出。在坐标 x 处射出一支箭， 若有一个气球的直径的开始和结束坐标为
xstart，xend， 且满足  xstart ≤ x ≤ xend，则该气球会被 引爆
。可以射出的弓箭的数量没有限制 。 弓箭一旦被射出之后，可以无限地前进。
给你一个数组 points ，返回引爆所有气球所必须射出的 最小 弓箭数 。*/

class Solution {
public:
	int findMinArrowShots(vector<vector<int>> &points) {
		if(points.size() == 0) return 0;
		sort(points.begin(), points.end(), [](vector<int> &a, vector<int> &b) {
			return a[0] < b[0];
		});
		int count = 1, i = 1, right = points[0][1]; //left = points[0][0],
		while(i < points.size()) {
			if(points[i][0] > right) {
				count++;
				// left = points[i][0];
				right = points[i][1];
			} else {
				// left = max(points[i][0], left);
				right = min(points[i][1], right);
			}
			i++;
		}
		return count;
	}
};

// 本质是求并集，从左往右，没有并集就把count++，与区间合并代码类似
