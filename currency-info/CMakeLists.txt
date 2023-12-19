# CMakeList.txt : CMake project for currency-info, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

#set(CMAKE_PREFIX_PATH "C:/src/vcpkg/installed/x64-windows/share")

set(CMAKE_TOOLCHAIN_FILE "C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("currency-info")

# Add source to this project's executable.
add_executable (currency-info "main.cpp" "main.h" "currencyretriever.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET currency-info PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

 find_package(CURL REQUIRED)
    target_link_libraries(currency-info PRIVATE CURL::libcurl)

 find_package(nlohmann_json CONFIG REQUIRED)
    target_link_libraries(currency-info PRIVATE nlohmann_json::nlohmann_json)