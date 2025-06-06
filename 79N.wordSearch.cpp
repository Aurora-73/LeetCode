// Created: 2025-05-12
#include "MyUtils.hpp"

/*79. 单词搜索
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。*/

class Solution1 {
public:
	bool exist(vector<vector<char>> &board, string &word) {
		m = board.size();
		n = board[0].size();
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(board[i][j] == word[deepth]) {
					dfs(board, word, i, j);
					if(find) {
						return true;
					}
				}
			}
		}
		return find;
	}

private:
	int m, n, deepth = 0, dirs[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }, find = 0;
	void dfs(vector<vector<char>> &board, string &word, int i, int j) {
		if(find || i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[deepth]) {
			return;
		}
		++deepth;
		char temp = board[i][j];
		board[i][j] = '#';
		if(word.size() == deepth) {
			find = 1;
			return;
		}
		for(auto dir : dirs) {
			int a = i + dir[0], b = j + dir[1];
			if(a >= 0 && a < m && b >= 0 && b < n && board[a][b] == word[deepth]) {
				dfs(board, word, a, b);
				if(find) {
					return;
				}
			}
		}
		--deepth;
		board[i][j] = temp;
	}
};

class Solution2 {
public:
	bool exist(vector<vector<char>> &board, const string &word) {
		int rows = board.size();
		if(rows == 0) return false;
		int cols = board[0].size();

		// 对每一个起点尝试一次 DFS
		for(int i = 0; i < rows; ++i) {
			for(int j = 0; j < cols; ++j) {
				if(board[i][j] == word[0] && dfs(board, word, i, j, 0)) return true;
			}
		}
		return false;
	}

private:
	// 四个方向：右、左、下、上
	const int dx[4] = { 0, 0, 1, -1 };
	const int dy[4] = { 1, -1, 0, 0 };

	// 从(board[i][j])开始，尝试匹配 word[idx...end]
	bool dfs(vector<vector<char>> &board, const string &word, int i, int j, int idx) {
		// 全部字符都匹配完，返回 true
		if(idx == word.size() - 1) return true;

		// 暂记并标记为已访问
		char saved = board[i][j];
		board[i][j] = '#';

		// 下一个字符索引
		int next = idx + 1;
		bool found = false;

		// 四个方向搜索
		for(int d = 0; d < 4; ++d) {
			int ni = i + dx[d], nj = j + dy[d];
			if(ni >= 0 && ni < board.size() && nj >= 0 && nj < board[0].size()
			    && board[ni][nj] == word[next]) {
				if(dfs(board, word, ni, nj, next)) {
					found = true;
					break;
				}
			}
		}

		// 恢复现场
		board[i][j] = saved;
		return found;
	}
};

class Solution {
public:
	vector<vector<vector<bool>>> dp;
	vector<vector<bool>> myhash;
	bool pass(int row, int col, int len) {
		if(!dp[row][col][len] || myhash[row][col]) return 0;
		if(len == 1) return 1;
		myhash[row][col] = 1;
		if(pass(row - 1, col, len - 1) || pass(row, col - 1, len - 1) || pass(row + 1, col, len - 1)
		    || pass(row, col + 1, len - 1))
			return 1;
		myhash[row][col] = 0;
		return 0;
	}
	bool exist(vector<vector<char>> &board, string word) {
		int m = board.size(), n = board[0].size(), len = word.size();
		dp.resize(m + 2, vector<vector<bool>>(n + 2, vector<bool>(len + 1, 0)));
		myhash.resize(m + 2, vector<bool>(n + 2, 0));
		for(int i = 0; i <= m + 1; i++) {
			for(int j = 0; j <= n + 1; j++) {
				dp[i][j][0] = 1;
			}
		}
		for(int k = 1; k <= len; k++) {
			for(int i = 1; i <= m; i++) {
				for(int j = 1; j <= n; j++) {
					dp[i][j][k] = (board[i - 1][j - 1] == word[k - 1]
					    && (dp[i - 1][j][k - 1] || dp[i][j - 1][k - 1] || dp[i + 1][j][k - 1]
					        || dp[i][j + 1][k - 1]));
				}
			}
		}
		vector<int> alterrow;
		vector<int> altercol;
		for(int i = 1; i <= m; i++) {
			for(int j = 1; j <= n; j++) {
				if(dp[i][j][len]) {
					alterrow.emplace_back(i);
					altercol.emplace_back(j);
				}
			}
		}
		int anslen = alterrow.size();
		for(int i = 0; i < anslen; i++) {
			if(pass(alterrow[i], altercol[i], len)) return 1;
		}
		return 0;
	}
}; // 动态规划
/* 二维字符串匹配，做多了正则表达式匹配，字符串子串匹配这种题，我脑子里第一想法就是dp。
显然给定二维字符串加上待匹配的字符串需要创建一个三维dp向量来存储答案。设dp[i][j][k]为以board[i][j]结束的字符串能否匹配word里的前i个字符。
显然board[i][j]的前一个字符只能是上下左右四个方向来的字符，即board[i-1][j]，board[i+1][j]，board[i][j-1]，board[i][j+1]，
所以如果以当前字符的上下左右任何一个字符结尾的字符串能匹配word的前i-1个字符且当前字符等于word的第i个字符那么dp[i][j][k]=1；
因此，状态转移方程为：
dp[i][j][k]=(board[i-1][j-1]==word[k-1]&&(dp[i-1][j][k-1]||dp[i][j-1][k-1]||dp[i+1][j][k-1]||dp[i][j+1][k-1]));
初始dp全设为0，因为当k=0也就是待匹配字符串为空串的时候任何位置都可以匹配，所以将dp[i][j][0]全设为1即可。然后从低层到高层从左到右从上到下依次更新dp即可。
因为判断board边缘的字符的上下左右的时候会越界，所以dp的大小设为(m+2) *(n+2) *(len+1)。
但是还没结束，因为题中要求同一位置的字符不能重复使用，所以还需要递归检验，遍历dp[i][j][len]，将值为1的dp的行和列存入alterrow和altercol中作为待选答案，
现在只需遍历待选答案看能否找到没有使用同一个位置的字符两次的答案即可。设置一个检验函数pass(int row,int col,int len)，len表示还需匹配的字符串长度。
每次检验当前位置的dp是否为1且当前字符是否已使用，如果dp为0或者字符已经用过则返回0；不然则递归检验上下左右的字符并将长度更新为上一层的检验长度-1，
len减到1就说明字符串已经检验完毕了。这样遍历检验alter答案，如果有一个满足最终答案要求则返回true，都不满足要求则返回false。*/

int main() {
	Solution1 sol1;
	vector<vector<char>> board;
	board = { { 'A', 'B', 'C', 'E' }, { 'S', 'F', 'C', 'S' }, { 'A', 'D', 'E', 'E' } };
	string word = "ABCCED";
	cout << sol1.exist(board, word) << endl;
	Solution2 sol2;
	cout << sol2.exist(board, word) << endl;
}