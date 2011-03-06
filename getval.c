
#define RETURN_VALUE gotval
#define OPTIMIZE_ROM_CALLS

#define USE_TI89
#define ENABLE_ERROR_RETURN   // Enable Returning Errors to TIOS

#define USE_TI92PLUS
#define USE_V200
//#define SAVE_SCREEN

#define MIN_AMS 101 //200

#include <tigcclib.h>

float matval(const char * tabela, short i, short j, short jmax, short fsz)
{
  static float d;
  FILE *f;
  static short fpos;
  static char buffer[10];
  //short i2,j2;
  
	TRY
		f = fopen (tabela, "rb");
		if (f!=NULL)
		{
			//for (i2=1;i2<10;i2++)
			//for (j2=1;j2<10;j2++)
			//{

			fpos = fsz - (2 + (jmax * 10 + 2) * (i-1) + j * 10);
			fseek (f, fpos, SEEK_SET);
			fread(buffer,1,10,f);

			d = estack_number_to_Float (buffer+9);
			//}
			//printf("%f\n",d);
			//ngetchx();
			fclose(f);

		}
  FINALLY
  ENDFINAL

	return d;
}

// Main Function
void _main(void)
{
  ESI argptr;
  short i,j,jmax,fsz;
	const char *tabela;
	static char tabela2[10];
	float val;

	//clrscr();
  //ngetchx();

	//get arguments
	argptr = top_estack;
	i = GetIntArg (argptr);
	j = GetIntArg (argptr);
	jmax = GetIntArg (argptr);
	fsz = GetIntArg (argptr);
	tabela = GetStrnArg (argptr);
	strcpy(tabela2,tabela);
  while (GetArgType (top_estack) != END_TAG)  // Clean up arguments
    top_estack = next_expression_index (top_estack);
  top_estack--;

	val=matval(tabela2, i, j, jmax, fsz);
	
	push_Float(val);

	return;
}
