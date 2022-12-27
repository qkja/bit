#include <iostream>
class Task
{
public:
  Task(/* args */)
      : _oneElem(0), _twoElem(0), _operator('0')
  {
  }

  Task(int one, int two, char op)
      : _oneElem(one), _twoElem(two), _operator(op)
  {
  }

  int run()
  {
    int result = 0;
    switch (_operator)
    {
    case '+':
      result = _oneElem + _twoElem;
      break;
    case '-':
      result = _oneElem - _twoElem;
      break;
    case '*':
      result = _oneElem * _twoElem;
      break;
    case '/':
    {
      if (_twoElem == 0)
      {
        std::cout << "div zero, abort" << std::endl;
        result = -1;
      }
      else
      {
        result = _oneElem / _twoElem;
      }
    }
    break;
    case '%':
    {
      if (_twoElem == 0)
      {
        std::cout << "mod zero, abort" << std::endl;
        result = -1;
      }
      else
      {
        result = _oneElem % _twoElem;
      }
    }
    break;
    default:
      break;
    }
    return result;
  }

  int operator()()
  {
    return run();
  }

  void get(int *one, int *two, char *op)
  {
    *one = _oneElem;
    *two = _twoElem;
    *op = _operator;
  }

private:
  int _oneElem;
  int _twoElem;
  char _operator;
};
