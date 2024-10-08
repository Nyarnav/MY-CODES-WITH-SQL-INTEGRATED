#include <algorithm>
#include <string>

std::string convertCharAsString(const unsigned char *passed_string)
    {
        std::string get_string_data;
        std::string ensure_if_correct;
        copy(passed_string, passed_string + strlen((const char *)passed_string), back_inserter(get_string_data));
        
        return get_string_data;
    }
    