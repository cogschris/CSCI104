#include "stackint.h"

StackInt::StackInt()
{
	list_.AListInt();
}

StackInt::~StackInt()
{
	list_.clear();
}

bool StackInt::empty() const;
{
	return list_.empty();
}

void StackInt::push(const int& val)
{
	list_.insert(0, val);
}

int const & StackInt::top() const
{
	list_.get(0);
}

void StackInt::pop()
{
	list_.remove(0);
}