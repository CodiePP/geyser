
cmake_minimum_required(VERSION 2.8)

project(UT_geyser)

IF(DEFINED CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release DebugProfile RelWithDebInfo MinSizeRel.")
ELSE()
   SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release DebugProfile RelWithDebInfo MinSizeRel.")
ENDIF()

# boost
#set(BOOST_ROOT "/usr/local/boost_1_57_0")
add_definitions( -DBOOST_ALL_DYN_LINK )
set(Boost_ADDITIONAL_VERSIONS "1.57")
set(Boost_DEBUG OFF)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_MULTITHREADED ON)
find_package( Boost 1.55.0 REQUIRED COMPONENTS system filesystem chrono thread
    date_time unit_test_framework )
LINK_DIRECTORIES ( ${Boost_LIBRARY_DIRS} )
INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIRS})

# mine
include_directories(../src)

file(GLOB SRCS ut*.cpp mocks/*.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")

        add_executable ( ${PROJECT_NAME}
          ${SRCS}
        )

target_link_libraries ( ${PROJECT_NAME}
          geyser_${CMAKE_BUILD_TYPE}
          ${Boost_LIBRARIES}
        )
endif()

if (CMAKE_BUILD_TYPE STREQUAL "DebugProfile")
        add_executable ( p${PROJECT_NAME}
                ${SRCS}
        )
        set_target_properties(p${PROJECT_NAME} PROPERTIES LINK_FLAGS "-fprofile-arcs -ftest-coverage ")
        target_link_libraries ( p${PROJECT_NAME}
                geyser_p${CMAKE_BUILD_TYPE}
                #${libs}
                #gcov
                ${Boost_LIBRARIES}
        )

endif()


