/******************************************************************************
                Copyright (c) 2014-2014 Ejoin-Tech Inc.
                
Filename   :    utl_httpc.h
Description:    define the interface of ccm http client
Revision:       1.0
Author:         pengjian
Date:           2015.12.23
******************************************************************************/

#ifndef __UTL_HTTPC_H__
#define __UTL_HTTPC_H__

#include <utl_http_msg.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 0~99: defined the failed status */
#define UTL_HTTP_STATUS_TIMEOUT        0
#define UTL_HTTP_STATUS_GETHOSTFAIL    1
#define UTL_HTTP_STATUS_CONNFAIL       2
#define UTL_HTTP_STATUS_SENDFAIL       3       /* send request failed */
#define UTL_HTTP_STATUS_RECVFAIL       4       /* receive response failed */
#define UTL_HTTP_STATUS_INCOMPLTD      5       /* incompleted message received */
#define UTL_HTTP_STATUS_INVALMSG       6       /* invalid message received */

/* 100~199 defined the temporary status */
#define UTL_HTTP_STATUS_REQSENT        100

/* 200~299 defined the success status */
#define UTL_HTTP_STATUS_OK             200

typedef struct tagstUtlHttpClient utl_httpc_t;
typedef int (*FP_UTL_HTTPC_RESP)(int tid, utl_http_msg_t* resp, const void* data);

utl_httpc_t* utl_httpc_create(FP_UTL_HTTPC_RESP fpResp, void* data);
void utl_httpc_delete(utl_httpc_t* httpc);

/**
 * SET the max number of cached sessions
 * @param httpc:        the http client to be worked
 * @param max_caches:   the max number of cached sessions to be set
 *                      0 or negative means no limitation
 */
void utl_httpc_set_max_caches(utl_httpc_t* httpc, int max_caches);

void utl_httpc_run(utl_httpc_t* httpc, int ms);

/**
 * SEND a url GET request within specified time
 * @param httpc:    the http client to be worked
 * @param url:      the url to be sent
 * @param tmo:      the specified time in seconds
 *                  = 0: no retry
 *                  < 0: retry always or more session need cache
 *                  > 0: retry within the duration or more session need cache
 * @param fpResp:   the function to be invoked when response received or some error occured
 * @param data:     the data to be used when the function fpResp is invoked
 *
 * @return:     the transaction id(tid) if successful, -1 otherwise
 */
int utl_httpc_send_url(utl_httpc_t* httpc, const char* url, int tmo, FP_UTL_HTTPC_RESP fpResp, void* data);
int utl_httpc_send_msg(utl_httpc_t* httpc, const char* msg, int tmo, FP_UTL_HTTPC_RESP fpResp, void* data);
int utl_httpc_send_req(utl_httpc_t* httpc, utl_http_msg_t* req, int tmo, FP_UTL_HTTPC_RESP fpResp, void* data);

/* used to send http request via a proxy */
int utl_httpc_send_req_to(utl_httpc_t* httpc, utl_http_msg_t* req, 
                          const char* host, int port, int tmo, 
                          FP_UTL_HTTPC_RESP fpResp, void* data);

int utl_httpc_get_progress(utl_httpc_t* httpc, int tid);

#ifdef __cplusplus
}
#endif

#endif

