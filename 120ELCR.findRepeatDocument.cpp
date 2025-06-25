// Created: 2025-06-24
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 120. 寻找文件副本
设备中存有 n 个文件，文件 id 记于数组 documents。
若文件 id 相同，则定义为该文件存在副本。请返回任一存在副本的文件 id。
示例 1：
	输入：documents = {2, 5, 3, 0, 5, 0}
	输出：0 或 5
提示：
	0 ≤ documents{i} ≤ n-1
	2 <= n <= 100000 */
// 注意区分比较 287N
// 给定一个包含 n 个整数的数组documents，其数字都在{0, n - 1}范围内（包括 0 和 n - 1），

class Solution1 {
public:
	int findRepeatDocument(vector<int> &documents) {
		unordered_set<int> set;
		for(auto d : documents) {
			auto pair = set.insert(d);
			if(!pair.second) {
				return d;
			}
		}
		return -1;
	}
};

class Solution {
public:
	int findRepeatDocument(vector<int> &documents) {
		int n = documents.size();
		for(int i = 0; i < n; ++i) {
			while(documents[i] != i) {
				if(documents[i] == documents[documents[i]]) {
					return documents[i];
				}
				swap(documents[i], documents[documents[i]]);
			}
		}
		return -1;
	}
}; // 本题和 287 题的共用解法

/* 原地置换法
我们把数组看作一个从「下标」到「值」的映射：
    下标范围是 0 … n-1
    值的取值范围也是 0…n-1（对于 LCR 120）或 1…n（对于 287）
当下标和值都在同一个区间时，就能把每个元素 “放到它该去的位置”——也就是把 A[i] 放到下标为 A[i] 的那个槽里。
    如果那个槽空着（恰好存的是它自己），就放进去；
    如果那个槽已经有一个相同的值了，就意味着这个值重复了，我们就可以直接返回它。


对于每一个下标 i：
    检查当前位置是否已就位
        如果 documents[i] == i，说明它已经在“正确位置”，跳过，继续下一个 i+1。

    尝试置换
        否则，看目标位置 j = documents[i] 上的值：
            若 documents[j] == documents[i]，说明“位置 j”上已经有了一个同样的文件 id，当前这个也是要放进来，故找到了重复，直接返回 documents[i]。
            否则，交换 documents[i] 和 documents[j]，把当前位置的值放到它“该在”的位置，让被换上来的值在下一个循环中重新检查。

    重复上述过程，直到遍历完所有 i 或者提前返回。
    
这样做的要点是，每次 swap 都是把一个 “未就位” 的元素向它正确的位置推进了一步，
最终要么所有元素都就位（这种情况下无重复，但按题意一定有重复，所以会在途中发现冲突），要么在赋值冲突时立刻返回。 */

/* 不同于287题，这个题的值域包含 0 ，Floyd 环形检测会失效——因为它的正确性依赖
「有且只有从下标 0 出发才能进入“重复值环”」，而且要保证 0 是“无入度”的节点（没人指向它）。
但在 LCR 120 的场景里，0 本身也可能是某些文件的 id，就会有人指向它，反而形成了“独立小环”，打乱了检测流程。*/

int main() {
	Solution sol;
	vector<int> documents;
	documents = { 3, 3, 3, 3 };
	cout << sol.findRepeatDocument(documents) << endl;
	documents = { 2, 5, 3, 0, 5, 0 };
	cout << sol.findRepeatDocument(documents) << endl;
}