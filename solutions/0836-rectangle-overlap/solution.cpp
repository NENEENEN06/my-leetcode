// 836. Rectangle Overlap
// 重叠的充要条件是两个方向上的投影区间都相交，四条不等式一次判完，取反即为「不重叠」。
class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        // 水平方向相交且垂直方向相交
        if (rec2[0] < rec1[2] && rec2[1] < rec1[3]
            && rec1[0] < rec2[2] && rec1[1] < rec2[3]) return true;
        return false;
    }
};
