target_sources(msgpackc
	INTERFACE
		free.h;
		net.h;
		bsdi.h;
		open.h;
		dragonfly.h
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
