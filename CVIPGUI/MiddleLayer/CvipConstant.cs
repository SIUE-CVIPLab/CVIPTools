/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: CvipConstant.cs
'           Description: Contains the controls and code
'                        for MiddleLayer->CvipConstant class
'   Initial Coding Date: April 2007
'              Modified: March 2010
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt
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
using System.Drawing;
using System.Text;

namespace CVIPGUI
{
    public enum colorFormat : int
    {
        BIN = 0, GRAY = 1, RGB = 2, HSL = 3, HSV = 4, SCT = 5, CCT = 6, LUV = 7, LAB = 8, XYZ = 9, PCT = 10
    }

    public enum dataFormat : int
    {
        REAL = 0,
        COMPLEX = 1
    }

    public enum dataType : int
    {
        CVIP_BYTE = 0,
        CVIP_SHORT = 1,
        CVIP_INTEGER = 2,
        CVIP_FLOAT = 3,
        CVIP_DOUBLE = 4
    }

    public enum imageFormat : int
    {
        PBM = 0, PGM = 1, PPM = 2, EPS = 3, TIF = 4, GIF = 5, RAS = 6, ITX = 7, IRIS = 8, CCC = 9,
        BIN = 10, VIP = 11, GLR = 12, BTC = 13, BRC = 14, HUF = 15, ZVL = 16, ARITH = 17, BTC2 = 18, BTC3 = 19,
        DPC = 20, ZON = 21, ZON2 = 22, SAFVR = 23, JPG = 24, WVQ = 25, FRA = 26, VQ = 27, XVQ = 28, TRCM = 29,
        PS = 30, BMP = 31, JP2 = 32, PNG = 33
    }

    public enum kernelType : int
    {
        circle = 1,
        square = 2,
        rectangle = 3,
        cross = 4
    }

    public enum LogRemap : int
    {
        All = -1,
        Red = 0,
        Green = 1,
        Blue = 2
    }

    static class CvipConstant
    {
        static public readonly Point ptEmpty = new Point(-1, -1);
        static public uint imageNameCount = 0;
        static public uint CvipMessageBufferSize = 100000;
    }

