
#include <Device.h>
#include <Types.h>
#include <memcpy.h>

__attribute__((used,visibility("default"))) const result(* syscalls[])(void){

};

long long seak_null(Device* dev,long long abs){
    return 0;
}

long read_null(Device* dev,long long offset,long len,void* addr){
    return 0;
}

long write_null(Device* dev,long long offset,long len,void* addr){
    return len;
}

const Device null_device = {
    .devno = 0x0103,
    .seak = seak_null
    .read = read_null,
    .write = write_null
};

long long seak_zero(Device* dev,long long abs){
    return abs;
}

long read_zero(Device* dev,long long abs,long len,void* addr){
    memset(addr,0,len);
    return len;
}

const Device zero = {
    .devno = 0x0105,
    .seak = seak_zero,
    .read = read_zero,
    .write = write_null
}

long write_full(Device* dev,long long abs,long len,void* addr){
    return DEVICE_FULL;
}

const Device full = {
    .devno = 0x0107,
    .seak = seak_zero,
    .read = read_zero,
    .write = write_full
}

