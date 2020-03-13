target_sources(msgpackc
	INTERFACE
		cpp11_zone_decl.hpp;
		cpp03_zone_decl.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
