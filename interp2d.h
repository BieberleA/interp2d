#ifndef __INTERP_2D_H__
#define __INTERP_2D_H__

#include <gsl/gsl_interp.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const char* name;
    unsigned int min_size;
    void* (*alloc)(size_t size);
    int (*init)(void*, const double xa[], const double ya[], const double za[], size_t xsize, size_t ysize);
    int (*eval)(const void*, const double xa[], const double ya[], const double za[], size_t xsize, size_t ysize, double x, double y, gsl_interp_accel*, gsl_interp_accel*, double* z);
//     int (*eval_deriv) (const void*, const double xa[], const double ya[], const double za[][], size_t size, double x, double y, interp2d_accel*, double* z_p);
//     int (*eval_deriv2) (const void*, const double xa[], const double ya[], const double za[][], size_t size, double x, double y, interp2d_accel*, double* z_pp);
//     int (*integ) (const void*, const double xa[], const double ya[], const double za[][], size_t size, interp2d_accel*, double xa, double xb, double ya, double yb, double* result);
    void (*free)(void*);
} interp2d_type;

typedef struct {
    const interp2d_type* type;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    size_t xsize;
    size_t ysize;
    void* state;
} interp2d;

GSL_VAR const interp2d_type* interp2d_bilinear;

size_t interp2d_type_min_size(const interp2d_type* T);
size_t interp2d_min_size(const interp2d* interp);
const char* interp2d_name(const interp2d* interp);

interp2d* interp2d_alloc(const interp2d_type* T, size_t xsize, size_t ysize);
int interp2d_init(interp2d* interp, const double xa[], const double ya[], const double za[], size_t xsize, size_t ysize);
void interp2d_free(interp2d* interp);

double interp2d_eval(const interp2d* interp, const double xarr[], const double yarr[], const double zarr[], const double x, const double y, gsl_interp_accel* xa, gsl_interp_accel* ya);

#define INDEX_2D(xi, yi, xsize, ysize) (xi) * (xsize) + (yi)

#ifdef __cplusplus
}
#endif

#endif
