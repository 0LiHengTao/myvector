#pragma once
#include<iostream>
#include<cassert>
#include<memory>
using namespace std;

template<class T>
class MyVector
{
public:
	typedef T* iterator;//可对对象内容进行读写操作
	//typedef T* const_iterator;  只能对对象内容进行读操作

	//构造函数
	MyVector();

	//析构函数
	~MyVector();

	//拷贝构造函数
	MyVector(const MyVector& vec);

	//赋值运算符重载函数
	MyVector& operator=(const MyVector& vec);

	//[]运算符重载函数（用于取出vector实例化对象的第index个元素)
	T& operator[](size_t index);

	//==运算符重载函数（用于判断两个vector对象是否相同）
	bool operator==(const MyVector& vec)const;

	//向实例化对象增添元素
	void push_back(const T& val);

	//删除实例化对象的最后一个元素
	void pop_back();

	//向vector实例化对象的it位置插入一个元素
	iterator insert(iterator it, const T& val);

	//删除vector实例化对象it位置的元素
	iterator erase(iterator it);

	//取出vector对象中的第一个元素
	T front()const;

	//取出vector对象中的最后一个元素
	T back()const;

	//获取vector实例化对象的首地址
	iterator begin();

	//获取vector实例化对象的最后一个元素的地址
	iterator end();

	//获取vector实例化对象的元素个数
	size_t size()const;
	size_t capacity()const;

	//判断vector实例化对象是否为空
	bool empty();

	//交换两容器对象
	void swap(MyVector& v);

	//开空间
	void reserve(size_t n);

private:
	iterator _start;//头指针
	iterator _last;//尾指针
	iterator _endofstorage;//最多能存储的尾位置（容器大小）

};

template<class T>
MyVector<T>::MyVector()
{
	//均为空指针
	this->_start = nullptr;
	this->_last = nullptr;
	this->_endofstorage = nullptr;
}

template<class T>
MyVector<T>::~MyVector()
{
	delete[] _start;
	_start = nullptr;
	_last = nullptr;
	_endofstorage = nullptr;
}

template<class T>
void MyVector<T>::swap(MyVector& v)
{
	std::swap(this->_start, v._start);//利用std::swap()函数交换地址,同时获取容器的大小和容量信息
	std::swap(this->_last, v._last);
	std::swap(this->_endofstorage, v._endofstorage);
}

template<class T>
MyVector<T>::MyVector(const MyVector& vec):_start(nullptr),_last(nullptr,_endofstorage(nullptr))
{
	if (vec.size() > 0)
	{
		this->_start = new T[vec.size()];
		this->_last = _start + vec.size();
		this->_endofstorage = this->_last;
	}
	for (size_t i = 0; i < vec.size(); i++)
	{
		this->_start[i] = vec._start[i];
	}
}

template<class T>
MyVector<T>& MyVector<T> ::operator=(const MyVector& vec)
{
	this->swap(vec);//交换内部指针，实现赋值运算
	return *this;
}

template<class T>
T& MyVector<T> ::operator[](size_t index)
{
	if (index < this->size())
	{
		return this->_start[index];
	} 
}

template<class T>
typename MyVector<T>::iterator MyVector<T>:: begin()
{
	return this->_start;
}

template<class T>
typename MyVector<T>::iterator MyVector<T>::end()
{
	return this->_last;
}

template<class T>
bool MyVector<T>::operator==(const MyVector& vec)const
{
	if (this->size() != vec.size())
	{
		return false;
	}
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (this->_start[i] != vec._start[i])
		{
			return false;
		}
	}
	return true;
}

template<class T>
void MyVector<T>::push_back( const T& val)
{
	if (_last == _endofstorage)
	{
		size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
		reserve(newcapacity);
	}
	*_last = val;
	++_last;
}

template<class T>
void MyVector<T>::pop_back()
{
	if (!empty())
	{
		_last--;
	}
}

template<class T>
typename MyVector<T>::iterator MyVector<T>::insert(iterator pos,const T&x)
{
	assert(pos >= _start && pos <= _last);
	if (_last == _endofstorage)
	{
		size_t len = pos - _start;
		size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
		reserve(newcapacity);
		pos = _start + len;
	}
	iterator end = _last;
	while (end >= pos)
	{
		*end = *(end - 1);
		--end;
	}
	*pos = x;
	++_last;
	return pos;
}

template<class T>
typename MyVector<T>::iterator MyVector<T>::erase(iterator it)
{
	assert(it >= _start && it <= _last);
	iterator end = it + 1;
	while (end < _last)
	{
		*(end - 1) = *end;//it位置的后一位数取代前一位数就相当于删去it位置所在的数据
		++end;
	}
	--_last;
	return it;
}

template<class T>
T MyVector<T>::front()const
{
	return MyVector<T>[0];
}

template<class T>
T MyVector<T>::back()const
{
	return MyVector<T>[this->size() - 1];
}

template<class T>
size_t MyVector<T>::size()const
{
	return (this->_last) - (this->_start);
}

template<class T>
size_t MyVector<T>::capacity()const
{
	return (this->_endofstorage) - (this->_start);
}

template<class T>
bool MyVector<T>::empty()
{
	if (this->size() == 0)
	{
		return true;
	}
	return false;
}

template<class T>
void MyVector<T>::reserve(size_t n)
{
	/*
	if (n > this->capacity())
	{
		size_t sz = this->capacity();
		T* tmp = new T[n];
		memcpy(tmp, _start, sizeof(T) * sz);
		_start = tmp;//将原来_start指向的空间改为tmp新的内存空间，将原来数据复制到新空间中
		_last = _start + sz;
		_endofstorage = _start + n;
	}
	*/
	if (n > capacity())
	{
		size_t sz = capacity();
		T* tmp = new T[n];
		std::uninitialized_copy(_start, _last, tmp);
		delete[] _start;
		_start = tmp;
		_last = _start + sz;
		_endofstorage = _start + n;
	}
}







