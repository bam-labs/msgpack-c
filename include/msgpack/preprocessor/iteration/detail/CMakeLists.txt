add_subdirectory(bounds)
add_subdirectory(iter)
target_sources(msgpackc
	INTERFACE
		self.hpp;
		rlocal.hpp;
		finish.hpp;
		local.hpp;
		start.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
