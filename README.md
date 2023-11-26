# kobj
Parser for a subset of Wavefront OBJ written in C99

### supported:
- `v` any dimension vertex positions
- `vn` per-vertex normals (per-face normals may be supported later)
- `vt` vertex texture UVs
- `f` supports only face indices (`f v1 v2 v3` not `f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3`)
