#include "utility.h"
#include <iostream> 
#include <algorithm> 

#define MAXRGB 255
#define MINRGB 0

std::string utility::intToString(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int utility::checkValue(int value)
{
	if (value > MAXRGB)
		return MAXRGB;
	if (value < MINRGB)
		return MINRGB;
	return value;
}

/*-----------------------------------------------------------------------**/
void utility::addGrey(image &src, image &tgt, int value)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)+value)); 
		}
}

/*-----------------------------------------------------------------------**/
void utility::binarize(image &src, image &tgt, int threshold)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if (src.getPixel(i,j) < threshold)
				tgt.setPixel(i,j,MINRGB);
			else
				tgt.setPixel(i,j,MAXRGB);
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::scale(image &src, image &tgt, float ratio)
{
	int rows = (int)((float)src.getNumberOfRows() * ratio);
	int cols  = (int)((float)src.getNumberOfColumns() * ratio);
	tgt.resize(rows, cols);
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{	
			/* Map the pixel of new image back to original image */
			int i2 = (int)floor((float)i/ratio);
			int j2 = (int)floor((float)j/ratio);
			if (ratio == 2) {
				/* Directly copy the value */
				tgt.setPixel(i,j,checkValue(src.getPixel(i2,j2)));
			}

			if (ratio == 0.5) {
				/* Average the values of four pixels */
				int value = src.getPixel(i2,j2) + src.getPixel(i2,j2+1) + src.getPixel(i2+1,j2) + src.getPixel(i2+1,j2+1);
				tgt.setPixel(i,j,checkValue(value/4));
			}
		}
	}
}
/*-----------------------------------------------------------------------**/
void utility::autoThresholding(image &src, image &tgt, int t1, int x1, int dx1, int y1, int dy1)
{
	int background, foreground;
	int threshold = t1;
	int limit = 50;

	background = 0;
	foreground = 0;
	int count1 = 0;
	int count2 = 0;
	int meanBackground, meanForeground;

	for (int i = 0; i < tgt.getNumberOfRows(); i++)
	{
		for (int j = 0; j < tgt.getNumberOfColumns(); j++)
		{
			if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
			{
				if (checkValue(tgt.getPixel(i, j)) > threshold)
				{
					foreground = foreground + checkValue(tgt.getPixel(i, j));
					count1 = count1 + 1;
				}

				else
				{
					background = background + checkValue(tgt.getPixel(i, j));
					count2 = count2 + 1;
				}

			}
		}
	}

	meanBackground = background / count2;
	meanForeground = foreground / count1;


	threshold = (meanBackground + meanForeground) / 2;



		for (int i = 0; i < tgt.getNumberOfRows(); i++)
		{
			for (int j = 0; j < tgt.getNumberOfColumns(); j++)
			{
				if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
				{
					if (checkValue(tgt.getPixel(i, j)) > threshold)
						tgt.setPixel(i, j, 255);
					else
						tgt.setPixel(i, j, 0);
				}
				else
					tgt.setPixel(i, j, checkValue(tgt.getPixel(i, j)));
			}
		}



}

/*-----------------------------------------------------------------------**/
void utility::cmodification(image &src, image &tgt, int r, int g, int b, int t1, int x1, int dx1, int y1, int dy1)
{
	for (int i = 0; i < src.getNumberOfRows(); i++)
	{
		for (int j = 0; j < src.getNumberOfColumns(); j++)
		{
			if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
			{
				tgt.setPixel(i, j, RED, checkValue(tgt.getPixel(i, j, RED)) + r);
				tgt.setPixel(i, j, GREEN, checkValue(tgt.getPixel(i, j, GREEN)) + g);
				tgt.setPixel(i, j, BLUE, checkValue(tgt.getPixel(i, j, BLUE)) + b);
			}
			else
			{
				tgt.setPixel(i, j, RED, checkValue(tgt.getPixel(i, j, RED)));
				tgt.setPixel(i, j, GREEN, checkValue(tgt.getPixel(i, j, GREEN)));
				tgt.setPixel(i, j, BLUE, checkValue(tgt.getPixel(i, j, BLUE)));
			}
		}
	}

}

