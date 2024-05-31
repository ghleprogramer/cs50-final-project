This is the final project for CS50.\
The project is a fractal image creation program written in C via the command line.


------------------------------------------------------------------


The program usage is: ./fractal_gen \<option-s\>\
#when no options are given the program runs on the defaults


options are:\
-F M(mandelbrot) B(burningship) | fractal type, default M\
-P pos num | fractal equation power, default 2\
-R pos num | range of fractal, default 4\
-C num,num | farctal center, default -0.6,0\
-M pos num | fractal equation max number of iterations, default 100\
-J nosubopt | conjugate fractal equation(neg power), default not\
-Q SD(480p) ED(720p) HD(1080p) 4K 8K | image quality, default HD


-------------------------------------------------------------------


In the making of this project, the first thing that I set out to learn
was using git for project management. Git was a huge help for me.
It helped keep track of all my changes, especially when any mistakes or
weird errors happen, and also made it much easier with help from github.
for me to work on the project from different computers, as I do not normally
have one device that I use for a long period of time, but multiple
that I switch between. With using git and github, I also
learned to organize my project files better.\
Resources that helped me learn git are:\
https://git-scm.com/videos git basics docs/videos\
https://www.youtube.com/watch?v=cspx7YSvp5Q cs50 seminar on git


For this program, since the images could get rather large in size,
to save on storage I chose to use the STB image library https://github.com/nothings/stb.
Specificly stb_image_write.h to write the image into pngs, monocromic pngs, and bmps.
and that was my first time using a third-party library other than of course cs50lib.


When working on the project vary quickly it was apperante that writing my
own makefiles was not going to cut it. So I chose to learn CMake, and it was
a great idea. It took some time to understand and write the CMakeLists.txt
file for this project, but after writing it I only had to touch it once to
set the mode to debug, and that was it for compiling the project on all
my devices.\
Understanding and writing the cmake file was only possible with the help
of sir GPT https://chatgpt.com/


What first pulled me to fractals was the amazing complex details and shapes in fractal
images from https://prettymathpics.com/. And after watching the pictures for a while,
I read the article about fractals they have on the site, explaining what fractals are
and some properties of them, and a simple explanation for the mandelbrot fractal.
After that, I found myself in Sprott's Fractal Gallery https://sprott.physics.wisc.edu/FRACTALS.HTM
seeing and learning about all different types of wired and natural fractals, and from there
I was set on creating my own. After that, I kept finding more and more sites that
host fractal galleries or write about fractal equations, the one that stands out most 
for me was https://theory.org/ with there section about the burning ship fractal.


While writing this project, I had to learn some standard C library functions.
Most important are getopt and getsubopt to add proper command line usage
to the project with clean minimal(kind of) code. And the switch statement
for clear and fast setting of the values for the options. And strstr and strtod
for simple string processing.


over all writing the project and a great learning experience that taught 
me a lot about project building and management, and I am glad I got to
do it and learn programming with the amazing people of CS50.
