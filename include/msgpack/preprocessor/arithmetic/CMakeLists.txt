add_subdirectory(detail)
target_sources(msgpackc
	INTERFACE
		add.hpp;
		sub.hpp;
		dec.hpp;
		div.hpp;
		mod.hpp;
		inc.hpp;
		mul.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
