#include <iostream>
namespace bit
{
  template<class T>
  class SmartPtr
  {
    public:
      SmartPtr(T* ptr)
        :_ptr(ptr)
      {
        // 这里我们给一个 打印函数
        //std::cout << "SmartPtr()" << std::endl;
      }

      T& operator*()
      {
        return *_ptr;
      }

      T* operator->()
      {
        return _ptr;
      }

      // 有些指针还会重载 []  这里等会再说
      ~SmartPtr()
      {
        //std::cout << "~SmartPtr()" << std::endl;
        //if(_ptr)
          delete _ptr; // 对于 多个自定义对象   等会在谈
        //_ptr = nullptr;
      }

    private:
      T* _ptr;
  };

  template<class T>
  class auto_ptr
  {
    public:
      auto_ptr(T* ptr = nullptr)
        :_ptr(ptr)
      {}

      // 拷贝构造 悬空
      auto_ptr(auto_ptr<T>& a)
      {
        _ptr = a._ptr;
        // 他给我悬空了
        a._ptr = nullptr;
      }

      // 赋值重载
      // 这里也有问题
      // 这里就不仔细谈
      auto_ptr<T>& operator=(auto_ptr<T>& a)
      {
        if(&a == this)
          return *this;
        free(_ptr);

        _ptr = a._ptr;
        // 他给我悬空了
        a._ptr = nullptr;

        // 注意放回置
        return *this;
      }

      T& operator*()
      {
        return *_ptr;
      }

      T* operator->()
      {
        return _ptr;
      }

      ~auto_ptr()
      {
          delete _ptr; // 对于 多个自定义对象   等会在谈
      }

    private:
      T* _ptr;
  };


  // 下面是 C++ 11 更新出来的
  // 我们重点看三个

  // 我们谈一下  boost
  // 这是一个 准标准库   里面可以看作一个使用
  // 现在不太谈了
 
  // boost scoped_ptr shared_ptr weak_ptr
  // c++11 unique_ptr shared_ptr weak_ptr
  
  
  template<class T>
  class unique_ptr
  {
    public:
      unique_ptr(T* ptr = nullptr)
        :_ptr(ptr)
      {}

      // 1 只声明 不实现  有老刘自己实现  这里 声明成 私有
      
      // 2 c++11 可以 使用 delete 
      unique_ptr(const unique_ptr<T>& u) =delete;
      unique_ptr operator=(const unique_ptr<T>& u) =delete;

      T& operator*()
      {
        return *_ptr;
      }

      T* operator->()
      {
        return _ptr;
      }

      ~unique_ptr()
      {
          delete _ptr; // 对于 多个自定义对象   等会在谈
      }
    private:
      T* _ptr;
  };


  // shared_ptr 
  template<class T>
  class shared_ptr
  {
    public:
      shared_ptr(T* ptr = nullptr)
        :_ptr(ptr)
         ,_pCount(new int)
      {
        *_pCount = 1;
      }

      shared_ptr(shared_ptr<T>& s)
      {
        _ptr = s._ptr;
        _pCount = s._pCount;
        (*_pCount)++;
      }

      shared_ptr<T>& operator=(shared_ptr<T>& s)
      {
        if(this == &s)
          return *this;
        if(_ptr == s._ptr)
          return *this;
        // 这个很 麻烦
        //我们要考虑情况
      
        if(*_pCount == 1)
        {
          delete _ptr;
          delete _pCount;
        }
        else 
        {
          (*_pCount)--;
        }

        _ptr = s._ptr;
        _pCount = s._pCount;
        (*_pCount)++;

        return *this;
      }

      T& operator*()
      {
        return *_ptr;
      }

      T* operator->()
      {
        return _ptr;
      }



      void Release()
		 {
       if (--(*_pCount) == 0 && _ptr)
		 	 {

         std::cout << "delete" << _ptr << std::endl;
				 delete _ptr;
				 _ptr = nullptr;

				 delete _pCount;
				 _pCount = nullptr;
			 }
		}
      ~shared_ptr()
		  {
		  	Release();
		  }

      /*~shared_ptr()
      {
        // 等到 剩下一个
        if(--(*_pCount) == 0 && _ptr)
        {
         delete _ptr; // 对于 多个自定义对象   等会在谈
         delete _pCount;
        }
      }*/

    private:
      T* _ptr;
      int* _pCount;
  };

}

