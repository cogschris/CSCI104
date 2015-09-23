#include <iostream>
#include "stackint.h"
#include <cstdlib>
#include <stdexcept>
using namespace std;

StackInt::StackInt()
{
	
}

StackInt::~StackInt()
{
	
}

bool StackInt::empty() const
{
	return list_.empty();
}

void StackInt::push(const int& val)
{
	list_.insert((list_.size()), val);
}

int const & StackInt::top() const
{
	return list_.get((list_.size() - 1));
}

void StackInt::pop()
{
	list_.remove((list_.size() - 1));
}

/*
int main() {
	StackInt test;

	test.push(5);
	test.push(4);
	test.push(3);

	cout << test.top() << endl;
	test.pop();
	cout << test.top() << endl;
	test.pop();
	cout << test.top() << endl;
	test.pop();
	cout << test.empty() << endl;

	return 0;
}
*/