cmake_minimum_required(VERSION 3.16)
project(WireGuard-Manager)

set(
	spdlog_DIR spdlog/build
)

find_package(
	cxxopts CONFIG REQUIRED
)
find_package(
	spdlog REQUIRED
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
	spdlog::spdlog
)
install(
	TARGETS
	wgm
	RUNTIME DESTINATION bin
)