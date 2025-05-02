/**
 * @file Helper_Functions.h
 * @brief Provides utility functions and templates for common operations.
 * @details This file contains a collection of helper functions and templates for string manipulation,
 *          vector operations, and filtering data structures.
 */

#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>

 /**
  * @brief Replaces all occurrences of a substring within a string.
  * @details This function searches for all occurrences of a specified substring in the given string
  *          and replaces them with another substring.
  * @param subject The string in which to perform the replacements.
  * @param search The substring to search for.
  * @param replace The substring to replace with.
  */
void replace_all_occurrences(std::string& subject, const std::string& search, const std::string& replace);

/**
 * @brief Removes all occurrences of a specific element from a vector.
 * @details This template function removes all elements in the vector that are equal to the specified element.
 * @tparam T The type of elements in the vector.
 * @param vector The vector from which to remove elements.
 * @param element The element to remove.
 */
template<typename T>
void remove_all(std::vector<T>& vector, const T& element)
{
	auto it = std::remove(vector.begin(), vector.end(), element);
	vector.erase(it, vector.end());
}

/**
 * @brief Removes all occurrences of a specific element from a vector of unique pointers.
 * @details This template function removes all elements in the vector of unique pointers that are equal to the specified element.
 * @tparam T The type of elements managed by the unique pointers in the vector.
 * @param vector The vector of unique pointers from which to remove elements.
 * @param element The element to remove.
 */
template<typename T>
void remove_all(std::vector<std::unique_ptr<T>>& vector, const T& element)
{
	auto it = std::remove_if(vector.begin(), vector.end(),
		[&element](const std::unique_ptr<T>& ptr) { return *ptr == element; });
	vector.erase(it, vector.end());
}

/**
 * @brief Checks if a vector contains a specific value.
 * @details This template function determines whether the specified value exists in the given vector.
 * @tparam T The type of elements in the vector.
 * @param vector The vector to search.
 * @param value The value to search for.
 * @return true if the value is found in the vector, false otherwise.
 */
template<typename T>
bool contains(const std::vector<T>& vector, const T& value)
{
	return std::find(vector.begin(), vector.end(), value) != vector.end();
}

/**
 * @brief Checks if a vector contains any value from another vector.
 * @details This template function determines whether any value from the second vector exists in the first vector.
 * @tparam T The type of elements in the vectors.
 * @param vector The vector to search.
 * @param values The vector of values to search for.
 * @return true if any value from `values` is found in `vector`, false otherwise.
 */
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

/**
 * @brief Filters a vector of pointers based on a predicate.
 * @details This template function returns a new vector containing pointers to elements that satisfy the given predicate.
 * @tparam T The type of elements pointed to in the vector.
 * @tparam Predicate The type of the predicate function.
 * @param vector The vector of pointers to filter.
 * @param predicate The predicate function to apply to each element.
 * @return A vector of pointers to elements that satisfy the predicate.
 */
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

/**
 * @brief Filters a vector of unique pointers based on a predicate.
 * @details This template function returns a new vector containing raw pointers to elements that satisfy the given predicate.
 * @tparam T The type of elements managed by the unique pointers in the vector.
 * @tparam Predicate The type of the predicate function.
 * @param vector The vector of unique pointers to filter.
 * @param predicate The predicate function to apply to each element.
 * @return A vector of raw pointers to elements that satisfy the predicate.
 */
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

/**
 * @brief Filters a multimap by its keys based on a predicate.
 * @details This template function returns a new vector containing pointers to elements whose keys satisfy the given predicate.
 * @tparam T The type of elements in the multimap.
 * @tparam S The type of the keys in the multimap.
 * @tparam Predicate The type of the predicate function.
 * @param map The multimap to filter.
 * @param predicate The predicate function to apply to each key.
 * @return A vector of pointers to elements whose keys satisfy the predicate.
 */
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

/**
 * @brief Calculates the Levenshtein distance between two strings.
 * @details This function computes the minimum number of single-character edits (insertions, deletions, or substitutions)
 *          required to change one string into the other.
 * @param string The first string.
 * @param reference The second string.
 * @return The Levenshtein distance between the two strings.
 */
size_t lavenstein_distance(const std::string& string, const std::string& reference);

#endif // !HELPER_FUNCTIONS_H_
