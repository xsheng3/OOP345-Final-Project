/**********************************************************
// Name: Xuewei Sheng
// Seneca Student ID: 061745121
// Seneca email: xsheng3@myseneca.ca
// Date of completion: 2021-07-18
**********************************************************/
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H
#include "Station.h"


namespace sdds {
	struct Item
	{
		std::string m_itemName{};
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item() {};

		Item(const std::string& src) : m_itemName(src) {};
	};
	class CustomerOrder
	{
		Item m_item;
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{ 0u };
		Item** m_lstItem{ nullptr };
		static size_t m_widthField;

	public:
		CustomerOrder() {}
		CustomerOrder(const std::string& order);
		CustomerOrder(const CustomerOrder& src);
		CustomerOrder& operator=(const CustomerOrder& src) = delete;
		CustomerOrder(CustomerOrder&& src) noexcept;
		CustomerOrder& operator=(CustomerOrder&& src) noexcept;
		~CustomerOrder();
		bool isFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif // !CUSTOMERORDER_H



