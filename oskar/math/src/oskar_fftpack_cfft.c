/*
 * Copyright (c) 2004 the University Corporation for
 * Atmospheric Research ("UCAR").
 * All rights reserved. Developed by NCAR's Computational and Information
 * Systems Laboratory, UCAR, www2.cisl.ucar.edu.
 *
 * Redistribution and use of the Software in source and binary forms,
 * with or without modification, is permitted provided that the following
 * conditions are met:
 * 1. Neither the names of NCAR's Computational and Information Systems
 *    Laboratory, the University Corporation for Atmospheric Research, nor the
 *    names of its sponsors or contributors may be used to endorse or promote
 *    products derived from this Software without specific prior written
 *    permission.
 * 2. Redistributions of source code must retain the above copyright
 *    notices, this list of conditions, and the disclaimer below.
 * 3. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions, and the disclaimer below in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING, BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS WITH
 * THE SOFTWARE.
 */

/*
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *                                                               *
     *                  copyright (c) 2011 by UCAR                   *
     *       University Corporation for Atmospheric Research         *
     *                      all rights reserved                      *
     *                     FFTPACK  version 5.1                      *
     *                 A Fortran Package of Fast Fourier             *
     *                Subroutines and Example Programs               *
     *                             by                                *
     *               Paul Swarztrauber and Dick Valent               *
     *                             of                                *
     *         the National Center for Atmospheric Research          *
     *                Boulder, Colorado  (80307)  U.S.A.             *
     *                   which is sponsored by                       *
     *              the National Science Foundation                  *
     *                                                               *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

/*
 * This C translation from the original Fortran sources is also covered by
 * the Modified BSD license, as follows:
 *
 * Copyright (c) 2016, The University of Oxford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Oxford nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <math.h>
#include "math/oskar_fftpack_cfft.h"

#define min(a,b) ((a) < (b) ? (a) : (b))

static void cfftmb(const int lot, const int jump, const int n, const int inc,
        double *c, double *wsave, double *work);
static void cfftmf(const int lot, const int jump, const int n, const int inc,
        double *c, double *wsave, double *work);
static void cfftmi(const int n, double *wsave);
static void cmfm1b(const int lot, const int jump, const int n, const int inc,
        double *restrict c, double *restrict ch, const double *restrict wa,
        const double fnf, const double *restrict fac);
static void cmfm1f(const int lot, const int jump, const int n, const int inc,
        double *restrict c, double *restrict ch, const double *restrict wa,
        const double fnf, const double *restrict fac);
static void mcfti1(const int n, double *restrict wa, double *restrict fnf,
        double *restrict fac);

static void cmf2kb(const int lot, const int ido, const int l1, const int na,
        double *restrict cc, const int im1, const int in1, double *restrict ch,
        const int im2, const int in2, const double *restrict wa);
static void cmf3kb(const int lot, const int ido, const int l1, const int na,
        double *restrict cc, const int im1, const int in1, double *restrict ch,
        const int im2, const int in2, const double *restrict wa);
static void cmf4kb(const int lot, const int ido, const int l1, const int na,
        double *restrict cc, const int im1, const int in1, double *restrict ch,
        const int im2, const int in2, const double *restrict wa);
static void cmf5kb(const int lot, const int ido, const int l1, const int na,
        double *restrict cc, const int im1, const int in1, double *restrict ch,
        const int im2, const int in2, const double *restrict wa);
static void cmfgkb(const int lot, const int ido, const int ip, const int l1,
        const int lid, const int na, double *restrict cc, double *restrict cc1,
        const int im1, const int in1, double *restrict ch, double *restrict ch1,
        const int im2, const int in2, const double *restrict wa);

static void cmf2kf(const int lot, const int ido, const int l1, const int na,
        double *restrict cc, const int im1, const int in1, double *restrict ch,
        const int im2, const int in2, const double *restrict wa);
static void cmf3kf(const int lot, const int ido, const int l1, const int na,
        double *restrict cc, const int im1, const int in1, double *restrict ch,
        const int im2, const int in2, const double *restrict wa);
static void cmf4kf(const int lot, const int ido, const int l1, const int na,
        double *restrict cc, const int im1, const int in1, double *restrict ch,
        const int im2, const int in2, const double *restrict wa);
static void cmf5kf(const int lot, const int ido, const int l1, const int na,
        double *restrict cc, const int im1, const int in1, double *restrict ch,
        const int im2, const int in2, const double *restrict wa);
static void cmfgkf(const int lot, const int ido, const int ip, const int l1,
        const int lid, const int na, double *restrict cc, double *restrict cc1,
        const int im1, const int in1, double *restrict ch, double *restrict ch1,
        const int im2, const int in2, const double *restrict wa);

static void tables(const int ido, const int ip, double *restrict wa);
static void factor(const int n, int *nf, double *fac);


void oskar_fftpack_cfft2b(const int ldim, const int l, const int m,
        double *c, double *wsave, double *work)
{
    /* Transform X lines of C array */
    cfftmb(l, 1, m, ldim, c,
            &wsave[(l << 1) + (int) (log((double) l) / log(2.0)) + 2], work);

    /* Transform Y lines of C array */
    cfftmb(m, ldim, l, 1, c, wsave, work);
}


void oskar_fftpack_cfft2f(const int ldim, const int l, const int m,
        double *c, double *wsave, double *work)
{
    /* Transform X lines of C array */
    cfftmf(l, 1, m, ldim, c,
            &wsave[(l << 1) + (int) (log((double) l) / log(2.0)) + 2], work);

    /* Transform Y lines of C array */
    cfftmf(m, ldim, l, 1, c, wsave, work);
}


void oskar_fftpack_cfft2i(const int l, const int m, double *wsave)
{
    cfftmi(l, wsave);
    cfftmi(m, &wsave[(l << 1) + (int) (log((double) l) / log(2.0)) + 2]);
}


void cfftmb(const int lot, const int jump, const int n, const int inc,
        double *c, double *wsave, double *work)
{
    int iw1;
    if (n == 1) return;
    iw1 = n + n;
    cmfm1b(lot, jump, n, inc, c, work, wsave, wsave[iw1], &wsave[iw1 + 1]);
}


void cfftmf(const int lot, const int jump, const int n, const int inc,
        double *c, double *wsave, double *work)
{
    int iw1;
    if (n == 1) return;
    iw1 = n + n;
    cmfm1f(lot, jump, n, inc, c, work, wsave, wsave[iw1], &wsave[iw1 + 1]);
}


void cfftmi(const int n, double *wsave)
{
    int iw1;
    if (n == 1) return;
    iw1 = n + n;
    mcfti1(n, wsave, &wsave[iw1], &wsave[iw1 + 1]);
}


void cmf2kb(const int lot, const int ido, const int l1, const int na,
        double *restrict cc, const int im1, const int in1, double *restrict ch,
        const int im2, const int in2, const double *restrict wa)
{
    int i, k, m1, m2, m1d, m2s, o1, o2, i1, i2;
    wa -= 1;
    cc -= 2 * (1 + in1 * (1 + l1 * (1 + ido)));
    ch -= 2 * (1 + in2 * (1 + l1 * 3));

    m1d = (lot - 1) * im1 + 1;
    m2s = 1 - im2;
    if (ido > 1 || na == 1)
    {
        double ti2, tr2, w1, w2;
        for (k = 1; k <= l1; ++k)
        {
            m2 = m2s;
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                m2 += im2;
                i1 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                i2 = (m1 + (k + (ido * 2 + 1) * l1) * in1) << 1;
                o1 = (m2 + (k + l1 * 3) * in2) << 1;
                o2 = (m2 + (k + l1 * 4) * in2) << 1;
                ch[o1]     = cc[i1] + cc[i2];
                ch[o2]     = cc[i1] - cc[i2];
                ch[o1 + 1] = cc[i1 + 1] + cc[i2 + 1];
                ch[o2 + 1] = cc[i1 + 1] - cc[i2 + 1];
            }
        }
        for (i = 2; i <= ido; ++i)
        {
            w1 = wa[i];
            w2 = wa[i + ido];
            for (k = 1; k <= l1; ++k)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m1 + (k + (i + ido) * l1) * in1) << 1;
                    i2 = (m1 + (k + (i + ido * 2) * l1) * in1) << 1;
                    o1 = (m2 + (k + (i * 2 + 1) * l1) * in2) << 1;
                    o2 = (m2 + (k + (i * 2 + 2) * l1) * in2) << 1;
                    ch[o1]     = cc[i1] + cc[i2];
                    tr2        = cc[i1] - cc[i2];
                    ch[o1 + 1] = cc[i1 + 1] + cc[i2 + 1];
                    ti2        = cc[i1 + 1] - cc[i2 + 1];
                    ch[o2 + 1] = w1 * ti2 + w2 * tr2;
                    ch[o2]     = w1 * tr2 - w2 * ti2;
                }
            }
        }
    }
    else
    {
        double chold1, chold2;
        for (k = 1; k <= l1; ++k)
        {
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                i1 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                i2 = (m1 + (k + (ido * 2 + 1) * l1) * in1) << 1;
                chold1     = cc[i1] + cc[i2];
                cc[i2]     = cc[i1] - cc[i2];
                cc[i1]     = chold1;
                chold2     = cc[i1 + 1] + cc[i2 + 1];
                cc[i2 + 1] = cc[i1 + 1] - cc[i2 + 1];
                cc[i1 + 1] = chold2;
            }
        }
    }
}


