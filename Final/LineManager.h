/**********************************************************
// Name: Xuewei Sheng
// Seneca Student ID: 061745121
// Seneca email: xsheng3@myseneca.ca
// Date of completion: 2021-07-23
**********************************************************/
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef LINEMANAGER_H
#define LINEMANAGER_H
#include "Workstation.h"

namespace sdds {
	class LineManager
	{
		std::vector<Workstation*> activeLine;
		size_t m_cntCustomerOrder{0};
		Workstation* m_firstStation{ nullptr };
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void linkStations();
		bool run(std::ostream& os);
		void display(std::ostream& os)const;
	};

}

#endif // !LINEMANAGER_H


