# DynamicMemoryAllocationSimulation

Group Members:
Aysu Sözen
Ceyda Alpay @ceydalpay

In this project , we implement a dynamic memory allocation simulation for a contiguous memory system
which includes three memory allocation strategies as first fit, best fit and worst fit. The p rogram takes the
size of memory, name of the text file that contains process operation (B for allocation, E deallocation ), ids,
and process sizes, and which memory allocation strategy program will use (1 for first fit, 2 for best fit, and 3
for worst fit) from the user.
The program reads the text file first and places the values to arrays that hold operations, the id of
processes, and the size of processes respectively. Then it calculates the frame sizes of each process and
places them into another array. The program calculates also the total frame size as memory size divided by
block size which is given in the question as 4 kb fixed. These operations are done for sending proper
parameters to functions used for memory allocation strategies.
The function used for first fit works as frame by frame. It checks the emptiness of frames which is called
holes and places the p rocess to the first empty place. It does this operation by comparing the frame size of
the process and the frame size of the hole and by checking the available frames for avoiding memory
overflow. It doesn’t check the best or worst place; it just places th e process to the first empty hole. For
example, let’s say we have three holes with size of 5, 35, and 40 and the size of process is 20. First fit places
the process to 35 and doesn’t check the other holes. But there is one exception which is checking the
external fragmentation error. The function gives the external fragmentation error when the process tries to
fit in the hole which has less frame size than the frame size of the process, w hen this error occurs the first fit
function searches for another hol e to fit the process. If any proper hole cannot be found, that means process
has external fragmentation
On the other hand, best fit and worst fit functions work in a different way. We have to consider all the
available holes at the same time for these strategies, and we have to choose the proper hole for the given
process. In both strategies, the program uses two different arrays, one of them is for holes and one of them
is for available hole at that moment. After we found all the holes in memory space, program determines the
available holes which mean the holes that have greater frame size than the process. For example, let’s say
we have three holes w ith size of 5, 3 5, and 40 and the size of process is 30. Program first chooses the holes
with size of 3 5 and 40 and places them into available holes array. And finally the actual choosing part begins.
In best fit the proper hole chosen as the minimum frame sized available hole, on the other hand in worst fit
the proper hole chosen as the maximum frame sized available hole. For example when best fit chooses the
35 frame sized hole for the 30 frame sized process, worst fit chooses the 40 frame sized for the 30 frame
sized process. The both functions do this process after every allocation and deallocation operat ions.
All three operations also check if there is an insufficient memory space, any external fragmentation, and
any internal fragmentation. These operations are done in the almost same way in all three functions. The
internal fragmentation occurred when the size of the process is smaller than the size of the memory block
which holds the process. The insufficient memory space and external fragmentation situation are also
explained above.
