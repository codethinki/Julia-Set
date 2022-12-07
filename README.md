# Julia-Set
Vulkan based Julia Set browser

Controls:
* w-a-s-d (movement)
* zoom (scroll)
* left/right mouseButton (more/less detail)
* arrows UP/DOWN (change imaginary seed part)
* arrows LEFT/RIGHT (change real seed part)
* space (save seed to seeds/savedSeeds.txt)

to load seeds simply copy paste a saved seed or make custom ones (pattern: a + ib)

# Repo cloning: 
 
Requirements:
* Vulkan sdk
* glm
* GLFW3
* C++ 20 or above (may be lower didn't test that)

Hardcoded paths to change:
* in the Vert_Frag_Compiler.bat -> path to local glsl compiler
* in main.cpp -> path to the Vert_Frag_Compiler.bat
