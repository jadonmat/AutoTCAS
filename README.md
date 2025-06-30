AutoTCAS Version v1.0.0
-----------------------
Class: Aerospace 424 - Pennsylvania State University

Team Members: Nicholas Surotchak and Jadon Matriccino

Built with Visual Studio 2022.



**Project Description**
-----------------------
AutoTCAS is a program developed in Visual Studio 2022 with the idea of simulating how an aircraft's traffic collision avoidance system will manipulate subparts of an aircraft to avoid colliding with another aircraft. This project started off as a project designed for AERSP 424 (Advanced Computer Programming for Aerospace Engineers) at The Pennsylvania State University and quickly became a passion of mine. This was completed using object-oriented programming with inheritance. The SFML third party library was used to create a window rendering interface where this process can be visualized. The idea was to create an aircraft object with multiple control surfaces such as ailerons and engines. The user simply clicks on the display to create an aircraft. The Aircraft will start in a random direction and if it veers too close to another aircraft the user will be able to view how the TCAS system will take over and manipulate the engines and ailerons. 



**System Requirements**
-----------------------
Operation System: Windows 10 or later (**64-bit only**)
Dependencies: Visual C++ Redistributable for Visual Studio 2022 (for 64-bit)



**General Installation**
------------------------
The latest release (v1.0.0) is available on the Releases page on "https://github.com/jadonmat/AutoTCAS". 

1. Download the "AutoTCAS-v1.0.0.zip" file to get the executable.

2. Install Visual C++ Redistributable for Visual Studio 2022 (64-bit) if not already installed from: "https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170&wt.mc_id=studentamb_203301#latest-microsoft-visual-c-redistributable-version"

3. Extract the .zip file to a folder (e.g., C:\Users\YourName\AutoTCAS). Ensure all DLLs and data files (if any) remain in the same folder as AutoTCAS.exe.

4. Double-click AutoTCAS.exe to run the application. Note: This is a 64-bit application and will not run on 32-bit Windows systems.



**For Those Building From Source Files**
----------------------------------------
1. Clone the repository or download files from: https://github.com/jadonmat/AutoTCAS.git (You can directly clone in visual studio).
2. Open the .sln file in Visual Studio 2022.
3. Set the build configuration to Release and platform to x64.
4. Build the solution (Build > Build Solution).


**If you have issues running SMFL with visual studio, make sure these following steps are implemented when cloning or downloading files from the repository just incase the project is not finding SFML path's automatically:
	
Open the SMFL folder in the AutoTCAS main folder.

Once you have the AutoTCAS project downloaded, open the project in visual studio. 

With the main file open, click the project tab -> properties. 

In properties expand the configuration properties and then expand the C/C++ properties. 

Click on C/C++ language, and make sure the C++ Language Standard is set to "C++ 17". 

Now go to C/C++ -> general -> “Additional include directories”, copy and paste the path to your SMFL/include folder. 

Now expand the linker tab and select general. 

Under “Additional library directories” paste the path to the SMFL/lib folder. 

Under linker -> input -> under additional dependencies type “sfml-graphics.lib;sfml-system.lib;sfml-window.lib;sfml-audio.lib”

Make sure each .dll file ("sfml-audio-3.dll", "sfml-graphics-3.dll", "sfml-window-3.dll", and "sfml-audio-3.dll") from SFML\bin are in the AutoTCAS folder which contains the .h and main.cpp files. These files can be copied from the SMFL bin folder. (This should already be implemented)


5. If you wish to create your own .exe from from the project you will have to copy the SFML DLLs from SFML\bin ("sfml-audio-3.dll", "sfml-graphics-3.dll", "sfml-window-3.dll", and "sfml-audio-3.dll") and the AutoTCAS\Fonts folder to the x64\release folder. You can then run the .exe file directly and/or compress it to a zip file with all those included files.




**AutoTCAS Classes/Objects Descriptions and Contributions for Version 1.0.0**
---------------------------------------------------------------------------------------------

Nick: 
-----
Aircraft (derived from TCAS) - member function “avoidCollision” (lines 74-102 & 109–120): 
This member function takes a vector of aircrafts and a time parameter as inputs.  This function 
loops over a vector of aircraft created in main by executing a for loop using auto. The goal of this 
member function is to establish separation distance using the position function from the radar 
class. It uses the time parameter, which was implemented by Jadon, to smooth out the turning 
mechanisms of the plane. The function calculates the distance of the aircraft using the cmath 
library function hypot and then checks the distance from a range of 0 to the range input from the 
TCAS class which is set to 100. It also makes sure the separation of the planes is accounted for 
by comparing two planes using the velocity vectors. The planes are compared by using the auto 
for loop which contains the other keyword, which is acting as the other plane object in this case. 

TCAS (derived from Radar) – member function detectAircraft (lines 16-21): This member 
function of type bool compares two objects of type TCAS (where the objective is to compare 
planes). This finds the distance manual using the Pythagorean theorem and then check whether 
the distance is less than the range, which is a protected member of TCAS. Member function 
getRange(lines 12-14), this is a function of type float which returns the range. 

