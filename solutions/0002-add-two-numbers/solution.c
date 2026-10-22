// 0002. Add Two Numbers
// 竖式加法：两条链表同位相加并带上进位，哪条链先走完就用 0 顶替它的位。
// 链表头靠三元表达式直接挂到 head 上，省掉哑结点。
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode *head = NULL, *tail = NULL, *newNode;
    int carry = 0;
    // 两条链都走完、进位也清零，循环才停
    while (l1 != NULL || l2 != NULL || carry) {
        int val1 = (l1 == NULL) ? 0 : l1->val;
        int val2 = (l2 == NULL) ? 0 : l2->val;
        int sum = val1 + val2 + carry;
        carry = sum / 10;
        sum %= 10;
        newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = sum;
        newNode->next = NULL;
        // 头结点还没建时挂 head，否则接在 tail 后面（此时 tail 必定非空）
        (head == NULL) ? (head = newNode) : (tail->next = newNode);
        tail = newNode;
        if (l1 != NULL) l1 = l1->next;
        if (l2 != NULL) l2 = l2->next;
    }
    return head;
}
