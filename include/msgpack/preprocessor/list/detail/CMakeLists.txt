add_subdirectory(edg)
add_subdirectory(dmc)
target_sources(msgpackc
	INTERFACE
		fold_right.hpp;
		fold_left.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
