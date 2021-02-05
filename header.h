/* include all libraries here */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* put any #define statements here */

typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;
//-----------------------------------------------------------------
// linked list
typedef struct linkedList
{
 int numBurger;
 int numSalad;
 char* orderName;
 
 int inRest; // compares 1 and 0s or true and falses

 struct linkedList*  next;


}stackList;

typedef struct linkedList linked;
typedef linked* linkedPtr; 
//-----------------------------------------------------------------
int isEmpty (stackList* hd)
{
 if (hd == NULL)
   return TRUE;
 else
   return FALSE;
}
//----------------------------------------------------------------
linkedPtr top (linkedPtr hd)
{
  // how to reference the top of the stack coordinates
  // top(hd) -> xpos
  // top(hd) -> ypos
 return (hd);
}
//------------------------------------------------

// queue
struct queue
{
  int count;
  struct linkedList* front;
  struct linkedList* rear;
};
typedef struct queue queue;

//----------------------------------------------------------------
void initialize(queue *q)
{
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}
//---------------------------------------------------------------
int isempty(queue *q)
{
    return (q->rear == NULL);
}

//----------------------------------------------------------------




//------------------------------------------------------------------
/* forward definition of functions */
void clearToEoln();

/* Read in until the first Non-White-Space character is Read */
/* The white space characters are:
 *      space, tab \t, newline \n, vertical tab \v, 
 *      form feed \f, and carriage return \r
 */ 
