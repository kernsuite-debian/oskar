#include <oskar_dierckx_fprpsp.h>

#ifdef __cplusplus
extern "C" {
#endif

void oskar_dierckx_fprpsp(int nt, int np, const double *co, const double *si,
        double *c, double *f, int ncoff)
{
    /* Local variables */
    int i, j, k, l, ii, np4, nt4, npp, ncof;
    double c1, c2, c3, cn;

    /* Parameter adjustments */
    --si;
    --co;
    --f;
    --c;

    /* Function Body */
    nt4 = nt - 4;
    np4 = np - 4;
    npp = np4 - 3;
    ncof = npp * (nt4 - 4) + 6;
    c1 = c[1];
    cn = c[ncof];
    j = ncoff;
    for (i = 1; i <= np4; ++i)
    {
        f[i] = c1;
        f[j] = cn;
        --j;
    }
    i = np4;
    j = 1;
    for (l = 3; l <= nt4; ++l)
    {
        ii = i;
        if (l == 3 || l == nt4)
        {
            if (l == nt4) c1 = cn;
            c2 = c[j + 1];
            c3 = c[j + 2];
            j += 2;
            for (k = 1; k <= npp; ++k)
            {
                ++i;
                f[i] = c1 + c2 * co[k] + c3 * si[k];
            }
        }
        else
        {
            for (k = 1; k <= npp; ++k)
            {
                ++i;
                ++j;
                f[i] = c[j];
            }
        }
        for (k = 1; k <= 3; ++k)
        {
            ++ii;
            ++i;
            f[i] = f[ii];
        }
    }
    for (i = 1; i <= ncoff; ++i)
    {
        c[i] = f[i];
    }
}

#ifdef __cplusplus
}
#endif

