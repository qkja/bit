#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Date
{
 friend ostream& operator << (ostream& out, const Date& d);
 friend istream& operator >> (istream& in, Date& d);
public:
 Date(int year = 1, int month = 1, int day = 1)
 :_year(year)
 , _month(month)
 , _day(day)
 {}
 operator bool()
 {
        // 这里是随意写的，假设输入_year为0，则结束
 if (_year == 0)
 return false;
 else
 return true;
 }
private:
 int _year;
 int _month;
 int _day;
};
istream& operator >> (istream& in, Date& d)
{
 in >> d._year >> d._month >> d._day;
 return in;
}
ostream& operator << (ostream& out, const Date& d)
{
 out << d._year << " " << d._month <<" "<< d._day ;
 return out;
}

struct ChatInfo
{
 string _name; // 名字
 int _id;      // id
 Date _date;   // 时间
 string _msg;  // 聊天信息
};

int main()
{
 // 结构信息序列化为字符串
 ChatInfo winfo = { "张三", 135246, { 2022, 4, 10 }, "晚上一起看电影吧"};
 
 ostringstream oss; // 字符串

 oss << winfo._name << " " << winfo._id << " " << winfo._date << " "
 << winfo._msg;
 
 // 拿到字符串
 string str = oss.str();
 
 cout << str << endl<<endl;
 // 我们通过网络这个字符串发送给对象，实际开发中，信息相对更复杂，
    // 一般会选用Json、xml等方式进行更好的支持
 // 字符串解析成结构信息
 ChatInfo rInfo;
 istringstream iss(str);
 iss >> rInfo._name >> rInfo._id >> rInfo._date >> rInfo._msg;

 cout << "-------------------------------------------------------"<< endl;
 cout << "姓名：" << rInfo._name << "(" << rInfo._id << ") ";
 cout << rInfo._date << endl;
 cout << rInfo._name << ":>" << rInfo._msg << endl;
 cout << "-------------------------------------------------------"<< endl;
 return 0;
 }























// 这里我们了解 会用就可以了
// 我们需要抱一个头文件
//#include <stringstream> 下面的是为了简写  下面的是对的用法
// 这里序列化和反序列化 很少用
// 序列化   类型   - > 字符串
// 反序列化 字符串 - > 原本的类型
// 网路里面要用
//int main()
//{
//
//  int i = 10;
//  double d = 10.11;
//  ostringstream oss;
//  oss << i; // 转字符串
//
//
//  string stri = oss.str();
//  oss << d; //这里是追加
//  string strd = oss.str();
//
//  //如果我不想连在一起 clear 不行 使用  
//  //如果请不掉 只能用一个定义一个对象  这里还不如 stoi to_string 这些方法
//  // 这里 可以  oss.str("") 这里是获取里面的字符串 这里清空
//  // 这里的价值 是下面的
//  // 把自定义类型转成字符串
//  ostringstream ossDate;
//  //Date d1(100,12,20);
//  //ossDate << d1;// 这里调用流插入
//  
//
//  istringstream iss;
//  // 转成整型
//  // 这里最好 的还是 转换成自定义
//  // 本质没变
//  
//  return 0;
//}

//class Date
//{
// friend ostream& operator << (ostream& out, const Date& d);
// friend istream& operator >> (istream& in, Date& d);
//public:
// Date(int year = 1, int month = 1, int day = 1)
// :_year(year)
// , _month(month)
// , _day(day)
// {}
// operator bool()
// {
//        // 这里是随意写的，假设输入_year为0，则结束
// if (_year == 0)
// return false;
// else
// return true;
// }
//private:
// int _year;
// int _month;
// int _day;
//};
//istream& operator >> (istream& in, Date& d)
//{
// in >> d._year >> d._month >> d._day;
// return in;
//}
//ostream& operator << (ostream& out, const Date& d)
//{
// out << d._year << " " << d._month <<" "<< d._day ;
// return out;
//}
//
//struct ServerInfo
//{
// // 这里我们为何不用 string
// // 我们需要明白string的本质
// // 这里是一个简单的自定类型
// // 里面包含的就是几个指针
// char _address[256];
// int _port;
// Date _date;
//};
//
//struct ConfigManager
//{
//public:
// ConfigManager(const char* filename)
//  :_filename(filename)
//   {}
// /*void WriteBin(const ServerInfo& info)
// {
//   // 这里是打开一个文件 一些的方式打开  
//   // 这里好像设计到标志位 这里到 Linux 中寻找
//   ofstream ofs(_filename.c_str(), ios_base::out | ios_base::binary);
//   //这里看读写的空间和读写的字节 
//   //算是值拷贝
//   // 这里为何是 char* 类型  关键是我想是什么类型
//   // 解引用这里得到一个字符 也就是一个字节  很不错  
//   // 不过我们需要具体看一下原理
//   ofs.write((const char*)&info, sizeof(info));
// }*/
//
// //void ReadBin(ServerInfo& info)
// //{
// // ifstream ifs(_filename, ios_base::in | ios_base::binary);
// // ifs.read((char*)&info, sizeof(info));
// //}
//
// //文本读写
// void WriteText(const ServerInfo& info)
// {
//  // 这里应该是默认的
//  ofstream ofs(_filename.c_str());
//  //这里我们怎办 C语言 只有一种方式转成字符串
//  //C++里面的 重载了类型 
//  //这里我们用string也可以   调用string <<的东西
//  //子类调用父类的
//  //这注意这里复用
//  //ofs << string 
//  // 这里解释一下  ofs 是子类调用父类的<< 父类调用 隐藏 (重定义)
//  // 弗雷就和 cout << string 这里看作函数重载
//  // 至于是否涉及到多态 这里先不考虑
//  // 这里为何会加上空格 为度做准备
//  ofs << info._address << " " << info._port<< " "<< info._date;
// }
//
//
//
// void ReadText(ServerInfo& info)
// {
//  ifstream ifs(_filename);
//  // 读的时候遇到空格结束
//  ifs >> info._address >> info._port>>info._date;
// }
//
//private:
// string _filename; // 配置文件
//};
//
//int main()
//{
//
// ServerInfo winfo = { "192.0.0.1", 80, { 2022, 4, 10 } };
// ConfigManager cf_bin("test.txt");
// // 二进制读写
// //cf_bin.WriteBin(winfo);
// 
// // 文本的写 
// cf_bin.WriteText(winfo);
//
// //这里我们想要都一下.用个空类
// ServerInfo readfo;
// cf_bin.ReadText(readfo);
//
// printf("%s\n",readfo._address);
// printf("%d\n",readfo._port);
// cout << readfo._date << endl;
// return 0;
//}

//如何把自定类型写道文件中
//一个是二进制
//一个是文本
//二进制  数字补码
//指针  指向的空间 后i面程序读写野指针
//文本读写 可以很好的看见

//这里可以取放

//int main()
//{
//	string str;
//  int i = 0;
//	while (cin >> str)
//	{
//		cout << str << (++i) << endl;
//	}
//
//	return 0;
//}
