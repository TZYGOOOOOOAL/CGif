#include <stdlib.h>
#include "include/cgif_main.h"
#include "include/cgif_read.h"

int main()
{
	CGif cgif;
	read_gif("C:/Users/tzy/Desktop/test/0.gif", &cgif);

	system("pause");
	return 0;
}