target_sources(msgpackc
	INTERFACE
		vms.h;
		zos.h;
		uc.h;
		gnu.h;
		cloudabi.h;
		_prefix.h
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
