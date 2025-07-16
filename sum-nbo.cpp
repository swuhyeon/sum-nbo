#include <stdint.h> // for uint32_t
#include <stdio.h> // for printf
#include <netinet/in.h> // for htonl

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    FILE *fp;
    uint32_t data[argc];
    int sum = 0;

    for (int i=1; i<argc; i++)
    {
        fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("ERROR: Failed to open file '%s'\n", argv[i]);
            return 1;
        }

        size_t read_count = fread(&data[i], sizeof(uint32_t), 1, fp);
        if (read_count != 1)
        {
            printf("ERROR: Failed to read file '%s'. file size is less than 4 bytes.\n", argv[i]);
            fclose(fp);
            return 1;
        }

        fclose(fp);

        data[i] = htonl(data[i]);
        sum += data[i];
    }

    for (int j=1; j<argc; j++)
    {
        printf("%d(0x%08x)", data[j], data[j]);
        if (j < argc - 1)
            printf(" + ");
    }

    printf(" = %d(0x%08x)\n", sum, sum);

    return 0;
}
