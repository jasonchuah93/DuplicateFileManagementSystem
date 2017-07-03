#ifndef Rotation_H
#define Rotation_H

#include "Node.h"

void leftRotate(Node **nodePtr); //pivot point
void rightRotate(Node **nodePtr);
void leftRightRotate(Node **nodePtr);
void rightLeftRotate(Node **nodePtr);

//Improved version
void leftRotateVer2(Node **nodePtr); //pivot point
void rightRotateVer2(Node **nodePtr);
void leftRightRotateVer2(Node **nodePtr);
void rightLeftRotateVer2(Node **nodePtr);

#endif // Rotation_H
