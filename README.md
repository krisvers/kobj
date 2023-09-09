# kobj
Parser for a subset of Wavefront OBJ written in C99

### supported:
- `v` any dimension vertex positions
- `vn` per-vertex normals (per-face normals may be supported later)
- `vt` vertex texture UVs
- `f` supports only face indices (`f v1 v2 v3` not `f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3`)

### usage example in C (C standard libraries error checking omitted for brevity)
```c
#include "kobj/kobj.h"
#include <stdio.h>
#include <stdlib.h>

void foo() {
  FILE * fp = fopen("model.obj", "rb");
  unsigned long long int length = 0;
  fseek(fp, 0L, SEEK_END);
  length = ftell(fp);
  fseek(fp, 0L, SEEK_SET);
  char * buffer = malloc(length);
  fread(buffer, 1, length, fp);
  fclose(fp);

  unsigned int flags;
  unsigned long long int vertex_count;
  unsigned long long int index_count;
  unsigned long long int normal_count;
  unsigned long long int uv_count;

  // retrieving lengths of the arrays for future allocation
  if (kobj_parse(
        buffer, length,
        &flags,
        NULL, &vertex_count,
        NULL, &index_count,
        NULL, &normal_count,
        NULL, &uv_count
  ) < KOBJ_SUCCESS) {
    // kobj_parse error
    return 1;
  }

  float * vertices = malloc(sizeof(float) * vertex_count * 3);
  unsigned int indices = malloc(sizeof(unsigned int) * index_count * 3);
  float * normals = malloc(sizeof(float) * normal_count * 3);
  float * uvs = malloc(sizeof(float) * uv_count * 2);

  // loading values into the already allocated arrays
  if (kobj_parse(
        buffer, length,
        NULL,
        vertices, NULL,
        indices, NULL,
        normals, NULL,
        uvs, NULL
  ) < KOBJ_SUCCESS) {
    // kobj_parse error
    return 2;
  }

  // do stuff with the arrays
}
```

### usage example in C++
```c++
#include "kobj/kobj.h"
#include <iostream>
#include <fstream>
#include <vector>

void foo() {
  std::ifstream file("model.obj");
  std::string string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

  unsigned int flags;
  std::vector<float> vertices;
  std::vector<unsigned int> indices;
  std::vector<float> normals;
  std::vector<float> uvs;
  {
    unsigned long long int vertex_count;
    unsigned long long int index_count;
    unsigned long long int normal_count;
    unsigned long long int uv_count;

    // retrieve lengths
    if (kobj_parse(
          buffer, length,
          &flags,
          NULL, &vertex_count,
          NULL, &index_count,
          NULL, &normal_count,
          NULL, &uv_count
    ) < KOBJ_SUCCESS) {
      // kobj_parse error
      return 1;
    }

    // reserve space for the vectors
    vertices.reserve(vertex_count);
    indices.reserve(index_count);
    normals.reserve(normal_count);
    uvs.reserve(uv_count);

    // load data
    if (kobj_parse(
          buffer, length,
          NULL,
          vertices.data(), NULL,
          indices.data(), NULL,
          normals.data(), NULL,
          uvs.data(), NULL
    ) < KOBJ_SUCCESS) {
      // kobj_parse error
      return 2;
    }
  }

  // do stuff
}
