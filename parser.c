#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX 70

int size=0;  //'size' gives the number of tokens present in the input string.
             // Its value, naturally, is 0 initially



//////////////////////////////////////////////// FUNCTION PROTOTYPES /////////////////////////////////////////////////////////////////

/* The various functions used are categorized and only a brief description of their utility is mentioned here.
   Details are provided for each of them immediately preceeding their definition.
*/


//background methods that perform tasks which must actually be performed by the Lexical Analyzer
int scanner(char token[MAX]);
int tokenSpecifier(char token[MAX]);
char** tokenizer(char stmnt[MAX],int *size);


//the various recursive descent parser methods as described in our textbook
bool EXP(char** tokens,int *ptr);
bool TERM(char** tokens,int *ptr);
bool FACTOR(char** tokens,int *ptr);
bool ASSIGN(char** tokens,int *ptr);
bool IDLIST(char** tokens,int *ptr);
bool READ(char** tokens,int *ptr);


//test methods to check the functionality of the recursive descent parser
bool checkParser(char **tokens, int a);
char* getSyntaxType(int a);


////////////////////////////////////////////////////////////////// MAIN() /////////////////////////////////////////////////////////////

void main()
{
     char stmnt[100];
     char** tokens; 
     int index=0;   
 
     //get input...
     printf("Enter statement: ");
     gets(stmnt);
 
     //tokenize the input string...
     tokens= tokenizer(stmnt,&index);
     size=index;   

     //parse it and display its type 
     for(int a=0; a<6; a++)
         if(checkParser(tokens,a))
            printf("\n%s:\ttrue\n",getSyntaxType(a));
         else
            printf("\n%s:\tfalse\n",getSyntaxType(a));

} // end of main()


//////////////////////////////////////////////////////////////// FUNCTIONS ////////////////////////////////////////////////////////////////



/* Pre:      input statement (char[]) and a variable to store size (int *).
   Function: tokenizes the input statement
   Post:     returns a sequence (char **) of tokens parsed from the input statement
*/
 
char** tokenizer(char stmnt[MAX],int *size)
{
  char** tokens = (char **) calloc(20, sizeof(char*));
  
  int i=0;
  for(;i<20;i++)
     tokens[i]= (char *)calloc(MAX, sizeof(char));

   int index=0;
 
  i=0;
 
 while(stmnt[i]==' ' || stmnt[i]=='\t' || (int)stmnt[i]==0)
    {
     i++;
    }

 while(i<strlen(stmnt))
  { 
    int k=0;
    int oldStatus=-1,newStatus=-1,underFlag=0,moveon=1; 
   while(stmnt[i]!=' ' && stmnt[i]!='\t' && (int)stmnt[i]!=0)
    {
    
     tokens[index][k]=stmnt[i];  
     i++;
     k++;  
     
     tokens[index][k]=0;
     
     if(newStatus==-1)
       {
         oldStatus=newStatus=scanner(tokens[index]);
       }
     else
       { 
        oldStatus= newStatus;
        newStatus= scanner(tokens[index]);
  
       }

     if(newStatus==0)
       {
        int exitFlag=0;    
        
          if(oldStatus==23)       
             {
                if((stmnt[i-1]<='Z' && stmnt[i-1]>='A')||stmnt[i-1]=='_') 
                   {
                      exitFlag=1;
                   }
             }
          if(strlen(tokens[index])==1)
             {
               exitFlag=1;
             }
       
          if(exitFlag)
             {
                printf("\nError\n");
                exit(0); 
             } 
         
              
       } 
     
    if(underFlag)
         underFlag++;
         
     if(newStatus!=oldStatus)
          {
           
             if((((stmnt[i-1]=='_') && (oldStatus==22) && (stmnt[i]<='Z' && stmnt[i]>='A'))) && !underFlag)  
              {
                 moveon=0;
                 underFlag=1; 
              }
         
              
              if(underFlag>2)    
                  {
                    moveon=1;  
                  }

             if(moveon)   
              {
               tokens[index][k-1]=0;
               i--;
               break;
              }               
          }
     else
        {
            if(newStatus==13 && stmnt[i]=='=') 
             {
              
                tokens[index][1]='=';
                tokens[index][2]=0;
                k++;
                i++;  
                break;
             } 
        } 
       
    }
   
   tokens[index][k]=0;

   while((stmnt[i]==' ' || stmnt[i]=='\t') &&  (int)stmnt[i]!=0)
    {
      i++;
    }
     index++;
  }
  
 
 *size= index;
 return tokens;
     
}



