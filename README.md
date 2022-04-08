# CG Tutorial files 

## Setting up the tutorials

- clone the repository or download snapshot
- Extract ```contrib.zip```  The folder should now contain two subfolders cmake and contrib, in addition to the tutorial files (```uXX```)

## Building the tutorials
The tutorials use the cmake build system. By using cmake you are able to create make and project files for various IDEs and platforms.
Please keep in mind that you'll need to have SFML (http://www.sfml-dev.org/) and GLEW (http://glew.sourceforge.net/) installed. 
To get you started here is a short tutorial  for Linux and Windows:


### Linux
- Install SFML (minimum 2.0) and GLEW
- cd to the tutorial's directory
- create a build folder
- cd to that folder
- execute ```cmake ..```
  it will generate a makefile. In case it gives you errors try to fix missing dependecies
- execute ```make```
- wait for the program to compile
- execute the executable


### Windows

- extract ```contrib.zip``` to the 
- install cmake https://cmake.org/ (3.23.3 at the time of writing)
- install Visual Studio 2017, 2019 or 2022
- 2 options
  - 1) manual
    - open a command line
    - cd to the directory of the tutorial
    - create a new folder called build
    - cd to that build folder
    - execute cmake with -G to show a list of generators
    - select the generator of the IDE of you choice and use the path to the upper directory as second parameter
	     e.g. ```cmake -G "Visual Studio 15 2017 Win64"``` 
	      creates a Project file for "Visual Studio 2017" and sets the architecture to 64 bit
  - 2) gui
    - open the cmake GUI
    - set source folder to the tutorial folder (e.g. ```c:/tutorials/u03```)
    - set binary folder to a new folder (e.g. (e.g. ```c:/tutorials/u03/build```)
    - click "Configure" and choose Generator of installed Visual Studio
    - once done, click "Generate"
	
- Open the newly generated projecte file (e.g. .sln for Visual Studio in you IDE)
- Try to compile it
- In order to launch the application from within Visual Studio you need to set the Startup-Project:
	- In the solutions explorer (Window on the left/right containing ALL_BUILD, U0\<NUMBER\> and ZERO_CHECK) right click on U0\<NUMBER\> and select ```Set as StartUp Project```
- When you try to execute you code it might complain about missing dlls. The dlls are provided in the contrib directory
  Copy the DLLs of the architecture of your choice to compilers output directory (where the exe lives)
  e.g. ```../build/Debug```
- Try launching the programm again
- If this should fail. Copy the dlls to your c:\windows\system32 folder

### OSX (experimental)

- install homebrew
- install sfml and glew
- follow Linux instructions concerning ```cmake``` with or without XCode

## Additional resources

- Visual Studio 2013 Redistributables (x86 and x64), in case you get some error like this:
  - https://stackoverflow.com/questions/31930652/visual-studio-missing-msvcr120d-dll-and-msvcp120d-dll-error
  - https://www.microsoft.com/en-us/download/details.aspx?id=40784