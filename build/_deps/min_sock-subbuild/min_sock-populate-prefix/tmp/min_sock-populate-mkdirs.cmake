# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/marcos/Escritorio/RoboCup/build/_deps/min_sock-src"
  "/home/marcos/Escritorio/RoboCup/build/_deps/min_sock-build"
  "/home/marcos/Escritorio/RoboCup/build/_deps/min_sock-subbuild/min_sock-populate-prefix"
  "/home/marcos/Escritorio/RoboCup/build/_deps/min_sock-subbuild/min_sock-populate-prefix/tmp"
  "/home/marcos/Escritorio/RoboCup/build/_deps/min_sock-subbuild/min_sock-populate-prefix/src/min_sock-populate-stamp"
  "/home/marcos/Escritorio/RoboCup/build/_deps/min_sock-subbuild/min_sock-populate-prefix/src"
  "/home/marcos/Escritorio/RoboCup/build/_deps/min_sock-subbuild/min_sock-populate-prefix/src/min_sock-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/marcos/Escritorio/RoboCup/build/_deps/min_sock-subbuild/min_sock-populate-prefix/src/min_sock-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/marcos/Escritorio/RoboCup/build/_deps/min_sock-subbuild/min_sock-populate-prefix/src/min_sock-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
