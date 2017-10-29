// test scalar

#include <dyn/scalar.h>
#include <string>

namespace dyn
{
    bool test_scalar(std::string& message)
    {
        scalar<int> i = 1234;
        if (i != 1234)
        {
            message = "Object expected to be equal to 1234.";
            return false;
        }
        else if (i <= 1233 || i >= 1235)
        {
            message = "Object expected to be greater than 1233 and lesser than 1235.";
            return false;
        }
        else if (!i)
        {
            message = "Object expected to be represented as boolean true.";
            return false;
        }

        scalar<float> f = 56.789f;
        if (f != 56.789f)
        {
            message = "Object expected to be equal to 56.789f.";
            return false;
        }
        else if (f < 56.788f || f > 56.790f)
        {
            message = "Object expected to be greater than 56.788f and lesser than 56.790f";
            return false;
        }
        else if(!f)
        {
            message = "Object expected to be represented as boolean true.";
            return false;
        }

        scalar<bool> b = true;
        if (!b)
        {
            message = "Object expected to be boolean true.";
            return false;
        }

        scalar<unsigned long long> u = 1234567890uLL;
        if (u != 1234567890uLL)
        {
            message = "Object expected to be equal to 1234567890uLL.";
            return false;
        }

        scalar<char> c = '*';
        if (c != '*')
        {
            message = "Object expected to be equal to '*'.";
            return false;
        }

        return true;
    }
}

// Unicode signature: Владимир Керимов
