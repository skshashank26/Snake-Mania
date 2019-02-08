#include<stdio.h>
#include<time.h>
#include<stdlib.h>

struct food                                                //Structure to define food item
{
 int x;
 int y;
 char value;
};

struct mine                                                 //Structure to define mine
{
 int x;
 int y;
 char value;
};

struct node                                                 //Structure to define Snake body
{
 int x;
 int y;
 char value;
 struct node *next;
 struct node *prev;
}p;

struct  node *n,*t,*h,*head,*tail;
struct food f;
struct mine po,po2,po3;
int hs=0;

struct node* insert()                                        //Functon to Create Body of Snake
{
n=malloc(sizeof(struct node));
n->x=1;
n->y=2;
n->value='A';
n->next=NULL;
n->prev=NULL;
t=n;
h=n;

n=malloc(sizeof(struct node));
n->x=1;
n->y=1;
n->value='#';
n->next=NULL;
n->prev=t;
t->next=n;
t=n;

n=malloc(sizeof(struct node));
n->x=1;
n->y=0;
n->value='Y';
n->next=NULL;
n->prev=t;
t->next=n;
t=n;
tail=t;
return h;
}

void create_food()                                        //Function to create food
{
 struct node *temp=h;
 f.x=rand()%20;
 f.y=rand()%50;
 f.value='o';
 while(temp!=NULL)
  {
    if(temp->x==f.x&&temp->y==f.y||f.x==0||f.x==19||f.y==0||f.y==49)
     {
       create_food();  
     }
     temp=temp->next;
  }
}

void create_mine()                                    //Function to create mine
{
 struct node *temp=h;
 po.x=rand()%20;
 po.y=rand()%50;
 po.value='*';

 while(temp!=NULL)
  {
    if(temp->x==po.x&&temp->y==po.y||po.x==f.x&&po.y==f.y||po.x==0||po.x==19||po.y==0||po.y==49)
     {
       create_mine();  
     }
     temp=temp->next;
  }

 if(hs>=40)
{
 po2.x=rand()%20;
 po2.y=rand()%50;
 po2.value='*';

 while(temp!=NULL)
  {
    if(temp->x==po2.x&&temp->y==po2.y||po2.x==f.x&&po2.y==f.y||po2.x==0||po2.x==19||po2.y==0||po2.y==49)
     {
       create_mine();
     }
     temp=temp->next;
  }

 po3.x=rand()%20;
 po3.y=rand()%50;
 po3.value='*';

 while(temp!=NULL)
  {
    if(temp->x==po3.x&&temp->y==po3.y||po3.x==f.x&&po3.y==f.y||po3.x==0||po3.x==19||po3.y==0||po3.y==49)
     {
       create_mine();
     }
     temp=temp->next;
  }
}
}

struct node *eat_food()                                    //Function to Eat Food
{
 hs+=1;
 static int i=20;
 char ch;
if(hs>=i)
{
i+=20;
system("clear");
printf("\nYOU ADVANCED TO NEXT LEVEL PRESS C TO CONTINUE\n");
scanf("   %c",&ch);
create_mine();
}
 n=malloc(sizeof(struct node));
 n->next=head->next;
 n->prev=head;
 head->next=n;
 n->next->prev=n;
 struct node *temp=head->next;

 while(temp->next!=NULL)
  {
   temp->x=temp->next->x;
   temp->y=temp->next->y;
   temp->value='#';
   temp=temp->next;
  }

 if(temp->x==temp->prev->prev->x&&temp->y<temp->prev->prev->y)
  {
   temp->y=temp->y-1;
  }
 else if(temp->x==temp->prev->prev->x&&temp->y > temp->prev->prev->y)
  {
   temp->y=temp->y+1;
  }
 else if(temp->y==temp->prev->prev->y&&temp->x > temp->prev->prev->x)
  {
   temp->x=temp->x+1; 
  }
 else
  {
    temp->x=temp->x-1;
  }
 create_food();
 return head;
}

struct node *eat_mine()                                 //Function to Eat mine
{
   printf("Game Over\nYour score:%d\n",hs);
   exit(0);
}


void display(char mat[] [50])                            //Function to Disply Game board
{
 system("clear");
 int i,j;
 mat[f.x][f.y]=f.value;
 mat[po.x][po.y]=po.value;
 if(hs>4)
{
 mat[po2.x][po2.y]=po2.value;
 mat[po3.x][po3.y]=po3.value;
}
 struct node *temp=head;
  while(temp!=NULL)
   {
    mat[temp->x][temp->y]=temp->value;
    temp=temp->next;
   }
   for(i=0;i<20;i++)
    {
     for(j=0;j<50;j++)
      {
       printf("%c",mat[i][j]);
      }
       printf("\n");
    }

 for(i=0;i<20;i++)
  {
   for(j=0;j<50;j++)
    {
      if(i==0||j==0||i==19||j==49)
       {
         mat[i][j]='.';
       }
      else
       {
        mat[i][j]=' ';
       }
    }
  }
 printf("\nHigh score:%d\n",hs);
}

