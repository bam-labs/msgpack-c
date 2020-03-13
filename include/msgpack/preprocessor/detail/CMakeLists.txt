add_subdirectory(dmc)
target_sources(msgpackc
	INTERFACE
		check.hpp;
		is_nullary.hpp;
		auto_rec.hpp;
		is_binary.hpp;
		null.hpp;
		is_unary.hpp;
		split.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