void utility::smoothing(image &src, image &tgt, int ws1, int x1, int y1, int dx1, int dy1)
{
	int x1Bound = x1;
	int y1Bound = y1;



		int val = 0;	//variable to hold values of pixels from window

		for (int i = 0; i < src.getNumberOfRows(); i++)
			for (int j = 0; j < src.getNumberOfColumns(); j++)
			{
				if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
				{
					int itX = i - ((ws1 - 1) / 2);
					int itY = j - ((ws1 - 1) / 2);

					if (itX < x1Bound || itX >(x1Bound + dx1) || itY < y1Bound || itY >(y1Bound + dy1))
					{
						tgt.setPixel(i, j, checkValue(src.getPixel(i, j)));
					}
					else
					{
						for (int k = 0; k < ws1; k++)
						{
							val += checkValue(src.getPixel(itX, j));
							itX++;
						}
						tgt.setPixel(i, j, (val / ws1));
						val = 0;

						for (int k = 0; k < ws1; k++)
						{
							val += checkValue(tgt.getPixel(i, itY));
							itY++;
						}
						tgt.setPixel(i, j, (val / ws1));
						val = 0;
					}
				}
				else
					tgt.setPixel(i, j, checkValue(src.getPixel(i, j)));

	}


}


/*-----------------------------------------------------------------------**/
void utility::autoColorThresholding(image &src, image &tgt, int t1, int hsi, int x1, int dx1, int y1, int dy1)
{
	int background, foreground;
	int threshold = t1;
	int limit = 50;

	double intensity, hue, saturation;
	double r, g, b;
	double rn;
	double gn;
	double bn;

	background = 0;
	foreground = 0;
	int count1 = 1;
	int count2 = 1;
	int meanBackground, meanForeground;

	for (int i = 0; i < tgt.getNumberOfRows(); i++)
	{
		for (int j = 0; j < tgt.getNumberOfColumns(); j++)
		{
			if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
			{
				
				if (checkValue(tgt.getPixel(i, j)) > threshold)
				{
					foreground = foreground + checkValue(tgt.getPixel(i, j));
					count1 = count1 + 1;
				}

				else
				{
					background = background + checkValue(tgt.getPixel(i, j));
					count2 = count2 + 1;
				}

			}
		}
	}

	meanBackground = background / count2;
	meanForeground = foreground / count1;


	threshold = (meanBackground + meanForeground) / 2;
	cout << "threshold: " << threshold << endl;
	cout << "hsi: " << hsi << endl;
	cout << "t1: " << t1 << endl;

	if (hsi == 1)
	{
		for (int i = 0; i < tgt.getNumberOfRows(); i++)
		{
			for (int j = 0; j < tgt.getNumberOfColumns(); j++)
			{
				if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
				{
					r = checkValue(tgt.getPixel(i, j, RED));
					g = checkValue(tgt.getPixel(i, j, GREEN));
					b = checkValue(tgt.getPixel(i, j, BLUE));

					intensity = (r + g + b) / 3.0;
					if (intensity > threshold)
					{
						tgt.setPixel(i, j, RED, 255);
						tgt.setPixel(i, j, GREEN, 255);
						tgt.setPixel(i, j, BLUE, 255);
					}
					else
					{
						tgt.setPixel(i, j, RED, 0);
						tgt.setPixel(i, j, GREEN, 0);
						tgt.setPixel(i, j, BLUE, 0);
					}
				}
				else
					tgt.setPixel(i, j, checkValue(tgt.getPixel(i, j)));
			}
		}
	}

	if (hsi == 2)
	{
		for (int i = 0; i < tgt.getNumberOfRows(); i++)
		{
			for (int j = 0; j < tgt.getNumberOfColumns(); j++)
			{
				if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
				{
					r = checkValue(tgt.getPixel(i, j, RED));
					g = checkValue(tgt.getPixel(i, j, GREEN));
					b = checkValue(tgt.getPixel(i, j, BLUE));
					rn = r / (r + g + b);
					gn = g / (r + g + b);
					bn = b / (r + g + b);

					intensity = (r + g + b) / 3.0;
					if (intensity > threshold)
					{
						tgt.setPixel(i, j, RED, 255);
						tgt.setPixel(i, j, GREEN, 255);
						tgt.setPixel(i, j, BLUE, 255);
					}
					else
					{
						tgt.setPixel(i, j, RED, 0);
						tgt.setPixel(i, j, GREEN, 0);
						tgt.setPixel(i, j, BLUE, 0);
					}
				}
				else
					tgt.setPixel(i, j, checkValue(tgt.getPixel(i, j)));
			}
		}
	}

	if (hsi == 3)
	{
		for (int i = 0; i < tgt.getNumberOfRows(); i++)
		{
			for (int j = 0; j < tgt.getNumberOfColumns(); j++)
			{
				if (i >= x1 && i <= (x1 + dx1) && j >= y1 && j <= (y1 + dy1))
				{
					r = checkValue(tgt.getPixel(i, j, RED));
					g = checkValue(tgt.getPixel(i, j, GREEN));
					b = checkValue(tgt.getPixel(i, j, BLUE));

					saturation = 1 - 3 * min(rn, min(gn, bn));
					if (saturation > threshold)
					{
						tgt.setPixel(i, j, RED, 255);
						tgt.setPixel(i, j, GREEN, 255);
						tgt.setPixel(i, j, BLUE, 255);
					}
					else
					{
						tgt.setPixel(i, j, RED, 0);
						tgt.setPixel(i, j, GREEN, 0);
						tgt.setPixel(i, j, BLUE, 0);
					}
				}
				else
					tgt.setPixel(i, j, checkValue(tgt.getPixel(i, j)));
			}
		}
	}






}



