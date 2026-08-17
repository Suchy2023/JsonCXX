

add_project_test(
    core_tests
    JsonValue_Test.cpp
    JsonValue.Accessors.Test.cpp
    JsonValue.Checkers.Test.cpp
    JsonValue.Comparers.Test.cpp
    JsonValue.Constructors.Test.cpp
)

target_link_libraries(core_tests PRIVATE Core)