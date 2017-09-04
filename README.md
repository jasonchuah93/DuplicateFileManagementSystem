Introduction
----------------------------------------------------------------------------------
DuplicateFileManagementSystem is a program that identify similar/duplicate files 
and let the user knows these duplicate files location.  

How It Work
----------------------------------------------------------------------------------
The software will need the user to input an argument which is the folder path that
they want to search for the duplicate files. Example of folder path: "testFolder".

1.	The program will scan the entire folder to look for any json file.
	If there is a json file exist in folder, update the json file with the latest data.
	If no json file inside the folder, the program will create json file with all the
	file information presented in json format. 

2.	A node is created to store a file and prepare to add into the Red Black Tree(RBT). 
	The node contains of file information from the json object. 
	The node is then added into the RBT by comparing the size & crc.
	When the RBT root is empty, the first node is added in without comparing. 
	For the next incoming nodes, they will compare the size & crc with the node inside 
	the RBT root. 
	If the incoming node has larger size, they will add to the left side of the RBT.
	If the incoming node has smaller size, they will add to the right side of the RBT.
	If the incoming node has similar size, the incoming node will compare the crc value 
	with the crc value of the node in the RBT. 
	If both node has the same size & same crc values, the node inside the RBT will make
	1 copy of itself and move out of the RBT. 
	Note: the incoming node which has the same size & crc did not add into the RBT as well.

3.  Now both incoming nodes and the copied node will group together in linked list.
	This applied to the next incoming nodes as well. 
	
4.  A second RBT is created. This second RBT will store the linked list in the form of node. 
	
5. 	After all the files in added into the 1st and 2nd RBT. The program will check if there is
	any sub folder. If yes, repeat Step 1 to Step 5 again untill all sub folder files is being add
	into the RBTs as well. 
	
6.	From 2nd RBT, each nodes which contain of linked list will be taken out from the RBT. 
	Then, the linked list which has a group of similar files will be print out as message to 
	let user know they are duplicated and their location. 

Method of Implementation 
----------------------------------------------------------------------------------
To build this software, there are few algorithms/APIs being used. 
1) Jansson Library/API
   Jansson is a C library for encoding, decoding and manipulating JSON data. 
   The purpose of using Jansson in this project is to list out all the file's 
   informations within the folder in json format. Basically one file contain few
   informations such as the name, size, last modified date & time & the crc32 value.
   Example:
   {
    "File Info":[
        {
            "crc":1695663528,
            "size":2888,
            "epoch":1503401536,
            "name":"forTesting/sysmem.c"
        },
        {
            "crc":1695663528,
            "size":2888,
            "epoch":1503401536,
            "name":"forTesting/sysmem2.c"
        },
	}
	
	With the files information listed out in json format. We can easily used these 
	information to do comparison of 2 files to find out whether there are duplicate 
	in term of size, crc value or even bytes. 
	
2) Red Black Tree (RBT)
   RBT is a binary search tree with one extra feature for each node: colour, which come
   in either red or black. 
   For more information, please refer : https://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html
   RBT in this project basically help to sort the file together in term of size & crc.
   
3) Linked-List 
   Linked list is a linear collection of data elements. Each element is pointing to the next element.
   The data is represent in sequence form. 
   In this project, files that are found out to be similar are group together in a link list. 

