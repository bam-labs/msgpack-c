add_subdirectory(detail)
target_sources(msgpackc
	INTERFACE
		deduce_d.hpp;
		expr_iif.hpp;
		if.hpp;
		while.hpp;
		iif.hpp;
		expr_if.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
