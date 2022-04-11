project(U03)
set(CGTUTORIAL_PROJ ${CMAKE_CURRENT_SOURCE_DIR})
cmake_minimum_required(VERSION 2.8)

set(ARCHITECTURE "Win32")
if (${CMAKE_GENERATOR} MATCHES "Visual Studio" AND ${CMAKE_GENERATOR} MATCHES "64")
	set(ARCHITECTURE "x64")
endif()

set(CMAKE_MODULE_PATH ${CGTUTORIAL_PROJ}/../cmake/modules)

# Add this dirs to include dirs
include_directories(${CGTUTORIAL_PROJ})
include_directories(${CGTUTORIAL_PROJ}/src/)

#OpenGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
	include_directories(${OPENGL_INCLUDE_DIR})
else()
    message(ERROR " OpenGL not found!")
endif()

#GLUT
if(WIN32)
	set(CMAKE_PREFIX_PATH ${CGTUTORIAL_PROJ}/../contrib/freeglut)
	set(CMAKE_LIBRARY_PATH ${CGTUTORIAL_PROJ}/../contrib/freeglut/lib/${ARCHITECTURE})

endif()

find_package(GLUT REQUIRED)
if(GLUT_FOUND)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})
else()
    message(ERROR " GLUT not found!")
endif()

#GLEW
if(WIN32)
	set(CMAKE_PREFIX_PATH ${CGTUTORIAL_PROJ}/../contrib/glew)
	set(CMAKE_LIBRARY_PATH ${CGTUTORIAL_PROJ}/../contrib/glew/lib/Release/${ARCHITECTURE})
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
		link_directories(${GLEW_LIBRARY_DIRS})
else()
    message(ERROR " GLEW not found!")
endif()

#SFML
if(WIN32)
	set(CMAKE_PREFIX_PATH ${CGTUTORIAL_PROJ}/../contrib/sfml)
	set(CMAKE_LIBRARY_PATH ${CGTUTORIAL_PROJ}/../contrib/sfml/lib/${ARCHITECTURE})
endif()

find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)
if (SFML_FOUND)
	IF(APPLE)
    		include_directories(/usr/local/Cellar/sfml/2.5.1_1/include)
		link_directories(/usr/local/Cellar/sfml/2.5.1_1/lib)
		SET(SFML_LIBRARIES sfml-system sfml-window sfml-graphics)
	ELSE(APPLE)
		include_directories(${SFML_INCLUDE_DIR})
	ENDIF(APPLE)
else()
    message(ERROR " SFML not found!")
endif()


ADD_EXECUTABLE(${PROJECT_NAME}
    src/mainsol.cpp
)

# Set compiler options
function(ADD_CXX_FLAG target opt)
    get_target_property(CXX_FLAGS ${target} COMPILE_FLAGS)
    if(CXX_FLAGS STREQUAL "CXX_FLAGS-NOTFOUND")
      set(CXX_FLAGS "")
    endif()
    set(CXX_FLAGS "${CXX_FLAGS} ${opt}")
    set_target_properties(${target} PROPERTIES COMPILE_FLAGS ${CXX_FLAGS})
endfunction(ADD_CXX_FLAG)

add_cxx_flag(${PROJECT_NAME} "-std=c++11 -g")

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SFML_LIBRARIES} ${GLUT_LIBRARIES})