void utility::grayEdgeDetection(image &src, image &tgtAmp, image &tgtBin, image &tgtBinT, int t1, int theta1, int x1, int y1, int szX1, int szY1)
{
	tgtAmp.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	tgtBin.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	tgtBinT.resize(src.getNumberOfRows(), src.getNumberOfColumns());

	int valX = 0, valY = 0;

	int auxX, auxY;
	int Hx = -1, Hy = 1;
	int Hx2 = -2, Hy2 = 2;
	int amplitude = 0;
	int theta = 0, thetaRad = 0;
	double PI = 3.14159;


	for (int i = 0; i < src.getNumberOfRows(); i++)
	{
		for (int j = 0; j < src.getNumberOfColumns(); j++)
		{
			if (i >= x1 && i <= (x1 + szX1) && j >= y1 && j <= (y1 + szY1))
			{
				auxX = i - 1;
				auxY = j - 1;

				if (auxX < x1 || auxX >(x1 + szX1) || auxY < y1 || auxY >(y1 + szY1))
				{
					tgtAmp.setPixel(i, j, checkValue(src.getPixel(i, j)));
					tgtBin.setPixel(i, j, checkValue(src.getPixel(i, j)));
				}
				else
				{

					auxX = i - 1;
					auxY = j - 1;

					for (int k = 0; k < 3; k++)
					{
						for (int l = 0; l < 3; l++)
						{
							if (k != 1)
							{
								valX += checkValue(src.getPixel(auxX, auxY)) * Hx;
								auxY++;
								Hx++;
							}
							else
							{
								valX += checkValue(src.getPixel(auxX, auxY)) * Hx2;
								auxY++;
								Hx2 = Hx2 + 2;
							}

						}

						auxX++;
						auxY = j - 1;
						Hx = -1;
						Hx2 = -2;
					}

					auxX = i - 1;
					auxY = j - 1;

					for (int k = 0; k < 3; k++)
					{
						for (int l = 0; l < 3; l++)
						{
							if (k != 1)
							{
								valY += checkValue(src.getPixel(auxX, auxY)) * Hy;
								auxX++;
								Hy--;
							}
							else
							{
								valY += checkValue(src.getPixel(auxX, auxY)) * Hy2;
								auxX++;
								Hy2 = Hy2 - 2;

							}
						}

						auxY++;
						auxX = i - 1;
						Hy = 1;
						Hy2 = 2;
					}

					if (valX != 0)
						theta = atan(valY / valX) * (180 / PI);
					else
						theta = 0;


					amplitude = sqrt(pow(valY, 2) + pow(valX, 2));
					tgtAmp.setPixel(i, j, amplitude);

					if (amplitude >= t1)
					{
						tgtBin.setPixel(i, j, 255);
						if ((theta - 10 <= theta1) && (theta + 10 >= theta1))
						{
							tgtBinT.setPixel(i, j, 255);
						}
						else
						{
							tgtBinT.setPixel(i, j, 0);
						}
					}
					else
					{
						tgtBin.setPixel(i, j, 0);
						tgtBinT.setPixel(i, j, 0);
					}

					valX = valY = amplitude = 0;

				}
			}
			else
			{
				tgtAmp.setPixel(i, j, checkValue(src.getPixel(i, j)));
				tgtBin.setPixel(i, j, checkValue(src.getPixel(i, j)));
				tgtBinT.setPixel(i, j, checkValue(src.getPixel(i, j)));
			}

		}
	}
}



