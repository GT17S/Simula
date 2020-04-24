cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(Simula)

set(CMAKE_AUTOMOC ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_INSTALL_PREFIX ~/Bureau)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(EXECUTABLE_OUTPUT_PATH ./bin/${CMAKE_BUILD_TYPE})

add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Boost 1.40.0 REQUIRED)

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

#Mettre à jour en fonction des nouveaux modules ajoutés
include_directories( ${Qt5Widgets_INCLUDES} include/ /usr/include ${Boost_INCLUDE_DIR})
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

add_executable (Simula ${SOURCES} ${HEADERS})
target_link_libraries(Simula ${Qt5Widgets_LIBRARIES} Qt5::Xml ${Boost_LIBRARIES})	

ADD_CUSTOM_TARGET(run COMMAND cd bin/Debug && ./Simula)
ADD_CUSTOM_TARGET(doc COMMAND doxygen docs/Doxyfile)