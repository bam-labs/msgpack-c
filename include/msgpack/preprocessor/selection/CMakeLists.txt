target_sources(msgpackc
	INTERFACE
		min.hpp;
		max.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
