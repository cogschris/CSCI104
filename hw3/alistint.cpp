#include <iostream>
#include "alistint.h"
#include <cstdlib>
#include <stdexcept>

using namespace std;

AListInt::AListInt()
{
	_size = 0;
	_cap = 5;
	_data = new int[5];
}

AListInt::AListInt(int cap) 
{
	_size = 0;
	_cap = cap;
	_data = new int[cap];
}

AListInt::AListInt(const AListInt& other)
{
	_cap = other._cap;
	_size = other._size;
	_data = new int[_cap];	
	for (unsigned int i = 0; i < _size; i++) {

		_data[i] = other._data[i];
	}
	
}


/////work on this!!
AListInt& AListInt::operator=(const AListInt& other)
{
	delete[] _data;
	_cap = other._cap;
	_size = other._size;
	_data = new int[_cap];	
	for (unsigned int i = 0; i < _size; i++) {

		_data[i] = other._data[i];
	}

	return *this;
}

AListInt::~AListInt()
{
	delete[] _data;
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
	if ((unsigned int)(pos) <= (_size) && pos >= 0) {	
		if ((_size) + 1 > (_cap)) {
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
	if ((unsigned int)(pos) < _size && pos >= 0) {
		for (int i = pos; i < (int)(_size) - 1; i++) {
			_data[i] = _data[i+1];
		}

		//unsigned int temp = (int)(_size) - 1;
		//delete _data[temp];
		if (_size != 0) {
			_size--;
		}
	}
}

void AListInt::set(int pos, const int& val) 
{
	if ((unsigned int)(pos) < _size && pos >= 0) {
		_data[pos] = val;
	}
}

int& AListInt::get(int position)
{
	if ((unsigned int)(position) < _size && position >= 0) {
		return _data[position];
	}
	return _data[0];
}

int const & AListInt::get(int position) const
{
	if ((unsigned int)(position) < _size && position >= 0) {
		return _data[position];
	}
	return _data[0];
}

AListInt AListInt::operator+(const AListInt& other) const
{
	unsigned int size = _size + other._size;
	AListInt temp(size);
	
	temp._size = size;
	//temp._data = _data;
	int i = 0;
	//int size = _size + other._size;
	while ((unsigned int)(i) < _size) {
		temp._data[i] = _data[i];
		i++;
	}
	

	while ((unsigned int)(i) < size) {
		temp[i] = other[i - _size];
		i++;
	}

	//_size = (unsigned int)(bigger);

	return temp;
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
	int* temp = new int[_size];
	
	_cap = _cap * 2;
	for (unsigned int i = 0; i < _size; i++) {
		temp[i] = _data[i];
	}
	delete[] _data;
	_data = new int[_cap];

	for (unsigned int i = 0; i < _size; i++) {
		_data[i] = temp[i];
	}

	delete[] temp;
	
}
/*
int main() {
	
	AListInt list;
	AListInt cool;

	list.insert(0, 5);
	list.insert(0, 4);

	//cout << "list.get(0) " << list.get(0) << endl << "list.get(1) " << list.get(1) << endl;

	list.insert(2, 1);
	

	list.insert(3, 1);
	
	list.insert(2, 3);
	
	list.insert(5, 6);
	

	//cout << list.get(5) << endl;

	cout << list.get(0) << " " << list.get(1) << endl;
	list.remove(0);
	cout << list.get(0) << endl;

	cool.insert(0, 1);
	cool.insert(1, 8);

	AListInt darn;
	darn = list + cool;
	cout << darn.get(5) << " " << darn.get(6) << endl;


} */