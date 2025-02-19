/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: MorphologicalMasks.cs
'           Description: Generates and stores masks for morphological
'                        functions.
'         Related Files: MorphologicalMaskForm.cs
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
    public class MorphologicalMasks
    {
        private HitOrMissMasks mskHitOrMiss = new HitOrMissMasks();
        private ThinningMasks mskThinning = new ThinningMasks();
        private ThinningMasks mskSkeletonization = new ThinningMasks();

        public void Clear()
        {
            this.mskHitOrMiss.Clear();
            this.mskSkeletonization.Clear();
            this.mskThinning.Clear();
        }
        static public double[,] RotateMask(int iterations, bool direction, double[,] mask)
        {
            int masksize = mask.GetLength(0);
            int center = masksize / 2;
            double[,] maskrotated = new double[masksize, masksize];
            Queue<double> mask1d = new Queue<double>();

            for (int ring = 1; ring <= center; ring++)
            {
                mask1d.Clear();

                for (int c = center - ring; c <= center + ring; c++)
                    mask1d.Enqueue(mask[center - ring, c]);
                for (int r = center - ring + 1; r <= center + ring; r++)
                    mask1d.Enqueue(mask[r, center + ring]);
                for (int c = center + ring - 1; c >= center - ring; c--)
                    mask1d.Enqueue(mask[center + ring, c]);
                for (int r = center + ring - 1; r > center - ring; r--)
                    mask1d.Enqueue(mask[r, center - ring]);

                if (direction)
                    mask1d = new Queue<double>(mask1d.Reverse());
                for (int i = 0; i < ring * iterations; i++)
                    mask1d.Enqueue(mask1d.Dequeue());
                if (direction)
                    mask1d = new Queue<double>(mask1d.Reverse());

                for (int c = center - ring; c <= center + ring; c++)
                    maskrotated[center - ring, c] = mask1d.Dequeue();
                for (int r = center - ring + 1; r <= center + ring; r++)
                    maskrotated[r, center + ring] = mask1d.Dequeue();
                for (int c = center + ring - 1; c >= center - ring; c--)
                    maskrotated[center + ring, c] = mask1d.Dequeue();
                for (int r = center + ring - 1; r > center - ring; r--)
                    maskrotated[r, center - ring] = mask1d.Dequeue();
            }
            maskrotated[center, center] = mask[center, center];
            return maskrotated;
        }

        public HitOrMissMasks HitOrMissMask { get { return this.mskHitOrMiss; } }
        public ThinningMasks SkeletonizationMask { get { return this.mskSkeletonization; } }
        public ThinningMasks ThinningMask { get { return this.mskThinning; } }
    }
}
