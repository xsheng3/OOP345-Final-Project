/**********************************************************
// Name: Xuewei Sheng
// Seneca Student ID: 061745121
// Seneca email: xsheng3@myseneca.ca
// Date of completion: 2021-07-12
**********************************************************/
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef UTILITIES_H
#define UTILITIES_H
namespace sdds {	
	class Utilities
	{
		unsigned m_widthField{ 0u };	
		static char m_delimiter;
	public:
		void setFieldWidth(size_t newWidth = 1);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};	
}

#endif // !UTILITIES_H



