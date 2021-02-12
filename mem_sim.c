#include<stdio.h>
#include<stdlib.h>


//beginning of firstFit
/*this operation done by comparing the frame size of
the process and the frame size of the hole and by checking the available frames for avoiding memory
overflow. It doesn’t check the best or worst place; it just placesoverflow. It doesn’t check the best or worst place; it just places the process to the first empty hole.*/
void firstFit(char type[], int id[], int frame_size[], int size[], int totalFrame,int flags[],int allocate[]){


int totalBlock=totalFrame;




int control, temp;

int i, j, b, n, m, k, extCount=0, intCount=0, insCount=0;



for(i=0; i<totalFrame; i++){

flags[i] = 0;

allocate[i] = -1;
}


for(b=0; b<11; b++)
{

if(type[b] == 'B'){


for(n=0; n<totalFrame; n++){

    if(totalBlock<frame_size[b]){
    
	printf("\n%c  %d  %d  -> ERROR! Insufficient memory \n", type[b], id[b], size[b]); 
	
	insCount++;
	
	break;   
    }
    
   

    if(n+frame_size[b]<totalFrame && flags[n]==0){
    
     if(flags[n+frame_size[b]]==1){
     
     
     temp = n+frame_size[b];
     	while(temp<totalFrame){
     	
     	if(flags[temp]==0 && flags[temp + frame_size[b]] ==0)
     	{
     	
     	   control = 1;
     	   for(m=temp; m<temp + frame_size[b] ; m++){
     	   
     	       allocate[m] = id[b];
    		
    	       flags[m] = 1;
     	
     	}
     	totalBlock = totalBlock-frame_size[b];
    	
    	printf("\n%c  %d  %d  ->  %d frames will be used, remaining # frames: %d\n", type[b], id[b], size[b], frame_size[b], totalBlock);
    	
    	if(size[b] % 4 !=0 )
	{
	intCount = intCount + (4*frame_size[b] - size[b]);

	}
    	
    	
     	}
     	temp+=frame_size[b];
     	
     	}
    	
    	if(control != 1){
    	extCount++;
    	printf("\n%c  %d  %d  -> %d frames will be used, ERROR! External fragmentation\n", type[b], id[b], size[b], frame_size[b]);
    	}
    	break;
    
    }
    
    
   else if(flags[n+frame_size[b]]!=1) 
    {
    	for(m=n; m<n+frame_size[b]; m++){
    	
    		allocate[m] = id[b];
    		
    		flags[m] = 1;
    		
    		
    		
    	}
    	
    	totalBlock = totalBlock-frame_size[b];
    	
    	printf("\n%c  %d  %d  ->  %d frames will be used, remaining # frames: %d\n", type[b], id[b], size[b], frame_size[b], totalBlock);
    	
    	if(size[b] % 4 !=0 )
	{
	intCount = intCount + (4*frame_size[b] - size[b]);

	}
	
    	break;
    }	
   
    
    


}





}



}
else if(type[b] == 'E'){

for(n=0; n<totalFrame; n++){

	if(allocate[n] == id[b]){
	
	flags[n] = 0;
	
	allocate[n] = -1;
	

	}


}

totalBlock = totalBlock + frame_size[b];

printf("\n%c %d  ->  %d frames are deallocated, available # frames: %d\n", type[b], id[b], frame_size[b], totalBlock);

}



}


printf("\nTotal free memory in holes: %d frames, %d KB\n", totalBlock, totalBlock*4);

printf("\nTotal memory wasted as an internal fragmentation: %d KB\n",intCount);

printf("\nTotal number of rejected processes due to external fragmentation: %d \n", extCount);

printf("\nTotal number of rejected processes due to insufficient memory: %d \n", insCount);

int start;
int end;

printf("Holes: \n");
//for finding holes at the end
for(i=0; i<totalFrame; i++)
{

    
    if(flags[i]==0 && flags[i-1]==1)
    {
    	start = i;
    
    	printf("%d  ", start);
    
    }


    if(flags[i] == 0 && flags[i+1]==1)
    {
    	end = i+1;
    
    	printf("%d \n", end-start);
    }


   if(flags[i] == 0 && i==totalFrame-1){
   
   	end = i+1;
    
    	printf("%d \n", end-start);
   
   
   
   }
    


}



}

int holeCount = 0;

int hole[10][2];

