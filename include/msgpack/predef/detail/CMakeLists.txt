target_sources(msgpackc
	INTERFACE
		comp_detected.h;
		endian_compat.h;
		test.h;
		platform_detected.h;
		os_detected.h;
		_cassert.h;
		_exception.h;
		test_def.h
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
