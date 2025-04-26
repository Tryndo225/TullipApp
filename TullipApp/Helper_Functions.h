#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

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

template<typename T, typename Predicate>
std::vector<T> filter(const std::vector<T>& vector, Predicate predicate)
{
	std::vector<T> result;
	std::copy_if(vector.begin(), vector.end(), std::back_inserter(result), predicate);
	return result;
}

template<typename T, typename Predicate>
std::vector<T> filter(const std::vector<std::unique_ptr<T>>& vector, Predicate predicate)
{
	std::vector<T> result;
	for (const auto& ptr : vector)
	{
		if (predicate(*ptr))
		{
			result.push_back(*ptr);
		}
	}
	return result;
}

#endif // !HELPER_FUNCTIONS_H_
