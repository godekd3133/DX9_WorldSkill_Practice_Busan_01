#pragma once
template <class T>
class CSingleton
{
public:
	CSingleton() {}
	virtual ~CSingleton() {}
private:
	static T* p;
public:
	static T * GetInstance()
	{
		if (!p) p = new T();
		return p;
	}
	static void ReleaseInstance() 
	{
		if (p)
			delete p;
	}
};
template <typename T>
T* CSingleton<T>::p = nullptr;