#ifndef REGIONS_H_INCLUDED 
#define REGIONS_H_INCLUDED 


static unsigned int region_map[][2] = { 
  {          0,         72 },  // conv2d weights 
  {         72,        216 },  // conv2d_1 weights 
  {        288,      23520 },  // dense weights 
  {      23808,        784 },  // input_image 
  {      24592,       6272 },  // conv2d outputs 
  {      30864,       2352 },  // conv2d_1 outputs 
  {      33216,         10 },  // dense outputs 
  {      33226, 4294967295 }   // out of bounds 
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
