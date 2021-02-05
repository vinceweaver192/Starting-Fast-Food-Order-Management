#include "header.h"

int main (int argc, char **argv)
{
 queue* theQueue;
 char *input;
 int ch;

 printf ("Starting Fast Food Order Management Program\n\n");
 printf ("Enter command: ");

 while ((ch = getNextNWSChar ()) != EOF)
   {
    /* check for the various commands */
    if ('q' == ch)
      {
       printf ("Quitting Program\n");
       return (0);
      }
    else if ('?' == ch)
      {
       printCommands();
      }
    else if('a' == ch)
      {
       doAdd(&theQueue);
      } 
    else if('c' == ch)
      {
       doCallAhead(&theQueue);
      } 
    else if('w' == ch)
      {
       doWaiting(&theQueue);
      } 
    else if('r' == ch)
      {
       doRetrieve(&theQueue);
      } 
    else if('l' == ch)
      {
       doList(theQueue);
      } 
    else if('d' == ch)
      {
       doDisplay(theQueue);
      } 

    else if('t' == ch)
      {
      	doEstimateTime(theQueue);
      }	
      
    else if('\n' == ch)
      {
       /* nothing entered on input line     *
        * do nothing, but don't give error  */
      } 
    else
      {
       printf ("%c - in not a valid command\n", ch);
       printf ("For a list of valid commands, type ?\n");
       clearToEoln();
      }

    printf ("\nEnter command: ");
   }

 printf ("Quiting Program - EOF reached\n");
 return 1;
}