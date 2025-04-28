#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>

void replace_all_occurrences(std::string& subject, const std::string& search, const std::string& replace);

template<typename T>
void remove_all(std::vector<T>& vector, const T& element)
{
	auto it = std::remove(vector.begin(), vector.end(), element);
	vector.erase(it, vector.end());
}

template<typename T>
void remove_all(std::vector<std::unique_ptr<T>>& vector, const T& element)
{
	auto it = std::remove_if(vector.begin(), vector.end(),
		[&element](const std::unique_ptr<T>& ptr) { return *ptr == element; });
	vector.erase(it, vector.end());
}

template<typename T>
bool contains(const std::vector<T>& vector, const T& value)
{
	return std::find(vector.begin(), vector.end(), value) != vector.end();
}

template<typename T>
bool contains_any_from_vector(const std::vector<T>& vector, const std::vector<T>& values)
{
	for (const auto& value : values)
	{
		if (contains(vector, value))
		{
			return true;
		}
	}
	return false;
}

template<typename T, typename Predicate>
std::vector<T*> filter(const std::vector<T*>& vector, Predicate predicate)
{
	std::vector<T*> result;
	for (const auto& ptr : vector)
	{
		if (predicate(*ptr))
		{
			result.push_back(ptr);
		}
	}
	return result;
}

template<typename T, typename Predicate>
std::vector<T*> filter(const std::vector<std::unique_ptr<T>>& vector, Predicate predicate)
{
	std::vector<T*> result;
	for (const auto& ptr : vector)
	{
		if (predicate(*ptr))
		{
			result.push_back(ptr.get());
		}
	}
	return result;
}

template<typename T, typename S, typename Predicate>
std::vector<T*> filter_multimap_by_keys(const std::multimap<S, T*>& map, Predicate predicate)
{
	std::vector<T*> result;
	bool found = false;
	for (const auto& element : map)
	{
		if (predicate(element.first))
		{
			result.push_back(element.second);
			found = true;
		}
		else if (found)
		{
			break;
		}
	}
	return result;
}

#endif // !HELPER_FUNCTIONS_H_
