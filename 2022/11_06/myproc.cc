/**
* User: Qkj
* Description: 信号
* Date: 2022-11-06
* Time: 19:47
*/

#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;

void handler(int signo)
{
  cout << "我是一个进程,刚刚捕捉了一个信号" << signo << endl;
}

int main()
{

  // 什么是信号  生活中  红绿灯  下课铃声  信号枪 烽火台 旗语
  // 我们是如何得知这些东西的  准确说 是如何明白 这些信号的含义的
  // 有人 规定的 有人教的   我们是能够知道和明白他们的意义的

  // 我们 是否明白不同的信号我们要干什么 
  // 知道 红灯行 绿灯停(反了) 下课铃声  -- 这里我们早就明白了
  //

  // 我们可以使用 kill 9 号信号杀掉进程
  // 也就是 在信号没有出来前 ,我们已经知道信号的处理的方法

  //  上面  就是前提条件   什么是  我们已经具备了处理能力
  //  拿到成绩后可以推测老妈的脸色  就可以推测 是不是会出现 混合双打

  // 这里下一个结论   信号是给进程发送的,进程也应该具备某些能力
  // 1. 早就拥有
  // 2. 识别对应信号
  // 3. 能够对不同的信号做出处理

  // 这里能力 都是 程序员给的   程序员写的代码
  // 我们现实生活 是社会给你的   外卖小哥(不接电话 不开门) 送外卖的例子

  // 对于进程 而言   我们还没有发 9号信号  进程也会知道 这是杀掉进程


  //while (1)
  //  sleep(1);

  // 为何  之前 我们 ctrl c 可以杀掉进程
  // 前台进程 ./myproc    我们前面一般使用的  
  // 后台进程 ./myproc & 这个就是后台进程  ctrl + c 杀不掉  当然 kill 是可以的
  // 后台->前台  jobs -> fg 1(这个1是任务编号)  前后端混搭 虽然看着打乱了 不影响我们输入  回显
  // 前台->后台  ctrl+z -> jobs -> bg(任务编号)


  // 再说 ctr + c 为何会 终止进程   键盘产生一个中断  这里还没有办法谈
  

  // 进程在任何时候任何地点 都会收到信号    -- 异步 
  // 点外外卖 手机扔到一边  外卖员什么时候到 我不知道,直到他打电话或者敲门
  
  // 那么我们究竟有多少信号 -- > 62个  注意不是 64个
  // 34 -> 64 是实时信号   实时操作系统(不主流,但是用) 我们现在用的是分时  只要任务到来了,必须立马处理 还要处理的快 最关键的是  只能一个一个处理   比如车载系统
  


  // 这些信号究竟是什么  左侧:右侧 信号编号:信号名称 (本质就是宏)
  // 我点了个外卖  我也不知道他什么时候来 开了一吧游戏
  // 外卖到了,我也不想去拿,告诉外卖小哥等一下, 或者同学叫我去吃饭  当是我正在处理非常重要的事情   这两个 我不一定里面处理  为何我不一定里面处理这些事 信号不是来了吗  因为这个世界不是围绕外卖小哥转的 ,我是一个难缠的客户  或许我正在瞒着重要的事  
  // 信号的产生与否和我做什么事情没有任何关系   -- 异步的
  // 当信号产生的时候,进程在忙着跟重要的事情   这是进程 不急着处理这个信号  比如在打游戏




  // 那么对于那些等者的信号 我们该如何做 我的记性不太好 是如何知道这些我们没有处理的信号
  // 这里我们需要明白一个道理  我们等会处理 不是不处理
  // 我们如何记住  记住什么
  
  // 先来看 记住什么  信号有吗 什么信号
  
  // 如何处理 信号(方式)
  // 外卖小哥等着  我们开门拿到外卖 吃外卖  -- 这里就是处理 默认动作
  // 和女朋友 吵架 点外买 扔到外面 当是我也不会吃  这里我们也处理这个信号了 就是扔到外面 忽略
  // 把外买给了你的弟弟妹妹  (百元外买) 也处理了   自定义处理  郭红路灯 非要摇头和跳着走 就是不一样
  // 
  // 前面的就是信号的处理 也就是 专业名词 信号的捕捉/信号的迪搭处理动作
  
  // 三个大阶段   信号产什么 信号产生中 信号处理后
  //
  
  // 如何记住进程记住 就是 task_struct 中有一个 32位 类型的 位图  这里也会 进一步证明我们学习的 31个信号量
  // 注意 这个不太严谨  0000 0001 1号信号
  // 内核数据结构 只有OS有这个权利 来修改  OS是进程的管理者
  // 这里 先回答一个异步 上课 饿了 吃饭 等着上课

  //while(1)
  //{
  //  //cout << "hello bit" << endl;
  //  //cout << "hello bit" << endl;
  //  sleep(1);
  //}

  // 我们要记住
  // 有没有   -> 0 -> 1
  // 什么信号 -> 位图bit位




  // 信号产生前 
  // 硬件 signal() 对一个信号 设置特定的处理操作 这里是 自定义 回调方法   ctr+c 发送  2号信号 给目标进程 默认是 终止当前进程 这里我们是自定义ctr +\ 是3号信号
  //
  // signal(2, handler);
  signal(SIGINT, handler);   // 注意 这里不是在调用hander 方法  只有产生相应的信号 才会调用
  sleep(3);

  

  cout << "进程设置完比" << endl;
  sleep(3);

  while(1)
  {
    cout << "我是一个正在运行的进程: pid" << getpid() << endl;
    sleep(1);
  }
  return 0;
}
