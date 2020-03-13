add_subdirectory(detail)
target_sources(msgpackc
	INTERFACE
		self.hpp;
		iterate.hpp;
		local.hpp
)
target_include_directories(msgpackc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
