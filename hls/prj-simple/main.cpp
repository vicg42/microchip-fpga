#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>

char app_name[128];
int spi_mode;
char spi_name[100] = {"/dev/spidev2.0"};
char text[100] = {""};

static const struct option long_opt_arr[] = {
    {"help", no_argument, 0, 'h'},
    {"input", required_argument, 0, 'i'},
    {"output", required_argument, 0, 'i'},
    {0, 0, 0, 0}};

int main(int argc, char *argv[])
{
    printf("Hello World!\n");
    int next = 0;
    do
    {
        switch (next = getopt_long(argc, argv, "i:o:", long_opt_arr, 0))
        {
        case 'i':
            strcpy(spi_name, optarg);
            break;
        case 'o':
            strcpy(text, optarg);
            break;
        case -1: // no more options
            break;
        case 'h':
            strncpy(app_name, __FILE__, (strlen(__FILE__) - 2));
            printf("Usage: ./%s [option]\n", app_name);
            printf("Mandatory option: \n");
            printf("    -h  --help              help\n");
            printf("    -d  --device   <path>   linux device. Default: %s\n", spi_name);
            exit(EXIT_SUCCESS);
        default:
            exit(EINVAL);
        };
    } while (next != -1);

    printf("prj-simple: -i %s -o %s\n", spi_name, text);

    return 0;
}
