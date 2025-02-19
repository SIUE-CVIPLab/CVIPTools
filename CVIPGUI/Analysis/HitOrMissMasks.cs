/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: HitOrMissMasks.cs
'           Description: Generates and stores masks for morphological
'                        HitOrMissMasks functions.
'         Related Files: MorphologicalMasks.cs
'   Initial Coding Date: March 2013
'       Delevoping tool: Visual Studio 2010-C#
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

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CVIPGUI.Analysis
{
    public class HitOrMissMasks
    {
        int nMaskSize = -1;
        int nCurrentMask = 7;
        double[,] maskCurrent = null;
        double[,] maskDefault = null;

        public void Clear()
        {
            this.maskCurrent = null;
            this.maskDefault = null;
        }
        double[,] RotateFromCurrent(double[,] current)
        {
            double[,] mask = null;
            switch (this.nCurrentMask)
            {
                case 1:
                    mask = MorphologicalMasks.RotateMask(3, false, current);
                   
                    break;
                case 2:
                  mask = MorphologicalMasks.RotateMask(3, true, current);//   mask = MorphologicalMasks.RotateMask(1, false, current);// 2-> 4
                    break;
                case 3:
                   mask = MorphologicalMasks.RotateMask(1, true, current);//  mask = MorphologicalMasks.RotateMask(4, false, current);
                    break;
                case 4:
              mask = MorphologicalMasks.RotateMask(1, false, current);//   mask = MorphologicalMasks.RotateMask(3, true, current);//    mask = MorphologicalMasks.RotateMask(2, true, current);
                    break;
                case 5:
                  mask = MorphologicalMasks.RotateMask(4, false, current);// mask = MorphologicalMasks.RotateMask(4, false, current);// mask = MorphologicalMasks.RotateMask(1, false, current);
                    break;
                case 6:
                   mask = MorphologicalMasks.RotateMask(2, true, current);// mask = MorphologicalMasks.RotateMask(2, true, current);// mask = MorphologicalMasks.RotateMask(3, false, current);
                    break;
                case 7:
                    mask = current;
                    break;
                case 8:
                 mask = MorphologicalMasks.RotateMask(2, false, current);//   mask = MorphologicalMasks.RotateMask(2, false, current);// mask = MorphologicalMasks.RotateMask(1, true, current);
                    break;
          /*  case 5:
                mask = MorphologicalMasks.RotateMask(4, false, current);
                break;
            case 6:
                mask = MorphologicalMasks.RotateMask(2, true, current);
                break;
            case 7:
                mask = current;
                break;
            case 8:
                mask = MorphologicalMasks.RotateMask(2, false, current);
                break;*/
            }
            return mask;
        }
        double[,] RotateToCurrent(double[,] mask)
        {
            double[,] current = null;
            switch (this.nCurrentMask)
            {

                case 1:
                    current = MorphologicalMasks.RotateMask(3, true, mask);
                   
                    break;
                case 2:
                  current = MorphologicalMasks.RotateMask(3, false, mask);//  current = MorphologicalMasks.RotateMask(1, true, mask);
                    break;
                case 3:
                    current = MorphologicalMasks.RotateMask(1, false, mask);// current = MorphologicalMasks.RotateMask(4, true, mask);
                    break;
                case 4:
                 current = MorphologicalMasks.RotateMask(1, true, mask);// current = MorphologicalMasks.RotateMask(3, false, mask);//  current = MorphologicalMasks.RotateMask(2, false, mask);
                    break;
                case 5:
                 current = MorphologicalMasks.RotateMask(4, false, mask);//  current = MorphologicalMasks.RotateMask(4, false, mask);//  current = MorphologicalMasks.RotateMask(1, true, mask);
                    break;
                case 6:
                 current = MorphologicalMasks.RotateMask(2, false, mask);// current = MorphologicalMasks.RotateMask(2, false, mask);//  current = MorphologicalMasks.RotateMask(3, true, mask);
                    break;
                case 7:
                    current = mask;
                    break;
                case 8:
                current = MorphologicalMasks.RotateMask(2, true, mask);//   current = MorphologicalMasks.RotateMask(2, true, mask);//  current = MorphologicalMasks.RotateMask(1, false, mask);
                    break;

            /*case 5:
                current = MorphologicalMasks.RotateMask(4, false, mask);
                break;
            case 6:
                current = MorphologicalMasks.RotateMask(2, false, mask);
                break;
            case 7:
                current = mask;
                break;
            case 8:
                current = MorphologicalMasks.RotateMask(2, true, mask);
                break;*/
            }
            return current;
        }

        public double[,] this[int idx, int size]
        {
            get
            {
                if ((idx < 1) || (idx > 8))
                    return null;

                this.nCurrentMask = idx;
                if (size != this.nMaskSize)
                {
                    Clear();
                    this.nMaskSize = size;
                }
                double[,] mask = this.maskCurrent;
                if (mask == null)
                    mask = DefaultMask;
                return RotateToCurrent(mask);
            }
            set
            {
                if ((idx < 1) || (idx > 8))
                    return;
                if (idx != this.nCurrentMask)
                    return;
                if (size != this.nMaskSize)
                    return;
                this.maskCurrent = RotateFromCurrent(value);
            }
        }
        private double[,] DefaultMask
        {
            get
            {
                if (this.maskDefault == null)
                {
                    this.maskDefault = new double[this.nMaskSize, this.nMaskSize];
                    int center = this.nMaskSize / 2;
                    for (int r = 0; r < this.nMaskSize; r++)
                    {
                        for (int c = 0; c < this.nMaskSize; c++)
                        {
                            if (r < center)
                                this.maskDefault[r, c] = (c < center) ? -1.0 : 0.0;
                            else if (r == center)
                                this.maskDefault[r, c] = (c > center) ? 0.0 : 1.0;
                            else
                                this.maskDefault[r, c] = (c == center) ? 1.0 : -1.0;
                        }
                    }
                }
                return this.maskDefault;
            }
        }
    }
}
