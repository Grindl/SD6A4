#include "NamedProperties.hpp"

#include "Memory Manager/MemoryManager.hpp"


//------------------------------------------------------------------------------
NamedProperties::NamedProperties()
{

}


//------------------------------------------------------------------------------
void NamedProperties::setProperty(std::string keyPair, NamedHelperBase* valuePair)
{
	m_propertyDictionary[keyPair] = valuePair;
}

//------------------------------------------------------------------------------
bool NamedProperties::addProperty(std::string keyPair, NamedHelperBase* valuePair)
{
	if(m_propertyDictionary.find(keyPair)._Ptr == NULL || m_propertyDictionary.find(keyPair) == m_propertyDictionary.end())
	{
		m_propertyDictionary[keyPair] = valuePair;
		return true;
	}
	else
	{
		return false;
	}
}

//------------------------------------------------------------------------------
bool NamedProperties::modifyProperty(std::string keyPair, NamedHelperBase* valuePair)
{
	if(m_propertyDictionary.find(keyPair)._Ptr == NULL || m_propertyDictionary.find(keyPair) == m_propertyDictionary.end())
	{
		m_propertyDictionary[keyPair] = valuePair;
		return true;
	}
	else
	{
		return false;
	}
}

//------------------------------------------------------------------------------
bool NamedProperties::deleteProperty(std::string keyPair)
{
	if(m_propertyDictionary.find(keyPair)._Ptr == NULL || m_propertyDictionary.find(keyPair) == m_propertyDictionary.end())
	{
		m_propertyDictionary.erase(keyPair);
		return true;
	}
	else
	{
		return false;
	}
}

//------------------------------------------------------------------------------
template<typename T_PropertyType> 
T_PropertyType* NamedProperties::getProperty(std::string keyPair)
{
	NamedHelperBase* valueAsBase =  m_propertyDictionary.at(keyPair);
	NamedHelper<T_PropertyType>* valueAsTemplate = dynamic_cast<NamedHelper<T_PropertyType>*>(valueAsBase);
	return valueAsTemplate->val;
}