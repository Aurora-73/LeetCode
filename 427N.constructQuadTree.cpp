// Created: 2025-05-13
#include "MyUtils.hpp"

/* 427. 建立四叉树
给你一个 n * n 矩阵 grid，矩阵由若干 0 和 1 组成。请你用四叉树表示该矩阵 grid。
你需要返回能表示矩阵 grid 的 四叉树 的根结点。
四叉树数据结构中，每个内部节点只有四个子节点。此外，每个节点都有两个属性：
val：储存叶子结点所代表的区域的值。1 对应 True，0 对应 False。注意，
当 isLeaf 为 False 时，你可以把 True 或者 False 赋值给节点，两种值都会被判题机制 接受。
isLeaf: 当这个节点是一个叶子结点时为 True，如果它有 4 个子节点则为 False。
class Node {
    public boolean val;
    public boolean isLeaf;
    public Node topLeft;
    public Node topRight;
    public Node bottomLeft;
    public Node bottomRight;
}
我们可以按以下步骤为二维区域构建四叉树：
如果当前网格的值相同（即，全为 0 或者全为 1），将 isLeaf 设为 True，
将 val 设为网格相应的值，并将四个子节点都设为 Null 然后停止。
如果当前网格的值不同，将 isLeaf 设为 False， 将 val 设为任意值，然后如下图所示，将当前网格划分为四个子网格。
使用适当的子网格递归每个子节点。
如果你想了解更多关于四叉树的内容，可以参考 百科。
四叉树格式：
你不需要阅读本节来解决这个问题。只有当你想了解输出格式时才会这样做。
输出为使用层序遍历后四叉树的序列化形式，其中 null 表示路径终止符，其下面不存在节点。
它与二叉树的序列化非常相似。唯一的区别是节点以列表形式表示 {isLeaf, val}。
如果 isLeaf 或者 val 的值为 True，
则表示它在列表 {isLeaf, val} 中的值为 1 ；如果 isLeaf 或者 val 的值为 False，则表示值为 0。
示例 1：
	输入：grid = {{0,1},{1,0}}
	输出：{{0,1},{1,0},{1,1},{1,1},{1,0}}
	解释：此示例的解释如下：
	请注意，在下面四叉树的图示中，0 表示 false，1 表示 True。
示例 2：
	输入：grid = {{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,0}}
	输出：{{0,1},{1,1},{0,1},{1,1},{1,0},null,null,null,null,{1,0},{1,0},{1,1},{1,1}}
	解释：网格中的所有值都不相同。我们将网格划分为四个子网格。
	topLeft，bottomLeft 和 bottomRight 均具有相同的值。
	topRight 具有不同的值，因此我们将其再分为 4 个子网格，这样每个子网格都具有相同的值。
	解释如下图所示：
提示：
	n == grid.length == grid{i}.length
	n == 2x 其中 0 <= x <= 6 */

// Definition for a QuadTree node.
class Node {
public:
	bool val;
	bool isLeaf;
	Node *topLeft;
	Node *topRight;
	Node *bottomLeft;
	Node *bottomRight;

	Node() {
		val = false;
		isLeaf = false;
		topLeft = NULL;
		topRight = NULL;
		bottomLeft = NULL;
		bottomRight = NULL;
	}

	Node(bool _val, bool _isLeaf) {
		val = _val;
		isLeaf = _isLeaf;
		topLeft = NULL;
		topRight = NULL;
		bottomLeft = NULL;
		bottomRight = NULL;
	}

	Node(bool _val,
	    bool _isLeaf,
	    Node *_topLeft,
	    Node *_topRight,
	    Node *_bottomLeft,
	    Node *_bottomRight) {
		val = _val;
		isLeaf = _isLeaf;
		topLeft = _topLeft;
		topRight = _topRight;
		bottomLeft = _bottomLeft;
		bottomRight = _bottomRight;
	}
};

class Solution1 {
public:
	Node *construct(vector<vector<int>> &grid) {
		size_t xh = grid.size(), yh = xh;
		return divide(grid, 0, xh, 0, yh);
	}
	Node *divide(vector<vector<int>> &grid, size_t xl, size_t xh, size_t yl, size_t yh) {
		if(xl + 1 == xh) {
			return new Node(grid[xl][yl], true);
		}
		size_t mid_x = (xl + xh) / 2, mid_y = (yl + yh) / 2;
		Node *_topLeft = divide(grid, xl, mid_x, yl, mid_y);     // _topLeft
		Node *_topRight = divide(grid, xl, mid_x, mid_y, yh);    // _topRight
		Node *_bottomLeft = divide(grid, mid_x, xh, yl, mid_y);  // _bottomLeft
		Node *_bottomRight = divide(grid, mid_x, xh, mid_y, yh); // _bottomRight
		// 注意横向的是y，纵向的是x，或者说不要用xy了
		if(!_topLeft->isLeaf || !_topRight->isLeaf || !_bottomLeft->isLeaf
		    || !_bottomRight->isLeaf) {
			return new Node(1, false, _topLeft, _topRight, _bottomLeft, _bottomRight);
		}
		if((_topLeft->val != _topRight->val) || (_bottomLeft->val != _bottomRight->val)
		    || (_topLeft->val != _bottomRight->val)) {
			return new Node(1, false, _topLeft, _topRight, _bottomLeft, _bottomRight);
		}
		Node *root = new Node(_topLeft->val, true);
		delete _topLeft;
		delete _topRight;
		delete _bottomLeft;
		delete _bottomRight;
		return root;
	}
};

