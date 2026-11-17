
#include <stdio.h>

int main()
{
    int allocation[2][2] = {
        {1, 0},
        {0, 1}
    };

    int request[2][2] = {
        {0, 1},
        {1, 0}
    };

    int graph[2][2] = {0};
    int visited[2] = {0};
    int stack[2] = {0};
    int deadlock = 0;

    printf("PRINTER AND SCANNER DEADLOCK DETECTION\n");

    printf("\nRESOURCE ALLOCATION:\n");
    printf("P1 holds Printer\n");
    printf("P2 holds Scanner\n");

    printf("\nRESOURCE REQUESTS:\n");
    printf("P1 requests Scanner\n");
    printf("P2 requests Printer\n");

    // Build Wait-For Graph
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (request[i][j])
            {
                for (int k = 0; k < 2; k++)
                {
                    if (allocation[k][j])
                    {
                        graph[i][k] = 1;
                    }
                }
            }
        }
    }

    printf("\nWAIT-FOR GRAPH:\n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (graph[i][j])
                printf("P%d -> P%d\n", i + 1, j + 1);
        }
    }

    // Deadlock detection using DFS
    for (int i = 0; i < 2; i++)
    {
        if (!visited[i])
        {
            int current = i;

            while (!visited[current])
            {
                visited[current] = 1;
                stack[current] = 1;

                int next = -1;

                for (int j = 0; j < 2; j++)
                {
                    if (graph[current][j])
                    {
                        next = j;
                        break;
                    }
                }

                if (next == -1)
                    break;

                if (stack[next])
                {
                    deadlock = 1;
                    break;
                }

                current = next;
            }

            if (deadlock)
                break;

            for (int j = 0; j < 2; j++)
                stack[j] = 0;
        }
    }

    printf("\nDEADLOCK DETECTION:\n");

    if (deadlock)
    {
        printf("DEADLOCK DETECTED!\n");
        printf("Processes involved: P1 and P2\n");
    }
    else
    {
        printf("NO DEADLOCK DETECTED.\n");
    }

    return 0;
}
