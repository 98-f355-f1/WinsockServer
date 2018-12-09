#include "Client.h"
#include "Chatter.h"

static
char *strcopy(char *dest, const char *src, size_t size)
{
	size_t i;

	for (i = 0; i < size && src[i] != '\0'; i++)
		dest[i] = src[i];
	for (; i < size; i++)
		dest[i] = '\0';

	return dest;
}

void
getInput(char *dest, int src, int bufSize)
{
	int count = 0;
	while ((src = getchar()) != EOF && src != '\n' && count < bufSize)
	{
		dest[count] = src;
		++count;
	}
	dest[count++] = '\0';
}
