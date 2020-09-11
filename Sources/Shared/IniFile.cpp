#include "IniFile.h"
#include <algorithm> 
#include <cctype>
#include <sys/stat.h>
#include <string.h> 

Ini_file::Ini_parameter empty_parameter = std::make_pair("", "");

Ini_file::Ini_file()
{
}

Ini_file::~Ini_file()
{
    Close();
}

inline bool exists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

bool Ini_file::Open(const std::string& filename)
{
    std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out;
    if (!exists(filename)) mode |= std::ios_base::trunc;
    m_file_stream.open(filename, mode);
    if (m_file_stream.is_open()) {
        Read_content();
        return true;
    }
    else {
        return false;
    }
}

void Ini_file::Save()
{
    if (m_file_stream.is_open()) {
        Write_content();
        m_file_stream.flush();
    }
}

void Ini_file::Close()
{
    if (m_file_stream.is_open()) {
        m_file_stream.close();
    }
}

int Ini_file::Get_value(const std::string& section, const std::string& parameter, int default_value)
{
    auto param = Find_parameter(section, parameter);
    if (param == empty_parameter) {
        return default_value;
    }

    int res;
    try
    {
        res = std::stoi(param.second);
    }
    catch (const std::exception&)
    {
        res = default_value;
    }
    return res;
}

int64_t Ini_file::Get_value(const std::string& section, const std::string& parameter, int64_t default_value)
{
    auto param = Find_parameter(section, parameter);
    if (param == empty_parameter) {
        return default_value;
    }

    int64_t res;
    try
    {
        res = std::stoll(param.second);
    }
    catch (const std::exception&)
    {
        res = default_value;
    }
    return res;
}

uint64_t Ini_file::Get_value(const std::string& section, const std::string& parameter, uint64_t default_value)
{
    auto param = Find_parameter(section, parameter);
    if (param == empty_parameter) {
        return default_value;
    }

    uint64_t res;
    try
    {
        res = std::stoull(param.second);
    }
    catch (const std::exception&)
    {
        res = default_value;
    }
    return res;
}

float Ini_file::Get_value(const std::string& section, const std::string& parameter, float default_value)
{
    auto param = Find_parameter(section, parameter);
    if (param == empty_parameter) {
        return default_value;
    }

    float res;
    try
    {
        res = std::stof(param.second);
    }
    catch (const std::exception&)
    {
        res = default_value;
    }
    return res;
}

std::string Ini_file::Get_value(const std::string& section, const std::string& parameter, const char* default_value)
{
    auto param = Find_parameter(section, parameter);
    if (param == empty_parameter) {
        return default_value;
    }

    return param.second;
}

bool Ini_file::Get_value(const std::string& section, const std::string& parameter, bool default_value)
{
    auto& param = Find_parameter(section, parameter);
    if (param == empty_parameter) {
        return default_value;
    }
#if _WIN32
    return _stricmp("true", param.second.c_str()) == 0;
#else
    return strcasecmp("true", param.second.c_str()) == 0;
#endif
}

void Ini_file::Set_value(const std::string& section, const std::string& parameter, const char* value)
{
    auto& param = Find_parameter(section, parameter);
    if (param == empty_parameter) {
        m_content[section].push_back(std::make_pair(parameter, value));
    }
    else {
        param.second = value;
    }
}

void Ini_file::Set_value(const std::string& section, const std::string& parameter, int value)
{
    Set_value(section, parameter, std::to_string(value).c_str());
}

void Ini_file::Set_value(const std::string& section, const std::string& parameter, int64_t value)
{
    Set_value(section, parameter, std::to_string(value).c_str());
}

void Ini_file::Set_value(const std::string& section, const std::string& parameter, uint64_t value)
{
    Set_value(section, parameter, std::to_string(value).c_str());
}

void Ini_file::Set_value(const std::string& section, const std::string& parameter, float value)
{
    Set_value(section, parameter, std::to_string(value).c_str());
}

void Ini_file::Set_value(const std::string& section, const std::string& parameter, bool value)
{
    Set_value(section, parameter, value? "True" : "False");
}

bool Ini_file::ParameterExists(const std::string& section, const std::string& parameter)
{
    return Find_parameter(section, parameter) != empty_parameter;
}

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

std::string Ini_file::Get_section_name(const std::string& line)
{
    size_t pos = line.find_last_of(']');
    if (pos == std::string::npos) return "";
    std::string res = line.substr(1, pos - 1);
    trim(res);
    return res;
}

void Ini_file::Parse_parameter(const std::string& section, const std::string& line)
{
    size_t pos = line.find_last_of('=');
    if (pos == std::string::npos || pos < 1) return;

    std::string name = line.substr(0, pos);
    std::string val  = line.substr(pos+1, line.length() - name.length() - 1);
    trim(name);
    ltrim(val);
    m_content[section].push_back(std::make_pair(name, val));
}

Ini_file::Ini_parameter& Ini_file::Find_parameter(const std::string& section, const std::string& parameter)
{
    const auto& sit = m_content.find(section);
    if (sit == m_content.end()) return empty_parameter;

    for (auto& pit : sit->second) {
        if (pit.first == parameter) return pit;
    }

    return empty_parameter;
}

void Ini_file::Read_content()
{
    std::string line;
    std::string section;
    std::string tmp;
    while (std::getline(m_file_stream, line)) {
        if (line[0] == '[') {
            tmp = Get_section_name(line);
            if (!tmp.empty()) {
                section = tmp;
            }
        }
        else if (!line.empty() && !section.empty()) {
            Parse_parameter(section, line);
        }
    }
}

void Ini_file::Write_content()
{
    m_file_stream.clear();
    m_file_stream.seekg(0, std::ios::beg);

    for (const auto& sit : m_content) {
        m_file_stream << "[" << sit.first << "]\n";
        for (const auto& pit : sit.second)
        {
            m_file_stream << pit.first << "=" << pit.second << "\n";
        }
    }
}
