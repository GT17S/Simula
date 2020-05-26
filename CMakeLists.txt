cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(Simula)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_INSTALL_PREFIX ~/Bureau)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(EXECUTABLE_OUTPUT_PATH ./bin/${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_FLAGS " -pthread -std=c++14 -funroll-loops -O3 -march=native")
add_compile_options(
  
  "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Boost 1.67.0 REQUIRED)


#Générateur de documentation
# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)
if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ../Simula
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
endif()

# Headers, absolute path
MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.hh)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(header_list)

#Mettre à jour en fonction des nouveaux modules ajoutés
include_directories( ${Qt5Widgets_INCLUDES} ${Qt5Widgets_INCLUDE_DIRS} include/ include/gui /usr/include ${Boost_INCLUDE_DIR} ${header_list})
link_directories(/usr/lib)

#Selection les fichiers à compiler
file(
        GLOB_RECURSE
        HEADERS
        "include/*.hh"

)
file(	
	GLOB_RECURSE
	SOURCES
        "src/*.cc"
	)


file(
    GLOB_RECURSE
    HEADERSGUI
    "include/gui/*.hh"
    "include/gSimulation/ThreadManager.hh"
       )

qt5_wrap_cpp(SOURCES ${HEADERSGUI})
add_executable (Simula ${SOURCES} ${HEADERS} resources.qrc)
target_link_libraries(Simula ${Qt5Widgets_LIBRARIES} Qt5::Widgets Qt5::Xml ${Boost_LIBRARIES} pthread)	


ADD_CUSTOM_TARGET(run COMMAND cd bin/Debug && ./Simula)
ADD_CUSTOM_TARGET(doc COMMAND doxygen doc/Doxyfile)
ADD_CUSTOM_TARGET(sup COMMAND rm -rf bin/ doc/)
