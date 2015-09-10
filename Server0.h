#ifndef SERVER0_H
#define SERVER0_H
#include <uv.h>
const char httpHeader[] = "HTTP/1.1 200 OK\r\n"
    "Last-Modified: Sat, 10 Mar 2012 14:42:12 GMT\r\n"
    "Accept-Ranges: bytes\r\n"
    "Content-Type:text/html;charset=utf-8\r\n"
    "Date: Sat, 10 Mar 2012 14:46:19 GMT\r\n"
    "Server: small\r\n"
    "Expires: Sat, 10 Mar 1900 14:47:19 GMT\r\n"
    "Content-Length:11\r\n"
    "Connection: close\r\n"
    "\r\n"
    "Hello world.cpp";

void start(int port, const char *ip, uv_loop_t *loop);

void connectionCB(uv_stream_t *stream, int status);
void allocateCB(uv_handle_t *handler, size_t suggestedSize, uv_buf_t *buf);
void readCB(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf);
void writeCB(uv_write_t *write, int status);
void closeCB(uv_handle_t *handler);

#endif
