/**
 * User: Qkj
 * Description:
 * Date: 2023-02-01
 * Time: 12:00
 */
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

class A
{
public:
    A(int b = 0)
        : a(b)
    {
        cout << "bbbb" << endl;
    }
    bool operator()()
    {
        cout << "cccccc" << endl;
        return true;
    }

public:
    int a;
};

int main()
{
    A a();
    /*A()();*/
    cout << "aaaaaaa" << endl;
    // a();
    return 0;
}

// bool myfunction(int i, int j)
// {
//     return i < j;
// }

// struct myclass
// {
//     bool operator()(int i, int j) { return (i < j); }
// } myobject;
// int main()
// {
//     int arr[] = {1, 3, 4, 5, 2, 0};

//     int sz = sizeof(arr) / sizeof(arr[0]);
//     sort(arr, arr + sz, myobject);
//     for (auto &val : arr)
//     {
//         cout << val << " ";
//     }
//     cout << endl;
//     return 0;
// }

// int main()
// {
//     set<int> s;
//      s.insert(3);
//     s.insert(4);
//     s.insert(1);
//     s.insert(2);

//     for(auto& val:s)
//     {
//         cout << val <<" " ;
//     }
//     return 0;
// }

// 这是一个二叉搜索树的节点
// template <class T>
// struct BSTreeNOde
// {
// public:
//     BSTreeNOde(const T &x = T())
//         : left(nullptr), right(nullptr), _key(x)
//     {
//     }

// public:
//     BSTreeNOde *left;
//     BSTreeNOde *right;
//     T _key;
// };

// template <class T>
// class BSTree
// {
// public:
//     typedef BSTreeNOde<T> Node; // 名字有点 长
// public:
//     /// @brief 构造函数
//     BSTree()
//         : _root(nullptr)
//     {
//     }
//     // 析构函数
//     ~BSTree()
//     {
//         DestoryTree(_root);
//         _root = nullptr;
//     }

//     //拷贝狗仔
//     BSTree(const BSTree<T> &b)
//         : _root(nullptr)
//     {
//         _root = CopyTree(b._root);
//     }

//     // 赋值重载
//     BSTree<T> &operator=(BSTree b)
//     {
//         swap(_root, b._root);
//         return *this;
//     }

// public:
//     bool eraseR(const T &val)
//     {
//         _eraseR(_root, val);
//     }
//     /// @brief 删除数据 非递归版本
//     /// @param val
//     /// @return
//     bool erase(const T &val)
//     {
//         if (_root == nullptr)
//         {
//             return false;
//         }

//         // 1 找到该节点 以及父节点
//         Node *parent = nullptr;
//         Node *cur = _root;
//         while (cur)
//         {
//             if (cur->_key == val)
//             {
//                 // 这里已经找到了,所有的删除都在这里进行

//                 // 没有左子树 或者 没有 左子树和右子树
//                 if (cur->left == nullptr)
//                 {
//                     // 判断是不是头节点
//                     if (cur == _root)
//                     {
//                         // 是根节点
//                         //_root = cur->left;
//                         _root = cur->right;
//                         delete cur;
//                         return true;
//                     }

//                     if (parent->right == cur)
//                     {
//                         parent->right = cur->right;
//                     }
//                     else
//                     {
//                         parent->left = cur->right;
//                     }
//                     delete cur;
//                     return true;
//                 }
//                 // 无右子树, 存在左子树
//                 else if (cur->right == nullptr)
//                 {
//                     if (cur == _root)
//                     {
//                         // _root = cur->right;

//                         _root = cur->left;
//                         delete cur;
//                         return true;
//                     }
//                     if (parent->right == cur)
//                     {
//                         parent->right = cur->left;
//                     }
//                     else
//                     {
//                         parent->left = cur->left;
//                     }
//                     delete cur;
//                     return true;
//                 }

//                 else
//                 {
//                     // 存在右子树和左子树
//                     // 两种方法

//                     // 1. 右节点中最小的值
//                     Node *minParent = cur;
//                     Node *minRight = cur->right;

//                     while (minRight->left)
//                     {
//                         minParent = minRight;
//                         minRight = minRight->left;
//                     }

//                     // 这里直接覆盖
//                     cur->_key = minRight->_key;

//                     // 删除 节点
//                     if (minParent->left == minRight)
//                     {
//                         minParent->left = minRight->right;
//                     }
//                     else
//                     {
//                         // 这情况很重要是
//                         // minp
//                         //    minR
//                         //        val
//                         // 这个情况
//                         minParent->right = minRight->right;
//                     }

//                     delete minRight;
//                 }
//                 return true;
//             }
//             else if (cur->_key > val)
//             {
//                 parent = cur;
//                 cur = cur->left;
//             }
//             else
//             {
//                 parent = cur;
//                 cur = cur->right;
//             }
//         }
//         return false;
//     }

//     /// @brief  查找数据
//     /// @param key
//     /// @return
//     Node *find(const T &key)
//     {
//         if (_root == nullptr)
//             return nullptr;
//         Node *cur = _root;
//         while (cur)
//         {
//             if (key > cur->_key)
//             {
//                 cur = cur->right;
//             }
//             else if (key < cur->_key)
//             {
//                 cur = cur->left;
//             }
//             else
//             {
//                 return cur;
//             }
//         }
//         return nullptr;
//     }

