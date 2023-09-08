#include "kobj.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

kobj_success_enum kobj_parse(void * buffer, unsigned long long int length, unsigned int * out_flags, float * out_vertices, unsigned long long int * out_vertices_length, unsigned int * out_indices, unsigned long long int * out_indices_length, float * out_normals, unsigned long long int * out_normals_length, float * out_uv, unsigned long long int * out_uv_length) {
	unsigned long long int i = 0;
	unsigned long long int current = 0;
	int state = 0;
	char started = 0;
	char c = ' ';
	char prevc = ' ';
	char nextc = ' ';

	float current_float = 0;
	unsigned long long int current_llu = 0;

	struct {
		unsigned long long int length;
		char * start;
	} word;

	if (out_flags != NULL) {
		*out_flags = 0;
	}

	while (i < length) {
		if (i + 1 < length) {
			nextc = ((char *) buffer)[i + 1];
		}

		prevc = c;
		c = ((char *) buffer)[i];

		switch (started) {
			case 1:
				if ((isalnum(c) && !isalpha(c)) || c == '-') {
					word.start = &((char *) buffer)[i];
					word.length = 1;
					started = 2;
				}
				goto kobj_parse_next;
			case 2:
				++word.length;
				if (c == '\n') {
					current_float = strtof(word.start, NULL);
					if (out_vertices != NULL) {
						out_vertices[current] = current_float;
					}
					++current;
					word.start = NULL;
					started = 0;
				}
				if (c == ' ') {
					current_float = strtof(word.start, NULL);
					if (out_vertices != NULL) {
						out_vertices[current] = current_float;
					}
					++current;
					word.start = NULL;
					started = 1;
				}
				goto kobj_parse_next;
			case 3:
				if ((isalnum(c) && !isalpha(c)) || c == '-') {
					word.start = &((char *) buffer)[i];
					word.length = 1;
					started = 4;
				}
				goto kobj_parse_next;
			case 4:
				++word.length;
				if (c == '\n') {
					current_float = strtof(word.start, NULL);
					if (out_normals != NULL) {
						out_normals[current] = current_float;
					}
					++current;
					word.start = NULL;
					started = 0;
				}
				if (c == ' ') {
					current_float = strtof(word.start, NULL);
					if (out_normals != NULL) {
						out_normals[current] = current_float;
					}
					++current;
					word.start = NULL;
					started = 3;
				}
				goto kobj_parse_next;
			case 5:
				if ((isalnum(c) && !isalpha(c))) {
					word.start = &((char *) buffer)[i];
					word.length = 1;
					started = 6;
				}
				goto kobj_parse_next;
			case 6:
				++word.length;
				if (c == '\n') {
					current_float = strtof(word.start, NULL);
					if (out_uv != NULL) {
						out_uv[current] = current_float;
					}
					++current;
					word.start = NULL;
					started = 0;
				}
				if (c == ' ') {
					current_float = strtof(word.start, NULL);
					if (out_uv != NULL) {
						out_uv[current] = current_float;
					}
					++current;
					word.start = NULL;
					started = 5;
				}
				goto kobj_parse_next;
			case 7:
				if ((isalnum(c) && !isalpha(c))) {
					word.start = &((char *) buffer)[i];
					word.length = 1;
					started = 8;
				}
				goto kobj_parse_next;
			case 8:
				++word.length;
				if (c == '\n') {
					current_llu = strtoull(word.start, NULL, 10);
					if (out_indices != NULL) {
						out_indices[current] = current_llu;
					}
					++current;
					word.start = NULL;
					started = 0;
				}
				if (c == ' ') {
					current_llu = strtoull(word.start, NULL, 10);
					if (out_indices != NULL) {
						out_indices[current] = current_llu;
					}
					++current;
					word.start = NULL;
					started = 7;
				}
				goto kobj_parse_next;
			default:
			case 0:
				break;
		}

		if (c == '\n') {
			started = 0;
		}
		if (c == 'v' && nextc == ' ') {
			if (state != 1) {
				current = 0;
			}
			state = 1;
			if (out_vertices_length != NULL) {
				++(*out_vertices_length);
			}

			started = 1;
		}
		if (c == 'v' && nextc == 'n') {
			if (out_flags != NULL) {
				*out_flags |= KOBJ_FLAG_NORMAL;
			}

			if (state != 2) {
				current = 0;
			}
			state = 2;
			if (out_normals_length != NULL) {
				++(*out_normals_length);
			}

			started = 3;
		}
		if (c == 'v' && nextc == 't') {
			if (out_flags != NULL) {
				*out_flags |= KOBJ_FLAG_UV;
			}
			if (state != 3) {
				current = 0;
			}
			state = 3;
			if (out_uv_length != NULL) {
				++(*out_uv_length);
			}

			started = 5;
		}
		if (c == 'f' && nextc == ' ') {
			if (out_flags != NULL) {
				*out_flags |= KOBJ_FLAG_FACE;
			}

			if (state != 4) {
				current = 0;
			}
			state = 4;
			if (out_indices_length != NULL) {
				++(*out_indices_length);
			}

			started = 7;
		}
		if (c == ' ') {
			goto kobj_parse_next;
		}

	kobj_parse_next:
		++i;
	}

	return KOBJ_SUCCESS;
}
