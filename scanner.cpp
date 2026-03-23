
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include "token.h"
#include <fstream>
#include "scanner.h"

std::ifstream inFile;
int lineNumber = 1;
char nextChar;


//get next char from input stream
char getNextChar()
{

    //ch stores the output
    char ch;

    
    if (inFile.get(ch))  
    {

        //increase line number counter when line ends
        if (ch == '\n')
            lineNumber++;

        return ch;
    }

    return EOF;
}

//skip over spaces
void skipSpaces()
{
    //while next char is white space get the next char
    while (isspace(nextChar)) {
        nextChar = getNextChar();
    }
}


void skipComments()
{
    if (nextChar == '!')
    {
        nextChar = getNextChar();  

        while (nextChar != '!' && nextChar != EOF)
        {
            nextChar = getNextChar();
        }

        if (nextChar == '!')
        {
            nextChar = getNextChar();  
        }
    }
}


void filter()
{
    /*
    go through each char
    if the char is whitespace or comment then skip it 
    */
   while(nextChar == '!' || isspace(nextChar))
   {
    if(nextChar == '!')
    {
        skipComments();
    }

    if(isspace(nextChar))
    {
        skipSpaces();
    }
   }
}


void scannerError()
{
    if (nextChar == '\n')
        std::cout << "SCANNER ERROR: \\n " << lineNumber << std::endl;
    else if (nextChar == EOF)
        std::cout << "SCANNER ERROR: EOF " << lineNumber << std::endl;
    else
        std::cout << "SCANNER ERROR: " << nextChar << " " << lineNumber << std::endl;

    exit(1);
}

//begins with # or " followed by one or more digits
token t1()
{

    token tk;

    if(nextChar == '#' || nextChar == '"')
    {

        //store token information
        tk.id = t1_tk;
        tk.instance = "";
        tk.line = lineNumber;

        tk.instance += nextChar;
        nextChar = getNextChar();

        if (!isdigit(nextChar))
        {
            scannerError();
        }

        while (isdigit(nextChar))
        {

            tk.instance += nextChar;
            nextChar = getNextChar();
            
        }
    

    }

    return tk;

}


//one or more letters followed by 1 or more digits
token t2()
{

    token tk;

    if(isalpha(nextChar))
    {
        tk.id = t2_tk;
        tk.instance = "";
        tk.line = lineNumber;

        tk.instance += nextChar;
        nextChar = getNextChar();


        while (isalpha(nextChar))
        {
            tk.instance += nextChar;
            nextChar = getNextChar();
        }

        if(!isdigit(nextChar))
        {
            scannerError();
        }

        while(isdigit(nextChar))
        {
            tk.instance += nextChar;
            nextChar = getNextChar();
        }
        
    }

    return tk;


}


//ascii 36-47
token t3()
{

    token tk;

    if (nextChar >= 36 && nextChar <= 47)
    {
        tk.id = t3_tk;
        tk.instance = "";
        tk.line = lineNumber;

        tk.instance += nextChar;

        nextChar = getNextChar();
    }

    return tk;
}


//filter comments and whitespace, return token 
token scanner()
{

    token tk;

    filter();

    if (nextChar == '#' || nextChar == '"')
        return t1();

    if (isalpha(nextChar))
        return t2();

    if (nextChar >= 36 && nextChar <= 47)
        return t3();

    if (nextChar == EOF)
    {
        tk.id = EOFTk;
        tk.instance = "EOF";
        tk.line = lineNumber;
        return tk;
    }

    scannerError();
    return tk;
}