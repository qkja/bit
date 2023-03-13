#define _CRT_SECURE_NO_WARNINGS 1

#include <string.h>
#include <iostream>
using namespace std;
//
//namespace bit
//{
//	template<class T>
//	struct list_node
//	{
//		list_node<T>* _next;
//		list_node<T>* _prev;
//		T _data;
//
//		list_node(const T& val = T())
//			:_next(nullptr)
//			, _prev(nullptr)
//			, _data(val) 
//		{}
//
//		list_node(T&& val)
//			:_next(nullptr)
//			, _prev(nullptr)
//			, _data(std::forward<T>(val))
//		{}
//	};
//
//
//	template<class T, class Ref, class Ptr>
//	struct __list_iterator
//	{
//		typedef list_node<T> Node;
//		typedef __list_iterator<T, Ref, Ptr> self;
//
//		typedef Ptr pointer;
//		typedef Ref reference;
//
//		Node* _node;
//
//		__list_iterator(Node* node)
//			:_node(node)
//		{}
//		Ref operator*()
//		{
//			return _node->_data;
//		}
//
//		Ptr operator->()
//		{
//			//return &(operator*());
//			return &_node->_data;
//		}
//
//		self& operator++()
//		{
//			_node = _node->_next;
//			return *this;
//		}
//
//		self operator++(int)
//		{
//			self tmp(*this);
//			_node = _node->_next;
//			return tmp;
//		}
//
//		self& operator--()
//		{
//			_node = _node->_prev;
//			return *this;
//		}
//
//		self operator--(int)
//		{
//			self tmp(*this);
//			_node = _node->_prev;
//			return tmp;
//		}
//
//
//		bool operator!=(const self& it)
//		{
//			return _node != it._node;
//		}
//
//		bool operator==(const self& it)
//		{
//			return _node == it._node;
//		}
//
//	};
//
//	template<typename T>
//	class list
//	{
//		typedef list_node<T> Node;
//	public:
//
//		typedef __list_iterator<T, T&, T*> iterator;
//		typedef __list_iterator<T, const T&, const T*> const_iterator;
//
//
//
//		iterator begin()
//		{
//			return iterator(_head->_next);
//		}
//
//		iterator end()
//		{
//			return iterator(_head);
//		}
//
//		list()
//		{
//			_head = new Node();
//			_head->_next = _head;
//			_head->_prev = _head;
//		}
//
//		void PushBack(T&& x)
//		{
//			//Insert(_head, x);
//			Insert(_head, std::forward<T>(x));
//		}
//		void PushFront(T&& x)
//		{
//			//Insert(_head->_next, x);
//			Insert(_head->_next, std::forward<T>(x));
//		}
//		void Insert(Node* pos, T&& x)
//		{
//			Node* prev = pos->_prev;
//			//Node* newnode = new Node;
//
//			//newnode->_data = std::forward<T>(x); // �ؼ�λ��
//			Node* newnode = new Node(std::forward<T>(x));
//			// prev newnode pos
//			prev->_next = newnode;
//			newnode->_prev = prev;
//			newnode->_next = pos;
//			pos->_prev = newnode;
//		}
//		void Insert(Node* pos, const T& x)
//		{
//			Node* prev = pos->_prev;
//			Node* newNode = new Node(x);
//
//			//Node* newnode = new Node;
//			//newnode->_data = x; // �ؼ�λ��
//			// prev newnode pos
//			prev->_next = newnode;
//			newnode->_prev = prev;
//			newnode->_next = pos;
//			pos->_prev = newnode;
//		}
//
//	/*	void push_back(const T& x)
//		{
//			insert(end(), x);
//		}
//*/
//		void push_back(T&& xx)
//		{
//			insert(end(), std::forward<T>(xx));
//			//insert(end(), xx);
//		}
//
//
//
//		//// ������posλ��֮ǰ
//		//iterator insert(iterator pos, const T& x)
//		//{
//
//		//	Node* newNode = new Node(x);
//		//	Node* cur = pos._node;
//		//	Node* prev = cur->_prev;
//
//		//	// prev  newnode  cur
//		//	prev->_next = newNode;
//		//	newNode->_prev = prev;
//		//	newNode->_next = cur;
//		//	cur->_prev = newNode;
//
//		//	return iterator(newNode);
//		//}
//
//		//iterator insert(iterator pos, T&& xx)
//		//{
//		//	Node* newNode = new Node(std::forward<T>(xx));
//		//	Node* cur = pos._node;
//		//	Node* prev = cur->_prev;
//
//		//	// prev  newnode  cur
//		//	prev->_next = newNode;
//		//	newNode->_prev = prev;
//		//	newNode->_next = cur;
//		//	cur->_prev = newNode;
//
//		//	return iterator(newNode);
//		//}
//
//	private:
//		Node* _head;
//	};
//}
//
//namespace bit
//{
//	class string
//	{
//	public:
//
//		string(const char* str = "")
//			:_size(strlen(str))
//			, _capacity(_size)
//		{
//			_str = new char[_capacity + 1];
//			strcpy(_str, str);
//		}
//		// ��������
//		string(const string& s)
//			:_str(nullptr)
//		{
//			cout << "string(const string& s) -- ���" << endl;
//			string tmp(s._str);
//			swap(tmp);
//		}
//		// �ƶ�����
//		string(string && s)
//			:_str(nullptr)
//			, _size(0)
//			, _capacity(0)
//		{
//			cout << "string(string&& s) -- �ƶ�����" << endl;
//			swap(s);
//		}
//		~string()
//		{
//			delete[] _str;
//			_str = nullptr;
//		}
//
//		void reserve(size_t n)
//		{
//			if (n > _capacity)
//			{
//				char* tmp = new char[n + 1];
//				strcpy(tmp, _str);
//				delete[] _str;
//				_str = tmp;
//				_capacity = n;
//			}
//		}
//		void push_back(char ch)
//		{
//			if (_size >= _capacity)
//			{
//				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
//				reserve(newcapacity);
//			}
//			_str[_size] = ch;
//			++_size;
//			_str[_size] = '\0';
//		}
//		string& operator+=(char ch)
//		{
//			push_back(ch);
//			return *this;
//		}
//	private:
//		void swap(string& s)
//		{
//			::swap(_str, s._str);
//			::swap(_size, s._size);
//			::swap(_capacity, s._capacity);
//		}
//	private:
//		char* _str;
//		size_t _size;
//		size_t _capacity; // �������������ʶ��\0
//	};
//
//	//���ʵ���ǲ��Ե�
//	bit::string to_string(int val)
//	{
//		bit::string str;
//		while (val > 0)
//		{
//			int x = val % 10;
//			val /= 10;
//			str += ('0' + x);
//		}
//		return str;
//	}
//}
//int main()
//{
//	bit::list<bit::string> lt;
//	bit::string s = "qqq";
//
//	lt.PushBack(s);
//	lt.PushBack("1111");
//	lt.PushFront("2222");
//	return 0;
//}
////int main()
////{
////	bit::list<bit::string> lt;
////	bit::string s1("1111");
////	// ������õ��ǿ�������
////	lt.push_back(s1);
////
////	// ������ö����ƶ�����
////	lt.push_back("2222");
////	lt.push_back(std::move(s1));
////
////	return 0;
////}
////
//
//
//
//
//
//
////void Fun(int& x)
////{
////	cout << "��ֵ����" << endl;
////}
////void Fun(const int& x)
////{
////	cout << "const ��ֵ����" << endl;
////}
////void Fun(int&& x)
////{
////	cout << "��ֵ����" << endl;
////}
////void Fun(const int&& x)
////{
////	cout << "const ��ֵ����" << endl;
////}
////template<typename T>
////void PerfectForward(T&& t)
////{
////	Fun(t);
////}
////int main()
////{
////	PerfectForward(10); // ��ֵ
////	int a;
////	PerfectForward(a); // ��ֵ
////	PerfectForward(std::move(a)); // ��ֵ
////	const int b = 8;
////	PerfectForward(b); // const ��ֵ
////	PerfectForward(std::move(b)); // const ��ֵ
////	return 0;
////}

