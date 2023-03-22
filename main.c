#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 256

struct ENVVAR
{
    char *name;
    char *value;
};

// Write a function that reads a file and returns a pointer to a struct ENVVAR
// The struct should contain the name and value of the environment variable
// The function should return a pointer to an array of ENVVAR structs
// The function should take the path to the file as a parameter
// The function should return the number of environment variables in the file
struct ENVVAR *dotenv_load(char *path, int count)
{
    // Read file
    FILE *fp;
    fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Error opening file");
        return NULL;
    }

    struct ENVVAR *envVars = malloc(sizeof(struct ENVVAR) * count);

    char line[MAX_LEN];
    int lineCount = 0;
    while (fgets(line, MAX_LEN, fp) != NULL)
    {
        // printf("New line: %s\n", line);

        // Split string
        char *token;
        // Get the first token
        token = strtok(line, "=");
        // Iterate through the string to extract all tokens
        int i = 0;
        while (token != NULL)
        {
            // remove newline character
            if (token[strlen(token) - 1] == '\n')
            {
                token[strlen(token) - 1] = '\0';
            }
            // printf("Token: %s - %d\n", token, i);
            if (i == 0)
                envVars[lineCount].name = strdup(token);
            else if (i == 1)
            {
                envVars[lineCount].value = strdup(token);
            }
            token = strtok(NULL, "=");
            i++;
        }
        lineCount++;
    }

    fclose(fp);

    return envVars;
}

// Return value of environment variable with given name
char *dotenv_get(struct ENVVAR *envVars, char *name, int count)
{
    for (int idx = 0; idx < count; idx++)
    {
        if (strcmp(envVars[idx].name, name) == 0)
        {
            return envVars[idx].value;
        }
    }
    return NULL;
}

void dotenv_free(struct ENVVAR *envVars, int count)
{
    for (int idx = 0; idx < count; idx++)
    {
        free(envVars[idx].name);
        free(envVars[idx].value);
    }
    free(envVars);
}

int main()
{
    int count = 2;
    struct ENVVAR *envVars = dotenv_load(".env", count);

    // Get env var A
    char *envVarA = dotenv_get(envVars, "A", count);
    if (envVarA == NULL)
    {
        printf("Env var A not found\n");
    }
    else
    {
        printf("Env var A: %s\n", envVarA);
    }

    // Get env var B
    char *envVarB = dotenv_get(envVars, "B", count);
    if (envVarB == NULL)
    {
        printf("Env var B not found\n");
    }
    else
    {
        printf("Env var B: %s\n", envVarB);
    }

    // Get env var C
    char *envVarC = dotenv_get(envVars, "C", count);
    if (envVarC == NULL)
    {
        printf("Env var C not found\n");
    }
    else
    {
        printf("Env var C: %s\n", envVarC);
    }

    // Print env vars
    // for (int idx = 0; idx < count; idx++)
    // {
    //     printf("Loaded env var: %s=%s\n", envVars[idx].name, envVars[idx].value);
    // }

    // Free memory
    dotenv_free(envVars, count);
    return 0;
}