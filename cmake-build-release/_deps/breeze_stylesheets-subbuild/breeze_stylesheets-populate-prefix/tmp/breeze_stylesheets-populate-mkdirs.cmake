# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/tommetz/CLionProjects/vteg/cmake-build-release/_deps/breeze_stylesheets-src"
  "/Users/tommetz/CLionProjects/vteg/cmake-build-release/_deps/breeze_stylesheets-build"
  "/Users/tommetz/CLionProjects/vteg/cmake-build-release/_deps/breeze_stylesheets-subbuild/breeze_stylesheets-populate-prefix"
  "/Users/tommetz/CLionProjects/vteg/cmake-build-release/_deps/breeze_stylesheets-subbuild/breeze_stylesheets-populate-prefix/tmp"
  "/Users/tommetz/CLionProjects/vteg/cmake-build-release/_deps/breeze_stylesheets-subbuild/breeze_stylesheets-populate-prefix/src/breeze_stylesheets-populate-stamp"
  "/Users/tommetz/CLionProjects/vteg/cmake-build-release/_deps/breeze_stylesheets-subbuild/breeze_stylesheets-populate-prefix/src"
  "/Users/tommetz/CLionProjects/vteg/cmake-build-release/_deps/breeze_stylesheets-subbuild/breeze_stylesheets-populate-prefix/src/breeze_stylesheets-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/tommetz/CLionProjects/vteg/cmake-build-release/_deps/breeze_stylesheets-subbuild/breeze_stylesheets-populate-prefix/src/breeze_stylesheets-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/tommetz/CLionProjects/vteg/cmake-build-release/_deps/breeze_stylesheets-subbuild/breeze_stylesheets-populate-prefix/src/breeze_stylesheets-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
