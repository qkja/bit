#include <iostream>
using namespace std;

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};

class Solution {
public:
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {

    }
};

//struct ListNode {
//	int val;
//	struct ListNode *next;
//	ListNode(int x) :
//			val(x), next(NULL) {
//	}
//};
//// 合并两个 有序链表  递归法
//// 这个方法可以 和 面试官 讲,写非递归方法
//class Solution {
//public:
//    ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
//
//      if(pHead1 == nullptr)
//        return pHead2;
//      if(pHead2 == nullptr)
//        return pHead1;
//      ListNode* head = nullptr;
//      if(pHead1->val <= pHead2->val)
//      {
//        head = pHead1;
//        pHead1 = pHead1->next;
//      }
//      else 
//      {
//        head = pHead2;
//        pHead2 = pHead2->next;
//      }
//
//      // 这里 开始 递归
//      head->next = Merge(pHead1, pHead2);
//      return head;
//    }
//};

int main()
{

  return 0;
}
