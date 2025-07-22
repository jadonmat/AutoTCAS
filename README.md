# AutoTCAS Version V1.1.6

Built with Visual Studio 2022 and Simple and Fast Multimedia Library (SFML).


Project Description
-----------------------
AutoTCAS is a program developed in Visual Studio 2022 with the idea of simulating how an aircraft's traffic collision avoidance system will manipulate subparts of an aircraft to avoid colliding with another aircraft. This project started off as a project designed for AERSP 424 (Advanced Computer Programming for Aerospace Engineers) at The Pennsylvania State University and quickly became a passion of mine. This was completed using object-oriented programming with inheritance and polymorphism. The SFML third party library was used to create a window rendering interface where this process can be visualized. The idea was to create an aircraft object with multiple control surfaces such as ailerons and engines. The user simply clicks on the display to create an aircraft. The Aircraft will start in a random direction and if it veers too close to another aircraft the user will be able to view how the TCAS system will take over and manipulate the engines and ailerons. 



**System Requirements**
-----------------------
Operation System: Windows 10 or later (**64-bit only**)

Dependencies: Visual C++ Redistributable for Visual Studio 2022 (for 64-bit)



**General Installation**
------------------------
The latest release is available on the Releases page on "https://github.com/jadonmat/AutoTCAS". 

1. Download the "AutoTCAS-Version#.zip" file to get the executable.

2. Install Visual C++ Redistributable for Visual Studio 2022 (64-bit) if not already installed from: "https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170&wt.mc_id=studentamb_203301#latest-microsoft-visual-c-redistributable-version"

3. Extract the .zip file to a folder (e.g., C:\Users\YourName\AutoTCAS). Ensure all DLLs and data files (if any) remain in the same folder as AutoTCAS.exe.

4. Double-click AutoTCAS.exe to run the application. Note: This is a 64-bit application and will not run on 32-bit Windows systems.


**Known Issues**
----------------
If the user's desktop resolution is not one of the ones manually defined in the code, they will receive an error message that they are unable to run the program. This is due to a lack of resolution scaling in SFML's render window. For now the user can change their desktop resolution in the windows display settings to one of the ones stated in the error message. A solution for this is planned to be implemented in version 1.4.0 alongside another big update.



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


5. If you wish to create your own .exe from from the project you will have to copy the SFML DLLs from SFML\bin ("sfml-audio-3.dll", "sfml-graphics-3.dll", "sfml-window-3.dll", and "sfml-audio-3.dll") and the AutoTCAS\Fonts folder to your x64\release folder. You can then run the .exe file directly and/or compress it to a zip file with all those included files.


**AutoTCAS Class Inheritance**
--------------------------------

| Level | Class | Purpose | Key Features |
|-------|-------|---------|-------------|
| 1 | `Engine` | Base movement system | Velocity management |
| 2 | `Aileron` | Flight control | Heading & deflection control |
| 3 | `Radar` | Detection system | Position tracking |
| 4 | `TCAS` | Collision avoidance sensor | Aircraft detection & warnings |
| 5 | `Aircraft` | **Abstract base** | Shape creation, collision avoidance |
| 6 | `A380` | Concrete airliner | Specific aircraft implementation |

### Independent Classes

- 🖥️ **UI** - User interface management (fonts, FPS, buttons)
- 🎮 **Events** - Input handling (mouse, keyboard, interactions)  
- 🚧 **Boundary** - Boundary management
- 🪟 **Window** - Display and rendering management

     
