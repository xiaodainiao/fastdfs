#include <stdio.h>
#include <hiredis.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, const char* argv[])
{
    if(argc < 2)
    {
        printf("%s port\n", argv[1]);
        exit(1);
    }

    // 连接redis服务器
    redisContext * res = redisConnect("127.0.0.1", atoi(argv[1]));
    if(res == NULL)
    {
        printf("redis server connect fail...\n");
        exit(1);
    }

    // 测试
    redisReply* ret = NULL;
    ret = redisCommand(res, "ping");
    freeReplyObject(ret);

    // 存储一个hash
    ret = redisCommand(res, "hset user name %s", "kevin");
    freeReplyObject(ret);
    ret = redisCommand(res, "hset user age %d", 34);
    freeReplyObject(ret);
    ret = redisCommand(res, "hset user passwd %s", "123abc");
    freeReplyObject(ret);

    // 释放资源
    redisFree(res);

    return 0;
}
