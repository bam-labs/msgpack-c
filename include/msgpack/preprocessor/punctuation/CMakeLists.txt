add_subdirectory(detail)
target_sources(msgpackc
	INTERFACE
		remove_parens.hpp;
		paren_if.hpp;
		comma.hpp;
		is_begin_parens.hpp;
		comma_if.hpp;
		paren.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
