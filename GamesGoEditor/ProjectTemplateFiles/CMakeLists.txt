cmake_minimum_required(VERSION 3.20)
project(GamesGoGame LANGUAGES CXX)
add_executable(GamesGoGame
     ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game.cpp
)
target_include_directories(GamesGoGame
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
)
target_link_directories(GamesGoGame
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(GamesGoGame
    PRIVATE
        GamesGoEngine
)
add_custom_command(TARGET GamesGoGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/GamesGoEngine.dll"
        "$<TARGET_FILE_DIR:GamesGoGame>/GamesGoEngine.dll"
)