/*Program to demonstrate simulation of reference parameters in C
  using three levels of procedure calls
  Written by Ron
  March 2004
  Language: C (gcc target)
*/

#include <stdio.h>

/*Function prototypes*/
void snidley (int *dudley, int *nell);
void green_acres (int *fred, int *arnold);

int main(void)
{
  int rocky, bw, boris;
  rocky=3;
  bw=4;
  boris=rocky+bw;
  snidley(&rocky, &boris);
  printf("After call on snidley rocky is %d, bw is %d, boris is %d\n", rocky, bw, boris);
  return 0;
}

void snidley (int *dudley, int *nell)
/*Function to demonstrate reference parameters
  Written by Ron
  March 2004
  Language: C (gcc target)

  Precondition:  actual arguments passed in are not altered
  Postcondition: actual arguments passed in are altered

*/

{  int oscar;
   oscar=(*dudley) * (*nell);  /*parens are for clarity*/
   *dudley=oscar+2;            /*note use of *  */
   *nell=*dudley-1;
   printf ("oscar is %d, dudley is %d, nell is %d\n", oscar, *dudley, *nell);
   green_acres(nell, &oscar);  /*note that nell is passed
                                 without & because it is already
                                 a pointer*/
   printf ("oscar is %d, dudley is %d, nell is %d\n", oscar, *dudley, *nell);
   return;
}

void green_acres(int *fred, int *arnold)
/*Third level function
  Written by Ron
  March 2004
  Language: C (gcc target)

  Precondition:  values of fred and arnold are unchanged from
                 calling environment
  Postconditon:  values of fred and arnold are changed in calling
                 environment

*/

{
  int haney;
  haney=(*fred)+((*arnold)*2); /*parens not required, provided for clarity*/
  *fred=haney+3;
  *arnold=*fred+haney;
  printf("fred is %d, arnold is %d, haney is %d\n",*fred,*arnold,haney);
  return;
}
