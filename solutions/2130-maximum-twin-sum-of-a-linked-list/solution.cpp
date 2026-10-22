// 2130. Maximum Twin Sum of a Linked List
// 快慢指针让 node1 停在链表中点，顺路把前半段的值按顺序存进 vec。
// 处理后半段时，下标 i 的孪生结点下标为 n-1-i，n 是链表总长，正好落回 vec 里。
class Solution {
public:
    int pairSum(ListNode* head) {
        int res = 0;
        int n = 0;
        int i = 0;
        vector<int> vec;
        ListNode* node1 = head;
        ListNode* node2 = head;
        while (node2 != nullptr) {
            // node2 一次走两步，它走到头时 node1 刚过半，n 也就攒到了全长
            vec.push_back(node1->val);
            n += 2;
            i++;
            node1 = node1->next;
            node2 = node2->next->next;
        }
        while (node1 != nullptr) {
            // i 从第一段接着数下来，此刻正是当前结点的全局下标，配对值在 n-1-i
            res = max(res, node1->val + vec[n - 1 - i]);
            i++;
            node1 = node1->next;
        }
        return res;
    }
};
