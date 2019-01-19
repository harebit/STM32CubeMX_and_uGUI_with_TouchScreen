### Description
I presume you have an IDE, in this example I use SW4STM32 (Eclipse), STM32CubeMX and µGui.

You can download all from STMicroelectronics and µgui from [here](http://embeddedlightning.com/ugui/).

If you prepare eclipse, **don't** use this letter "**µ**" this will make problems, use instead of "**u**".

The display in this example uses pins in two different ways, there isn't a possibility to make the configuration directly with STM32CubeMX, therefore we use a trick.

Make the configuration in STM32CubeMX in two version. First with all pins **without** the pins for the touch screen and the second version **with** the pins, which change be using the touch screen. Compare the different files and prepare it for changing in the program. 

In the folder docs I have made some sketches and a calculation for background knowledge.

Compile the project and program your controller.

The display should look like this. 

![Start](C:\Users\Hare\Desktop\ugui\Start.JPG)


harebit

