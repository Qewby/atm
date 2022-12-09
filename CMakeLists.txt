cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

project(atm)
set(EXE_NAME ${PROJECT_NAME})

set(HEADER_FILES
        src/server/CardNetwork.h
        src/atm/ATM.h
        src/server/ICardValidator.h
        src/server/LuhnValidator.h src/server/IBankServer.h)

set(SOURCE_FILES
        src/main.cpp
        src/server/CardNetwork.cpp
        src/atm/ATM.cpp
        src/server/LuhnValidator.cpp src/utils/String.cpp src/utils/String.h src/server/IBankServer.h src/atm/CardReader.cpp src/atm/CardReader.h src/utils/ReadedCardInfo.cpp src/utils/ReadedCardInfo.h src/server/LocalServer.cpp src/server/LocalServer.h)

add_executable(${EXE_NAME} ${SOURCE_FILES} ${HEADER_FILES})

#find_package(httplib)
#
#FetchContent_Declare(
#        httplib
#        GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
#)
#
#FetchContent_Declare(
#        json
#        URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
#)
#FetchContent_MakeAvailable(json)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.x
)

FetchContent_GetProperties(spdlog)
if (NOT spdlog_POPULATED)
    FetchContent_Populate(spdlog)
    add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
endif ()

target_link_libraries(${EXE_NAME} PRIVATE
#        httplib::httplib
#        nlohmann_json::nlohmann_json
        spdlog::spdlog
        )
