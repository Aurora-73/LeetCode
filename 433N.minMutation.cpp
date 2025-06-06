// Created: 2025-05-08
#include "MyUtils.hpp"

/*433. 最小基因变化
基因序列可以表示为一条由 8 个字符组成的字符串，其中每个字符都是 'A'、'C'、'G' 和 'T' 之一。
假设我们需要调查从基因序列 start 变为 end 所发生的基因变化。一次基因变化就意味着这个基因序列中的一个字符发生了变化。
例如，"AACCGGTT" --> "AACCGGTA" 就是一次基因变化。
另有一个基因库 bank 记录了所有有效的基因变化，只有基因库中的基因才是有效的基因序列。（变化后的基因必须位于基因库 bank 中）
给你两个基因序列 start 和 end ，以及一个基因库 bank ，请你找出并返回能够使 start 变化为 end 所需的最少变化次数。如果无法完成此基因变化，返回 -1 。
注意：起始基因序列 start 默认是有效的，但是它并不一定会出现在基因库中。*/

class Solution {
public:
	bool onStep(string &a, string &b) {
		bool diff = false;
		for(size_t i = 0; i < a.size(); i++) {
			if(a[i] != b[i]) {
				if(diff) {
					return false;
				} else {
					diff = true;
				}
			}
		}
		return diff;
	}
	int minMutation(string startGene, string endGene, vector<string> &bank) {
		vector<bool> visited(bank.size(), false);
		queue<string *> q;
		q.push(&startGene);
		int step = -1;
		while(!q.empty()) {
			size_t size = q.size();
			++step;
			while(size--) {
				string &now = *q.front();
				q.pop();
				if(now == endGene) {
					return step;
				}
				for(int i = 0; i < bank.size(); ++i) {
					if(!visited[i] && onStep(bank[i], now)) {
						visited[i] = true;
						q.push(&bank[i]);
					}
				}
			}
		}
		return -1;
	}
};

int main() {
	Solution sol;
}