    public static class CvipFunctionNames
    {
        public static int longFileNamesChecked;
        //analysis tab
        //edge_detection
        static string[] fncLaplacian = new string[2];
        static string[] fncRoberts = new string[2];
        static string[] fncSobel = new string[2];
        static string[] fncSobelDirection = new string[2];
        static string[] fncPrewitt = new string[2];
        static string[] fncPrewittDirection = new string[2];
        static string[] fncKirsch = new string[2];
        static string[] fncKirschDirection = new string[2];
        static string[] fncRobinson = new string[2];
        static string[] fncRobinsonDirection = new string[2];
        static string[] fncPyramid = new string[2];
        static string[] fncFreichen = new string[2];
        static string[] fncCerchar = new string[2];
        static string[] fncMarrhildreth = new string[2];
        static string[] fncMarrhildrethSigmaPlusDelta = new string[2];
        static string[] fncMarrhildrethSigmaMinusDelta = new string[2];
        static string[] fncCanny = new string[2];
        static string[] fncCannyMagnitude = new string[2];
        static string[] fncCannyDirection = new string[2];
        static string[] fncBoiecox = new string[2];
        static string[] fncBoiecoxThreshold = new string[2];
        static string[] fncBoiecoxHyst = new string[2];
        static string[] fncShencastan = new string[2];
        static string[] fncShencastanZeroInter = new string[2];
        static string[] fncMoravec = new string[2];
        static string[] fncHarris = new string[2];
        static string[] fncHough = new string[2];
        static string[] fncEdgelink = new string[2];
        static string[] fncPratt = new string[2];
        //geometry
        static string[] fncCrop = new string[2];
        static string[] fncPaste = new string[2];
        static string[] fncResize = new string[2];
        static string[] fncRotate = new string[2];
        static string[] fncTranslate = new string[2];
        static string[] fncZoom = new string[2];
        //transforms
        static string[] fncDct = new string[2];
        static string[] fncFft = new string[2];
        static string[] fncWalhad = new string[2];
        static string[] fncHadamard = new string[2];
        static string[] fncHaar = new string[2];
        static string[] fncWavelet = new string[2];
        static string[] fncLowpass = new string[2];
        static string[] fncHighpass = new string[2];
        static string[] fncBandpass = new string[2];
        static string[] fncBandreject = new string[2];
        static string[] fncHighfreqemphasis = new string[2];
        static string[] fncNotch = new string[2];
        static string[] fncFftphase = new string[2];
        static string[] fncFftmagnitude = new string[2];
        //segmentation
        static string[] fncGrayquant = new string[2];
        static string[] fncFuzzyc = new string[2];
        static string[] fncAutothreshold = new string[2];
        static string[] fncOutsu = new string[2];
        static string[] fncGvfsnake = new string[2];
        static string[] fncLivewire = new string[2];
        static string[] fncHistthreshold = new string[2];
        static string[] fncMedcut = new string[2];
        static string[] fncPctmed = new string[2];
        static string[] fncSct = new string[2];
        static string[] fncMultires = new string[2];
        static string[] fncSplitmerge = new string[2];
        static string[] fncWatershed = new string[2];
        static string[] fncMorphc = new string[2];
        static string[] fncMorpho = new string[2];
        static string[] fncMorphe = new string[2];
        static string[] fncMorphd = new string[2];
        static string[] fncMorphi = new string[2];
        static string[] fncMorphhit = new string[2];
        static string[] fncMorphthin = new string[2];
        static string[] fncMorphskel = new string[2];
        //feature
        static string[] fncLabel = new string[2];
        //compression tab
        //lossless
        static string[] fncHuffman = new string[2];
        static string[] fncZivlempel = new string[2];
        static string[] fncDpc = new string[2];
        static string[] fncBitplane = new string[2];
        static string[] fncJpeg2000 = new string[2];
        //lossy
        static string[] fncBtc = new string[2];
        static string[] fncMbtc = new string[2];
        static string[] fncPmbtc = new string[2];
        static string[] fncJpeg = new string[2];
        static string[] fncDyrlc = new string[2];
        static string[] fncBitplanerlc = new string[2];
        static string[] fncZonal = new string[2];
        static string[] fncFractal = new string[2];
        static string[] fncXvq = new string[2];
        static string[] fncVq = new string[2];
        static string[] fncTransformcompression = new string[2];
        //preprocessing
        static string[] fncBin2gray = new string[2];
        static string[] fncGray2bin = new string[2];
        static string[] fncSpatialquant = new string[2];
        static string[] fncGquant = new string[2];
        //restoration tab
        //frequency filter
        static string[] fncInverse = new string[2];
        static string[] fncGeomean = new string[2];
        static string[] fncPowerspecteq = new string[2];
        static string[] fncConstleastsqu = new string[2];
        static string[] fncWiener = new string[2];
        static string[] fncPractwiener = new string[2];
        static string[] fncParawiener = new string[2];
        //geometric transform
        static string[] fncNewmesh = new string[2];
        static string[] fncOpenmesh = new string[2];
        static string[] fncSinemesh = new string[2];
        //noise
        static string[] fncNegexp = new string[2];
        static string[] fncRayleigh = new string[2];
        static string[] fncGaussian = new string[2];
        static string[] fncUniform = new string[2];
        static string[] fncGamma = new string[2];
        static string[] fncSaltpepper = new string[2];
        //spatial filter
        static string[] fncMedian = new string[2];
        static string[] fncMinimum = new string[2];
        static string[] fncMidpoint = new string[2];
        static string[] fncMaximum = new string[2];
        static string[] fncAlphamean = new string[2];
        static string[] fncArithmetic = new string[2];
        static string[] fncGeometric = new string[2];
        static string[] fncHarmonic = new string[2];
        static string[] fncContra = new string[2];
        static string[] fncYpmean = new string[2];
        static string[] fncMmse = new string[2];
        static string[] fncAdaptmedian = new string[2];
        static string[] fncKuwahara = new string[2];
        static string[] fncAdaptcontrast = new string[2];
        static string[] fncAnisotropic = new string[2];
        //enhancement tab
        //histogram
        static string[] fncHisteq = new string[2];
        static string[] fncHistslide = new string[2];
        static string[] fncHiststretch = new string[2];
        static string[] fncHistshrink = new string[2];
        static string[] fncLocaleq = new string[2];
        static string[] fncAce = new string[2];
        static string[] fncAceII = new string[2];
        static string[] fncLogace = new string[2];
        static string[] fncExpace = new string[2];
        static string[] fncHistspec = new string[2];
        static string[] fncLinearmod = new string[2];
        static string[] fncGraylevelmult = new string[2];
        static string[] fncShowhistogram = new string[2];
        static string[] fncShowhistogramspec = new string[2];
        static string[] fncShowhistogramresult = new string[2];
        static string[] fncColorenhancement = new string[2];
        static string[] fncCLAHE = new string[2];
        //pseudocolor
        static string[] fncGraylevelmap = new string[2];
        static string[] fncFrequencydomainmap = new string[2];
        static string[] fncIntensityslice = new string[2];
        static string[] fncGraylevelmapII = new string[2];
        //sharpening
        static string[] fncSharpingI = new string[2];
        static string[] fncSharpingII = new string[2];
        static string[] fncHighpassspatial = new string[2];
        static string[] fncHighboost = new string[2];
        static string[] fncUnsharpmasking = new string[2];
        static string[] fncFftsharpening = new string[2];
        static string[] fncDctsharpening = new string[2];
        static string[] fncHighfreqemph = new string[2];
        static string[] fncHomomorphic = new string[2];
        //smoothing
        static string[] fncAdapanisotropic = new string[2];
        static string[] fncMean = new string[2];
        static string[] fncFftsmooth = new string[2];
        static string[] fncDctsmooth = new string[2];
        //utilities
        //arith/logic
        static string[] fncAdd = new string[2];
        static string[] fncSubtract = new string[2];
        static string[] fncMultiply = new string[2];
        static string[] fncDivide = new string[2];
        static string[] fncAnd = new string[2];
        static string[] fncNot = new string[2];
        static string[] fncOr = new string[2];
        static string[] fncXor = new string[2];
        //compare
        static string[] fncCompSub = new string[2];
        static string[] fncCompXor = new string[2];
        static string[] fncSnr = new string[2];
        static string[] fncRms = new string[2];
        //convert
        static string[] fncConvThreshold = new string[2];
        static string[] fncConvByte = new string[2];
        static string[] fncConvShort = new string[2];
        static string[] fncConvInteger = new string[2];
        static string[] fncConvFloat = new string[2];
        static string[] fncConvHalftone = new string[2];
        static string[] fncConvGLQ = new string[2];
        static string[] fncConvGraycode = new string[2];
        static string[] fncConvPseudo = new string[2];
        static string[] fncConvLum = new string[2];
        static string[] fncConvLumavg = new string[2];
        static string[] fncConvXYZ = new string[2];
        static string[] fncConvInvXYZ = new string[2];
        static string[] fncConvLAB = new string[2];
        static string[] fncConvInvLAB = new string[2];
        static string[] fncConvLUV = new string[2];
        static string[] fncConvInvLUV = new string[2];
        static string[] fncConvCCT = new string[2];
        static string[] fncConvInvCCT = new string[2];
        static string[] fncConvHSL = new string[2];
        static string[] fncConvInvHSL = new string[2];
        static string[] fncConvHSV = new string[2];
        static string[] fncConvInvHSV = new string[2];
        static string[] fncConvPCT = new string[2];
        static string[] fncConvInvPCT = new string[2];
        static string[] fncConvSCT = new string[2];
        static string[] fncConvInvSCT = new string[2];
        static string[] fncConvLabel = new string[2];
        //create
        static string[] fncCrtCheckboard = new string[2];
        static string[] fncCrtCircle = new string[2];
        static string[] fncCrtEllipse = new string[2];
        static string[] fncCrtLine = new string[2];
        static string[] fncCrtRectangle = new string[2];
        static string[] fncCrtCosinewave = new string[2];
        static string[] fncCrtSinewave = new string[2];
        static string[] fncCrtSquarewave = new string[2];
        static string[] fncCrtBlackimage = new string[2];
        static string[] fncCrtExtractbandRed = new string[2];
        static string[] fncCrtExtractbandGreen = new string[2];
        static string[] fncCrtExtractbandBlue = new string[2];
        static string[] fncCrtAssembleBands = new string[2];
        static string[] fncCrtBordermask = new string[2];
        static string[] fncCrtBorderimage = new string[2];
        static string[] fncCrtAddnoiseGamma = new string[2];
        static string[] fncCrtAddnoiseGaussian = new string[2];
        static string[] fncCrtAddnoiseNegExponential = new string[2];
        static string[] fncCrtAddnoiseRayleigh = new string[2];
        static string[] fncCrtAddnoiseSaltPepper = new string[2];
        static string[] fncCrtAddnoiseUniform = new string[2];
        //enhance
        static string[] fncEnhHighFreqEmphasis = new string[2];
        static string[] fncEnhUnsharp = new string[2];
        static string[] fncEnhFFTSharp = new string[2];
        static string[] fncEnhDCTSharp = new string[2];
        static string[] fncEnhHistEq = new string[2];
        static string[] fncEnhHistStretch = new string[2];
        static string[] fncEnhPseudocolor = new string[2];
        static string[] fncEnhSharpening = new string[2];
        //Size
        static string[] fncSzeCrop = new string[2];
        static string[] fncSzeFstDublSze = new string[2];
        static string[] fncSzeReSze = new string[2];
        static string[] fncSzeSptialQuant = new string[2];

