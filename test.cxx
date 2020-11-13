#include <iostream>

using namespace std;

int main (int argc, char** argv)
{
	if (argc > 1) return 1;
	printf("%s says \'Hello World!\'.\n", argv[0]);
	return 0;
}
