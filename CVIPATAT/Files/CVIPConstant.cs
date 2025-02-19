/*************************************************************************
* ========================================================================
*
*			      CVIP_ATAT - Dr. Scott Umbaugh SIUE
* 
* ========================================================================
*
*             File Name: CVIPConstant.cs 
*           Description: Constant for CVIPATAT.
*   Initial Coding Date: June 6, 2006
*Last Modification Made: June 22, 2010
*  Programming Language: Visual Studio C#.NET 2008 
*             Credit(s): Wenjun(Evan) Bian, Pelin Guvenc
*                        Southern Illinois University at Edwardsville
*
*		  Copyright (c): 2010-2011 SIUE - Scott Umbaugh
****************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;

namespace CVIP_ATAT.Files
{
    public class Globals
    {
        public static int imageCount = 0;
        public static int algorithmCount = 0;
    }
    
    public enum imageFormat : int  //global enum
    {
        PBM = 0,  PGM = 1,  PPM = 2,   EPS = 3,    TIF = 4,  GIF = 5,  RAS = 6,  ITX = 7,    IRIS = 8,  CCC = 9,
        BIN = 10, VIP = 11, GLR = 12,  BTC = 13,   BRC = 14, HUF = 15, ZVL = 16, ARITH = 17, BTC2 = 18, BTC3 = 19,
        DPC = 20, ZON = 21, ZON2 = 22, SAFVR = 23, JPG = 24, WVQ = 25, FRA = 26, VQ = 27,    XVQ = 28,  TRCM = 29,
        PS = 30,  BMP = 31
    }

    public enum colorFormat : int
    {
        BINARY=0, GRAY_SCALE=1, RGB=2, HSL=3, HSV=4, SCT=5, CCT=6, LUV=7, LAB=8, XYZ=9, PCT=10
    }

    public enum dataType : int
    {
        CVIP_BYTE = 0,
        CVIP_SHORT = 1,
        CVIP_INTEGER = 2,
        CVIP_FLOAT = 3,
        CVIP_DOUBLE = 4
    }

    public enum dataFormat : int
    {
        REAL=0, 
        COMPLEX=1
    }

    public enum CVIPYesNo : int
    {
        CVIP_NO = 0,
        CVIP_YES = 1
    }

    //<thresh_inbyte> -  CVIP_NO = "0": Apply threshold value directly to original image data;
    //                  CVIP_YES = "1": Threshold value is CVIP_BYTE range; 
    //                                  Remap to image data range before thresholding.
    public enum threshInByte : int
    {
        CVIP_NO = 0,
        CVIP_YES = 1
    }

    public enum kernelType : int
    { 
        circle=1,   
        square=2,   
        rectangle=3,     
        cross=4    
    }

    public enum edgeType : int
    {
        /*EDGE_KIRSCH = 2, 
        EDGE_ROBINSON = 3,
        EDGE_PYRAMID = 4,
        EDGE_LAPLACIAN = 5,
        EDGE_SOBEL = 6,
        EDGE_ROBERTS = 7,
        EDGE_PREWITT = 8,
        EDGE_FREI = 9*/
    }

    class CVIPConstant
    {
        /*Example for global variable and function;
          
          public static int aaa=100;  //used to define a global variable
          public static int globalFunction(int a) //global function definition
          {
              int c;
              c = a;
              return c;
          }*/

        public CVIPConstant()
        {
        }
    }
}
//How to invoke global enum, variable and function?
//   1. Using the namespace including global variables in the file that will invoke global variables
//   2. For enum just use enum name in the file :(int)imageFormat.VIP
//   3. For variable and function (classname.variable/function): int aa=CVIPConstant.globalFunction();
//                                                               int bb=CVIPConstant.aaa;