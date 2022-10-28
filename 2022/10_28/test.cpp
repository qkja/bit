#include <iostream>
// 隐式
// 显式
using namespace std;

//int main()
//{
//  // 没人用
//  // 可读性 提升
//  // 出错概率降低
//  //
//  return 0;
//}



//int main()
//{
  //const char* s = "abcd";
  //char* s = "abcd";
  //char* p = s;
  //cout << p << endl;
  //cout << s << endl;

  //const int a =10;
  //int b = 10;
  //cout << a << " " << b << endl;
  //return 0;
//}


///////////////////////////////////////////////////////////////// 
// 单例模式

// 设计一个类  不能被拷贝
// C++98   之声明不实现   老刘会自己实现  这里声明成 私有   线程 锁  unique_ptr istream ostream -- 类内可以使用 
// C++11   delete 

// 只能在 堆上创建对象
// new  delete  
// new 里面 可以需要构造函数
//class HeapOnly
//{
//
//  // 第一步 把  构造给封了
//  private:
//    HeapOnly()
//    {};
//
//  public:
//  // 想一想如何 开new 这个口
//    static HeapOnly* CreateObj()
//    {
//      return new HeapOnly;
//    }
//
//    // 又存在了破绽  --   这里拷贝构造  赋值重载
//    //operator=() 注意 赋值重载的前提前提是要有 对象
//    //这里不用 考虑了
//    //我们只需要把防拷贝就可以了
//    // 这里来一个新玩法  不需要写形参名字
//    HeapOnly(const HeapOnly&) = delete;
//
//};

//int main()
//{
//  // 全局区   
//  // 栈
//  // 堆
//  // 这里得到成员函数必须要要有对象  这里就需要static
//  // 或者使用下面的方法
//  //HeapOnly* ptr = nullptr;
//  //HeapOnly* p1 = ptr->CreateObj();
//
//  //cout << p1 << endl;
//  //cout << p2 << endl;
//  //delete p1;
//  return 0;
//}


// 这还有一种玩法  --  析构函数私有
// 如何解决   -- 这里不能自己detect 内存泄漏 
// 只能在栈上创建

//class StackOnly
//{
//
//  // 第一步 把  构造给封了
//  private:
//    StackOnly()
//    {};
//
//  public:
//  // 想一想如何 开new 这个口
//  //StackOnly(const StackOnly&) = delete;
//  // 或者禁止 operato new 这里有一个缺陷 没有禁止干净
//  // 那么 我们这个方法是如何禁止静态的
//  static StackOnly CreateObj()
//  {
//    return StackOnly();
//  }
//};
//
//
//int main()
//{
//  static StackOnly s = StackOnly::CreateObj();
//  cout << &s << endl;
//  return 0;
//}
//


// 只是一种思维方式

// 不能被继承的类
// 构造函数私有化    -- 不可见   什么叫不可见
// final 

// 不可见 是在子类中可以调用吗   
// 单例模式  全局(进程)只能有一个实例对象
// 大思路 构造函数私有化  创建一个函数
// getInstance  把 拷贝也给放掉


// 懒汉模式

//class Singleton
//{
//public:
//  // 饿汉模式
//  // 一上来就要吃
//  // 卖弄函数之前需要做的准备工作
//  static Singleton* GetInstance()
//  {
//    // 如何得到这个对象
//    return _spInst;
//  }
//  void print()
//  {
//    cout << "写文件" << endl;
//  }
//    // 还放不住拷贝
//    Singleton(const Singleton&) = delete;
//    Singleton& operator=(const Singleton&) = delete;
//private:
//    Singleton()
//    {}
//    int _a;
//    //static Singleton sInst;  // 创建一个静态对象
//    static Singleton* _spInst;  // 创建一个静态对象
//    // 只是收到类域的限制  生命周期没有限制
//
//    // 有没有什么好的方式可以初始化一下
//    // 饿汉模式很不好解决
//};
//// 为何没有声明定义到全局   -- 这是由于构造函数私有
//Singleton* Singleton::_spInst = new Singleton;
//
//int main()
//{
//
//  Singleton::GetInstance()->print();
//  return 0;
//}

////////////////////////////
//上面太太谈报了


// InfoMgr -- 单例
/*class InfoMgr
{
public:
	static InfoMgr* GetInstance()
	{
		return _spInst;
	}

	void SetAddress(const string& s)
	{
		_address = s;
	}

	string& GetAddress()
	{
		return _address;
	}

private:
	InfoMgr()
	{}

	InfoMgr(const InfoMgr&) = delete;

	string _address;
	int _secretKey;

	static InfoMgr* _spInst; // 声明
};

InfoMgr* InfoMgr::_spInst = new InfoMgr; // 定义

int main()
{
	//InfoMgr info1;
	//static InfoMgr info2;
	//InfoMgr info3;

	// 全局只有一个InfoMgr对象
	InfoMgr::GetInstance()->SetAddress("陕西省西安市雁塔区");

	cout << InfoMgr::GetInstance()->GetAddress() << endl;

	return 0;
}*/

// 饿汉模式

// InfoMgr -- 单例
class InfoMgr
{
public:
	static InfoMgr* GetInstance()
	{
    // 害需要加索  这个后面谈
    if(_spInst == nullptr)
      _spInst = new InfoMgr;

		return _spInst;
	}

	void SetAddress(const string& s)
	{
		_address = s;
	}

	string& GetAddress()
	{
		return _address;
	}

private:
	InfoMgr()
	{}

	InfoMgr(const InfoMgr&) = delete;

	string _address;
	int _secretKey;

	static InfoMgr* _spInst; // 声明
};

InfoMgr* InfoMgr::_spInst = nullptr; // 定义

int main()
{
	//InfoMgr info1;
	//static InfoMgr info2;
	//InfoMgr info3;

	// 全局只有一个InfoMgr对象
	InfoMgr::GetInstance()->SetAddress("陕西省西安市雁塔区");

	cout << InfoMgr::GetInstance()->GetAddress() << endl;

	return 0;
}

class A final
{

};


class B
{
public:
  B()
  {};
private:
  B(const B&) = delete;
};

// 两者的区别  饿汉在加载一直满 可以理解为黑屏
// 懒汉 



// 不考虑析构
// 析构的时候  可能会写文件
//


