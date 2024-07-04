# /Tools
This contains scripts / tools to help with the development of the project.

eg. building for Arduino IDE, docs etc.

## Building for Arduino IDE
To make Arduino IDE happy you need to:
1. Create a folder called LaserTag.
2. Rename the main.cpp file in /src to LaserTag.ino and move it to the LaserTag folder.
3. Move the /src folder to the LaserTag folder.
4. Change the ```#include "LaserTag.h"``` line in new LaserTag.ino to ```#include "src/LaserTag.h"```.
5. Open the LaserTag.ino file in Arduino IDE.

- Make sure there's no main.cpp file left over
- Make sure the only file in LaserTag folder is LaserTag.ino and there's a src/ folder with the PIO src/ code in it.

Or... you can use the build script in this folder to do it for you.

```bash
chmod +x ./arduinoIDECompiler.sh

./arduinoIDECompiler.sh
```

## ```#include``` path errors
If the Arduino IDE doesn't compile this may be due to me including files in a way that PlatformIO is happy with but
Arduino IDE isn't (addresses relative to the src folder). To fix this you could change the ```#include``` lines in the
src code manually to be relative to the file itself or just run the python script in this folder.

```bash
chmod +x ./relativeAddressConverter.sh

./relativeAddressConverter.sh
```

or 

```bash
python -m relativeAddressConverter
```

