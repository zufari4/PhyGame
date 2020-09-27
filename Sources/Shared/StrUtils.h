#pragma once

#include <string>
#include <vector>

namespace StrUtils
{
	bool stob(const std::string& str);
	std::vector<float> strtokf(const std::string& str);
	std::vector<int> strtoki(const std::string& str);
	std::vector<std::string> Tokinize(const std::string& str, char delimiter);
	bool strncasecpm(const std::string& a, const std::string& b);
}