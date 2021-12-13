cmake_minimum_required(VERSION 3.13.4)

add_library(SOIL2 STATIC
  image_helper.c
  stb_image
  stb_image_write
  stbi_DDS
  stbi_DDS_c
  stbi_ext
  stbi_ext_c
  stbi_pkm
  stbi_pkm_c
  stbi_pvr
  stbi_pvr_c
  image_DXT.c
  pvr_helper
  jo_jpeg
  SOIL2.c
  wfETC
)