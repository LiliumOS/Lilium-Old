#ifndef __PHANTOMOS_DEVICE_H_2021_02_02_04_29_03
#define __PHANTOMOS_DEVICE_H_2021_02_02_04_29_03

typedef struct Device{
    unsigned short devno;
    long long(*seak)(Device* dev,long long abs);
    long(*read)(Device* dev,long long offset,long len,void* v);
    long(*write)(Device* dev,long long offset,long len,const void* v);
};

#define BROKEN_DEVREF (-0x200)
#define DEVICE_FULL (-0x205)

#endif /* __PHANTOMOS_DEVICE_H_2021_02_02_04_29_03 */
