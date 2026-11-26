class Solution {
public:
    bool canAliceWin(int n) {
        int remainingStones = n;
        int completedMoves = 0;
        int requiredStones = 10;
        while (remainingStones >= requiredStones && requiredStones > 0) {
            remainingStones -= requiredStones;
            completedMoves++;
            requiredStones--;
        }
        return completedMoves % 2 == 1;
    }
};