void cmf2kf(const int lot, const int ido, const int l1, const int na,
        double *restrict cc, const int im1, const int in1, double *restrict ch,
        const int im2, const int in2, const double *restrict wa)
{
    int i, k, m1, m2, m1d, m2s, o1, o2, i1, i2;
    wa -= 1 + (ido << 1);
    cc -= 2 * (1 + in1 * (1 + l1 * (1 + ido)));
    ch -= 2 * (1 + in2 * (1 + l1 * 3));

    m1d = (lot - 1) * im1 + 1;
    m2s = 1 - im2;
    if (ido > 1)
    {
        double ti2, tr2, w1, w2;
        for (k = 1; k <= l1; ++k)
        {
            m2 = m2s;
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                m2 += im2;
                i1 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                i2 = (m1 + (k + ((ido << 1) + 1) * l1) * in1) << 1;
                o1 = (m2 + (k + l1 * 3) * in2) << 1;
                o2 = (m2 + (k + (l1 << 2)) * in2) << 1;
                ch[o1]     = cc[i1] + cc[i2];
                ch[o2]     = cc[i1] - cc[i2];
                ch[o1 + 1] = cc[i1 + 1] + cc[i2 + 1];
                ch[o2 + 1] = cc[i1 + 1] - cc[i2 + 1];
            }
        }
        for (i = 2; i <= ido; ++i)
        {
            w1 = wa[i + ido * 2];
            w2 = wa[i + ido * 3];
            for (k = 1; k <= l1; ++k)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m1 + (k + (i + ido) * l1) * in1) << 1;
                    i2 = (m1 + (k + (i + (ido << 1)) * l1) * in1) << 1;
                    o1 = (m2 + (k + ((i << 1) + 1) * l1) * in2) << 1;
                    o2 = (m2 + (k + ((i << 1) + 2) * l1) * in2) << 1;
                    ch[o1]     = cc[i1] + cc[i2];
                    tr2        = cc[i1] - cc[i2];
                    ch[o1 + 1] = cc[i1 + 1] + cc[i2 + 1];
                    ti2        = cc[i1 + 1] - cc[i2 + 1];
                    ch[o2 + 1] = w1 * ti2 - w2 * tr2;
                    ch[o2]     = w1 * tr2 + w2 * ti2;
                }
            }
        }
    }
    else
    {
        double sn, chold1, chold2;
        sn = 1. / (double) (l1 << 1);
        if (na == 1)
        {
            for (k = 1; k <= l1; ++k)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                    i2 = (m1 + (k + ((ido << 1) + 1) * l1) * in1) << 1;
                    o1 = (m2 + (k + l1 * 3) * in2) << 1;
                    o2 = (m2 + (k + (l1 << 2)) * in2) << 1;
                    ch[o1]     = sn * (cc[i1] + cc[i2]);
                    ch[o2]     = sn * (cc[i1] - cc[i2]);
                    ch[o1 + 1] = sn * (cc[i1 + 1] + cc[i2 + 1]);
                    ch[o2 + 1] = sn * (cc[i1 + 1] - cc[i2 + 1]);
                }
            }
        }
        else
        {
            for (k = 1; k <= l1; ++k)
            {
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    i1 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                    i2 = (m1 + (k + ((ido << 1) + 1) * l1) * in1) << 1;
                    chold1     = sn * (cc[i1] + cc[i2]);
                    cc[i2]     = sn * (cc[i1] - cc[i2]);
                    cc[i1]     = chold1;
                    chold2     = sn * (cc[i1 + 1] + cc[i2 + 1]);
                    cc[i2 + 1] = sn * (cc[i1 + 1] - cc[i2 + 1]);
                    cc[i1 + 1] = chold2;
                }
            }
        }
    }
}


void cmf3kb(const int lot, const int ido, const int l1, const int na,
        double *restrict cc, const int im1, const int in1, double *restrict ch,
        const int im2, const int in2, const double *restrict wa)
{
    static const double taur = -.5;
    static const double taui = .866025403784439;
    int i, k, m1, m2, m1d, m2s, o1, o2, o3, i1, i2, i3;
    double ci2, ci3, cr2, cr3, di2, di3, dr2, dr3, ti2, tr2;
    wa -= 1;
    cc -= 2 * (1 + in1 * (1 + l1 * (1 + ido)));
    ch -= 2 * (1 + in2 * (1 + (l1 << 2)));

    m1d = (lot - 1) * im1 + 1;
    m2s = 1 - im2;
    if (ido > 1 || na == 1)
    {
        double w1, w2, w3, w4;
        for (k = 1; k <= l1; ++k)
        {
            m2 = m2s;
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                m2 += im2;
                i1 = (m1 + (k + (ido * 2 + 1) * l1) * in1) << 1;
                i2 = (m1 + (k + (ido * 3 + 1) * l1) * in1) << 1;
                i3 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                o1 = (m2 + (k + l1 * 4) * in2) << 1;
                o2 = (m2 + (k + l1 * 5) * in2) << 1;
                o3 = (m2 + (k + l1 * 6) * in2) << 1;
                tr2        = cc[i1] + cc[i2];
                cr2        = cc[i3] + taur * tr2;
                ch[o1]     = cc[i3] + tr2;
                ti2        = cc[i1 + 1] + cc[i2 + 1];
                ci2        = cc[i3 + 1] + taur * ti2;
                ch[o1 + 1] = cc[i3 + 1] + ti2;
                cr3        = taui * (cc[i1] - cc[i2]);
                ci3        = taui * (cc[i1 + 1] - cc[i2 + 1]);
                ch[o2]     = cr2 - ci3;
                ch[o3]     = cr2 + ci3;
                ch[o2 + 1] = ci2 + cr3;
                ch[o3 + 1] = ci2 - cr3;
            }
        }
        for (i = 2; i <= ido; ++i)
        {
            w1 = wa[i];
            w2 = wa[i + ido];
            w3 = wa[i + ido * 2];
            w4 = wa[i + ido * 3];
            for (k = 1; k <= l1; ++k)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m1 + (k + (i + ido * 2) * l1) * in1) << 1;
                    i2 = (m1 + (k + (i + ido * 3) * l1) * in1) << 1;
                    i3 = (m1 + (k + (i + ido) * l1) * in1) << 1;
                    o1 = (m2 + (k + (i * 3 + 1) * l1) * in2) << 1;
                    o2 = (m2 + (k + (i * 3 + 2) * l1) * in2) << 1;
                    o3 = (m2 + (k + (i * 3 + 3) * l1) * in2) << 1;
                    tr2        = cc[i1] + cc[i2];
                    cr2        = cc[i3] + taur * tr2;
                    ch[o1]     = cc[i3] + tr2;
                    ti2        = cc[i1 + 1] + cc[i2 + 1];
                    ci2        = cc[i3 + 1] + taur * ti2;
                    ch[o1 + 1] = cc[i3 + 1] + ti2;
                    cr3        = taui * (cc[i1] - cc[i2]);
                    ci3        = taui * (cc[i1 + 1] - cc[i2 + 1]);
                    dr2        = cr2 - ci3;
                    dr3        = cr2 + ci3;
                    di2        = ci2 + cr3;
                    di3        = ci2 - cr3;
                    ch[o2 + 1] = w1 * di2 + w3 * dr2;
                    ch[o2]     = w1 * dr2 - w3 * di2;
                    ch[o3 + 1] = w2 * di3 + w4 * dr3;
                    ch[o3]     = w2 * dr3 - w4 * di3;
                }
            }
        }
    }
    else
    {
        for (k = 1; k <= l1; ++k)
        {
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                i1 = (m1 + (k + ((ido << 1) + 1) * l1) * in1) << 1;
                i2 = (m1 + (k + (ido * 3 + 1) * l1) * in1) << 1;
                i3 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                tr2        = cc[i1] + cc[i2];
                cr2        = cc[i3] + taur * tr2;
                cc[i3]     += tr2;
                ti2        = cc[i1 + 1] + cc[i2 + 1];
                ci2        = cc[i3 + 1] + taur * ti2;
                cc[i3 + 1] += ti2;
                cr3        = taui * (cc[i1] - cc[i2]);
                ci3        = taui * (cc[i1 + 1] - cc[i2 + 1]);
                cc[i1]     = cr2 - ci3;
                cc[i2]     = cr2 + ci3;
                cc[i1 + 1] = ci2 + cr3;
                cc[i2 + 1] = ci2 - cr3;
            }
        }
    }
}


