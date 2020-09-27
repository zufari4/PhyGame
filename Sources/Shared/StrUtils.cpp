#include "StrUtils.h"

#include <sstream>

namespace StrUtils
{
	bool stob(const std::string& str)
	{
		bool res;
		std::istringstream(str) >> std::boolalpha >> res;
		return res;
	}

	std::vector<float> strtokf(const std::string& str)
	{
		std::vector<float> res;
		const auto v = Tokinize(str, ',');
		for (const auto& t : v) {
			res.push_back(std::stof(t));
		}
		return res;
	}

	std::vector<int> strtoki(const std::string& str)
	{
		std::vector<int> res;
		const auto v = Tokinize(str, ',');
		for (const auto& t : v) {
			res.push_back(std::stoi(t));
		}
		return res;
	}

	std::vector<std::string> Tokinize(const std::string& str, char delimiter)
	{
		std::vector<std::string> result;
		size_t offset = 0;
		while (true)
		{
			auto pos = str.find(delimiter, offset);
			if (pos == std::string::npos) break;
			std::string tok = str.substr(offset, pos - offset);
			result.push_back(tok);
			offset = pos + 1;
		}
		auto pos = str.rfind(delimiter);
		if (pos != std::string::npos) {
			result.push_back(str.substr(pos + 1));
		}
		return result;
	}

	bool strncasecpm(const std::string& a, const std::string& b)
	{
		size_t sz = a.size();
		if (b.size() != sz)
			return false;
		for (size_t i = 0; i < sz; ++i)
			if (tolower(a[i]) != tolower(b[i]))
				return false;
		return true;
	}
}