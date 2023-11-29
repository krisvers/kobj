# kobj
Parser for a subset of Wavefront OBJ written in C99

### supported:
- the basics required for vertices, normals, tex coordinates, and faces

### unsupported:
- mtl
- listing vertices or normals or tex coords not in one go
  - example
    supported:
    ```obj
    v 1 1 1
    v 1 0 1
    v 0 1 0
    ...
    v 1 1 0

    vn 1 0 1
    ...
    vn 0 1 1

    vt 0 0
    vt 1 0
    ...
    vt 1 1
    ```
    unsupported:
    ```obj
    v 1 1 1
    vn 1 0 1
    vt 0 1
    ...
    v 1 1 0

    v 1 0 1
    ...
    vt 0 1

    vt 0 0
    vn 1 0 1
    ...
    vn 1 1 0
    ```
