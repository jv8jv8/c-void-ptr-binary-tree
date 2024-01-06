# C-void-ptr-binary-tree
Implementation of binary tree node and binary tree using void pointers for data
to allow for greater flexibility at cost of greater memory overhead. Attribute 
type_size is used as in indicator for how many bytes the associated data type 
uses. For example, if the node points to a standard int type, then 
type_size = 4. A uint64_t is used so that the node struct is a round 32 bytes 
in size. Since data is referenced by a pointer, and the node struct is intended 
to be dynamically allocated, the function deconstructing the node takes a 
parameter that specifies whether or not to also free the data pointer because 
the referenced data may not be dynamically allocated. The tree struct has an 
attribute that indicates if the data of its nodes is dynamically allocated 
or not.

## Notes:  
(1) The user should still (/is expected to) cast the data they are accessing.  
(2) The tree struct is handled through pointers when passing to functions.  
(3) This library does not contain any method for memory pools and is up to the
    user to implement

### ABOUT TEST PROGRAM

BUILD:
gcc -DJV_BINTREE_INT_DEBUG jv_bintree.h jv_bintree.c bintreetest.c -o test

RUN:
./test

Program uses debug functions and must have them defined like in the included
build command line.

### REMARKS

I'm an electrical engineering major that took great intereset in lower level
programing. I have a semester of experience in a C fundamentals course and
a pretty basic knowledge of C++ which I self taught and took another semester
long course on. This repository represents step 1 of my own implementation of
jpg to bmp image conversion. I don't have anymore strictly software based
classes left in my curriculum, but fully intend on continuing to learn and
improve my C/C++ programing knowledge so any feedback on this and following
projects is more than welcome.
