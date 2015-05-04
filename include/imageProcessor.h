#ifndef IMG_PROCESSOR_H_
#define IMG_PROCESSOR_H_

// OpenCV headers:
#include <cv.h>
#include <highgui.h>

// Standard C++ headers:
#include <iostream>
#include <string>
#include <vector>

/*!	\brief Implements the functions asked in Homework 1.
 */
class imageProcessor {


	//////////////// Definitions ////////////////
private:
	// ...
protected:
	//...
public:
	//...


	//////////////// Methods ////////////////
private:
	//...

protected:
	/*!	\brief Splits a filename at each dot.
	 *
	 */
	std::vector<std::string> parseImageFilename (std::string filename);

	/*!	\brief Helps determine the data type of an image, just for debugging.
	 *
	 */
	std::string type2str(int type);


public:
	/*!	\brief Constructor of the class, does not do much.
	 */
	imageProcessor();

	/*!	\brief Destructor of the class, does not do much.
	 */
	~imageProcessor();

	/*!	\brief Performs edge detection on an image using median smoothing and the Laplace operator.
	 *
	 * Takes the original image and applies a blur to make edges easier to find.
	 * Uses the Laplace Operator to detect edges on the blurred/smoothed image.
	 * Finally, calculates the absolute values and converts the result to 8-bit.
	 */
	cv::Mat laplaceEdgeDetection (cv::Mat& source);

	/*!	\brief Finds the dominating color of each pixel in a matrix, sets the rest to zero
	 *
	 * Preferred color is channel 2 (blue).
	 */
	cv::Mat getDominatrix (cv::Mat& source);

	/*!	\brief Uses the watershed algorithm to segment an image.
	 */
	cv::Mat watershedSegmentation (cv::Mat& source);

	/*!	\brief Adds a custom string just before a filename's extension.
	 *
	 * Example: if we have a "picture.jpg" and we modified it so that it now is flipped, we
	 * can use this function to name the new file "picture.flipped.jpg":
	 *
	 * imwrite(addStringToFilename(filenameAsString, "flipped"), myImageMatrix);
	 */
	std::string addStringToFilename(std::string& filename, std::string addition);

	//////////////// Variables ////////////////
private:
	//...
protected:
	//...
public:
	//...

};	// End of imageProcessor class.

#endif /* IMG_PROCESSOR_H_ */
