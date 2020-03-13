add_subdirectory(simd)
target_sources(msgpackc
	INTERFACE
		simd.h
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
