#ifndef KRISVERS_KOBJ_H
#define KRISVERS_KOBJ_H

#define KOBJ_FLAG_FACE 0x0001
#define KOBJ_FLAG_NORMAL 0x0002
#define KOBJ_FLAG_PER_FACE_NORMAL 0x0004
#define KOBJ_FLAG_UV 0x0008
#define KOBJ_FLAG_PER_FACE_UV 0x0010

typedef enum KObjSuccessEnum {
	KOBJ_ERROR_GENERIC = -1,
	KOBJ_SUCCESS = 0,
} kobj_success_enum;

/*
  kobj_parse():

  Required arguments:
    void * buffer (a pointer to a buffer which you would like to parse)
    unsigned long long int length (length of the buffer you'd like to parse)

  Optional output arguments:
    unsigned int * out_flags (a pointer to an unsigned int that holds flag values)
    float * out_vertices (a pointer to an *already* allocated buffer where the vertices will be stored)
    unsigned long long int * out_vertices_length (a pointer to a ULL where the length of the vertices array will be stored)
*/
kobj_success_enum kobj_parse(void * buffer, unsigned long long int length, unsigned int * out_flags, float * out_vertices, unsigned long long int * out_vertices_length, unsigned int * out_indices, unsigned long long int * out_indices_length, float * out_normals, unsigned long long int * out_normals_length, float * out_uv, unsigned long long int * out_uv_length);

#endif
