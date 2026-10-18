class Solution {
public:
    int pairSum(ListNode* head) {
        int res=0;
        int n=0;
        int i=0;
        vector<int>vec;
        ListNode* node1=head;
        ListNode* node2=head;
        while(node2!=nullptr){
            vec.push_back(node1->val);
            n+=2;
            i++;
            node1=node1->next;
            node2=node2->next->next;
        }
        while(node1!=nullptr){
            res=max(res,node1->val+vec[n-1-i]);
            i++;
            node1=node1->next;
        }
        return res;
    }
};
