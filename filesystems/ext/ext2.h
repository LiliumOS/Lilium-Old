#ifndef PHANTOMOS_EXT2_H_2021_01_03_17_41_32 
#define PHANTOMOS_EXT2_H_2021_01_03_17_41_32

#include <stdint.h>

typedef struct{
    uint32_t inode_cnt;
    uint32_t block_cnt;
    uint32_t reserved_cnt;
    uint32_t unallocated_blocks;
    uint32_t unallocated_inodes;
    uint32_t superblock_position;
    uint32_t block_size;
    uint32_t fragment_size;
    uint32_t group_block_count;
    uint32_t group_fragment_count;
    uint32_t group_inode_count;
    uint32_t mount_time;
    uint32_t write_time;
    uint16_t mounts_since_fsck;
    uint16_t allowed_mounts_since_fsck;
    uint16_t signature;
    uint16_t dirty;
    uint16_t err_handling;
    uint16_t minor_version;
    uint32_t last_fsck;
    uint32_t max_fsck_interval;
    uint32_t creator_os;
    uint32_t major_version;
    uint16_t reserved_uid;
    uint16_t reserved_gid;
    struct Extended{
        uint32_t first_available_inode;
        uint16_t inode_size;
        uint16_t superblock_group_no;
        uint32_t optional_features;
        uint32_t required_features;
        uint32_t rofeatures;
        unsigned char fsid[16];
        char volume_name[16];
        char last_mount_path[64];
        uint32_t compression_used;
        uint8_t file_preallocate_blocks;
        uint8_t dir_preallocate_blocks;
        uint16_t unused;
        unsigned char journelid[16];
        uint32_t journel_inode;
        uint32_t journel_device;
        uint32_t orphan_list_head;
    } extended[];
} __attribute__((aligned(1024))) Ext2Superblock;



typedef struct {
    uint32_t block_usage_addr;
    uint32_t inode_usage_addr;
    uint32_t inode_table_addr;
    uint16_t unallocated_blocks;
    uint16_t unallocated_inodes;
    uint16_t dir_count;
    unsigned char reserved[14];
}Ext2BlockGroupHeader;

typedef struct {
    uint16_t type_and_permissions;
    uint16_t in_uid;
    uint32_t size_low;
    uint32_t atime;
    uint32_t ctime;
    uint32_t mtime;
    uint32_t dtime;
    
} Ext2INodeBlock;

#endif