void cmf3kf(const int lot, const int ido, const int l1, const int na,
        double *restrict cc, const int im1, const int in1, double *restrict ch,
        const int im2, const int in2, const double *restrict wa)
{
    static const double taur = -.5;
    static const double taui = -.866025403784439;
    int i, k, m1, m2, m1d, m2s, o1, o2, o3, i1, i2, i3;
    double sn, ci2, ci3, di2, di3, cr2, cr3, dr2, dr3, ti2, tr2;
    wa -= 1;
    cc -= 2 * (1 + in1 * (1 + l1 * (1 + ido)));
    ch -= 2 * (1 + in2 * (1 + (l1 << 2)));

    m1d = (lot - 1) * im1 + 1;
    m2s = 1 - im2;
    if (ido > 1)
    {
        double w1, w2, w3, w4;
        for (k = 1; k <= l1; ++k)
        {
            m2 = m2s;
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                m2 += im2;
                i1 = (m1 + (k + (ido * 2 + 1) * l1) * in1) << 1;
                i2 = (m1 + (k + (ido * 3 + 1) * l1) * in1) << 1;
                i3 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                o1 = (m2 + (k + l1 * 4) * in2) << 1;
                o2 = (m2 + (k + l1 * 5) * in2) << 1;
                o3 = (m2 + (k + l1 * 6) * in2) << 1;
                tr2        = cc[i1] + cc[i2];
                cr2        = cc[i3] + taur * tr2;
                ch[o1]     = cc[i3] + tr2;
                ti2        = cc[i1 + 1] + cc[i2 + 1];
                ci2        = cc[i3 + 1] + taur * ti2;
                ch[o1 + 1] = cc[i3 + 1] + ti2;
                cr3        = taui * (cc[i1] - cc[i2]);
                ci3        = taui * (cc[i1 + 1] - cc[i2 + 1]);
                ch[o2]     = cr2 - ci3;
                ch[o3]     = cr2 + ci3;
                ch[o2 + 1] = ci2 + cr3;
                ch[o3 + 1] = ci2 - cr3;
            }
        }
        for (i = 2; i <= ido; ++i)
        {
            w1 = wa[i];
            w2 = wa[i + ido];
            w3 = wa[i + ido * 2];
            w4 = wa[i + ido * 3];
            for (k = 1; k <= l1; ++k)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m1 + (k + (i + ido * 2) * l1) * in1) << 1;
                    i2 = (m1 + (k + (i + ido * 3) * l1) * in1) << 1;
                    i3 = (m1 + (k + (i + ido) * l1) * in1) << 1;
                    o1 = (m2 + (k + (i * 3 + 1) * l1) * in2) << 1;
                    o2 = (m2 + (k + (i * 3 + 2) * l1) * in2) << 1;
                    o3 = (m2 + (k + (i * 3 + 3) * l1) * in2) << 1;
                    tr2        = cc[i1] + cc[i2];
                    cr2        = cc[i3] + taur * tr2;
                    ch[o1]     = cc[i3] + tr2;
                    ti2        = cc[i1 + 1] + cc[i2 + 1];
                    ci2        = cc[i3 + 1] + taur * ti2;
                    ch[o1 + 1] = cc[i3 + 1] + ti2;
                    cr3        = taui * (cc[i1] - cc[i2]);
                    ci3        = taui * (cc[i1 + 1] - cc[i2 + 1]);
                    dr2        = cr2 - ci3;
                    dr3        = cr2 + ci3;
                    di2        = ci2 + cr3;
                    di3        = ci2 - cr3;
                    ch[o2 + 1] = w1 * di2 - w3 * dr2;
                    ch[o2]     = w1 * dr2 + w3 * di2;
                    ch[o3 + 1] = w2 * di3 - w4 * dr3;
                    ch[o3]     = w2 * dr3 + w4 * di3;
                }
            }
        }
    }
    else
    {
        sn = 1. / (double) (l1 * 3);
        if (na == 1)
        {
            for (k = 1; k <= l1; ++k)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m1 + (k + (ido * 2 + 1) * l1) * in1) << 1;
                    i2 = (m1 + (k + (ido * 3 + 1) * l1) * in1) << 1;
                    i3 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                    o1 = (m2 + (k + l1 * 4) * in2) << 1;
                    o2 = (m2 + (k + l1 * 5) * in2) << 1;
                    o3 = (m2 + (k + l1 * 6) * in2) << 1;
                    tr2        = cc[i1] + cc[i2];
                    cr2        = cc[i3] + taur * tr2;
                    ch[o1]     = sn * (cc[i3] + tr2);
                    ti2        = cc[i1 + 1] + cc[i2 + 1];
                    ci2        = cc[i3 + 1] + taur * ti2;
                    ch[o1 + 1] = sn * (cc[i3 + 1] + ti2);
                    cr3        = taui * (cc[i1] - cc[i2]);
                    ci3        = taui * (cc[i1 + 1] - cc[i2 + 1]);
                    ch[o2]     = sn * (cr2 - ci3);
                    ch[o3]     = sn * (cr2 + ci3);
                    ch[o2 + 1] = sn * (ci2 + cr3);
                    ch[o3 + 1] = sn * (ci2 - cr3);
                }
            }
        }
        else
        {
            for (k = 1; k <= l1; ++k)
            {
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    i1 = (m1 + (k + (ido * 2 + 1) * l1) * in1) << 1;
                    i2 = (m1 + (k + (ido * 3 + 1) * l1) * in1) << 1;
                    i3 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                    tr2        = cc[i1] + cc[i2];
                    cr2        = cc[i3] + taur * tr2;
                    cc[i3]     = sn * (cc[i3] + tr2);
                    ti2        = cc[i1 + 1] + cc[i2 + 1];
                    ci2        = cc[i3 + 1] + taur * ti2;
                    cc[i3 + 1] = sn * (cc[i3 + 1] + ti2);
                    cr3        = taui * (cc[i1] - cc[i2]);
                    ci3        = taui * (cc[i1 + 1] - cc[i2 + 1]);
                    cc[i1]     = sn * (cr2 - ci3);
                    cc[i2]     = sn * (cr2 + ci3);
                    cc[i1 + 1] = sn * (ci2 + cr3);
                    cc[i2 + 1] = sn * (ci2 - cr3);
                }
            }
        }
    }
}


void cmf4kb(const int lot, const int ido, const int l1, const int na,
        double *restrict cc, const int im1, const int in1, double *restrict ch,
        const int im2, const int in2, const double *restrict wa)
{
    int i, k, m1, m2, m1d, m2s, o1, o2, o3, o4, i1, i2, i3, i4;
    double ci2, ci3, ci4, cr3, cr2, cr4;
    double ti1, ti2, ti3, ti4, tr1, tr2, tr3, tr4;
    wa -= 1;
    cc -= 2 * (1 + in1 * (1 + l1 * (1 + ido)));
    ch -= 2 * (1 + in2 * (1 + l1 * 5));

    m1d = (lot - 1) * im1 + 1;
    m2s = 1 - im2;
    if (ido > 1 || na == 1)
    {
        double w1, w2, w3, w4, w5, w6;
        for (k = 1; k <= l1; ++k)
        {
            m2 = m2s;
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                m2 += im2;
                i1 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                i2 = (m1 + (k + (ido * 3 + 1) * l1) * in1) << 1;
                i3 = (m1 + (k + (ido * 4 + 1) * l1) * in1) << 1;
                i4 = (m1 + (k + (ido * 2 + 1) * l1) * in1) << 1;
                o1 = (m2 + (k + l1 * 5) * in2) << 1;
                o2 = (m2 + (k + l1 * 7) * in2) << 1;
                o3 = (m2 + (k + l1 * 6) * in2) << 1;
                o4 = (m2 + (k + l1 * 8) * in2) << 1;
                ti1        = cc[i1 + 1] - cc[i2 + 1];
                ti2        = cc[i1 + 1] + cc[i2 + 1];
                tr4        = cc[i3 + 1] - cc[i4 + 1];
                ti3        = cc[i4 + 1] + cc[i3 + 1];
                tr1        = cc[i1] - cc[i2];
                tr2        = cc[i1] + cc[i2];
                ti4        = cc[i4] - cc[i3];
                tr3        = cc[i4] + cc[i3];
                ch[o1]     = tr2 + tr3;
                ch[o2]     = tr2 - tr3;
                ch[o1 + 1] = ti2 + ti3;
                ch[o2 + 1] = ti2 - ti3;
                ch[o3]     = tr1 + tr4;
                ch[o4]     = tr1 - tr4;
                ch[o3 + 1] = ti1 + ti4;
                ch[o4 + 1] = ti1 - ti4;
            }
        }
        for (i = 2; i <= ido; ++i)
        {
            w1 = wa[i];
            w2 = wa[i + ido];
            w3 = wa[i + ido * 2];
            w4 = wa[i + ido * 3];
            w5 = wa[i + ido * 4];
            w6 = wa[i + ido * 5];
            for (k = 1; k <= l1; ++k)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m1 + (k + (i + ido) * l1) * in1) << 1;
                    i2 = (m1 + (k + (i + ido * 3) * l1) * in1) << 1;
                    i3 = (m1 + (k + (i + ido * 2) * l1) * in1) << 1;
                    i4 = (m1 + (k + (i + ido * 4) * l1) * in1) << 1;
                    o1 = (m2 + (k + ((i << 2) + 1) * l1) * in2) << 1;
                    o2 = (m2 + (k + ((i << 2) + 2) * l1) * in2) << 1;
                    o3 = (m2 + (k + ((i << 2) + 3) * l1) * in2) << 1;
                    o4 = (m2 + (k + ((i << 2) + 4) * l1) * in2) << 1;
                    ti1        = cc[i1 + 1] - cc[i2 + 1];
                    ti2        = cc[i1 + 1] + cc[i2 + 1];
                    ti3        = cc[i3 + 1] + cc[i4 + 1];
                    tr4        = cc[i4 + 1] - cc[i3 + 1];
                    tr1        = cc[i1] - cc[i2];
                    tr2        = cc[i1] + cc[i2];
                    ti4        = cc[i3] - cc[i4];
                    tr3        = cc[i3] + cc[i4];
                    ch[o1]     = tr2 + tr3;
                    cr3        = tr2 - tr3;
                    ch[o1 + 1] = ti2 + ti3;
                    ci3        = ti2 - ti3;
                    cr2        = tr1 + tr4;
                    cr4        = tr1 - tr4;
                    ci2        = ti1 + ti4;
                    ci4        = ti1 - ti4;
                    ch[o2]     = w1 * cr2 - w4 * ci2;
                    ch[o2 + 1] = w1 * ci2 + w4 * cr2;
                    ch[o3]     = w2 * cr3 - w5 * ci3;
                    ch[o3 + 1] = w2 * ci3 + w5 * cr3;
                    ch[o4]     = w3 * cr4 - w6 * ci4;
                    ch[o4 + 1] = w3 * ci4 + w6 * cr4;
                }
            }
        }
    }
    else
    {
        for (k = 1; k <= l1; ++k)
        {
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                i1 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                i2 = (m1 + (k + (ido * 3 + 1) * l1) * in1) << 1;
                i3 = (m1 + (k + ((ido << 2) + 1) * l1) * in1) << 1;
                i4 = (m1 + (k + ((ido << 1) + 1) * l1) * in1) << 1;
                ti1        = cc[i1 + 1] - cc[i2 + 1];
                ti2        = cc[i1 + 1] + cc[i2 + 1];
                tr4        = cc[i3 + 1] - cc[i4 + 1];
                ti3        = cc[i4 + 1] + cc[i3 + 1];
                tr1        = cc[i1] - cc[i2];
                tr2        = cc[i1] + cc[i2];
                ti4        = cc[i4] - cc[i3];
                tr3        = cc[i4] + cc[i3];
                cc[i1]     = tr2 + tr3;
                cc[i2]     = tr2 - tr3;
                cc[i1 + 1] = ti2 + ti3;
                cc[i2 + 1] = ti2 - ti3;
                cc[i4]     = tr1 + tr4;
                cc[i3]     = tr1 - tr4;
                cc[i4 + 1] = ti1 + ti4;
                cc[i3 + 1] = ti1 - ti4;
            }
        }
    }
}


