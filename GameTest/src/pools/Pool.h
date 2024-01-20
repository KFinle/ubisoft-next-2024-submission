#pragma once
#include <vector>
#include <memory>

class BasePool
{
public:
    virtual ~BasePool() = default;
    virtual void Initialize() = 0;
};

template<class T>
class Pool : public BasePool
{
public:
    Pool(int pool_size) : m_pool_size(pool_size), m_objects(pool_size), m_start(0), m_end(0)
    {
        Initialize();
    }

    virtual ~Pool() override = default;

    virtual void Initialize() override
    {
        for (int i = 0; i < m_pool_size; ++i)
        {
            m_objects[i] = std::make_unique<T>();
        }
    }

    std::unique_ptr<T> GetPoolObject()
    {
        if (m_start != m_end)
        {
            auto entity = std::move(m_objects[m_start]);
            m_objects[m_start] = nullptr;
            IncrementIndex(m_start);
            return entity;
        }
        return nullptr;
    }

    void ReleaseObject(std::unique_ptr<T> entity)
    {
        if (!m_objects[m_end])
        {
            m_objects[m_end] = std::move(entity);
            IncrementIndex(m_end);
        }
    }

    //private:
    void IncrementIndex(int& index)
    {
        index = (index + 1) % m_pool_size;
    }

    //protected:
    int m_pool_size;
    std::vector<std::unique_ptr<T>> m_objects;
    int m_start;
    int m_end;
};
