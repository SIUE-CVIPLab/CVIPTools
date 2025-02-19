/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: check_xform_history.c
'           Description: check_xform_history function implementation
'         Related Files: CVIPC Directory
'                        Include Directory
'   Initial Coding Date: February 2013
'       Delevoping tool: Visual Studio 2010-C++
'             Credit(s): Patrick Solt
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2013 Scott Umbaugh and SIUE
'
' Permission to use, copy, modify, and distribute this software and its
' documentation for any non-commercial purpose and without fee is hereby
' granted, provided that the above copyright notice appear in all copies
' and that both that copyright notice and this permission notice appear
' in supporting documentation.  This software is provided "as is"
' without express or implied warranty.
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''*/

#include "CVIPimage.h"

int check_xform_history(Image* image, unsigned filter, PROGRAMS* xform)
{
    PROGRAMS i, progs[6] = {FFT, DCTXFORM, WALSH, WAVELET, HAAR, HADAMARD};
    HISTORY history;

    if ((i = getlast_Hist(image, progs, 6)) == 0)
        return i;

    if ((filter > 0) && (filter < 6))
    {
        history = (HISTORY)malloc(sizeof(struct history));
        history->next = NULL;
        history->packetP = (PACKET*)malloc(sizeof(PACKET));
        history->packetP->dtype = (CVIP_TYPE*)malloc(sizeof(CVIP_TYPE));
        *(history->packetP->dtype) = CVIP_INTEGER;
        history->packetP->dsize = 1;
        history->packetP->dptr = (void**)malloc(sizeof(void*));
        history->packetP->dptr[0] = (int*)malloc(sizeof(int));
        memcpy((void*)history->packetP->dptr[0], (void*)&filter, sizeof(int));
        history->ftag = XFORMFILTER;
        history_add(image, history);
    }
    *xform = i;
    return 1;
}