void cmf4kf(const int lot, const int ido, const int l1, const int na,
        double *restrict cc, const int im1, const int in1, double *restrict ch,
        const int im2, const int in2, const double *restrict wa)
{
    int i, k, m1, m2, m1d, m2s, o1, o2, o3, o4, i1, i2, i3, i4;
    double sn, ci2, ci3, ci4, cr3, cr2, cr4;
    double ti1, ti2, ti3, ti4, tr1, tr2, tr3, tr4;
    wa -= 1;
    cc -= 2 * (1 + in1 * (1 + l1 * (1 + ido)));
    ch -= 2 * (1 + in2 * (1 + l1 * 5));

    m1d = (lot - 1) * im1 + 1;
    m2s = 1 - im2;
    if (ido > 1)
    {
        double w1, w2, w3, w4, w5, w6;
        for (k = 1; k <= l1; ++k)
        {
            m2 = m2s;
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                m2 += im2;
                i1 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                i2 = (m1 + (k + (ido * 3 + 1) * l1) * in1) << 1;
                i3 = (m1 + (k + ((ido << 1) + 1) * l1) * in1) << 1;
                i4 = (m1 + (k + ((ido << 2) + 1) * l1) * in1) << 1;
                o1 = (m2 + (k + l1 * 5) * in2) << 1;
                o2 = (m2 + (k + l1 * 7) * in2) << 1;
                o3 = (m2 + (k + l1 * 6) * in2) << 1;
                o4 = (m2 + (k + (l1 << 3)) * in2) << 1;
                ti1        = cc[i1 + 1] - cc[i2 + 1];
                ti2        = cc[i1 + 1] + cc[i2 + 1];
                tr4        = cc[i3 + 1] - cc[i4 + 1];
                ti3        = cc[i3 + 1] + cc[i4 + 1];
                tr1        = cc[i1] - cc[i2];
                tr2        = cc[i1] + cc[i2];
                ti4        = cc[i4] - cc[i3];
                tr3        = cc[i3] + cc[i4];
                ch[o1]     = tr2 + tr3;
                ch[o2]     = tr2 - tr3;
                ch[o1 + 1] = ti2 + ti3;
                ch[o2 + 1] = ti2 - ti3;
                ch[o3]     = tr1 + tr4;
                ch[o4]     = tr1 - tr4;
                ch[o3 + 1] = ti1 + ti4;
                ch[o4 + 1] = ti1 - ti4;
            }
        }
        for (i = 2; i <= ido; ++i)
        {
            w1 = wa[i];
            w2 = wa[i + ido];
            w3 = wa[i + ido * 2];
            w4 = wa[i + ido * 3];
            w5 = wa[i + ido * 4];
            w6 = wa[i + ido * 5];
            for (k = 1; k <= l1; ++k)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m1 + (k + (i + ido) * l1) * in1) << 1;
                    i2 = (m1 + (k + (i + ido * 3) * l1) * in1) << 1;
                    i3 = (m1 + (k + (i + (ido << 1)) * l1) * in1) << 1;
                    i4 = (m1 + (k + (i + (ido << 2)) * l1) * in1) << 1;
                    o1 = (m2 + (k + ((i << 2) + 1) * l1) * in2) << 1;
                    o2 = (m2 + (k + ((i << 2) + 2) * l1) * in2) << 1;
                    o3 = (m2 + (k + ((i << 2) + 3) * l1) * in2) << 1;
                    o4 = (m2 + (k + ((i << 2) + 4) * l1) * in2) << 1;
                    ti1        = cc[i1 + 1] - cc[i2 + 1];
                    ti2        = cc[i1 + 1] + cc[i2 + 1];
                    ti3        = cc[i3 + 1] + cc[i4 + 1];
                    tr4        = cc[i3 + 1] - cc[i4 + 1];
                    tr1        = cc[i1] - cc[i2];
                    tr2        = cc[i1] + cc[i2];
                    ti4        = cc[i4] - cc[i3];
                    tr3        = cc[i3] + cc[i4];
                    ch[o1]     = tr2 + tr3;
                    cr3        = tr2 - tr3;
                    ch[o1 + 1] = ti2 + ti3;
                    ci3        = ti2 - ti3;
                    cr2        = tr1 + tr4;
                    cr4        = tr1 - tr4;
                    ci2        = ti1 + ti4;
                    ci4        = ti1 - ti4;
                    ch[o2]     = w1 * cr2 + w4 * ci2;
                    ch[o2 + 1] = w1 * ci2 - w4 * cr2;
                    ch[o3]     = w2 * cr3 + w5 * ci3;
                    ch[o3 + 1] = w2 * ci3 - w5 * cr3;
                    ch[o4]     = w3 * cr4 + w6 * ci4;
                    ch[o4 + 1] = w3 * ci4 - w6 * cr4;
                }
            }
        }
    }
    else
    {
        sn = 1. / (double) (l1 << 2);
        if (na == 1)
        {
            for (k = 1; k <= l1; ++k)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                    i2 = (m1 + (k + (ido * 3 + 1) * l1) * in1) << 1;
                    i3 = (m1 + (k + ((ido << 1) + 1) * l1) * in1) << 1;
                    i4 = (m1 + (k + ((ido << 2) + 1) * l1) * in1) << 1;
                    o1 = (m2 + (k + l1 * 5) * in2) << 1;
                    o2 = (m2 + (k + l1 * 7) * in2) << 1;
                    o3 = (m2 + (k + l1 * 6) * in2) << 1;
                    o4 = (m2 + (k + l1 * 8) * in2) << 1;
                    ti1        = cc[i1 + 1] - cc[i2 + 1];
                    ti2        = cc[i1 + 1] + cc[i2 + 1];
                    tr4        = cc[i3 + 1] - cc[i4 + 1];
                    ti3        = cc[i3 + 1] + cc[i4 + 1];
                    tr1        = cc[i1] - cc[i2];
                    tr2        = cc[i1] + cc[i2];
                    ti4        = cc[i4] - cc[i3];
                    tr3        = cc[i3] + cc[i4];
                    ch[o1]     = sn * (tr2 + tr3);
                    ch[o2]     = sn * (tr2 - tr3);
                    ch[o1 + 1] = sn * (ti2 + ti3);
                    ch[o2 + 1] = sn * (ti2 - ti3);
                    ch[o3]     = sn * (tr1 + tr4);
                    ch[o4]     = sn * (tr1 - tr4);
                    ch[o3 + 1] = sn * (ti1 + ti4);
                    ch[o4 + 1] = sn * (ti1 - ti4);
                }
            }
        }
        else
        {
            for (k = 1; k <= l1; ++k)
            {
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    i1 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                    i2 = (m1 + (k + (ido * 3 + 1) * l1) * in1) << 1;
                    i3 = (m1 + (k + ((ido << 1) + 1) * l1) * in1) << 1;
                    i4 = (m1 + (k + ((ido << 2) + 1) * l1) * in1) << 1;
                    ti1        = cc[i1 + 1] - cc[i2 + 1];
                    ti2        = cc[i1 + 1] + cc[i2 + 1];
                    tr4        = cc[i3 + 1] - cc[i4 + 1];
                    ti3        = cc[i3 + 1] + cc[i4 + 1];
                    tr1        = cc[i1] - cc[i2];
                    tr2        = cc[i1] + cc[i2];
                    ti4        = cc[i4] - cc[i3];
                    tr3        = cc[i3] + cc[i4];
                    cc[i1]     = sn * (tr2 + tr3);
                    cc[i2]     = sn * (tr2 - tr3);
                    cc[i1 + 1] = sn * (ti2 + ti3);
                    cc[i2 + 1] = sn * (ti2 - ti3);
                    cc[i3]     = sn * (tr1 + tr4);
                    cc[i4]     = sn * (tr1 - tr4);
                    cc[i3 + 1] = sn * (ti1 + ti4);
                    cc[i4 + 1] = sn * (ti1 - ti4);
                }
            }
        }
    }
}


