/**
 * Author       : Qkj
 * Description  : 线程控制
 * Date         : 2022-11-24 22:50:06
 * LastEditTime : 2022-11-25 14:00:40
 */
// linux 是存在线程的,只不过我们不谈    
// 里面都是什么东西  是寄存器
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

// 线程同步
// 线程互斥是对的,但是它合理吗(在任何地方)
// 食堂大妈给优先级更高的打饭,这里合理吗   你抢到是你的  你只能饿死
// 食堂大妈错了吗, 但是这里不合理
// 图书馆的自习室只能一个人, 有一个钥匙,可以打开,你很早就跑过了
// 你人不在把钥匙拿走了,别人进不去,这里合理吗   
// 不能颓废,你坚持,其他人都在等者,你的速度快,又把钥匙拿了出来,别人不揍死你
// 互斥是对的,但是不一定合理   这会导致饥饿问题      记住这个是有可能
// 我要加一个游戏规则,只要你进去了,可以,我们不打扰,但是你出来了,好了,去后面排队
// 等待其他人用过之后,才轮到你   这个特性叫做  同步
// 早保证临界资源安全的前体下,让线程访问某种资源具有一个的顺序性
// 互斥保证安全
// 同步保证顺序(不一定互斥)
//
// 为何    1. 防止饥饿 2. 线程协同:w





//// 一把锁会不会有死锁问题  -- 有的  脑子抽了,自己也会把自己绊倒
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//int cnt = 100;
//
//void *startRoutine(void *args)
//{
//  string str = (char *)args;
//  while (true)
//  {
//    //pthread_mutex_lock(&mutex);
//    pthread_mutex_lock(&mutex);
//    cout << "count: " << cnt-- << endl;
//    pthread_mutex_unlock(&mutex);
//    sleep(1);
//  }
//}
//
//int main()
//{
//  pthread_t tid;
//  pthread_create(&tid, nullptr, startRoutine, (void *)"thread");
//
//  pthread_join(tid, nullptr);
//  return 0;
//}

// int main()
// {
//   //int *p = new int();
//   int *p = new int;
//   *p = 10;
//   cout << p << "  " << *p << endl;
//   delete p;
//   p = nullptr;
//   return 0;
// }
// 互斥锁的原理

// 1. 加锁 == 不会切换?  --> 完全可以
// 即使我窃走了,也不有其他线程访问临界区  它是被枷锁了,其他线程只能等待锁被打开
// 必须先申请锁   它是抱着这个锁走的 江湖仍旧有哥的传说
// 一旦一个线程持有了锁,该线程根本就不担心任何的切换问题

// 2. 细化接口    这个 了解一下  但是要写

// 线程同步  --> 条件变量

// int a = 0;
// int tickets = 10000; // 抢票
// void *getTickets(void *args)
// {
//   const char *name = (char *)args;
//   while (true)
//   {
//     // a++;
//     if (tickets > 0) // 这里面有问题
//     {
//       usleep(1000); // 微妙

//       // 抢票
//       cout << name << "  抢到了票, 票号是 " << tickets << endl;
//       tickets--;
//       //等下给他加锁
//       // a++;
//     }
//     else
//     {
//       cout << name << "  没抢到了票 " << endl;
//       break;
//     }
//   }
//   return nullptr;
// }

// int main()
// {
//   pthread_t tid1 = 0;
//   pthread_t tid2 = 0;
//   pthread_t tid3 = 0;
//   pthread_t tid4 = 0;

//   pthread_create(&tid1, nullptr, getTickets, (void *)"thread1");
//   pthread_create(&tid2, nullptr, getTickets, (void *)"thread2");
//   pthread_create(&tid3, nullptr, getTickets, (void *)"thread3");
//   pthread_create(&tid4, nullptr, getTickets, (void *)"thread4");

//   pthread_join(tid1, nullptr);
//   pthread_join(tid2, nullptr);
//   pthread_join(tid3, nullptr);
//   pthread_join(tid4, nullptr);
//   cout << "抢票完成" << endl;
//   // cout << a<<endl;
//   return 0;
// }

// void* callback(void* argc)
// {
// }

// int main()
// {
//   pthread_t tid=0;
//   // 这个就是一个地址
//   pthread_create(&tid, nullptr, callback, (void*)"thread");

//   // 上面说了  线程有自己的  东西
//   // 那么pcb
//   // 这个是   join出来的   他就像是malloc出来的空间
//   // 还是没有谈   pthread_t
//   // 我们要不要加载动态库到内存里面呢
//   return 0;
// }

// int main()
// {
//   // 创建
//   // 使用
//   // 等待
//   // tid 非常大 这个究竟是什么  -- 暂时放着    格式打印 16进制

//   // 什么叫做获取线程id,他和那个参数有关
//   return 0;
// }

// 线程分离

/////////////////////////////////////////////////

// 锁的原理 是如何实现的  这里我们谈最常规的
// 二进制级别的 一条语句  就是原子性语句
// 不同的体系结构(芯片结构) 给了我们几个指令  这个指令 一条汇编可以把数据和内存与CPU做交换
// 凡是在寄存器中的数据,都是线程内部上下文,多个线程看起来同时访问,但是互不影响.

// 寄存器是被所有线程共享的,但是数据是私有的

// 交换这个动作就叫做加锁      一条语句

// > 0 就是申请成功了

// B来的时候.A去哪了    必须被剥离下去      拨走需要把你的上下文拿走

// 这里是暂时听懂的

// 1这个就像是  令牌一般
//
