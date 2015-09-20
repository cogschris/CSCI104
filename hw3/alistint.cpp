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
	for (int i = 0; i < other.size(); i++) {
		_data[i] = other._data[i];
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

int& AListInt::get(int position) const
{
	if (position < _size && position >= 0) {
		return _data[position];
	}
	return;
}

int const & AListInt::get(int position) const
{
	if (position < _size && position >= 0) {
		return _data[position];
	}
	return;
}

int& AListInt::operator+(const AListInt& other) const
{
	int new temp[_size];
	temp = _data;
	int bigger = _size + other._size()
	int i = _size;
	while (_cap < bigger) {
		resize();
	}
	while (i < bigger) {
		_data[i] = other[i - _size];
	}

	_size = bigger;
}

int const & AListInt::operator[](int positon) const
{
	return _data[positon];
}

int& AListInt::operator[](int position)
{
	return _data[position];
}


void AListInt::resize()
{
	new temp[cap];
	_cap = _cap * 2;
	delete[] _data;
	new _data[cap] = temp;
	delete[] temp;
}