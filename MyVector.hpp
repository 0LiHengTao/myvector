#pragma once
#include<iostream>
#include<cassert>
#include<memory>
using namespace std;

template<class T>
class MyVector
{
public:
	typedef T* iterator;//�ɶԶ������ݽ��ж�д����
	//typedef T* const_iterator;  ֻ�ܶԶ������ݽ��ж�����

	//���캯��
	MyVector();

	//��������
	~MyVector();

	//�������캯��
	MyVector(const MyVector& vec);

	//��ֵ��������غ���
	MyVector& operator=(const MyVector& vec);

	//[]��������غ���������ȡ��vectorʵ��������ĵ�index��Ԫ��)
	T& operator[](size_t index);

	//==��������غ����������ж�����vector�����Ƿ���ͬ��
	bool operator==(const MyVector& vec)const;

	//��ʵ������������Ԫ��
	void push_back(const T& val);

	//ɾ��ʵ������������һ��Ԫ��
	void pop_back();

	//��vectorʵ���������itλ�ò���һ��Ԫ��
	iterator insert(iterator it, const T& val);

	//ɾ��vectorʵ��������itλ�õ�Ԫ��
	iterator erase(iterator it);

	//ȡ��vector�����еĵ�һ��Ԫ��
	T front()const;

	//ȡ��vector�����е����һ��Ԫ��
	T back()const;

	//��ȡvectorʵ����������׵�ַ
	iterator begin();

	//��ȡvectorʵ������������һ��Ԫ�صĵ�ַ
	iterator end();

	//��ȡvectorʵ���������Ԫ�ظ���
	size_t size()const;
	size_t capacity()const;

	//�ж�vectorʵ���������Ƿ�Ϊ��
	bool empty();

	//��������������
	void swap(MyVector& v);

	//���ռ�
	void reserve(size_t n);

private:
	iterator _start;//ͷָ��
	iterator _last;//βָ��
	iterator _endofstorage;//����ܴ洢��βλ�ã�������С��

};

template<class T>
MyVector<T>::MyVector()
{
	//��Ϊ��ָ��
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
	std::swap(this->_start, v._start);//����std::swap()����������ַ,ͬʱ��ȡ�����Ĵ�С��������Ϣ
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
	this->swap(vec);//�����ڲ�ָ�룬ʵ�ָ�ֵ����
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
		*(end - 1) = *end;//itλ�õĺ�һλ��ȡ��ǰһλ�����൱��ɾȥitλ�����ڵ�����
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
		_start = tmp;//��ԭ��_startָ��Ŀռ��Ϊtmp�µ��ڴ�ռ䣬��ԭ�����ݸ��Ƶ��¿ռ���
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







