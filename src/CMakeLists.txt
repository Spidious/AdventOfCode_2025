set(AOC_DIR ${CMAKE_SOURCE_DIR}/challenges)

add_executable(main "main.cpp" ${AOC_DIR}/${AOC_CHAL}.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif()

target_compile_definitions(main PRIVATE
        AOC_DATA_FILE="${AOC_DIR}/chal_data/${AOC_CHAL}.txt"
)

target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)
#target_link_libraries(main PRIVATE main_lib)
