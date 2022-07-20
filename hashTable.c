#include	<stdio.h>
#include	<stdlib.h>	//	rand()
//	https://www.tutorialspoint.com/c_standard_library/string_h.htm
#include	<string.h>	//	strcpy(), NULL

//	Hash table 
//	Array of character string pointers
//	See below for "const char *" for string literal and "char" for a single char.
//  double quote means const char*, and single qoute means char.
//	https://stackoverflow.com/questions/20294015/a-value-of-type-const-char-cannot-be-assigned-to-an-entity-of-type-char-c

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
//	Programming in C by Kochan	p.260 and p.266
void	strCopy(char* dst, char* src)
{
	while (*src != '\0')
	{
		*dst++ = *src++;
	}
	*dst = '\0';
}

#define		uint	unsigned int
uint	copy;
//#include	<stdint.h>
struct ab
{
	int a;
	//uint32_t b;
	uint	b;
};
//typedef	unsigned int	uint;
// 
//	https://stackoverflow.com/questions/18582205/linkedlist-struct-typedef-in-c
//	Kochan Programming in C p.238
typedef struct Person
{
	const	char* name;
	const	char* role;
	uint	age;
	struct	Person* next;	//	need "struct Person" as "person" hasn't been typedef
}	person;	//	Use typedef so that "person" can replace "struct Person"


#define	HashTblSize	17
person*	hashTable[HashTblSize];

void	initHashTbl(void)
{
	for (int i = 0; i < HashTblSize; i++)
	{
		hashTable[i] = NULL;
	}
}

//	Convert each char of the pass-in string to integer and add them up
//	sum will be at most 0xFF (256) * strlen(Str)
//	The return value will be too big and get truncated for a long string Str.
int	sumCharToInt(const	char* Str)
{
	int	strI;
	int	sum = 0;
	for (int i = 0; i < strlen(Str); i++)
	{
		strI = (int)Str[i];
		sum += strI << (2 * i);	//	shift left two bits, i.e. * 4
	}
	printf("sumCharToInt(%s)\t= 0x%010x\t", Str, sum);
	return	sum;
}

int	hash(int num)
{
	int hash_value;
	hash_value = num % HashTblSize;	//	modulo < [HashTblSize]
	return	hash_value;
}

//	Insert at the head of hash table[hash_index].
person* hash_table_insert(person* p)
{
	int	hash_index = hash(sumCharToInt(p->name));
	printf("\thash index %d\n", hash_index);
	p->next = hashTable[hash_index];
	hashTable[hash_index] = p;
}

typedef	enum { true, false } bool;

person* hash_table_lookup(char* name)
{
	int	hash_index = hash(sumCharToInt(name));
	person* link_list_ptr = hashTable[hash_index];
	uint	link_list_search_depth = 0;
	while (link_list_ptr != NULL && strcmp(link_list_ptr->name, name) != 0)
	{
		link_list_ptr = link_list_ptr->next;
		link_list_search_depth++;
	}
	printf("hash_table_lookup() hash index = %d, search depth = %d\n", hash_index, link_list_search_depth);
	return	link_list_ptr;
}

#define	hw	"HW engineer"
#define sw	"SW engineer"
#define ad	"Administrator"
#define mg	"Manager"
#define	tn	"Technician"
#define	sc	"Security"
#define	co	"Chief Exec. Officer"

uint	number_employees(person* worker)
{
	uint cnt = 0;
	while (worker++->name != NULL)	//	The last person is a NULL.
		cnt++;
	printf("Total number of employees = %d", cnt);
	return	cnt;
}

int	main(void)
{
	/*
	const	char* employees[] = { "John", "Joanne", "Arther", "Lyft", "Uber", "Wilson", "Xiu", "Charles" };
	const	char* roles[] = { hw, sw, ad"HW engineer", "Technician", "SW engineer", "Manager", "Administrator" };
	employee john = { .age = 15, .name = "John", .role = "HW engineer" };
	employee joanne = { "Joanne", roles[1], 35 };
	static	employee workers[] = {john, joanne};	//	expression must have a constant value
	*/
	//	Initialization of a static array of the employee structures
	static	person employees[] = { {.age = 15, .name = "John", .role = hw, .next=NULL },	{"Whitehead", hw, 40},
			{ "Joanne", sw, 35}, {"Arthur", co, 56},	{"Lyft", sc, 70},	{"Uber", tn, 55}, {"Wilson", ad, 44},
				{"Xiu", sw, 47}, {"Cooper", ad, 29},	{"Ferguson", tn, 33}, {"Skywalker", sc, 42},
				{"Washington", .age = 39, .role = mg},	{.role = co, .name = "Jefferson", .age = 62},
				{"Beckman", mg, 34}, {"Blacksmith", ad, 29}, {"Springfield", tn, 52}, {"Jacobson", hw, 27}, {NULL} };
	//		The last {.name=NULL} is for number_employees() counting below
	initHashTbl();
	int	i, total;
	person* who;
	total = number_employees(&employees);
	for (i = 0; i < total; i++)
	{
		//	Press Ctrl twice to toggle inline hints...
		who = &employees[i];		
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
		printf("\nEmployee id = %4d\tname %s\tage %d\trole %s\n", i, who->name, who->age, who->role);
		hash_table_insert(who);
	}
	char name[30];
	while (1)
	{
		printf("Please enter a name to search (case-sensitive): ");
		scanf_s("%s", name, (uint)sizeof(name));
		who = hash_table_lookup(name);
		if (who)	//	true if return is a bool
			printf("Found employee with name %s\tage %d\trole %s\n\n", who->name, who->age, who->role);
		else		//	false
			printf("Employee by the name of %s NOT found\n", name);
	}
}