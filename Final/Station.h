/**********************************************************
// Name: Xuewei Sheng
// Seneca Student ID: 061745121
// Seneca email: xsheng3@myseneca.ca
// Date of completion: 2021-07-12
**********************************************************/
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef STATION_H
#define STATION_H

namespace sdds {
	class Station
	{
		int m_id{ 0 };
		std::string m_name{};
		std::string m_desc{};
		unsigned m_nextSerialNo{ 0u };
		unsigned m_quantity{ 0u };
		static unsigned m_widthField;
		static unsigned id_generator;
	public:
		Station(const std::string& record);
		const std::string& getItemName()const;
		size_t getNextSerialNumber();
		size_t getQuantity()const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif // 



