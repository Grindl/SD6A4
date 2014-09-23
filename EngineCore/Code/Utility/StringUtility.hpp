#pragma once
#ifndef include_STRINGUTILITY
#define include_STRINGUTILITY

#include <string>
#include <vector>


namespace StringUtility
{
//----------------------------------------------------------------------------------------
	static std::vector<std::string> StringSplit(const std::string& stringToBeSplit, const std::string& delimitingCharacters, const std::string& ignoredCharacters)
	{
		std::vector<std::string> finalizedSplit;

		std::vector<std::string> delimitingArray;
		for(unsigned int delimitingIterator = 0; delimitingIterator < delimitingCharacters.size(); delimitingIterator++)
		{
			delimitingArray.push_back(delimitingCharacters.substr(delimitingIterator, 1));
		}

		std::vector<std::string> ignoredArray;
		for(unsigned int ignoredIterator = 0; ignoredIterator < ignoredCharacters.size(); ignoredIterator++)
		{
			ignoredArray.push_back(ignoredCharacters.substr(ignoredIterator, 1));
		}

		std::string currentStringSegment = "";
		for(unsigned int splitStringIterator = 0; splitStringIterator < stringToBeSplit.size(); splitStringIterator++)
		{
			std::string currenCharacter = stringToBeSplit.substr(splitStringIterator, 1);
			bool characterConsumed = false;

			for(unsigned int ignoredConsumptionIterator = 0; ignoredConsumptionIterator < ignoredArray.size(); ignoredConsumptionIterator++)
			{
				if(currenCharacter == ignoredArray[ignoredConsumptionIterator])
				{
					characterConsumed = true;
				}
			}
			for(unsigned int delimitingConsumptionIterator = 0; delimitingConsumptionIterator < delimitingArray.size(); delimitingConsumptionIterator++)
			{
				if(currenCharacter == delimitingArray[delimitingConsumptionIterator] && currentStringSegment != "")
				{
					finalizedSplit.push_back(currentStringSegment);
					currentStringSegment = "";
					characterConsumed = true;
				}
			}

			if(!characterConsumed)
			{
				currentStringSegment.append(currenCharacter);
			}
		}
		if (currentStringSegment !="")
		{
			finalizedSplit.push_back(currentStringSegment);
		}
		return finalizedSplit;
	}
}



#endif