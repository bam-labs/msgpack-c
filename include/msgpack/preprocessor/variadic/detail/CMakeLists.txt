target_sources(msgpackc
	INTERFACE
		is_single_return.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