void utility::colorEdgeDetection(image &src, image &tgtAmp, image &tgtBin, image &tgtBinT, int t1, int theta1, int x1, int y1, int szX1, int szY1)
{
	tgtAmp.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	tgtBin.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	tgtBinT.resize(src.getNumberOfRows(), src.getNumberOfColumns());

	int valXR = 0, valXG = 0, valXB = 0, valYR = 0, valYG = 0, valYB = 0;

	int auxX, auxY;
	int Hx = -1, Hy = 1;
	int Hx2 = -2, Hy2 = 2;
	int amplitude = 0;
	int thetaR = 0, thetaG = 0, thetaB = 0;
	double PI = 3.14159;



	for (int i = 0; i < src.getNumberOfRows(); i++)
		for (int j = 0; j < src.getNumberOfColumns(); j++)
		{
			if (i >= x1 && i <= (x1 + szX1) && j >= y1 && j <= (y1 + szY1))
			{
				auxX = i - 1;
				auxY = j - 1;
				if (auxX < x1 || auxX >(x1 + szX1) || auxY < y1 || auxY >(y1 + szY1))
				{
					tgtAmp.setPixel(i, j, RED, checkValue(src.getPixel(i, j, RED)));
					tgtAmp.setPixel(i, j, GREEN, checkValue(src.getPixel(i, j, GREEN)));
					tgtAmp.setPixel(i, j, BLUE, checkValue(src.getPixel(i, j, BLUE)));

					tgtBin.setPixel(i, j, RED, checkValue(src.getPixel(i, j, RED)));
					tgtBin.setPixel(i, j, GREEN, checkValue(src.getPixel(i, j, GREEN)));
					tgtBin.setPixel(i, j, BLUE, checkValue(src.getPixel(i, j, BLUE)));
				}
				else
				{
					//DeltaX
					auxX = i - 1;
					auxY = j - 1;
					for (int k = 0; k < 3; k++)
					{
						for (int l = 0; l < 3; l++)
						{
							if (k != 1)
							{
								valXR += checkValue(src.getPixel(auxX, auxY, RED)) * Hx;
								valXG += checkValue(src.getPixel(auxX, auxY, GREEN)) * Hx;
								valXB += checkValue(src.getPixel(auxX, auxY, BLUE)) * Hx;
								auxY++;
								Hx++;
							}
							else
							{
								valXR += checkValue(src.getPixel(auxX, auxY, RED)) * Hx2;
								valXG += checkValue(src.getPixel(auxX, auxY, GREEN)) * Hx2;
								valXB += checkValue(src.getPixel(auxX, auxY, BLUE)) * Hx2;
								auxY++;
								Hx2 = Hx2 + 2;
							}

							auxY++;
							Hx++;
						}
						auxX++;
						auxY = j - 1;
						Hx = -1;
						Hx2 = -2;
					}

					//DeltaY
					auxX = i - 1;
					auxY = j - 1;
					for (int k = 0; k < 3; k++)
					{
						for (int l = 0; l < 3; l++)
						{

							if (k != 1)
							{
								valYR += checkValue(src.getPixel(auxX, auxY, RED)) * Hy;
								valYG += checkValue(src.getPixel(auxX, auxY, GREEN)) * Hy;
								valYB += checkValue(src.getPixel(auxX, auxY, BLUE)) * Hy;
								auxX++;
								Hy--;
							}
							else
							{
								valYR += checkValue(src.getPixel(auxX, auxY, RED)) * Hy2;
								valYG += checkValue(src.getPixel(auxX, auxY, GREEN)) * Hy2;
								valYB += checkValue(src.getPixel(auxX, auxY, BLUE)) * Hy2;
								auxX++;
								Hy2 = Hy2 - 2;

							}

							auxX++;
							Hy--;
						}
						auxY++;
						auxX = i - 1;
						Hy = 1;
						Hy2 = 2;
					}

					if (valXR != 0)
					{
						thetaR = atan(valYR / valXR) * (180 / PI);
					}
					else
					{
						thetaR = 0;
					}

					if (valXG != 0)
					{
						thetaG = atan(valYG / valXG) * (180 / PI);
					}
					else
					{
						thetaG = 0;
					}

					if (valXB != 0)
					{
						thetaB = atan(valYB / valXB) * (180 / PI);
					}
					else
					{
						thetaB = 0;
					}


					amplitude = sqrt(pow(valYR, 2) + pow(valXR, 2));
					tgtAmp.setPixel(i, j, RED, amplitude);					//amplitude display image
					amplitude = sqrt(pow(valYG, 2) + pow(valXG, 2));
					tgtAmp.setPixel(i, j, GREEN, amplitude);
					amplitude = sqrt(pow(valYB, 2) + pow(valXB, 2));
					tgtAmp.setPixel(i, j, BLUE, amplitude);

					if (amplitude >= t1)			//edge image only from thresholding
					{
						tgtBin.setPixel(i, j, RED, 255);
						tgtBin.setPixel(i, j, GREEN, 255);
						tgtBin.setPixel(i, j, BLUE, 255);

						if ((thetaR - 15 <= theta1) && (thetaR + 15 >= theta1))
						{
							tgtBinT.setPixel(i, j, RED, 255);		//edge image from thresholding and direction
						}
						else
						{
							tgtBinT.setPixel(i, j, RED, 0);
						}

						if ((thetaG - 15 <= theta1) && (thetaG + 15 >= theta1))
						{
							tgtBinT.setPixel(i, j, GREEN, 255);
						}
						else
						{
							tgtBinT.setPixel(i, j, GREEN, 0);
						}

						if ((thetaB - 15 <= theta1) && (thetaB + 15 >= theta1))
						{
							tgtBinT.setPixel(i, j, BLUE, 255);
						}
						else
						{
							tgtBinT.setPixel(i, j, BLUE, 0);
						}
					}
					else
					{
						tgtBin.setPixel(i, j, RED, 0);
						tgtBin.setPixel(i, j, GREEN, 0);
						tgtBin.setPixel(i, j, BLUE, 0);
						tgtBinT.setPixel(i, j, RED, 0);
						tgtBinT.setPixel(i, j, GREEN, 0);
						tgtBinT.setPixel(i, j, BLUE, 0);
					}
					valXR = valXG = valXB = valYR = valYG = valYB = amplitude = 0;

				}
			}
			else
			{
				tgtAmp.setPixel(i, j, RED, checkValue(src.getPixel(i, j, RED)));
				tgtAmp.setPixel(i, j, GREEN, checkValue(src.getPixel(i, j, GREEN)));
				tgtAmp.setPixel(i, j, BLUE, checkValue(src.getPixel(i, j, BLUE)));
				tgtBin.setPixel(i, j, RED, checkValue(src.getPixel(i, j, RED)));
				tgtBin.setPixel(i, j, GREEN, checkValue(src.getPixel(i, j, GREEN)));
				tgtBin.setPixel(i, j, BLUE, checkValue(src.getPixel(i, j, BLUE)));
				tgtBinT.setPixel(i, j, RED, checkValue(src.getPixel(i, j, RED)));
				tgtBinT.setPixel(i, j, GREEN, checkValue(src.getPixel(i, j, GREEN)));
				tgtBinT.setPixel(i, j, BLUE, checkValue(src.getPixel(i, j, BLUE)));
			}
		}
}




