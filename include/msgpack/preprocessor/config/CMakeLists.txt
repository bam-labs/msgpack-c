target_sources(msgpackc
	INTERFACE
		config.hpp;
		limits.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
