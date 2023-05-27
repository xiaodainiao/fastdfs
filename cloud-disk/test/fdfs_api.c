/**
* Copyright (C) 2008 Happy Fish / YuQing
*
* FastDFS may be copied only under the terms of the GNU General
* Public License V3, which may be found in the FastDFS source kit.
* Please visit the FastDFS Home Page http://www.csource.org/ for more detail.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include "make_log.h"
#include "fdfs_client.h"
#include "logger.h"
#include "fdfs_api.h"


int fdfs_upload_file1(const char* filename, char* fileid, int size)
{
    // 创建匿名管道
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1)
    {
        perror("pipe error");
        exit(1);
    }
    
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }
    // 父进程
    if(pid > 0)
    {
        // 关闭写端
        close(fd[1]);
        // 阻塞读管道
        read(fd[0], fileid, size);
        // 写log日志文件
        LOG("fastDFS", "upload_file", "fileID = %s", fileid);
        // 回收子进程资源
        close(fd[0]);
        wait(NULL);
    }
    // 子进程
    else if(pid == 0)
    {
        // 关闭读端
        close(fd[0]);
        // 执行execl操作
        const char* conf_file = "conf/client.conf";
        // 默认数据输出到终端, 需要将其保存起来
        // 解决思路, 将终端数据重定向到管道中
        // 标准输出重定向到管道写端
        dup2(fd[1], STDOUT_FILENO);
        execlp("fdfs_upload_file", "fdsf_upload_file", conf_file, filename, NULL);
        // 错误日志记录
        LOG("fastDFS", "upload_file", "upload file failed, file name: %s", filename);
    }

    return 0;
}

int fdfs_upload_file(const char* filename, char* fileid)
{
	char group_name[FDFS_GROUP_NAME_MAX_LEN + 1];
	ConnectionInfo *pTrackerServer;
	int result;
	int store_path_index;
	ConnectionInfo storageServer;
	
	log_init();
	g_log_context.log_level = LOG_ERR;
	ignore_signal_pipe();

    // 加载配置文件, 并初始化
    const char* conf_file = "conf/client.conf";
	if ((result=fdfs_client_init(conf_file)) != 0)
	{
		return result;
	}

    // 通过配置文件信息连接tracker, 并得到一个可以访问tracker的句柄
	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL)
	{
		fdfs_client_destroy();
		return errno != 0 ? errno : ECONNREFUSED;
	}

	*group_name = '\0';

    // 通过tracker句柄得到一个可以访问的storage句柄
	if ((result=tracker_query_storage_store(pTrackerServer, \
	                &storageServer, group_name, &store_path_index)) != 0)
	{
		fdfs_client_destroy();
		LOG("fastDFS", "upload_file", "tracker_query_storage fail, error no: %d, error info: %s",
			result, STRERROR(result));
		return result;
	}

    // 通过得到的storage句柄, 上传本地文件
	result = storage_upload_by_filename1(pTrackerServer, \
			&storageServer, store_path_index, \
			filename, NULL, \
			NULL, 0, group_name, fileid);
	if (result == 0)
	{
        LOG("fastDFS", "upload_file", "fileID = %s", fileid);
	}
	else
	{
        LOG("fastDFS", "upload_file", "upload file fail, error no: %d, error info: %s",
			result, STRERROR(result));
	}

    // 断开连接, 释放资源
	tracker_disconnect_server_ex(pTrackerServer, true);
	fdfs_client_destroy();

	return result;
}

