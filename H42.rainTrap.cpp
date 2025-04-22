#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

/*
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 
*/

class Solution {
public:
	int trap1(vector<int> &height) {
		int water = 0, n = height.size();
		vector<int> left(n), right(n);
		left[0] = height[0];
		right[n - 1] = height[n - 1];
		for(int i = 1; i < n; i++) {
			left[i] = max(left[i - 1], height[i]);
			right[n - 1 - i] = max(right[n - i], height[n - 1 - i]);
		}
		for(int i = 1; i < n - 1; i++) {
			water += max(min(left[i] - height[i], right[i] - height[i]), 0);
		}
		return water;
	}
	int trap2(vector<int> &height) {
		int water = 0, l = 0, r = height.size() - 1, maxL = -1, maxR = -1;
		while(l < r) {
			maxL = max(maxL, height[l]);
			maxR = max(maxR, height[r]);
			if(maxL < maxR) {
				water += maxL - height[l];
				l++;
			} else {
				water += maxR - height[r];
				r--;
			}
		}
		return water;
	}
	int trap3(vector<int> &height) {
		int water = 0, l = 0, r = height.size() - 1, maxL = -1, maxR = -1;
		while(l < r) {
			int level = min(maxL, maxR);
			if(height[l] <= level) {
				water += level - height[l];
				l++;
				continue;
			}
			if(height[r] <= level) {
				water += level - height[r];
				r--;
				continue;
			}
			maxL = max(maxL, height[l]);
			maxR = max(maxR, height[r]);
		}
		return water;
	}
	int trap4(vector<int> &height) {
		int water = 0, l = 0, r = height.size() - 1, maxL = -1, maxR = -1;
		while(l < r) {
			maxL = max(height[l], maxL);
			maxR = max(height[r], maxR);
			// left 单调递增 right 单调递减
			if(height[l] < height[r]) {
				water += maxL - height[l];
				l++;
			} else {
				water += maxR - height[r];
				r--;
			}
		}
		return water;
	}
};

int main() {
	Solution sol;
	vector<int> height1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
	vector<int> height2 = {4, 2, 0, 3, 2, 5};
	vector<int> height3 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
	cout << sol.trap1(height1) << " " << sol.trap2(height1) << " " << sol.trap3(height1) << " " << sol.trap4(height1)
	     << " " << endl;
	cout << sol.trap1(height2) << " " << sol.trap2(height2) << " " << sol.trap3(height2) << " " << sol.trap4(height2)
	     << " " << endl;
	cout << sol.trap1(height1) << " " << sol.trap2(height1) << " " << sol.trap3(height1) << " " << sol.trap4(height1)
	     << " " << endl;
}

/*
1、
两次遍历（一次顺序遍历、一次逆序遍历），分别获得每一个格子的前后信息
每个格子能承载的雨水量为该格子左边的最大值lmax和右边的最大值rmax二者中最小的（短板效应）那一个减去本格的高度
2、
对于某一个位置的格子，其实没必要同时知道左右两侧的最大高度，只需要知道当前格子左侧的最大高度和右侧的最大高度中的较小值即可
因为遍历时左右两侧的最大高度是单调递增的，因此对于l指针，左侧最大高度已定是maxL，但是右侧最大高度大于等于maxR，因此如果maxL小于maxR，那么l指针能承载的雨水量就是maxL
同理对于r指针，右侧最大高度已定是maxR，但是左侧最大高度大于等于maxL，因此如果maxR小于maxL，那么r指针能承载的雨水量就是maxR
这样就可以迭代l和r指针，求出每一个格子的雨水量
*/