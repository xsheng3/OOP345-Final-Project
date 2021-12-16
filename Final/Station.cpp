/**********************************************************
// Name: Xuewei Sheng
// Seneca Student ID: 061745121
// Seneca email: xsheng3@myseneca.ca
// Date of completion: 2021-07-12
**********************************************************/
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"

namespace sdds {
	unsigned Station::m_widthField = 0u;
	unsigned Station::id_generator = 0u;
	//recieve a single station record as string, using Utility object to get tokens for each attribute
	Station::Station(const std::string& record) {
		Utilities uti;
		size_t pos = 0u;
		bool more = true;
		m_name = uti.extractToken(record, pos, more);
		m_nextSerialNo = stoi(uti.extractToken(record, pos, more));
		m_quantity = stoi(uti.extractToken(record, pos, more));
		m_widthField = m_widthField > uti.getFieldWidth() ? m_widthField : uti.getFieldWidth();
		m_desc = uti.extractToken(record, pos, more);
		id_generator++;
		m_id = id_generator;
	}
	const std::string& Station::getItemName()const {
		return m_name;
	}
	size_t Station::getNextSerialNumber() {
		return m_nextSerialNo++;
	}
	size_t Station::getQuantity()const {
		return m_quantity;
	}
	void Station::updateQuantity() {
		if (m_quantity > 0)
		{
			m_quantity--;
		}		
	}
	void Station::display(std::ostream& os, bool full) const {
		//print information of one station
		if (!full)
		{
			os <<  '[' << std::setw(3) << std::setfill('0') << std::right << m_id << ']' << " Item: " << std::setw(m_widthField) << std::setfill(' ')  << std::left << m_name << " [" << std::setw(6) << std::setfill('0') << std::right << m_nextSerialNo << "]";
		}
		else
		{
			os << '[' << std::setw(3) << std::setfill('0') << std::right << m_id << ']' << " Item: " << std::setw(m_widthField) << std::setfill(' ') << std::left << m_name << " [" << std::setw(6) << std::setfill('0') << std::right << m_nextSerialNo << "] " << "Quantity: " << std::setw(m_widthField) << std::setfill(' ') << std::left << m_quantity << " Description: " << m_desc;
		}
		os << std::endl;
	}
}