#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>
#include <string.h>
#include <uv.h>
#include "Server0.h"

static uv_tcp_t serverSocket;
static uv_tcp_t clientSocket;
static uv_loop_t *serverLoop;

void start(int port, const char *ip, uv_loop_t *loop=NULL)
{
    if (loop == NULL)
    {
        serverLoop = uv_default_loop();
    }
    else
    {
        serverLoop = (uv_loop_t *) loop;
    }
    printf("The server is listening at %d\n", port);
    uv_tcp_init(serverLoop, &serverSocket);
    sockaddr_in addr;
    assert(uv_ip4_addr("127.0.0.1", port, &addr) == 0);
    uv_tcp_bind(&serverSocket, (const sockaddr *)&addr, 0);
    uv_listen((uv_stream_t *)&serverSocket, 1024, connectionCB);
    uv_run(serverLoop, UV_RUN_DEFAULT);
}

void connectionCB(uv_stream_t *stream, int status)
{
    if (status == 0)
    {
        uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
        uv_tcp_init(serverLoop, client);
        uv_accept(stream, (uv_stream_t *)client);
        uv_read_start((uv_stream_t *)client, allocateCB, readCB);
    }
}

void allocateCB(uv_handle_t *handler, size_t suggestSize, uv_buf_t *buf)
{
    buf->base = (char *)malloc(suggestSize);
    buf->len = suggestSize;
}

void readCB(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
    printf("%s\n", buf->base);
    free(buf->base);
    uv_write_t *write = (uv_write_t *)malloc(sizeof(uv_write_t));
    write->data = (char *)malloc(sizeof(char) * (strlen(httpHeader)+1));
    strcpy((char *)write->data, httpHeader);
    uv_buf_t writeBuffer = uv_buf_init((char *)write->data, strlen(httpHeader)+1);
    uv_write(write, stream, &writeBuffer, 1, writeCB);
}

void writeCB(uv_write_t *write, int status)
{
    free(write->data);
    uv_close((uv_handle_t *)write->handle, closeCB);
    free(write);
}

void closeCB(uv_handle_t *handler)
{
    free(handler);
}

