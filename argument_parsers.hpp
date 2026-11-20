#pragma once

#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>

namespace repl
{

template<class T>
struct ArgParser;

template<>
struct ArgParser<float>
{
    static float parse(std::string_view str)
    {
        try
        {
            return std::stof(std::string{str});
        }
        catch (const std::invalid_argument& err)
        {
            // std::stof message is kind of stupid,
            // we will replace it
            std::ostringstream msg{};
            msg << "failed to parse float from '" << str << '\'';
            throw std::invalid_argument(msg.str());
        }
        catch (const std::out_of_range& err)
        {
            std::ostringstream msg{};
            msg << "value is out of range for float: '" << str << '\'';
            throw std::out_of_range(msg.str());
        }
    }
};

template<>
struct ArgParser<std::string_view>
{
    static std::string_view parse(std::string_view str)
    {
        return str;
    }
};
template<>
struct ArgParser<char>
{
    static char parse(std::string_view str)
    {
        return str.at(0);
    }
};

template<>
struct ArgParser<std::size_t>
{
    static std::size_t parse(std::string_view str)
    {
        return std::stol(std::string {str});
    }
};

} // namespace repl
