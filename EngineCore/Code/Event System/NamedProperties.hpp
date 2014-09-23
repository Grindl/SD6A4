#pragma once
#ifndef include_NAMEDPROPERTIES
#define include_NAMEDPROPERTIES

#include <map>
#include <string>

class NamedProperties
{
public:
	class NamedHelperBase{};
	template <typename T_PropertyType>
	class NamedHelper : public NamedHelperBase{public: T_PropertyType* val;};
	

	NamedProperties();

	//
	std::map< std::string, NamedHelperBase*> m_propertyDictionary;

	void setProperty(std::string keyPair, NamedHelperBase* valuePair);
	bool addProperty(std::string keyPair, NamedHelperBase* valuePair);
	bool modifyProperty(std::string keyPair, NamedHelperBase* valuePair);
	bool deleteProperty(std::string keyPair);
	template <typename T_PropertyType> 
	T_PropertyType* getProperty(std::string keyPair);
};

#endif