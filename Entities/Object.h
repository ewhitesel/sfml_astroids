#pragma once

#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>

class Object : public std::enable_shared_from_this<Object>
{
private:
    int m_instance;
public:

    sf::ConvexShape model;
    Object();
    ~Object();

    virtual void update();
  
    void createObject();
    void killObject();
    Object* returnPtr();

    sf::ConvexShape* returnModel()
    {
        return &model;
    }
    std::vector<std::shared_ptr<Object>> returnList();
};

template <typename T>
class EntityManager
{
public:
    template<class... Args>
    void create(Args&&... args)
    {
        std::shared_ptr<T> obj(std::make_shared<T>(args...));

        instances.push_back(reinterpret_cast<T*>(obj->returnPtr()));
      
        obj->createObject();
    }

    void kill(int i)
    {
        if (instances.size() != 0)
        {
            instances[i]->killObject();
            instances.erase(instances.begin() + i);
            instances.shrink_to_fit();
        }
    }
    std::vector<T*> returnInstance() { return instances; }

private:
    std::vector<T*> instances;
};

#endif