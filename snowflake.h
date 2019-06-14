#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <linux/types.h>
#include <time.h>
#include <stdint.h>
#include <sys/time.h>

#define   sequenceMask  (-1L ^ (-1L << 12L))

struct snowFlake {
    int global_int:12;
	uint64_t lastTime;
	int workID;
	int SeqID;
};
struct snowFlake snowFlakeInfo;

int setWorkID( int workID ){
    snowFlakeInfo.workID = workID;
    return snowFlakeInfo.workID;
}
// pid_t getTaskID() {
//     if( snowFlakeInfo.workID ){
//         return snowFlakeInfo.workID;
//     }
// 	return syscall( __NR_gettid );
// }
uint64_t getCurrentMillisecond(){
	struct timeval nowTime;
	gettimeofday(&nowTime,NULL);
    // return (nowTime.tv_sec)*1000 + time_now.tv_usec/1000;
	return (nowTime.tv_sec - 1500000000)*1000 + nowTime.tv_usec/1000;
}

uint64_t waitNextMillisecond( uint64_t lastStamp ){
	uint64_t cur = 0;
	do {
		cur = getCurrentMillisecond();
	} while (cur <= lastStamp);
	return cur;
}
int atomic_incr( int id ) {
	__sync_add_and_fetch( &id, 1 );
	return id;
}
uint64_t getUniqueId() {
	uint64_t  uniqueId=0;
	uint64_t nowtime = getCurrentMillisecond();
	uniqueId = nowtime<<22;
	uniqueId |=( snowFlakeInfo.workID&0x3ff)<<12;

	if ( nowtime < snowFlakeInfo.lastTime ) {
		exit( -1 );
	}
	if ( nowtime == snowFlakeInfo.lastTime ) {
		snowFlakeInfo.SeqID = atomic_incr( snowFlakeInfo.SeqID )& sequenceMask;
		if ( snowFlakeInfo.SeqID == 0 ) {
			nowtime = waitNextMillisecond( snowFlakeInfo.lastTime );
		}
	} else {
		snowFlakeInfo.SeqID  = 0;
	}
	snowFlakeInfo.lastTime = nowtime;
	uniqueId |= snowFlakeInfo.SeqID;
	return uniqueId;
}
