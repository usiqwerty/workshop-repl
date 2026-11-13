#ifndef REPL_COMPLEX_PARSER_H
#define REPL_COMPLEX_PARSER_H
#include <complex>
namespace repl
{
template <class T>
struct ArgParser;

template <>
struct ArgParser<std::complex<float>>
{
    static std::complex<float> parse(std::string_view str)
    {
        float real = 0;
        float imaginary = 0;

        bool realDone = false;

        for (unsigned long i = 0; i < str.size(); i++)
        {
            const char digit = str[i];
            if (digit == ' ')
            {
                continue;
            }
            if (!realDone)
            {
                if (digit == '+' || digit == '-')
                {
                    realDone = true;
                    if (digit == '-')
                    {
                        imaginary = -1;
                    }
                    continue;
                }
                real = real * 10 + static_cast<float>(digit - '0');
            }
            else
            {
                if (digit == 'i')
                {
                    if (imaginary == 0)
                    {

                    }
                    break;
                }
                imaginary = imaginary * 10 + static_cast<float>(digit - '0');
            }

        }
        return std::complex<float>{real, imaginary};
    }
};

}
#endif // REPL_COMPLEX_PARSER_H
