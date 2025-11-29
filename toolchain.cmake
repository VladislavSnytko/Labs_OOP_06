# Toolchain file для GCC из w64devkit
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER "C:/w64devkit/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/w64devkit/bin/g++.exe")

# Пропускаем проверку компилятора
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
