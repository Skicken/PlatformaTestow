#pragma once
#include "ptpch.h"
#include "View.h"
#include "UI/Text.h"

template<typename T>
class SelectList:public View
{
	private:
	struct Element
	{
		Text text;
		T data;
	};
	public:
	SelectList(std::vector<std::pair<std::string, T>> list);

	std::vector<Element> list;
	Element selectedElement;
	void render() override;
	void update()override;

};



template <typename T>
void SelectList<T>::render()
{
	for(auto&element:list)
	{


	}
}

template <typename T>
 void SelectList<T>::update()
{

}


