# Clang or AppleClang (see CMP0025)
if(NOT DEFINED C_CLANG AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(C_CLANG 1)
elseif(NOT DEFINED C_GCC AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(C_GCC 1)
elseif(NOT DEFINED C_MSVC AND CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(C_MSVC 1)
endif()