struct node *move(char dir)          //Function to move snake on board
{
  char opt;
  struct node *temp=tail;
  struct node *temp2=head;
  struct node *tr;
  if(dir=='q')
  {
     printf("You quit your game\n");
     printf("Your high score:%d\n",hs);
     exit(0);    
  }

  if(dir=='d')
  {
     if(head->y+1!=head->next->y)
     {
        while(temp->prev!=NULL)
         {
          temp->x=temp->prev->x;
          temp->y=temp->prev->y;
          temp=temp->prev;
         }
         temp->y=temp->y+1;
     }
   if(temp->x==f.x && temp->y==f.y)
    {
      head=eat_food();
    }
   if(temp->x==po.x && temp->y==po.y)
    {
      eat_mine();
    }
   if(temp->x==po2.x && temp->y==po2.y)
    {
      eat_mine();
    }
   if(temp->x==po3.x && temp->y==po3.y)
    {
      eat_mine();
    }
tr=temp;
tr=tr->next;
    while(tr!=NULL)
     {
      if(temp->x==tr->x&&temp->y==tr->y)
       {
        printf("Game over Your score:%d\n",hs);
        exit(0); 
       }
      tr=tr->next;
     }
  }

 if(dir=='a')
   {
      if(head->x!=head->next->x||h->y-1!=h->next->y)
       {
         while(temp->prev!=NULL)
           {
             temp->x=temp->prev->x;
             temp->y=temp->prev->y;
             temp=temp->prev;
           }
           temp->y=temp->y-1;
       }
  if(temp->x==f.x && temp->y==f.y)
    {
      head=eat_food();
    }
   if(temp->x==po.x && temp->y==po.y)
    {
      eat_mine();
    }
  if(temp->x==po2.x && temp->y==po2.y)
    {
      eat_mine();
    }
   if(temp->x==po3.x && temp->y==po3.y)
    {
      eat_mine();
    }
tr=temp;
tr=tr->next;
        while(tr!=NULL)
     {
      if(temp->x==tr->x&&temp->y==tr->y)
       {
        printf("Game over Your score:%d\n",hs);
        exit(0); 
       }
      tr=tr->next;
     }
   }

   if(dir=='w')
    {
    if(head->x-1!=head->next->x)
       {
        while(temp->prev!=NULL)
         {
          temp->x=temp->prev->x;
          temp->y=temp->prev->y;
          temp=temp->prev;
         }
         temp->x=temp->x-1;
       }
  if(temp->x==f.x && temp->y==f.y)
   {
     head=eat_food();
   }
   if(temp->x==po.x && temp->y==po.y)
    {
      eat_mine();
    }
  if(temp->x==po2.x && temp->y==po2.y)
    {
      eat_mine();
    }
   if(temp->x==po3.x && temp->y==po3.y)
    {
      eat_mine();
    }
tr=temp;
tr=tr->next;
        while(tr!=NULL)
     {
      if(temp->x==tr->x&&temp->y==tr->y)
       {
        printf("Game over Your score:%d\n",hs);
        exit(0); 
       }
      tr=tr->next;
     }
  }

  if(dir=='s')
   {
      if(head->x+1!=head->next->x)
       {
         while(temp->prev!=NULL)
         {
           temp->x=temp->prev->x;
           temp->y=temp->prev->y;
           temp=temp->prev;
         }
           temp->x=temp->x+1;
       }
     if(temp->x==f.x && temp->y==f.y)
      {
        head=eat_food();
      }
   if(temp->x==po.x && temp->y==po.y)
    {
      tail=eat_mine();
    }
  if(temp->x==po2.x && temp->y==po2.y)
    {
      eat_mine();
    }
   if(temp->x==po3.x && temp->y==po3.y)
    {
      eat_mine();
    }
tr=temp;
tr=tr->next;
        while(tr!=NULL)
     {
      if(temp->x==tr->x&&temp->y==tr->y)
       {
        printf("Game over Your score:%d\n",hs);
        exit(0); 
       }
      tr=tr->next;
     }
   }

return head;
}

void create_game_board(char mat[] [50])       //Function to create game board
{
 int i,j;
 for(i=0;i<20;i++)
  {
   for(j=0;j<50;j++)
    {
      if(i==0||j==0||i==19||j==49)
       {
         mat[i][j]='.';
       }
      else
       {
        mat[i][j]=' ';
       }
    }
  }
}

int main() //Driver Function
{
 char i;
 printf("N to start new, Press q to quit\n");
 scanf(" %c",&i);
 create_food();                                     //Function call to create_food()
 char mat[20][50];
 create_game_board(mat);
 head=insert();                                     //function call to  insert()
 display(mat);                                     //function call to display()
 char dir;
 while(scanf("%c",&dir)==1)
  {
   head=move(dir);                                //function to call move()
   display(mat);                                 //function call to display()
  }
 return 0;
}
