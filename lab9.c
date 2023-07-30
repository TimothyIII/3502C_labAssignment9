#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	int id;
	char name;
	int order;
    int index;
	struct HashType* next;
};

// Inputs to HashType
void insert(struct HashType** head, struct RecordType* ppData, int index)
{
	struct HashType* newHash = (struct HashType*)malloc(sizeof(struct HashType));

	newHash->id = ppData->id;
	newHash->name = ppData->name;
	newHash->order = ppData->order;
    newHash->index = index;
	newHash->next = NULL;

    if (*head == NULL) {
		*head = newHash;
	} else {
		struct HashType* temp = *head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newHash;
	}
}

// Compute the hash function
int hash(int x)
{
	return ((x % 5) + 1);
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

    printf("Index %d:\n", pHashArray->index);
	while (pHashArray != NULL)
	{
		printf("\tID: %d,\tName: %c,\tPosition in original List: %d\n", pHashArray->id, pHashArray->name, pHashArray->order);
		pHashArray = pHashArray->next;
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	struct HashType *student1 = NULL, *student2 = NULL, *student3 = NULL, *student4 = NULL, *student5 = NULL;
    int code, studentCount1 = 0, studentCount2 = 0, studentCount3 = 0, studentCount4 = 0, studentCount5 = 0;
	
    // Insert to 5 different Hash functions
	for (int i = 0; i < recordSz; i++) {
		
        code = hash(pRecords->id);
		
        if (code == 1) {
			insert(&student1, pRecords, 1);
            studentCount1++;
		} else if (code == 2) {
			insert(&student2, pRecords, 2);
            studentCount2++;
		} else if (code == 3) {
			insert(&student3, pRecords, 3);
            studentCount3++;
		} else if (code == 4) {
			insert(&student4, pRecords, 4);
            studentCount4++;
		} else {
			insert(&student5, pRecords, 5);
            studentCount5++;
		}

        // Next Record
        pRecords++;
	}

    // Print each list (If list is empty skip)
	if (student1 != NULL) displayRecordsInHash(student1, studentCount1);
	if (student2 != NULL) displayRecordsInHash(student2, studentCount2);
	if (student3 != NULL) displayRecordsInHash(student3, studentCount3);
	if (student4 != NULL) displayRecordsInHash(student4, studentCount4);
	if (student5 != NULL) displayRecordsInHash(student5, studentCount5);
}