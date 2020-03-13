target_sources(msgpackc
	INTERFACE
		objc.h;
		stdc.h;
		cuda.h;
		stdcpp.h
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