/* The following applies to the next two functions.

   Pre:      token (char[])
   Function: identify the type of the token
   Post:     token code (int)
*/

int scanner(char token[MAX])
{

    int errorFlagId=0,LastCharIsUnderscore=0,errorFlagNum=0;
    int errorFlagAs=1,errorFlagSym=1; 
 

    int i=1;

    if(token[0]<='Z' && token[0]>='A')
    {
       while(i<strlen(token))
       {        
            if(!((token[i]<='Z' && token[i]>='A')|| (token[i]<='9' && token[i]>='0') || token[i]=='_'))
            { 
              errorFlagId=1;
              break;
            } 
            
            LastCharIsUnderscore=token[i]=='_'? 1 : 0 ;   
            i++;
       }

       if(!errorFlagId)
          errorFlagId=LastCharIsUnderscore==1 ? 1 : 0 ; 
    }
    
    else
        errorFlagId=1;
  
    if(!errorFlagId)
       return 22; 

    i=1;
    if(token[0]<='9' && token[0]>='0')
    {
       while(i<strlen(token))
       {
            if(!(token[i]<='9' && token[i]>='0'))
            {
               errorFlagNum=1;
               break;
            }
            
            i++;
       }
    }
    else
    {
        errorFlagNum=1;
    }    

    if(!errorFlagNum)
       return 23; 

    if(strlen(token)==2)
    {
       if((token[0]==':' && token[1]== '='))
       {
          errorFlagAs=0;
       }
    } 
 
    if(!errorFlagAs)
       return 15;

 
    if(strlen(token)==1)
    {
       if((token[0]==';' || token[0]== ',' || token[0]=='+' || token[0]=='*' || token[0]==')' || token[0]=='(' || token[0]==':' || token[0]=='-'))
       {
          errorFlagSym=0;
       }
    
      if(!errorFlagSym )
      {
         switch(token[0])
         {
             case ';': return 12;
             
             case ',': return 14;
             
             case '+': return 16;
             
             case '*': return 18;
             
             case '(': return 20;
             
             case ')': return 21;
             
             case ':': return 13;
             
             case '-': return 17;

         }
      }
    }
  
    return 0;   
} 


int tokenSpecifier(char token[MAX])
{
	 int returnVal=scanner(token); 
	  
	   if(returnVal==22)
		{
		    
		   if(!strcmp(token,"PROGRAM"))
		     return 1;
		   else if(!strcmp(token,"VAR"))
		     return 2;
		   else if(!strcmp(token,"BEGIN"))
		     return 3;
		   else if(!strcmp(token,"END"))
		     return 4;
		   else if(!strcmp(token,"INTEGER"))
		     return 6;
		   else if(!strcmp(token,"FOR"))
		     return 7;
		   else if(!strcmp(token,"READ"))
		     return 8;
		   else if(!strcmp(token,"WRITE"))
		     return 9;
		   else if(!strcmp(token,"TO"))
		     return 10;
		   else if(!strcmp(token,"DO"))
		     return 11;
		   else if(!strcmp(token,"DIV"))
		     return 19;
		
		   else
		     return 22; 
		} 

	  return returnVal;
}





//The following is a general description for all the recursive descent parser methods defined here.

/* Pre:      **tokens      =  input statement (parsed as a sequence of tokens)  
             currentToken  =  an integer pointer that points to the index of the current token being scanned. It initially points to 0.
                                
   Function: evident by the name of the method
   
   Post:     depending on the type of the input statement the appropriate methods returns true
             others return false
*/

///////////////////////////////////////////////// RECURSIVE DESCENT PARSER METHODS /////////////////////////////////////////////////////////

bool ASSIGN(char **tokens, int *currentToken){

     bool FOUND = false;
     
     if(tokenSpecifier(tokens[*currentToken])==22){ //token: id
      
        (*currentToken)++;
        
        if(tokenSpecifier(tokens[*currentToken])==15){ // token: ":="
        
           (*currentToken)++;
           
           if(EXP(tokens,currentToken))  //if EXP returns success
              FOUND = true;              
        }        
     }

     return FOUND;     
}



