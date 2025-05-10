// Created: 2025-05-08
#include "MyUtils.h"

/*909. 蛇梯棋
给你一个大小为 n x n 的整数矩阵 board ，方格按从 1 到 n2 编号，编号遵循 转行交替方式 ，从左下角开始 （即，从 board[n - 1][0] 开始）的每一行改变方向。
你一开始位于棋盘上的方格  1。每一回合，玩家需要从当前方格 curr 开始出发，按下述要求前进：
选定目标方格 next ，目标方格的编号在范围 [curr + 1, min(curr + 6, n2)] 。
该选择模拟了掷 六面体骰子 的情景，无论棋盘大小如何，玩家最多只能有 6 个目的地。
传送玩家：如果目标方格 next 处存在蛇或梯子，那么玩家会传送到蛇或梯子的目的地。否则，玩家传送到目标方格 next 。 
当玩家到达编号 n2 的方格时，游戏结束。
如果 board[r][c] != -1 ，位于 r 行 c 列的棋盘格中可能存在 “蛇” 或 “梯子”。那个蛇或梯子的目的地将会是 board[r][c]。编号为 1 和 n2 的方格不是任何蛇或梯子的起点。
注意，玩家在每次掷骰的前进过程中最多只能爬过蛇或梯子一次：就算目的地是另一条蛇或梯子的起点，玩家也 不能 继续移动。
举个例子，假设棋盘是 [[-1,4],[-1,3]] ，第一次移动，玩家的目标方格是 2 。那么这个玩家将会顺着梯子到达方格 3 ，但 不能 顺着方格 3 上的梯子前往方格 4 。
（简单来说，类似飞行棋，玩家掷出骰子点数后移动对应格数，遇到单向的路径（即梯子或蛇）可以直接跳到路径的终点，但如果多个路径首尾相连，也不能连续跳多个路径）
返回达到编号为 n2 的方格所需的最少掷骰次数，如果不可能，则返回 -1。*/

class Solution1 {
public:
	int snakesAndLadders(vector<vector<int>> &board) {
		int now = 1, n = board.size(), step = -1;
		vector<bool> visited(
		    n * n + 1, false); // 只需要考虑第一次遇到格子的步数，因为这个一定是最短的，从而进行剪枝，否则超时
		visited[now] = true;
		queue<int> pos;
		pos.push(now);
		auto now2board = [&](int now) {
			int r = (now - 1) / n, c = (now - 1) % n;
			if(r % 2 == 1) {
				c = n - 1 - c;
			}
			r = n - 1 - r;
			return board[r][c];
		};
		while(!pos.empty()) {
			size_t size = pos.size();
			++step;
			for(int i = 0; i < size; ++i) {
				now = pos.front();
				if(now == n * n) {
					return step;
				}
				pos.pop();
				for(int j = 1; j < 7; ++j) {
					int next = now + j;
					if(next > n * n) {
						continue;
					}
					if(now2board(next) != -1) {
						next = now2board(next); // 必须进行跳跃，不能不跳跃
					}
					if(!visited[next]) {
						visited[next] = true; // 剪枝要在入栈的时候进行，访问的时候进行可能已经多次入栈
						pos.push(next);
					}
				}
			}
		}
		return -1;
	}
};

class Solution2 {
public:
	int snakesAndLadders(vector<vector<int>> &board) {
		int n = board.size();
		unordered_map<int, int> jump; // 记录蛇和梯子的起止位置

		// 构建从编号到编号的跳跃关系
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if(board[i][j] != -1) {
					int r = n - 1 - i; // 编号的行号
					int k = (r % 2 == 0) ? j : n - 1 - j; // 根据行号奇偶性转换列
					int s = r * n + k + 1;
					jump[s] = board[i][j];
				}
			}
		}

		queue<int> q;
		vector<bool> visited(n * n + 1, false);
		q.push(1);
		visited[1] = true;
		int steps = -1;

		while(!q.empty()) {
			int size = q.size();
			++steps;
			for(int i = 0; i < size; ++i) {
				int curr = q.front();
				q.pop();
				// 如果到达终点，直接返回步数
				if(curr == n * n)
					return steps;
				for(int dice = 1; dice <= 6; ++dice) {
					int next = curr + dice;
					if(next > n * n)
						continue;
					if(jump.count(next)) {
						next = jump[next]; // 如果有蛇或梯子，跳到对应位置
					}
					if(!visited[next]) {
						visited[next] = true; // 剪枝：避免重复状态
						q.push(next);
					}
				}
			}
		}

		return -1; // 无法到达终点
	}
};

int main() {
	Solution1 sol1;
	Solution2 sol2;
	vector<vector<int>> board;
	board = { { -1, -1, 19, 10, -1 },
		{ 2, -1, -1, 6, -1 },
		{ -1, 17, -1, 19, -1 },
		{ 25, -1, 20, -1, -1 },
		{ -1, -1, -1, -1, 15 } };
	cout << sol1.snakesAndLadders(board) << endl;
	cout << sol2.snakesAndLadders(board) << endl;
}