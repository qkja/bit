#include <iostream>
#include <vector>
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

  // 全排列
  vector<string> Permutation(string str) {
    vector<string> v;
    if(str.empty() == 0)
      return v;
    return v;
  } 
  // 简单的 回溯法
  // 结果集   所有满足条件的结果
  // 待选结果 所有的结果,需要挑选
  //void FindPathDFS(TreeNode* root, int expectNumber, vector<vector<int>>& result, vector<int>& list) {

  //   if(root == nullptr)
  //     return;
  //   list.push_back(root->val);
  //   expectNumber -= root->val;
  //   
  //   // 这里 判断 到叶子节点路径 是不是合适 
  //   if(root->left == nullptr && root->right == nullptr && expectNumber == 0)
  //   {
  //     result.push_back(list);
  //   }

  //   // 开始遍历左右子树 这里的 expectNumber 已经被更新了
  //   FindPathDFS(root->left, expectNumber, result, list);
  //   FindPathDFS(root->right, expectNumber, result, list);
  //   // 这里 要pop 一下 社么时候 回退 左右子树的都判断过了 才会回退
  //   list.pop_back();
  // }
  // vector<vector<int>> FindPath(TreeNode* root,int expectNumber) {
  //   
  //   vector<vector<int>> result;
  //   if(nullptr == root)
  //   {
  //     return result;
  //   }
  //   vector<int> list;
  //   FindPathDFS(root, expectNumber,result, list);
  //   return result;
  // }
};
