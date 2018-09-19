/*
Access Pixel Intensity Values in a Single-Channel Image.

Code by: Ishan Taldekar (ishantaldekar1@gmail.com)

*/


#include <stdio.h>
#include <stdlib.h>

#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc/types_c.h>


/*

Function Description:
This method allows you to access the pixel intensity values of a single channel (grayscale) image. The pixel intensity value can be further 
modified as per the project requirements. 

*/

void AccessPixelIntensityValues(IplImage** user_image)
{
	//Initializing the image
	IplImage* source = 0;

	//Scalar to hold the pointer to a pixel in the image.
	CvScalar Pixel;

	int i, j;

	//Declaring a variable to hold the intensity values we access.
	double intensity_value;

	source = cvCloneImage(*user_image);

	//Nested for-loop will allow us to access each pixel in a given image based on their axis values.
	for(i = 0; i < source->height; i++)
	{
		for(j = 0; j < source->width; j++)
		{

			//Getting a pointer to a pixel.
			Pixel = cvGet2D(source, i, j);

			//Accessing the intensity value at that pixel location. 
			intensity_value = Pixel.val[0];

		}
	}
}
