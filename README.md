<div align="center">

# ✈️ AutoTCAS - Traffic Collision Avoidance System Simulator

![Release Version](https://img.shields.io/badge/Release_Version-1.1.6-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%2010%2B-lightgrey.svg)
![Architecture](https://img.shields.io/badge/Architecture-x64-green.svg)
![Language](https://img.shields.io/badge/C%2B%2B-17-00599C.svg?logo=c%2B%2B)
![SFML](https://img.shields.io/badge/SFML-3.0.0-8CC445.svg)
![License](https://img.shields.io/badge/License-MIT-brightgreen.svg)

*A real-time aircraft collision avoidance system simulation built with modern C++ and SFML*

## [🚀 Download Latest Release](https://github.com/jadonmat/AutoTCAS/releases)

</div>


Project Description
-----------------------
AutoTCAS is a program developed in Visual Studio 2022 with the idea of simulating how an aircraft's traffic collision avoidance system will manipulate subparts of an aircraft to avoid colliding with another aircraft. This project started off as an idea for AERSP 424 (Advanced Computer Programming for Aerospace Engineers) at The Pennsylvania State University and quickly became a passion of mine. This was completed using object-oriented programming with inheritance and polymorphism. The SFML third party library was used to create a window rendering interface where this process can be visualized. The idea was to create an aircraft object with multiple control surfaces such as ailerons and engines. The user simply clicks on the display to create an aircraft. The Aircraft will start in a random direction and if it veers too close to another aircraft the user will be able to view how the TCAS system will take over and manipulate the engines and ailerons.



**System Requirements**
-----------------------
Operating System: Windows 10 or later (**64-bit only**)

Dependencies: Visual C++ Redistributable for Visual Studio 2022 (for 64-bit)



**Installation**
----------------

1. **Download** the latest release from the [releases page](https://github.com/jadonmat/AutoTCAS/releases)
2. **Install** [Visual C++ Redistributable 2022 (x64)](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist)
3. **Extract** the ZIP file to your desired location
4. **Run** `AutoTCAS.exe` and start simulating!

> ⚠️ **Note**: Keep all DLL files in the same directory as the executable

**Known Issues**
----------------
1. UI text does not currently change size based on window size. This will be fixed in version 1.2.0.
  
2. If the user's desktop resolution is not one of the ones manually defined in the code, they will receive an error message that they are unable to run the program. This is due to a lack of resolution scaling in SFML's render window. For now the user can change their desktop resolution in the windows display settings to one of the ones stated in the error message. A solution for this is planned to be implemented in version 1.4.0 alongside another big update.




**For Those Building From Source Files**
----------------------------------------
1. Clone the repository or download files from: https://github.com/jadonmat/AutoTCAS.git (You can directly clone in visual studio).
2. Open the .sln file in Visual Studio 2022.
3. Set the build configuration to Release and platform to x64.
4. Build the solution (Build > Build Solution).

### 🔧 SFML Configuration

If you encounter linking issues:

<details>
<summary>Click to expand SFML setup instructions</summary>

1. Open the SMFL folder in the AutoTCAS main folder.

2. Once you have the AutoTCAS project downloaded, open the project in visual studio. 

3. With the main file open, click the project tab -> properties. 

4. In properties expand the configuration properties and then expand the C/C++ properties. 

5. Click on C/C++ language, and make sure the C++ Language Standard is set to "C++ 17". 

6. Now go to C/C++ -> general -> “Additional include directories”, copy and paste the path to your SMFL/include folder. 

7. Now expand the linker tab and select general. 

8. Under “Additional library directories” paste the path to the SMFL/lib folder. 

9. Under linker -> input -> under additional dependencies type “sfml-graphics.lib;sfml-system.lib;sfml-window.lib;sfml-audio.lib”

> ⚠️ **Note**: Make sure each .dll file ("sfml-audio-3.dll", "sfml-graphics-3.dll", "sfml-window-3.dll", and "sfml-audio-3.dll") from SFML\bin are in the AutoTCAS folder which contains the .h and main.cpp files. These files can be copied from the SMFL bin folder. (This should already be implemented)


</details>


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

- **UI** - User interface management (fonts, FPS, buttons)
- **Events** - Input handling (mouse, keyboard, interactions)  
- **Boundary** - Boundary management
- **Window** - Display and rendering management
  
## 🚀 Roadmap (Subject to change)

- **v1.2.0** - Basic settings menu, intro screen, spawn too close notification, auto scale UI.
- **v1.3.0** - TCAS audio, right click to delete aircraft, hover to view aircraft info.
- **v1.4.0** - Zoom and pan ability with larger map (circular boundary). Max # of aircraft. Set resolution scaling in settings.
- **v1.5.0** - Animated ailerons, aircraft collisions
- **v1.6.0** - New types of aircraft, aircraft names.
- **v1.7.0** - Overhauled intro screen, overhauled UI system. LIkely to implement a UI library.
- **v1.8.0** - Advanced predictive avoidance handling with speed changes, engine animations.
- **v1.9.0** - Ability to select aircraft starting heading.
- **v2.0.0** - To be determined

## 🤝 Contributing

Contributions are welcome! Please feel free to submit issues, feature requests, or pull requests.


## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.


## 🙏 Acknowledgments

- **Penn State AERSP 424** - Course that inspired this project
- **SFML Community** - For the excellent multimedia library
- **Aviation Industry** - For the real-world TCAS systems that inspired this simulation
---
<div align="center">
  
## [⭐ Star this repo](https://github.com/jadonmat/AutoTCAS)
  
## [🐛 Report Bug](https://github.com/jadonmat/AutoTCAS/issues)

## [💡 Request Feature](https://github.com/jadonmat/AutoTCAS/issues)

