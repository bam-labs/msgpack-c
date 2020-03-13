add_subdirectory(std)
add_subdirectory(c)
target_sources(msgpackc
	INTERFACE
		c.h;
		std.h
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
