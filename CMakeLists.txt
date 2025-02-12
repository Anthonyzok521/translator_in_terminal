cmake_minimum_required(VERSION 3.28)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("translator_in_terminal")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
find_package(httplib CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

# Add source to this project's executable.
add_executable (translator_in_terminal "translator_in_terminal.cpp" "translator_in_terminal.h")

if (CMAKE_VERSION VERSION_GREATER 3.20)
    set_property(TARGET translator_in_terminal PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(translator_in_terminal PRIVATE httplib::httplib OpenSSL::SSL OpenSSL::Crypto)
