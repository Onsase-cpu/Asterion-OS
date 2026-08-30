#include "asterion.h"
ast_status_t security_validate_user_pointer(const void *p,size_t length){return p&&length?AST_OK:AST_ERR_INVALID;}
