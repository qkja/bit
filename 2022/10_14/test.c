// 七个接口之多  
// 进程替换
// 简单的shell 这里我们把代码 放在 VS 中,避免这里出现看错问题
// 这里VS可能演示不出来
// ls 带颜色  裸漏的ls 不带  这里起了一个别名 alias 重启没有了  永久需要改配置文件
// 已经有颜色了  这里 需要 cd .. 为何不会改变 我们shell根本就不是 cd 
// 那么我们执行的是哪一个
// cd 只是影响 子进程 子进程执行完就没了,改变它没有用,不改变父进程
// 如果有些行为,是必须让父进程执行的 不想让子进程  这里就不创建子进程
// 父进程自己实现 代码  这里叫做 内建 or 内置命令
// 这里如何内建
// 这里我把自己的风格确定了  大驼峰(C++常用的)不过OJ按照它的分割来
// 这里 解释的粗糙一点
// 子进程 继承 父进程 的环境变量
// 默认会传递
// 为何 导入 环境变量 为何不行
// putenv
//

// 基础 IO进程 还没完  概念+控制  搞定了
// 通信还没有 
// 预计3-4结课
// 文件描述符 

// 文件描述符 
//
// 进程和文件
// 复习一下文件操作

// 打开文件  关闭文件
// 打开文件   文本 二进制
// 当前路径 是什么
// a
// r
// w
// 理论回归
//
int main()
{

  return 0;
}