//for finding all holes in memory space
void findHole(int memory[],int totalFrame)
{
	int i,j;
	int holeSize=0;
	int a=0;
	int start;
	
	for( i=0;i<totalFrame;i++)
	{
		if(memory[i]==0)
		{	
			holeSize=0;
	 		if(memory[i-1]!=0)
			{	 		
		 		holeSize++;
		 		start=i;
		      	for( j=start;j<totalFrame;j++)
				{
		      		if(memory[j+1]!=0)
					{
		                break;
				    }
		         	else if(memory[j+1]==0)
		           		holeSize++;
		        }
		    	hole[a][0]=start;
	 	        hole[a][1]=holeSize;
		        a++;   
		    }
	 	}	
	}
	holeCount=a;
}

/* In best- fit strategy, the program uses two different arrays, one of them is for holes and one of them
is for available hole at that moment. After we found all the holes in memory space, program determines the
available holes which mean the holes that have greater frame size than the process.*/
void bestFit(char type[], int id[], int frame_size[], int size[], int memory[], int totalFrame)
{

int totalBlock = totalFrame;

int properHole= 0;

int temp=0;

int holeController[10][2]; 

int i, b, j;

int insCount = 0;
int intCount=0;
int extCount=0;


for(b=0; b<11; b++){

temp=0;


for(i=0;i<10;i++)
{
   holeController[i][0]=-1;
   holeController[i][1]=-1;
}

int controller=0;
int allocate=1;
int min,c=0;

int frameSize = frame_size[b]; 

findHole(memory, totalFrame);

for(i=0;i<=holeCount;i++)
{
	if(hole[i][1]>=frameSize)
	{
        holeController[temp][0]=hole[i][0];
        holeController[temp][1]=hole[i][1];
        temp++;
        }
}

        min=holeController[0][1];
        if(temp==0)
        {
            allocate=0;
        }
        for(j=0;j<=temp;j++)
        {
            if(min>holeController[j][1] && 0<holeController[j][1])
            {
                min= holeController[j][1];
                c=j;
            }
        }
        properHole= holeController[c][0];



        if(type[b]=='B')
        {
            if(totalBlock<frame_size[b])
            {
                printf("%c %d %d -> ERROR! Insufficient memory\n",type[b],id[b],size[b]);
                insCount++;
            }
            else
            {
                if(allocate==1)  
                {
                    for(i=properHole;i<properHole+frame_size[b];i++)
                    {
                        memory[i]=id[b];
                    }
                    totalBlock=totalBlock-frame_size[b];
                    printf("%c %d %d -> %d frames will be used, remaining #frame: %d\n",type[b], id[b], size[b], frame_size[b],totalBlock);
                    if(size[b]%4!=0)
                        intCount = intCount + (4*frame_size[b] - size[b]);
                        
                        
                }
                
                if(allocate==0)
                {
                    findHole(memory,totalFrame);
                    for(i=0;i<=holeCount;i++)
                    {
                        if(hole[i][1]==0 && totalBlock>frame_size[b])
                        {
                            printf("%c %d %d -> %d frames will be used, ERROR! External fragmentation\n",type[b],id[b],size[b],frame_size[b]);
                            extCount++;
                            break;
                        }
                    }
                }
            }
        }
        
        
        
        else if(type[b] == 'E'){
        
            for(i=0;i<totalFrame;i++)
            {
                if(memory[i]==id[b])
                {
                    memory[i]=0; 
                }
                
            }
            totalBlock= totalBlock+ frame_size[b];
            printf("%c %d     -> %d frames are dealllocated, available  #frame: %d\n",type[b],id[b],frame_size[b],totalBlock);
        }
        
        
        }

findHole(memory, totalFrame);

printf("\nTotal free memory in holes: %d frames, %d KB\n", totalBlock, totalBlock*4);

printf("\nTotal memory wasted as an internal fragmentation: %d KB\n",intCount);

printf("\nTotal number of rejected processes due to external fragmentation: %d \n", extCount);

printf("\nTotal number of rejected processes due to insufficient memory: %d \n", insCount);

printf("\nHoles:\n");

for(i=0;i<holeCount;i++)
{
  printf("\n%d    %d\n", hole[i][0], hole[i][1]);
}

}
/* In worst- fit strategy, the program uses two different arrays, one of them is for holes and one of them
is for available hole at that moment. After we found all the holes in memory space, program determines the
available holes which mean the holes that have greater frame size than the process.*/
void worstFit(char type[], int id[], int frame_size[], int size[], int memory[], int totalFrame){


int totalBlock = totalFrame;

int properHole= 0;

int temp=0;

int holeController[10][2]; 

int i, b, j;

int insCount = 0;
int intCount=0;
int extCount=0;


for(b=0; b<11; b++){

temp=0;


for(i=0;i<10;i++)
{
    holeController[i][0]=-1;
    holeController[i][1]=-1;
}

int controller=0;
int allocate=1;

int max,c=0;

int frameSize = frame_size[b]; 

findHole(memory, totalFrame);

for(i=0;i<=holeCount;i++)
{
	if(hole[i][1]>=frameSize)
	{
         holeController[temp][0]=hole[i][0];
         holeController[temp][1]=hole[i][1];
        temp++;
        }
}

        max= holeController[0][1];
        if(temp==0)
        {
            allocate=0;
        }
        for(j=0;j<=temp;j++)
        {
            if(max< holeController[j][1] && 0< holeController[j][1])
            {
                max= holeController[j][1];
                c=j;
            }
        }
        properHole= holeController[c][0];



        if(type[b]=='B')
        {
            if(totalBlock<frame_size[b])  
            {
                printf("%c %d %d -> ERROR! Insufficient memory\n",type[b],id[b],size[b]);
                insCount++;
            }
            else
            {
                if(allocate==1)  
                {
                    for(i=properHole;i<properHole+frame_size[b];i++)
                    {
                        memory[i]=id[b];
                    }
                    totalBlock=totalBlock-frame_size[b]; 
                    printf("%c %d %d -> %d frames will be used, remaining #frame: %d\n",type[b], id[b], size[b], frame_size[b],totalBlock);
                    if(size[b]%4!=0)
                        intCount = intCount + (4*frame_size[b] - size[b]); 
                        
                        
                }
                
                if(allocate==0)  
                {
                    findHole(memory,totalFrame);
                    for(i=0;i<=holeCount;i++)
                    {
                        if(hole[i][1]==0 && totalBlock>frame_size[b]) 
                        {
                            printf("%c %d %d -> %d frames will be used, ERROR! External fragmentation\n",type[b],id[b],size[b],frame_size[b]);
                            extCount++;
                            break;
                        }
                    }
                }
            }
        }
        
        
        
        else if(type[b] == 'E'){
        
            for(i=0;i<totalFrame;i++)
            {
                if(memory[i]==id[b])
                {
                    memory[i]=0; 
                    totalBlock++;
                }
            }
          
            printf("%c %d     -> %d frames are dealllocated, available  #frame: %d\n",type[b],id[b],frame_size[b],totalBlock);
        }
        
        
        }

findHole(memory, totalFrame);

printf("\nTotal free memory in holes: %d frames, %d KB\n", totalBlock, totalBlock*4);

printf("\nTotal memory wasted as an internal fragmentation: %d KB\n",intCount);

printf("\nTotal number of rejected processes due to external fragmentation: %d \n", extCount);

printf("\nTotal number of rejected processes due to insufficient memory: %d \n", insCount);

printf("\nHoles:\n");

for(i=0;i<holeCount;i++)
{
  printf("\n%d    %d\n", hole[i][0], hole[i][1]);
}








}


