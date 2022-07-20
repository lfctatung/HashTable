#include	<stdio.h>
#include	<stdlib.h>	//	rand()
#include	<string.h>	//	strcpy()

//	Hash table 
//	Array of character string pointers
//	See below for "const char *" for string literal and "char" for a single char.
//  double quote means const char*, and single qoute means char.
//	https://stackoverflow.com/questions/20294015/a-value-of-type-const-char-cannot-be-assigned-to-an-entity-of-type-char-c
const	char*	employees[] = {"John", "Joanne", "Arther", "Lyft", "Uber", "Wilson", "Xiu", "Charles"};
const	char*	roles[] = { "HW engineer", "Technician", "SW engineer", "Manager", "Administrator" };

//	Convert each char of the pass-in string to integer and add them up
//	sum will be at most 0xFF (256) * strlen(Str)
int	sumCharToInt(const	char* Str)
{
	int	strI;
	int	sum = 0;
	for (int i = 0; i < strlen(Str); i++)
	{
		strI = (int)Str[i];
		sum += strI << (2 * i);	//	shift left two bits, i.e. * 4
	}
	printf("sumCharToInt(%s)\t= 0x%010x\n", Str, sum);
	return	sum;
}

//	The return value will be too big and get truncated for a long string Str.
#define	STR_MAX	50
int	strToInt(const	char* Str)
{
	//	char* Str = "John";	
	// employees[0] contains a pointer to the character string "John";
	char	hexStr[STR_MAX];
	int	strI, k, i, j = 0;
	for (i = 0; i < strlen(Str); i++)
	{
		strI = (int)Str[i];
		//	https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/sprintf-s-sprintf-s-l-swprintf-s-swprintf-s-l?view=msvc-170
		k = sprintf_s(hexStr + j, 10, "%02X", strI);
		j += k;	// one byte => k = 2 nibbles.
	}
	hexStr[STR_MAX - 1] = '\0';
	printf("Converted hex string = %s\n", hexStr);
	int	num = (int)strtol(hexStr, NULL, 16);
	printf("strtol hex = %X, decimal %d, ", num, num);	//	num (overflow) > int32 for Str > 4 characters.
	return	num;
	//	See	https://www.codevscolor.com/c-convert-string-to-hexadecimal
	/*
	printf("%x, %X\n", 'j', 'J');
	char	hex[] = "6a6b6c";	//	jkl
	int	num = (int)strtol(hex, NULL, 16);
	printf("decimal %d, hex %x", num, num);

	Python See	https://www.adamsmith.haus/python/answers/how-to-convert-a-string-from-hex-to-ascii-in-python
	>>> a = 0x6a6b6c
	>>> a
	6974316
	>>> hex(a)
	'0x6a6b6c'
	>>> hexString = hex(a)[2:]
	>>> hexString
	'6a6b6c'
	>>> bytes.fromhex(hexString).decode("ASCII")
	'jkl'
	*/
}

//	https://stackoverflow.com/questions/18582205/linkedlist-struct-typedef-in-c
//	Kochan Programming in C p.238
typedef	struct Person
{
	const	char	*name;
	int		age;
	const	char	*role;
	struct Person* next;	//	need "struct Person" as "person" hasn't been typedef
}	person;	//	for typedef so that "person" can replace "struct person"

#define	HashTblSize	17
person	people[HashTblSize];

void	initHashTbl(void)
{
	for (int i = 0; i < HashTblSize; i++)
	{
		people[i].name = "\0";	// double-quote for string literal
		people[i].next = NULL;
	}
}

int	hash(int num)
{
	int hash_value;
	hash_value = num % HashTblSize;	//	modulo < people[size]
	return	hash_value;
}

//	Programming in C by Kochan	p.260 and p.266
void	strCopy(char* dst, char* src)
{
	while (*src != '\0')
	{
		*dst++ = *src++;
	}
	*dst = '\0';
}

person* find_entry(person* list_head)
{
	person* listPtr;
	if (list_head->next == NULL)
	{
		if (list_head->name == "\0")	//	no collision
			return	list_head;
		else	//	collision with first entry non-empty
		{
			list_head->next = (person*)malloc(sizeof(person));
			return	list_head->next;
		}
	}
	else	//	multiple entries have been taken
	{
		listPtr = list_head->next;
		while (listPtr->next != NULL)
			listPtr = listPtr->next;
		listPtr->next = (person*)malloc(sizeof(person));
		return	listPtr->next;
	}
}

person* lookup(person* list_head, char* name)
{	
	if (strcmp(list_head->name, name) == 0)
		return	list_head;
	person* listPtr = list_head->next;
	while (listPtr != NULL)
	{		
		if (strcmp(listPtr->name, name) == 0)
			break;
		listPtr = listPtr->next;
	}
	return	listPtr;
}

int	main(void)
{
	initHashTbl();
	int	k, i;
	person* who;
	for (i = 0; i < 8; i++)
	{
		//	Press Ctrl twice to toggle inline hints...

		printf("Employee id = %4d name %s\t", i, employees[i]);
		//	k = hash(strToInt(employees[i]));
		k = hash(sumCharToInt(employees[i]));
		who = find_entry(&people[k]);
		//	https://www.geeksforgeeks.org/is-sizeof-for-a-struct-equal-to-the-sum-of-sizeof-of-each-member/
		//	int	length = sizeof(who->name);
		//	https://stackoverflow.com/questions/32136185/difference-between-strcpy-and-strcpy-s
		//	A buffer who->name which holds # of chars incluing the null character.
		/*	char* Destination, SizeInBytes, const char* Source
		strcpy_s(who->name, sizeof(who->name), employees[i]);			
		strcpy_s(who->role, sizeof(who->role), roles[i % 5]);
		
		strCopy(who->name, employees[i]);
		strCopy(who->role, roles[i % 5]);
		*/
		//	Use pointers in lieu of array char for zero copy.
		who->name = employees[i];
		who->role = roles[i % 5];
		who->age = rand() % 80;
		who->next = NULL;
		printf("Hashed employee id = %4d\tname %s\tage %d\trole %s\n\n", k, who->name, who->age, who->role);
	}
	char name[30];
	while (1)
	{
		printf("Please enter a name to search (case-sensitive): ");
		scanf_s("%s", name, (unsigned int)sizeof(name));
		k = hash(sumCharToInt(name));
		printf("hash id = %4d\n", k);
		who = lookup(&people[k], name);
		if (who != NULL)
			printf("Found employee: name %s\tage %d\trole %s\n\n", who->name, who->age, who->role);
		else
			printf("Person by the name of %s is NOT found\n", name);
	}
}