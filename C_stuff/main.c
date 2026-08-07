// welcome welcome, reading my shitty code are we xD, anyways keep going down. I will try my best to explain stuff :)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION // ok so like line 2-15 just import the stuff needed such as Stb libraries for processing and resizing images and ofc stdio.h the goat cant even print without it lol
#include "stb_image_resize2.h"


#define  Pr  .299
#define  Pg  .587
#define  Pb  .114

int size;

EMSCRIPTEN_KEEPALIVE
void get_size(int a) {
    size = a;
  }

void changeSaturation(double *R, double *G, double *B, double change) {       //stole this code from here: https://alienryderflex.com/saturation.html

  double  P=sqrt(
  (*R)*(*R)*Pr+
  (*G)*(*G)*Pg+
  (*B)*(*B)*Pb ) ;

  *R=P+((*R)-P)*change;
  *G=P+((*G)-P)*change;
  *B=P+((*B)-P)*change; }

int width_shrunk;
int height_shrunk;
int main(void)
{
  int width, height, original_channels; // ah yes, initialising some *kewl* variables :)
  int img_index;
  int index;
  int x = 0;
  int y = 0;
  int i = 0;
  double r = 0;
  double b = 0;
  double g = 0;
  char ASCIIMAP[31] = "N@#W$9876543210?!abc;:+=-_,.  "; // i stole this online
  int num_char = strlen(ASCIIMAP);
  unsigned char *img = stbi_load(
      "googoo.png", // i am not a baby, its from this video: https://youtube.com/shorts/1MCfhbbxogQ?si=rioc5poo844f9C3y | walt disney, nike, *GOOGOO*
      &width, &height, &original_channels, 3);
  width_shrunk = width;   // this is because uhhhh idk
  height_shrunk = height; // no actually this is so that we can shrink them with the algorithm (or whatever the fuck you call it) below
  if (size <= 0) {
    size = 40;
  }
  while (width_shrunk > size && height_shrunk > size)
  {
    width_shrunk = width_shrunk * 0.95;
    height_shrunk = height_shrunk * 0.95; // this is smart right ( ˊᵕˋ )
  }
  width_shrunk = width_shrunk * 2;                                      // this is because terminal likes to shrink the width to roughly half of height (shoutout bolt from cs50 discord)
  unsigned char *img_resize = malloc(width_shrunk * height_shrunk * 3); // this is to reserve data in heap so that my program does not kill itself lol
  float brightness;
  if (img == NULL)
  {
    printf("failure\n");
    free(img_resize); // ahh yes i dont wanna take up your ram
    free(img);
    return 1;
  }
  else
  {
    stbir_resize_uint8_srgb(img, width, height, 0, img_resize, width_shrunk, height_shrunk, 0, STBIR_RGB); // stb the goat
  }
  printf("\n");
  while (y != height_shrunk)
  {
    while (x != width_shrunk)
    {
      img_index = (((y * width_shrunk) + x) * 3);
      r = img_resize[img_index + 0];
      g = img_resize[img_index + 1];
      b = img_resize[img_index + 2];
      changeSaturation(&r, &g, &b, 1.5);
      brightness = ((r * 0.2126) + (g * 0.7152) + (b * 0.0722)); // basically the entire ascii thing, so like till one y is done it keeps doing the x axis so like imagine (0,0) so it will keep increasing x by one until width is reached then it increases y by one and resets x. also it prints every pixel with a character based of brightness using luma formula
      index = (int)((brightness * (num_char - 1)) / 255);
      printf("%c", ASCIIMAP[index]);
      x++;
      i++;
    }
    printf("\n");
    x = 0;
    y++;
  }
  free(img_resize);
  free(img); // no ram hogging in here :D
}

EMSCRIPTEN_KEEPALIVE
int image_width()
{
  return width_shrunk; // this is to give the data to emscripten so that it can resize the div
}

EMSCRIPTEN_KEEPALIVE
int image_height()
{
  return height_shrunk; // same as above
}

// i hope you did not find my comments annoying, jassi out :)
