
#include "Core/JsonValue.h"
#include "Core/JsonValue.Types.h"
#include "gtest/gtest.h"
#include <string>

namespace Tests {

template <typename T> class JsonValue_Checkers_Test : public ::testing::Test {};

using JsonUnderlyingTypes =
    ::testing::Types<Core::JsonNull, Core::JsonInt, Core::JsonDouble,
                     Core::JsonString, Core::JsonObject, Core::JsonArray>;

TYPED_TEST_SUITE(JsonValue_Checkers_Test, JsonUnderlyingTypes);

TYPED_TEST(JsonValue_Checkers_Test, is_returns_true_for_own_type) {
  using T = TypeParam;

  Core::JsonValue json{T{}};

  EXPECT_TRUE(json.is<T>());
}
} // namespace Tests

TEST(JsonValue_Checkers_Test, has_works) {

  Core::JsonValue json{Core::JsonObject{{"key", 1}}};

  EXPECT_TRUE(json.has("key"));
}