#include <string>
//template <class T>
//int PrintArg(const T& t)
//{
//	cout << t << " ";
//	return 0;
//}
//template <class ...Args>
//void ShowList(Args... args)
//{
//	int arr[] = { (PrintArg(args), 0)... };
//	cout << endl;
//}

//int main()
//{
//	ShowList(1, 'x', 1.1, string("hello world"));
//	cout << endl;
//
//	ShowList(1, 2, 3, 4, 5);
//	return 0;
//}
//#include <list>
//
//int main()
//{
//	std::list< std::pair<int, char> > mylist;
//
//	mylist.emplace_back(10, 'a');
//	mylist.emplace_back(20, 'b');
//
//	std::pair<int, char> kv(100, 'x');
//
//	mylist.push_back({ 50, 'e' });
//
//	mylist.emplace_back(10, 'a');
//
//
//	for (auto e : mylist)
//		cout << e.first << ":" << e.second << endl;
//
//	return 0;
//}

#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;
//
//int main()
//{
//	int array[] = { 4, 1, 8, 5, 3, 7, 0, 9, 2, 6 };
//	std::sort(array, array + sizeof(array) / sizeof(array[0]), greater<int>());
//	for (auto& e : array)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//	return 0;
//}

#include <algorithm>
#include <functional>

