# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/KiuPhox/esp/esp-idf/components/bootloader/subproject"
  "D:/Documents/Embedded_System/Lab_4/build/bootloader"
  "D:/Documents/Embedded_System/Lab_4/build/bootloader-prefix"
  "D:/Documents/Embedded_System/Lab_4/build/bootloader-prefix/tmp"
  "D:/Documents/Embedded_System/Lab_4/build/bootloader-prefix/src/bootloader-stamp"
  "D:/Documents/Embedded_System/Lab_4/build/bootloader-prefix/src"
  "D:/Documents/Embedded_System/Lab_4/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Documents/Embedded_System/Lab_4/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Documents/Embedded_System/Lab_4/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
