aux_source_directory(./ DIR_TOOT_SRCS)
add_executable(svd_demo ${DIR_TOOT_SRCS} )
target_link_libraries( svd_demo m)
 