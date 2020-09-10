#pragma once

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <inttypes.h>

class Ini_file
{
public:
    Ini_file();
    ~Ini_file();
    bool Open(const std::string& filename);
    void Save();
    void Close();
    int         Get_value(const std::string& section, const std::string& parameter, int default_value);
    int64_t     Get_value(const std::string& section, const std::string& parameter, int64_t default_value);
    uint64_t    Get_value(const std::string& section, const std::string& parameter, uint64_t default_value);
    float       Get_value(const std::string& section, const std::string& parameter, float default_value);
    std::string Get_value(const std::string& section, const std::string& parameter, const char* default_value);
    bool        Get_value(const std::string& section, const std::string& parameter, bool default_value);
    void        Set_value(const std::string& section, const std::string& parameter, int value);
    void        Set_value(const std::string& section, const std::string& parameter, int64_t value);
    void        Set_value(const std::string& section, const std::string& parameter, uint64_t value);
    void        Set_value(const std::string& section, const std::string& parameter, float value);
    void        Set_value(const std::string& section, const std::string& parameter, const char* value);
    void        Set_value(const std::string& section, const std::string& parameter, bool value);
    bool        ParameterExists(const std::string& section, const std::string& parameter);
    typedef std::pair<std::string/*name*/, std::string/*value*/> Ini_parameter;
private:
    std::fstream m_file_stream;
    std::map<std::string/*section*/, std::vector<Ini_parameter>> m_content;
    void Read_content();
    void Write_content();
    std::string Get_section_name(const std::string& line);
    void Parse_parameter(const std::string& section, const std::string& line);
    Ini_parameter& Find_parameter(const std::string& section, const std::string& parameter);
};