#include <iostream>
#include <vector>

using namespace std;

/*
给你一个正整数 n ，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。
输入：n = 3   输出：[[1,2,3],[8,9,4],[7,6,5]]
 */
class Solution {
public:
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int>> vec(n, vector<int>(n, -1));
		int num = 1, i = 0, j = 0, step = n - 1, step_now = 0, reduce = 3;
		bool right = true, down = true, move_j = true;
		vec[0][0] = num++;
		while(step > 0) { // or (num <= n*n)
			if(move_j) {
				if(step_now < step) {
					if(right) {
						++j;
						++step_now;
					} else {
						--j;
						++step_now;
					}
					vec[i][j] = num++;
				} else {
					move_j = false;
					step_now = 0;
					right = !right;
					reduce--;
					if(reduce == 0) {
						step--;
						reduce = 2;
					}
				}
			} else {
				if(step_now < step) {
					if(down) {
						++i;
						++step_now;
					} else {
						--i;
						++step_now;
					}
					vec[i][j] = num++;
				} else {
					move_j = true;
					step_now = 0;
					down = !down;
					reduce--;
					if(reduce == 0) {
						step--;
						reduce = 2;
					}
				}
			}
		}
		return vec;
	}
};
/*重点：
1、每次移动之后再赋值，则最初需要先给(0,0)赋值，
2、可以在纸上模拟，移动次数依次为
    n-1、n-1、n-1、n-2、n-2、n-3、n-3....(除了第一个之外均为重复两次)
3、设置一个当前方向的需要移动步数，和已经移动步数，每两次切换移动方向让需要移动步数减一，第一次需要额外且切换一次
4、使用movej表示当前移动的是i还是j、使用right和down表示当前的移动方向
5、记录当前方向的移动次数，当移动步数达到目标移动步数后切换移动方向
易错点：
1、左右移动变化的时 j，上下移动变化的才是 i，并且向下移动 i 增加而不是减少
2、当前方向的需要移动步数的变化
*/

int main() {
	Solution sol;
	int n;
	cin >> n;
	auto res = sol.generateMatrix(n);
	for(auto vec : res) {
		for(auto i : vec) {
			cout << i << " ";
		}
		cout << endl;
	}
	return 0;
}