//     /// @brief 递归版本插入元素
//     /// @param val
//     /// @return
//     bool insertR(const T &val)
//     {
//         return _insertR(_root, val);
//     }

//     /// @brief 中序遍历
//     void inorder()
//     {
//         _inorderR(_root);
//     }

//     /// @brief 非递归版本插入函数
//     /// @param val  插入元素
//     /// @return  成功返回 true
//     bool insert(const T &val)
//     {
//         // new 出一个节点
//         Node *node = new Node(val);

//         // 头一次插入
//         if (nullptr == _root)
//         {
//             _root = node;
//             return true;
//         }
//         Node *parent = nullptr;
//         Node *cur = _root;
//         while (cur != nullptr)
//         {
//             // 禁止插入相同的元素
//             if (cur->_key == val)
//             {
//                 return false;
//             }
//             if (cur->_key > val)
//             {
//                 parent = cur;
//                 cur = cur->left;
//             }
//             else
//             {
//                 parent = cur;
//                 cur = cur->right;
//             }
//         }

//         // 到这里判断插入右侧还是左侧
//         if (parent->_key < val)
//         {
//             parent->right = node;
//         }
//         else
//         {
//             parent->left = node;
//         }
//         return true;
//     }

//     Node *findR(const T &key)
//     {
//         return _findR(_root, key);
//     }

// private:
//     Node *CopyTree(Node *root)
//     {
//         if (root == nullptr)
//         {
//             return nullptr;
//         }
//         Node *copyNode = new Node(root->_key);

//         copyNode->left = CopyTree(root->left);
//         copyNode->right = CopyTree(root->right);
//         return copyNode;
//     }
//     void DestoryTree(Node *root)
//     {
//         if (root == nullptr)
//             return;
//         DestoryTree(root->left);
//         DestoryTree(root->right);
//         delete root;
//     }
//     bool _eraseR(Node *&root, const T &val)
//     {
//         if (root == nullptr)
//             return false;
//         if (root->_key > val)
//         {
//             _eraseR(root->left, val);
//         }
//         else if (root->_key < val)
//         {
//             _eraseR(root->right, val);
//         }
//         else
//         {
//             // 找到了
//             if (root->left == nullptr)
//             {
//                 Node *cur = root;
//                 root = root->right; // 这是引用
//                 delete cur;
//             }
//             else if (root->right == nullptr)
//             {
//                 Node *cur = root;
//                 root = root->left;
//                 delete cur;
//             }
//             else
//             {
//                 Node *minRight = root->right;
//                 while (minRight->left != nullptr)
//                 {
//                     minRight = minRight->left;
//                 }
//                 // 这是一个好东西
//                 swap(root->_key, minRight->_key);
//                 // 这里 递归  删除  要知道 现在 val所在的节点 一定是 没有左子树的
//                 return _eraseR(root->right, val);
//             }
//             return true;
//         }
//         return false;
//     }

//     Node *_findR(Node *root, const T &key)
//     {
//         if (root == nullptr)
//             return nullptr;

//         if (key > root->_key)
//             return _findR(root->right, key);

//         else if (key < root->_key)
//             return _findR(root->left, key);

//         else
//             return root;
//     }

//     bool _insertR(Node *&root, const T &val)
//     {
//         if (root == nullptr)
//         {
//             // 注意我们传入是引用,这就意味这我们修改是对的
//             root = new Node(val);
//             return true;
//         }
//         if (root->_key == val)
//         {
//             return false;
//         }
//         else if (root->_key > val)
//         {
//             _insertR(root->left, val);
//         }
//         else
//         {
//             _insertR(root->right, val);
//         }
//         return true;
//     }
//     /// @brief 中序遍历 子函数
//     /// @param root  遍历的节点
//     void _inorderR(Node *root)
//     {
//         if (root == nullptr)
//             return;
//         _inorderR(root->left);
//         cout << root->_key << " ";
//         _inorderR(root->right);
//     }

// private:
//     Node *_root;
// };

// int main()
// {
//     BSTree<int> b;
//     int a[] = {8, 3, 1, 10, 6, 4, 7, 14, 13};
//     int sz = sizeof(a) / sizeof(int);

//     for (int i = 0; i < sz; i++)
//     {
//         b.insertR(a[i]);
//     }
//     b.inorder();
//     cout << endl;

//     b.erase(8);
//     // for (int e : a)
//     // {
//     //     b.erase(e);
//     //     b.inorder();
//     //     cout << endl;
//     // }

//     b.inorder();
//     cout << endl;

//     return 0;
// }

// int main()
// {
//     BSTree<int> b;
//     int a[] = {8, 3, 1, 10, 6, 4, 7, 14, 13};
//     int sz = sizeof(a) / sizeof(int);

//     for (int i = 0; i < sz; i++)
//     {
//         b.insertR(a[i]);
//     }
//     b.inorder();
//     cout << endl;
//     // 插入个 相同的
//     b.insert(8);
//     b.inorder();
//     cout << endl;

//     return 0;
// }