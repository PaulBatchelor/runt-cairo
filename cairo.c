#include <cairo/cairo.h>
#include <stdlib.h>
#include <stdio.h>
#include <runt.h>

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

static runt_int rproc_image_surface_create(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    runt_float w, h;
    cairo_surface_t *surface;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    h = s->f;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    w = s->f;

    rc = runt_ppush(vm, &s);
    RUNT_ERROR_CHECK(rc);
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h);
    s->p = runt_mk_cptr(vm, surface);

    return RUNT_OK;
}

static runt_int rproc_surface_destroy(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    cairo_surface_t *surface;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    surface = runt_to_cptr(s->p);
    cairo_surface_destroy(surface);
    return RUNT_OK;
}

static runt_int rproc_create(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    cairo_t *cr = NULL;
    cairo_surface_t *surface;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    surface = runt_to_cptr(s->p);

    rc = runt_ppush(vm, &s);
    RUNT_ERROR_CHECK(rc);
    cr = cairo_create(surface);
    s->p = runt_mk_cptr(vm, cr);

    return RUNT_OK;
}

static runt_int rproc_destroy(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    cairo_t *cr = NULL;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    cr = runt_to_cptr(s->p);
    cairo_destroy(cr);
    free(cr);
    return RUNT_OK;
}

static runt_int rproc_surface_write_to_png(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    const char *filename;
    cairo_surface_t *surface;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    surface = runt_to_cptr(s->p);

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    filename = runt_to_string(s->p);

    cairo_surface_write_to_png(surface, filename);

    return RUNT_OK;
}

static runt_int rproc_set_source_rgb (runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    runt_float r, g, b;
    cairo_t *cr;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    cr = runt_to_cptr(s->p);
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    b = s->f;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    g = s->f;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    r = s->f;

    cairo_set_source_rgb(cr, r, g, b);

    return RUNT_OK;
}

static runt_int rproc_fill(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    cairo_t *cr;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    cr = runt_to_cptr(s->p);

    cairo_fill(cr);
    return RUNT_OK;
}

static runt_int rproc_fill_preserve(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    cairo_t *cr;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    cr = runt_to_cptr(s->p);

    cairo_fill_preserve(cr);
    return RUNT_OK;
}

static runt_int rproc_paint(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    cairo_t *cr;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    cr = runt_to_cptr(s->p);

    cairo_paint(cr);
    return RUNT_OK;
}

static runt_int rproc_stroke(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    cairo_t *cr;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    cr = runt_to_cptr(s->p);

    cairo_stroke(cr);
    return RUNT_OK;
}

static runt_int rproc_stroke_preserve(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    cairo_t *cr;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    cr = runt_to_cptr(s->p);

    cairo_stroke_preserve(cr);
    return RUNT_OK;
}

static runt_int rproc_set_line_width(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    runt_float width;
    cairo_t *cr;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    cr = runt_to_cptr(s->p);

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    width = s->f;
    
    cairo_set_line_width(cr, width);
    return RUNT_OK;
}

static runt_int rproc_rectangle(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    runt_float x, y, w, h;
    cairo_t *cr;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    cr = runt_to_cptr(s->p);
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    h = s->f;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    w = s->f;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    y = s->f;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    x = s->f;

    cairo_rectangle(cr, x, y, w, h);
    return RUNT_OK;
}

static runt_int rproc_arc(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    runt_float x, y, r, a1, a2;
    cairo_t *cr;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    cr = runt_to_cptr(s->p);
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    a2 = s->f;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    a1 = s->f;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    r = s->f;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    y = s->f;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    x = s->f;

    cairo_arc(cr, x, y, r, a1 * M_PI, a2 * M_PI);
    return RUNT_OK;
}

runt_int runt_load_cairo(runt_vm *vm)
{
    runt_word_define(vm, 
        "cairo_image_surface_create", 
        26, 
        rproc_image_surface_create);

    runt_word_define(vm, 
        "cairo_surface_destroy", 
        21, 
        rproc_surface_destroy);
    runt_word_define(vm, 
        "cairo_create", 
        12, 
        rproc_create);
    
    runt_word_define(vm, 
        "cairo_destroy", 
        13, 
        rproc_destroy);
    
    runt_word_define(vm, 
        "cairo_surface_write_to_png", 
        26, 
        rproc_surface_write_to_png);
    
    runt_word_define(vm, 
        "cairo_set_source_rgb", 
        20, 
        rproc_set_source_rgb);
    
    runt_word_define(vm, 
        "cairo_fill", 
        10, 
        rproc_fill);
    
    runt_word_define(vm, 
        "cairo_fill_preserve", 
        19, 
        rproc_fill_preserve);
    
    runt_word_define(vm, 
        "cairo_stroke", 
        12, 
        rproc_stroke);
    
    runt_word_define(vm, 
        "cairo_stroke_preserve", 
        21, 
        rproc_stroke_preserve);
    
    runt_word_define(vm, 
        "cairo_paint", 
        11, 
        rproc_paint);

    runt_word_define(vm, 
        "cairo_rectangle", 
        15, 
        rproc_rectangle);
    
    runt_word_define(vm, 
        "cairo_set_line_width", 
        20, 
        rproc_set_line_width);
    
    runt_word_define(vm, 
        "cairo_arc", 
        9, 
        rproc_arc);

    return RUNT_OK;
}
