cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

project(atm)
set(EXE_NAME ${PROJECT_NAME})

set(HEADER_FILES
        src/server/cards/CardNetwork.h
        src/atm/ATM.h
        src/server/cards/ICardValidator.h
        src/server/cards/LuhnValidator.h src/server/IBankServer.h)

set(SOURCE_FILES
        src/main.cpp
        src/server/cards/CardNetwork.cpp
        src/atm/ATM.cpp
        src/server/cards/LuhnValidator.cpp src/utils/String.cpp src/utils/String.h src/server/IBankServer.h src/atm/CardReader.cpp src/atm/CardReader.h src/utils/ReadedCardInfo.cpp src/utils/ReadedCardInfo.h src/server/local/LocalServer.cpp src/server/local/LocalServer.h src/server/cards/ACard.cpp src/server/cards/ACard.h src/server/cards/CardFactory.cpp src/server/cards/CardFactory.h src/server/cards/ICard.h src/server/services/ICardService.h src/server/services/in-memory/InMemoryCardService.cpp src/server/services/IAccountService.h src/server/services/in-memory/InMemoryAccountService.cpp src/server/services/in-memory/InMemoryAccountService.h src/server/services/ServiceFactory.cpp src/server/services/ServiceFactory.h)

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

target_include_directories(${EXE_NAME} PRIVATE src)

target_link_libraries(${EXE_NAME} PRIVATE
#        httplib::httplib
#        nlohmann_json::nlohmann_json
        spdlog::spdlog
        )
