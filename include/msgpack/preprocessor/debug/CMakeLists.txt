target_sources(msgpackc
	INTERFACE
		error.hpp;
		assert.hpp;
		line.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
