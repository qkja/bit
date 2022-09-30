#include <iostream>
#include <stack>
#include <vector>
#include <queue>

using namespace std;

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};
// 合并两个有序链表
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
        if(pHead1 == nullptr || pHead2 == nullptr)
        {
          if(pHead1)
            return pHead1;
          if(pHead2)
            return pHead2;
          return nullptr;
        }
        ListNode* newHead = nullptr;
        ListNode* cur = nullptr;
        // 这里 我们使用多个 while
        while(pHead1 && pHead2)
        {
          if(pHead1->val <= pHead2->val)
          {
            while(pHead1 && pHead2 && pHead1->val <= pHead2->val)
            {
              // 第一次 插入
              if(newHead == nullptr)
              {
                newHead = pHead1;
                cur = pHead1;
              }
              else 
              {
                cur->next = pHead1;
                cur = pHead1;
              }
              pHead1 = pHead1->next;
            }
          }
          else 
          {
            while(pHead1 && pHead2 &&  pHead1->val > pHead2->val)
            {
              if(newHead == nullptr)
              {
                newHead = pHead2;
                cur = pHead2;
              }
              else 
              {
                cur->next = pHead2;
                cur = pHead2;
              }
              pHead2 = pHead2->next;
            }
          }
        }// end of while 

        if(pHead1)
          cur->next = pHead1;
        if(pHead2)
          cur->next = pHead2;

        return newHead;
    }
};
// 合并两个有序链表 
//class Solution {
//public:
//    ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
//      if(pHead1 == nullptr && pHead2 == nullptr)
//        return nullptr;
//      if(pHead1 && !pHead2)
//        return pHead1;
//      if(!pHead1 && pHead2)
//        return pHead2;
//
//      // 合并 形成一个 新的 链表
//      ListNode* newHead = nullptr;
//      ListNode* next = nullptr;
//      while(pHead1 && pHead2)
//      {
//        if(pHead1->val >= pHead2->val)
//        {
//          // 这里是 插入 判断第一次插入
//          if(newHead == nullptr)
//          {
//            newHead = pHead1;
//            next = newHead;
//          }
//          else 
//          {
//            next->next = pHead1;
//            next = pHead1;
//          }
//          pHead1 = pHead1->next;
//        }
//        else 
//        {
//          if(newHead == nullptr)
//          {
//            newHead = pHead2;
//            next = newHead;
//          }
//          else 
//          {
//            next->next = pHead2;
//            next = pHead2;
//          }
//          pHead2 = pHead2->next;
//        }  
//      }
//        if(pHead1)
//        {
//          next->next = pHead1;
//        }
//        if(pHead2)
//        {
//          next->next = pHead2;
//        }
//        return newHead;
//    }
//};



// 头插 法 
//class Solution {
//public:
//    ListNode* ReverseList(ListNode* pHead) {
//      if(pHead == nullptr)
//        return nullptr;
//      ListNode* newHead = nullptr;
//      while(pHead)
//      {
//        ListNode* p = pHead;
//        pHead = p->next;
//
//        // 头擦
//        p->next = newHead;
//        newHead = p;
//      }
//      return newHead;
//    }
//};
// 三个指针
//class Solution {
//public:
//    ListNode* ReverseList(ListNode* pHead) {
//
//      if(pHead == nullptr)
//        return nullptr;
//      ListNode* prev = nullptr;
//      ListNode* cur = pHead;
//      ListNode* curNext = pHead->next; // 保存 next 指针
//      while(cur!=nullptr)
//      {
//        cur->next = prev;
//        prev = cur;
//        cur = curNext;
//        if(curNext) // 这个 很重要 看判断 条件
//          curNext = cur->next;
//      }
//      return prev;
//    }
//};

// 二叉搜索树的 后序遍历
//class Solution {
//public:
//    bool VerifySquenceOfBSTChild(const vector<int>& v,int left,int right) {
//
//      if(right <= left)
//      {
//        return true;
//      }
//      int rootData = v[right];
//      // 分成 两段
//      int i = left;
//      for(; i < right;  i++)
//      {
//        if(v[i] > rootData)
//        {
//          break;
//        }
//      }
//      // 这里需要 判断 右侧 的是不是 都大于  rootData 
//      for(int j = i;j < right; j++)
//      {
//        if(v[j] < rootData)
//          return false;
//      }
//
//      //  这里 需要 判断 左和右
//      return VerifySquenceOfBSTChild(v, left, i-1)
//        && VerifySquenceOfBSTChild(v, i, right-1);
//
//    }
//    bool VerifySquenceOfBST(vector<int> sequence) {
//      if(sequence.empty())
//        return false;
//
//      return VerifySquenceOfBSTChild(sequence,0,sequence.size()-1);
//    }
//};

//struct TreeNode {
//	int val;
//	struct TreeNode *left;
//	struct TreeNode *right;
//	TreeNode(int x) :
//			val(x), left(NULL), right(NULL) {
//	}
//};
//// 二叉树 的层序遍历  简单
//class Solution {
//public:
//    vector<int> PrintFromTopToBottom(TreeNode* root) {
//      vector<int> v;
//      if(root == nullptr)
//        return v;
//
//      // 需要借助 队列
//      queue<TreeNode*> q;
//      q.push(root);
//      while(!q.empty())
//      {
//        // 得到 队列  最前面的元素
//        TreeNode* ret = q.front();
//        v.push_back(ret->val);
//        q.pop();
//        if(ret->left)
//          q.push(ret->left);
//        if(ret->right)
//          q.push(ret->right);
//      }
//      return v;
//    }
//};

// 入栈和 出栈顺序
//class Solution {
//public:
//    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
//      stack<int> s;
//      int index = 0;
//      for(size_t i = 0; i < pushV.size(); i++)
//      {
//        // 入栈
//        int ret = pushV[i];
//        s.push(ret);
//        while(s.top() == popV[index])
//        {
//          s.pop();
//          index++;
//          if(s.empty())
//          {
//            break;
//          }
//
//        }
//      }
//      return s.empty();
//    }
//};
int main()
{

  return 0;
}


//class Solution {
//public:
//    void push(int value) {
//
//        // 这里 我们让 辅助栈的元素个数一样
//        s.push(value);
//        if (minStack.empty() || value <= minStack.top())
//        {
//            minStack.push(value);
//        }
//        else
//        {
//            minStack.push(minStack.top());
//        }
//    }
//    void pop() {
//        s.pop();
//        minStack.pop();
//    }
//    int top() {
//        return s.top();
//    }
//    int min() {
//        return minStack.top();
//    }
//private:
//    stack<int> s;
//    stack<int> minStack;
//};
//int main()
//{
//
//  cout << "测试" << endl;
//  return 0;
//}
