// Created: 2025-05-11
#include "MyUtils.h"

/*212. 单词搜索 II
给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words， 返回所有二维网格上的单词 。
单词必须按照字母顺序，通过 相邻的单元格 内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母在一个单词中不允许被重复使用。*/

struct TrieNode {
	int IsEnd = -1;
	unique_ptr<TrieNode> children[26] { nullptr };
};

class Solution1 {
public:
	vector<string> findWords(vector<vector<char>> &board, vector<string> &words) {
		for(int i = 0; i < words.size(); i++) {
			insert(words[i], i);
		}
		m = board.size();
		n = m ? board[0].size() : 0;
		words_ptr = &words;
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(!root.children[board[i][j] - 'a'])
					continue;
				// vector<vector<char>> now = board;
				// 在这里拷贝board只能防止不同起点的路线之间相互影响，
				// 需要回溯还原防止同一个原点出发的不同分支之间相互影响
				dfs(board, i, j, &root);
			}
			if(res.size() == words.size()) {
				return res;
			} // 提前结束
		}
		return res;
	}

private:
	int m, n;
	TrieNode root;
	vector<string> res;
	vector<string> *words_ptr;
	int dirs[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
	// unordered_set<int> res_index; 由于可能存在重复的因此需要用set去重，但是将root->IsEnd置为-1也有同样的效果

	void insert(const string &s, int i) {
		TrieNode *now = &root;
		for(auto c : s) {
			if(!now->children[c - 'a']) {
				now->children[c - 'a'] = make_unique<TrieNode>();
			}
			now = now->children[c - 'a'].get();
		}
		now->IsEnd = i;
	}

	void dfs(vector<vector<char>> &board, int i, int j, TrieNode *root) {
		if(i < 0 || j < 0 || i >= m || j >= n || !root || board[i][j] == '#') {
			return;
		}
		root = root->children[board[i][j] - 'a'].get();
		if(!root)
			return;
		if(root->IsEnd != -1) {
			res.push_back((*words_ptr)[root->IsEnd]);
			root->IsEnd = -1; // 防止重复访问
		}
		char temp = board[i][j];
		board[i][j] = '#';

		for(auto &dir : dirs) {
			dfs(board, i + dir[0], j + dir[1], root);
		}
		// —— 回溯还原 ——
		board[i][j] = temp; // 防止同一个原点出发的不同分支之间相互影响
	}
};

class Solution2 {
public:
	vector<string> findWords(vector<vector<char>> &board, vector<string> &words) {
		// 1. 初始化 Trie 容器
		wordsPtr = &words;
		int total = words.size();
		// 预估空间
		int est = 1;
		for(auto &w : words)
			est += w.size();
		tree.clear();
		pass.clear();
		wordIndex.clear();
		tree.reserve(est);
		pass.reserve(est);
		wordIndex.reserve(est);
		// root 节点编号 0
		tree.emplace_back(); // tree[0], 全部默认 0
		pass.emplace_back(0); // pass[0] = 0
		wordIndex.emplace_back(-1); // wordIndex[0] = -1

		// 2. 插入所有单词
		for(int i = 0; i < total; ++i) {
			insert(words[i], i);
		}

		// 3. 在 board 上 DFS 搜索
		m = board.size();
		n = m ? board[0].size() : 0;
		res.clear();
		res.reserve(total);

		for(int i = 0; i < m && res.size() < total; ++i) {
			for(int j = 0; j < n && res.size() < total; ++j) {
				dfs(board, 0, i, j);
			}
		}
		return std::move(res);
	}

private:
	// Trie 存储
	vector<array<int, 26>> tree; // 树的保存结构，用int表示下标，由于0号是根节点，不应该被指向，所以默认值0即为空
	vector<int> pass; // 有多少个单词经过过第i个节点
	vector<int> wordIndex; // 标记第i个树是谁的叶子结点，如果都不是则为-1
	vector<string> *wordsPtr;
	vector<string> res;

	int m, n;
	// 四个方向
	static constexpr int dirs[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

	// 插入单词到 Trie，同时更新 pass 计数
	void insert(const string &s, int idx) {
		int u = 0;
		pass[u]++; // root 也算一个前缀
		for(char ch : s) {
			int c = ch - 'a';
			if(tree[u][c] == 0) {
				// 新建一个节点
				tree[u][c] = tree.size();
				tree.emplace_back(); // new node, 默认全 0
				pass.emplace_back(0);
				wordIndex.emplace_back(-1);
			}
			u = tree[u][c];
			pass[u]++;
		}
		// 终点存下标
		wordIndex[u] = idx;
	}

	// 从 board[x][y]、Trie 节点 u 开始 DFS
	// 返回本次调用找到的单词数（用于剪枝更新 pass）
	int dfs(vector<vector<char>> &B, int u, int x, int y) {
		// 越界、已访问、Trie 无此分支、或前缀已无剩余单词 → 剪枝
		if(x < 0 || x >= m || y < 0 || y >= n)
			return 0;
		char ch = B[x][y];
		if(ch == '#')
			return 0;
		int v = tree[u][ch - 'a'];
		if(v == 0 || pass[v] == 0)
			return 0;

		int found = 0;
		// advance 到 v
		u = v;
		// 如果是单词终点
		int widx = wordIndex[u];
		if(widx != -1) {
			res.push_back(std::move((*wordsPtr)[widx]));
			wordIndex[u] = -1; // 去重
			found = 1;
		}

		// 标记访问
		B[x][y] = '#';
		// 四方向递归
		for(auto &d : dirs) {
			found += dfs(B, u, x + d[0], y + d[1]);
		}
		// 回溯还原
		B[x][y] = ch;

		// 用完后更新 pass，后续路径能及时剪枝
		pass[u] -= found;
		return found;
	}
};

int main() {
	Solution1 sol1;
}