void cmf5kb(const int lot, const int ido, const int l1, const int na,
        double *restrict cc, const int im1, const int in1, double *restrict ch,
        const int im2, const int in2, const double *restrict wa)
{
    static const double tr11 = .3090169943749474;
    static const double ti11 = .9510565162951536;
    static const double tr12 = -.8090169943749474;
    static const double ti12 = .5877852522924731;
    int i, k, m1, m2, m1d, m2s, o1, o2, o3, o4, o5, i1, i2, i3, i4, i5;
    double ci2, ci3, ci4, ci5;
    double di3, di4, di5, di2, cr2, cr3, cr5, cr4, ti2, ti3, ti4;
    double ti5, dr3, dr4, dr5, dr2, tr2, tr3, tr4, tr5, chold1, chold2;
    wa -= 1;
    cc -= 2 * (1 + in1 * (1 + l1 * (1 + ido)));
    ch -= 2 * (1 + in2 * (1 + l1 * 6));

    m1d = (lot - 1) * im1 + 1;
    m2s = 1 - im2;
    if (ido > 1 || na == 1)
    {
        double w1, w2, w3, w4, w5, w6, w7, w8;
        for (k = 1; k <= l1; ++k)
        {
            m2 = m2s;
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                m2 += im2;
                i1 = (m1 + (k + (ido * 2 + 1) * l1) * in1) << 1;
                i2 = (m1 + (k + (ido * 5 + 1) * l1) * in1) << 1;
                i3 = (m1 + (k + (ido * 3 + 1) * l1) * in1) << 1;
                i4 = (m1 + (k + (ido * 4 + 1) * l1) * in1) << 1;
                i5 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                o1 = (m2 + (k + l1 * 6) * in2) << 1;
                o2 = (m2 + (k + l1 * 7) * in2) << 1;
                o3 = (m2 + (k + l1 * 10) * in2) << 1;
                o4 = (m2 + (k + l1 * 8) * in2) << 1;
                o5 = (m2 + (k + l1 * 9) * in2) << 1;
                ti5        = cc[i1 + 1] - cc[i2 + 1];
                ti2        = cc[i1 + 1] + cc[i2 + 1];
                ti4        = cc[i3 + 1] - cc[i4 + 1];
                ti3        = cc[i3 + 1] + cc[i4 + 1];
                tr5        = cc[i1] - cc[i2];
                tr2        = cc[i1] + cc[i2];
                tr4        = cc[i3] - cc[i4];
                tr3        = cc[i3] + cc[i4];
                ch[o1]     = cc[i5] + tr2 + tr3;
                ch[o1 + 1] = cc[i5 + 1] + ti2 + ti3;
                cr2        = cc[i5] + tr11 * tr2 + tr12 * tr3;
                ci2        = cc[i5 + 1] + tr11 * ti2 + tr12 * ti3;
                cr3        = cc[i5] + tr12 * tr2 + tr11 * tr3;
                ci3        = cc[i5 + 1] + tr12 * ti2 + tr11 * ti3;
                cr5        = ti11 * tr5 + ti12 * tr4;
                ci5        = ti11 * ti5 + ti12 * ti4;
                cr4        = ti12 * tr5 - ti11 * tr4;
                ci4        = ti12 * ti5 - ti11 * ti4;
                ch[o2]     = cr2 - ci5;
                ch[o3]     = cr2 + ci5;
                ch[o2 + 1] = ci2 + cr5;
                ch[o4 + 1] = ci3 + cr4;
                ch[o4]     = cr3 - ci4;
                ch[o5]     = cr3 + ci4;
                ch[o5 + 1] = ci3 - cr4;
                ch[o3 + 1] = ci2 - cr5;
            }
        }
        for (i = 2; i <= ido; ++i)
        {
            w1 = wa[i];
            w2 = wa[i + ido];
            w3 = wa[i + ido * 2];
            w4 = wa[i + ido * 3];
            w5 = wa[i + ido * 4];
            w6 = wa[i + ido * 5];
            w7 = wa[i + ido * 6];
            w8 = wa[i + ido * 7];
            for (k = 1; k <= l1; ++k)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m1 + (k + (i + (ido << 1)) * l1) * in1) << 1;
                    i2 = (m1 + (k + (i + ido * 5) * l1) * in1) << 1;
                    i3 = (m1 + (k + (i + ido * 3) * l1) * in1) << 1;
                    i4 = (m1 + (k + (i + (ido << 2)) * l1) * in1) << 1;
                    i5 = (m1 + (k + (i + ido) * l1) * in1) << 1;
                    o1 = (m2 + (k + (i * 5 + 1) * l1) * in2) << 1;
                    o2 = (m2 + (k + (i * 5 + 2) * l1) * in2) << 1;
                    o3 = (m2 + (k + (i * 5 + 3) * l1) * in2) << 1;
                    o4 = (m2 + (k + (i * 5 + 4) * l1) * in2) << 1;
                    o5 = (m2 + (k + (i * 5 + 5) * l1) * in2) << 1;
                    ti5        = cc[i1 + 1] - cc[i2 + 1];
                    ti2        = cc[i1 + 1] + cc[i2 + 1];
                    ti4        = cc[i3 + 1] - cc[i4 + 1];
                    ti3        = cc[i3 + 1] + cc[i4 + 1];
                    tr5        = cc[i1] - cc[i2];
                    tr2        = cc[i1] + cc[i2];
                    tr4        = cc[i3] - cc[i4];
                    tr3        = cc[i3] + cc[i4];
                    ch[o1]     = cc[i5] + tr2 + tr3;
                    ch[o1 + 1] = cc[i5 + 1] + ti2 + ti3;
                    cr2        = cc[i5] + tr11 * tr2 + tr12 * tr3;
                    ci2        = cc[i5 + 1] + tr11 * ti2 + tr12 * ti3;
                    cr3        = cc[i5] + tr12 * tr2 + tr11 * tr3;
                    ci3        = cc[i5 + 1] + tr12 * ti2 + tr11 * ti3;
                    cr5        = ti11 * tr5 + ti12 * tr4;
                    ci5        = ti11 * ti5 + ti12 * ti4;
                    cr4        = ti12 * tr5 - ti11 * tr4;
                    ci4        = ti12 * ti5 - ti11 * ti4;
                    dr3        = cr3 - ci4;
                    dr4        = cr3 + ci4;
                    di3        = ci3 + cr4;
                    di4        = ci3 - cr4;
                    dr5        = cr2 + ci5;
                    dr2        = cr2 - ci5;
                    di5        = ci2 - cr5;
                    di2        = ci2 + cr5;
                    ch[o2]     = w1 * dr2 - w5 * di2;
                    ch[o2 + 1] = w1 * di2 + w5 * dr2;
                    ch[o3]     = w2 * dr3 - w6 * di3;
                    ch[o3 + 1] = w2 * di3 + w6 * dr3;
                    ch[o4]     = w3 * dr4 - w7 * di4;
                    ch[o4 + 1] = w3 * di4 + w7 * dr4;
                    ch[o5]     = w4 * dr5 - w8 * di5;
                    ch[o5 + 1] = w4 * di5 + w8 * dr5;
                }
            }
        }
    }
    else
    {
        for (k = 1; k <= l1; ++k)
        {
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                i1 = (m1 + (k + (ido * 2 + 1) * l1) * in1) << 1;
                i2 = (m1 + (k + (ido * 5 + 1) * l1) * in1) << 1;
                i3 = (m1 + (k + (ido * 3 + 1) * l1) * in1) << 1;
                i4 = (m1 + (k + (ido * 4 + 1) * l1) * in1) << 1;
                i5 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                ti5        = cc[i1 + 1] - cc[i2 + 1];
                ti2        = cc[i1 + 1] + cc[i2 + 1];
                ti4        = cc[i3 + 1] - cc[i4 + 1];
                ti3        = cc[i3 + 1] + cc[i4 + 1];
                tr5        = cc[i1] - cc[i2];
                tr2        = cc[i1] + cc[i2];
                tr4        = cc[i3] - cc[i4];
                tr3        = cc[i3] + cc[i4];
                chold1     = cc[i5] + tr2 + tr3;
                chold2     = cc[i5 + 1] + ti2 + ti3;
                cr2        = cc[i5] + tr11 * tr2 + tr12 * tr3;
                ci2        = cc[i5 + 1] + tr11 * ti2 + tr12 * ti3;
                cr3        = cc[i5] + tr12 * tr2 + tr11 * tr3;
                ci3        = cc[i5 + 1] + tr12 * ti2 + tr11 * ti3;
                cc[i5]     = chold1;
                cc[i5 + 1] = chold2;
                cr5        = ti11 * tr5 + ti12 * tr4;
                ci5        = ti11 * ti5 + ti12 * ti4;
                cr4        = ti12 * tr5 - ti11 * tr4;
                ci4        = ti12 * ti5 - ti11 * ti4;
                cc[i1]     = cr2 - ci5;
                cc[i2]     = cr2 + ci5;
                cc[i1 + 1] = ci2 + cr5;
                cc[i3 + 1] = ci3 + cr4;
                cc[i3]     = cr3 - ci4;
                cc[i4]     = cr3 + ci4;
                cc[i4 + 1] = ci3 - cr4;
                cc[i2 + 1] = ci2 - cr5;
            }
        }
    }
}


