include(Platform/Linux-LCC)
__linux_compiler_lcc(Fortran)
if (CMAKE_Fortran_COMPILER_VERSION VERSION_LESS "1.26.03")
  set(CMAKE_SHARED_LIBRARY_LINK_Fortran_FLAGS "-llfortran")
else()
  set(CMAKE_SHARED_LIBRARY_LINK_Fortran_FLAGS "-lgfortran")
endif()
