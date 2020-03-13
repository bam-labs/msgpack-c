target_sources(msgpackc
	INTERFACE
		unordered_map.hpp;
		unordered_set.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
