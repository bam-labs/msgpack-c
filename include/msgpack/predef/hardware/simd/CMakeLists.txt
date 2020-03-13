add_subdirectory(x86_amd)
add_subdirectory(ppc)
add_subdirectory(x86)
add_subdirectory(arm)
target_sources(msgpackc
	INTERFACE
		arm.h;
		x86.h;
		ppc.h;
		x86_amd.h
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
