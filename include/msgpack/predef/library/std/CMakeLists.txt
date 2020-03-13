target_sources(msgpackc
	INTERFACE
		stlport.h;
		modena.h;
		roguewave.h;
		msl.h;
		stdcpp3.h;
		cxx.h;
		libcomo.h;
		_prefix.h;
		vacpp.h;
		sgi.h;
		dinkumware.h
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
