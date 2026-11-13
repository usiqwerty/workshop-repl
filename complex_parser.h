#ifndef REPL_COMPLEX_PARSER_H
#define REPL_COMPLEX_PARSER_H
#include <complex>
namespace repl
{
template<class T>
struct ArgParser;

template<>
struct ArgParser<std::complex<float>>
{
    static std::complex<float> parse(std::string_view str)
    {
        if (str.at(str.size() - 1) != 'i')
        {
            return std::complex{std::stof(static_cast<std::string>(str))};
        }

        long splitPos = -1;
        for (long i = str.size() - 1; i >= 0; i--)
        {
            if (str[i] == '+' || str[i] == '-')
            {
                splitPos = i;
                break;
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
        if (realString.size() > 0)
        {
            real = std::stof(static_cast<std::string>(realString));
        }
        if (imaginaryString.size() > 0)
        {
            imaginary = std::stof(static_cast<std::string>(imaginaryString));
        }
        return std::complex<float>{real,imaginary};
    }
};

} // namespace repl
#endif // REPL_COMPLEX_PARSER_H
