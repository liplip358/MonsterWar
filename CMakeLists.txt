cmake_minimum_required(VERSION 3.21)
project(MonsterWar)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# 專案源碼
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# 建立 target
add_executable(MonsterWar ${SOURCES} ${IMGUI_SOURCES})

# 設定執行檔輸出目錄
set_target_properties(MonsterWar PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}"
)

# SDL3_mixer 手動指定
set(SDL3_MIXER_DIR "C:/Library/SDL3_mixer")
include_directories(${SDL3_MIXER_DIR}/include)
link_directories(${SDL3_MIXER_DIR})
target_link_libraries(MonsterWar PRIVATE "${SDL3_MIXER_DIR}/lib/x64/SDL3_mixer.lib")

# ImGui 手動指定
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)


# vcpkg 套件
find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(MonsterWar PRIVATE SDL3::SDL3)

find_package(SDL3_image CONFIG REQUIRED)
target_link_libraries(MonsterWar PRIVATE $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>)

find_package(SDL3_ttf CONFIG REQUIRED)
target_link_libraries(MonsterWar PRIVATE SDL3_ttf::SDL3_ttf)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(MonsterWar PRIVATE spdlog::spdlog)

find_package(glm CONFIG REQUIRED)
target_link_libraries(MonsterWar PRIVATE glm::glm)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(MonsterWar PRIVATE nlohmann_json::nlohmann_json)

find_package(EnTT CONFIG REQUIRED)
target_link_libraries(MonsterWar PRIVATE EnTT::EnTT)

# 音頻日志選項
option(ENABLE_AUDIO_LOG "启用音频日志" OFF)
if(ENABLE_AUDIO_LOG)
    message(STATUS "音频日志已启用 (ENABLE_AUDIO_LOG=ON)")
    target_compile_definitions(MonsterWar PRIVATE ENABLE_AUDIO_LOG)
else()
    message(STATUS "音频日志已禁用 (ENABLE_AUDIO_LOG=OFF)")
endif()

if(MSVC)
    target_compile_options(MonsterWar PRIVATE "/utf-8")
    target_link_options(MonsterWar PRIVATE "/SUBSYSTEM:CONSOLE")
endif()
