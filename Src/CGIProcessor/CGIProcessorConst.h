#ifndef CGIPROCESSOR_CONST_H
#define CGIPROCESSOR_CONST_H
namespace CGIProcessor
{

/**
variables, that are not yet used at the moment
      AUTH_TYPE
      HTTP_*
      GATEWAY_INTERFACE
      PATH_INFO
      PATH_TRANSLATED
      REMOTE_ADDR
      REMOTE_HOST
      REMOTE_IDENT
      REMOTE_USER
      SCRIPT_NAME
      SERVER_NAME
      SERVER_PORT
      SERVER_PROTOCOL
      SERVER_SOFTWARE
 */

/** holds the size of the input buffer */
static char const s_const_contentLength[] = "CONTENT_LENGTH";
static  char const s_const_contentType[]   = "CONTENT_TYPE";

/** holds the parameters of the http request */
static char const s_const_parameters[]    = "QUERY_STRING";

/** holds the type of the request [ "GET" | "HEAD" | "POST" ]*/
static char const s_const_reqMethod[]     = "REQUEST_METHOD";
static char const s_const_get_reqMethod[]   = "GET";
static char const s_const_post_reqMethod[]  = "POST";


}

#endif //CGIPROCESSOR_CONST
