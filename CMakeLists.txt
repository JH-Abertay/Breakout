cmake_minimum_required(VERSION 3.24)

project(
  "Breakout"
  VERSION 1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME})

include(FetchContent)
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL SYSTEM)
FetchContent_MakeAvailable(SFML)

target_sources(
  ${PROJECT_NAME}
  PRIVATE Breakout/main.cpp
          Breakout/Ball.cpp
          Breakout/Brick.cpp
          Breakout/BrickManager.cpp
          Breakout/GameManager.cpp
          Breakout/Leaderboard.cpp
          Breakout/LocalLeaderboard.cpp
          Breakout/MessagingSystem.cpp
          Breakout/Paddle.cpp
          Breakout/PowerupBase.cpp
          Breakout/PowerupBigPaddle.cpp
          Breakout/PowerupFastBall.cpp
          Breakout/PowerupFireBall.cpp
          Breakout/PowerupManager.cpp
          Breakout/PowerupSlowBall.cpp
          Breakout/PowerupSmallPaddle.cpp
          Breakout/UI.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window
                                              sfml-system)

target_include_directories(
  ${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Breakout/SFML/include"
                          "${CMAKE_CURRENT_SOURCE_DIR}/Breakout")

if(WIN32)
  add_custom_command(
    TARGET main
    COMMENT "Copy OpenAL DLL"
    PRE_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy
      ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
      $<TARGET_FILE_DIR:main>
    VERBATIM)
endif()

# if(${CMAKE_GENERATOR} EQUAL "Ninja Multi-Config")
#   set(DEBUG_FOLDER_LIST Debug Release RelWithDebInfo)
#
#   foreach(dir IN LISTS DEBUG_FOLDER_LIST)
#     add_custom_command(
#       TARGET ${PROJECT_NAME}
#       POST_BUILD
#       COMMAND
#         ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Breakout/font/montS.ttf
#         ${CMAKE_CURRENT_BINARY_DIR}/${dir}/font/montS.ttf
#       COMMENT "Copying font to binary directory")
#   endforeach()
# else()
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Breakout/font/montS.ttf
    ${CMAKE_CURRENT_BINARY_DIR}/font/montS.ttf
  COMMENT "Copying font to binary directory")
# endif()
