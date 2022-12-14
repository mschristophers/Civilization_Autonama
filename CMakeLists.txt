cmake_minimum_required(VERSION 3.10)

#Set up project
project(empire VERSION 1.0)

#Set executable
add_executable(${PROJECT_NAME}     
    src/main.cpp
    src/Application.cpp
    src/ResourceStuff/ResourceHolder.cpp
    src/Util/Common.cpp
    src/Util/Random.cpp
    src/Util/FPSCounter.cpp
    src/Feature/EmpireStatistics.cpp
    src/Feature/EmpireCreator.cpp
    src/Feature/Map.cpp
    src/Feature/CustomEmpireCreator.cpp
    src/Feature/Empire.cpp
    src/Feature/RandomEmpireCreator.cpp
    src/Feature/World.cpp
    src/Feature/Person.cpp
)

#Set C++17
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

#Set flags
if(MSVC)
  	target_compile_options(${PROJECT_NAME} PRIVATE 
    	/W4 /WX)
else()
  	target_compile_options(${PROJECT_NAME} PRIVATE 
		-Wall -Wextra -pedantic )
        #-Werror)		#Warning flags
endif()

#Set module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

#Find libraries
find_package(Threads)
find_package(SFML REQUIRED audio network graphics window system)

#Finally
target_link_libraries(${PROJECT_NAME} 
    Threads::Threads 
    ${SFML_LIBRARIES} 
    ${SFML_DEPENDENCIES}
)