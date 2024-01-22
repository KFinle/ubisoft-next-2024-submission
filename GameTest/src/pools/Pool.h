#pragma once
#include <vector>

// Templated Pool class
// This class is used to create a Pool of any GameObjects required.
// This is a singletop class that can be instantiated for Pools of any 
// object type 
template<class T>
class Pool
{
public:
	// Return or create the Singleton instance
	static Pool* GetInstance(int pool_size)
	{
		if (instance == nullptr)
		{
			instance = new Pool(pool_size);
			instance->RefreshPool();
		}
		return instance;
	}

	// Refresh the pool if it is empty
	void RefreshPool()
	{
		for (int i = 0; i < m_pool_size; i++)
		{
			m_objects.push_back(new T());
		}
	}

	// Get an object from the pool.
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

	// Return an object to the pool
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

