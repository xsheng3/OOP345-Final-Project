/**********************************************************
// Name: Xuewei Sheng
// Seneca Student ID: 061745121
// Seneca email: xsheng3@myseneca.ca
// Date of completion: 2021-07-12
**********************************************************/
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <string>
#include "Utilities.h"

namespace sdds {
	char Utilities::m_delimiter = '\0';

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string token = str;				
		char tester = token.at(next_pos);
		if (tester == m_delimiter)
		{
			more = false;
			throw std::string("Delimiter not found at") + std::to_string(next_pos);
		}
		else
		{
			token = str.substr(next_pos, str.size());
			token = token.substr(0, token.find_first_of(m_delimiter));
			next_pos += (token.size() + 1);
			if (next_pos >= str.size())
			{
				more = false;
			}
			m_widthField = m_widthField < token.size() ? token.size() : m_widthField;
		}			
		return token;		
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter() {
		return m_delimiter;
	}
}