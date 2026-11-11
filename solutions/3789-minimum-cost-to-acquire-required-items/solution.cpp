// 3789. Minimum Cost to Acquire Required Items
// 会跨类型省钱的只有「组合包」，所以最优解只可能是三种形态之一：
// 全部买单品类、组合包买到够需求大的那类、组合包买满需求小的那类再多补单品。
class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        return min(
            // 一、两类需求各买各的单品
            1LL * need1 * cost1 + 1LL * need2 * cost2,
            min(
                // 二、组合包直接买到满足较多需求的那一侧（多出来的那部分算白送）
                1LL * costBoth * max(need1, need2),
                // 三、组合包只买满需求较少的一侧，差额用需求较大那类的单品补齐
                1LL * costBoth * min(need1, need2) +
                    1LL * (max(need1, need2) - min(need1, need2)) * (need1 > need2 ? cost1 : cost2)));
    }
};
