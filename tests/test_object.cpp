// test object

#include <dyn/object.h>
#include <string>

namespace dyn
{
    bool test_object(std::string& message)
    {
        object n;
        if (!n.is_null())
        {
            message = "Null expected after default construcor of object.";
            return false;
        }

        return true;
    }
}

// Unicode signature: Владимир Керимов
