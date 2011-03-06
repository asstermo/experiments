// C Source File
// Created 2005-08-30; 01:37:45

#define RETURN_VALUE testar

#include <tigcclib.h>

float matval(FILE *f, short i, short j, short jmax, short fsz, const BOOL transpose)
{
  static float d;
  static short fpos, ii, jj;
  static char buffer[10];

	if (transpose)
	{ii=j;jj=i;}
	else
	{ii=i;jj=j;}

	fpos = fsz - (2 + (jmax * 10 + 2) * (ii-1) + jj * 10);
	fseek (f, fpos, SEEK_SET);
	fread(buffer,1,10,f);

	d = estack_number_to_Float (buffer+9);

	return d;
}


short *GetIntListArg (ESI *argptr, short *numlist)
{
	short *int_list, mylist[20], i, szi;
	
	memset (mylist, (short) NULL, sizeof(mylist));
	int_list=NULL;
	*numlist=(short) NULL;

	if (GetArgType(*argptr) == LIST_TAG)	
	{
		(*argptr)--;
		for (i=0;i<20;i++)
		{
			if ( GetArgType (*argptr) != END_TAG)
			{
				if (GetArgType (*argptr) == POSINT_TAG)
				{
					(*argptr)--;
					szi=(BYTE) **argptr;
					(*argptr)-=szi;
					mylist[i]=(BYTE) **argptr;
					(*numlist)++;
				}
			}
			else
				break;
			(*argptr)--;
		}
		(*argptr)--;

		if (*numlist>0)
		{
			int_list=calloc(*numlist, sizeof(short));
			memcpy(int_list,mylist,sizeof(short) * (*numlist));
		}
	}

	return int_list;
}

// Main Function
void _main(void)
{

  ESI argptr;
  FILE *f;
  short i,j,jmax, fsz, transpose;
	const char *tabela;
  
	argptr = top_estack;
	i = GetIntArg (argptr);
	j = GetIntArg (argptr);
	tabela = GetStrnArg (argptr);
	fsz = GetIntArg (argptr);
	jmax = GetIntArg (argptr);
	transpose = GetIntArg (argptr);

  while (GetArgType (top_estack) != END_TAG)  // Clean up arguments
    top_estack = next_expression_index (top_estack);
  top_estack--;
  
  push_END_TAG();

	f = fopen (tabela, "rb");
	if (f!=NULL)
	{
		push_Float (matval(f, i, j, jmax, fsz, transpose));
		fclose(f);
	}
  
  push_LIST_TAG();
  
	return;
}
