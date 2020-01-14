*** This project is built under Visual Studio 2017 with OpenCV 4 under Windows 10 64-bit


This software is architectured as follows

iptool/iptool.cpp- This file includes the main function.

iptool/iptools -This folder hosts the files that are compiled into a static library. 
	image - This folder hosts the files that define an image.
	utility- this folder hosts the files that students store their implemented algorithms.



*** INSTALATION ***

On Windows

Open the project by double click iptool.sln.
The environment is setting follow the link:
http://opencv-srf.blogspot.com/2013/05/installing-configuring-opencv-with-vs.html


*** Run the program:

Directly debug in Visual Studio.
You can find the output image in output folder.


*** FUNCTIONS ***

1. Add intensity: add
Increase the intensity for a gray-level image.
parameter: intensity

2. Binarization: binarize
Binarize the pixels with the threshold.
parameter: threshold

3. Scaling: Scale
Reduce or expand the heigh and width with twp scale factors.
Scaling factor = 2: double height and width of the input image.
Scaling factor = 0.5: half height and width of the input image.
parameter: scaling_factor



*** FUNCTIONS (with OpenCV) ***

1. Gray Scale: gray
Change whole image to gray-level.
parameter: no

2. Average Blur: blur_avg
Uniform smoothing.
parameter: window_size

3. Histogram Equalization: equalization
parameter: number of roi, roi(s) x1, dx1, y1, dy1

4. Histogram Stretching: stretching
parameter: number of roi, roi(s) x1, dx1, y1, dy1

5. Sobel edge detector: sobel
parameter: number of roi, roi(s) x1, dx1, y1, dy1

6. Canny Edge Detector: canny
parameter: number of roi, roi(s) x1, dx1, y1, dy1

7. Histogram Equalization + Canny Edge Detector: histcanny
parameter: number of roi, roi(s) x1, dx1, y1, dy1

8. Histogram Equalization + Sobel Edge Detector: histsobel
parameter: number of roi, roi(s) x1, dx1, y1, dy1

9. QR reader: qr
parameter: none




*** PARAMETERS ***

The first parameter of the parameters.txt is the number of operations (lines).
There are four parameters for each operation (line):
1. the input file name;
2. the output file name; NOTE: for QR reader just write "null" for the output file name.
3. opencv / FUNCTIONS (without OpenCV): skip to 5 for parameters
4. the name of the function with OpenCV. Check FUNCTIONS (with OpenCV).
5. parameters (Check FUNCTIONS (with OpenCV) for parameters)



*** Important information ***

Application assumes the next format of input image (ppm/pgm) file:
line1: <version>
line2: <#columns> <#rows>
line3: <max_value>
line4-end-of-file:<pix1><pix2>...<pix_n>

if it is a grayscale image then every pixel is a char value. If it is a RGB image then every pixel is a set of 3 char values: <red><green><blue>

Thus, if you have a problem with reading image, the first thing you should check is input file format.
