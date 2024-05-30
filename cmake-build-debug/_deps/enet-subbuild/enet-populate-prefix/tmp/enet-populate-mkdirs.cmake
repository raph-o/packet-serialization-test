# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "F:/C/serialize-test/cmake-build-debug/_deps/enet-src"
  "F:/C/serialize-test/cmake-build-debug/_deps/enet-build"
  "F:/C/serialize-test/cmake-build-debug/_deps/enet-subbuild/enet-populate-prefix"
  "F:/C/serialize-test/cmake-build-debug/_deps/enet-subbuild/enet-populate-prefix/tmp"
  "F:/C/serialize-test/cmake-build-debug/_deps/enet-subbuild/enet-populate-prefix/src/enet-populate-stamp"
  "F:/C/serialize-test/cmake-build-debug/_deps/enet-subbuild/enet-populate-prefix/src"
  "F:/C/serialize-test/cmake-build-debug/_deps/enet-subbuild/enet-populate-prefix/src/enet-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "F:/C/serialize-test/cmake-build-debug/_deps/enet-subbuild/enet-populate-prefix/src/enet-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "F:/C/serialize-test/cmake-build-debug/_deps/enet-subbuild/enet-populate-prefix/src/enet-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