        static CvipFunctionNames()
        {
            //edge-detection
            fncLaplacian[0] = "laplacian";
            fncLaplacian[1] = "lapl";
            fncRoberts[0] = "roberts";
            fncRoberts[1] = "rob";
            fncSobel[0] = "sobel";
            fncSobel[1] = "sbl";
            fncSobelDirection[0] = "_sobel_dir";
            fncSobelDirection[1] = "_sbl_dr";
            fncPrewitt[0] = "prewitt";
            fncPrewitt[1] = "prwt";
            fncPrewittDirection[0] = "_prewitt_dir";
            fncPrewittDirection[1] = "_prwt_dr";
            fncKirsch[0] = "kirsch";
            fncKirsch[1] = "krsh";
            fncKirschDirection[0] = "_kirsch_dir";
            fncKirschDirection[1] = "_krsh_dr";
            fncRobinson[0] = "robinson";
            fncRobinson[1] = "robsn";
            fncRobinsonDirection[0] = "_robinson_dir";
            fncRobinsonDirection[1] = "_robsn_dr";
            fncPyramid[0] = "pyramid";
            fncPyramid[1] = "pyr";
            fncFreichen[0] = "freichen";
            fncFreichen[1] = "frchn";
            fncCerchar[0] = "cerchar";
            fncCerchar[1] = "crchr";
            fncMarrhildreth[0] = "marrhildreth";
            fncMarrhildreth[1] = "mrhil";
            fncMarrhildrethSigmaPlusDelta[0] = "_marrhildreth_sigma+delta";
            fncMarrhildrethSigmaPlusDelta[1] = "_mrhil_sgm+dlt";
            fncMarrhildrethSigmaMinusDelta[0] = "_marrhildreth_sigma-delta";
            fncMarrhildrethSigmaMinusDelta[1] = "_mrhil_sgm-dlt";
            fncCanny[0] = "canny";
            fncCanny[1] = "cny";
            fncCannyMagnitude[0] = "_canny_mag";
            fncCannyMagnitude[1] = "_cny_mg";
            fncCannyDirection[0] = "_canny_dir";
            fncCannyDirection[1] = "_cny_dir";
            fncBoiecox[0] = "boiecox";
            fncBoiecox[1] = "bocx";
            fncBoiecoxThreshold[0] = "_boiecox_Threshold";
            fncBoiecoxThreshold[1] = "_bocx_Thr";
            fncBoiecoxHyst[0] = "_boiecox_Hyst";
            fncBoiecoxHyst[1] = "_bocx_Hyst";
            fncShencastan[0] = "shencastan";
            fncShencastan[1] = "shncst";
            fncShencastanZeroInter[0] = "_shencastan_ZeroInter";
            fncShencastanZeroInter[1] = "_shncst_ZIntr";
            fncMoravec[0] = "moravec";
            fncMoravec[1] = "mrvc";
            fncHarris[0] = "harris";
            fncHarris[1] = "hrrs";
            fncHough[0] = "hough";
            fncHough[1] = "hgh";
            fncEdgelink[0] = "edgelink";
            fncEdgelink[1] = "edlnk";
            fncPratt[0] = "pratt";
            fncPratt[1] = "prtt";
            //geometry
            fncCrop[0] = "crop";
            fncCrop[1] = "crp";
            fncPaste[0] = "paste";
            fncPaste[1] = "pst";
            fncResize[0] = "resize";
            fncResize[1] = "rsz";
            fncRotate[0] = "rotate";
            fncRotate[1] = "rot";
            fncTranslate[0] = "translate";
            fncTranslate[1] = "trnslt";
            fncZoom[0] = "zoom";
            fncZoom[1] = "zm";
            //transforms
            fncDct[0] = "dct";
            fncDct[1] = "dct";
            fncFft[0] = "fft";
            fncFft[1] = "fft";
            fncWalhad[0] = "walhad";
            fncWalhad[1] = "walhad";
            fncHadamard[0] = "hadamard";
            fncHadamard[1] = "had";
            fncHaar[0] = "haar";
            fncHaar[1] = "haar";
            fncWavelet[0] = "wavelet";
            fncWavelet[1] = "wvlt";
            fncLowpass[0] = "low_pass";
            fncLowpass[1] = "lp";
            fncHighpass[0] = "high_pass";
            fncHighpass[1] = "hp";
            fncBandpass[0] = "band_pass";
            fncBandpass[1] = "bp";
            fncBandreject[0] = "band_reject";
            fncBandreject[1] = "brej";
            fncHighfreqemphasis[0] = "high_freq_emphasis";
            fncHighfreqemphasis[1] = "hfe";
            fncNotch[0] = "notch";
            fncNotch[1] = "ntch";
            fncFftphase[0] = "fft_phase";
            fncFftphase[1] = "fft_ph";
            fncFftmagnitude[0] = "fft_magnitude";
            fncFftmagnitude[1] = "fft_mg";
            //segmentation
            fncGrayquant[0] = "grayQuant";
            fncGrayquant[1] = "grQnt";
            fncFuzzyc[0] = "fuzzyC";
            fncFuzzyc[1] = "fzyC";
            fncAutothreshold[0] = "autoThreshold";
            fncAutothreshold[1] = "autThr";
            fncOutsu[0] = "otsu";
            fncOutsu[1] = "otsu";
            fncGvfsnake[0] = "gvfSnake";
            fncGvfsnake[1] = "gvfSnk";
            fncLivewire[0] = "livewire";
            fncLivewire[1] = "lvewr";
            fncHistthreshold[0] = "histThreshold";
            fncHistthreshold[1] = "hstThr";
            fncMedcut[0] = "medCut";
            fncMedcut[1] = "mCt";
            fncPctmed[0] = "pctMed";
            fncPctmed[1] = "pctMd";
            fncSct[0] = "sct";
            fncSct[1] = "sct";
            fncMultires[0] = "multiRes";
            fncMultires[1] = "mulRs";
            fncSplitmerge[0] = "splitMerge";
            fncSplitmerge[1] = "splMrg";
            fncWatershed[0] = "watershed";
            fncWatershed[1] = "wtrshd";
            fncMorphc[0] = "morphC";
            fncMorphc[1] = "mrphC";
            fncMorpho[0] = "morphO";
            fncMorpho[1] = "mrphO";
            fncMorphe[0] = "morphE";
            fncMorphe[1] = "mrphE";
            fncMorphd[0] = "morphD";
            fncMorphd[1] = "mrphD";
            fncMorphi[0] = "morphI";
            fncMorphi[1] = "mrphI";
            fncMorphhit[0] = "morphHit";
            fncMorphhit[1] = "mrpHt";
            fncMorphthin[0] = "morphThin";
            fncMorphthin[1] = "mrphThn";
            fncMorphskel[0] = "morphSkel";
            fncMorphskel[1] = "mrphSkl";
            //feature
            fncLabel[0] = "_Label";
            fncLabel[1] = "_Lbl";
            //lossless
            fncHuffman[0] = "Huffman";
            fncHuffman[1] = "Hfmn";
            fncZivlempel[0] = "ZivLempel";
            fncZivlempel[1] = "ZvLmp";
            fncDpc[0] = "DPC";
            fncDpc[1] = "DPC";
            fncBitplane[0] = "Bitplane";
            fncBitplane[1] = "Btpln";
            fncJpeg2000[0] = "JPEG2_";
            fncJpeg2000[1] = "JPG2_";
            //lossy
            fncBtc[0] = "BTC";
            fncBtc[1] = "BTC";
            fncMbtc[0] = "MBTC";
            fncMbtc[1] = "MBTC";
            fncPmbtc[0] = "PMBTC";
            fncPmbtc[1] = "PMBTC";
            fncJpeg[0] = "JPEG";
            fncJpeg[1] = "JPG";
            fncDyrlc[0] = "DyRLC";
            fncDyrlc[1] = "DyRLC";
            fncBitplanerlc[0] = "BitplaneRLC";
            fncBitplanerlc[1] = "BtplRLC";
            fncZonal[0] = "Zonal";
            fncZonal[1] = "Znl";
            fncFractal[0] = "Fractal";
            fncFractal[1] = "Frctl";
            fncXvq[0] = "XVQ";
            fncXvq[1] = "XVQ";
            fncVq[0] = "VQ";
            fncVq[1] = "VQ";
            fncTransformcompression[0] = "XfrmCmpr";
            fncTransformcompression[1] = "XfrmCmpr";
            //preprocessing
            fncBin2gray[0] = "bin2gray";
            fncBin2gray[1] = "bn2gry";
            fncGray2bin[0] = "gray2bin";
            fncGray2bin[1] = "gry2bn";
            fncSpatialquant[0] = "spatialquant";
            fncSpatialquant[1] = "spqnt";
            fncGquant[0] = "grayquant";
            fncGquant[1] = "gryqnt";
            //frequency filter
            fncInverse[0] = "inverse";
            fncInverse[1] = "inv";
            fncGeomean[0] = "geoMean";
            fncGeomean[1] = "geoMn";
            fncPowerspecteq[0] = "powerSpectEq";
            fncPowerspecteq[1] = "pwrSptEq";
            fncConstleastsqu[0] = "constLeastSqu";
            fncConstleastsqu[1] = "cnstLstSq";
            fncWiener[0] = "wiener";
            fncWiener[1] = "wenr";
            fncPractwiener[0] = "practWiener";
            fncPractwiener[1] = "pracWenr";
            fncParawiener[0] = "paraWiener";
            fncParawiener[1] = "paraWenr";
            //geometric transform
            fncNewmesh[0] = "newmesh";
            fncNewmesh[1] = "nwmsh";
            fncOpenmesh[0] = "openmesh";
            fncOpenmesh[1] = "opnmsh";
            fncSinemesh[0] = "sinemesh";
            fncSinemesh[1] = "sinmsh";
            //noise
            fncNegexp[0] = "negexp";
            fncNegexp[1] = "negexp";
            fncRayleigh[0] = "rayleigh";
            fncRayleigh[1] = "rayl";
            fncGaussian[0] = "gaussian";
            fncGaussian[1] = "gaus";
            fncUniform[0] = "uniform";
            fncUniform[1] = "unfrm";
            fncGamma[0] = "gamma";
            fncGamma[1] = "gam";
            fncSaltpepper[0] = "saltpepper";
            fncSaltpepper[1] = "sltpepr";
            //spatial filter
            fncMedian[0] = "median";
            fncMedian[1] = "medn";
            fncMinimum[0] = "minimum";
            fncMinimum[1] = "min";
            fncMidpoint[0] = "midpoint";
            fncMidpoint[1] = "mdpt";
            fncMaximum[0] = "maximum";
            fncMaximum[1] = "max";
            fncAlphamean[0] = "alphamean";
            fncAlphamean[1] = "alphmn";
            fncArithmetic[0] = "arithmetic";
            fncArithmetic[1] = "arith";
            fncGeometric[0] = "geometric";
            fncGeometric[1] = "geomtrc";
            fncHarmonic[0] = "harmonic";
            fncHarmonic[1] = "harmnc";
            fncContra[0] = "contra";
            fncContra[1] = "cntra";
            fncYpmean[0] = "ypmean";
            fncYpmean[1] = "ypmn";
            fncMmse[0] = "mmse";
            fncMmse[1] = "mmse";
            fncAdaptmedian[0] = "adaptmedian";
            fncAdaptmedian[1] = "adapmed";
            fncKuwahara[0] = "kuwahara";
            fncKuwahara[1] = "kwhra";
            fncAdaptcontrast[0] = "adaptcontrast";
            fncAdaptcontrast[1] = "adpcntr";
            fncAnisotropic[0] = "anisotropic";
            fncAnisotropic[1] = "ad";
            //histogram
            fncHisteq[0] = "HistEQ";
            fncHisteq[1] = "HstEQ";
            fncHistslide[0] = "HistSlide";
            fncHistslide[1] = "HstSl";
            fncHiststretch[0] = "HistStretch";
            fncHiststretch[1] = "HstStr";
            fncHistshrink[0] = "HistShrink";
            fncHistshrink[1] = "HstSrnk";
            fncLocaleq[0] = "LocalEQ";
            fncLocaleq[1] = "LocEQ";
            fncAce[0] = "ACE";
            fncAce[1] = "ACE";
            fncAceII[0] = "ACEII";
            fncAceII[1] = "ACEII";
            fncLogace[0] = "logACE";
            fncLogace[1] = "logACE";
            fncExpace[0] = "expACE";
            fncExpace[1] = "expACE";
            fncHistspec[0] = "HistSpec";
            fncHistspec[1] = "HstSpc";
            fncLinearmod[0] = "LinearMod";
            fncLinearmod[1] = "LinMod";
            fncGraylevelmult[0] = "GrayLevelMult";
            fncGraylevelmult[1] = "GryLMult";
            fncShowhistogram[0] = "_histogram";
            fncShowhistogram[1] = "_hstogr";
            fncShowhistogramspec[0] = "_spec";
            fncShowhistogramspec[1] = "_spc";
            fncShowhistogramresult[0] = "_result";
            fncShowhistogramresult[1] = "_rsult";
            fncColorenhancement[0] = "ColorContrastEnhance";
            fncColorenhancement[1] = "ClrCnEn";
            fncCLAHE[0] = "CLAHE";
            fncCLAHE[1] = "CLAHE";
            //pseudocolor
            fncGraylevelmap[0] = "GrayLevelMap";
            fncGraylevelmap[1] = "GryLevMp";
            fncFrequencydomainmap[0] = "FreqMap";
            fncFrequencydomainmap[1] = "FrqMp";
            fncIntensityslice[0] = "IntensitySlice";
            fncIntensityslice[1] = "IntSlce";
            fncGraylevelmapII[0] = "Pseudo_Remap";
            fncGraylevelmapII[1] = "Psdo_Rmp";
            //sharpening
            fncSharpingI[0] = "SharpI";
            fncSharpingI[1] = "ShrpI";
            fncSharpingII[0] = "SharpII";
            fncSharpingII[1] = "ShrpII";
            fncHighpassspatial[0] = "Highpass";
            fncHighpassspatial[1] = "HpSptl";
            fncHighboost[0] = "HighBoost";
            fncHighboost[1] = "HiBst";
            fncUnsharpmasking[0] = "Unsharp";
            fncUnsharpmasking[1] = "Unshrp";
            fncFftsharpening[0] = "FFTSharpen";
            fncFftsharpening[1] = "FFTShrp";
            fncDctsharpening[0] = "DCTSharpen";
            fncDctsharpening[1] = "DCTShrp";
            fncHighfreqemph[0] = "HighFreqEmph";
            fncHighfreqemph[1] = "HiFrqEmph";
            fncHomomorphic[0] = "Homomorphic";
            fncHomomorphic[1] = "Homrphc";
            //smoothing
            fncAdapanisotropic[0] = "param_anisotropic";
            fncAdapanisotropic[1] = "param_ad";
            fncMean[0] = "mean";
            fncMean[1] = "mean";
            fncFftsmooth[0] = "fftsmooth";
            fncFftsmooth[1] = "fftsmth";
            fncDctsmooth[0] = "dctsmooth";
            fncDctsmooth[1] = "dctsmth";
            //utilities
            //arith/logic
            fncAdd[0] = "Add";
            fncAdd[1] = "Add";
            fncSubtract[0] = "Subtract";
            fncSubtract[1] = "Sbtrct";
            fncMultiply[0] = "Multiply";
            fncMultiply[1] = "Mul";
            fncDivide[0] = "Divide";
            fncDivide[1] = "Div";
            fncAnd[0] = "AND";
            fncAnd[1] = "AND";
            fncNot[0] = "NOT";
            fncNot[1] = "NOT";
            fncOr[0] = "OR";
            fncOr[1] = "OR";
            fncXor[0] = "XOR";
            fncXor[1] = "XOR";
            //compare
            fncCompSub[0] = "Sub";
            fncCompSub[1] = "Sub";
            fncCompXor[0] = "XOR";
            fncCompXor[1] = "XOR";
            fncSnr[0] = "SNR";
            fncSnr[1] = "SNR";
            fncRms[0] = "RMS";
            fncRms[1] = "RMS";
            //convert
            fncConvThreshold[0] = "Thresh";
            fncConvThreshold[1] = "Thresh";
            fncConvByte[0] = "BYTE";
            fncConvByte[1] = "BYT";
            fncConvShort[0] = "SHORT";
            fncConvShort[1] = "SHRT";
            fncConvInteger[0] = "INTGER";
            fncConvInteger[1] = "INT";
            fncConvFloat[0] = "FLOAT";
            fncConvFloat[1] = "FLT";
            fncConvHalftone[0] = "Halftone";
            fncConvHalftone[1] = "Hlfton";
            fncConvGLQ[0] = "GLQ";
            fncConvGLQ[1] = "GLQ";
            fncConvGraycode[0] = "GrayCode";
            fncConvGraycode[1] = "GryCod";
            fncConvPseudo[0] = "Pseudo";
            fncConvPseudo[1] = "Psudo";
            fncConvLum[0] = "Lum";
            fncConvLum[1] = "Lum";
            fncConvLumavg[0] = "LumAvg";
            fncConvLumavg[1] = "LumAvg";
            fncConvXYZ[0] = "XYZ";
            fncConvXYZ[1] = "XYZ";
            fncConvInvXYZ[0] = "InvXYZ";
            fncConvInvXYZ[1] = "InvXYZ";
            fncConvLAB[0] = "LAB";
            fncConvLAB[1] = "LAB";
            fncConvInvLAB[0] = "InvLAB";
            fncConvInvLAB[1] = "InvLAB";
            fncConvLUV[0] = "LUV";
            fncConvLUV[1] = "LUV";
            fncConvInvLUV[0] = "InvLUV";
            fncConvInvLUV[1] = "InvLUV";
            fncConvCCT[0] = "CCT";
            fncConvCCT[1] = "CCT";
            fncConvInvCCT[0] = "InvCCT";
            fncConvInvCCT[1] = "InvCCT";
            fncConvHSL[0] = "HSL";
            fncConvHSL[1] = "HSL";
            fncConvInvHSL[0] = "InvHSL";
            fncConvInvHSL[1] = "InvHSL";
            fncConvHSV[0] = "HSV";
            fncConvHSV[1] = "HSV";
            fncConvInvHSV[0] = "InvHSV";
            fncConvInvHSV[1] = "InvHSV";
            fncConvPCT[0] = "PCT";
            fncConvPCT[1] = "PCT";
            fncConvInvPCT[0] = "InvPCT";
            fncConvInvPCT[1] = "InvPCT";
            fncConvSCT[0] = "SCT";
            fncConvSCT[1] = "SCT";
            fncConvInvSCT[0] = "InvSCT";
            fncConvInvSCT[1] = "InvSCT";
            fncConvLabel[0] = "Label";
            fncConvLabel[1] = "Label";
            //create
            fncCrtCheckboard[0] = "Checkerboard";
            fncCrtCheckboard[1] = "Chckrbrd";
            fncCrtCircle[0] = "Circle";
            fncCrtCircle[1] = "Crcle";
            fncCrtEllipse[0] = "Ellipse";
            fncCrtEllipse[1] = "Ellps";
            fncCrtLine[0] = "Line";
            fncCrtLine[1] = "Line";
            fncCrtRectangle[0] = "Rectangle";
            fncCrtRectangle[1] = "Rctngle";
            fncCrtCosinewave[0] = "Cosine_Wave";
            fncCrtCosinewave[1] = "Cos_Wve";
            fncCrtSinewave[0] = "Sine_Wave";
            fncCrtSinewave[1] = "Sin_Wve";
            fncCrtSquarewave[0] = "Square_Wave";
            fncCrtSquarewave[1] = "Sqr_Wve";
            fncCrtBlackimage[0] = "Black_Image";
            fncCrtBlackimage[1] = "Blck_Img";
            fncCrtExtractbandRed[0] = "bandR";
            fncCrtExtractbandRed[1] = "bndR";
            fncCrtExtractbandGreen[0] = "bandG";
            fncCrtExtractbandGreen[1] = "bndG";
            fncCrtExtractbandBlue[0] = "bandB";
            fncCrtExtractbandBlue[1] = "bndB";
            fncCrtAssembleBands[0] = "Assemble_Bands";
            fncCrtAssembleBands[1] = "AsmBnd";
            fncCrtBordermask[0] = "Border_Mask";
            fncCrtBordermask[1] = "Brdr_Msk";
            fncCrtBorderimage[0] = "Border_Image";
            fncCrtBorderimage[1] = "Brdr_Img";
            fncCrtAddnoiseGamma[0] = "Gamma_Noise";
            fncCrtAddnoiseGamma[1] = "Gamma_Noise";
            fncCrtAddnoiseGaussian[0] = "Gaussian_Noise";
            fncCrtAddnoiseGaussian[1] = "Gaussian_Noise";
            fncCrtAddnoiseNegExponential[0] = "Neg_Exp_Noise";
            fncCrtAddnoiseNegExponential[1] = "Neg_Exp_Noise";
            fncCrtAddnoiseRayleigh[0] = "Rayleigh_Noise";
            fncCrtAddnoiseRayleigh[1] = "Rayleigh_Noise";
            fncCrtAddnoiseSaltPepper[0] = "Salt_Pepper_Noise";
            fncCrtAddnoiseSaltPepper[1] = "Salt_Pepper_Noise";
            fncCrtAddnoiseUniform[0] = "Uniform_Noise";
            fncCrtAddnoiseUniform[1] = "Uniform_Noise";
            //enhance
            fncEnhHighFreqEmphasis[0] = "Hfe";
            fncEnhHighFreqEmphasis[1] = "Hfe";
            fncEnhUnsharp[0] = "Unsharp";
            fncEnhUnsharp[1] = "Ushrp";
            fncEnhFFTSharp[0] = "FFTSharp";
            fncEnhFFTSharp[1] = "FFTShrp";
            fncEnhDCTSharp[0] = "DCTSharp";
            fncEnhDCTSharp[1] = "DCTShrp";
            fncEnhHistEq[0] = "Heq";
            fncEnhHistEq[1] = "Heq";
            fncEnhHistStretch[0] = "HistStretch";
            fncEnhHistStretch[1] = "HstStrtch";
            fncEnhPseudocolor[0] = "Pseudo";
            fncEnhPseudocolor[1] = "Psudo";
            fncEnhSharpening[0] = "Sharpening";
            fncEnhSharpening[1] = "Shrpng";
            //Size
            fncSzeCrop[0]  = "Crop";
            fncSzeCrop[1]  = "Crp";
            fncSzeFstDublSze[0] = "DoubleSize";
            fncSzeFstDublSze[1] = "DblSz";
            fncSzeReSze[0]  = "ReSize";
            fncSzeReSze[1] = "ReSz";
            fncSzeSptialQuant[0] = "SpatialQuant";
            fncSzeSptialQuant[1] = "SpQnt";


        }

