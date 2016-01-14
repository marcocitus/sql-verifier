#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define INNER_JOIN (0)
#define LEFT_JOIN  (1)
#define RIGHT_JOIN (2)
#define FULL_JOIN  (3)

#define SMALL_1 (0)
#define SMALL_2 (1)
#define LARGE_3 (2)
#define LARGE_4 (3)

char* JOIN[] = {"INNER", "LEFT", "RIGHT", "FULL"};
int NUM_JOINS = 4;

char* TABLE[] = {"table1", "table2", "table3", "table4"};
int NUM_TABLES = 4;


uint32_t getJoinType(uint64_t queryConfig, int joinIndex)
{
	return (queryConfig >> (joinIndex * 4 + 2)) & 3;
}


uint32_t getTableType(uint64_t queryConfig, int joinIndex)
{
	return (queryConfig >> (joinIndex * 4 + 4)) & 3;
}


void printJoins(int numJoins)
{
	uint32_t queryCount = 4 << (4 * numJoins);
	uint64_t queryConfig = 0;

	for (queryConfig = 0; queryConfig < queryCount; queryConfig++)
	{
		int joinIndex = -1;
		uint32_t tableType = 0;

		tableType = queryConfig & 3;

		printf("SELECT * FROM %s a", TABLE[tableType]);

		for (joinIndex = 0; joinIndex < numJoins; joinIndex++)
		{
			uint32_t joinType = 0;

			joinType = getJoinType(queryConfig, joinIndex);
			tableType = getTableType(queryConfig, joinIndex);

			printf(" %s JOIN %s %c ON (%c.id = %c.id)",
				   JOIN[joinType],
				   TABLE[tableType],
				   'a' + (joinIndex + 1),
				   'a' + (joinIndex),
				   'a' + (joinIndex + 1));
		}

		printf(" ORDER BY 1, 2");

		for (joinIndex = 0; joinIndex < numJoins; joinIndex++)
		{
			printf(", %d, %d", joinIndex * 2 + 3, joinIndex * 2 + 4);
		}

		printf(";\n");
	}
}


int main(void)
{
	int numJoins = 0;

	for (numJoins = 1; numJoins < 4; numJoins++)
	{
		printJoins(numJoins);
	}

	return 0;
}
