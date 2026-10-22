// 3. Longest Substring Without Repeating Characters
// 滑动窗口：right 只向前推进，一旦窗口里出现重复字符，就让 left 收缩到该重复被移出为止。
int lengthOfLongestSubstring(char* s) {
    int flag[127] = {0};    // 窗口内每个字符出现的次数
    int left = 0, right = 0;
    int ans = 0;
    int len = strlen(s);
    while (right < len) {
        while (flag[s[right]] == 0 && right < len) {
            ans = (ans > right - left + 1) ? (ans) : (right - left + 1);
            flag[s[right++]]++;
        }
        // 此刻 s[right] 已在窗口内，收缩左端直到它的计数归零
        while (flag[s[right]] == 1 && left < right) {
            flag[s[left++]]--;
        }
    }
    return ans;
}
