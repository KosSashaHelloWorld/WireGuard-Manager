cmake_minimum_required(VERSION 3.16)
project(WireGuard-Manager)

find_package(
	cxxopts CONFIG REQUIRED
)

add_executable(
	wgm 
	main.cpp
	wireguard.h
	wireguard.c
)
set_source_files_properties(
	wireguard.c 
	PROPERTIES
	LANGUAGE C
)
target_link_libraries(
	wgm
	PRIVATE
	cxxopts::cxxopts
)
install(
	TARGETS
	wgm
	RUNTIME DESTINATION bin
)