// 2409. Count Days Spent Together
// 两人都在的天数 = 两段日期的交集：晚到的那天 到 早走的那天，含首尾。
// "MM-DD" 定长且零填充，字典序就是时间序，所以端点直接对字符串取 max/min。
class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        string arrive = max(arriveAlice, arriveBob);   // 两人都到了的那天
        string leave = min(leaveAlice, leaveBob);      // 有一方要先走的那天
        if (arrive > leave) {
            return 0;   // 没有交集
        }
        // daysum[m] = 第 m 个月之前累计的天数（非闰年），把 MM-DD 换算成年内第几天
        int daysum[] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
        return daysum[stoi(leave.substr(0, 2))] + stoi(leave.substr(3, 2))
             - daysum[stoi(arrive.substr(0, 2))] - stoi(arrive.substr(3, 2)) + 1;
    }
};
