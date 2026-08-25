
#include "JsonC++/Core/JsonValue.Types.h"
#include "JsonC++/Core/JsonValue.h"
#include <cstdint>

int main() {
    

    const auto toPlace = 20;

    auto json = Core::JsonValue{};

    const auto res = json.emplace("key", toPlace);

    const auto x = res.value().get() == toPlace;

    const auto& real = res.value().get();

    const auto isInt = res.value().get().is<int>();
    const auto isInt1 = res.value().get().is<long>();
    const auto isIn2 = res.value().get().is<short>();
    const auto isIn3 = res.value().get().is<int8_t>(); 
       const auto isuInt = res.value().get().is<Core::Json_UInt8>();
       const auto isuInt1 = res.value().get().is<Core::Json_UInt16>();
       const auto isuIn2 = res.value().get().is<Core::Json_UInt32>();
       const auto isuInt3 = res.value().get().is<Core::Json_UInt64>();
    const auto isuIn3 = res.value().get().is<int8_t>();
    const auto isNull = res.value().get().isNull();
    const auto isObject= res.value().get().isObject();
    const auto isArr= res.value().get().isArray();
    const auto issTR= res.value().get().is<Core::Json_String>();
};