## /Images
This folder contains all the images used in the project.
The images will be in byte format and will be used in the project to display the images in the GUI.

The [template file](img_Template.h) gives an example of how these need to be layed out in the header file.

After adding the images to the folder the new image header file will need to be included in the
[Image Data file](../ImageData.h) file. eg. ```#include "Displays/Images/img_Bullet.h"```
NB. Try to use full addresses after source file rather than relative so it's easier to convert to arduino IDE.