int main(int argc, char *argv[]){

FILE *myFile;
myFile = fopen(argv[2], "r");


int totalMemory = atoi(argv[1]);

int allocStrategy = atoi(argv[3]);

int blockSize = 4;

int totalFrame;

char type[11];
int id[11];
int size[11];
int frame_size[11];

int num;


int i;
int j;



for(i=0; i<11; i++){
fscanf(myFile, " %c", &type[i]);

fscanf(myFile, "%d", &id[i]);

if(type[i] =='B')
{
fscanf(myFile, "%d", &size[i]);
}

else if(type[i] =='E'){
size[i] = 0;
}

if(size[i]!=0){

if(size[i]%blockSize == 0)
{
frame_size[i] = size[i]/(double) blockSize;
}

else if(size[i]%blockSize != 0){
frame_size[i] = (size[i] / (double) blockSize) + 0.5;
}


}

else{

    for(j=0; j<i; j++){
    
    if(type[j] == 'B' && id[i]==id[j]){
    num=j;
    break;
}


}

frame_size[i] = frame_size[num];
}

}


totalFrame = totalMemory/blockSize;
int flags[totalFrame];

int allocate[totalFrame];


int memory[totalFrame];

for(i=0;i<totalFrame;i++)
{
    memory[i]=0;
}


if(allocStrategy==1){

firstFit(type, id, frame_size, size, totalFrame,flags,allocate);
}

else if(allocStrategy==2){
bestFit(type, id, frame_size, size, memory, totalFrame);
}

else if(allocStrategy ==3){
worstFit(type, id, frame_size, size, memory, totalFrame);
}

return 0;

}
