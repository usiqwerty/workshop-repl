#include <iostream>

#include "repl.hpp"

namespace repl
{
namespace strings
{

class Concat : public BaseCommand<Concat, std::string, std::string_view,
                   std::string_view>
{
public:
    const std::string_view longName = "concat";
    const std::string_view shortName = "ct";
    Concat() = default;
    std::string operator()(const std::string_view a,
        const std::string_view b) const
    {
        return std::string{a} + std::string{b};
    }
};
class Find : public BaseCommand<Find, std::size_t, std::string_view, char>
{
public:
    const std::string_view longName = "find";
    const std::string_view shortName = "fd";
    Find() = default;
    std::size_t operator()(const std::string_view a, char c) const
    {
        std::size_t result = a.find(c);
        if (result == std::string::npos)
        {
            throw std::out_of_range("Could not find character");
        }
        return result;
    }
};
class Length : public BaseCommand<Length, std::size_t, std::string_view>
{
public:
    const std::string_view longName = "length";
    const std::string_view shortName = "len";
    Length() = default;
    std::size_t operator()(const std::string_view a) const
    {
        return a.size();
    }
};
class StringCharAt : public BaseCommand<StringCharAt, char, std::string_view, std::size_t>
{
public:
    const std::string_view longName = "atindex";
    const std::string_view shortName = "at";
    StringCharAt() = default;
    char operator()(const std::string_view a, std::size_t idx) const
    {
        return a.at(idx);
    }
};
using Repl = ::repl::Repl<Concat, Find, Length, StringCharAt>;

} // namespace strings
} // namespace repl

int main()
{
    using namespace repl::strings;

    try
    {
        Repl repl{std::cin, std::cout, "str"};
        repl.Run();
        return EXIT_SUCCESS;
    }
    catch (const std::exception& err)
    {
        std::cerr << "Error: " << err.what() << '\n';
    }
    catch (...)
    {
        std::cerr << "Error: unknown\n";
    }
    return EXIT_FAILURE;
}
