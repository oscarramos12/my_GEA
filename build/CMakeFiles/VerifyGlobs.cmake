# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.22
cmake_policy(SET CMP0009 NEW)

# SOURCES at CMakeLists.txt:11 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/oscar/Desktop/GEAFINAL/src/*.cpp")
set(OLD_GLOB
  "/home/oscar/Desktop/GEAFINAL/src/ECS/glm/detail/glm.cpp"
  "/home/oscar/Desktop/GEAFINAL/src/Game/Game.cpp"
  "/home/oscar/Desktop/GEAFINAL/src/Game/Graphics/Texture.cpp"
  "/home/oscar/Desktop/GEAFINAL/src/Game/Graphics/TextureManager.cpp"
  "/home/oscar/Desktop/GEAFINAL/src/Game/ScriptingManager.cpp"
  "/home/oscar/Desktop/GEAFINAL/src/Pong/Pong.cpp"
  "/home/oscar/Desktop/GEAFINAL/src/Scene/Scene.cpp"
  "/home/oscar/Desktop/GEAFINAL/src/main.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/oscar/Desktop/GEAFINAL/build/CMakeFiles/cmake.verify_globs")
endif()
