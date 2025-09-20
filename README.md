# SatTree-simulator-C
This program simulates the assembly and management of a satellite network represented as a binary tree, using custom data structures in C.

=============================================================================================================================================================================

The satellites are connected to each other, and there is a root satellite, which links all the other satellites.

Each satellite that will be part of the network has a reporting frequency. Satellites that report more frequently should be closer to the root, while satellites that report less frequently should be placed farther away. Any connection between two satellites has a constant distance K. To establish these connections, any number of link satellites may be used. The link satellites are intended to ensure communication between the main satellites.

To guarantee the connectivity of the satellites, link satellites are added whenever necessary. These intermediate satellites are responsible for maintaining the binary tree structure. The linking of satellites in the network is carried out as follows:

1. Identify the two satellites with the lowest reporting frequencies.

2. Introduce a link satellite as the parent node for these two satellites. The reporting frequency of the link satellite is calculated as the sum of the frequencies of its two child satellites. Its name is obtained by concatenating the name of the left child with the name of the right child.

3. The link satellite is then added back into the Min-Heap, and the process is repeated until all satellites are connected into a single binary tree.


EXAMPLE
 4- B4
 7- A7
 7- C7
 12- D12
 16- E16

 The final tree:
                         46-C7B4A7D12E16
                           /           \
                        18-C7B4A4     28-D12E16
                        /       \       /     \
                      7-C7    11-B4A7  12-D12  16-E16
                                /    \
                              4-B4   7-A7

=============================================================================================================================================================================

# HOW TO EXECUTE THE PROGRAM

To execute the program, you shall use the following template:

`````````````````
make
./sattree [-c1 |-c2 |-c3 |-c4] [input_file] [output_file]
`````````````````

-c1 indicates that the program will be execute operation nr. 1
-c2 indicates that the program will be execute operation nr. 2
-c3 indicates that the program will be execute operation nr. 3
-c4 indicates that the program will be execute operation nr. 4

=============================================================================================================================================================================

# -C1 | OPERATION NR. 1

The program receives as input a list of satellites, each characterized by a unique identifier and a data reporting frequency. A function must be implemented to build the binary tree, such that the following criteria: satellites with higher reporting frequency are closer to the root, while those with lower frequency are placed farther away. The function will return the root of the satellite network.

For building this binary tree, a Min-Heap will be used to extract, at each step, the two satellites with the smallest reporting frequencies. The satellite with the smaller reporting frequency will become the left child of the link node.

If both satellites have the same reporting frequency, the one whose name appears first in alphabetical order will be placed on the left. If there are multiple satellites with the same reporting frequency, extraction will also be performed in alphabetical order.

The resulting tree must be displayed level by level. The information in the link nodes represents the sum of the reporting times for the satellites in the two subtrees, and the name is obtained by concatenating the names of the two child nodes.

INPUT FORMAT:

Number_of_satellites  
ReportingFrequency_1 SatelliteName_1  
ReportingFrequency_2 SatelliteName_2  
...  
ReportingFrequency_N SatelliteName_N  


INPUT RESTRICTIONS: The reporting frequency is an integer. A satellite’s name is a string of at most 15 characters.

Example Input:
5  
4 B4  
7 A7  
7 C7  
12 D12  
16 E16  


Example Output:
46-C7B4A7D12E16  
18-C7B4A7 28-D12E16  
7-C7 11-B4A7 12-D12 16-E16  
4-B4 7-A7

=============================================================================================================================================================================

# -C2 | OPERATION NR. 2

The program receives a binary-encoded message. Each 0 represents a move to the left child in the satellite tree, and each 1 represents a move to the right child. The task is to decode the sequence in order to determine the satellites it refers to.

INPUT FORMAT:

Number_of_encodings  
Encoding1  
Encoding2  
...  
EncodingN  


INPUT RESTRICTIONS: Each encoding is a string of at most 1000 characters.

Example Input:
2  
00010  
1110011  


Example Output:
C7 B4  
E16 D12 A7  


Explanation:
00010 → 00 | 010
1110011 → 11 | 10 | 011

=============================================================================================================================================================================

