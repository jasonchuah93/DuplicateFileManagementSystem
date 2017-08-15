#ifndef Rotation_H
#define Rotation_H

#include "Node.h"

//Use for add node function
void leftRotate(Node **nodePtr); //pivot point
void rightRotate(Node **nodePtr);
void leftRightRotate(Node **nodePtr);
void rightLeftRotate(Node **nodePtr);

//Use for delete node function
void leftRotateVer2(Node **nodePtr); //pivot point
void rightRotateVer2(Node **nodePtr);
void leftRightRotateVer2(Node **nodePtr);
void rightLeftRotateVer2(Node **nodePtr);

#endif // Rotation_H
