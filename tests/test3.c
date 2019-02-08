#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../includes/malloc.h"
#define M (1024 * 1024)

void	print(char *s)
{
	write(1, s, strlen(s));
}

int		main(void)
{
	char	*addr1;
	char	*addr3;

	addr1 = (char*)malloc(16 * M);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr3 = (char*)realloc(addr1, 128 * M);
	addr3[127 * M] = 42;
//	printf("addr1 : %p\n", addr1);
//	printf("addr3 : %p\n", addr3);
	print(addr3);
	return (0);
}
