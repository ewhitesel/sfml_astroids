#include "Object.h"



static std::vector<std::shared_ptr<Object>>objList;
static int s_instance = 0;


Object::Object()
{
	s_instance = s_instance++;
	m_instance = s_instance;
}


Object::~Object()
{
	
}

void Object::update() {}

void Object::createObject()
{
	objList.emplace_back(shared_from_this());
}


void Object::killObject()
{
	for (int i = 0; i < objList.size(); i++)
	{
		if (objList[i].get() == this)
		{

			objList.erase(objList.begin() + i);
			objList.shrink_to_fit();
		}
	}
}

Object* Object::returnPtr()
{
	return this;
}

std::vector<std::shared_ptr<Object>> Object::returnList()
{
	return objList;
}