#include <iostream>

using namespace std;

int main (int argc, char** argv)
{
	if (argc > 2) return 1;
	printf("%s says \'Hello World!\'.\n", argv[1]);
	return 0;
}
