#include<iostream>
#include<cv.h>
#include<highgui.h>
#include"hotSpotDetectionAlgorithm.h"

using namespace cv;

int main()
{
	// Read the Line Detection Image
	Mat lineDetectImage = imread("ENTER FILE NAME HERE");

	// Read the Thermal Image
	Mat thermalImage = imread("ENTER FILE NAME HERE");

	// Read the Hot Spot Image
	Mat hotSpotImage = imread("ENTER FILE NAME HERE");

	// Remove the false positives
	Mat hotSpotsOnLines = lineDetectImage + hotSpotImage;

	// Write the hotSpotsOnLines to a file
	imwrite("Images/Thermal/test.jpg", hotSpotsOnLines);

	// Read an image from directory and create Mat src
	const char* ir_image = "Images/Thermal/test.jpg";
	Mat src = imread(ir_image, CV_LOAD_IMAGE_GRAYSCALE);
	Mat dst = src.clone();

	// Create contour vector for points
	vector<vector<Point> > contours;
	double pixel_thresh = 20.0;

	if(src.empty())
	{
		std::cout << "Image not found. Check directory.\n";
		return 0;
	}

	// Original Image
	namedWindow("Original Image", 2);
	imshow("Original Image", src);

	hotSpotDetectionAlgorithm(dst, contours, pixel_thresh); //blur filter - getContourImg()

	// Hot Spot Image
	namedWindow("Hot Spot Image", 2);
	imshow("Hot Spot Image", dst);

	// Calculate threshold level using mean and standard deviation
	Scalar mean, stddev;
	meanStdDev(thermalImage, mean, stddev);

	cout << "Mean: " << mean;
	cout << "Standard Deviation: " << stddev;

	int thresh; // Figure out how to calculate our threshold value

	// Retrieve the location of hot spot and compare with thermal image
	for(unsigned int i= 0; i < contours.size(); i++)
	{
	    for(unsigned int j= 0; j < contours[i].size(); j++) // run until j < contours[i].size();
	    {
	    	int intensity = thermalImage.at<uchar>(Point(i, j));
	    	if(intensity > thresh)
	    	{
	    		// Print out the location of the hot spot to be examined
	    		cout << "Hot Spot has been detected at (" << i << ", " << j << ")" << endl;
	    	}
	    }
	}

	waitKey(0);

	return 0;
}
