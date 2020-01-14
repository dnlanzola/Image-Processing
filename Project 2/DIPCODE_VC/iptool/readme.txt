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

1. autoThresholding

2. autoSThresholding

3. autoColorThresholding


*** PARAMETERS ***

The first parameter of the parameters.txt is the number of operations (lines).
There are four parameters for each operation (line):
1. the input file name;
2. the output file name;
3. the name of the filter. Use "autoThresholding", "autoSThresholding", and "autoColorThresholding" for your filters;
4. the value for adding intensity, threshold value for binarize filter, or the scaling factor for scale filter.

For function 1
1. the input file name;
2. the output file name;
3. the name of the filter.
4. # of roi
5. threshold
6. x
7. Sx
8. y
9. Sy

For function 2
1. the input file name;
2. the output file name;
3. the name of the filter.
4. # of roi
5. ws
6. threshold
7. x
8. Sx
9. y
10. Sy

For function 3
1. the input file name;
2. the output file name;
3. the name of the filter.
4. # of roi
5. hsi (1 = intensity, 2 = hue, 3 = saturation)
6. threshold
7. x
8. Sx
9. y
10. Sy

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
