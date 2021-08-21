# List CPU source files.
set(cpuSources alu_ops.cc cpu.cc interrupt.cc flow_ops.cc ops.cc mem_ops.cc registers.cc switches.cc)

# Add CPU sources to 'gb' target.
target_sources(gb PRIVATE ${cpuSources})

# Setup include directories.
target_include_directories(gb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