//int main()
//{
//	// ��򵥵�lambda���ʽ, ��lambda���ʽû���κ�����
//	[]{};
//	// ʡ�Բ����б�ͷ���ֵ���ͣ�����ֵ�����ɱ������Ƶ�Ϊint
//	int a = 3, b = 4;
//	//[=]{return a + 3; };
//	//// ʡ���˷���ֵ���ͣ��޷���ֵ����
//	//auto fun1 = [&](int c){b = a + c; }; // a = 3 b = 3+c
//	//fun1(10);// a = 3 b = 13
//	//cout << a << " " << b << endl; // 3 13
//	//// �����ֶ������Ƶ�lambda����
//	//auto fun2 = [=, &b](int c)->int{return b += a + c; }; //a = 3 b=26
//	//cout << fun2(10) << endl;
//	// ���Ʋ�׽x
//	int x = 10;
//	auto add_x = [x](int a) mutable { x *= 2; return a + x; };
//	cout << add_x(10) << endl;
//	return 0;
//
//}
//void(*PF)();
//int main()
//{
//	auto f1 = []{cout << "hello world1" << endl; };
//	auto f2 = []{cout << "hello world2" << endl; };
//	// �˴��Ȳ�����ԭ�򣬵�lambda���ʽ�ײ�ʵ��ԭ����󣬴�Ҿ������
//	//f1 = f2; // ����ʧ��--->��ʾ�Ҳ���operator=()
//	// ����ʹ��һ��lambda���ʽ��������һ���µĸ���
//	auto f3(f2);
//	f3();
//	// ���Խ�lambda���ʽ��ֵ����ͬ���͵ĺ���ָ��
//	PF = f2;
//	PF();
//	return 0;
//}
//
//class Rate
//{
//public:
//	Rate(double rate) 
//		: _rate(rate)
//	{}
//	double operator()(double money, int year)
//	{
//		return money * _rate * year;
//	}
//private:
//	double _rate;
//};
//int main()
//{
//	// ��������
//	double rate = 0.49;
//	Rate r1(rate);
//	r1(10000, 2);
//	// lamber
//	auto r2 = [=](double monty, int year)->
//		double {return monty * rate * year;};
//	r2(10000, 2);
//	return 0;
//}
//int main()
//{
//	int ret = func();
//	return 0;
//}
//template <class F, class T>
//T useF(F f, T x)
//{
//	static int count = 0;
//	cout << "count:" << ++count << endl;
//	cout << "count:" << &count << endl;
//	return f(x);
//}
//double f(double i)
//{
//	return i / 2;
//}
//struct Functor
//{
//	double operator()(double d)
//	{
//		return d / 3;
//	}
//};
//int main()
//{
//	// ������
//	cout << useF(f, 11.11) << endl; // count:1 count:0025C140  5.555
//	// ��������
//	cout << useF(Functor(), 11.11) << endl; // count:1 count: 0025C144 3.70333
//	// lamber���ʽ
//	cout << useF([](double d) -> double
//	{ return d / 4; },
//	11.11)
//	<< endl; // count : 1 count: 0025C148 2.7775
//	return 0;
//}


