struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
struct ListNode* head=NULL,*tail=NULL,*pNew;
int flag=0;
while(l1!=NULL||l2!=NULL||flag){
int val1=(l1==NULL)?0:l1->val;
int val2=(l2==NULL)?0:l2->val;
int sum=val1+val2+flag;
flag=sum/10;
sum%=10;
pNew=(struct ListNode*)malloc(sizeof(struct ListNode));
pNew->val=sum;
pNew->next=NULL;
(head==NULL)?(head=pNew):(tail->next=pNew);
tail=pNew;
if(l1!=NULL) l1=l1->next;
if(l2!=NULL) l2=l2->next;
}
return head;
}
