#ifndef REPL_COMPLEX_PARSER_H
#define REPL_COMPLEX_PARSER_H
#include <complex>
#include <format>
namespace repl
{
template<class T>
struct ArgParser;


template<>
struct ArgParser<std::complex<float>>
{
    static std::complex<float> parse(std::string_view str)
    {
        if (std::isdigit(str.at(str.size() - 1)))
        {
            return std::complex{std::stof(static_cast<std::string>(str))};
        }

        long splitPos = -1;
        for (long i = str.size() - 1; i >= 0; i--)
        {
            if (str[i] == '+' || str[i] == '-')
            {
                if (splitPos == -1)
                {
                    splitPos = i;
                }
                else
                {
                    throw std::runtime_error("Incorrect format for complex number");
                }
            }
            else if (str[i] != 'i' && !(std::isdigit(str[i]) || str[i] == '.')){
                throw std::runtime_error("Wrong character for complex number");
            }
        }
        if (splitPos == -1)
        {
            const auto imString = str.substr(0, str.size() - 1);
            float imaginary = std::stof(static_cast<std::string>(imString));
            return std::complex<float>{0, imaginary};
        }
        const std::string_view realString = str.substr(0, splitPos);
        const std::string_view imaginaryString = str.substr(splitPos, str.size() - splitPos - 1);

        float real = 0;
        float imaginary = 0;
        if (!realString.empty())
        {
            real = std::stof(static_cast<std::string>(realString));
        }
        if (!imaginaryString.empty())
        {
            imaginary = std::stof(static_cast<std::string>(imaginaryString));
        }
        return std::complex<float>{real,imaginary};
    }
};

} // namespace repl
#endif // REPL_COMPLEX_PARSER_H
