/**********************************************************
// Name: Xuewei Sheng
// Seneca Student ID: 061745121
// Seneca email: xsheng3@myseneca.ca
// Date of completion: 2021-07-23
**********************************************************/
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Workstation.h"

namespace sdds {
	std::deque<CustomerOrder> pending{};
	std::deque<CustomerOrder> completed{};
	std::deque<CustomerOrder> incomplete{};
	Workstation::Workstation(const std::string& record): Station(record){}

	//fills the order at the front of the queue, if there are CustomerOrders in the queue; 
	//otherwise, does nothing.
	void Workstation::fill(std::ostream& os) {
		if (m_orders.size() != 0)
		{
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder() {
		bool moved = false;
		if (!m_orders.empty())
		{
			CustomerOrder& order = m_orders.front();
			// if the order is filled at this station, or the invetory of this station is insufficent (==0)
			if (order.isItemFilled(this->getItemName()) || this->getQuantity() == 0)
			{
				//if there is a nextStation, move to next station
				if (m_pnextStation != nullptr)
				{
					*m_pnextStation += (std::move(order));
					
				}
				//if at the end of the managerLine
				//move ot complete que if all items in the order is filled
				//else move to incomplete que
				else
				{
					if (order.isFilled())
					{
						completed.push_back(std::move(order));
					}
					else
					{
						incomplete.push_back(std::move(order));
					}
				}
				moved = true;
				m_orders.pop_front();
			}
		}		
		return moved;
	}

	//default to nullptr, in .h
	void Workstation::setNextStation(Workstation* station) {
		m_pnextStation = station;
	}

	Workstation* Workstation::getNextStation()const {
		return m_pnextStation;
	}

	void Workstation::display(std::ostream& os) const {
		if (m_pnextStation == nullptr)
		{
			os << getItemName() << " --> " << "End of Line" << std::endl;
		}
		else
		{
			os << getItemName() << " --> " << m_pnextStation->getItemName() << std::endl;
		}
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}