//struct Goods
//{
//	string _name;
//	double _price;
//};
//struct Compare
//{
//	bool operator()(const Goods& gl, const Goods& gr)
//	{
//		return gl._price <= gr._price;
//	}
//};
//int main()
//{
//	Goods gds[] = { { "ƻ��", 2.1 }, { "�㽶", 3 }, { "����", 2.2 }, { "����",
//		1.5 } };
//	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), Compare());
//	return 0;
//}

// ���ۣ�auto_ptr��һ��ʧ����ƣ��ܶ๫˾��ȷҪ����ʹ��auto_ptr
//int main()
//{
// std::auto_ptr<int> sp1(new int);
// std::auto_ptr<int> sp2(sp1); // ����Ȩת��
//
// // sp1����
// *sp2 = 10;
// cout << *sp2 << endl;
// //cout << *sp1 << endl;
// return 0;
//}
#include <memory>

//using namespace std;

//int main()
//{
// /*bit::unique_ptr<int> sp1(new int);
// bit::unique_ptr<int> sp2(sp1);*/
//
//	std::unique_ptr<int> sp1(new int);
//	std::unique_ptr<int> sp2(sp1);
//
//	//sp1 = sp2;
// 
// //std::unique_ptr<int> sp2(sp1);
//
// return 0;
//}

//#include <mutex>
//
//namespace bit
//{
//	template<class T>
//	class shared_ptr
//	{
//	public:
//		///
//		shared_ptr(T* ptr = nullptr)
//			:_ptr(ptr)
//			, _pRefCount(new int(1))
//			, _pmtx(new mutex)
//		{}
//		// ��������
//		shared_ptr(const shared_ptr<T>& sp)
//			:_ptr(sp._ptr)
//			, _pRefCount(sp._pRefCount)
//			, _pmtx(sp._pmtx)
//		{
//			// ���ü���++
//			AddRef();
//		}
//		void AddRef()
//		{
//			_pmtx->lock();
//			++(*_pRefCount);
//			_pmtx->unlock();
//		}
//		// ��������
//		~shared_ptr()
//		{
//			Release();
//		}
//		void Release()
//		{
//			_pmtx->lock();
//			bool flag = false;
//			// ֻ�� �� ���ǵ����ü���--��0��ʱ��,��ʱ�������ͷſռ�
//			// ������Ǽ򵥵�--
//			if (--(*_pRefCount) == 0 && _ptr)
//			{
//				cout << "delete:" << _ptr << endl;
//				delete _ptr;
//				delete _pRefCount;
//				flag = true;
//			}
//			_pmtx->unlock();
//
//			if (flag == true)
//			{
//				delete _pmtx;
//			}
//		}
//
//		// ��������
//		// 
//		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
//		{
//			//if (this != &sp)
//			if (_ptr != sp._ptr)
//			{
//				// �Ͼ�����Ҫ����һ��ָ��,��Դ���ͷ��������ﲻ�ù���
//				Release();
//				//
//				_ptr = sp._ptr;
//				// ֱ�Ӹ�ֵ
//				_pRefCount = sp._pRefCount;
//				// �ı���
//				_pmtx = sp._pmtx;
//				AddRef();
//			}
//			return *this;
//		}
//
//		int use_count()
//		{
//			return *_pRefCount;
//		}
//	
//		// ��ָ��һ��ʹ��
//		T& operator*()
//		{
//			return *_ptr;
//		}
//		T* operator->()
//		{
//			return _ptr;
//		}
//		T* get() const
//		{
//			return _ptr;
//		}
//	private:
//		T* _ptr;
//		int* _pRefCount;
//		mutex* _pmtx;
//	};
//}
//
//int main()
//{
//	return 0;
//}

