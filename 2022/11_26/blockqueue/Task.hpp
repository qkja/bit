#ifndef __TASK_HPP__
#define __TASK_HPP__

#endif

class Task
{
public:
  Task()
      : _elemOne(0), _elemTwo(0), _operator('0')
  {
  }
  Task(int one, int two, char op)
      : _elemOne(one), _elemTwo(two), _operator(op)
  {
  }
  int run()
  {
    int resut = 0;
    switch (_operator)
    {
    case '+':
      break;
    case '-':
      break;
    case '-':
      break;
    case:
      break;
    case:
      break;
    default:
      break;
    }
  }

private:
  int _elemOne;
  int _elemTwo;
  int _operator;
};
