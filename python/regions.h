#ifndef REGIONS_H_INCLUDED 
#define REGIONS_H_INCLUDED 


static unsigned int region_map[][2] = { 
  {          0,         90 },  // conv2d weights 
  {         90,        270 },  // conv2d_1 weights 
  {        360,      23520 },  // dense weights 
  {      23880,        784 },  // input_image 
  {      24664,       7840 },  // conv2d outputs 
  {      32504,       2352 },  // conv2d_1 outputs 
  {      34856,         10 },  // dense outputs 
  {      34866, 4294967295 }   // out of bounds 
}; 
 
 
static char region_names[][40] = { 
  { "conv2d weights" }, 
  { "conv2d_1 weights" }, 
  { "dense weights" }, 
  { "input image " }, 
  { "conv2d outputs " }, 
  { "conv2d_1 outputs " }, 
  { "dense outputs " }, 
  { "out of bounds " } 
}; 

#endif 
