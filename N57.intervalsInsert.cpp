#include "MyUtils.h"

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        auto lb = lower_bound(intervals.begin(), intervals.end(), newInterval, [](vector<int> a, vector<int> b){return a[0] < b[0];});
        auto ub = upper_bound(intervals.begin(), intervals.end(), newInterval, [](vector<int> a, vector<int> b){return a[1] < b[1];});
        vector<int> &before = *(lb - 1), &after = *lb;
        bool done = false;
        if(before[1] >= newInterval[0]){
            before[1] = max(before[1], newInterval[1]);
            done = true;
        }
        if(after[0] <= newInterval[1]){
            after[0] = min(after[0], newInterval[1]);
            if(done){
                before[1] = max(before[1], after[1]);
                intervals.erase(lb);
            }
            done = true;
        }
        
        if(!done){
            intervals.insert(lb, newInterval);
        }
        return intervals;
    }
};
    
int main(){
    Solution sol;
    vector<vector<int>> intervals = {{1,3},{6,9}};
    vector<int> newInterval = {2,5};
    cout << sol.insert(intervals, newInterval);
}