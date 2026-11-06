class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int totalLogs = logs.size();
        int totalQueries = queries.size();
        // 先一律按「没有任何服务器请求过」填 n，窗口内出现过的服务器再多退少补
        vector<int> answer(totalQueries, n);

        // 查询要按时间升序扫描，所以把原始下标一起捆上，算完回填
        vector<vector<int>> sortedQueries;
        for (int i = 0; i < totalQueries; i++) {
            sortedQueries.push_back({queries[i], i});
        }
        sort(sortedQueries.begin(), sortedQueries.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        // 日志按时间升序，窗口只向右滑，不需要回退
        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        int leftLog = 0;   // 窗口左端：第一条时间 >= 左边界 的日志
        int rightLog = 0;  // 窗口右端：第一条时间 > 右边界 的日志
        vector<int> count(n + 1, 0);  // 每个服务器在当前窗口里出现了几次
        for (int i = 0; i < totalQueries; i++) {
            int queryIndex = sortedQueries[i][1];
            int queryTime = sortedQueries[i][0];
            int windowLeft = queryTime - x;
            // 查询时间递增，当前窗口只会在上一个窗口基础上右移，先继承上一个答案
            if (i >= 1) {
                answer[sortedQueries[i][1]] = answer[sortedQueries[i - 1][1]];
            }
            // 右端扩张：新进入窗口的服务器如果此前没被统计过，未请求数减一
            while (rightLog < totalLogs && logs[rightLog][1] <= queryTime) {
                if (count[logs[rightLog][0]] == 0) {
                    answer[queryIndex]--;
                }
                count[logs[rightLog][0]]++;
                rightLog++;
            }
            // 左端收缩：离开窗口的服务器如果就此清零，未请求数加一
            while (leftLog < totalLogs && logs[leftLog][1] < windowLeft) {
                count[logs[leftLog][0]]--;
                if (count[logs[leftLog][0]] == 0) {
                    answer[queryIndex]++;
                }
                leftLog++;
            }
        }
        return answer;
    }
};
