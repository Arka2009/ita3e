#ifndef _COMMON_UTIL_H                                                          
#define _COMMON_UTIL_H                                                          
                                                                                
#include <time.h>                                                               
#include <stdlib.h>                                                             
#include <stdio.h>                                                              
                                                                                
// Please Also move task queue methods to this file                             
long long calculate_time_diff_spec(struct timespec, struct timespec);           
#endif /* _COMMON_UTIL_H */