// �򻯰汾��weak_ptrʵ�� --  �����Ȳ�˵

//template<class T>
//class weak_ptr
//{
//public:
//	weak_ptr()
//		:_ptr(nullptr)
//	{}
//	weak_ptr(const shared_ptr<T>& sp)
//		:_ptr(sp.get())
//	{}
//	weak_ptr<T>& operator=(const shared_ptr<T>& sp)
//	{
//		_ptr = sp.get();
//		return *this;
//	}
//	T& operator*()
//	{
//		return *_ptr;
//	}
//	T* operator->()
//	{
//		return _ptr;
//	}
//private:
//	T* _ptr;
//};
//
//struct ListNode
//{
//	/*ListNode()
//	{
//
//	}*/
//	int _data;
//	bit::shared_ptr<ListNode> _prev =nullptr;  // ע�� 
//	bit::shared_ptr<ListNode> _next;
//	~ListNode(){ cout << "~ListNode()" << endl; }
//};
//int main()
//{
//	bit::shared_ptr<ListNode> node1(new ListNode);
//	bit::shared_ptr<ListNode> node2(new ListNode);
//	cout << node1.use_count() << endl;
//	cout << node2.use_count() << endl;
//	node1->_next = node2;
//	node2->_prev = node1;
//	cout << node1.use_count() << endl;
//	cout << node2.use_count() << endl;
//
//	//cout << node1->_next.use_count() << endl;
//	return 0;
//}

//int main()
//{
//	//ListNode* p = new ListNode;
//	bit::shared_ptr<ListNode> node1(new ListNode);
//
//	cout << node1->_next.use_count() << endl;
//	//cout << p->_next.use_count()<< endl; 
//	return 0;
//}




//
//int main()
//{
//	shared_ptr<ListNode> node1(new ListNode);
//	shared_ptr<ListNode> node2(new ListNode);
//
//	cout << node1.use_count() << endl;
//	cout << node1->_next.use_count() << endl;
//	/*cout << node2.use_count() << endl;
//	node1->_next = node2;
//	node2->_prev = node1;
//	cout << node1.use_count() << endl;
//	cout << node2.use_count() << endl;*/
//	return 0;
//}

//int main()
//{
//
//	return 0;
//}

// �º�����ɾ����
template<class T>
struct FreeFunc {
	void operator()(T* ptr)
	{
		cout << "free:" << ptr << endl;
		free(ptr);
	}
};
template<class T>
struct DeleteArrayFunc {
	void operator()(T* ptr)
	{
		cout << "delete[]" << ptr << endl;
		delete[] ptr;
	}
};
int main()
{
	FreeFunc<int> freeFunc;

	std::shared_ptr<int> sp1((int*)malloc(4), freeFunc);
	DeleteArrayFunc<int> deleteArrayFunc;
	std::shared_ptr<int> sp2((int*)malloc(4), deleteArrayFunc);
	//std::shared_ptr<A> sp4(new A[10], [](A* p){delete[] p; });
	std::shared_ptr<FILE> sp5(fopen("test.txt", "w"), [](FILE* p)
	{fclose(p); });
	return 0;
}