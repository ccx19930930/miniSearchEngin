 /// /// @file    thread_pool.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-16 16:54:12
 ///


#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "Pthread.h"
#include "Task.h"
#include "../../src/thread_pool/Buffer.cc"
#include "root/Noncopyable.h"


#include <vector>
#include <memory>


namespace ccx{

using std::vector;
using std::shared_ptr;

typedef Task DATA;

class Thread_Pool
: private Noncopyable
{
	friend class Worker;
	public:
		Thread_Pool(const int pthread_num, const int task_num);
		~Thread_Pool();
		void start();
		void stop();
		void recvTask(DATA data);
		void function();
		bool taskFull();
	private:
		DATA getTask();
		int _pthread_num;
		int _task_num;
		vector<shared_ptr<Pthread> > _pthread;
		Buffer<DATA> _task_list;
		bool _isrunning;
		bool _isExit;
};



}







#endif
