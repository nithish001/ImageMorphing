# ImageMorphing

# Compilation
$ g++ -ggdb ImageMorphing.cpp `pkg-config --cflags --libs opencv`
$./a.out

# About
  This has 2 functions, first one is to transform one image where affine transform matrix is given,
second one is changing from image1 to image2 where tie points are given using delaunay trianglulation technique.
This program generates multiple intermediate images. You can generate GIF by saving all the images in a folder
and write this command in shell
$ sudo apt-get install imagemagick
$ convert -resize 50% -delay 10 -loop 0 image_{0..n}.jpg output.gif //where n is number images.
