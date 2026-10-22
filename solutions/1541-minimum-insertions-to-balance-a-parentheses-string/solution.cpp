// 1541. Minimum Insertions to Balance a Parentheses String
// 贪心扫描：每个未配对的 '(' 需要两个 ')'，用一个标志位记「刚读到半个括号对」。
class Solution {
public:
    int minInsertions(string s) {
        // openCnt：还没被闭合的左括号数；extraNeed：连 '(' 都没得配时额外欠的插入次数
        // needRight：还缺的右括号数，按每个左括号记 2 个；pending：已读到半个括号对
        int openCnt = 0, extraNeed = 0, needRight = 0;
        int pending = 0;
        for (auto &ch : s) {
            if (ch == '(') {
                // 上一个 ')' 还没凑成对就又来了 '('，先把那半个补齐
                if (pending) {
                    if (openCnt == 0) {
                        extraNeed++;
                        needRight++;
                    } else {
                        needRight--;
                        openCnt--;
                    }
                    pending = 0;
                }
                openCnt++;
                needRight += 2;
            } else if (openCnt > 0) {
                // 有左括号可配：先记半对，下一次 ')' 才真正闭合
                if (pending) {
                    openCnt--;
                    needRight -= 2;
                    pending = 0;
                } else {
                    pending = 1;
                }
            } else {
                // 没有左括号可用，这个 ')' 只能靠插入来凑对
                if (pending) {
                    extraNeed++;
                    pending = 0;
                } else {
                    pending = 1;
                }
            }
        }
        // 收尾：残留的半对要么补一个 ')'，要么补左括号
        if (pending) {
            if (openCnt > 0) {
                needRight--;
            } else {
                needRight++;
                extraNeed++;
            }
        }
        return needRight + extraNeed;
    }
};