class Solution2 {
public:
	Node *construct(vector<vector<int>> &grid) {
		int n = grid.size();
		return divide(grid, 0, n, 0, n);
	}

private:
	// 构造 [rowStart, rowEnd) × [colStart, colEnd) 区域的四叉树
	Node *divide(vector<vector<int>> &grid, int rowStart, int rowEnd, int colStart, int colEnd) {
		// 只有一个元素时直接返回叶子
		if(rowStart + 1 == rowEnd) {
			return new Node(grid[rowStart][colStart] == 1, true);
		}
		// 判断当前区域是否都相同
		bool same = true, val = grid[rowStart][colStart];
		for(int r = rowStart; r < rowEnd && same; ++r) {
			for(int c = colStart; c < colEnd && same; ++c) {
				if(grid[r][c] != val) {
					same = false;
				}
			}
		}
		if(same) {
			return new Node(val == 1, true);
		}
		// 否则继续四分
		int rowMid = (rowStart + rowEnd) / 2;
		int colMid = (colStart + colEnd) / 2;
		Node *topLeft = divide(grid, rowStart, rowMid, colStart, colMid);
		Node *topRight = divide(grid, rowStart, rowMid, colMid, colEnd);
		Node *bottomLeft = divide(grid, rowMid, rowEnd, colStart, colMid);
		Node *bottomRight = divide(grid, rowMid, rowEnd, colMid, colEnd);
		// 构造内部节点（val 值随意，判题不检查）
		return new Node(true, false, topLeft, topRight, bottomLeft, bottomRight);
	}
};
/*矩阵里下标 (i, j)（行、列）和我们在平面直角坐标系里常说的 (x, y)（横、纵）往往不是一个顺序，
又一个方向是往下、一个是往上，很容易搞混。这里给你几点实战中常用的小技巧，帮你把它们彻底分离、不会混：
1. 变量命名要分清语义
矩阵下标：永远用 row, col、r, c 来命名，第一个表示“第几行”，第二个表示“第几列”。
笛卡尔坐标：永远用 x, y 来命名，x 表示水平方向（通常往右是正向），y 表示竖直方向（通常往上是正向）。
这样在读代码的时候，一看变量名就知道“这是在访问矩阵”、“这是在平面坐标”，永远不会把它们混淆。
row是行 col是列 ( column ) */

class Solution3 {
public:
	Node *construct(const vector<vector<int>> &grid) {
		int n = grid.size();
		// 1. 预处理二维前缀和
		sum.assign(n + 1, vector<int>(n + 1, 0));
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				sum[i + 1][j + 1] = sum[i][j + 1] + sum[i + 1][j] - sum[i][j] + grid[i][j];
		// 2. 递归构建
		return build(0, n, 0, n);
	}

private:
	vector<vector<int>> sum;

	// 计算 [r0,r1)×[c0,c1) 区域的元素总和
	int regionSum(int r0, int r1, int c0, int c1) {
		return sum[r1][c1] - sum[r0][c1] - sum[r1][c0] + sum[r0][c0];
	}

	Node *build(int r0, int r1, int c0, int c1) {
		int total = regionSum(r0, r1, c0, c1);
		int area = (r1 - r0) * (c1 - c0);
		// 全 0 或 全 1，直接返回叶子
		if(total == 0 || total == area) {
			return new Node(total == area, true, nullptr, nullptr, nullptr, nullptr);
		}
		// 否则继续四分
		int rm = (r0 + r1) >> 1;
		int cm = (c0 + c1) >> 1;
		Node *tl = build(r0, rm, c0, cm);
		Node *tr = build(r0, rm, cm, c1);
		Node *bl = build(rm, r1, c0, cm);
		Node *br = build(rm, r1, cm, c1);
		// 返回内部节点
		return new Node(true, false, tl, tr, bl, br);
	}
}; /*我们可以预处理一个 sum[i+1][j+1] 表示原矩阵 [0..i][0..j] 范围内所有元素之和，那么任意子矩阵 [r0,r1)×[c0,c1) 的总和就是
S = sum[r1][c1] - sum[r0][c1] - sum[r1][c0] + sum[r0][c0];
如果 S == 0，说明全是 0；
如果 S == (r1−r0)*(c1−c0)，说明全是 1；
否则就必须继续拆分。
这样每次判断都是 O(1)，整个构建过程的时间复杂度降到 O(n²)（前缀和预处理）+ O(节点数)=O(n²)。*/

int main() {
	Solution1 sol1;
	vector<vector<int>> grid = { { 0, 1 }, { 1, 0 } };
	sol1.construct(grid);
}