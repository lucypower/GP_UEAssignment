# GP_UEAssignment
 
A PCG map creator which allows the user to generate simple maps for dungeon/cave usage, using Cellular Automata and Marching Sqaure techniques. The user is able to generate and walk around the map created, with a simple "collecy the pickups" style game being included in the playing stage of the tool. I decided to use Cellular Automata as it is a technique that I am already familiar with and I wanted to focus my efforts on learning more advanced techniques. Marching Squares allowed me to smooth out the noise created with Cellular Automata to give the map less of a Minecraft blocky feeling.

This module was focused on creating a games mechanic in both Unity and Unreal to compare the development process of each. I chose PCG as my mechanic of choice for this module as I love the Binding of Isaac games and wanted to push the knowledge that I already had in the area to learn something new and more advanced.

# How to Install

The latest release can be found within the releases tab. This is a .zip folder that just needs extracting. The .exe is within this folder :)

# How to Use

The project will open to the "Map Generator" stage of the project. The user will be able to input the height and width of the grid, along with the iteration count and the density number. Upon pressing "Generate", the project will generate the map following the parameters inputted. The user can generate as many maps as they'd like.

The user will be to press the "Play" button to be transported into the map itself, being able to explore it to the hearts content. To provide incentive to explore the entirety of the map, a random number of pickups are spawned around the map for the user to collect. The map will be the exact same map as the one that was last generated.
