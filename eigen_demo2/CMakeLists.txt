aux_source_directory(./ DIR_TOOT_SRCS)
add_executable(eigen_demo2 ${DIR_TOOT_SRCS} )
target_link_libraries( eigen_demo2 ${OpenMP_EXE_LINKER_FLAGS} "-lblas -llapack -llapacke")