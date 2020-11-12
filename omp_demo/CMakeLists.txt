aux_source_directory(./ DIR_TOOT_SRCS)
add_executable(omp_demo ${DIR_TOOT_SRCS} )
 target_link_libraries( omp_demo ${OpenMP_EXE_LINKER_FLAGS})