void cmf5kf(const int lot, const int ido, const int l1, const int na,
        double *restrict cc, const int im1, const int in1, double *restrict ch,
        const int im2, const int in2, const double *restrict wa)
{
    static const double tr11 = .3090169943749474;
    static const double ti11 = -.9510565162951536;
    static const double tr12 = -.8090169943749474;
    static const double ti12 = -.5877852522924731;
    int i, k, m1, m2, m1d, m2s, o1, o2, o3, o4, o5, i1, i2, i3, i4, i5;
    double sn, ci2, ci3, ci4, ci5;
    double di3, di4, di5, di2, cr2, cr3, cr5, cr4, ti2, ti3, ti4;
    double ti5, dr3, dr4, dr5, dr2, tr2, tr3, tr4, tr5, chold1, chold2;
    wa -= 1;
    cc -= 2 * (1 + in1 * (1 + l1 * (1 + ido)));
    ch -= 2 * (1 + in2 * (1 + l1 * 6));

    m1d = (lot - 1) * im1 + 1;
    m2s = 1 - im2;
    if (ido > 1)
    {
        double w1, w2, w3, w4, w5, w6, w7, w8;
        for (k = 1; k <= l1; ++k)
        {
            m2 = m2s;
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                m2 += im2;
                i1 = (m1 + (k + (ido * 2 + 1) * l1) * in1) << 1;
                i2 = (m1 + (k + (ido * 5 + 1) * l1) * in1) << 1;
                i3 = (m1 + (k + (ido * 3 + 1) * l1) * in1) << 1;
                i4 = (m1 + (k + (ido * 4 + 1) * l1) * in1) << 1;
                i5 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                o1 = (m2 + (k + l1 * 6) * in2) << 1;
                o2 = (m2 + (k + l1 * 7) * in2) << 1;
                o3 = (m2 + (k + l1 * 10) * in2) << 1;
                o4 = (m2 + (k + l1 * 8) * in2) << 1;
                o5 = (m2 + (k + l1 * 9) * in2) << 1;
                ti5        = cc[i1 + 1] - cc[i2 + 1];
                ti2        = cc[i1 + 1] + cc[i2 + 1];
                ti4        = cc[i3 + 1] - cc[i4 + 1];
                ti3        = cc[i3 + 1] + cc[i4 + 1];
                tr5        = cc[i1] - cc[i2];
                tr2        = cc[i1] + cc[i2];
                tr4        = cc[i3] - cc[i4];
                tr3        = cc[i3] + cc[i4];
                ch[o1]     = cc[i5] + tr2 + tr3;
                ch[o1 + 1] = cc[i5 + 1] + ti2 + ti3;
                cr2        = cc[i5] + tr11 * tr2 + tr12 * tr3;
                ci2        = cc[i5 + 1] + tr11 * ti2 + tr12 * ti3;
                cr3        = cc[i5] + tr12 * tr2 + tr11 * tr3;
                ci3        = cc[i5 + 1] + tr12 * ti2 + tr11 * ti3;
                cr5        = ti11 * tr5 + ti12 * tr4;
                ci5        = ti11 * ti5 + ti12 * ti4;
                cr4        = ti12 * tr5 - ti11 * tr4;
                ci4        = ti12 * ti5 - ti11 * ti4;
                ch[o2]     = cr2 - ci5;
                ch[o3]     = cr2 + ci5;
                ch[o2 + 1] = ci2 + cr5;
                ch[o4 + 1] = ci3 + cr4;
                ch[o4]     = cr3 - ci4;
                ch[o5]     = cr3 + ci4;
                ch[o5 + 1] = ci3 - cr4;
                ch[o3 + 1] = ci2 - cr5;
            }
        }
        for (i = 2; i <= ido; ++i)
        {
            w1 = wa[i];
            w2 = wa[i + ido];
            w3 = wa[i + ido * 2];
            w4 = wa[i + ido * 3];
            w5 = wa[i + ido * 4];
            w6 = wa[i + ido * 5];
            w7 = wa[i + ido * 6];
            w8 = wa[i + ido * 7];
            for (k = 1; k <= l1; ++k)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m1 + (k + (i + ido * 2) * l1) * in1) << 1;
                    i2 = (m1 + (k + (i + ido * 5) * l1) * in1) << 1;
                    i3 = (m1 + (k + (i + ido * 3) * l1) * in1) << 1;
                    i4 = (m1 + (k + (i + ido * 4) * l1) * in1) << 1;
                    i5 = (m1 + (k + (i + ido) * l1) * in1) << 1;
                    o1 = (m2 + (k + (i * 5 + 1) * l1) * in2) << 1;
                    o2 = (m2 + (k + (i * 5 + 2) * l1) * in2) << 1;
                    o3 = (m2 + (k + (i * 5 + 3) * l1) * in2) << 1;
                    o4 = (m2 + (k + (i * 5 + 4) * l1) * in2) << 1;
                    o5 = (m2 + (k + (i * 5 + 5) * l1) * in2) << 1;
                    ti5        = cc[i1 + 1] - cc[i2 + 1];
                    ti2        = cc[i1 + 1] + cc[i2 + 1];
                    ti4        = cc[i3 + 1] - cc[i4 + 1];
                    ti3        = cc[i3 + 1] + cc[i4 + 1];
                    tr5        = cc[i1] - cc[i2];
                    tr2        = cc[i1] + cc[i2];
                    tr4        = cc[i3] - cc[i4];
                    tr3        = cc[i3] + cc[i4];
                    ch[o1]     = cc[i5] + tr2 + tr3;
                    ch[o1 + 1] = cc[i5 + 1] + ti2 + ti3;
                    cr2        = cc[i5] + tr11 * tr2 + tr12 * tr3;
                    ci2        = cc[i5 + 1] + tr11 * ti2 + tr12 * ti3;
                    cr3        = cc[i5] + tr12 * tr2 + tr11 * tr3;
                    ci3        = cc[i5 + 1] + tr12 * ti2 + tr11 * ti3;
                    cr5        = ti11 * tr5 + ti12 * tr4;
                    ci5        = ti11 * ti5 + ti12 * ti4;
                    cr4        = ti12 * tr5 - ti11 * tr4;
                    ci4        = ti12 * ti5 - ti11 * ti4;
                    dr3        = cr3 - ci4;
                    dr4        = cr3 + ci4;
                    di3        = ci3 + cr4;
                    di4        = ci3 - cr4;
                    dr5        = cr2 + ci5;
                    dr2        = cr2 - ci5;
                    di5        = ci2 - cr5;
                    di2        = ci2 + cr5;
                    ch[o2]     = w1 * dr2 + w5 * di2;
                    ch[o2 + 1] = w1 * di2 - w5 * dr2;
                    ch[o3]     = w2 * dr3 + w6 * di3;
                    ch[o3 + 1] = w2 * di3 - w6 * dr3;
                    ch[o4]     = w3 * dr4 + w7 * di4;
                    ch[o4 + 1] = w3 * di4 - w7 * dr4;
                    ch[o5]     = w4 * dr5 + w8 * di5;
                    ch[o5 + 1] = w4 * di5 - w8 * dr5;
                }
            }
        }
    }
    else
    {
        sn = 1. / (double) (l1 * 5);
        if (na == 1)
        {
            for (k = 1; k <= l1; ++k)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m1 + (k + (ido * 2 + 1) * l1) * in1) << 1;
                    i2 = (m1 + (k + (ido * 5 + 1) * l1) * in1) << 1;
                    i3 = (m1 + (k + (ido * 3 + 1) * l1) * in1) << 1;
                    i4 = (m1 + (k + (ido * 4 + 1) * l1) * in1) << 1;
                    i5 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                    o1 = (m2 + (k + l1 * 6) * in2) << 1;
                    o2 = (m2 + (k + l1 * 7) * in2) << 1;
                    o3 = (m2 + (k + l1 * 10) * in2) << 1;
                    o4 = (m2 + (k + l1 * 8) * in2) << 1;
                    o5 = (m2 + (k + l1 * 9) * in2) << 1;
                    ti5        = cc[i1 + 1] - cc[i2 + 1];
                    ti2        = cc[i1 + 1] + cc[i2 + 1];
                    ti4        = cc[i3 + 1] - cc[i4 + 1];
                    ti3        = cc[i3 + 1] + cc[i4 + 1];
                    tr5        = cc[i1] - cc[i2];
                    tr2        = cc[i1] + cc[i2];
                    tr4        = cc[i3] - cc[i4];
                    tr3        = cc[i3] + cc[i4];
                    ch[o1]     = sn * (cc[i5] + tr2 + tr3);
                    ch[o1 + 1] = sn * (cc[i5 + 1] + ti2 + ti3);
                    cr2        = cc[i5] + tr11 * tr2 + tr12 * tr3;
                    ci2        = cc[i5 + 1] + tr11 * ti2 + tr12 * ti3;
                    cr3        = cc[i5] + tr12 * tr2 + tr11 * tr3;
                    ci3        = cc[i5 + 1] + tr12 * ti2 + tr11 * ti3;
                    cr5        = ti11 * tr5 + ti12 * tr4;
                    ci5        = ti11 * ti5 + ti12 * ti4;
                    cr4        = ti12 * tr5 - ti11 * tr4;
                    ci4        = ti12 * ti5 - ti11 * ti4;
                    ch[o2]     = sn * (cr2 - ci5);
                    ch[o3]     = sn * (cr2 + ci5);
                    ch[o2 + 1] = sn * (ci2 + cr5);
                    ch[o4 + 1] = sn * (ci3 + cr4);
                    ch[o4]     = sn * (cr3 - ci4);
                    ch[o5]     = sn * (cr3 + ci4);
                    ch[o5 + 1] = sn * (ci3 - cr4);
                    ch[o3 + 1] = sn * (ci2 - cr5);
                }
            }
        }
        else
        {
            for (k = 1; k <= l1; ++k)
            {
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    i1 = (m1 + (k + (ido * 2 + 1) * l1) * in1) << 1;
                    i2 = (m1 + (k + (ido * 5 + 1) * l1) * in1) << 1;
                    i3 = (m1 + (k + (ido * 3 + 1) * l1) * in1) << 1;
                    i4 = (m1 + (k + (ido * 4 + 1) * l1) * in1) << 1;
                    i5 = (m1 + (k + (ido + 1) * l1) * in1) << 1;
                    ti5        = cc[i1 + 1] - cc[i2 + 1];
                    ti2        = cc[i1 + 1] + cc[i2 + 1];
                    ti4        = cc[i3 + 1] - cc[i4 + 1];
                    ti3        = cc[i3 + 1] + cc[i4 + 1];
                    tr5        = cc[i1] - cc[i2];
                    tr2        = cc[i1] + cc[i2];
                    tr4        = cc[i3] - cc[i4];
                    tr3        = cc[i3] + cc[i4];
                    chold1     = sn * (cc[i5] + tr2 + tr3);
                    chold2     = sn * (cc[i5 + 1] + ti2 + ti3);
                    cr2        = cc[i5] + tr11 * tr2 + tr12 * tr3;
                    ci2        = cc[i5 + 1] + tr11 * ti2 + tr12 * ti3;
                    cr3        = cc[i5] + tr12 * tr2 + tr11 * tr3;
                    ci3        = cc[i5 + 1] + tr12 * ti2 + tr11 * ti3;
                    cc[i5]     = chold1;
                    cc[i5 + 1] = chold2;
                    cr5        = ti11 * tr5 + ti12 * tr4;
                    ci5        = ti11 * ti5 + ti12 * ti4;
                    cr4        = ti12 * tr5 - ti11 * tr4;
                    ci4        = ti12 * ti5 - ti11 * ti4;
                    cc[i1]     = sn * (cr2 - ci5);
                    cc[i2]     = sn * (cr2 + ci5);
                    cc[i1 + 1] = sn * (ci2 + cr5);
                    cc[i3 + 1] = sn * (ci3 + cr4);
                    cc[i3]     = sn * (cr3 - ci4);
                    cc[i4]     = sn * (cr3 + ci4);
                    cc[i4 + 1] = sn * (ci3 - cr4);
                    cc[i2 + 1] = sn * (ci2 - cr5);
                }
            }
        }
    }
}


