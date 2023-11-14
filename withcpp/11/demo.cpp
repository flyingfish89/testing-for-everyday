#include "test.hpp"

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};
ListNode* head = nullptr;
void push_back(int val)
{
    ListNode* p = nullptr;
    ListNode* pnext;
    
    if (head == nullptr)
    {
        p = (ListNode*)malloc(sizeof(struct ListNode));
        p->val = val;
        p->next = nullptr;
        head = p;
    }
    else
    {
        p = head;
        pnext = p->next;
        while (pnext != nullptr)
        {
            p = pnext;
            pnext = p->next;
        }
        pnext = (ListNode*)malloc(sizeof(struct ListNode));
        pnext->val = val;
        pnext->next = nullptr;
        p->next = pnext;
    }
}
void prinlist()
{
    ListNode* p = head;
    while (p != nullptr)
    {
        cout << p->val;
        p = p->next;
    }
}
int main(int argc, char *argv[])
{
    for (int i = 0; i < 10; i++)
    {
        push_back(i);
    }
    prinlist();
	stack<ListNode*> mystack;
    ListNode* p = head;
    ListNode* pnext = nullptr;

    while (p != nullptr)
    {
        mystack.push(p);
        p = p->next;
    }
    p = head;
    pnext = p->next;
    while (p != mystack.top())
    {
        p->next = mystack.top();
        p->next->next = pnext;
        pnext = pnext->next;
        mystack.pop();
    }
	
	
	return 0;
}