/* 

Geometric Tranformations.
Code by: Ishan Taldekar (ishantaldekar1@gmail.com)

References: 
https://docs.opencv.org/2.4.13.4/doc/tutorials/imgproc/imgtrans/warp_affine/warp_affine.html
https://docs.opencv.org/2.4/modules/imgproc/doc/geometric_transformations.html?highlight=warpaffine#warpaffine
https://docs.opencv.org/3.3.0/d3/db2/structCvMat.html
https://www.ics.uci.edu/~majumder/VC/new-lectures/geom.pdf

*/

#include <stdio.h>
#include <stdlib.h>

#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc/types_c.h>

/*

Function Description: 
An image is passed in by reference to the function, the function rotates it in a process described by the lecture slides
in the references above. We get the transformation matrix using the cv2DRotationMatrix() function, and then transform the 
image using the cvWarpAffine() function.

*/

void ImageRotate(IplImage** user_image, double angle)
{

	//Initializing the source and destination images.
	IplImage* source = 0;
	IplImage* destination = 0;

	//Declaring a point (the center)
	CvPoint2D32f center;
	
	//Initializing the scale (1 = no scaling)
	double scale = 1;

	//Declaring the transformation matrix
	CvMat* matrix_map;

	source = cvCloneImage(*user_image);
	destination = cvCloneImage(*user_image);

	//Creating a 2x3 matrix
	matrix_map = cvCreateMat(2, 3, CV_32FC1);

	//Storing the co-ordinates to the center of the image.
	center = cvPoint2D32f(source->width/2, source->height/2);

	//Acquiring the transformation matrix
	cv2DRotationMatrix(center, angle, scale, matrix_map);

	//Performing the transformation on the image.
	cvWarpAffine(source, destination, matrix_map, CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS, cvScalarAll((0)));

	*user_image = cvCloneImage(destination);

}

/*

Function Description:
In a process similar to the one above, a scaling factor is passed in along with a pointer to the image.
The factor can be looked at as how much the width, and the height of the image will altered by.

*/

void ImageScale(IplImage** user_image, double scale)
{
	//Initializing the source and destination images.
	IplImage* source = 0;
	IplImage* destination = 0;

	//Declaring a point (the center)
	CvPoint2D32f center;
	
	//Initializing the angle (0 = no rotation)
	double angle = 0;

	//Declaring the transformation matrix
	CvMat* matrix_map;

	source = cvCloneImage(*user_image);
	destination = cvCloneImage(*user_image);

	//Creating a 2x3 matrix
	matrix_map = cvCreateMat(2, 3, CV_32FC1);

	//Storing the co-ordinates to the center of the image.
	center = cvPoint2D32f(source->width/2, source->height/2);

	//Acquiring the transformation matrix
	cv2DRotationMatrix(center, angle, scale, matrix_map);

	//Performing the transformation on the image.
	cvWarpAffine(source, destination, matrix_map, CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS, cvScalarAll((0)));

	*user_image = cvCloneImage(destination);

}

/*
Function Description:
Please read the section on image translation to get a better understanding of the transformation.
We create the transformation matrix and add elements to it using the CV_MAT_ELEM macro.
Our objective is to create a transformation matrix similar to the one in the reference lecture slides. 
We then transform the image using the cvWarpAffine() function.

*/

void ImageTranslate(IplImage** user_image, float translation_factor)
{

	//Initializing the source and destination images.
	IplImage* source = 0;
	IplImage* destination = 0;

	//Declaring the transformation Matrix.
	CvMat* matrix_map;

	source = cvCloneImage(*user_image);
	destination = cvCloneImage(*user_image);

	//Creating a 3x2 matrix
	matrix_map = cvCreateMat(2, 3, CV_32FC1);

	//Setting the element values of the transformation matrix in order to perform a translation (refer to reference slides)
	CV_MAT_ELEM( *matrix_map, float, 0, 0 ) = 1;
	CV_MAT_ELEM( *matrix_map, float, 0, 1 ) = 0;
	CV_MAT_ELEM( *matrix_map, float, 0, 2 ) = translation_factor;
	CV_MAT_ELEM( *matrix_map, float, 1, 0 ) = 0;
	CV_MAT_ELEM( *matrix_map, float, 1, 1 ) = 1;
	CV_MAT_ELEM( *matrix_map, float, 1, 2 ) = translation_factor;

	//Performing the transformation on the image.
	cvWarpAffine(source, destination, matrix_map, CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS, cvScalarAll((0)));

	*user_image = cvCloneImage(destination);

}