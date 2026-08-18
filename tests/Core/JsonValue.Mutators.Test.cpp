

#include "Core/JsonValue.h"
#include "helpers/JsonTypeHelpers.h"
#include "gtest/gtest.h"
#include <gtest/gtest.h>

namespace Tests
{

template <typename T> class JsonValue_Mutators_Test : public ::testing::Test
{
};

TYPED_TEST_SUITE(JsonValue_Mutators_Test, Tests::Helpers::JsonFundamentalType);

TYPED_TEST(JsonValue_Mutators_Test, emplace_works_for_convertible_type)
{
  auto json = Core::JsonValue{};

  const auto param = TypeParam();

  const auto toAdd = TypeParam{};

  const auto emplaceResult = json.emplace("key", toAdd);

  EXPECT_TRUE(emplaceResult.has_value());

  EXPECT_TRUE(json.has("key").has_value());

  EXPECT_EQ(emplaceResult.value().get(), toAdd);
};
} // namespace Tests