# -C3 | OPERATION NR. 3

The program must encode a given list of satellites based on the previously built binary tree.
It reads a number N and then the names of N satellites. For each satellite, the binary code is determined by traversing the tree (0 = left child, 1 = right child).
The final output is the concatenation of the binary codes in the given order.

INPUT FORMAT:

N  
SatelliteName1  
SatelliteName2  
...  
SatelliteNameN  


Example Input:
3  
A7  
D12  
E16  


Example Output:
0111011  

=============================================================================================================================================================================

# -C4 | OPERATION NR. 4

The program must determine the lowest common ancestor of a given set of satellites in the binary tree.
It receives as input a list of satellite identifiers and must return the unique identifier of the parent satellite that connects all of them.

INPUT FORMAT:

Number_of_satellites  
SatelliteName1  
SatelliteName2  
...  
SatelliteNameN  


Example Input:
3  
B4  
A7  
C7  


Example Output:
C7B4A7

=============================================================================================================================================================================

# DOCUMENTATION


In struct_fct.h, we have the structures for a tree, nodes, queue, heap.

First, the program checks that it received 4 arguments. If it did, it gets the number of the task from the second argument and it opens the input file and output file from the third and fourth argument.

For OPERATION NR. 1, the program first reads the number of satellites from the input file, then it goes through each of them, extracting their frequency and name, creating a binary tree node for each satellite using ConstrFrBin, and inserting it into the minheap. Once all satellites are in the heap, the program extracts the two nodes (every time until we have one node left) with the lowest frequency (or alphabetically first), creates a new parent node with the combined frequencies and names of the children, links the nodes as the left and right children of the parent and inserts the parent into the heap. The last node is the root of the binary tree. The tree is printed level by level with DisplayOnLevels. At the end, all dynamically allocated memory is freed.


For OPERATION NR. 2, the program reads the number of codes from the input file, then each code line by line. For each code, it uses the PrintSatelite function to decode the binary path through the constructed binary tree and print the result: satellite's name. After it goes through all the codes, all dynamically allocated memory is freed.

For OPERATION NR. 3, the program reads the number of satellite names that need to be encoded. It then processes each satellite name by calling PrintCode to go through the binary tree and determine the binary path that leads to the leaf node (the satellite). After all satellite codes have been printed, all dynamically allocated memory is freed.

For OPERATION NR. 4, the program reads the number of satellites and allocates an array of strings to store their names. It then reads each satellite name line by line and stores is dinamically in the array. Afterthat, the program calls FindParent, which searches the binary tree to find the lowest parent of the satellites and stores the result in the parent variable. If a common parent is found, its name is printed. At the end, all dynamically allocated memory is freed.

FUNCTIONS

DisplayOnLevels
The function goes through the binary tree level by level and prints the detailes of the satelites from each level. First, it checks if the tree is empty, then initializes a queue and adds the root node to it. For each level, it counts have many nodes are there, then extracts each node, prints its frequency and name, and adds itschildren to the queue (if they exist). After printing all nodes from the current level, it writes a newline, and repeats process until the queue is empty. Finally, all dynamically allocated memory of the queue is freed.

PrintSatelite
The function starts at the root of the tree and processes each character in the code: for `'0'`, it moves to the left child, for `'1'`, it moves to the right. If it reaches a leaf node, it prints the node's name and resets the process back to the root and continues the decoding. After the loop, it checks if the last position is also a leaf. If it is, it prints its name.

PrintCode
The function does a recursive process in a binary tree to find a the given satellite and prints the path to it, where '0' means moving left and '1' means moving right. At each step, it adds the current direction to the code string and increases the level number. When the satellite is found, it ends the string with a null terminator and writes the full code to the output file and the program stops. If the satellite isn’t found in the left subtree, it goes back and tries the right one.

FindParent
The function goes through the tree until it finds the lowest parent of all the given satelites.
At each node, it recursively checks how many of the given satellites are found in the left and right subtrees and it also checks whether the current node itself is any of the satellites. If the sum of the satelites found equals to the numver of given satelites and the parent is still NULL, then the current node is the parent.

Additional explanations can be found in the comments.

