 ///
 /// @file    thread_pool.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-16 17:10:14
 ///


#include "thread_pool/Thread_pool.h"

#include <unistd.h>
#include <functional>

namespace ccx{

using std::bind;

Thread_Pool::Thread_Pool(const int pthread_num, const int task_num)
: _pthread_num(pthread_num)
, _task_num(task_num)
, _task_list(_task_num)
, _isrunning(false)
, _isExit(false)
{
}

Thread_Pool::~Thread_Pool()
{
	stop();
}

void Thread_Pool::start()
{
	for(int i = 0; i < _pthread_num; ++i)
	{
		shared_ptr<Pthread> p(new Pthread(bind(&Thread_Pool::function, this)));
		p->start();
		_pthread.push_back(p);
	}
	_isrunning = true;
}


void Thread_Pool::stop()
{
	while(!_task_list.isEmpty())
	{
		_task_list._NotFull.wait();
	}
	_isExit = true;
	if(_isrunning)
	{
		for(int i = 0; i < _pthread_num; ++i)
		{
	//		_pthread[i]->stop();
			_pthread[i]->join();
		}
	}
}

void Thread_Pool::recvTask(DATA data)
{
	_task_list.Push(data);
}

DATA Thread_Pool::getTask()
{
	return _task_list.Pop();	
}

void Thread_Pool::function()
{
	while(!_isExit)
	{
		DATA task = getTask(); 
		if(task)
		{
			task();
		}
		cout << pthread_self() << " ----->> Mission reporter : success!" << endl;
	}
}

bool Thread_Pool::taskFull()
{
	return _task_list.getNum() == _task_num;
}




}
