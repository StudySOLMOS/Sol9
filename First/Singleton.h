#pragma once

template <typename T>
class Singleton
{
protected:
	Singleton() {}
	Singleton(const Singleton& other);
	virtual ~Singleton() {};

public:
	static T* instance()
	{
		static T instance;
		return &instance;
	}
};
