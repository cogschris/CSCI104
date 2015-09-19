#include "alistint.h"


AListInt::AListInt()
{
	_size = 0;
	_cap = 5;
	*_data[5];
}

AListInt::AListInt(int cap) 
{
	_size = 0;
	_cap = cap;
}

AListInt::AListInt(const AListInt& other)
{
	for (int i =0; i < _size; i++) {
		other[i] = _data[i];
	}
}


/////work on this!!
AListInt::AListInt& operator=(const AListInt& other)
{
	if (this != &other) {
		if (_cap >= other._cap()) {
			delete[] _data;

		}
	}
}

AListInt::~AListInt()
{
	clear();
}

int AListInt::size() const
{
	return _size;
}

bool AListInt::empty() const
{
	if (_size == 0) {
		return true;
	}
	return false;
}

void AListInt::insert(int pos, const int& val)
{
	if (pos <= size && pos >= 0) {	
		if (_size + 1 > _cap) {
			resize();
		}

		for (int i = _size - 1; i >= pos; i--) {
			_data[i + 1] = _data[i];
		}

		_data[pos] = val;
		_size++;
	}
}

void AListInt::remove(int pos)
{
	if (pos < _size && pos >= 0) {
		for (int i = pos; i < _size - 1; i++) {
			_data[i] = _data[i+1];
		}

		_data[_size-1] = NULL;
		_size--;
	}
}

void AListInt::set(int pos, const int& val) 
{
	if (pos < _size && pos >= 0) {
		_data[pos] = val;
	}
}

int AListInt::get(int position) const
{
	if (position < _size && position >= 0) {
		return _data[position];
	}
	return;
}


