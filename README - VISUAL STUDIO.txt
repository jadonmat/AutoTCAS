** Getting Started **
---------------------
Project Name: AutoTCAS 
Class: Aerospace 424 - Pennsylvania State University
Team Members: Nicholas Surotchak and Jadon Matriccino

*All code (.h and .cpp files), fonts, and .dll files are in the AutoTCAS folder.
**Note** visual studio must be in release config in order to run the code due to the use of linking text files in main.cpp.

**Project Description**
------------------------
This project simulates an aircrafts traffic collision avoidance system through visual means. Aircraft will appear to fly through the air with a TCAS system handling avoidance with other aircraft objects. The aircrafts will avoid each other and will turn red when a possible collision is detected. To interact with the interface that appears when you run the code, you simply click the interface and place the aircraft and its corresponding shape for visualization. The aircraft will automatically detect each other and they will avoid each other. If they reach the boundaries of the window they appear to "bounce" off the boundary by changing their velocity directions. Redundancies have been implemented in case the window is resized or put into Fullscreen. If an aircraft object does happen to make it outside the boundary, it will be erased. There is also a reset button that will allow all of the planes to be deleted. The window will stay open until the window is closed or the escape button is pressed.

The following inheritance structure was implemented in the code:
	Engine ->  Aileron -> Radar -> TCAS -> Aircraft

This inheritance structure allowed us to simulate parts of an Aircraft and the way they would react to a sensor system in order to allow the planes to warn and avoid each other.


** SMFL3.0 ISSUES **
-----------------
If you have issues running SMFL with visual studio, make sure these following steps are implemented when cloning or downloading files from the repository:

Open the SMFL folder in the AutoTCAS main folder.
Once you have the AutoTCAS project downloaded, open the project in visual studio. 
With the main file open, click the project tab -> properties. 
In properties expand the configuration properties and then expand the C/C++ properties. 
Click on C/C++ language, and make sure the C++ Language Standard is set to "C++ 17". 
Now go to C/C++ -> general -> “Additional include directories”, copy and paste the path to your SMFL/include folder. 
Now expand the linker tab and select general. 
Under “Additional library directories” paste the path to the SMFL/lib folder. 
Under linker -> input and under additional dependencies type “sfml-graphics.lib;sfml-system.lib;sfml-window.lib;sfml-audio.lib”

You may need to reinclude each .dll file in the AutoTCAS folder which contains the .h and main.cpp files. These files can be copied from the SMFL bin folder.

SMFL third party software link: https://www.sfml-dev.org/documentation/3.0.0/