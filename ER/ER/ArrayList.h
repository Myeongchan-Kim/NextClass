#pragma once
#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
class ArrayList
{
protected:
	int m_max;
	int m_size;
	T* list;
	char m_listName[256];
	virtual void MakeLarger();
	virtual bool isFull();
	virtual bool isEmpty();

public:
	ArrayList(const char * name = "UnknownList", int i = 10);
	virtual ~ArrayList();
	virtual bool isContain(const T& obj);
	virtual int GetId(const T& obj);
	virtual void Add(T obj);
	virtual T& Get(int id);
	virtual T Pop(int id);
	virtual T Set(int id, T source);
	virtual int size();
};

template<typename T>
inline bool ArrayList<T>::isContain(const T& obj)
{
	for (int i = 0; i < m_size; i++)
	{
		if (list[i] == obj)
			return true;
	}
	return false;
}

template<typename T>
inline int ArrayList<T>::GetId(const T& obj)
{
	for (int i = 0; i < m_size; i++)
	{
		if (list[i] == obj)
			return i;
	}
	return -1; //means err
}


template<typename T>
inline ArrayList<T>::ArrayList(const char * name, int i ) : m_max(i)
{
	strcpy_s(m_listName, name);
	cout << "ArrList():" << m_listName << endl;
	list = new T[m_max];
	m_size = 0;
};

template<typename T>
inline ArrayList<T>::~ArrayList()
{
	cout << "~ArrList():"<< m_listName << endl;
};

template<typename T>
inline void ArrayList<T>::Add(T obj)
{
	if (isFull())
		MakeLarger();
	list[m_size] = obj;
	m_size++;
};

template<typename T>
inline T& ArrayList<T>::Get(int id)
{
	return list[id];
};

template<typename T>
inline T ArrayList<T>::Pop(int id)
{
	//This cause change of original Array.
	//YOU MUST be concerned of using this inside loop
	//Maybe you use this inside loop, have to do i-- , size-- .
	T result = list[id];
	list[id] = list[m_size - 1];
	m_size--;
	return result;
};

template<typename T>
inline T ArrayList<T>::Set(int id, T source)
{
	T result = list[id];
	list[id] = source;
	return result;
};

template<typename T>
inline void ArrayList<T>::MakeLarger()
{
	T* newList = new T[m_max * 2];
	for (int i = 0; i < m_size; i++)
	{
		newList[i] = list[i];
	}
	m_max *= 2;
	delete[] list;
	list = newList;
};

template <typename T>
inline bool ArrayList<T>::isFull()
{
	if (m_size >= m_max)
		return true;
	else
		return false;
};

template <typename T>
inline bool ArrayList<T>::isEmpty()
{
	if (m_size == 0)
		return true;
	else
		return false;
};

template <typename T>
inline int ArrayList<T>::size()
{
	return m_size;
}