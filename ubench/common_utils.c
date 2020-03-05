#include "common_utils.h"

/* Compute t2 - t1 */                                                           
                                                                                
inline long long calculate_time_diff_spec(struct timespec t2, struct timespec t1) {
    long long elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000000000LL + t2.tv_nsec - t1.tv_nsec;
    return elapsedTime;                                                         
}  
