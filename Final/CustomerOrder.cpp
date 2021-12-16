/**********************************************************
// Name: Xuewei Sheng
// Seneca Student ID: 061745121
// Seneca email: xsheng3@myseneca.ca
// Date of completion: 2021-07-18
**********************************************************/
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"

namespace sdds {
	size_t CustomerOrder::m_widthField = 0u;

	//recieve a single order record as string, using Utility object to get tokens for each attribute
	CustomerOrder::CustomerOrder(const std::string& order) {
		Utilities uti;
		size_t pos = 0u;
		bool more = true;
		m_name = uti.extractToken(order, pos, more);
		m_product = uti.extractToken(order, pos, more);
		for (long unsigned i = 0; i < order.size(); i++)
		{
			//count the delimiter number to get the items number in this order
			if (order[i] == uti.getDelimiter())
			{
				m_cntItem++;
			}
		}
		m_cntItem--;
        
		//create new Iems objects for each object in the order
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++)
		{
			m_lstItem[i] = new Item(uti.extractToken(order, pos, more));
		}

		//set the field width for displaying
		m_widthField = m_widthField > uti.getFieldWidth() ? m_widthField : uti.getFieldWidth();
	}

	//if copy constructor called, throw a error--using move constructor for copying and moving
	CustomerOrder::CustomerOrder(const CustomerOrder& src) {
		throw std::string("Copy constructor is deleted!");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
		*this = std::move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept{
		if (this != &src)
		{
			for (size_t i = 0; i < m_cntItem; i++)
			{
				if (m_lstItem[i] != nullptr)
				{
					delete m_lstItem[i];
					m_lstItem[i] = nullptr;
				}
			}
			if (m_lstItem != nullptr)
				delete[] m_lstItem;
			m_lstItem = src.m_lstItem;

			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;	

			src.m_lstItem = nullptr;
			src.m_name = {};
			src.m_product = {};
			src.m_cntItem = 0u;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		//delete each Items first then delete the m_lstItem array
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i] != nullptr)
			{
				delete m_lstItem[i];
				m_lstItem[i] = nullptr;
			}
		}
		if (m_lstItem != nullptr)
		{
			delete[] m_lstItem;
			m_lstItem = nullptr;
		}
	}

	bool CustomerOrder::isFilled() const {
		//loop through the Items in the list, check if all ietem are filled
		bool allfill = true;
		for (size_t i = 0; i < m_cntItem && allfill; i++)
		{
			if (m_lstItem[i]->m_isFilled == false)
			allfill = false;
		}
		return allfill;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		//loop through the items, check if any item match the string
		//if match found, then this the item with "itemName" in the order is filled
		bool fill = true;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				fill = m_lstItem[i]->m_isFilled;
			}
		}
		return fill;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		//find the item which the name is matched the name of recieved station
		//if found and the quantity in this station is not zero
		//fill is item by setting the m_isFilled to true. 
		//then update the quantity in this station(decrease the quantity by one)
		//and print out this item is filled
		//else, print out this item is not filled.
		for (size_t i = 0; i < m_cntItem; i++)
		{   
			if (station.getItemName() == m_lstItem[i]->m_itemName)
			{   
				if (station.getQuantity() > 0)
				{
					m_lstItem[i]->m_isFilled = true;
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				else 
				{
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const {
        //loop through the items in the order, prin out the information in required format
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ') << std::setw(m_widthField) << std::left << m_lstItem[i]->m_itemName << " - ";
			if (m_lstItem[i]->m_isFilled)
			{
				os << "FILLED" << std::endl;
			}
			else
			{
				os << "TO BE FILLED" << std::endl;
			}
		}
	}
}
