#include "MyUtils.h"

class Solution {
public:
	void gameOfLife(vector<vector<int>> &board) {
		int n = board.size(), m = board[0].size();
		auto alive = [&](int x, int y) {
			if(x < 0 || x >= n) {
				return false;
			}
			if(y < 0 || y >= m) {
				return false;
			}
			return abs(board[x][y]) == 1;
		};
		auto get_near = [&](int x, int y) {
			return alive(x - 1, y - 1) + alive(x - 1, y) + alive(x - 1, y + 1) + alive(x, y - 1) + alive(x, y + 1) +
			       alive(x + 1, y - 1) + alive(x + 1, y) + alive(x + 1, y + 1);
		};
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				int get_ed = get_near(i, j), &now = board[i][j];
				if(get_ed < 2) {
					now = now ? -1 : 0;
				} else if(get_ed == 3) {
					now = now ? 1 : 2;
				} else if(get_ed > 3) {
					now = now ? -1 : 0;
				}
			}
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				int &now = board[i][j];
				if(now == -1)
					now = 0;
				if(now == 2)
					now = 1;
			}
		}
	}
};
// -1 代表现在没死，将来会死
// 2 代表现在没活 将来会活

class Solution {
public:
	void gameOfLife(vector<vector<int>> &board) {
		int n = board.size(), m = board[0].size();
		vector<int> dir = {-1, 0, 1};
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				int cnt = 0, &now = board[i][j];
				for(int di : dir) {
					for(int dj : dir) {
						if(di == 0 && dj == 0)
							continue;
						int a = i + di, b = j + dj;
						if(a > -1 && a < n && b > -1 && b < m && (board[a][b] & 1))
							cnt++;
					}
				}
				if((now && cnt == 2) || cnt == 3) {
					now |= 2;
				}
			}
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				board[i][j] >>= 1;
			}
		}
	}
};
// 1、用{-1 , 0 , 1}控制位移
// 2、用二进制最低位表示当前的死活，第二位表示下一轮的死活

int main() {
	Solution sol;
	vector<vector<int>> board = {{0, 1, 0}, {0, 0, 1}, {1, 1, 1}, {0, 0, 0}};
	sol.gameOfLife(board);
	cout << board;
}