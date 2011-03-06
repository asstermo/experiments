// C Source File
// Created 2005-08-18; 18:46:45

// Delete or comment out the items you do not need.
//#define COMMENT_STRING         "Place your comment here."
//#define COMMENT_PROGRAM_NAME   "Place your program name here."
//#define COMMENT_VERSION_STRING "Place your version string here."
//#define COMMENT_VERSION_NUMBER 0,1,0,0 /* major, minor, revision, subrevision */
//#define COMMENT_AUTHORS        "BMSS"

#define RETURN_VALUE tares

#define USE_TI89
#define ENABLE_ERROR_RETURN   // Enable Returning Errors to TIOS

//#define USE_TI92PLUS
//#define USE_V200
//#define SAVE_SCREEN

#define MIN_AMS 200

#include <all.h>

float matval(const char * tabela, short i, short j)
{
	const char tabela2[30], string1[5];
  static float d;
	strcpy(tabela2,tabela);
	strcat(tabela2,"[");
	sprintf (string1, "%d", i);
	strcat(tabela2,string1);
	strcat(tabela2,",");
	sprintf (string1, "%d", j);
	strcat(tabela2,string1);
	strcat(tabela2,"]");

  CESI tab2cesid;
  push_END_TAG();
	push_zstr (tabela2);
	tab2cesid = top_estack;

	TRY
	push_str_to_expr (tab2cesid);
  tab2cesid = top_estack;
  d = estack_number_to_Float (tab2cesid);
  while (GetArgType (top_estack) != END_TAG)  // Clean up arguments
    top_estack = next_expression_index (top_estack);
  top_estack--;
  FINALLY
  ENDFINAL

	return d;
}

void _main(void)
{
	//get arguments
  ESI argptr = top_estack;
  short a = GetIntArg (argptr);
//  clrscr();
//  printf("%d\n",a);
  short b = GetIntArg (argptr);
//  printf("%d\n",b);
	const char *tabela;
	const char tabela2[10];
	tabela = GetStrnArg (argptr);
//  printf("%s\n",tabela);
//  ngetchx();
	strcpy(tabela2,tabela);
  while (GetArgType (top_estack) != END_TAG)  // Clean up arguments
    top_estack = next_expression_index (top_estack);
  top_estack--;

	
	float d;
	d=matval(tabela2, a, b);

  push_END_TAG();
	push_Float(d);
//	push_zstr (tabela2);
//  push_LIST_TAG();
}