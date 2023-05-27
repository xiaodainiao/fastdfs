# 基于c++分布式文件传输系统

## 目录结构

```shell
.
├── cloud-disk
│   ├── bin_cgi
│   │   ├── dealfile
│   │   ├── dealsharefile
│   │   ├── login
│   │   ├── md5
│   │   ├── myfiles
│   │   ├── register
│   │   ├── sharefiles
│   │   └── upload
│   ├── cloud_disk.sql
│   ├── common
│   │   ├── base64.c
│   │   ├── base64.o
│   │   ├── cfg.c
│   │   ├── cfg.o
│   │   ├── cJSON.c
│   │   ├── cJSON.o
│   │   ├── deal_mysql.c
│   │   ├── deal_mysql.o
│   │   ├── des.c
│   │   ├── des.o
│   │   ├── make_log.c
│   │   ├── make_log.o
│   │   ├── md5.c
│   │   ├── md5.o
│   │   ├── redis_op.c
│   │   ├── redis_op.o
│   │   ├── util_cgi.c
│   │   └── util_cgi.o
│   ├── conf
│   │   ├── cfg.json
│   │   ├── client.conf
│   │   ├── redis.conf
│   │   ├── redis.log
│   │   ├── storage.conf
│   │   └── tracker.conf
│   ├── fastdfs.sh
│   ├── fcgi.sh
│   ├── include
│   │   ├── base64.h
│   │   ├── cfg.h
│   │   ├── cJSON.h
│   │   ├── deal_mysql.h
│   │   ├── des.h
│   │   ├── make_log.h
│   │   ├── md5.h
│   │   ├── redis_keys.h
│   │   ├── redis_op.h
│   │   └── util_cgi.h
│   ├── logs
│   │   ├── cgi
│   │   │   ├── 2017
│   │   │   └── 2023
│   │   └── database
│   ├── Makefile
│   ├── nginx.conf
│   ├── nginx.sh
│   ├── README
│   ├── redis
│   │   ├── dump.rdb
│   │   └── redis.log
│   ├── redis.sh
│   ├── src_cgi
│   │   ├── dealfile_cgi.c
│   │   ├── dealfile_cgi.o
│   │   ├── dealsharefile_cgi.c
│   │   ├── dealsharefile_cgi.o
│   │   ├── login_cgi.c
│   │   ├── login_cgi.o
│   │   ├── md5_cgi.c
│   │   ├── md5_cgi.o
│   │   ├── myfiles_cgi.c
│   │   ├── myfiles_cgi.o
│   │   ├── reg_cgi.c
│   │   ├── reg_cgi.o
│   │   ├── sharefiles_cgi.c
│   │   ├── sharefiles_cgi.o
│   │   ├── upload_cgi.c
│   │   └── upload_cgi.o
│   ├── start.sh
│   └── test
│       ├── a.out
│       ├── echo.c
│       ├── fastcgi_demo.c
│       ├── fdfs_api.c
│       ├── fdfs_api.h
│       ├── fdfs_upload_file.c
│       ├── main.c
│       ├── myredis.c
│       └── redis_example.c
├── main.cpp
├── main.exe
└── README.md
```

- `bin`：可执行文件
- `cloud_disk.sql`：数据库表创建
- `common`：封装的一些接口
- `conf`：Redis、MySQL、fastcgi、fastdfs配置
- `src_cgi`：cgi进程，每个文件代表一个处理进程
- `test`：测试用例
- `.sh`：各种软件的启动的脚本



## 整体流程

![image-20230527120613943](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230527120613943.png)

##  文件上传流程

![image-20230527123513031](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230527123513031.png)

## 文件下载流程

![image-20230527124549802](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230527124549802.png)

## 快速下载流程

- 在数据库中存储，存储节点的IP+port。
- 当文件下载的时候，只需要通过cgi进程查询数据库来获取ip+port
- 客户端直接通过ip+port请求存储节点

注意：因为fastdfs不能直接解析http请求，所以需要先安装nginx-fastdfs插件，也就是先让nginx解析，在发送给fastdfs

![image-20230527125025054](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230527125025054.png)
