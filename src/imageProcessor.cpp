// Own headers:
#include "imageProcessor.h"

// OpenCV headers:
#include <cv.h>
#include <highgui.h>

// Standard C++ headers:
#include <iostream>
#include <string>
#include <vector>

using namespace cv;

// Constructor of the class, does not do much.
imageProcessor::imageProcessor() {}

// Destructor of the class, does not do much.
imageProcessor::~imageProcessor() {}

// Splits a filename at each dot.
std::vector<std::string> imageProcessor::parseImageFilename (std::string filename){
	std::string
		delimiter = ".",	// Defines where filename is split.
		token;				// Temporarily stores each chunk of filename.
	std::vector<std::string>
		tokens;				// Stores all found chunks.
	size_t
		pos = 0;			// Position where a delimiter is found in filename.

	while ((pos = filename.find(delimiter)) != std::string::npos) {
	    token = filename.substr(0, pos);
	    tokens.push_back(token);
	    filename.erase(0, pos + delimiter.length());
	}
    tokens.push_back(filename);
	return tokens;
}

// Helps determine the data type of an image.
std::string imageProcessor::type2str(int type) {
	std::string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	r = "CV_";
	switch ( depth ) {
	case CV_8U:  r += "8U"; break;
	case CV_8S:  r += "8S"; break;
	case CV_16U: r += "16U"; break;
	case CV_16S: r += "16S"; break;
	case CV_32S: r += "32S"; break;
	case CV_32F: r += "32F"; break;
	case CV_64F: r += "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans+'0');

	return r;
}

// Performs edge detection on an image using median smoothing and the Laplace operator.
cv::Mat imageProcessor::laplaceEdgeDetection (cv::Mat& source) {
	int
		ksize = 13; // IMPORTANT! This number (filter size) MUST be positive and odd.
	Mat
		blurred,	// Blurred version of the original image. Makes edge detection easier.
		laplace,	// Stores the laplacian-modified image.
		result;		// Contains a modified version of the laplace matrix (absolute values, 8bit).

	// 1st, we blur the image to make edges easier to find.
	medianBlur(source, blurred, ksize);

	// 2nd, Erstellung eines Kantenbildes vom Graustufenbild (mittels Laplace-Operator)
	Laplacian(blurred, laplace, CV_16S, 5);

	// 3rd, calculate absolute values and convert the result to 8-bit.
	convertScaleAbs(laplace, result);

	return result;
}


// Finds the dominating color of each pixel in a matrix, sets the rest to zero.
Mat imageProcessor::getDominatrix (Mat& source) {
	Mat destination = Mat::zeros(source.size(), source.type());
	uchar totalChans = 1 + (source.type() >> CV_CN_SHIFT);

	if (totalChans < 2) {
		std::cerr << "Matrix should be colored, not grayscale!\n" << std::endl;
		return destination;
	}

	// Scan each pixel of the original matrix, row by row, column by column.
	for (int row=0; row<source.rows; row++) {
		for (int col=0; col<source.cols; col++) {

			uchar domina = 0;	// Pixel value.
			int chanOfDna = 2;	// Arbitrary dominant color for tie breaking: blue.

			// Scan each channel in current pixel for the dominant color.
			for (int chan=0; chan<totalChans; chan++) {
				// TODO: Would be nice to make this a template and thus flexible with
				// different data type depths, but we will have to stick to how the
				// original image was imported: 3-channels @ 8-bits (i.e. use Vec3b).
				uchar pixel = source.at<Vec3b>(row,col)[chan];
				if (pixel > domina) {
					domina = pixel;
					chanOfDna = chan;
				}
			}
			// Store the dominating color in the corresp. pixel of the dest. matrix.
			destination.at<Vec3b>(row,col)[chanOfDna] = domina;
		}
	}
	return destination;
}

// Uses the watershed algorithm to segment an image.
Mat imageProcessor::watershedSegmentation (cv::Mat& source) {
    Mat binary;
    cvtColor(source,binary,CV_RGB2GRAY);	// Original to grayscale.
    cv::threshold(binary, binary, 100, 255, THRESH_BINARY);

    // Eliminate noise and smaller objects.
    Mat fg;
    erode(binary,fg,Mat(),Point(-1,-1),2);

    // Identify image pixels without objects.
    Mat bg;
    dilate(binary,bg,Mat(),Point(-1,-1),3);
    threshold(bg,bg,1,128,THRESH_BINARY_INV);

    // Create markers image.
    Mat markers(binary.size(),CV_8U,Scalar(0));
    markers= fg+bg;

    // Use OpenCV's watershed algorithm.
    markers.convertTo(markers, CV_32S);
    watershed(source,markers);

    markers.convertTo(markers,CV_8U);
    return markers;
}

// Adds a custom string just before a filename's extension.
std::string imageProcessor::addStringToFilename(std::string& filename, std::string addition) {
	  std::string newFilename;
	  std::vector<std::string> splitArgString;
	  splitArgString = parseImageFilename(filename);
	  for (unsigned int i = 0; i < splitArgString.size(); i++) {
		  newFilename = newFilename + splitArgString.at(i);
		  if (i == splitArgString.size()-2)
			  newFilename = newFilename + "." + addition + ".";
		  else if (i != splitArgString.size()-1)
			  newFilename = newFilename + ".";
	  }
	  return newFilename;
}