int getNextNWSChar ()
{
 int ch;

 ch = getc(stdin);
 if (ch == EOF || ch == '\n')
   return ch;
 while (isspace (ch))
   {
    ch = getc(stdin);
    if (ch == EOF || ch == '\n')
      return ch;
   }
 return ch;
}
//--------------------------------------------------------------------
/* read in the next Positive Integer or error:    */
/*    we can count zero as a positive number */ 
int getPosInt ()
{
 int value = -1;

 /* clear white space characters */
 int ch;
 ch = getc(stdin);
 while (!isdigit(ch))
   {
    if ('\n' == ch)  /* error \n ==> no integer given */
       return -1;
    if (!isspace(ch)) /* error non white space ==> integer not given next */
      {
       clearToEoln();
       return -1;
      }
    ch = getc(stdin);
   }

 value = ch - '0';
 ch = getc(stdin);
 while (isdigit(ch))
   {
    value = value * 10 + ch - '0';
    ch = getc(stdin);
   }

 ungetc (ch, stdin);  /* put the last read character back in input stream */

 /* Integer value less than 0 is an error in this program */
 if (0 > value)
    clearToEoln();
   
 return value;
}
//--------------------------------------------------------------------
/* read in the name until the end of the input */
char *getName()
{
 /* skip over the white space characters */
 int ch;
 ch = getc(stdin);
 while (isspace(ch))
   {
    if ('\n' == ch)  /* error \n ==> no integer given */
       return NULL;
    ch = getc(stdin);
   }

 char *word;
 int size;
 size = 10;
 word = (char *) malloc (sizeof(char) * size);
  
 // read in character-by-character until the newline is encountered
 int count = 0;

 while (ch != '\n')
   {
    if (count+1 >= size)
      {
       // to grow an array to make it "dynamically sized" using malloc
       char* temp;
       int i;
       size = size * 2;
       temp = (char *) malloc (sizeof(char) * size);
    
       // copy the characters to the new array
       for (i = 0 ; i < count ; i++)
           temp[i] = word[i];

       free (word);
       word = temp;
      }

    word[count] = ch;
    count++;
    word[count] = '\0';

    // read next character
    ch = getc(stdin);
   }

 if (count > 30)
   {
    count = 30;
    word[count] = '\0';
   }
 
 /* clear ending white space characters */
 while (isspace (word[count-1]))
   {
    count--;
    word[count] = '\0';
   }

 return word;
}
//---------------------------------------------------------------------
/* Clear input until next End of Line Character - \n */
void clearToEoln()
{
 int ch;
 
 do {
     ch = getc(stdin);
    }
 while ((ch != '\n') && (ch != EOF));
}
//-------------------------------------------------------------------------
/* Print out a list of the commands for this program */
void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("a <# burgers> <# salads> <name> - to add your order to the order list\n");
 printf ("c <# burgers> <# salads> <name> - to add a call-ahead order to the order list\n");
 printf ("w <name> - to specify a call-ahead group is now waiting in the restaurant\n");
 printf ("r <# burgers> <# salads> - to retrieve the first waiting group whose order matches the items on the counter\n");
 printf ("l <name> - list how many orders are ahead of the named order\n");
 printf ("d - display the order list information\n");
 printf ("t <name> - display an estimated wait time for the given order name\n");
       
 /* clear input to End of Line */
 clearToEoln();
}
//----------------------------------------------------------------------
void doAdd (queue** theQueue)
{
 /* get number of burgers ordered from input */
 int NumBurgers = getPosInt();
 if (NumBurgers < 0)
   {
    printf ("Error: Add command requires an integer value of at least 0\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

  /* get number of salads ordered from input */
 int NumSalads = getPosInt(); 
 if (NumSalads < 0)
   {
    printf ("Error: Add command requires an integer value of at least 0\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }  

 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Add command requires a name to be given\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }
 // add code to perform this operation here

 // add linked List to queue
  //stackList* ptr = (stackList*) malloc (sizeof(stackList));
  
  struct linkedList *ptr;
  ptr = malloc(sizeof(struct linkedList));

  ptr->orderName = name;
  ptr->numBurger = NumBurgers;
  ptr->numSalad = NumSalads;
  ptr->inRest = 1; // is true
  ptr->next = NULL;

  if(!isempty(*theQueue))
  {
    // point the end node of linked list to the 
    // top of queue (first in first out)
    // check for duplicate names
    struct linkedList* tmp;
    tmp = (*theQueue)->front;
    int numCustomers = 0;
    int result;

    while (tmp != NULL){
      result = strcmp(name, tmp->orderName);

      if (result == 0){
        printf("Error name already exist***\n");
        break;
      }
      tmp = tmp->next;
      numCustomers++;
    }// end of while loop
    //printf("%d == %d\n", numCustomers, ((*theQueue)->count)-1);
    if (numCustomers == ((*theQueue)->count)-1){
      // name doesnt exist 
      // add new name to linked list
      printf ("Adding In-restaurant order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);  
      (*theQueue)->rear->next = ptr; 
      (*theQueue)->rear = ptr;
    }
  }
  else // queue is empty
  {
    // point front node of linked list to the new 
    // pointer that the end node is pointing to
     printf ("Adding In-restaurant order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);
    (*theQueue)->rear = ptr;
    (*theQueue)->front = (*theQueue)->rear;
  }
  (*theQueue)->count++; // increment size of queue
}

//------------------------------------------------------------------------
void doCallAhead (queue** theQueue)
{
   /* get number of burgers ordered from input */
 int NumBurgers = getPosInt();
 if (NumBurgers < 0)
   {
    printf ("Error: Call-ahead command requires an integer value of at least 0\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

  /* get number of salads ordered from input */
 int NumSalads = getPosInt(); 
 if (NumSalads < 0)
   {
    printf ("Error: Call-ahead command requires an integer value of at least 0\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }  


 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Call-ahead command requires a name to be given\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }


 // add code to perform this operation here


  struct linkedList *ptr;
  ptr = malloc(sizeof(struct linkedList));

  ptr->orderName = name;
  ptr->numBurger = NumBurgers;
  ptr->numSalad = NumSalads;
  ptr->inRest = 0; // is false
  ptr->next = NULL;

  if(!isempty(*theQueue))
  {
    // point the end node of linked list to the 
    // top of queue (first in first out)
    // check for duplicate names
    struct linkedList* tmp;
    tmp = (*theQueue)->front;
    int numCustomers = 0;
    int result;

    while (tmp != NULL){
      result = strcmp(name, tmp->orderName);

      if (result == 0){
        printf("Error name already exist***\n");
        break;
      }
      tmp = tmp->next;
      numCustomers++;
    }// end of while loop
    //printf("%d == %d\n", numCustomers, ((*theQueue)->count)-1);
    if (numCustomers == ((*theQueue)->count)-1){
      // name doesnt exist 
      // add new name to linked list
      printf ("Adding Call-ahead order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);
      (*theQueue)->rear->next = ptr; 
      (*theQueue)->rear = ptr;
    }
  }
  else
  {
    // point front node of linked list to the new 
    // pointer that the end node is pointing to
    printf ("Adding Call-ahead order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);
    (*theQueue)->rear = ptr;
    (*theQueue)->front = (*theQueue)->rear;
  }
  (*theQueue)->count++; // increment size of queue
}
//--------------------------------------------------------------------
void doWaiting (queue** theQueue)
{
 /* get order name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Waiting command requires a name to be given\n");
    printf ("Waiting command is of form: w <name>\n");
    printf ("  where: <name> is the name of the group that is now waiting\n");
    return;
   }

 printf ("Call-ahead order \"%s\" is now waiting in the restaurant\n", name);

 // add code to perform this operation here

 struct linkedList* tmp;
 tmp = (*theQueue)->front;

 int result;
 int numCustomers = 0;

 while (tmp != NULL){
   //printf("name is %s burgers %d salads %d\n", tmp->orderName, tmp->numBurger, tmp->numSalad);
   result = strcmp(name, tmp->orderName);
   //printf("%s == %s\n", name, tmp->orderName);
   if (result == 0){
     //printf("%s is now in restaruant\n", tmp->orderName);
     tmp->inRest = 1; // is true
     break;
   }
   tmp = tmp->next;
   numCustomers = numCustomers + 1;

   if (numCustomers == ((*theQueue)->count)-1){
     printf("Name not found*** \n");
   }
 }

}
//------------------------------------------------------------------
void doRetrieve (queue** theQueue)
{
 /* get info of prepared food ready on the counter from input */
 int PreparedBurgers = getPosInt();
 if (PreparedBurgers < 0)
   {
    printf ("Error: Retrieve command requires an integer value of at least 0\n");
    printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
    printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
    printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
    return;
   }

 int PreparedSalads = getPosInt();
 if (PreparedSalads < 0)
   {
    printf ("Error: Retrieve command requires an integer value of at least 0\n");
    printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
    printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
    printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
    return;
   }   

 clearToEoln();
 printf ("Retrieve (and remove) the first group that can pick up the order of %d burgers and %d salads\n", PreparedBurgers ,PreparedSalads);

 // add code to perform this operation here

  linkedPtr tmp = (*theQueue)->front;
  linkedPtr parent = tmp;

  int numCustomers = 0;

  while (tmp != NULL) {
    int frontSalad = tmp->numSalad;
    int frontBurger = tmp->numBurger;
    
    if (tmp->inRest == 1){
      
      if (PreparedBurgers >= frontBurger && PreparedSalads >= frontSalad){
        
        if (PreparedBurgers != 0){
          PreparedBurgers = PreparedBurgers - frontBurger;
        }
        if (PreparedSalads != 0){
          PreparedSalads = PreparedSalads - frontSalad;
        }

        (*theQueue)->front = (*theQueue)->front->next;
        
        parent = tmp;
        (*theQueue)->count--;
        free(tmp);

        if (tmp == (*theQueue)->rear){
          break;
        }
      }
    }
    if (PreparedBurgers == 0 && PreparedSalads == 0){
      break;
    }

    tmp = tmp->next;
    numCustomers = numCustomers + 1;

    if (numCustomers == ((*theQueue)->count)-1){
      printf("Name not found*** \n");
    }


  }


  //return(n);
}
//--------------------------------------------------------------
void doList (queue* theQueue)
{
 /* get order name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: l <name>\n");
    printf ("  where: <name> is the name of the order to inquire about\n");
    return;
   }

 printf ("Order for \"%s\" is behind the following orders\n", name);

 // add code to perform this operation here
 struct linkedList* tmp;
 tmp = theQueue->front;
 int numCustomers = 0;
 int result;

 while (tmp != NULL){
   result = strcmp(name, tmp->orderName);
   if (result == 0){
     printf("There are %d customers ahead\n", numCustomers);
     break;
   }

   numCustomers = numCustomers + 1;
   tmp = tmp->next;
 //printf("%d == %d\n", numCustomers, (theQueue->count)-1);
   if (numCustomers == (theQueue->count)-1){
     printf("Name not found*** \n");
   }
 }

}
//----------------------------------------------------------------
void doDisplay (queue* theQueue)
{
 clearToEoln();
 printf ("Display information about all orders\n");
 int orderNum = 1;
 struct linkedList* tmp;
 tmp = theQueue->front;

 while (tmp != NULL){
   printf("Order # %d.) %s: # burgers %d, # salads %d\n", orderNum, tmp->orderName, tmp->numBurger, tmp->numSalad);
   
   tmp = tmp->next;
   orderNum++;
 }
 // add code to perform this operation here
}

//-------------------------------------------------------------------------
void doEstimateTime(queue* theQueue)
{
  /* get order name from input */
 
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: t <name>\n");
    printf ("  where: <name> is the name of the order to inquire about\n");
    return;
   }


  // add code to perform this operation here  

 struct linkedList* tmp;
 tmp = theQueue->front;
 int numCustomers = 0;

 int total = 0;

 int result;

 while (tmp != NULL){
   result = strcmp(name, tmp->orderName);
   int timeBurger = 10;
   int timeSalad = 5; 

   if (result == 0){
     timeBurger = timeBurger * tmp->numBurger;
     timeSalad = timeSalad * tmp->numSalad;
     total = total + timeBurger + timeSalad;
     //printf("There are %d customers ahead\n", numCustomers);
     printf("The wait is about %d minutes\n", total);
     break;
   }

   //numCustomers = numCustomers + 1;
   //printf("burgers %d\n", tmp->numBurger);
   //printf("salad %d\n", tmp->numSalad);
   timeBurger = timeBurger * tmp->numBurger;
   timeSalad = timeSalad * tmp->numSalad;

   tmp = tmp->next;
   if (numCustomers == (theQueue->count)-1){
     printf("Name not found*** \n");
   }

   total = total + timeBurger + timeSalad;
 }

}
