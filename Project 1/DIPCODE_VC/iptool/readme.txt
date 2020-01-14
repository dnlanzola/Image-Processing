*** This project is built under Visual Studio 2017


This software is architectured as follows

iptool/iptool.cpp- This file includes the main function.

iptool/iptools -This folder hosts the files that are compiled into a static library. 
	image - This folder hosts the files that define an image.
	utility- this folder hosts the files that students store their implemented algorithms.



*** INSTALATION ***

On Windows

Open the project by double click iptool.sln.

*** FUNCTIONS ***

1. Add intensity: add
Increase the intensity for a gray-level image.

2. Binarization: binarize
Binarize the pixels with the threshold.

3. Scaling: Scale
Reduce or expand the heigh and width with twp scale factors.
Scaling factor = 2: double height and width of the input image.
Scaling factor = 0.5: half height and width of the input image.

4. Channel Binarization

5. Color Modification

*** PARAMETERS ***

The first parameter of the parameters.txt is the number of operations (lines).
There are four parameters for each operation (line):
1. the input file name;
2. the output file name;
3. the name of the filter. Use "add", "binarize", and "scale" for your filters;
4. the value for adding intensity, threshold value for binarize filter, or the scaling factor for scale filter.

For function 4 there are 10 parameters.
1. the input file name;
2. the output file name;
3. the name of the filter.
4. # of roi
5. channel color (1 = RED, 2 = GREEN, 3 = BLUE)
6. threshold
7. x
8. Sx
9. y
10. Sy

For function 5 there are 12 parameters.
1. the input file name;
2. the output file name;
3. the name of the filter.
4. # of roi
5. r
6. g
7. b
8. threshold
9. x
10. Sx
11. y
12. Sy

*** Run the program:

Directly debug in Visual Studio.
You can find the output image in output folder.


*** Important information ***

Known bug: sometimes the parameter file only executes the last filter (it has to be executed one by one).

Application assumes the next format of input image (ppm/pgm) file:
line1: <version>
line2: <#columns> <#rows>
line3: <max_value>
line4-end-of-file:<pix1><pix2>...<pix_n>

if it is a grayscale image then every pixel is a char value. If it is a RGB image then every pixel is a set of 3 char values: <red><green><blue>

Thus, if you have a problem with reading image, the first thing you should check is input file format.
