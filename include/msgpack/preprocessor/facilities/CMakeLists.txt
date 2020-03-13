add_subdirectory(detail)
target_sources(msgpackc
	INTERFACE
		is_1.hpp;
		is_empty_variadic.hpp;
		expand.hpp;
		apply.hpp;
		empty.hpp;
		is_empty.hpp;
		is_empty_or_1.hpp;
		identity.hpp;
		overload.hpp;
		intercept.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
