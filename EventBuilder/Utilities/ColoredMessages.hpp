
#include <iostream>
#include <string>

// Replace '<< "\033[0;"' with '<< "\033[1;"' if you want Bold
#ifndef REDERROROUT
#define REDERROROUT
void RedErrorOut(string message)
{
cerr 		<< "\033[0;" << 31 << "m" 
		<< message 
		<< "\033[0m" 
		;//<< endl;
}


void RedOut(string message)
{
cout 		<< "\033[0;" << 31 << "m" 
		<< message 
		<< "\033[0m" 
		;//<< endl;
}
void GreenOut(string message)
{
cout 		<< "\033[0;" << 32 << "m" 
		<< message 
		<< "\033[0m" 
		;//<< endl;
}

void YellowOut(string message)
{
cout 		<< "\033[0;" << 33 << "m" 
		<< message 
		<< "\033[0m" 
		;//<< endl;
}

void BlueOut(string message)
{
cout 		<< "\033[0;" << 34 << "m" 
		<< message 
		<< "\033[0m" 
		;//<< endl;
}
#endif
