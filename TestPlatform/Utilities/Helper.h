#pragma once
class Helper
{
	public:
	template<typename T,typename F>
	static std::string ListToStringSeparated(std::vector<T> &list,
		const F f);
	template<typename T>
	static std::string ListToStringSeparated(std::vector<T>& list,
		std::string (T::*pointer)() const);
};

template <typename T, typename F>
std::string Helper::ListToStringSeparated(std::vector<T>& list, const 
	F f)
{
	std::string str="";
	for(auto& element:list)
	{
		str += f(element);
		str += ";";
	}
	if(!str.empty())
	str.pop_back();
	return str;
}

template <typename T>
std::string Helper::ListToStringSeparated(std::vector<T>& list, std::string(T::* pointer)()const)
{
	std::string str = "";
	for (auto& element : list)
	{
		str += (element.*pointer)();
		str += ";";
	}
	if (!str.empty())
	str.pop_back();
	return str;

}

