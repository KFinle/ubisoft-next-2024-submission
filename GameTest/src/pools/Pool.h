#pragma once
#include <vector>

#include <memory>
#include "../components/Projectile.h"

template<class T>
class Pool
{
public:
	static Pool* GetInstance(int pool_size)
	{
		if (instance == nullptr)
		{
			instance = new Pool(pool_size);
			instance->RefreshPool();
		}
		return instance;
	}

	void RefreshPool()
	{
		for (int i = 0; i < m_pool_size; i++)
		{
			m_objects.push_back(new T());
		}
	}

	T* GetPoolObject()
	{
		if (m_objects.empty())
		{
			RefreshPool();
		}

		T* object = m_objects.front();
		m_objects.erase(m_objects.begin());
		return object;
		
	}

	void ReturnPoolObject(T* object)
	{
		delete object;
		m_objects.emplace_back(new T());

	}

private:


	static Pool<T>* instance;
	Pool(int pool_size) : m_pool_size(pool_size)  {}
	std::vector<T*> m_objects;
	int m_pool_size;
};

template<class T>
Pool<T>* Pool<T>::instance = nullptr;

// declare projectile pool
Pool<Projectile>* Pool<Projectile>::instance = nullptr;