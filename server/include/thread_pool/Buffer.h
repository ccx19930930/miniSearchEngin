 ///
 /// @file    Buffer.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-15 21:06:51
 ///


#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "Mutex.h"
#include "Cond.h"
#include "Task.h"
#include "root/Noncopyable.h"

#include <deque>



namespace ccx{

using std::deque;

template <typename DATA>
class Buffer
: private Noncopyable
{
	friend class Thread_Pool;
	public:
		Buffer(int max);
		~Buffer();

		void Push(DATA);
		DATA Pop();
	
		int getNum();
	private:
		bool isFull();
		bool isEmpty();
	private:
		int _num;
		int _max;
		Mutex _mutex;
		Cond _NotEmpty;
		Cond _NotFull;
		deque<DATA> _TaskList;
};

}

#endif
