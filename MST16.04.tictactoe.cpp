// Created: 2026-01-01
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 设计一个算法，判断玩家是否赢了井字游戏。
输入是一个 N x N 的数组棋盘，由字符" "，"X"和"O"组成，其中字符" "代表一个空位。
以下是井字游戏的规则：
	玩家轮流将字符放入空位（" "）中。
	第一个玩家总是放字符"O"，且第二个玩家总是放字符"X"。
	"X"和"O"只允许放置在空位中，不允许对已放有字符的位置进行填充。
	当有N个相同（且非空）的字符填充任何行、列或对角线时，游戏结束，对应该字符的玩家获胜。
	当所有位置非空时，也算为游戏结束。
	如果游戏结束，玩家不允许再放置字符。
如果游戏存在获胜者，就返回该游戏的获胜者使用的字符（"X"或"O"）；
如果游戏以平局结束，则返回 "Draw"；
如果仍会有行动（游戏未结束），则返回 "Pending"。
示例 1：
	输入： board = {"O X"," XO","X O"}
	输出： "X"
示例 2：
	输入： board = {"OOX","XXO","OXO"}
	输出： "Draw"
	解释： 没有玩家获胜且不存在空位
示例 3：
	输入： board = {"OOX","XXO","OX "}
	输出： "Pending"
	解释： 没有玩家获胜且仍存在空位
提示：
	1 <= board.length == board{i}.length <= 100
	输入一定遵循井字棋规则 */

class Solution {
public:
	string tictactoe(vector<string> &board) {
		bool block = false, diag1 = true, diag2 = true;
		int n = board.size();
		for(int i = 0; i < n; ++i) {
			bool line = true;
			for(int j = 0; j < n; ++j) {
				if(board[i][j] == ' ') {
					block = true;
					line = false;
					break;
				}
				if(board[i][j] != board[i][0]) line = false;
			}
			if(line) return { board[i][0] };
		} // 行，顺带检查有无空
		for(int i = 0; i < n; ++i) {
			int j;
			for(j = 1; j < n; ++j) {
				if(board[j][i] == ' ') {
					block = true;
					break;
				}
				if(board[j][i] != board[0][i]) break;
			}
			if(j == n) return { board[0][i] };
		} // 列
		for(int i = 0; i < n; ++i) {
			if(board[0][0] == ' ' || board[i][i] != board[0][0]) diag1 = 0;
			if(board[0][n - 1] == ' ' || board[i][n - i - 1] != board[0][n - 1]) diag2 = 0;
		} // 主副对角线
		if(diag1) return { board[0][0] };
		if(diag2) return { board[0][n - 1] };
		return block ? "Pending" : "Draw";
	}
};

int main() {
	Solution sol;
	vector<string> board;
	board = { "O X", " XO", "X O" };
	cout << sol.tictactoe(board) << endl;

	board = { "OOX", "XXO", "OXO" };
	cout << sol.tictactoe(board) << endl;

	board = { "OOX", "XXO", "OX " };
	cout << sol.tictactoe(board) << endl;
}