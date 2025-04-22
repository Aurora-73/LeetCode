#include "MyUtils.h"

class Solution1 {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> newIntervals; // 不设置新数组很难写
        int i = 0;
        while(i < intervals.size() && intervals[i][1] < newInterval[0]){
            newIntervals.push_back(intervals[i]);
            i++;
        } // 先插入没有重叠的
        newIntervals.push_back(newInterval);
        while(i < intervals.size() && intervals[i][0] <= newInterval[1]){
            newIntervals.back()[0] = min(newIntervals.back()[0], intervals[i][0]);
            newIntervals.back()[1] = max(newIntervals.back()[1], intervals[i][1]);
            i++;
        } // 处理重叠的
        while(i < intervals.size()){ 
            newIntervals.push_back(intervals[i]);
            i++;
        } // 再插入没有重叠的
        return newIntervals;
    }
};

class Solution2 {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int i = 0;
        while(i < intervals.size() && intervals[i][1] < newInterval[0]) i++; // 先跳过没有重叠的

        intervals.insert(intervals.begin() + i, newInterval);
        if(i < intervals.size() - 1)    intervals[i][0] = min(intervals[i][0], intervals[i + 1][0]); 
        // 将自身插入进去，必须插入，为了归一化后面为空的情况，同时调整自身的最小值

        while(i + 1 < intervals.size() && intervals[i][1] >= intervals[i + 1][0]){
            intervals[i][1] = max(intervals[i][1], intervals[i + 1][1]);
            intervals.erase(intervals.begin() + i + 1);
        } // 处理重叠的，吃掉后面和自己重叠的
        return intervals;
    }
};
    
int main(){
    Solution1 sol1;
    Solution2 sol2;
    vector<vector<int>> intervals = {{1,3},{6,9}};
    vector<int> newInterval = {2,5};
    cout << sol1.insert(intervals, newInterval) << endl;
    cout << sol2.insert(intervals, newInterval) << endl;
}