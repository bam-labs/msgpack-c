add_subdirectory(msgpack)
target_sources(msgpackc
	INTERFACE
		vrefbuffer.c;
		unpack.c;
		objectc.c;
		zone.c;
		version.c
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
