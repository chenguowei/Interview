//
// Created by 陈国威 on 2018/3/26.
//

#ifndef INTERVIEW_BIG_LITTLE_H
#define INTERVIEW_BIG_LITTLE_H

typedef unsigned short int uint16;
typedef unsigned long int uint32;

#define sw16(x) \
		(((short)(x) & (short)0x00ff) << 8) | \
		(((short)(x) & (short)0xff00) >> 8)

#define Swap32(A) \
		( (((uint32)(A) & (0xff000000)) >> 24) | \
		(((uint32)(A) & (0x00ff0000)) >> 8) | \
		(((uint32)(A) & (0x0000ff00)) << 8) | \
		(((uint32)(A) & (0x000000ff)) << 24) )


#endif //INTERVIEW_BIG_LITTLE_H
