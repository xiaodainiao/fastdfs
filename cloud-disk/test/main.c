#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "fdfs_api.h"

int main(int argc, const char* argv[])
{
    char buf[1024] = {0};
    fdfs_upload_file(argv[1], buf);
    printf("fileId = %s\n", buf);
    
    printf("=========================\n");
    memset(buf, 0, sizeof(buf));
    fdfs_upload_file1(argv[1], buf, sizeof(buf));
    printf("fileId = %s\n", buf);

    return 0;
}
