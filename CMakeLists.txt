cmake_minimum_required(VERSION 3.6)

set(project_name my-project) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 20)

add_library(${project_name}-lib
        src/AppComponent.hpp
        src/server/LicenseGenerationController.cpp
        src/server/LicenseGenerationController.hpp
        src/dto/DTOs.hpp
)

## link libs

find_package(oatpp 1.2.0 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
)

target_include_directories(${project_name}-lib PUBLIC src)

## add executables

add_executable(${project_name}-exe
        src/App.cpp
        src/client/LicenseRequestClient.hpp
        src/client/LicenseRequestClient.cpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)



#add_subdirectory(extern)

SET(CMAKE_DISABLE_SOURCE_CHANGES ON)
SET(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

IF(NOT LCC_PROJECT_NAME)
		message(WARNING "You should define a variable LCC_PROJECT_NAME containing the name of the software you want to add a license to.\n \
		 A mock project named `DEFAULT` has been added for you.\n \
		 This project name should correspond to an existing project name in licensecc library. use `lcc project create` to create new projects.") 
	set(LCC_PROJECT_NAME "DEFAULT" CACHE STRING "Project name (name of the software for which you want to issue a license)") 
ENDIF(NOT LCC_PROJECT_NAME)

#project (simple_pc_id CXX)
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

find_package(licensecc 2.0.0 REQUIRED)
message(STATUS "LicenseCC found " ${licensecc_FOUND})
add_executable(request_license 
src/license/main.cpp
src/client/LicenseRequestClient.hpp
src/client/LicenseRequestClient.cpp
src/license/Request.hpp
src/license/Request.cpp)
cmake_policy(SET CMP0028 NEW)
target_link_libraries(request_license 
licensecc::licensecc_static
oatpp::oatpp)

#run open-license-manager tests
INCLUDE(CTest)




add_executable(${project_name}-test
        test/tests.cpp
        test/app/TestComponent.hpp
        test/LicenseGenerationControllerTest.cpp
        test/LicenseGenerationControllerTest.hpp
        src/client/LicenseRequestClient.hpp
        src/client/LicenseRequestClient.cpp
        src/license/Request.hpp
        src/license/Request.cpp)

target_link_libraries(${project_name}-test ${project_name}-lib 
licensecc::licensecc_static)
add_dependencies(${project_name}-test ${project_name}-lib)

# add_executable(${project_name}-getlicense-exe)

set_target_properties(${project_name}-lib ${project_name}-exe ${project_name}-test PROPERTIES
        CXX_STANDARD 20
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

enable_testing()
add_test(project-tests ${project_name}-test)