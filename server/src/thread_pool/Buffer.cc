 ///
 /// @file    Buffer.cc
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-15 22:44:45
 ///


#include "thread_pool/Buffer.h"
#include "thread_pool/safeMutex.h"

#include <iostream>

namespace ccx{

using std::cout;
using std::endl;


template <typename DATA>
Buffer<DATA>::Buffer(int max)
: _num(0)
, _max(max)
, _mutex()
, _NotEmpty(_mutex)
, _NotFull(_mutex)
{
}

template <typename DATA>
Buffer<DATA>::~Buffer()
{
}

template <typename DATA>
bool Buffer<DATA>::isFull()
{
	return _max == _num;
}

template <typename DATA>
bool Buffer<DATA>::isEmpty()
{
	return 0 == _num;
}

template <typename DATA>
int Buffer<DATA>::getNum()
{
	return _num;
}

template <typename DATA>
void Buffer<DATA>::Push(DATA goods)
{
	safeMutex mutex(_mutex);
	while(isFull())
	{
		cout << pthread_self() << " =====>>  Purchase waiting... " << endl;
		_NotFull.wait();
	}
	_TaskList.push_back(goods);
	++_num;
	if(isFull())
	{
		_NotEmpty.notifyall();
	}else{
		_NotEmpty.notify();
	}
}

template <typename DATA>
DATA Buffer<DATA>::Pop()
{
	safeMutex mutex(_mutex);
	while(isEmpty())
	{
		cout << pthread_self() << " =====>>  Shipment waiting... " << endl;
		_NotEmpty.wait();
	}
	DATA temp = _TaskList.front();
	_TaskList.pop_front();
	--_num;
	if(isEmpty())
	{
		_NotFull.notifyall();
	}else{
		_NotFull.notify();
	}
	return temp;
}


}
