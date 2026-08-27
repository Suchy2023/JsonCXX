

#include <cstdint>
#include <limits>
#include <string>
#include <type_traits>
namespace Tests::Helpers
{
template <typename T>
concept Numeric = 
std::is_same_v<T, int64_t> || std::is_same_v<T, uint64_t> ||
std::is_same_v<T, int32_t> || std::is_same_v<T, uint32_t> ||
std::is_same_v<T, int16_t> || std::is_same_v<T, uint16_t> ||
std::is_same_v<T, int8_t> || std::is_same_v<T, uint8_t> ||
std::is_same_v<T, double>;

template <Numeric T> struct NumericHelper
{
    const T max = std::numeric_limits<T>::max();
    const std::string max_string = std::to_string(max);
    const char* max_string_iterator = max_string.data();
    const char* max_string_end = max_string.data() + max_string.size();

    std::string max_string_overflowed = std::to_string(max) + "0";
    const char* max_string_overflowed_iterator = max_string_overflowed.data();
    const char* max_string_overflowed_end = max_string_overflowed.data() + max_string_overflowed.size();

    const T min = std::numeric_limits<T>::min();
    const std::string min_string = std::to_string(min);
    const char* min_string_iterator = min_string.data();
    const char* min_string_end = min_string.data() + min_string.size();

    const std::string min_string_overflowed = std::to_string(min) + "0";
    const char* min_string_overflowed_iterator = min_string_overflowed.data();
    const char* min_string_overflowed_end = min_string_overflowed.data() + min_string_overflowed.size();
};

} // namespace Tests::Helpers