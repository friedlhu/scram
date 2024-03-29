include_directories(SYSTEM "catch2/single_include")

# Include the project headers.
include_directories("${CMAKE_SOURCE_DIR}/src")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SCRAM_CORE_TEST_SOURCE
  linear_map_tests.cc
  xml_stream_tests.cc
  settings_tests.cc
  config_tests.cc
  element_tests.cc
  event_tests.cc
  expression_tests.cc
  extern_function_tests.cc
  ccf_group_tests.cc
  fault_tree_tests.cc
  alignment_tests.cc
  pdag_tests.cc
  initializer_tests.cc
  serialization_tests.cc
  risk_analysis_tests.cc
  bench_core_tests.cc
  bench_two_train_tests.cc
  bench_lift_tests.cc
  bench_ne574_tests.cc
  bench_theatre_tests.cc
  bench_three_motor_tests.cc
  bench_200_event_tests.cc
  bench_small_tree_tests.cc
  bench_bscu_tests.cc
  bench_chinese_tree_tests.cc
  bench_baobab1_tests.cc
  bench_baobab2_tests.cc
  bench_CEA9601_tests.cc
  bench_hipps_tests.cc
  bench_attack.cc
  bench_gas_leak.cc
  performance_tests.cc
  )

# Make tests switch and run in install directory.
configure_file(scram_unit_test_driver.cc.in scram_unit_test_driver.cc @ONLY)

add_executable(scram_tests ${CMAKE_CURRENT_BINARY_DIR}/scram_unit_test_driver.cc ${SCRAM_CORE_TEST_SOURCE})
target_link_libraries(scram_tests ${LIBS} scram)
target_compile_options(scram_tests PRIVATE $<$<CONFIG:DEBUG>:${SCRAM_CXX_FLAGS_DEBUG}>)

install(
  TARGETS scram_tests
  RUNTIME DESTINATION bin
  COMPONENT testing
  )

# Create dummy library to test dynamic loading and extern function.
add_library(scram_dummy_extern SHARED scram_dummy_extern.cc)
target_compile_options(scram_dummy_extern PRIVATE $<$<CONFIG:DEBUG>:${SCRAM_CXX_FLAGS_DEBUG}>)
if(WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
install(
  TARGETS scram_dummy_extern
  LIBRARY DESTINATION "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
  ARCHIVE DESTINATION "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/static"
  RUNTIME DESTINATION "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
  COMPONENT testing
  )
endif()
