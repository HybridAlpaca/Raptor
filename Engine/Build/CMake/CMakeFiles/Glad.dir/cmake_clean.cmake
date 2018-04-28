file(REMOVE_RECURSE
  "libGlad.pdb"
  "libGlad.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/Glad.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