Contributions in main: (1) prevent placing planes in the same place (lines 97 – 103), and (2) 
adjusting the color of the plane when they get to close (lines 187-206)

(1) This was executed by creating a bool variable occupied, which is initialized to false. 
These lines use an auto for loop to compare an aircraft object and the position on the 
game window, and then sets occupied to true if there is already an object in that position. 
This bool will later be used to create new occupants of the aircraft vector.

(2) This is executed by using a nested for loop rather than auto, since both of the planes need 
to be able to change color. This nested for loop included an if statement that makes sure 
the same object isn’t being compared, and used the TCAS member function detect 
aircraft to check if the planes are in the range, initialized as 100 in TCAS. If both of these 
conditions are met, the color of both planes are turned to red using the setFillColor 
member function in the convex shape class in SFML. This also creates a bool variable 
that will be able to tell if the planes are about to collide. It then keeps the color as green if 
this variable is false(the plane are not about to collide).


Jadon:
------
Implemented SFML into the project. For any further discussion related to SFML classes, the 
documentation can be found here: "https://www.sfml-dev.org/documentation/3.0.1/annotated.html".
I primarily worked in main.ccp, but I also created the Engine, Aileron, and Radar 
classes, and a few member functions in the Aircraft class.
 
The Engine class defines the aircraft’s velocity (Type sf::Vector2f) and includes corresponding 
setters and getters. 

The Aileron class (derived from Engine) defines the aircraft heading angle (Type sf::Angle) and 
includes setters and getters. The getter takes the inverse tangent of the velocity components and 
returns the heading angle. The setter takes a float angle, converts it into radians, finds the 
magnitude of the velocity (speed), and then updates the aircraft’s velocity vector based on the 
new angle.

The Radar class (derived from Aileron) defines the aircraft position (Type sf::Vector2f) and has 
corresponding setters and getters.

The TCAS class (derived from Radar) was created and described above by Nick.

In the Aircraft class (derived from TCAS) I sculpted the aircrafts shape using SFML’s 
sf::ConvexShape, where 32 points were created in a clockwise order to generate a shape. This 
was put into a member function called createAircraftShape. In this member function, the size 
(scale) of the aircraft, the origin (set as geometric center of shape), and the fill color were all 
defined using SFML’s shape class. I also implemented an update member function, which takes a 
differential time (created in main) multiplies it by velocity and updates the aircrafts position (this 
is how the aircraft moves). The avoidCollision member function (much more complicated 
function) was created by nick and described above. However, in that function I assisted with the 
implementation of smooth turning aircraft by utilizing differential time changes (from main).
 
In main I utilized existing tutorials found on SFML’s tutorial website ("https://www.sfml-dev.org/tutorials/3.0/") 
to create a render window, and all that encompasses. STL’s vector class 
creates a vector of planes and corresponding shapes, and a reset button is created by tying a 
string using a font (pulled from file) to a rectangle shape. Time starts elapsing by defining a 
clock using the sf::Clock class. SFML classes are used to implement all of this. Inside of the 
render window multiple nested loops can be found inside of a while loop defining what occurs 
when the window is open. Utilizing tutorials related to window events, event loops were 
implemented:

The window will close if the esc key is pressed. Aircraft and their corresponding shapes are 
created when the user clicks on the screen (mouse click event) (push_back is used to add a plane 
and shape to the back of the vector). Nick implemented a section which prevents aircraft from 
being created on top of each other. The resize event automatically resizes the viewing area when 
the window is resized by the user and also makes sure that all aircraft are inside of the window 
when resized. It also ensures that the reset button maintains its position in the top right when the 
window is resized. The reset button is implemented in the mouse click event where if the mouse 
is clicked inside the button the vector containing the aircraft and corresponding shapes are 
cleared.

Outside of the event loops (inside the main while loop, dictating when the window is open) the 
clock is restarted signalizing a differential change in time as the code loops. The window is also 
constantly being cleared so only the current state of the aircraft is being shown. In this section 
there’s another for loop that loops through each existing aircraft and determines whether an 
aircraft is at a window boundary and updates the aircraft’s position for the differential time. If it 
is at a window boundary, depending on which one, the aircraft will change its velocity in a way 
that it appears to bounce off the wall. Now just in case the aircraft somehow manages to glitch 
out of the wall, inside the same loop I implemented a series of deletions if an aircraft glitches 
outside of a particular boundary. This is using STL’s erase in the vector class, which in this case 
erases a singular aircraft in the vector. Inside the same loop, if the aircraft are not at the boundary 
and are too close together Nick implemented the changing of the aircraft’s colors to red if they 
are within range. I set the aircrafts shapes to be at the same position as the aircraft, and its 
rotation is set to using the aircraft’s heading angle. Nick implemented another for loop inside of 
this loop using the avoidCollision function as he described above. Outside of this for loop and 
back into the main loop dictating while the window is open, the aircraft shapes and reset button 
are both drawn and displayed on the window during that differential amount of time.
