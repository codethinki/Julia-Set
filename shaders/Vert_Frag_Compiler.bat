@echo off
"E:/Visual Studio/SDK/Vulkan/Bin/glslc.exe" shader.vert -o vert.spv>NUL 2>vert.txt
"E:/Visual Studio/SDK/Vulkan/Bin/glslc.exe" shader.frag -o frag.spv>NUL 2>frag.txt
"E:/Visual Studio/SDK/Vulkan/Bin/glslc.exe" shader32.frag -o frag32.spv>NUL 2>frag32.txt

