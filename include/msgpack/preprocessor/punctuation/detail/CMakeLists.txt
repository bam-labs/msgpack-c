target_sources(msgpackc
	INTERFACE
		is_begin_parens.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
