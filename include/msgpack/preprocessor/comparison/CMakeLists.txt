target_sources(msgpackc
	INTERFACE
		greater.hpp;
		equal.hpp;
		less.hpp;
		less_equal.hpp;
		not_equal.hpp;
		greater_equal.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
