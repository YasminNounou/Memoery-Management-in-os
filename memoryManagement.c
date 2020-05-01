#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int PageNumbers;
int *temp;
void fifo(){
    int fault = 0; //counter for page faults
    int array[MAX];      //array to hold inputs
    int frameNo[PageNumbers];   //frames
    int input;  //flag for found pages
    int flag=0;         // flag for fault in print
    int count=0;    //count for page inputs
    int index=0;    //index for frames
    int nextinput=PageNumbers;  //counter to avoid fault in empty buffer
    //*temp=frameNo[];
    //init_frames(temp);
    for (int m=0;m<PageNumbers;m++){        //init frames to 0
        frameNo[m]=0;
    }

    for(int i=0;i<MAX;i++){     //loop to count pages till it finds -1
        scanf("%d",&array[i]);
        if(array[i]!=-1){
        count++;
        }
        else
            break;
    }
    for(int i=0;i<count;i++){ //start loop for replacement
        printf("%02d",array[i]);

       flag=0;
       input=0;
        for (int j=0;j<PageNumbers;j++){
            if(frameNo[j]==array[i]){       //if element found raise flag of input
                flag=0;
                input=1;
            }

        }
        if(input==0){   //if not found start adding it to frameNo array for frames
                frameNo[index]=array[i];
                index++; // increment index
                nextinput--;
                index%=PageNumbers; //for circular buffer
                if(nextinput<0){
                flag=1;     //start raising flags for faults
                fault++;
                }
        }

        if(flag==1){
            printf(" F   ");
        }
        else{
            printf("     ");
        }
        for(int k=0;k<PageNumbers;k++){
            if(frameNo[k]!=0){
                printf("%02d ",frameNo[k]); // start printing frames no.in two digits

            }
        }
        printf("\n");

    }
    printf("-------------------------------------\n");
        printf("Number of page faults = %d\n",fault);

}
void clock(){
    int fault = 0;
    int array[MAX];
    int frameNo[PageNumbers];
    int use_bit[PageNumbers]; //used to keep track of used bits
    int flag=0; //flag for faults
    int count=0;        //count pages
    int index=0;    //index for frames
    int input=0;    //flag for found pages
    int nextinput=PageNumbers-1;    //index to keep track of fault in empty buffer
    for (int m=0;m<PageNumbers;m++){
        frameNo[m]=0;       //init frames and usebits to 0
        use_bit[m]=1;
    }

    for(int i=0;i<MAX;i++){         //counting pages
        scanf("%d",&array[i]);
        if(array[i]!=-1){
        count++;
        }
        else
            break;
    }
    for(int i=0;i<count;i++){
        printf("%02d",array[i]);
       flag=0;
       input=0;
        for (int j=0;j<PageNumbers;j++){
            if(frameNo[j]==array[i]){       // if found element raise use bit to 1 and end loop
                flag=0;
                input=1;

                    use_bit[j]=1;
                //index=j;
                break;
            }
            else if(frameNo[j]==0){
                    //to add elements first to empty buffer and set use bit to 1
            frameNo[j]=array[i];
            flag=0;
            input=1;
            use_bit[j]=1;
            break;
            }
        }
        if(input==0){ // if element not found

                while(!input){
                if(use_bit[index]==0){// if use bit=0? so we can add page
                        frameNo[index]=array[i];
                    use_bit[index]=1;
                    flag=1; //raise flag to print F
                    fault++; //increment fault
                input=1;  //raise flag of found

                }
                else{
                    use_bit[index]=0;//else set use bit to 0
                }
                }
            index+=1;
            index%=PageNumbers; //increment index

        }

        if(flag==1){
            printf(" F   ");
        }
        else{
            printf("     ");
        }
        for(int k=0;k<PageNumbers;k++){
            if(frameNo[k]!=0){
                printf("%02d ",frameNo[k]);

            }
        }
        printf("\n");

    }
    printf("-------------------------------------\n");
        printf("Number of page faults = %d\n",fault);


}
void lru(){
int fault = 0;      //no. of faults
    int array[MAX];  //array of page numbers
    int frameNo[PageNumbers];//frames array
    int input; //flag for found
    int flag=0;//flag for print
    int count=0;    //count pages
    int index=0;    //index for frames
    int loc=0;  //location of second array of holding least recently used pages of the whole frames -1
    int max=PageNumbers-1;
    int nextinput[max]; //array of holding LRU pages

    for (int m=0;m<PageNumbers;m++){  //initialization
        frameNo[m]=0;
        nextinput[m]=0;
    }

    for(int i=0;i<MAX;i++){
        scanf("%d",&array[i]);
        if(array[i]!=-1){ //count of pages
        count++;
        }
        else
            break;
    }

    for(int i=0;i<count;i++){
        printf("%02d",array[i]);
       flag=0;
       input=0;
       index=0; //init index
    int flag1=0;

        for (int j=0;j<PageNumbers;j++){
            if(frameNo[j]==array[i]){       //if found element raise flag
                flag=0;
                input=1;
               nextinput[loc]=array[i];// add to LRU buffer
               loc++;
               loc%=(max);//increment location
                break;
            }
            else if(frameNo[j]==0){
            frameNo[j]=array[i];
             nextinput[loc]=array[i]; //loop for adding page to empty buffer of frames and adding it to LRU buffer
               loc++;
               loc%=(max);  //increment location
            flag=0;
            input=1;
            break;
            }

        }
if(input==0){

            for(int n=0;n<PageNumbers;n++){   //ne itested loop for checking page thats not found in LRU buffer to replac
                    for(int g=0;g<max;g++){
                    if(frameNo[n]==nextinput[g]){
                            flag1=0;
                        break;
                    }
                    else{
                       // printf("%d %d\n",nextinput[0],nextinput[1]);
                      //  printf("ERRRORRR!!!");
                        index=n;
                        flag1=1;
                        break;
                    }
                    if(flag1==1) // flag to end loop once element found
                        break;
                }
            }
                frameNo[index]=array[i];
                flag=1;
                fault++; //raising flags and incrementing faults for adding new page
        }
        if(flag==1){
            printf(" F   ");
        }
        else{
            printf("     ");
        }
        for(int k=0;k<PageNumbers;k++){
           // if(frameNo[k]!=0){
                printf("%02d ",frameNo[k]); //printing elements

           // }
        }
        printf("\n");

    }
    printf("-------------------------------------\n");
        printf("Number of page faults = %d\n",fault);

}
void optimal(){
    int fault = 0;
    int array[MAX];
    int frameNo[PageNumbers];
    int input;
    int flag=0;
    int count=0;
    int index=0;

    for (int m=0;m<PageNumbers;m++){    //initialization
        frameNo[m]=0;
    }

    for(int i=0;i<MAX;i++){
        scanf("%d",&array[i]);  //counting pages
        if(array[i]!=-1){
        count++;
        }
        else
            break;
    }
    for(int i=0;i<count;i++){
        printf("%02d",array[i]);

       flag=0;
       input=0;
        for (int j=0;j<PageNumbers;j++){
            if(frameNo[j]==array[i]){ //found page
                flag=0;
                input=1;
                break;
            }
            else if(frameNo[j]==0){
            frameNo[j]=array[i]; //fill empty buffer
            flag=0;
            input=1;
            break;
            }

        }
        int index1=0;  //index for first frame no
        int index2=0;   //index for second frame no
        int index3=0;   //index for third frame no
        if(input==0 ){

                for(int i1=i+1;i1<count;i1++){
                    if (frameNo[0]==array[i1]){ //loop to find nearst occurance for page no for frame 1
                        index1=i1;
                        break;
                    }
                    else{
                        index1=100; //adding large number so that any index would be less than that and end loop succesfully
                    }

                }

                for(int i2=i+1;i2<count;i2++){
                    if (frameNo[1]==array[i2]){
                        index2=i2;      //loop to find nearst occurance for page no for frame 2
                        break;
                    }
                    else{
                        index2=100; //adding large number so that any index would be less than that and end loop succesfully
                    }

                }
                for(int i3=i+1;i3<count;i3++){
                    if (frameNo[2]==array[i3]){
                        index3=i3;
                        break;              //loop to find nearst occurance for page no for frame 3
                    }
                    else{
                        index3=100; //adding large number so that any index would be less than that and end loop succesfully
                    }
                }

//checks which index if the greatest to replace
                    if(index1>=index2 && index1>=index3){
                frameNo[0]=array[i];
                flag=1;
                fault++;

                }

                else if (index2>=index1 && index2>=index3){
                frameNo[1]=array[i];
                flag=1;
                fault++;

                }
                else if (index3>=index1 && index3>=index2){
                frameNo[2]=array[i];
                flag=1;
                fault++;

                }
                else
                    printf("ERROR!!!");

        }


        if(flag==1){
            printf(" F   ");
        }
        else{
            printf("     ");
        }
        for(int k=0;k<PageNumbers;k++){
            if(frameNo[k]!=0){
                printf("%02d ",frameNo[k]);

            }
        }
        printf("\n");

    }
    printf("-------------------------------------\n");
        printf("Number of page faults = %d\n",fault);


}

int main()
{
    //int PageNumber =3;
    int command[5];
    scanf("%d",&PageNumbers);
    char type[10];
    char type_fifo[] = "FIFO";  //initializing types
    char type_clock[] = "CLOCK";
    char type_lru[] = "LRU";
    char type_optimal[] ="OPTIMAL";
    scanf("%s",type);       //scanning type
    printf("Replacement Policy = %s\n",type);
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");
    //check which type to run
    if (strcmp(type,type_fifo)==0){
        fifo();
    }
    else if(strcmp(type,type_clock)==0){
        clock();
    }
    else if(strcmp(type,type_lru)==0){
            lru();
    }
    else if(strcmp(type,type_optimal)==0){
            optimal();
    }
    else{
        printf("Type not available!!");
    }
    //printf("Hello world!\n");
    return 0;
}
