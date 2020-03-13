target_sources(msgpackc
	INTERFACE
		upper4.hpp;
		upper5.hpp;
		upper2.hpp;
		upper3.hpp;
		upper1.hpp;
		lower5.hpp;
		lower4.hpp;
		lower1.hpp;
		lower3.hpp;
		lower2.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
