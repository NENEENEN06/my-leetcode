class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        set<int> freeServers;               // 当前空闲的服务器编号
        vector<int> count(k, 0);            // 每台服务器已处理的请求数
        vector<int> result;
        // {释放时刻, 服务器编号}，小根堆按释放时刻排序
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> busy;
        int maxCount = 0;
        int totalRequests = arrival.size();
        for (int i = 0; i < k; i++) {
            freeServers.insert(i);
        }
        for (int i = 0; i < totalRequests; i++) {
            // 到达前已经跑完的服务器放回空闲池
            while (!busy.empty() && busy.top().first <= arrival[i]) {
                freeServers.insert(busy.top().second);
                busy.pop();
            }
            // 一台都空不出来就丢弃这次请求
            if (freeServers.size() == 0) {
                continue;
            }
            // 从 i % k 开始顺时针找第一个空闲的，找不到就回绕到最小编号
            auto pos = freeServers.lower_bound(i % k);
            if (pos == freeServers.end())
                pos = freeServers.begin();
            int serverId = *pos;
            busy.push({arrival[i] + load[i], serverId});
            freeServers.erase(serverId);
            count[serverId]++;
            maxCount = max(maxCount, count[serverId]);
        }
        for (int i = 0; i < k; i++) {
            if (count[i] == maxCount) {
                result.push_back(i);
            }
        }
        return result;
    }
};