void cmfgkb(const int lot, const int ido, const int ip, const int l1,
        const int lid, const int na, double *restrict cc, double *restrict cc1,
        const int im1, const int in1, double *restrict ch, double *restrict ch1,
        const int im2, const int in2, const double *restrict wa)
{
    int i, j, k, l, m1, m2, jc, lc, ki, m1d, m2s, ipp2, idlj, ipph, ipm1;
    int i1, i2, i3, o1, o2;
    double wai, war, chold1, chold2, w1, w2;
    ipm1 = ip - 1;
    wa -= 1 + ido * (1 + ipm1);
    cc1 -= 2 * (1 + in1 * (1 + lid));
    cc -= 2 * (1 + in1 * (1 + l1 * (1 + ip)));
    ch1 -= 2 * (1 + in2 * (1 + lid));
    ch -= 2 * (1 + in2 * (1 + l1 * (1 + ido)));

    m1d = (lot - 1) * im1 + 1;
    m2s = 1 - im2;
    ipp2 = ip + 2;
    ipph = (ip + 1) / 2;
    for (ki = 1; ki <= lid; ++ki)
    {
        m2 = m2s;
        for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
        {
            m2 += im2;
            i1 = (m1 + (ki + lid) * in1) << 1;
            o1 = (m2 + (ki + lid) * in2) << 1;
            ch1[o1]     = cc1[i1];
            ch1[o1 + 1] = cc1[i1 + 1];
        }
    }
    for (j = 2; j <= ipph; ++j)
    {
        jc = ipp2 - j;
        for (ki = 1; ki <= lid; ++ki)
        {
            m2 = m2s;
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                m2 += im2;
                i1 = (m1 + (ki + j * lid) * in1) << 1;
                i2 = (m1 + (ki + jc * lid) * in1) << 1;
                o1 = (m2 + (ki + j * lid) * in2) << 1;
                o2 = (m2 + (ki + jc * lid) * in2) << 1;
                ch1[o1]     = cc1[i1] + cc1[i2];
                ch1[o2]     = cc1[i1] - cc1[i2];
                ch1[o1 + 1] = cc1[i1 + 1] + cc1[i2 + 1];
                ch1[o2 + 1] = cc1[i1 + 1] - cc1[i2 + 1];
            }
        }
    }
    for (j = 2; j <= ipph; ++j)
    {
        for (ki = 1; ki <= lid; ++ki)
        {
            m2 = m2s;
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                m2 += im2;
                i1 = (m2 + (ki + j * lid) * in2) << 1;
                o1 = (m1 + (ki + lid) * in1) << 1;
                cc1[o1]     += ch1[i1];
                cc1[o1 + 1] += ch1[i1 + 1];
            }
        }
    }
    for (l = 2; l <= ipph; ++l)
    {
        lc = ipp2 - l;
        w1 = wa[(l - 1 + ipm1) * ido + 1];
        w2 = wa[(l - 1 + (ipm1 << 1)) * ido + 1];
        for (ki = 1; ki <= lid; ++ki)
        {
            m2 = m2s;
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                m2 += im2;
                i1 = (m2 + (ki + lid) * in2) << 1;
                i2 = (m2 + (ki + (lid << 1)) * in2) << 1;
                i3 = (m2 + (ki + ip * lid) * in2) << 1;
                o1 = (m1 + (ki + l * lid) * in1) << 1;
                o2 = (m1 + (ki + lc * lid) * in1) << 1;
                cc1[o1]     = ch1[i1] + w1 * ch1[i2];
                cc1[o2]     = w2 * ch1[i3];
                cc1[o1 + 1] = ch1[i1 + 1] + w1 * ch1[i2 + 1];
                cc1[o2 + 1] = w2 * ch1[i3 + 1];
            }
        }
        for (j = 3; j <= ipph; ++j)
        {
            jc = ipp2 - j;
            idlj = (l - 1) * (j - 1) % ip;
            war = wa[(idlj + ipm1) * ido + 1];
            wai = wa[(idlj + (ipm1 << 1)) * ido + 1];
            for (ki = 1; ki <= lid; ++ki)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m2 + (ki + j * lid) * in2) << 1;
                    i2 = (m2 + (ki + jc * lid) * in2) << 1;
                    o1 = (m1 + (ki + l * lid) * in1) << 1;
                    o2 = (m1 + (ki + lc * lid) * in1) << 1;
                    cc1[o1]     += war * ch1[i1];
                    cc1[o2]     += wai * ch1[i2];
                    cc1[o1 + 1] += war * ch1[i1 + 1];
                    cc1[o2 + 1] += wai * ch1[i2 + 1];
                }
            }
        }
    }
    if (ido > 1 || na == 1)
    {
        for (ki = 1; ki <= lid; ++ki)
        {
            m2 = m2s;
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                m2 += im2;
                i1 = (m1 + (ki + lid) * in1) << 1;
                o1 = (m2 + (ki + lid) * in2) << 1;
                ch1[o1]     = cc1[i1];
                ch1[o1 + 1] = cc1[i1 + 1];
            }
        }
        for (j = 2; j <= ipph; ++j)
        {
            jc = ipp2 - j;
            for (ki = 1; ki <= lid; ++ki)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m1 + (ki + j * lid) * in1) << 1;
                    i2 = (m1 + (ki + jc * lid) * in1) << 1;
                    o1 = (m2 + (ki + j * lid) * in2) << 1;
                    o2 = (m2 + (ki + jc * lid) * in2) << 1;
                    ch1[o1]     = cc1[i1] - cc1[i2 + 1];
                    ch1[o2]     = cc1[i1] + cc1[i2 + 1];
                    ch1[o2 + 1] = cc1[i1 + 1] - cc1[i2];
                    ch1[o1 + 1] = cc1[i1 + 1] + cc1[i2];
                }
            }
        }
        if (ido == 1) return;
        for (i = 1; i <= ido; ++i)
        {
            for (k = 1; k <= l1; ++k)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m2 + (k + (i + ido) * l1) * in2) << 1;
                    o1 = (m1 + (k + (i * ip + 1) * l1) * in1) << 1;
                    cc[o1]     = ch[i1];
                    cc[o1 + 1] = ch[i1 + 1];
                }
            }
        }
        for (j = 2; j <= ip; ++j)
        {
            for (k = 1; k <= l1; ++k)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m2 + (k + (j * ido + 1) * l1) * in2) << 1;
                    o1 = (m1 + (k + (j + ip) * l1) * in1) << 1;
                    cc[o1]     = ch[i1];
                    cc[o1 + 1] = ch[i1 + 1];
                }
            }
        }
        for (j = 2; j <= ip; ++j)
        {
            for (i = 2; i <= ido; ++i)
            {
                w1 = wa[i + (j - 1 + ipm1) * ido];
                w2 = wa[i + (j - 1 + (ipm1 << 1)) * ido];
                for (k = 1; k <= l1; ++k)
                {
                    m2 = m2s;
                    for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                    {
                        m2 += im2;
                        i1 = (m2 + (k + (i + j * ido) * l1) * in2) << 1;
                        o1 = (m1 + (k + (j + i * ip) * l1) * in1) << 1;
                        cc[o1]     = w1 * ch[i1] - w2 * ch[i1 + 1];
                        cc[o1 + 1] = w1 * ch[i1 + 1] + w2 * ch[i1];
                    }
                }
            }
        }
    }
    else
    {
        for (j = 2; j <= ipph; ++j)
        {
            jc = ipp2 - j;
            for (ki = 1; ki <= lid; ++ki)
            {
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    i1 = (m1 + (ki + j * lid) * in1) << 1;
                    i2 = (m1 + (ki + jc * lid) * in1) << 1;
                    chold1      = cc1[i1] - cc1[i2 + 1];
                    chold2      = cc1[i1] + cc1[i2 + 1];
                    cc1[i1]     = chold1;
                    cc1[i2 + 1] = cc1[i1 + 1] - cc1[i2];
                    cc1[i1 + 1] += cc1[i2];
                    cc1[i2]     = chold2;
                }
            }
        }
    }
}


void cmfgkf(const int lot, const int ido, const int ip, const int l1,
        const int lid, const int na, double *restrict cc, double *restrict cc1,
        const int im1, const int in1, double *restrict ch, double *restrict ch1,
        const int im2, const int in2, const double *restrict wa)
{
    int i, j, k, l, m1, m2, jc, lc, ki, m1d, m2s, ipp2, idlj, ipph, ipm1;
    int i1, i2, i3, o1, o2;
    double sn, wai, war, chold1, chold2, w1, w2;
    ipm1 = ip - 1;
    wa -= 1 + ido * (1 + ipm1);
    cc1 -= 2 * (1 + in1 * (1 + lid));
    cc -= 2 * (1 + in1 * (1 + l1 * (1 + ip)));
    ch1 -= 2 * (1 + in2 * (1 + lid));
    ch -= 2 * (1 + in2 * (1 + l1 * (1 + ido)));

    m1d = (lot - 1) * im1 + 1;
    m2s = 1 - im2;
    ipp2 = ip + 2;
    ipph = (ip + 1) / 2;
    for (ki = 1; ki <= lid; ++ki)
    {
        m2 = m2s;
        for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
        {
            m2 += im2;
            i1 = (m1 + (ki + lid) * in1) << 1;
            o1 = (m2 + (ki + lid) * in2) << 1;
            ch1[o1]     = cc1[i1];
            ch1[o1 + 1] = cc1[i1 + 1];
        }
    }
    for (j = 2; j <= ipph; ++j)
    {
        jc = ipp2 - j;
        for (ki = 1; ki <= lid; ++ki)
        {
            m2 = m2s;
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                m2 += im2;
                i1 = (m1 + (ki + j * lid) * in1) << 1;
                i2 = (m1 + (ki + jc * lid) * in1) << 1;
                o1 = (m2 + (ki + j * lid) * in2) << 1;
                o2 = (m2 + (ki + jc * lid) * in2) << 1;
                ch1[o1]     = cc1[i1] + cc1[i2];
                ch1[o2]     = cc1[i1] - cc1[i2];
                ch1[o1 + 1] = cc1[i1 + 1] + cc1[i2 + 1];
                ch1[o2 + 1] = cc1[i1 + 1] - cc1[i2 + 1];
            }
        }
    }
    for (j = 2; j <= ipph; ++j)
    {
        for (ki = 1; ki <= lid; ++ki)
        {
            m2 = m2s;
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                m2 += im2;
                i1 = (m2 + (ki + j * lid) * in2) << 1;
                o1 = (m1 + (ki + lid) * in1) << 1;
                cc1[o1]     += ch1[i1];
                cc1[o1 + 1] += ch1[i1 + 1];
            }
        }
    }
    for (l = 2; l <= ipph; ++l)
    {
        w1 = wa[(l - 1 + ipm1) * ido + 1];
        w2 = wa[(l - 1 + (ipm1 << 1)) * ido + 1];
        lc = ipp2 - l;
        for (ki = 1; ki <= lid; ++ki)
        {
            m2 = m2s;
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                m2 += im2;
                i1 = (m2 + (ki + lid) * in2) << 1;
                i2 = (m2 + (ki + (lid << 1)) * in2) << 1;
                i3 = (m2 + (ki + ip * lid) * in2) << 1;
                o1 = (m1 + (ki + l * lid) * in1) << 1;
                o2 = (m1 + (ki + lc * lid) * in1) << 1;
                cc1[o1]     = ch1[i1] + w1 * ch1[i2];
                cc1[o2]     = -w2 * ch1[i3];
                cc1[o1 + 1] = ch1[i1 + 1] + w1 * ch1[i2 + 1];
                cc1[o2 + 1] = -w2 * ch1[i3 + 1];
            }
        }
        for (j = 3; j <= ipph; ++j)
        {
            jc = ipp2 - j;
            idlj = (l - 1) * (j - 1) % ip;
            war = wa[(idlj + ipm1) * ido + 1];
            wai = -wa[(idlj + (ipm1 << 1)) * ido + 1];
            for (ki = 1; ki <= lid; ++ki)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m2 + (ki + j * lid) * in2) << 1;
                    i2 = (m2 + (ki + jc * lid) * in2) << 1;
                    o1 = (m1 + (ki + l * lid) * in1) << 1;
                    o2 = (m1 + (ki + lc * lid) * in1) << 1;
                    cc1[o1]     += war * ch1[i1];
                    cc1[o2]     += wai * ch1[i2];
                    cc1[o1 + 1] += war * ch1[i1 + 1];
                    cc1[o2 + 1] += wai * ch1[i2 + 1];
                }
            }
        }
    }
    if (ido > 1)
    {
        for (ki = 1; ki <= lid; ++ki)
        {
            m2 = m2s;
            for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
            {
                m2 += im2;
                i1 = (m1 + (ki + lid) * in1) << 1;
                o1 = (m2 + (ki + lid) * in2) << 1;
                ch1[o1]     = cc1[i1];
                ch1[o1 + 1] = cc1[i1 + 1];
            }
        }
        for (j = 2; j <= ipph; ++j)
        {
            jc = ipp2 - j;
            for (ki = 1; ki <= lid; ++ki)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m1 + (ki + j * lid) * in1) << 1;
                    i2 = (m1 + (ki + jc * lid) * in1) << 1;
                    o1 = (m2 + (ki + j * lid) * in2) << 1;
                    o2 = (m2 + (ki + jc * lid) * in2) << 1;
                    ch1[o1]     = cc1[i1] - cc1[i2 + 1];
                    ch1[o1 + 1] = cc1[i1 + 1] + cc1[i2];
                    ch1[o2]     = cc1[i1] + cc1[i2 + 1];
                    ch1[o2 + 1] = cc1[i1 + 1] - cc1[i2];
                }
            }
        }
        for (i = 1; i <= ido; ++i)
        {
            for (k = 1; k <= l1; ++k)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m2 + (k + (i + ido) * l1) * in2) << 1;
                    o1 = (m1 + (k + (i * ip + 1) * l1) * in1) << 1;
                    cc[o1]     = ch[i1];
                    cc[o1 + 1] = ch[i1 + 1];
                }
            }
        }
        for (j = 2; j <= ip; ++j)
        {
            for (k = 1; k <= l1; ++k)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m2 + (k + (j * ido + 1) * l1) * in2) << 1;
                    o1 = (m1 + (k + (j + ip) * l1) * in1) << 1;
                    cc[o1]     = ch[i1];
                    cc[o1 + 1] = ch[i1 + 1];
                }
            }
        }
        for (j = 2; j <= ip; ++j)
        {
            for (i = 2; i <= ido; ++i)
            {
                w1 = wa[i + (j - 1 + ipm1) * ido];
                w2 = wa[i + (j - 1 + (ipm1 << 1)) * ido];
                for (k = 1; k <= l1; ++k)
                {
                    m2 = m2s;
                    for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                    {
                        m2 += im2;
                        i1 = (m2 + (k + (i + j * ido) * l1) * in2) << 1;
                        o1 = (m1 + (k + (j + i * ip) * l1) * in1) << 1;
                        cc[o1]     = w1 * ch[i1] + w2 * ch[i1 + 1];
                        cc[o1 + 1] = w1 * ch[i1 + 1] - w2 * ch[i1];
                    }
                }
            }
        }
    }
    else
    {
        sn = 1. / (double) (ip * l1);
        if (na == 1)
        {
            for (ki = 1; ki <= lid; ++ki)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m1 + (ki + lid) * in1) << 1;
                    o1 = (m2 + (ki + lid) * in2) << 1;
                    ch1[o1]     = sn * cc1[i1];
                    ch1[o1 + 1] = sn * cc1[i1 + 1];
                }
            }
            for (j = 2; j <= ipph; ++j)
            {
                jc = ipp2 - j;
                for (ki = 1; ki <= lid; ++ki)
                {
                    m2 = m2s;
                    for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                    {
                        m2 += im2;
                        i1 = (m1 + (ki + j * lid) * in1) << 1;
                        i2 = (m1 + (ki + jc * lid) * in1) << 1;
                        o1 = (m2 + (ki + j * lid) * in2) << 1;
                        o2 = (m2 + (ki + jc * lid) * in2) << 1;
                        ch1[o1]     = sn * (cc1[i1] - cc1[i2 + 1]);
                        ch1[o1 + 1] = sn * (cc1[i1 + 1] + cc1[i2]);
                        ch1[o2]     = sn * (cc1[i1] + cc1[i2 + 1]);
                        ch1[o2 + 1] = sn * (cc1[i1 + 1] - cc1[i2]);
                    }
                }
            }
        }
        else
        {
            for (ki = 1; ki <= lid; ++ki)
            {
                m2 = m2s;
                for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                {
                    m2 += im2;
                    i1 = (m1 + (ki + lid) * in1) << 1;
                    cc1[i1]     *= sn;
                    cc1[i1 + 1] *= sn;
                }
            }
            for (j = 2; j <= ipph; ++j)
            {
                jc = ipp2 - j;
                for (ki = 1; ki <= lid; ++ki)
                {
                    for (m1 = 1; im1 < 0 ? m1 >= m1d : m1 <= m1d; m1 += im1)
                    {
                        i1 = (m1 + (ki + j * lid) * in1) << 1;
                        i2 = (m1 + (ki + jc * lid) * in1) << 1;
                        chold1      = sn * (cc1[i1] - cc1[i2 + 1]);
                        chold2      = sn * (cc1[i1] + cc1[i2 + 1]);
                        cc1[i1]     = chold1;
                        cc1[i2 + 1] = sn * (cc1[i1 + 1] - cc1[i2]);
                        cc1[i1 + 1] = sn * (cc1[i1 + 1] + cc1[i2]);
                        cc1[i2]     = chold2;
                    }
                }
            }
        }
    }
}