bool EXP(char** tokens,int *ptr){
      
     bool FOUND=false;
  
     if(TERM(tokens,ptr)==true){
        FOUND=true;
       
        while(tokenSpecifier(tokens[*ptr])==16 || tokenSpecifier(tokens[*ptr])==17){ //token: '+' || token: '-'
             (*ptr)++;
                  
             if(TERM(tokens,ptr)==false)
                FOUND=false;
        }
     } 
     
     return FOUND;
}



bool IDLIST(char **tokens,int *currentToken){

     bool FOUND=false;
     
     if(tokenSpecifier(tokens[*currentToken])==22){ //token: id
        FOUND=true;
        (*currentToken)++;
        while(tokenSpecifier(tokens[*currentToken])==14 && FOUND==true){ //token: ','
             (*currentToken)++;	
             if(tokenSpecifier(tokens[*currentToken])==22) //token: id
               (*currentToken)++;
             else
                 FOUND=false;
        }
     } 
     return FOUND;
}



bool READ(char **tokens,int *ptr)
{
	  bool FOUND = false;
	  
	  if(tokenSpecifier(tokens[*ptr])==8)           //checking for "READ" keyword
	  {
		(*ptr)++; 
		if(tokenSpecifier(tokens[*ptr])==20)        //checking for "("
		{
		   (*ptr)++;
		   
		   if(IDLIST(tokens,ptr)==true)
		   {
		      if(tokenSpecifier(tokens[*ptr])==21)  //checking for ")"
		      {
		        FOUND = true;
		        (*ptr)++;
		      }
		   }
		}
	  }
	 
	  return FOUND;
	  
}



bool TERM(char **tokens,int *currentToken){

	bool FOUND = false;
	
	if(FACTOR(tokens,currentToken)){
		FOUND = true;
		while((tokenSpecifier(tokens[*currentToken]) == 18 || //token '*'
			   tokenSpecifier(tokens[*currentToken]) == 19) && //token 'DIV'
			   FOUND == true){   
			(*currentToken)++;
			if(!FACTOR(tokens,currentToken))
				FOUND = false;
		}
	}
	return FOUND;
}



bool FACTOR(char** tokens,int *ptr){

     bool FOUND=false;
   
     if(tokenSpecifier(tokens[*ptr])==22 || tokenSpecifier(tokens[*ptr])==23) //token: id || token: int
     {
        FOUND=true;
        (*ptr)++; 
     }
     else
     {
         if(tokenSpecifier(tokens[*ptr])==20) //token: '('
         {
            (*ptr)++; 
            if(EXP(tokens,ptr)==true)
            {  
              (*ptr)++;   
              if(tokenSpecifier(tokens[*ptr])==21) //token: ')'
                 FOUND=true;
            }    
         } 

     }
  
     return FOUND;
}


/////////////////////////////////////////////////////////// TEST METHODS ///////////////////////////////////////////////////////////////////


/* Pre:      input statement parsed as a sequence of tokens (char **tokens) and 
             an integer to indicate which method needs to be invoked
             
   Function: calls the appropriate method to check the type of the input statement
   
   Post:     returns true if the input statement matches any of the types, else false
*/

bool checkParser(char **tokens, int a){

     int index=0;
     
     switch(a){
     
         case 0: READ(tokens,&index);
                 break;
         
         case 1: IDLIST(tokens,&index);
                 break;
         
         case 2: ASSIGN(tokens,&index);
                 break;
                 
         case 3: EXP(tokens,&index);
                 break;
                 
         case 4: TERM(tokens,&index);
                 break;
                 
         case 5: FACTOR(tokens,&index);
                 break;
     }
     
     return size==index;
}



/* Pre:      an integer to indicate which parser method was invoked 
   Function: gets the name of the parser method
   Post:     returns the name of the parser method
*/

char* getSyntaxType(int a){

      switch(a){
     
         case 0: return "READ";
         
         case 1: return "IDLIST";
         
         case 2: return "ASSIGN";
                 
         case 3: return "EXP";
                 
         case 4: return "TERM";
                 
         case 5: return "FACTOR";
     }
}     

