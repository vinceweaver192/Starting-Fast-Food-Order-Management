#include "header.h"

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
