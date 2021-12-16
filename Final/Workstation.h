/**********************************************************
// Name: Xuewei Sheng
// Seneca Student ID: 061745121
// Seneca email: xsheng3@myseneca.ca
// Date of completion: 2021-07-23
**********************************************************/
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef WORKSTATION_H
#define WORKSTATION_H
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds {
	extern std::deque<CustomerOrder> pending;
	extern std::deque<CustomerOrder> completed;
	extern std::deque<CustomerOrder> incomplete;

	class Workstation : public Station
	{
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pnextStation{ nullptr };
	public:
		Workstation(const std::string& record);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation()const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
		Workstation(const Workstation& src) = delete;
		Workstation& operator=(const Workstation& src) = delete;
		Workstation(Workstation&& src) = delete;
		Workstation& operator=(Workstation&& src) = delete;
		//~Workstation();
	};

}

#endif // !WORKSTATION_H