void cmfm1b(const int lot, const int jump, const int n, const int inc,
        double *restrict c, double *restrict ch, const double *restrict wa,
        const double fnf, const double *restrict fac)
{
    int k1, l1 = 1, l2, na = 0, nf, ip, iw = 0, lid, ido, nbr;
    nf = (int) fnf;
    for (k1 = 0; k1 < nf; ++k1)
    {
        ip = (int) fac[k1];
        l2 = ip * l1;
        ido = n / l2;
        lid = l1 * ido;
        nbr = na + 1 + (min(ip - 2, 4) << 1);
        switch (nbr)
        {
        case 1:
            cmf2kb(lot, ido, l1, na, c, jump, inc, ch, 1, lot, &wa[iw]);
            break;
        case 2:
            cmf2kb(lot, ido, l1, na, ch, 1, lot, c, jump, inc, &wa[iw]);
            break;
        case 3:
            cmf3kb(lot, ido, l1, na, c, jump, inc, ch, 1, lot, &wa[iw]);
            break;
        case 4:
            cmf3kb(lot, ido, l1, na, ch, 1, lot, c, jump, inc, &wa[iw]);
            break;
        case 5:
            cmf4kb(lot, ido, l1, na, c, jump, inc, ch, 1, lot, &wa[iw]);
            break;
        case 6:
            cmf4kb(lot, ido, l1, na, ch, 1, lot, c, jump, inc, &wa[iw]);
            break;
        case 7:
            cmf5kb(lot, ido, l1, na, c, jump, inc, ch, 1, lot, &wa[iw]);
            break;
        case 8:
            cmf5kb(lot, ido, l1, na, ch, 1, lot, c, jump, inc, &wa[iw]);
            break;
        case 9:
            cmfgkb(lot, ido, ip, l1, lid, na, c, c, jump, inc,
                    ch, ch, 1, lot, &wa[iw]);
            break;
        case 10:
            cmfgkb(lot, ido, ip, l1, lid, na, ch, ch, 1, lot,
                    c, c, jump, inc, &wa[iw]);
            break;
        }
        l1 = l2;
        iw += (ip - 1) * (ido + ido);
        if (ip <= 5) na = 1 - na;
    }
}


void cmfm1f(const int lot, const int jump, const int n, const int inc,
        double *restrict c, double *restrict ch, const double *restrict wa,
        const double fnf, const double *restrict fac)
{
    int k1, l1 = 1, l2, na = 0, nf, ip, iw = 0, lid, ido, nbr;
    nf = (int) fnf;
    for (k1 = 0; k1 < nf; ++k1)
    {
        ip = (int) fac[k1];
        l2 = ip * l1;
        ido = n / l2;
        lid = l1 * ido;
        nbr = na + 1 + (min(ip - 2, 4) << 1);
        switch (nbr)
        {
        case 1:
            cmf2kf(lot, ido, l1, na, c, jump, inc, ch, 1, lot, &wa[iw]);
            break;
        case 2:
            cmf2kf(lot, ido, l1, na, ch, 1, lot, c, jump, inc, &wa[iw]);
            break;
        case 3:
            cmf3kf(lot, ido, l1, na, c, jump, inc, ch, 1, lot, &wa[iw]);
            break;
        case 4:
            cmf3kf(lot, ido, l1, na, ch, 1, lot, c, jump, inc, &wa[iw]);
            break;
        case 5:
            cmf4kf(lot, ido, l1, na, c, jump, inc, ch, 1, lot, &wa[iw]);
            break;
        case 6:
            cmf4kf(lot, ido, l1, na, ch, 1, lot, c, jump, inc, &wa[iw]);
            break;
        case 7:
            cmf5kf(lot, ido, l1, na, c, jump, inc, ch, 1, lot, &wa[iw]);
            break;
        case 8:
            cmf5kf(lot, ido, l1, na, ch, 1, lot, c, jump, inc, &wa[iw]);
            break;
        case 9:
            cmfgkf(lot, ido, ip, l1, lid, na, c, c, jump, inc,
                    ch, ch, 1, lot, &wa[iw]);
            break;
        case 10:
            cmfgkf(lot, ido, ip, l1, lid, na, ch, ch, 1, lot,
                    c, c, jump, inc, &wa[iw]);
            break;
        }
        l1 = l2;
        iw += (ip - 1) * (ido + ido);
        if (ip <= 5) na = 1 - na;
    }
}


void factor(const int n, int *nf, double *fac)
{
    static const int ntryh[4] = { 4,2,3,5 };
    int j = 0, nl, nq, nr, ntry = 0;
    --fac;

    nl = n;
    *nf = 0;
L101:
    ++j;
    if (j - 4 <= 0)
        ntry = ntryh[j - 1];
    else
        ntry += 2;
L104:
    nq = nl / ntry;
    nr = nl - ntry * nq;
    if (nr != 0) goto L101;
    ++(*nf);
    fac[*nf] = (double) ntry;
    nl = nq;
    if (nl != 1) goto L104;
}


void mcfti1(const int n, double *restrict wa, double *restrict fnf,
        double *restrict fac)
{
    int k1, l1 = 1, l2, nf, ip, iw = 0, ido;
    factor(n, &nf, fac);
    *fnf = (double) nf;
    for (k1 = 0; k1 < nf; ++k1)
    {
        ip = (int) fac[k1];
        l2 = l1 * ip;
        ido = n / l2;
        tables(ido, ip, &wa[iw]);
        iw += (ip - 1) * (ido + ido);
        l1 = l2;
    }
}


void tables(const int ido, const int ip, double *restrict wa)
{
    int ipm1, i, j;
    double tpi, arg1, arg2, arg3, arg4, argz;
    ipm1 = ip - 1;
    wa -= (ido * ip);

    tpi = 8.0 * atan(1.0);
    argz = tpi / (double) (ip);
    arg1 = tpi / (double) (ido * ip);
    for (j = 1; j < ip; ++j)
    {
        arg2 = (double) j * arg1;
        for (i = 0; i < ido; ++i)
        {
            arg3 = (double) i * arg2;
            wa[i + (j + ipm1) * ido] = cos(arg3);
            wa[i + (j + (ipm1 << 1)) * ido] = sin(arg3);
        }
        if (ip <= 5) continue;
        arg4 = (double) j * argz;
        wa[(j + ipm1) * ido] = cos(arg4);
        wa[(j + (ipm1 << 1)) * ido] = sin(arg4);
    }
}
