target_sources(msgpackc
	INTERFACE
		windows_desktop.h;
		ios.h;
		windows_runtime.h;
		windows_store.h;
		mingw64.h;
		cloudabi.h;
		windows_uwp.h;
		mingw.h;
		windows_server.h;
		windows_phone.h;
		mingw32.h;
		windows_system.h
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
