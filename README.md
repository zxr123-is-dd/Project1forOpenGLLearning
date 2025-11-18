# 简介

这个项目是为了学习OpenGL。

## 注意:

### 在 Windows 下:

我使用 assimp 库来加载模型。externl 文件夹里的 lib 文件是我在 windows 操作系统
上用mingw编译的，如果在你的电脑上不能正常使用，或者你使用的是MSVC，希望你可以重新编译
一遍 assimp 的源码

运行时需要的 libassimp-6.dll 在 bin 文件夹里，运行时请将其复制到可执行文件所在目录下

assimp 项目地址: https://github.com/assimp/assimp

如果你是中文使用者，这里有一篇文章是介绍了如果在 windows 下用 mingw 编译: 
https://sirlis.cn/posts/windows-mingw64-assimp/

### 在 Linux 下:

使用依赖库:
```
# Fedora
glfw-devel assimp-devel mesa-libGL-devel mesa-libGLU-devel

# Ubuntu
libglfw3-dev libassimp-dev libgl1-mesa-dev libglu1-mesa-dev
```

# Introduction

This is a project for OpenGL learning.

## Notice:

### Windows

I use the assimp library to load models. The lib files in the externl folder 
were compiled using Mingw on the Windows operating system. If they don't work 
properly on your computer, or if you're using MSVC, I hope you can recompile 
the assimp source code.

The libassimp-6.dll required for runtime is located in the bin folder. When 
running the program, please copy it to the directory containing the executable 
file.

assimp github: https://github.com/assimp/assimp

### Linux

Dependencies
```
# Fedora
glfw-devel assimp-devel mesa-libGL-devel mesa-libGLU-devel

# Ubuntu
libglfw3-dev libassimp-dev libgl1-mesa-dev libglu1-mesa-dev
```
