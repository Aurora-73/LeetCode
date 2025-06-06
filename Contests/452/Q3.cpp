// Created: 2025-06-06
#include "MyDateGen.h"
#include "MyUtils.hpp"

/*Q3. 清理教室的最少移动
给你一个 m x n 的网格图 classroom，其中一个学生志愿者负责清理散布在教室里的垃圾。网格图中的每个单元格是以下字符之一：
'S' ：学生的起始位置
'L' ：必须收集的垃圾（收集后，该单元格变为空白）
'R' ：重置区域，可以将学生的能量恢复到最大值，无论学生当前的能量是多少（可以多次使用）
'X' ：学生无法通过的障碍物
'.' ：空白空间
同时给你一个整数 energy，表示学生的最大能量容量。学生从起始位置 'S' 开始，带着 energy 的能量出发。
每次移动到相邻的单元格（上、下、左或右）会消耗 1 单位能量。如果能量为 0，学生此时只有处在 'R' 格子时可以继续移动，此区域会将能量恢复到 最大 能量值 energy。
返回收集所有垃圾所需的 最少 移动次数，如果无法完成，返回 -1。
示例 1：
	输入: classroom = ["S.", "XL"], energy = 2
	输出: 2
	解释:
	学生从单元格 (0, 0) 开始，带着 2 单位的能量。
	由于单元格 (1, 0) 有一个障碍物 'X'，学生无法直接向下移动。
	收集所有垃圾的有效移动序列如下：
	移动 1：从 (0, 0) → (0, 1)，消耗 1 单位能量，剩余 1 单位。
	移动 2：从 (0, 1) → (1, 1)，收集垃圾 'L'。
	学生通过 2 次移动收集了所有垃圾。因此，输出为 2。
示例 2：
	输入: classroom = ["LS", "RL"], energy = 4
	输出: 3
	解释:
	学生从单元格 (0, 1) 开始，带着 4 单位的能量。
	收集所有垃圾的有效移动序列如下：
	移动 1：从 (0, 1) → (0, 0)，收集第一个垃圾 'L'，消耗 1 单位能量，剩余 3 单位。
	移动 2：从 (0, 0) → (1, 0)，到达 'R' 重置区域，恢复能量为 4。
	移动 3：从 (1, 0) → (1, 1)，收集第二个垃圾 'L'。
	学生通过 3 次移动收集了所有垃圾。因此，输出是 3。
示例 3：
	输入: classroom = ["L.S", "RXL"], energy = 3
	输出: -1
	解释:
	没有有效路径可以收集所有 'L'。
提示：
1 <= m == classroom.length <= 20
1 <= n == classroom[i].length <= 20
classroom[i][j] 是 'S'、'L'、'R'、'X' 或 '.' 之一
1 <= energy <= 50
网格图中恰好有 一个 'S'。
网格图中 最多 有 10 个 'L' 单元格。*/

class Solution1 {
public:
	int minMoves(vector<string> &classroom, int energy) {
		vn = classroom.size(), sn = classroom[0].size();
		allR = 0, maxEnergy = energy;
		int bi, bj;
		for(int i = 0; i < vn; ++i) {
			for(int j = 0; j < sn; ++j) {
				if(classroom[i][j] == 'L') {
					++allR;
				} else if(classroom[i][j] == 'S') {
					bi = i, bj = j;
				}
			}
		}
		return dfs(classroom, energy, bi, bj, 0);
	}

private:
	int vn, sn, allR, maxEnergy;
	const vector<vector<int>> dirs = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
	int dfs(vector<string> &classroom, int energy, int i, int j, int nowR) {
		if(i < 0 || j < 0 || i >= vn || j >= sn || classroom[i][j] == 'X') {
			return -1;
		}
		if(classroom[i][j] == 'R') {
			energy = maxEnergy;
		}
		if(classroom[i][j] == 'L') {
			++nowR;
		}
		if(nowR == allR) {
			return 0;
		}
		int minStepNow = -1;
		if(energy > 0) {
			char nowC = classroom[i][j];
			classroom[i][j] = '.';
			for(auto &dir : dirs) {
				int a = dfs(classroom, energy - 1, i + dir[0], j + dir[1], nowR);
				if(minStepNow == -1 || (a != -1 && a < minStepNow)) {
					minStepNow = a;
				}
			}
			classroom[i][j] = nowC;
		}
		if(minStepNow != -1) {
			return minStepNow + 1;
		}
		return -1;
	}
}; // 记忆化搜索要保存 classroom 比较麻烦

class Solution {
public:
	int minMoves(vector<string> &classroom, int energy) {
		int m = classroom.size(), n = classroom[0].size();
		vector<pair<int, int>> garbage;
		int si, sj;
		// 记录每个垃圾的编号
		vector<vector<int>> lid(m, vector<int>(n, -1));
		int lid_cnt = 0;
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(classroom[i][j] == 'L') {
					lid[i][j] = lid_cnt++;
					garbage.emplace_back(i, j);
				} else if(classroom[i][j] == 'S') {
					si = i, sj = j;
				}
			}
		}
		if(lid_cnt == 0) return 0;
		int all_mask = (1 << lid_cnt) - 1;
		using State = tuple<int, int, int, int>;
		queue<State> q;
		vector<vector<vector<vector<bool>>>> visited(m,
		    vector<vector<vector<bool>>>(
		        n, vector<vector<bool>>(energy + 1, vector<bool>(1 << lid_cnt, false))));
		q.emplace(si, sj, energy, 0);
		visited[si][sj][energy][0] = true;
		int step = 0;
		vector<pair<int, int>> dirs = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
		while(!q.empty()) {
			int sz = q.size();
			while(sz--) {
				auto [i, j, e, mask] = q.front();
				q.pop();
				// 收集垃圾
				if(lid[i][j] != -1) {
					mask |= (1 << lid[i][j]);
					if(mask == all_mask) return step;
				}
				// 恢复能量
				if(classroom[i][j] == 'R') e = energy;
				if(e == 0 && classroom[i][j] != 'R') continue;
				for(auto &d : dirs) {
					int ni = i + d.first, nj = j + d.second;
					int ne = e - 1;
					if(ni < 0 || nj < 0 || ni >= m || nj >= n) continue;
					if(classroom[ni][nj] == 'X') continue;
					if(ne < 0 && classroom[ni][nj] != 'R') continue;
					int ne2 = ne;
					if(classroom[ni][nj] == 'R') ne2 = energy;
					if(!visited[ni][nj][ne2][mask]) {
						visited[ni][nj][ne2][mask] = true;
						q.emplace(ni, nj, ne2, mask);
					}
				}
			}
			++step;
		}
		return -1;
	}
};

int main() {
	Solution sol;
	vector<string> classroom;
	int energy;
	classroom = { "L.S", "RXL" }, energy = 3;
	cout << sol.minMoves(classroom, energy) << endl;
	// 输出: -1
	classroom = { "LS", "RL" }, energy = 4;
	cout << sol.minMoves(classroom, energy) << endl;
	// 输出: 3
	classroom = { "S.", "XL" }, energy = 2;
	cout << sol.minMoves(classroom, energy) << endl;
	// 输出: 2
}