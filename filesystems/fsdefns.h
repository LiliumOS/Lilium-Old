#ifndef PHANTOMOS_FS_FSDEFNS_H_2021_04_14_09_27_03
#define PHANTOMOS_FS_FSDEFNS_H_2021_04_14_09_27_03

enum FSFlags{
    FSPermissionsAreUnix = 0x01,
    FSHasACL = 0x02,
    FSHasPACL = 0x04,
    FSHasExtObjs = 0x08,
    
}

typedef struct FSDescription{

} FSDescription;

#endif /* PHANTOMOS_FS_FSDEFNS_H_2021_04_14_09_27_03 */