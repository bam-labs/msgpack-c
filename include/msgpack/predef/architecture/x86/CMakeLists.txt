target_sources(msgpackc
	INTERFACE
		32.h;
		64.h
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
