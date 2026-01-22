cmake_minimum_required(VERSION 3.21)
project(MonsterWar)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 🔹 ImGui 要先定義
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

# 🔹 專案源碼
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# 過濾掉 *_component.cpp
# list(FILTER SOURCES EXCLUDE REGEX "_component\\.cpp$")

# 過濾掉特定檔案
list(REMOVE_ITEM SOURCES
    "${CMAKE_SOURCE_DIR}/src/engine/scene/level_loader.cpp"
)

# 印出清單
message(STATUS "Sources count: ${SOURCES}")


# 🔹 建立執行檔
add_executable(MonsterWar ${SOURCES} ${IMGUI_SOURCES})

# 🔹 SDL3_mixer
set(SDL3_MIXER_DIR "C:/Users/esmon/OneDrive/Desktop/CppGames/MonsterWar/external/sdl_mixer")
include_directories(${SDL3_MIXER_DIR}/include)
link_directories(${SDL3_MIXER_DIR})
target_link_libraries(MonsterWar PRIVATE "${SDL3_MIXER_DIR}/lib/SDL3_mixer.lib")

# 🔹 vcpkg 套件
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

# 設定執行檔輸出目錄
set_target_properties(MonsterWar PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}"
)

if(MSVC)
    target_compile_options(MonsterWar PRIVATE "/utf-8")
    target_link_options(MonsterWar PRIVATE "/SUBSYSTEM:CONSOLE")
endif()