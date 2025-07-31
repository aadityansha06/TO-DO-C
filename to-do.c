#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>



typedef struct node{
    char data[500];
    int status;
    struct node *next;
}node;
node *start = NULL;
FILE *fp;
node* createnode(){
    node *addr;
    addr= (node *)malloc(sizeof(node));
    return (addr); // p is address of the dynamically created pointer
}

void viewtodo();

void inserttodo();
void edit();

void completetodo();

void deletetodo();
void fetchdata();
void storefile();
int main(int argc, char const *argv[])
{

    int opt;
    fp =fopen("to-do.txt","r");
   if (fp!=NULL)
   {
         fetchdata();   // fetch data from the file
   }
   
         
    
    
    
   
      label:
            
    viewtodo();
   printf("\n\t\t===============================================\n");
    printf("\t\t1. Add new To-do\n");
    printf("\t\t2. Edit existing To-do\n");
    printf("\t\t3. Mark To-do as completed\n");
    printf("\t\t4. Delete To-do\n");
    printf("\t\t5. Quit\n");
    printf("\t\t===============================================\n");
    printf("\t\tPress your choice... ");
        scanf("%d",&opt);

        switch (opt)
        {
        case 1:
             inserttodo();
             goto label;
        case 2:
                edit();
                goto label;
         case 3:
                completetodo();
                goto label;
        
        case 4:
                deletetodo();
                goto label;
        case 5:
                printf("\n By-By see you next time\n");
                system("pause");
                return(1);
        default:
            printf("\n invalid choice");
            Sleep(1000);
              goto label;
        }

    return 0;
}




void inserttodo(){
    char buffer [500]; // temprory to sotre data
   fflush(stdin);
    printf("\nEnter new item to the list:\t");
     fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // remove the new line at the end of buffer
    if (start==NULL)
    {
        start = createnode();
        strcpy(start->data,buffer);
        start->next=NULL;
        start->status=0;// 0 is not done and 1 is done
            fp= fopen("to-do.txt","w");
            fprintf(fp,"%s|%d\n",start->data,start->status);
            fclose(fp);
         printf("\nInserted into TO-DO LIST Sucessfully..\n");
        Sleep(1000); 

    }else{

        node *temp;
        temp = createnode();
        strcpy(temp->data,buffer);
        temp->next = start;
        temp->status=0;
        start = temp;
        storefile();
        printf("\nInserted into TO-DO LIST Sucessfully..\n");
        Sleep(1000);
    }
    
}
void viewtodo(){
       system("cls");
      
     printf("\n\t\t\t********* TO-DO LIST *********\n\n");
    if (start==NULL)
    {
        printf("\n \t\t\t\tNo To-do-list inserted\n");
          printf("\t\t\tAdd some items to get started...\n");
    }else{
     node *temp;
        temp = start;
        char complete[20] ="not-done";
        int i=1;
            printf("\t+-----+----------------------------------------------------------------------+------------+\n");
        printf("\t| %-3s | %-54s | %-10s |\n", "ID", "\t\tTO-DO ITEM", "STATUS");
    printf("\t+-----+----------------------------------------------------------------------+------------+\n");
        
        while (temp!=NULL)
        {
           strcpy(complete,"not-done");
            if (temp->status==1)
            {
                strcpy(complete,"Done");
            }
            
                 printf("\t| %-3d | %-68s | %-10s |\n", i, temp->data, complete);
                     

            temp =temp->next;
     
            i++;
            
        }
           printf("\t+-----+----------------------------------------------------------------------+------------+\n");
        


    }
    


}
void edit(){
     int id,counter;
    id=0,counter=1;
    char buffer[500];
    if (start==NULL)
    {
        printf("\n\t\t\tNo To-Do found\t");
    }
    
     printf("\n Enter the id. to edit item..");
     scanf("%d",&id);
         fflush(stdin);
    printf("\nEnter edited item to the list:\t");
     fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // remove the \n which is at the end of buffer and insted add NULL . So, that the status doesn't show below the to-do-iteams
     node *temp,*temp2;
     temp = start;
     while (counter!=id)
     {
        
        temp=temp->next;
        counter ++;
        
     }
     
   
    strcpy(temp->data,buffer);
    // after editing or deleting(same logic for deleting) we would rewrite whole node data inside the txt file 
    // rather searching it(i.e the file to edit or delete) inside the txt file
 
     temp2= start;
     fp = fopen("to-do.txt","w");
    if (fp==NULL)
    {
       printf("error opening");
       exit(0);
    }
    
    
        while (temp2!=NULL)
        {
            fprintf(fp,"%s|%d\n",temp2->data,temp2->status);
            temp2=temp2->next;
        }
        fclose(fp);
        
    printf("\n\t\tTo-do item updated successfully!\n");
    Sleep(1000);
     
}


void  completetodo(){
    int id=0;
    int counter=1;
    if (start==NULL)
    {
      printf("\n\t\t\tNo To-Do found\t");
    }else{
            printf("\n\t\t\t Enter the id of  done work:\t");
            scanf("%d",&id);
            node *temp,*temp2;
            temp=start;
            while (counter!=id)
            {
                temp=temp->next;
                counter++;
                
            }
            temp->status=1; // 1 for completed
            temp2= start;
     fp = fopen("to-do.txt","w");
    if (fp==NULL)
    {
       printf("error opening");
       exit(0);
    }
    
    
        while (temp2!=NULL)
        {
            fprintf(fp,"%s|%d\n",temp2->data,temp2->status);
            temp2=temp2->next;
        }
        fclose(fp);
        
    printf("\n\t\tTo-do item updated successfully!\n");
    Sleep(1000);
            printf("\nUpdated To-do sucessfully..\n");
         
              Sleep(1000);
    }
    


    
}

void deletetodo(){
    int id,counter;
    id=0,counter=1;
    if (start==NULL)
    {
        printf("\n\t\t\tNo To-Do found\t");
    }
    
     printf("\n Enter the id. to Delete item..");
     scanf("%d",&id);
     node *temp,*temp2 ,*temp3;
     temp = start;
     while (counter!=id)
     {
        temp2=temp;
        temp=temp->next;
        counter ++;
        
     }
     temp2->next=temp->next;
     free(temp);
     temp3 = start;
     fp = fopen("to-do.txt","w");
    if (fp==NULL)
    {
       printf("error opening");
       exit(0);
    }
    
    
        while (temp3!=NULL)
        {
            fprintf(fp,"%s|%d\n",temp3->data,temp3->status);
            temp3=temp3->next;
        }
        
            
    
        
    
        
    
    fclose(fp);
     printf("\nIteam deleted Sucessfully..");
     Sleep(1000);


}



void storefile(){
    fp = fopen("to-do.txt","a+");
    if (fp==NULL)
    {
       printf("error opening");
       exit(0);
    }
    
    
        
            
     fprintf(fp,"%s|%d\n",start->data,start->status);
        
    
        
    
    fclose(fp);
    
    

}

void fetchdata(){
    char buffer[500];
    int status;
        node *temp;
    temp=start;
    while (temp!=NULL)
    {
        start= temp->next;
        free(temp);
        temp=start;
    }
    
    fp = fopen("to-do.txt","r");
    if (fp==NULL)
    {
        printf("\nUnable to fetch data!!");
        exit(0);
    }

    while (fscanf(fp,"%[^|]|%d\n",buffer,&status)==2)
    {
                temp = createnode();
            strcpy(temp->data,buffer);
        temp->next = start;
        temp->status=status;
        start = temp;
        
    }
    
 fclose(fp);
    


}