 ///
 /// @file    Noncopyable.h
 /// @author  chinxi(chenchengxi993@gmail.com)
 /// @date    2016-11-20 11:29:43
 ///

#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__

namespace ccx{

class Noncopyable
{
	protected:
		Noncopyable(){}
		~Noncopyable(){}
	private:
		Noncopyable & operator=(Noncopyable &);
		Noncopyable(Noncopyable &);
};

}

#endif
