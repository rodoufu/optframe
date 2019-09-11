file(GLOB_RECURSE lib_sources *)
list(FILTER lib_sources INCLUDE REGEX "\\.cpp$")

add_library(npp ${lib_sources})