void utility::hsiEdgeDetection(image &src, image &tgtAmp, image &tgtBin, image &tgtBinT, int t1, int theta1, int x1, int y1, int szX1, int szY1)
{
	tgtAmp.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	tgtBin.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	tgtBinT.resize(src.getNumberOfRows(), src.getNumberOfColumns());

	double H, S, I;
	double min;
	int red, blue, green, theta;
	int regRed, regBlue, regGreen;

	int valXR = 0, valXG = 0, valXB = 0, valYR = 0, valYG = 0, valYB = 0;
	double valX = 0, valY = 0;

	int auxX, auxY;
	int Hx = -1, Hy = 1;
	int Hx2 = -2, Hy2 = 2;
	int amplitude = 0;
	int thetaR = 0, thetaG = 0, thetaB = 0;
	double PI = 3.14159;




	for (int i = 0; i < src.getNumberOfRows(); i++)
		for (int j = 0; j < src.getNumberOfColumns(); j++)
		{
			red = src.getPixel(i, j, RED);
			green = src.getPixel(i, j, GREEN);
			blue = src.getPixel(i, j, BLUE);

			if (red > green && red > blue)
			{
				if (green > blue)
				{
					min = blue;
				}
				else
					min = green;
			}
			else if (green > red && green > blue) {
				if (red > blue) {
					min = blue;
				}
				else
					min = red;
			}
			else if (blue > red && blue > green) {
				if (red > green) {
					min = green;
				}
				else
					min = red;
			}

			I = (red + green + blue) / 3;

			if (I > 0)
				S = 1 - min / I;
			else if (I == 0)
				S = 0;


			double thta = ((((red - green) + (red - blue)) / 2) / sqrt(pow((red - green), 2) + (red - blue)*(green - blue)));
			double hue = (acos((thta * (PI / 180))));

			if (blue <= green)
				H = hue;
			else if (blue > green)
				H = 360 - hue;



			if (i >= x1 && i <= (x1 + szX1) && j >= y1 && j <= (y1 + szY1))
			{
				auxX = i - 1;
				auxY = j - 1;

				if (auxX < x1 || auxX >(x1 + szX1) || auxY < y1 || auxY >(y1 + szY1))
				{
					tgtAmp.setPixel(i, j, checkValue(src.getPixel(i, j)));
					tgtBin.setPixel(i, j, checkValue(src.getPixel(i, j)));
				}
				else
				{
					auxX = i - 1;
					auxY = j - 1;

					regRed = src.getPixel(auxX, auxY, RED);
					regGreen = src.getPixel(auxX, auxY, GREEN);
					regBlue = src.getPixel(auxX, auxY, BLUE);


					for (int k = 0; k < 3; k++)
					{
						for (int l = 0; l < 3; l++)
						{
							if (k != 1)
							{
								valX += (regRed*Hx + regGreen * Hx + regBlue * Hx) / 3;
								auxY++;
								Hx++;
							}
							else
							{
								valX += (regRed*Hx + regGreen * Hx + regBlue * Hx) / 3;
								auxY++;
								Hx2 = Hx2 + 2;
							}

						}

						auxX++;
						auxY = j - 1;
						Hx = -1;
						Hx2 = -2;
					}

					auxX = i - 1;
					auxY = j - 1;

					for (int k = 0; k < 3; k++)
					{
						for (int l = 0; l < 3; l++)
						{
							if (k != 1)
							{
								valY += checkValue(src.getPixel(auxX, auxY)) * Hy;
								auxX++;
								Hy--;
							}
							else
							{
								valY += checkValue(src.getPixel(auxX, auxY)) * Hy2;
								auxX++;
								Hy2 = Hy2 - 2;
							}
						}

						auxY++;
						auxX = i - 1;
						Hy = 1;
						Hy2 = 2;
					}

					if (valX != 0)
						theta = atan(valY / valX) * (180 / PI);
					else
						theta = 0;

					amplitude = sqrt(pow(valY, 2) + pow(valX, 2));
					double auxAmp = sqrt(pow(valY, 2) + pow(valX, 2));


					if (H == 0)
					{
						red = auxAmp + 2 * (I*S);
						green = auxAmp - auxAmp * S;
						blue = auxAmp - auxAmp * S;
					}
					else if (H <= 120 && H > 0)
					{
						red = auxAmp + auxAmp * S * (cos(H * (PI / 180)) / cos((60 - H) * PI / 180));
						green = auxAmp + auxAmp * S * (1 - cos(H * (PI / 180)) / cos((60 - H) * PI / 180));
						blue = auxAmp - auxAmp * S;
					}
					else if (H <= 240 && H > 120)
					{
						green = auxAmp + auxAmp * S * (cos(H * (PI / 180)) / cos((60 - H) * PI / 180));
						blue = auxAmp + auxAmp * S * (1 - cos(H * (PI / 180)) / cos((60 - H) * PI / 180));
						red = auxAmp - auxAmp * S;
					}
					else if (H <= 360 && H > 240)
					{
						blue = auxAmp + auxAmp * S * (cos(H * (PI / 180)) / cos((60 - H) * PI / 180));
						red = auxAmp + auxAmp * S * (1 - cos(H * (PI / 180)) / cos((60 - H) * PI / 180));
						green = auxAmp - auxAmp * S;
					}

					if (valXR != 0)
						thetaR = atan(valYR / valXR) * (180 / PI);
					else
						thetaR = 0;

					if (valXG != 0)
						thetaG = atan(valYG / valXG) * (180 / PI);
					else
						thetaG = 0;

					if (valXB != 0)
						thetaB = atan(valYB / valXB) * (180 / PI);
					else
						thetaB = 0;

					auxAmp = sqrt(pow(valYR, 2) + pow(valXR, 2));
					tgtAmp.setPixel(i, j, RED, int(auxAmp));
					auxAmp = sqrt(pow(valYG, 2) + pow(valXG, 2));
					tgtAmp.setPixel(i, j, GREEN, int(auxAmp));
					auxAmp = sqrt(pow(valYB, 2) + pow(valXB, 2));
					tgtAmp.setPixel(i, j, BLUE, int(auxAmp));

					amplitude = amplitude * 0.0001;
					//cout << "Amp: " << amplitude << endl;


					if (amplitude >= t1)
					{
						tgtBin.setPixel(i, j, RED, 255);
						tgtBin.setPixel(i, j, GREEN, 255);
						tgtBin.setPixel(i, j, BLUE, 255);

						if ((thetaR - 10 <= theta1) && (thetaR + 10 >= theta1))
							tgtBinT.setPixel(i, j, RED, 255);
						else
							tgtBinT.setPixel(i, j, RED, 0);

						if ((thetaG - 10 <= theta1) && (thetaG + 10 >= theta1))
							tgtBinT.setPixel(i, j, GREEN, 255);
						else
							tgtBinT.setPixel(i, j, GREEN, 0);

						if ((thetaB - 10 <= theta1) && (thetaB + 10 >= theta1))
							tgtBinT.setPixel(i, j, BLUE, 255);
						else
							tgtBinT.setPixel(i, j, BLUE, 0);
					}
					else
					{
						tgtBin.setPixel(i, j, RED, 0);
						tgtBin.setPixel(i, j, GREEN, 0);
						tgtBin.setPixel(i, j, BLUE, 0);
						tgtBinT.setPixel(i, j, RED, 0);
						tgtBinT.setPixel(i, j, GREEN, 0);
						tgtBinT.setPixel(i, j, BLUE, 0);
					}

					valXR = valXG = valXB = valYR = valYG = valYB = amplitude = valX = valY = 0;

				}
			}
			else
			{
				tgtAmp.setPixel(i, j, RED, checkValue(src.getPixel(i, j, RED)));
				tgtAmp.setPixel(i, j, GREEN, checkValue(src.getPixel(i, j, GREEN)));
				tgtAmp.setPixel(i, j, BLUE, checkValue(src.getPixel(i, j, BLUE)));
				tgtBin.setPixel(i, j, RED, checkValue(src.getPixel(i, j, RED)));
				tgtBin.setPixel(i, j, GREEN, checkValue(src.getPixel(i, j, GREEN)));
				tgtBin.setPixel(i, j, BLUE, checkValue(src.getPixel(i, j, BLUE)));
				tgtBinT.setPixel(i, j, RED, checkValue(src.getPixel(i, j, RED)));
				tgtBinT.setPixel(i, j, GREEN, checkValue(src.getPixel(i, j, GREEN)));
				tgtBinT.setPixel(i, j, BLUE, checkValue(src.getPixel(i, j, BLUE)));
			}

		}

}



