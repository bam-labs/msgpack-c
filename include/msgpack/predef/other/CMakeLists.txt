target_sources(msgpackc
	INTERFACE
		endian.h;
		workaround.h
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
