#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void replace_all_occurrences(std::string& subject, const std::string& search, const std::string& replace);

template<typename T>
inline void remove_all(std::vector<T>& vector, const T& element) { vector.erase(std::remove(vector.begin(), vector.end(), element), vector.end()); }

#endif // !HELPER_FUNCTIONS_H_
