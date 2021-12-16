/**********************************************************
// Name: Xuewei Sheng
// Seneca Student ID: 061745121
// Seneca email: xsheng3@myseneca.ca
// Date of completion: 2021-07-23
**********************************************************/
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

//using namespace std;

namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {

		if (file.empty()) {
			throw std::string("ERROR: No filename provided.");
		}
		std::ifstream fin(file);
		if (!fin)
			throw std::string("Unable to open [") + file + "] file.";		

		std::string line;
		while (std::getline(fin, line))
		{
			// the tokens from the record(line) 
			std::string workstation = line.substr(0, line.find_first_of('|'));
			std::string nxtWorkstation = line.erase(0, workstation.size() + 1);
			
			//loop through stations, find the station witch the name match the record token "workstation"
			//push it into activeLine
			auto ws = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws1) {return ws1->getItemName() == workstation; });
			activeLine.push_back(*ws);

			//if the string nextworkstaion is not empty
			//loop through stations agian, find the station wich the name mathc the record token "next workstation"
			//set this station as the next station of this record

			//else(nextworkstation string is empty), set the next station pointer point to nullptr			
			if (!nxtWorkstation.empty()) 
			{
				for_each(stations.begin(), stations.end(), [&](Workstation* ws1) {					
					if(ws1->getItemName() == nxtWorkstation) 
						activeLine.back()->setNextStation(ws1); 
					});
			}
			else
			{
				activeLine.back()->setNextStation(nullptr);
			}		
		}
		
		//find the m_firstStation
		for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws) {
			auto first = std::find_if(activeLine.begin(), activeLine.end(), [&](Workstation* ws1) {
				return ws == ws1->getNextStation();
				});
			if (first == activeLine.end()) 
			{
				m_firstStation = ws;
			}
			});

		//record the number of customer orders needs to be filled
		m_cntCustomerOrder = pending.size();
	}
	void LineManager::linkStations() {
		//create a vector of workstations named temp
		//copy the activeLine to this temp
		//loop throu the temp, find the station which name matched name of staion in the current station's pnextWorkstation pointer
		//store this matched station as the next station in the activeLine
		//repeat this process for each station in the original activeLine station, and get a new ordered line of stations
		std::vector<Workstation*> temp;
		temp = activeLine;
		activeLine[0] = m_firstStation;
	
		for (long unsigned i = 0; i < temp.size(); i++)
		{
			bool found = false;
			for (long unsigned j = 1; j < temp.size() && !found; j++)
			{
				if (activeLine[i]->getNextStation() != nullptr && activeLine[i]->getNextStation()->getItemName() == temp[j]->getItemName())
				{
					activeLine[i + 1] = temp[j];
					found = true;
				}
			}
		}
	}
	bool LineManager::run(std::ostream& os) {
		//set a local variable for counting iterations
		//if there is orders in the pending vector, move the first one to the m_firstStation, remove this order from pending
		//loop through the line to fill
		//loop through the line to move the order(using attemptToMoveOrder())
		static unsigned int COUNTER = 0u;
		os << "Line Manager Iteration: " << ++COUNTER << std::endl;
		if (!pending.empty())
		{
			*m_firstStation += std::move(pending.front());
			pending.pop_front();
			
		}
		for (size_t i = 0; i < activeLine.size(); i++)
		{
			activeLine[i]->fill(os);
		
		}
		for (size_t i = 0; i < activeLine.size(); i++)
		{
			activeLine[i]->attemptToMoveOrder();
		}
		//check if all the orders are finished processing-- the sum of orders in complete and incomplete equals the number in the pending at the beginning
		return completed.size() + incomplete.size() == m_cntCustomerOrder;
	}
	void LineManager::display(std::ostream& os)const {
		//print the workstations in the line
		for_each(activeLine.begin(), activeLine.end(), [&](const Workstation* ws) {ws->display(os); });
	}
}