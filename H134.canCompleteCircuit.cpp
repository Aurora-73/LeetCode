#include <vector>
#include <iostream>
using namespace std;

/*
* 在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。
你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。
给定两个整数数组 gas 和 cost ，如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1 。如果存在解，则 保证 它是 唯一 的。
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int sum = 0, now = 0, index = 0,n = gas.size();
        for (int i = 0;i < n;i++) {
            sum += gas[i] - cost[i];
            now += gas[i] - cost[i];
            if (now < 0) {
                now = 0;
                index = i + 1;
            }
        }
        return sum < 0 ? -1 : index;
    }
};

int main() {
    Solution sol;
    vector<int> gas =  { 2,3,4 };
    vector<int> cost = { 3,4,3 };
    cout << sol.canCompleteCircuit(gas, cost);
}
/*​​1. 全局可行性判断​​
若所有站点净油量总和（总补给 - 总消耗）为负，则无论如何无法完成环路。
​​2. 贪心策略的核心逻辑​​
当从起点 start 出发至 end 站点时油量耗尽，说明：
在 [start, end) 区间内，任何起点出发的局部油量只会更少（因起点 start 已选择净油量最大的位置）。
因此直接跳过 [start, end] 区间，尝试以 end+1 为新的起点，避免无效遍历。
​​3. 终局验证条件​​(对前半段使用结论1)
遍历完成后，若全局油量非负，则最后记录的起点 start 即为答案。此时的剩余油量足以覆盖 [0, start) 区间的消耗，与您提到的「剩余钱足够应付前半段坏人」完全一致

*/