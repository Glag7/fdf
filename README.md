# From the subject

__Summary:__ 
This project is about representing a landscape as a 3D object in which all surfaces are outlined in lines.  
Version: 3  

Your program has to represent the model in isometric projection.
The coordinates of the landscape are stored in a .fdf file passed as a parameter to
your program. Here is an example:
```$>cat 42.fdf
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 10 10 0 0 10 10 0 0 0 10 10 10 10 10 0 0 0
0 0 10 10 0 0 10 10 0 0 0 0 0 0 0 10 10 0 0
0 0 10 10 0 0 10 10 0 0 0 0 0 0 0 10 10 0 0
0 0 10 10 10 10 10 10 0 0 0 0 10 10 10 10 0 0 0
0 0 0 10 10 10 10 10 0 0 0 10 10 0 0 0 0 0 0
0 0 0 0 0 0 10 10 0 0 0 10 10 0 0 0 0 0 0
0 0 0 0 0 0 10 10 0 0 0 10 10 10 10 10 10 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
$>
```
Each number represents a point in space:
• The horizontal position corresponds to its axis.
• The vertical position corresponds to its ordinate.
• The value corresponds to its altitude.  
  
__Bonuses:__  
• Include one extra projection (such as parallel or conic)!
• Zoom in and out.
• Translate your model.
• Rotate your model.
• Add one more bonus of your choice. (in my case : fps counter, z scale, view saver, reset button, colors, an animation...)  

# usage
Don't forget to `git submodule init` and `git submodule update` to get the [MacroLibX](https://github.com/seekrs/MacroLibX) See their repo for how to install dependencies.
`make` to create a binary which displays a still image, or `make bonus` for the version with bonuses.  
`./fdf [path_to_map].fdf`. You can use `-a` to use any file as input and `-f` to silence the warnings and parse the map as if it was perfect.  
The controls are displayed when launching a map.
