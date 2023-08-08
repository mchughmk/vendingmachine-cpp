include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
FetchContent_MakeAvailable(googletest)

include_directories (${VendingMachine_SOURCE_DIR}/src)

add_executable(
  vendingmachine-test
  vendingmachine_test.cc
  coinpaymentprocessor_test.cc
  paymentdb_test.cc
  vendingmachine_integration_test.cc
  coinpaymentprocessor_integration_test.cc
)

target_link_libraries(
  vendingmachine-test
  VendingMachine
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(vendingmachine-test)