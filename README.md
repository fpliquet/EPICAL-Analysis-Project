# EPICAL-Analysis-Project
Project containing code used in the analysis of test beam data for the Electromagnetic PIxel CALorimeter (EPICAL).
The general folder structure and a short explanation on how to use the code are given below.

## Structure
The general basic structure (with some explanation) of the project is as follows:
- **build** *cmake and make files needed to compile the code and in addition the executables (if `make install` is not used)*
- **include** *header files used in the projects (classes and others)*
- **input** *external input files in the form of text files*
  - **deadpixels_classification**
  - **noisypixels_beam**
  - **noisypixels_classification**
- **install** *executables if compiled with `make install`*
- **output** *output files produced with the analysis code*
  - **pics** *plots in pdf and png format*
  - **rootfiles** *root files as a product of the analysis*
    - **hitmaps**
    - **pixelmasks**
- **src** *source cxx files*
  - **classes** *cxx files (implementations) of classes*
  - **macros** *cxx files of macros to be compiled into executables*


## Usage
Although the analysis macros and classes will probably also run in interpreted-mode the project is set up to use compiled executables via cmake/make.
That is why, to run any analysis, two steps are in general necessary: **compilation** and **running**.

### Compiling code
The `CMakeLists.txt` file handles everything related to the compilation of the code.
Every new header or cxx file that is written has to be added to the CMakeLists so that `make` knows what to do with it.
For example, all macros that should be compiled into executables, all classes that should be built into libraries, the linking of the libraries and also the install paths for using `make install` need to be specified.

If working with a clean build directory the first step is to call `cmake ..` in the build directory.
The MakeFile is then correctly set up to ease the compilation procedure and can be used in the common way, e.g. `make`, `make install`, ...
By default only files that have been changed are recompiled, so if you want to make sure to compile everything clean up first with `make clean`.

In summary:
1. edit `CMakeLists.txt` in the main working directory of the project to incorporate the files to be compiled
1. `cd build` to change to build directory
1. `cmake ..` to set up MakeFile
1. `make` or `make install` or `make *<YOUR_EXECUTABLE>*` to compile the code
1. `make clean` to clean up

### Running analysis
If the compilation went through without error the executable is now in the build directory.
It can be run as usual with `./*<YOUR_EXECUTABLE> <YOUR_ARGS>*`.
The classes are set up in a way that the output of anything that is produced with them is stored in `output/` and there sorted thematically.

The main class in the project is called **`EPICALAnalysisObject`**. 
Its methods handle all analyses like or what is needed for them like the production of integrated hitmaps or pixel masks for the different methods.
In addition, there are supporting classes and header files:
- **EPICALGeometry** *class handling the geometry of the prototype, i.e. number of chips, columns, rows, ...*
- **EPICALConversions.h** *header file including conversions of e.g. lane->chip, chip->layer, ... *
- **EPICALUtility.h** *header file including some useful but not class specific helper functions*
To use the main analysis class in a macro just create an instance with the run number you're interested in as argument.
The methods of the class can then be used to do the analyses (check the header file or other macros for available methods).

Example (not tested):
```C++
EPICALAnalysisObject ao(1413); // create analysis object for run 1413
ao.LoadPixelMasks(kAll); // load combined (containing pixels masked for all different methods) pixel masks if already available
vector<TH2C*> vh2_PixelMasks = ao.GetPixelMasks(); // get vector of pixel masks (one entry in vector per chip) for analysis
bool isMasked = false;
if (vh2_PixelMasks.at(20)->GetBinContent(123, 456) > 0) isMasked = true; // check if the pixel in column 123 and row 456 in chip 20 is masked
```

Some macros are already available, mostly for producing root files and plotting, and located in `src/macros/`.
The macros loosely follow a naming scheme:
- `produce_<SOMETHING>.cxx` *output root files are produced and stored in `output/rootfiles/`*
- `draw_<SOMETHING>.cxx` *plots are drawn in some shape or form and stored in `output/pics/`*
