

#include "Core/JsonValue.h"
#include "Core/JsonValue.Types.h"
#include "gtest/gtest.h"
#include <type_traits>
#include <variant>

namespace Tests
{

class Equal_Overload
    : public ::testing::TestWithParam<Core::JsonVariant>
{
};

TEST_P(Equal_Overload, is_comparable_to)
{

  std::visit(
      [](auto &&val)
      {
        using T = std::remove_cvref_t<decltype(val)>;

        EXPECT_TRUE(val == val);
      },
      GetParam());
};

INSTANTIATE_TEST_SUITE_P(JsonValue_Comparers_Test, Equal_Overload,
                         ::testing::Values(Core::JsonNull{}, Core::JsonInt{},
                                           Core::JsonDouble{},
                                           Core::JsonString{},
                                           Core::JsonObject{},
                                           Core::JsonArray{}));

} // namespace Tests