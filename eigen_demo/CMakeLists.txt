aux_source_directory(./ DIR_TOOT_SRCS)
add_executable(eigen_demo ${DIR_TOOT_SRCS} )
 target_link_libraries( eigen_demo ${OpenMP_EXE_LINKER_FLAGS})