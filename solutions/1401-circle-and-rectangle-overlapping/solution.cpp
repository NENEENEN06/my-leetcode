// 1401. Circle and Rectangle Overlapping
// 把圆心钳制到矩形范围内，得到矩形上离圆心最近的点，
// 再比较该点的距离平方与半径平方（不开方，避开浮点误差）。
class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        int x, y;
        if (xCenter > x2) {
            x = x2;
        } else if (xCenter < x1) {
            x = x1;
        } else {
            x = xCenter;
        }
        // y 方向同理：圆心落在矩形内时最近点就是圆心本身
        if (yCenter > y2) {
            y = y2;
        } else if (yCenter < y1) {
            y = y1;
        } else {
            y = yCenter;
        }
        return (x - xCenter) * (x - xCenter) + (y - yCenter) * (y - yCenter) <= radius * radius;
    }
};