        public static string getFncName(string selection)
        {
            switch (selection)
            {
            case "laplacian":
                return fncLaplacian[longFileNamesChecked];
            case "roberts":
                return fncRoberts[longFileNamesChecked];
            case "sobel":
                return fncSobel[longFileNamesChecked];
            case "sobel_direction":
                return fncSobelDirection[longFileNamesChecked];
            case "prewitt":
                return fncPrewitt[longFileNamesChecked];
            case "prewitt_direction":
                return fncPrewittDirection[longFileNamesChecked];
            case "kirsch":
                return fncKirsch[longFileNamesChecked];
            case "kirsch_direction":
                return fncKirschDirection[longFileNamesChecked];
            case "robinson":
                return fncRobinson[longFileNamesChecked];
            case "robinson_direction":
                return fncRobinsonDirection[longFileNamesChecked];
            case "pyramid":
                return fncPyramid[longFileNamesChecked];
            case "freichen":
                return fncFreichen[longFileNamesChecked];
            case "cerchar":
                return fncCerchar[longFileNamesChecked];
            case "marrhildreth":
                return fncMarrhildreth[longFileNamesChecked];
            case "marrhildreth_sigma+delta":
                return fncMarrhildrethSigmaPlusDelta[longFileNamesChecked];
            case "marrhildreth_sigma-delta":
                return fncMarrhildrethSigmaMinusDelta[longFileNamesChecked];
            case "canny":
                return fncCanny[longFileNamesChecked];
            case "canny_magnitude":
                return fncCannyMagnitude[longFileNamesChecked];
            case "canny_direction":
                return fncCannyDirection[longFileNamesChecked];
            case "boiecox":
                return fncBoiecox[longFileNamesChecked];
            case "boiecox_threshold":
                return fncBoiecoxThreshold[longFileNamesChecked];
            case "boiecox_hyst":
                return fncBoiecoxHyst[longFileNamesChecked];
            case "shencastan":
                return fncShencastan[longFileNamesChecked];
            case "shencastan_zerointer":
                return fncShencastanZeroInter[longFileNamesChecked];
            case "moravec":
                return fncMoravec[longFileNamesChecked];
            case "harris":
                return fncHarris[longFileNamesChecked];
            case "hough":
                return fncHough[longFileNamesChecked];
            case "edgelink":
                return fncEdgelink[longFileNamesChecked];
            case "pratt":
                return fncPratt[longFileNamesChecked];
            case "crop":
                return fncCrop[longFileNamesChecked];
            case "paste":
                return fncPaste[longFileNamesChecked];
            case "resize":
                return fncResize[longFileNamesChecked];
            case "rotate":
                return fncRotate[longFileNamesChecked];
            case "translate":
                return fncTranslate[longFileNamesChecked];
            case "zoom":
                return fncZoom[longFileNamesChecked];
            case "dct":
                return fncDct[longFileNamesChecked];
            case "fft":
                return fncFft[longFileNamesChecked];
            case "walhad":
                return fncWalhad[longFileNamesChecked];
            case "hadamard":
                return fncHadamard[longFileNamesChecked];
            case "haar":
                return fncHaar[longFileNamesChecked];
            case "wavelet":
                return fncWavelet[longFileNamesChecked];
            case "low_pass":
                return fncLowpass[longFileNamesChecked];
            case "high_pass":
                return fncHighpass[longFileNamesChecked];
            case "band_pass":
                return fncBandpass[longFileNamesChecked];
            case "band_reject":
                return fncBandreject[longFileNamesChecked];
            case "high_freq_emphasis":
                return fncHighfreqemphasis[longFileNamesChecked];
            case "notch":
                return fncNotch[longFileNamesChecked];
            case "fft_phase":
                return fncFftphase[longFileNamesChecked];
            case "fft_magnitude":
                return fncFftmagnitude[longFileNamesChecked];
            case "grayQuant":
                return fncGrayquant[longFileNamesChecked];
            case "fuzzyc":
                return fncFuzzyc[longFileNamesChecked];
            case "autoThreshold":
                return fncAutothreshold[longFileNamesChecked];
            case "otsu":
                return fncOutsu[longFileNamesChecked];
            case "gvfSnake":
                return fncGvfsnake[longFileNamesChecked];
            case "livewire":
                return fncLivewire[longFileNamesChecked];
            case "histThreshold":
                return fncHistthreshold[longFileNamesChecked];
            case "medCut":
                return fncMedcut[longFileNamesChecked];
            case "pctMed":
                return fncPctmed[longFileNamesChecked];
            case "sct":
                return fncSct[longFileNamesChecked];
            case "multiRes":
                return fncMultires[longFileNamesChecked];
            case "splitMerge":
                return fncSplitmerge[longFileNamesChecked];
            case "watershed":
                return fncWatershed[longFileNamesChecked];
            case "morphC":
                return fncMorphc[longFileNamesChecked];
            case "morphO":
                return fncMorpho[longFileNamesChecked];
            case "morphE":
                return fncMorphe[longFileNamesChecked];
            case "morphD":
                return fncMorphd[longFileNamesChecked];
            case "morphI":
                return fncMorphi[longFileNamesChecked];
            case "morphHit":
                return fncMorphhit[longFileNamesChecked];
            case "morphThin":
                return fncMorphthin[longFileNamesChecked];
            case "morphSkel":
                return fncMorphskel[longFileNamesChecked];
            case "_Label":
                return fncLabel[longFileNamesChecked];
            case "Huffman":
                return fncHuffman[longFileNamesChecked];
            case "ZivLempel":
                return fncZivlempel[longFileNamesChecked];
            case "DPC":
                return fncDpc[longFileNamesChecked];
            case "Bitplane":
                return fncBitplane[longFileNamesChecked];
            case "JPEG2_":
                return fncJpeg2000[longFileNamesChecked];
            case "BTC":
                return fncBtc[longFileNamesChecked];
            case "MBTC":
                return fncMbtc[longFileNamesChecked];
            case "PMBTC":
                return fncPmbtc[longFileNamesChecked];
            case "JPEG":
                return fncJpeg[longFileNamesChecked];
            case "DyRLC":
                return fncDyrlc[longFileNamesChecked];
            case "BitplaneRLC":
                return fncBitplanerlc[longFileNamesChecked];
            case "Zonal":
                return fncZonal[longFileNamesChecked];
            case "Fractal":
                return fncFractal[longFileNamesChecked];
            case "XVQ":
                return fncXvq[longFileNamesChecked];
            case "VQ":
                return fncVq[longFileNamesChecked];
            case "XfrmCmpr":
                return fncTransformcompression[longFileNamesChecked];
            case "bin2gray":
                return fncBin2gray[longFileNamesChecked];
            case "gray2bin":
                return fncGray2bin[longFileNamesChecked];
            case "spatialquant":
                return fncSpatialquant[longFileNamesChecked];
            case "grayquant":
                return fncGquant[longFileNamesChecked];
            case "inverse":
                return fncInverse[longFileNamesChecked];
            case "geoMean":
                return fncGeomean[longFileNamesChecked];
            case "powerSpectEq":
                return fncPowerspecteq[longFileNamesChecked];
            case "constLeastSqu":
                return fncConstleastsqu[longFileNamesChecked];
            case "wiener":
                return fncWiener[longFileNamesChecked];
            case "practWiener":
                return fncPractwiener[longFileNamesChecked];
            case "paraWiener":
                return fncParawiener[longFileNamesChecked];
            case "newmesh":
                return fncNewmesh[longFileNamesChecked];
            case "openmesh":
                return fncOpenmesh[longFileNamesChecked];
            case "sinemesh":
                return fncSinemesh[longFileNamesChecked];
            case "negexp":
                return fncNegexp[longFileNamesChecked];
            case "rayleigh":
                return fncRayleigh[longFileNamesChecked];
            case "gaussian":
                return fncGaussian[longFileNamesChecked];
            case "uniform":
                return fncUniform[longFileNamesChecked];
            case "gamma":
                return fncGamma[longFileNamesChecked];
            case "saltpepper":
                return fncSaltpepper[longFileNamesChecked];
            case "median":
                return fncMedian[longFileNamesChecked];
            case "minimum":
                return fncMinimum[longFileNamesChecked];
            case "midpoint":
                return fncMidpoint[longFileNamesChecked];
            case "maximum":
                return fncMaximum[longFileNamesChecked];
            case "alphamean":
                return fncAlphamean[longFileNamesChecked];
            case "arithmetic":
                return fncArithmetic[longFileNamesChecked];
            case "geometric":
                return fncGeometric[longFileNamesChecked];
            case "harmonic":
                return fncHarmonic[longFileNamesChecked];
            case "contra":
                return fncContra[longFileNamesChecked];
            case "ypmean":
                return fncYpmean[longFileNamesChecked];
            case "mmse":
                return fncMmse[longFileNamesChecked];
            case "adapmedian":
            case "adaptmedian":
                return fncAdaptmedian[longFileNamesChecked];
            case "kuwahara":
                return fncKuwahara[longFileNamesChecked];
            case "adaptcontrast":
                return fncAdaptcontrast[longFileNamesChecked];
            case "anisotropic":
                return fncAnisotropic[longFileNamesChecked];
            case "HistEQ":
                return fncHisteq[longFileNamesChecked];
            case "HistSlide":
                return fncHistslide[longFileNamesChecked];
            case "HistStretch":
                return fncHiststretch[longFileNamesChecked];
            case "HistShrink":
                return fncHistshrink[longFileNamesChecked];
            case "LocalEQ":
                return fncLocaleq[longFileNamesChecked];
            case "CLAHE":
                return fncCLAHE[longFileNamesChecked];
            case "ACE":
                return fncAce[longFileNamesChecked];
            case "ACEII":
                return fncAceII[longFileNamesChecked];
            case "logACE":
                return fncLogace[longFileNamesChecked];
            case "expACE":
                return fncExpace[longFileNamesChecked];
            case "HistSpec":
                return fncHistspec[longFileNamesChecked];
            case "LinearMod":
                return fncLinearmod[longFileNamesChecked];
            case "GrayLevelMult":
                return fncGraylevelmult[longFileNamesChecked];
            case "_histogram":
                return fncShowhistogram[longFileNamesChecked];
            case "_spec":
                return fncShowhistogramspec[longFileNamesChecked];
            case "_result":
                return fncShowhistogramresult[longFileNamesChecked];
            case "ColorEnhancement":
                return fncColorenhancement[longFileNamesChecked];
            case "GrayLevelMap":
                return fncGraylevelmap[longFileNamesChecked];
            case "FreqMap":
                return fncFrequencydomainmap[longFileNamesChecked];
            case "IntensitySlice":
                return fncIntensityslice[longFileNamesChecked];
            case "Pseudo_Remap":
                return fncGraylevelmapII[longFileNamesChecked];
            case "SharpI":
                return fncSharpingI[longFileNamesChecked];
            case "SharpII":
                return fncSharpingII[longFileNamesChecked];
            case "Highpass":
                return fncHighpassspatial[longFileNamesChecked];
            case "HighBoost":
                return fncHighboost[longFileNamesChecked];
            case "Unsharp":
                return fncUnsharpmasking[longFileNamesChecked];
            case "FFTSharpen":
                return fncFftsharpening[longFileNamesChecked];
            case "DCTSharpen":
                return fncDctsharpening[longFileNamesChecked];
            case "HighFreqEmph":
                return fncHighfreqemph[longFileNamesChecked];
            case "Homomorphic":
                return fncHomomorphic[longFileNamesChecked];
            case "adapanisotropic":
                return fncAdapanisotropic[longFileNamesChecked];
            case "mean":
                return fncMean[longFileNamesChecked];
            case "fftsmooth":
                return fncFftsmooth[longFileNamesChecked];
            case "dctsmooth":
                return fncDctsmooth[longFileNamesChecked];
            case "Add":
                return fncAdd[longFileNamesChecked];
            case "Subtract":
                return fncSubtract[longFileNamesChecked];
            case "Multiply":
                return fncMultiply[longFileNamesChecked];
            case "Divide":
                return fncDivide[longFileNamesChecked];
            case "AND":
                return fncAnd[longFileNamesChecked];
            case "NOT":
                return fncNot[longFileNamesChecked];
            case "OR":
                return fncOr[longFileNamesChecked];
            case "XOR":
                return fncXor[longFileNamesChecked];
            case "Sub":
                return fncCompSub[longFileNamesChecked];
            //case "XOR":
            //    return fncCompXor[longFileNamesChecked];  same name with XOR in Arith/Logic: Disabled
            case "SNR":
                return fncSnr[longFileNamesChecked];
            case "RMS":
                return fncRms[longFileNamesChecked];
            case "Thresh":
                return fncConvThreshold[longFileNamesChecked];
            case "BYTE":
                return fncConvByte[longFileNamesChecked];
            case "SHORT":
                return fncConvShort[longFileNamesChecked];
            case "INTEGER":
                return fncConvInteger[longFileNamesChecked];
            case "FLOAT":
                return fncConvFloat[longFileNamesChecked];
            case "Halftone":
                return fncConvHalftone[longFileNamesChecked];
            case "GLQ":
                return fncConvGLQ[longFileNamesChecked];
            case "GrayCode":
                return fncConvGraycode[longFileNamesChecked];
            case "Pseudo":
                return fncConvPseudo[longFileNamesChecked];
            case "Lum":
                return fncConvLum[longFileNamesChecked];
            case "LumAvg":
                return fncConvLumavg[longFileNamesChecked];
            case "XYZ":
                return fncConvXYZ[longFileNamesChecked];
            case "InvXYZ":
                return fncConvInvXYZ[longFileNamesChecked];
            case "LAB":
                return fncConvLAB[longFileNamesChecked];
            case "InvLAB":
                return fncConvInvLAB[longFileNamesChecked];
            case "LUV":
                return fncConvLUV[longFileNamesChecked];
            case "InvLUV":
                return fncConvInvLUV[longFileNamesChecked];
            case "CCT":
                return fncConvCCT[longFileNamesChecked];
            case "InvCCT":
                return fncConvInvCCT[longFileNamesChecked];
            case "HSL":
                return fncConvHSL[longFileNamesChecked];
            case "InvHSL":
                return fncConvInvHSL[longFileNamesChecked];
            case "HSV":
                return fncConvHSV[longFileNamesChecked];
            case "InvHSV":
                return fncConvInvHSV[longFileNamesChecked];
            case "PCT":
                return fncConvPCT[longFileNamesChecked];
            case "InvPCT":
                return fncConvInvPCT[longFileNamesChecked];
            case "SCT":
                return fncConvSCT[longFileNamesChecked];
            case "InvSCT":
                return fncConvInvSCT[longFileNamesChecked];
            case "Label":
                return fncConvLabel[longFileNamesChecked];
            case "Checkerboard":
                return fncCrtCheckboard[longFileNamesChecked];
            case "Circle":
                return fncCrtCircle[longFileNamesChecked];
            case "Ellipse":
                return fncCrtEllipse[longFileNamesChecked];
            case "Line":
                return fncCrtLine[longFileNamesChecked];
            case "Rectangle":
                return fncCrtRectangle[longFileNamesChecked];
            case "Cosine_Wave":
                return fncCrtCosinewave[longFileNamesChecked];
            case "Sine_Wave":
                return fncCrtSinewave[longFileNamesChecked];
            case "Square_Wave":
                return fncCrtSquarewave[longFileNamesChecked];
            case "Black_Image":
                return fncCrtBlackimage[longFileNamesChecked];
            case "bandR":
                return fncCrtExtractbandRed[longFileNamesChecked];
            case "bandG":
                return fncCrtExtractbandGreen[longFileNamesChecked];
            case "bandB":
                return fncCrtExtractbandBlue[longFileNamesChecked];
            case "Assemble_Bands":
                return fncCrtAssembleBands[longFileNamesChecked];
            case "Border_Mask":
                return fncCrtBordermask[longFileNamesChecked];
            case "Border_Image":
                return fncCrtBorderimage[longFileNamesChecked];
            case "Gamma_Noise":
                return fncCrtAddnoiseGamma[longFileNamesChecked];
            case "Gaussian_Noise":
                return fncCrtAddnoiseGaussian[longFileNamesChecked];
            case "Neg_Exp_Noise":
                return fncCrtAddnoiseNegExponential[longFileNamesChecked];
            case "Rayleigh_Noise":
                return fncCrtAddnoiseRayleigh[longFileNamesChecked];
            case "Salt_Pepper_Noise":
                return fncCrtAddnoiseSaltPepper[longFileNamesChecked];
            case "Uniform_Noise":
                return fncCrtAddnoiseUniform[longFileNamesChecked];
            case "Hfe":
                return fncEnhHighFreqEmphasis[longFileNamesChecked];
            //case "Unsharp":
            //    return fncEnhUnsharp[longFileNamesChecked];
            case "FFTSharp":
                return fncEnhFFTSharp[longFileNamesChecked];
            case "DCTSharp":
                return fncEnhDCTSharp[longFileNamesChecked];
            case "Heq":
                return fncEnhHistEq[longFileNamesChecked];
            //case "HistStretch":
            //    return fncEnhHistStretch[longFileNamesChecked];
            //case "Pseudo":
            //    return fncEnhPseudocolor[longFileNamesChecked];
            case "Sharpening":
                return fncEnhSharpening[longFileNamesChecked];
                
            case "SzeCrop":
                return fncSzeCrop[longFileNamesChecked];

            case "SzeFstDublSze":
                return fncSzeFstDublSze[longFileNamesChecked];

            case "SzeReSze":
                return fncSzeReSze[longFileNamesChecked];

            case "SzeSptialQuant":
                return fncSzeSptialQuant[longFileNamesChecked];


            default:
                return "error";
            }
        }
    }
}
