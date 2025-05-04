#include "Helper_Functions.h"
#include <string>

void replace_all_occurrences(std::string& subject, const std::string& search, const std::string& replace)
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos)
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

size_t lavenstein_distance(const std::string& string, const std::string& reference)
{
	size_t string_length = string.length();
	size_t reference_length = reference.length();
	std::vector<std::vector<size_t>> distance(string_length + 1, std::vector<size_t>(reference_length + 1));
	for (size_t i = 0; i <= string_length; ++i)
	{
		distance[i][0] = i;
	}
	for (size_t j = 0; j <= reference_length; ++j)
	{
		distance[0][j] = j;
	}
	for (size_t i = 1; i <= string_length; ++i)
	{
		for (size_t j = 1; j <= reference_length; ++j)
		{
			size_t cost = (string[i - 1] == reference[j - 1]) ? 0 : 1;
			distance[i][j] = std::min({ distance[i - 1][j] + 1, distance[i][j - 1] + 1, distance[i - 1][j - 1] + cost });
		}
	}
	return distance[string_length][reference_length];
}

size_t search_lavenstein_name_surname_helper(const std::string& name, const std::string& surname, const std::string& reference_name, const std::string& reference_surname)
{
	size_t distance = 0;
	if (!reference_name.empty())
	{
		distance += lavenstein_distance(name, reference_name);
	}
	if (!reference_surname.empty())
	{
		distance += lavenstein_distance(surname, reference_surname);
	}
	return distance;
}