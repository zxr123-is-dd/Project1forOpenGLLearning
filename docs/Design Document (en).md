# Designe Document

## Overview

The goal was to implement the basic functions of a 3D engine.

Functions such as mathematical calculations amd model loading used libraries such as glm, stb_image, assimp.

Other functions such as lighting and physics, were implemented manually.

"S_" means system

"C_" means compenent

## Functions

### Object (Object.h)

There should be several base object classes and multiple derived classes to construct the object management system.

#### Base Class

##### BaseTerrianObject

### Mesh (Mesh.h)

Meshes are categorized to two types.

#### StaticMesh

StaticMesh is used for render what the players should see and marked with "SM_" (static mesh) prefix.

#### CollsionMesh

CollsionMesh is primarily used for terrain collision detection and marked with "MC_" (mesh collision) prefix.

CollsionMesh also employed for collsion detection in certain movable objects, such as doors which can open and close. ConvexCollsionMeshes should be simple and low-polygon. This kind of meshes is marked with "UCX_" (mesh collision) prefix.