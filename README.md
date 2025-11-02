<div align="center">

# ✈️ AutoTCAS - Traffic Collision Avoidance System Simulator

![Release Version](https://img.shields.io/badge/Release_Version-1.2.0-blue.svg)
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
On higher resolution displays (for example 4k) aircrafts and too close messages will appear small. They are not being scaled with increasing resolution and are by default modeled on 1440p. If the aircrafts were to be scaled all distances would become smaller/larger depending on user resolution and would mess up the visual aspect during avoidance detection. In version 1.4.0 a solution will be implemented in which users will be able to zoom in/out fixing the issue without having to implement a solution to scale distances and speeds.




**For Those Building From Source Files**
----------------------------------------
1. Clone the repository or download files from: https://github.com/jadonmat/AutoTCAS.git (You can directly clone in visual studio).

      If you wish to contribute follow these steps in [Contributing](https://github.com/jadonmat/AutoTCAS?tab=readme-ov-file#-contributing).


3. Open the .sln file in Visual Studio 2022.
4. Set the build configuration to Release and platform to x64.
5. Build the solution (Build > Build Solution).

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
  
## 🚀Feature Roadmap (Subject to change)
- ~~**v1.1.0** - Add seperate warning and collision detections. Redsign advoidance to focus on closet aircraft. More realistic flight physics.~~
- ~~**v1.2.0** - Basic settings menu, intro screen, spawn too close notification, auto scale UI, reset notification.~~
- **v1.3.0** - TCAS audio, right click to delete aircraft, hover to view aircraft info.
- **v1.4.0** - Zoom and pan ability with larger map (circular boundary). Max # of aircraft.
- **v1.5.0** - Complete simulation physics overhaul (ideal cruise scenario with no disturbances) with aircraft flight perfomance based off of its aerodynamic and propulsive properties. New physics will be scaled to the map realistically with distances in nm.
#### Rough outline
- **v1.6.0** -  Introduction of equations of motion to better model 2d rotational dynamics. Advanced predictive avoidance handling.
- **v1.7.0** -
- **v1.8.0** - Addition of wind (system disturbance) with control system implementation for lateral static stabilization. Introduces rudder component to system.
- **v1.9.0** - Manual speed changes, initial heading selction, aircraft collisions, aircraft stall (low speeds).
- **v2.0.0** - Animated ailerons and rudders, aircraft collisions, engine animations, new types of aircraft, aircraft names on hover, program thumbnail, overhauled intro screen, overhauled UI system. Likely to implement a UI library.

## 🤝 Contributing

Contributions are welcome! Please feel free to submit issues and/or feature requests.

If you want to directly contribute:
1. Fork the repository.
2. Clone your fork.
3. Create a new branch seperate from master branch.
4. Make and commit changes.
5. Push changes to Github.
6. Create a pull request, please write a description explaining your changes between your branch and the master branch.


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