void utility::compassEdgeDetection(image &src, image &tgtAmp, image &tgtBin, image &tgtBinT, int t1, int theta1, int x1, int y1, int szX1, int szY1)
{
	tgtAmp.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	tgtBin.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	tgtBinT.resize(src.getNumberOfRows(), src.getNumberOfColumns());

	int valX = 0, valY = 0, valW = 0, valZ = 0;

	int auxX, auxY;
	int Hx = -1, Hy = 1;
	int Hx2 = -2, Hy2 = 2;

	int amplitude = 0;
	int theta = 0, thetaRad = 0;
	double PI = 3.14159;


	for (int i = 0; i < src.getNumberOfRows(); i++)
	{
		for (int j = 0; j < src.getNumberOfColumns(); j++)
		{
			if (i >= x1 && i <= (x1 + szX1) && j >= y1 && j <= (y1 + szY1))
			{
				auxX = i - 1;
				auxY = j - 1;

				if (auxX < x1 || auxX >(x1 + szX1) || auxY < y1 || auxY >(y1 + szY1))
				{
					tgtAmp.setPixel(i, j, checkValue(src.getPixel(i, j)));
					tgtBin.setPixel(i, j, checkValue(src.getPixel(i, j)));
				}
				else
				{

					auxX = i - 1;
					auxY = j - 1;

					for (int k = 0; k < 3; k++)
					{
						for (int l = 0; l < 3; l++)
						{
							if (k != 1)
							{
								valX += checkValue(src.getPixel(auxX, auxY)) * Hx;
								auxY++;
								Hx++;
							}
							else
							{
								valX += checkValue(src.getPixel(auxX, auxY)) * Hx2;
								auxY++;
								Hx2 = Hx2 + 2;
							}

						}

						auxX++;
						auxY = j - 1;
						Hx = -1;
						Hx2 = -2;
					}

					auxX = i - 1;
					auxY = j - 1;

					for (int k = 0; k < 3; k++)
					{
						for (int l = 0; l < 3; l++)
						{
							if (k != 1)
							{
								valY += checkValue(src.getPixel(auxX, auxY)) * Hy;
								auxX++;
								Hy--;
							}
							else
							{
								valY += checkValue(src.getPixel(auxX, auxY)) * Hy2;
								auxX++;
								Hy2 = Hy2 - 2;

							}
						}

						auxY++;
						auxX = i - 1;
						Hy = 1;
						Hy2 = 2;
					}

					auxX = i - 1;
					auxY = j - 1;

					for (int k = 0; k < 3; k++)
					{
						for (int l = 0; l < 3; l++)
						{
								valW += checkValue(src.getPixel(auxX, auxY)) * Hy2;
								auxX++;
								Hy2--;
						}

						auxY++;
						auxX = i - 1;

						Hy2 = 2;
					}

					for (int k = 0; k < 3; k++)
					{
						for (int l = 0; l < 3; l++)
						{
							valZ += checkValue(src.getPixel(auxX, auxY)) * Hx2;
							auxX++;
							Hx2++;
						}

						auxY++;
						auxX = i - 1;

						Hx2 = -2;
					}



					if (valX != 0)
						theta = atan(valY / valX) * (180 / PI);
					else
						theta = 0;


					if (valX < 0)
						valX = valX * (-1);
					if (valY < 0)
						valY = valY * (-1);
					if (valW < 0)
						valW = valW * (-1);
					if (valZ < 0)
						valZ = valZ * (-1);



					amplitude = valX;

					if (valY > amplitude)
						amplitude = valY;
					if (valW > amplitude)
						amplitude = valY;
					if (valZ > amplitude)
						amplitude = valY;

					tgtAmp.setPixel(i, j, amplitude);

					if (amplitude >= t1)
					{
						tgtBin.setPixel(i, j, 255);
						if ((theta - 10 <= theta1) && (theta + 10 >= theta1))
						{
							tgtBinT.setPixel(i, j, 255);
						}
						else
						{
							tgtBinT.setPixel(i, j, 0);
						}
					}
					else
					{
						tgtBin.setPixel(i, j, 0);
						tgtBinT.setPixel(i, j, 0);
					}

					valX = valY = amplitude = 0;

				}
			}
			else
			{
				tgtAmp.setPixel(i, j, checkValue(src.getPixel(i, j)));
				tgtBin.setPixel(i, j, checkValue(src.getPixel(i, j)));
				tgtBinT.setPixel(i, j, checkValue(src.getPixel(i, j)));
			}

		}
	}
}