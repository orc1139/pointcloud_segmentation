# pointcloud_segmentation
Computer Vision algorithm for room delimitation and identification (segmentation) from a point cloud (indoor scanning).

-- OpenCV & Watershed tests: Using OpenCV for basic image processing --

Libraries required: 
	- OpenCV (obviously)
CMake will throw warnings if anything is missing.


-- Instructions (Using the terminal) --

1.- On the project directory create a new directory called "build":
~/path/to/project $ mkdir build

2.- Go to that directory and call "cmake ..":
~/path/to/project $ cd build
~/path/to/project/build $ cmake ..

You should see some output, no errors.
Some new files appeared!

3.- Now type "make" to compile:
~/path/to/project/build $ make

Again, you should see some more output, no errors.
Even more files appeared!

4.- Now you can invoke the application. In this case
    the application is simply called "test_opencv".
    In order to use it, you should pass ONE parameter:
    a picture file. 
    In this case, any of the jpg files under the img directory,
    e.g. "Mokka.jpg", like so:
~/path/to/project/build $ ./test_opencv ../img/Mokka.jpg

A series of pictures will pop up, these correspond to each
task in the homework. Press any key to open the next image.


-- Instructions (Using the Eclipse) --

This project was written using Eclipse.
So, in order to use this app, just import it as an existing
project. [Instructions here: 
http://help.eclipse.org/juno/index.jsp?topic=%2Forg.eclipse.platform.doc.user%2Ftasks%2Ftasks-importproject.htm]

There are two build configurations: "cmake" and "make" (hammer button). 
Before using any of these, create a "build" directory where the 
project is.
Use "cmake" first to generate the Makefile, then use "make" to
build the project. TA-DA!

Also, if you click on the "play" button, it should also run the app.
However, I did not have time to test it in other computers.
The running configuration being used passes "../img/Mokka.jpg" as argument.

Enjoy.

