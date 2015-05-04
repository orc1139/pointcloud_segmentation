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

int main( int argc, char** argv ) {
  if( argc != 2 ) {
      std::cerr << argv[0] << " requires one argument!\n";
      return -1;
    }

  Mat img_rgb;
  // Load original color picture.
  img_rgb = imread( argv[1], 1 );
  std::string filenameAsString = argv[1];

  if( !img_rgb.data ) {
	  std::cerr << "Image file is empty!\n";
      return -1;
    }

  // Instance of the class, which implements the functions of the homework.
  imageProcessor imgProcessor;

  /*
  //----------- GRAYSCALE -----------
  Mat img_gray;
  cvtColor(img_rgb,img_gray,CV_RGB2GRAY);	// Original to grayscale.

  // Save grayscale image.
  imwrite(imgProcessor.addStringToFilename(filenameAsString, "gray"), img_gray);

  namedWindow("Original Image", CV_WINDOW_NORMAL);
  imshow("Original Image", img_rgb);
  waitKey(0);

  namedWindow( "Grayscale Image", CV_WINDOW_NORMAL );
  imshow( "Grayscale Image", img_gray);
  waitKey(0);

  //----------- LAPLACIAN EDGE DETECTOR -----------

  Mat laplacian = imgProcessor.laplaceEdgeDetection(img_gray);

  // Save laplacian image.
  imwrite(imgProcessor.addStringToFilename(filenameAsString, "edges"), laplacian);

  namedWindow( "Laplacian image (edges)", CV_WINDOW_NORMAL );
  imshow("Laplacian image (edges)", laplacian);
  waitKey(0);

  //----------- NEGATIVE -----------
  Mat img_negative;

  bitwise_not(img_rgb, img_negative);

  // Save negative image.
  imwrite(imgProcessor.addStringToFilename(filenameAsString, "neg"), img_negative);

  namedWindow("Negative image", CV_WINDOW_NORMAL );
  imshow("Negative image", img_negative);
  waitKey(0);

  //----------- DOMINATRIX -----------

  Mat dominatingColorMatrix = imgProcessor.getDominatrix(img_rgb);

  // Save image with dominating color:
  imwrite(imgProcessor.addStringToFilename(filenameAsString, "dom.color"), dominatingColorMatrix);

  namedWindow("Dominating color matrix", CV_WINDOW_NORMAL );
  imshow("Dominating color matrix", dominatingColorMatrix);
  waitKey(0);
  */

  //----------- WATERSHED -----------

  Mat watershedSegmentedMatrix = imgProcessor.watershedSegmentation(img_rgb);

  // Save segmented image to file:
  imwrite(imgProcessor.addStringToFilename(filenameAsString, "segmented"), watershedSegmentedMatrix);

  namedWindow("Segmentation using watershed", CV_WINDOW_NORMAL );
  imshow("Segmentation using watershed", watershedSegmentedMatrix);
  waitKey(0);

  destroyAllWindows();
  return 0;
}
