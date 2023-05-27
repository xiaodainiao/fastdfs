#include <stdlib.h>
#include <unistd.h>
#include "fcgi_stdio.h"
#include "fcgi_config.h"

// linux系统函数库中的全局变量, 存储环境变量
extern char **environ;

static void PrintEnv(char *label, char **envp)
{
    printf("%s:<br>\n<pre>\n", label);
    for ( ; *envp != NULL; envp++) {
        printf("%s\n", *envp);
    }
    printf("</pre><p>\n");
}

int main ()
{
    char **initialEnv = environ;
    int count = 0;

    // 有连接请求
    while (FCGI_Accept() >= 0) {
        // CONTENT_LENGTH post 数据的长度
        char *contentLength = getenv("CONTENT_LENGTH");
        int len;

        printf("Content-type: text/html\r\n"
               "\r\n"
               "<title>FastCGI echo</title>"
               "<h1>FastCGI echo</h1>\n"
               "Request number %d,  Process ID: %d<p>\n", ++count, getpid());

        if (contentLength != NULL) {
            len = strtol(contentLength, NULL, 10);
        }
        else {
            len = 0;
        }

        if (len <= 0) {
            printf("No data from standard input.<p>\n");
        }
        else {
            int i, ch;

            printf("Standard input:<br>\n<pre>\n");
            for (i = 0; i < len; i++) {
                if ((ch = getchar()) < 0) {
                    printf("Error: Not enough bytes received on standard input<p>\n");
                    break;
                }
                putchar(ch);
            }
            printf("\n</pre><p>\n");
        }

        PrintEnv("Request environment", environ);
        PrintEnv("Initial environment", initialEnv);
    } /* while */

    return 0;
}
