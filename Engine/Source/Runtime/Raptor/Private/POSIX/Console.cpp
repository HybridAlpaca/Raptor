#include <Console.h>

#include <unistd.h>
#include <stdlib.h>

void Raptor::Print (cchar string)
{
	write(STDOUT_FILENO, string, Strlen(string));
}

void Raptor::Println (cchar string)
{
	// Hacky; but hey, it works
	Print(string);
	Print("\n");
}

void Raptor::Println (uint32 val)
{
	char buf [16];
	Println(ItoA(val, buf));
}

cchar Raptor::ItoA (uint32 num, char * str)
{
	int i = 0;
	bool isNegative = false;

	/* Handle 0 explicitely, otherwise empty string is printed for 0 */
	if (num == 0)
	{
			str[i++] = '0';
			str[i] = '\0';
			return str;
	}

	// In standard itoa(), negative numbers are handled only with
	// base 10. Otherwise numbers are considered unsigned.
	if (num < 0)
	{
			isNegative = true;
			num = -num;
	}

	// Process individual digits
	while (num != 0)
	{
			int rem = num % 10;
			str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
			num = num/10;
	}

	// If number is negative, append '-'
	if (isNegative)
			str[i++] = '-';

	str[i] = '\0'; // Append string terminator

	return str;
}

uintptr Raptor::Strlen (cchar string)
{
	uintptr len = 0;

	while ((* string) != '\0')
	{
		++string;
		++len;
	}

	return len;

}
