/***************************************************************************
* =========================================================================
*
*			 CVIP_ATAT - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: Processes.cs 
*           Description: Used to get algorithms.
*   Initial Coding Date: June 6, 2006
*Last Modification Made: Feb 25, 2019
*  Programming Language: Visual Studio C#.NET 2008, 2019 
*             Credit(s): Wenjun(Evan) Bian, Pelin Guvenc, Charles Stacey
*                        Southern Illinois University at Edwardsville
*
*		  Copyright (c): 2010-2021 SIUE - Scott Umbaugh
****************************************************************************/

//How to add a new algorithm: (Pelin Guvenc)
//   1. Add code into process_cbBoxSeclectProcess_SelectedIndexChanged() (you define the parameters of the functions)
//   2. Add code into listview public void process_btAddProcess_Click() (the parameter ranges are adjusted)
//   3. Add code into private void TestRun() (here you add the function call)

using System;
using System.Drawing;
using System.Windows.Forms;

namespace CVIP_ATAT.Files
{
    class Processes
    {
        CVIPATATForm CProcessRef;

        //p1L is parameter 1's lower bound;
        //p1I is parameter 1's increment;
        //p1U is parameter 1's upper bound...
        double p1L = 0, p1I = 0, p1U = 0, p2L = 0, p2I = 0, p2U = 0, p3L = 0, p3I = 0, p3U = 0;
        double[] p1Options, p2Options, p3Options;
        int processOptions1 = 0, processOptions2 = 0, processOptions3 = 0;

        //Maximum Stage = 20;
        public static int[] optionInOneStageCount = new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


        public Processes(CVIPATATForm reference, MDIMainForm reference1)
        {
            CProcessRef = reference;
        }

        public void process_cbBoxSeclectProcess_SelectedIndexChanged()
        {
            switch (CProcessRef.cbBoxSeclectProcess.Text)
            {
                case "ACE II":
                    CProcessRef.labelParameter11.Text = "Mask Size:";
                    CProcessRef.labelParameter13.Text = "Range(Odd #: 3-21)";
                    CProcessRef.tbParameter11.Text = "9";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "13";  //upper bound
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    //Parameter2
                    CProcessRef.labelParameter21.Text = "Local Mean:";
                    CProcessRef.labelParameter23.Text = "Range(0-1)";
                    CProcessRef.tbParameter21.Text = "0.3";
                    CProcessRef.tbParameter22.Text = "0.1";
                    CProcessRef.tbParameter23.Text = "0.5";
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    //Parameter3
                    CProcessRef.labelParameter31.Text = "Local Gain:";
                    CProcessRef.labelParameter33.Text = "Range(0-1)";
                    CProcessRef.tbParameter31.Text = "0.5";
                    CProcessRef.tbParameter32.Text = "0.2";
                    CProcessRef.tbParameter33.Text = "0.9";
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    break;

                case "Adaptive Median Filtering":
                    CProcessRef.labelParameter11.Text = "Mask Size:";
                    CProcessRef.labelParameter13.Text = "Range(3~11)";
                    CProcessRef.tbParameter11.Text = "3";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "5";  //upper bound
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    //Parameter2
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    //Parameter3
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    break;

                case "Anisotropic Diffusion Filter":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Number of Iterations:";
                    CProcessRef.labelParameter13.Text = "(Range: 1~...)";
                    CProcessRef.tbParameter11.Text = "1";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "15";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Speed:";
                    CProcessRef.labelParameter23.Text = "(Range: 1~5)";
                    CProcessRef.tbParameter21.Text = "1";
                    CProcessRef.tbParameter22.Text = "1";
                    CProcessRef.tbParameter23.Text = "5";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Edge-Height:";
                    CProcessRef.labelParameter33.Text = "(Range: 1~10)";
                    CProcessRef.tbParameter31.Text = "1";
                    CProcessRef.tbParameter32.Text = "1";
                    CProcessRef.tbParameter33.Text = "10";
                    break;

                case "Alpha Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Mask Size:";
                    CProcessRef.labelParameter13.Text = "Range(3~11)";
                    CProcessRef.tbParameter11.Text = "3";
                    CProcessRef.tbParameter12.Text = "2";
                    CProcessRef.tbParameter13.Text = "5";

                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Trim Size:";
                    CProcessRef.labelParameter23.Text = "Range(0~(N*N-1)/2)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "1";
                    CProcessRef.tbParameter23.Text = "4";

                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Boie-Cox Edge Detection":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Low Threshold Value Scale Factor:";
                    CProcessRef.labelParameter13.Text = "Range(0.0~10.0)";
                    CProcessRef.tbParameter11.Text = "0.1";
                    CProcessRef.tbParameter12.Text = "0.2";
                    CProcessRef.tbParameter13.Text = "1.0";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "High Threshold Value Scale Factor:";
                    CProcessRef.labelParameter23.Text = "Range(0.0~10.0)";
                    CProcessRef.tbParameter21.Text = "0.5";
                    CProcessRef.tbParameter22.Text = "2.0";
                    CProcessRef.tbParameter23.Text = "8.0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Variance:";
                    CProcessRef.labelParameter33.Text = "Range(0.5~5.0)";
                    CProcessRef.tbParameter31.Text = "1.0";
                    CProcessRef.tbParameter32.Text = "1.0";
                    CProcessRef.tbParameter33.Text = "5.0";
                    break;

                case "Boie-Cox-Hysterisis":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Low Threshold Value Scale Factor:";
                    CProcessRef.labelParameter13.Text = "Range(0.0~10.0)";
                    CProcessRef.tbParameter11.Text = "0.1";
                    CProcessRef.tbParameter12.Text = "0.2";
                    CProcessRef.tbParameter13.Text = "1.0";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "High Threshold Value Scale Factor:";
                    CProcessRef.labelParameter23.Text = "Range(0.0~10.0)";
                    CProcessRef.tbParameter21.Text = "0.5";
                    CProcessRef.tbParameter22.Text = "2.0";
                    CProcessRef.tbParameter23.Text = "8.0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Variance:";
                    CProcessRef.labelParameter33.Text = "Range(0.5~5.0)";
                    CProcessRef.tbParameter31.Text = "1.0";
                    CProcessRef.tbParameter32.Text = "1.0";
                    CProcessRef.tbParameter33.Text = "5.0";
                    break;

                case "Binary Thresholding":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Threshold Value:";
                    CProcessRef.labelParameter13.Text = "Range(0~255)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "255";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Canny Edge Detection":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Low Threshold Value Scale Factor:";
                    CProcessRef.labelParameter13.Text = "Range(0.0~10.0)";
                    CProcessRef.tbParameter11.Text = "0.0";
                    CProcessRef.tbParameter12.Text = "2.0";
                    CProcessRef.tbParameter13.Text = "4.0";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "High Threshold Value Scale Factor:";
                    CProcessRef.labelParameter23.Text = "Range(low~10.0)";
                    CProcessRef.tbParameter21.Text = "2.0";
                    CProcessRef.tbParameter22.Text = "2.0";
                    CProcessRef.tbParameter23.Text = "8.0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Variance:";
                    CProcessRef.labelParameter33.Text = "Range(0.5~5.0)";
                    CProcessRef.tbParameter31.Text = "0.5";
                    CProcessRef.tbParameter32.Text = "2.0";
                    CProcessRef.tbParameter33.Text = "5.0";
                    break;

                case "Color-to-Gray Conversion - Average":
                    CProcessRef.tbParameter11.Enabled = false;
                    CProcessRef.tbParameter12.Enabled = false;
                    CProcessRef.tbParameter13.Enabled = false;
                    CProcessRef.labelParameter11.Text = "Parameter 1:";
                    CProcessRef.labelParameter13.Text = "(Parameter Range)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "0";
                    CProcessRef.tbParameter13.Text = "0";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Color-to-Gray Conversion - Luminance":
                    CProcessRef.tbParameter11.Enabled = false;
                    CProcessRef.tbParameter12.Enabled = false;
                    CProcessRef.tbParameter13.Enabled = false;
                    CProcessRef.labelParameter11.Text = "Parameter 1:";
                    CProcessRef.labelParameter13.Text = "(Parameter Range)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "0";
                    CProcessRef.tbParameter13.Text = "0";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Color Transformation (RGB->HSL,HSV,SCT,CCT,LUV,LAB,XYZ)":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Color Space:";
                    CProcessRef.labelParameter13.Text = "(3=HSL,4=HSV,5=SCT,6=CCT,7=LUV,8=LAB,9=XYZ)";
                    CProcessRef.tbParameter11.Text = "3";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "9";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Contra-Harmonic Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Mask Size:";
                    CProcessRef.labelParameter13.Text = "Range(3~11)";
                    CProcessRef.tbParameter11.Text = "3";
                    CProcessRef.tbParameter12.Text = "2";
                    CProcessRef.tbParameter13.Text = "5";

                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Filter Order:";
                    CProcessRef.labelParameter23.Text = "Range(? -5~+5)";
                    CProcessRef.tbParameter21.Text = "-1";
                    CProcessRef.tbParameter22.Text = "1";
                    CProcessRef.tbParameter23.Text = "1";

                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Contrast-Limited Adaptive Hist Eq":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Block Size:";
                    CProcessRef.labelParameter13.Text = "Range(3~11)";
                    CProcessRef.tbParameter11.Text = "3";
                    CProcessRef.tbParameter12.Text = "2";
                    CProcessRef.tbParameter13.Text = "5";

                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Clip Percent:";
                    CProcessRef.labelParameter23.Text = "Range(0-1)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0.25";
                    CProcessRef.tbParameter23.Text = "0.5";

                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Band(Color Only):";
                    CProcessRef.labelParameter33.Text = "Range(0-2)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "1";
                    CProcessRef.tbParameter33.Text = "2";
                    break;

                case "Direct Cosine Transform":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Block Size:";
                    CProcessRef.labelParameter13.Text = "Range(2~2048)Please enter a fixed value.";
                    CProcessRef.tbParameter11.Text = "128";
                    CProcessRef.tbParameter12.Text = "128";
                    CProcessRef.tbParameter13.Text = "128";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Extract Band":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Band No:";
                    CProcessRef.labelParameter13.Text = "(Range:1~3) ";
                    CProcessRef.tbParameter11.Text = "1";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "3";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Edge-Linking":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Max. Connect Distance:";
                    CProcessRef.labelParameter13.Text = "Range(1~10)";
                    CProcessRef.tbParameter11.Text = "1";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "10";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Fast Fourier Transform":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Block Size:";
                    CProcessRef.labelParameter13.Text = "Range(2~2048)Please enter a fixed value.";
                    CProcessRef.tbParameter11.Text = "128";
                    CProcessRef.tbParameter12.Text = "128";
                    CProcessRef.tbParameter13.Text = "128";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Fuzzyc Segmentation":
                    CProcessRef.labelParameter11.Text = "Gaussian Kernal Variance:";
                    CProcessRef.labelParameter13.Text = "Range(0~20.0)";
                    CProcessRef.tbParameter11.Text = "0";  //lower bound
                    CProcessRef.tbParameter12.Text = "1";  //increment
                    CProcessRef.tbParameter13.Text = "1";  //upper bound
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    //Parameter2
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    //Parameter3
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    break;

                case "Gaussian Filter":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Mask size:";
                    CProcessRef.labelParameter13.Text = "(Range: 3~7)";
                    CProcessRef.tbParameter11.Text = "3";
                    CProcessRef.tbParameter12.Text = "2";
                    CProcessRef.tbParameter13.Text = "7";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Geometric Filtering":
                    CProcessRef.labelParameter11.Text = "Mask Size:";
                    CProcessRef.labelParameter13.Text = "Range(3~11)";
                    CProcessRef.tbParameter11.Text = "3";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "5";  //upper bound
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    //Parameter2
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    //Parameter3
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    break;

                case "Gray Level Quantization":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Number of Desired Gray Levels:";
                    CProcessRef.labelParameter13.Text = "Range(2~128)Please enter a fixed value.";
                    CProcessRef.tbParameter11.Text = "64";
                    CProcessRef.tbParameter12.Text = "64";
                    CProcessRef.tbParameter13.Text = "64";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Haar Transform":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Type of Transform:";
                    CProcessRef.labelParameter13.Text = "(1=Forward, 0=Inverse)";
                    CProcessRef.tbParameter11.Text = "1";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "1";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Block Size:";
                    CProcessRef.labelParameter23.Text = "Range(2~2048)Please enter a fixed value.";
                    CProcessRef.tbParameter21.Text = "64";
                    CProcessRef.tbParameter22.Text = "64";
                    CProcessRef.tbParameter23.Text = "64";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Harmonic Filtering":
                    CProcessRef.labelParameter11.Text = "Mask Size:";
                    CProcessRef.labelParameter13.Text = "Range(3~11)";
                    CProcessRef.tbParameter11.Text = "3";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "5";  //upper bound
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    //Parameter2
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    //Parameter3
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    break;

                case "High Boost":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Mask Size:";
                    CProcessRef.labelParameter13.Text = "(Range: 3~9)";
                    CProcessRef.tbParameter11.Text = "3";
                    CProcessRef.tbParameter12.Text = "2";
                    CProcessRef.tbParameter13.Text = "7";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Center Value:";
                    CProcessRef.labelParameter23.Text = "(Range: 0~100)";
                    CProcessRef.tbParameter21.Text = "5";
                    CProcessRef.tbParameter22.Text = "2";
                    CProcessRef.tbParameter23.Text = "49";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Add to Original:";
                    CProcessRef.labelParameter33.Text = "(Range: 0, 1)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "1";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "High Freq. Emphasis (DC=>On)":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Cutoff Freq.:";
                    CProcessRef.labelParameter13.Text = "(Range:64~512)Please enter a fixed value.";
                    CProcessRef.tbParameter11.Text = "64";
                    CProcessRef.tbParameter12.Text = "64";
                    CProcessRef.tbParameter13.Text = "64";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Alpha:";
                    CProcessRef.labelParameter23.Text = "(Range:1.2~2.5)";
                    CProcessRef.tbParameter21.Text = "1.2";
                    CProcessRef.tbParameter22.Text = "0.3";
                    CProcessRef.tbParameter23.Text = "2.5";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Filter Order:";
                    CProcessRef.labelParameter33.Text = "(Range:1~8)";
                    CProcessRef.tbParameter31.Text = "1";
                    CProcessRef.tbParameter32.Text = "2";
                    CProcessRef.tbParameter33.Text = "8";
                    break;

                case "High Freq. Emphasis (DC=>Off)":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Cutoff Freq.:";
                    CProcessRef.labelParameter13.Text = "(Range:64~512)Please enter a fixed value.";
                    CProcessRef.tbParameter11.Text = "64";
                    CProcessRef.tbParameter12.Text = "64";
                    CProcessRef.tbParameter13.Text = "64";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Alpha:";
                    CProcessRef.labelParameter23.Text = "(Range:1.2~2.5)";
                    CProcessRef.tbParameter21.Text = "1.2";
                    CProcessRef.tbParameter22.Text = "0.3";
                    CProcessRef.tbParameter23.Text = "2.5";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Filter Order:";
                    CProcessRef.labelParameter33.Text = "(Range:1~8)";
                    CProcessRef.tbParameter31.Text = "1";
                    CProcessRef.tbParameter32.Text = "2";
                    CProcessRef.tbParameter33.Text = "8";
                    break;

                case "Highpass Spatial Filter":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Add to Original Image:";
                    CProcessRef.labelParameter13.Text = "(Range: 0,1)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "1";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Histogram Equalization":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Band to Operate On?";
                    CProcessRef.labelParameter13.Text = "(0=Red/Gray, 1=Green, 2=Blue)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "2";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Histogram Slide":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Threshold Value:";
                    CProcessRef.labelParameter13.Text = "Range(-255~255)";
                    CProcessRef.tbParameter11.Text = "-50";
                    CProcessRef.tbParameter12.Text = "50";
                    CProcessRef.tbParameter13.Text = "50";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Histogram Stretch":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Low Limit:";
                    CProcessRef.labelParameter13.Text = "Range(0~255)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "50";
                    CProcessRef.tbParameter13.Text = "100";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "High Limit:";
                    CProcessRef.labelParameter23.Text = "Range(0-255)";
                    CProcessRef.tbParameter21.Text = "100";
                    CProcessRef.tbParameter22.Text = "50";
                    CProcessRef.tbParameter23.Text = "200";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Clip Percenatage:";
                    CProcessRef.labelParameter33.Text = "Range(0-1)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0.25";
                    CProcessRef.tbParameter33.Text = "0.5";
                    break;

                case "Histogram Thresholding Segmentation":
                    CProcessRef.labelParameter11.Text = "Gaussian Kernel Variance:";
                    CProcessRef.labelParameter13.Text = "Range(0.2-8.2)";
                    CProcessRef.tbParameter11.Text = "0.25";  //lower bound
                    CProcessRef.tbParameter12.Text = "0.25";  //increment
                    CProcessRef.tbParameter13.Text = "0.5";  //upper bound
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    //Parameter2
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    //Parameter3
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    break;

                case "Hough Transform":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Angle of Interest:";
                    CProcessRef.labelParameter13.Text = "(0~180)";
                    CProcessRef.tbParameter11.Text = "45";
                    CProcessRef.tbParameter12.Text = "1.0";
                    CProcessRef.tbParameter13.Text = "45";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Line Pixels:";
                    CProcessRef.labelParameter23.Text = "(10~100)";
                    CProcessRef.tbParameter21.Text = "10";
                    CProcessRef.tbParameter22.Text = "10";
                    CProcessRef.tbParameter23.Text = "100";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Connect Distance:";
                    CProcessRef.labelParameter33.Text = "(1~10)";
                    CProcessRef.tbParameter31.Text = "1";
                    CProcessRef.tbParameter32.Text = "1";
                    CProcessRef.tbParameter33.Text = "10";
                    break;

                case "HSL -> RGB Transform":
                    CProcessRef.tbParameter11.Enabled = false;
                    CProcessRef.tbParameter12.Enabled = false;
                    CProcessRef.tbParameter13.Enabled = false;
                    CProcessRef.labelParameter11.Text = "Parameter 1:";
                    CProcessRef.labelParameter13.Text = "(Parameter Range)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "0";
                    CProcessRef.tbParameter13.Text = "0";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "HSV -> RGB Transform":
                    CProcessRef.tbParameter11.Enabled = false;
                    CProcessRef.tbParameter12.Enabled = false;
                    CProcessRef.tbParameter13.Enabled = false;
                    CProcessRef.labelParameter11.Text = "Parameter 1:";
                    CProcessRef.labelParameter13.Text = "(Parameter Range)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "0";
                    CProcessRef.tbParameter13.Text = "0";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Inverse Direct Cosine Transform":
                    CProcessRef.tbParameter11.Enabled = false;
                    CProcessRef.tbParameter12.Enabled = false;
                    CProcessRef.tbParameter13.Enabled = false;
                    CProcessRef.labelParameter11.Text = "Parameter 1:";
                    CProcessRef.labelParameter13.Text = "(Parameter Range)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "0";
                    CProcessRef.tbParameter13.Text = "0";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Inverse Fast Fourier Transform":
                    CProcessRef.tbParameter11.Enabled = false;
                    CProcessRef.tbParameter12.Enabled = false;
                    CProcessRef.tbParameter13.Enabled = false;
                    CProcessRef.labelParameter11.Text = "Parameter 1:";
                    CProcessRef.labelParameter13.Text = "(Parameter Range)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "0";
                    CProcessRef.tbParameter13.Text = "0";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Kuwahara Filter":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Mask Size:";
                    CProcessRef.labelParameter13.Text = "(Range: 3~11)";
                    CProcessRef.tbParameter11.Text = "3";
                    CProcessRef.tbParameter12.Text = "2";
                    CProcessRef.tbParameter13.Text = "11";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Laplacian Edge Detection":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Mask Choice:";
                    CProcessRef.labelParameter13.Text = "Note:Edge_Detect_Filter.c function used here, CVIPtools uses separate functions.";
                    FontFamily family3 = new FontFamily("Times New Roman");

                    Font font3 = new Font(family3, 9.0f,
                    FontStyle.Italic);
                    CProcessRef.labelParameter13.Font = font3;
                    CProcessRef.tbParameter11.Text = "1";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "4";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Mask Size:";
                    CProcessRef.labelParameter23.Text = "(1~3)";
                    CProcessRef.tbParameter21.Text = "1";
                    CProcessRef.tbParameter22.Text = "1";
                    CProcessRef.tbParameter23.Text = "2";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Keep DC?";
                    CProcessRef.labelParameter33.Text = "(0 = No, 1 = Yes)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "1";
                    CProcessRef.tbParameter33.Text = "1";
                    break;

                case "Label Image":
                    CProcessRef.tbParameter11.Enabled = false;
                    CProcessRef.tbParameter12.Enabled = false;
                    CProcessRef.tbParameter13.Enabled = false;
                    CProcessRef.labelParameter11.Text = "Parameter 1:";
                    CProcessRef.labelParameter13.Text = "(Parameter Range)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "0";
                    CProcessRef.tbParameter13.Text = "0";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Maximum Filtering":
                    CProcessRef.labelParameter11.Text = "Mask Size:";
                    CProcessRef.labelParameter13.Text = "Range(3~11)";
                    CProcessRef.tbParameter11.Text = "3";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "5";  //upper bound
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    //Parameter2
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    //Parameter3
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    break;
                case "Mean Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Mask Size:";
                    CProcessRef.labelParameter13.Text = "Range(3~11)";
                    CProcessRef.tbParameter11.Text = "3";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "5";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;
                case "Median Cut Segmentation":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "# of Desired Colors:";
                    CProcessRef.labelParameter13.Text = "Range(2~1000)";
                    CProcessRef.tbParameter11.Text = "2";  //lower bound
                    CProcessRef.tbParameter12.Text = "1";  //increment
                    CProcessRef.tbParameter13.Text = "3";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;
                case "Median Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Mask Size:";
                    CProcessRef.labelParameter13.Text = "Range(3~31)";
                    CProcessRef.tbParameter11.Text = "3";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "5";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;
                case "Midpoint Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Mask Size:";
                    CProcessRef.labelParameter13.Text = "Range(3~11)";
                    CProcessRef.tbParameter11.Text = "3";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "5";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;
                case "MMSE Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Kernel Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~15)";
                    CProcessRef.tbParameter11.Text = "3";
                    CProcessRef.tbParameter12.Text = "2";
                    CProcessRef.tbParameter13.Text = "5";
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Noise Variance:";
                    CProcessRef.labelParameter23.Text = "Range(? 100~800)";
                    CProcessRef.tbParameter21.Text = "50";
                    CProcessRef.tbParameter22.Text = "50";
                    CProcessRef.tbParameter23.Text = "100";
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;
                case "Morphological Closing-Circle Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~13)";
                    CProcessRef.tbParameter11.Text = "3";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "5";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;
                case "Morphological Closing-Cross Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~13)";
                    CProcessRef.tbParameter11.Text = "5";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "9";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Thickness:";
                    CProcessRef.labelParameter23.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter21.Text = "1";
                    CProcessRef.tbParameter22.Text = "2";
                    CProcessRef.tbParameter23.Text = "3";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Cross Size:";
                    CProcessRef.labelParameter33.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter31.Text = "3";
                    CProcessRef.tbParameter32.Text = "2";
                    CProcessRef.tbParameter33.Text = "5";
                    break;
                case "Morphological Closing-Rectangle Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~13)";
                    CProcessRef.tbParameter11.Text = "5";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "9";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Width:";
                    CProcessRef.labelParameter23.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter21.Text = "1";
                    CProcessRef.tbParameter22.Text = "2";
                    CProcessRef.tbParameter23.Text = "3";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Height:";
                    CProcessRef.labelParameter33.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter31.Text = "3";
                    CProcessRef.tbParameter32.Text = "2";
                    CProcessRef.tbParameter33.Text = "5";
                    break;
                case "Morphological Closing-Square Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~13)";
                    CProcessRef.tbParameter11.Text = "5";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "9";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Side:";
                    CProcessRef.labelParameter23.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter21.Text = "3";
                    CProcessRef.tbParameter22.Text = "2";
                    CProcessRef.tbParameter23.Text = "5";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;
                case "Morphological Dilation-Circle Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~13)";
                    CProcessRef.tbParameter11.Text = "3";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "5";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;
                case "Morphological Dilation-Cross Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~13)";
                    CProcessRef.tbParameter11.Text = "5";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "9";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Thickness:";
                    CProcessRef.labelParameter23.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter21.Text = "1";
                    CProcessRef.tbParameter22.Text = "2";
                    CProcessRef.tbParameter23.Text = "3";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Cross Size:";
                    CProcessRef.labelParameter33.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter31.Text = "3";
                    CProcessRef.tbParameter32.Text = "2";
                    CProcessRef.tbParameter33.Text = "5";
                    break;
                case "Morphological Dilation-Rectangle Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~13)";
                    CProcessRef.tbParameter11.Text = "5";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "9";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Width:";
                    CProcessRef.labelParameter23.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter21.Text = "1";
                    CProcessRef.tbParameter22.Text = "2";
                    CProcessRef.tbParameter23.Text = "3";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Height:";
                    CProcessRef.labelParameter33.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter31.Text = "3";
                    CProcessRef.tbParameter32.Text = "2";
                    CProcessRef.tbParameter33.Text = "5";
                    break;
                case "Morphological Dilation-Square Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~13)";
                    CProcessRef.tbParameter11.Text = "3";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "9";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Side:";
                    CProcessRef.labelParameter23.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter21.Text = "3";
                    CProcessRef.tbParameter22.Text = "2";
                    CProcessRef.tbParameter23.Text = "5";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;
                case "Morphological Erosion-Circle Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~13)";
                    CProcessRef.tbParameter11.Text = "3";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "5";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;
                case "Morphological Erosion-Cross Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~13)";
                    CProcessRef.tbParameter11.Text = "5";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "9";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Thickness:";
                    CProcessRef.labelParameter23.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter21.Text = "1";
                    CProcessRef.tbParameter22.Text = "2";
                    CProcessRef.tbParameter23.Text = "3";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Cross Size:";
                    CProcessRef.labelParameter33.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter31.Text = "3";
                    CProcessRef.tbParameter32.Text = "2";
                    CProcessRef.tbParameter33.Text = "5";
                    break;
                case "Morphological Erosion-Rectangle Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~13)";
                    CProcessRef.tbParameter11.Text = "5";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "9";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Width:";
                    CProcessRef.labelParameter23.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter21.Text = "1";
                    CProcessRef.tbParameter22.Text = "2";
                    CProcessRef.tbParameter23.Text = "3";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Height:";
                    CProcessRef.labelParameter33.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter31.Text = "3";
                    CProcessRef.tbParameter32.Text = "2";
                    CProcessRef.tbParameter33.Text = "5";
                    break;
                case "Morphological Erosion-Square Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~13)";
                    CProcessRef.tbParameter11.Text = "5";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "9";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Side:";
                    CProcessRef.labelParameter23.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter21.Text = "3";
                    CProcessRef.tbParameter22.Text = "2";
                    CProcessRef.tbParameter23.Text = "5";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;
                case "Morphological Opening-Circle Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~13)";
                    CProcessRef.tbParameter11.Text = "3";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "5";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;
                case "Morphological Opening-Cross Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~13)";
                    CProcessRef.tbParameter11.Text = "5";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "9";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Thickness:";
                    CProcessRef.labelParameter23.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter21.Text = "1";
                    CProcessRef.tbParameter22.Text = "2";
                    CProcessRef.tbParameter23.Text = "3";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Cross Size:";
                    CProcessRef.labelParameter33.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter31.Text = "3";
                    CProcessRef.tbParameter32.Text = "2";
                    CProcessRef.tbParameter33.Text = "5";
                    break;
                case "Morphological Opening-Rectangle Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~13)";
                    CProcessRef.tbParameter11.Text = "5";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "9";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Width:";
                    CProcessRef.labelParameter23.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter21.Text = "1";
                    CProcessRef.tbParameter22.Text = "2";
                    CProcessRef.tbParameter23.Text = "3";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Height:";
                    CProcessRef.labelParameter33.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter31.Text = "3";
                    CProcessRef.tbParameter32.Text = "2";
                    CProcessRef.tbParameter33.Text = "5";
                    break;
                case "Morphological Opening-Square Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Size:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~13)";
                    CProcessRef.tbParameter11.Text = "5";  //lower bound
                    CProcessRef.tbParameter12.Text = "2";  //increment
                    CProcessRef.tbParameter13.Text = "9";  //upper bound
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Side:";
                    CProcessRef.labelParameter23.Text = "Range(? 1~11)";
                    CProcessRef.tbParameter21.Text = "3";
                    CProcessRef.tbParameter22.Text = "2";
                    CProcessRef.tbParameter23.Text = "5";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "MorphSkel 4-mask,And":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Filter Size:";
                    CProcessRef.labelParameter13.Text = "(Range: 3~9)";
                    CProcessRef.tbParameter11.Text = "3";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "3";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Number of Iterations:";
                    CProcessRef.labelParameter23.Text = "(Range: 2~20)";
                    CProcessRef.tbParameter21.Text = "5";
                    CProcessRef.tbParameter22.Text = "5";
                    CProcessRef.tbParameter23.Text = "20";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "MorphSkel 4-mask,Sequential":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Filter Size:";
                    CProcessRef.labelParameter13.Text = "(Range: 3~9)";
                    CProcessRef.tbParameter11.Text = "3";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "3";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Number of Iterations:";
                    CProcessRef.labelParameter23.Text = "(Range: 2~20)";
                    CProcessRef.tbParameter21.Text = "5";
                    CProcessRef.tbParameter22.Text = "5";
                    CProcessRef.tbParameter23.Text = "20";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "MorphSkel 8-mask,And":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Filter Size:";
                    CProcessRef.labelParameter13.Text = "(Range: 3~9)";
                    CProcessRef.tbParameter11.Text = "3";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "3";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Number of Iterations:";
                    CProcessRef.labelParameter23.Text = "(Range: 2~20)";
                    CProcessRef.tbParameter21.Text = "5";
                    CProcessRef.tbParameter22.Text = "5";
                    CProcessRef.tbParameter23.Text = "20";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "MorphSkel 8-mask,Sequential":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Filter Size:";
                    CProcessRef.labelParameter13.Text = "(Range: 3~9)";
                    CProcessRef.tbParameter11.Text = "3";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "3";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Number of Iterations:";
                    CProcessRef.labelParameter23.Text = "(Range: 2~20)";
                    CProcessRef.tbParameter21.Text = "5";
                    CProcessRef.tbParameter22.Text = "5";
                    CProcessRef.tbParameter23.Text = "20";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Not":
                    CProcessRef.labelParameter11.Text = "Parameter 1:";
                    CProcessRef.labelParameter13.Text = "(Parameter Range)";
                    CProcessRef.tbParameter11.Text = "0";  //lower bound
                    CProcessRef.tbParameter12.Text = "0";  //increment
                    CProcessRef.tbParameter13.Text = "0";  //upper bound
                    CProcessRef.tbParameter11.Enabled = false;
                    CProcessRef.tbParameter12.Enabled = false;
                    CProcessRef.tbParameter13.Enabled = false;
                    //Parameter2
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    //Parameter3
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    break;

                case "Otsu Thresholding":
                    CProcessRef.tbParameter11.Enabled = false;
                    CProcessRef.tbParameter12.Enabled = false;
                    CProcessRef.tbParameter13.Enabled = false;
                    CProcessRef.labelParameter11.Text = "Parameter 1:";
                    CProcessRef.labelParameter13.Text = "(Parameter Range)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "0";
                    CProcessRef.tbParameter13.Text = "0";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Parametric AD Filter":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Number of Iterations:";
                    CProcessRef.labelParameter13.Text = "(Range: 1~...)";
                    CProcessRef.tbParameter11.Text = "1";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "15";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Edge-Height:";
                    CProcessRef.labelParameter23.Text = "(Range: 1~10)";
                    CProcessRef.tbParameter21.Text = "1";
                    CProcessRef.tbParameter22.Text = "1";
                    CProcessRef.tbParameter23.Text = "5";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Block Size:";
                    CProcessRef.labelParameter33.Text = "(Range: 2~2024)Please enter a fixed value.";
                    CProcessRef.tbParameter31.Text = "64";
                    CProcessRef.tbParameter32.Text = "64";
                    CProcessRef.tbParameter33.Text = "64";
                    break;

                case "PCT Transform":
                    CProcessRef.labelParameter11.Text = "Parameter 1:";
                    CProcessRef.labelParameter13.Text = "(Parameter Range)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "0";
                    CProcessRef.tbParameter13.Text = "0";
                    CProcessRef.tbParameter11.Enabled = false;
                    CProcessRef.tbParameter12.Enabled = false;
                    CProcessRef.tbParameter13.Enabled = false;
                    //Parameter2
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    //Parameter3
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    break;

                case "PCT Median Segmentation":
                    CProcessRef.labelParameter11.Text = "# of Desired Colors:";
                    CProcessRef.labelParameter13.Text = "Range(2~1000)";
                    CProcessRef.tbParameter11.Text = "2";  //lower bound
                    CProcessRef.tbParameter12.Text = "1";  //increment
                    CProcessRef.tbParameter13.Text = "3";  //upper bound
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    //Parameter2
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    //Parameter3
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    break;

                case "Prewitt Edge Detection":/*EDGE_PREWITT = 8*/
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "PreFilter:";
                    CProcessRef.labelParameter13.Text = "Note:Edge_Detect_Filter.c function used here, CVIPtools uses separate functions.";
                    FontFamily family2 = new FontFamily("Times New Roman");

                    Font font2 = new Font(family2, 9.0f,
                    FontStyle.Italic);
                    CProcessRef.labelParameter13.Font = font2;
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "4";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Mask Size:";
                    CProcessRef.labelParameter23.Text = "(3~21)";
                    CProcessRef.tbParameter21.Text = "3";
                    CProcessRef.tbParameter22.Text = "2";
                    CProcessRef.tbParameter23.Text = "9";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Keep DC?";
                    CProcessRef.labelParameter33.Text = "(0 = No, 1 = Yes)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "1";
                    CProcessRef.tbParameter33.Text = "1";
                    break;

                case "Roberts Edge Detection":/*EDGE_ROBERTS = 6*/
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "PreFilter:";
                    CProcessRef.labelParameter13.Text = "Note:Edge_Detect_Filter.c function used here, CVIPtools uses separate functions.";
                    FontFamily family1 = new FontFamily("Times New Roman");

                    Font font1 = new Font(family1, 9.0f,
                    FontStyle.Italic);
                    CProcessRef.labelParameter13.Font = font1;
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "4";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Mask Size:";
                    CProcessRef.labelParameter23.Text = "(1~2)";
                    CProcessRef.tbParameter21.Text = "1";
                    CProcessRef.tbParameter22.Text = "1";
                    CProcessRef.tbParameter23.Text = "2";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Keep DC?";
                    CProcessRef.labelParameter33.Text = "(0 = No, 1 = Yes)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "1";
                    CProcessRef.tbParameter33.Text = "1";
                    break;

                case "Auto Single Threshold":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Limit:";
                    CProcessRef.labelParameter13.Text = "(Range:1~...)";
                    CProcessRef.tbParameter11.Text = "1";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "5";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "SCT Center Segmentation":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "# of Colors Along Axis A:";
                    CProcessRef.labelParameter13.Text = "Range(? 3~100)";
                    CProcessRef.tbParameter11.Text = "3";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "4";
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "# of Colors Along Axis B:";
                    CProcessRef.labelParameter23.Text = "Range(? 3~100)";
                    CProcessRef.tbParameter21.Text = "3";
                    CProcessRef.tbParameter22.Text = "1";
                    CProcessRef.tbParameter23.Text = "4";
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Sharpening AlgorithmI ( Mask II )":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Mask Size:";
                    CProcessRef.labelParameter13.Text = "(Range: 3,5,7)";
                    CProcessRef.tbParameter11.Text = "3";
                    CProcessRef.tbParameter12.Text = "2";
                    CProcessRef.tbParameter13.Text = "7";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Low Clip Percentage:";
                    CProcessRef.labelParameter23.Text = "(Range: 0.0~0.5)";
                    CProcessRef.tbParameter21.Text = "0.0";
                    CProcessRef.tbParameter22.Text = "0.05";
                    CProcessRef.tbParameter23.Text = "0.1";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "High Clip Percentage:";
                    CProcessRef.labelParameter33.Text = "(Range: 0.0~0.5)";
                    CProcessRef.tbParameter31.Text = "0.0";
                    CProcessRef.tbParameter32.Text = "0.05";
                    CProcessRef.tbParameter33.Text = "0.1";
                    break;

                case "Sharpening AlgorithmII":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Add to Original Image:";
                    CProcessRef.labelParameter13.Text = "(Range: 0,1)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "1";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Shen-Castan Edge Detection":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Low Threshold Value Scale Factor:";
                    CProcessRef.labelParameter13.Text = "Range(0.0~10.0)";
                    CProcessRef.tbParameter11.Text = "1.0";
                    CProcessRef.tbParameter12.Text = "2.0";
                    CProcessRef.tbParameter13.Text = "4.0";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "High Threshold Value Scale Factor:";
                    CProcessRef.labelParameter23.Text = "Range(0.0~10.0)";
                    CProcessRef.tbParameter21.Text = "2";
                    CProcessRef.tbParameter22.Text = "2";
                    CProcessRef.tbParameter23.Text = "8";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Smoothing Factor:";
                    CProcessRef.labelParameter33.Text = "Range(0.1~0.9)";
                    CProcessRef.tbParameter31.Text = "0.5";
                    CProcessRef.tbParameter32.Text = "0.2";
                    CProcessRef.tbParameter33.Text = "0.9";
                    break;

                case "Skip/Null":
                    CProcessRef.tbParameter11.Enabled = false;
                    CProcessRef.tbParameter12.Enabled = false;
                    CProcessRef.tbParameter13.Enabled = false;
                    CProcessRef.labelParameter11.Text = "Parameter 1:";
                    CProcessRef.labelParameter13.Text = "(Parameter Range)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "0";
                    CProcessRef.tbParameter13.Text = "0";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Sobel Edge Detection":/*EDGE_SOBEL = 7*/
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "PreFilter:";
                    CProcessRef.labelParameter13.Text = "Note:Edge_Detect_Filter.c function used here, CVIPtools uses separate functions.";
                    FontFamily family = new FontFamily("Times New Roman");

                    Font font = new Font(family, 9.0f,
                    FontStyle.Italic);
                    CProcessRef.labelParameter13.Font = font; CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "4";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Mask Size:";
                    CProcessRef.labelParameter23.Text = "(3,5,7)";
                    CProcessRef.tbParameter21.Text = "3";
                    CProcessRef.tbParameter22.Text = "2";
                    CProcessRef.tbParameter23.Text = "7";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Keep DC?";
                    CProcessRef.labelParameter33.Text = "(0 = No, 1 = Yes)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "1";
                    CProcessRef.tbParameter33.Text = "1";
                    break;

                case "Spatial Quantization":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "# of Rows for Reduced Image:";
                    CProcessRef.labelParameter13.Text = "Range(2~Image Size)Please enter a fixed value.";
                    CProcessRef.tbParameter11.Text = "64";
                    CProcessRef.tbParameter12.Text = "64";
                    CProcessRef.tbParameter13.Text = "64";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "# of Columns for Reduced Image:";
                    CProcessRef.labelParameter23.Text = "Range(2~Image Size)Please enter a fixed value.";
                    CProcessRef.tbParameter21.Text = "64";
                    CProcessRef.tbParameter22.Text = "64";
                    CProcessRef.tbParameter23.Text = "64";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Reduction Method:";
                    CProcessRef.labelParameter33.Text = "(1=Average, 2=Median, 3=Decimation)";
                    CProcessRef.tbParameter31.Text = "1";
                    CProcessRef.tbParameter32.Text = "1";
                    CProcessRef.tbParameter33.Text = "3";
                    break;

                case "Threshold(remapped) Segmentation":
                    CProcessRef.labelParameter11.Text = "Threshold Value:";
                    CProcessRef.labelParameter13.Text = "Range(0~255)";
                    CProcessRef.tbParameter11.Text = "0";  //lower bound
                    CProcessRef.tbParameter12.Text = "50";  //increment
                    CProcessRef.tbParameter13.Text = "255";  //upper bound
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    //Parameter2
                    CProcessRef.labelParameter21.Text = "Parameter 2:";
                    CProcessRef.labelParameter23.Text = "(Parameter Range)";
                    CProcessRef.tbParameter21.Text = "0";
                    CProcessRef.tbParameter22.Text = "0";
                    CProcessRef.tbParameter23.Text = "0";
                    CProcessRef.tbParameter21.Enabled = false;
                    CProcessRef.tbParameter22.Enabled = false;
                    CProcessRef.tbParameter23.Enabled = false;
                    //Parameter3
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    break;

                case "Unsharp Masking":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Low Limit:";
                    CProcessRef.labelParameter13.Text = "(Range: 0~255)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "50";
                    CProcessRef.tbParameter13.Text = "200";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Upper Limit:";
                    CProcessRef.labelParameter23.Text = "(Range: 0~255)";
                    CProcessRef.tbParameter21.Text = "100";
                    CProcessRef.tbParameter22.Text = "50";
                    CProcessRef.tbParameter23.Text = "200";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = true;
                    CProcessRef.tbParameter32.Enabled = true;
                    CProcessRef.tbParameter33.Enabled = true;
                    CProcessRef.labelParameter31.Text = "Clip Percentage:";
                    CProcessRef.labelParameter33.Text = "(Range: 0.0~0.5)";
                    CProcessRef.tbParameter31.Text = "0.0";
                    CProcessRef.tbParameter32.Text = "0.05";
                    CProcessRef.tbParameter33.Text = "0.2";
                    break;

                case "Walsh-Hadamard Transform":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Type of Transform:";
                    CProcessRef.labelParameter13.Text = "(0=Inverse Walsh, 1=Walsh, 2=Inverse Hadamard, 3=Hadamard)";
                    CProcessRef.tbParameter11.Text = "1";
                    CProcessRef.tbParameter12.Text = "2";
                    CProcessRef.tbParameter13.Text = "3";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Block Size:";
                    CProcessRef.labelParameter23.Text = "Range(2~2048)Please enter a fixed value.";
                    CProcessRef.tbParameter21.Text = "64";
                    CProcessRef.tbParameter22.Text = "64";
                    CProcessRef.tbParameter23.Text = "64";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Watershed Segmentation":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Merge Result?";
                    CProcessRef.labelParameter13.Text = "(0 = No, 1 = Yes)";
                    CProcessRef.tbParameter11.Text = "0";
                    CProcessRef.tbParameter12.Text = "1";
                    CProcessRef.tbParameter13.Text = "1";
                    //Parameter2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Threshold:";
                    CProcessRef.labelParameter23.Text = "Range(0.1~0.9)";
                    CProcessRef.tbParameter21.Text = "0.1";
                    CProcessRef.tbParameter22.Text = "0.1";
                    CProcessRef.tbParameter23.Text = "0.9";
                    //Parameter3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;

                case "Yp-Mean Filtering":
                    CProcessRef.tbParameter11.Enabled = true;
                    CProcessRef.tbParameter12.Enabled = true;
                    CProcessRef.tbParameter13.Enabled = true;
                    CProcessRef.labelParameter11.Text = "Mask Size:";
                    CProcessRef.labelParameter13.Text = "Range(3~11)";
                    CProcessRef.tbParameter11.Text = "3";
                    CProcessRef.tbParameter12.Text = "2";
                    CProcessRef.tbParameter13.Text = "5";
                    //Parameter 2
                    CProcessRef.tbParameter21.Enabled = true;
                    CProcessRef.tbParameter22.Enabled = true;
                    CProcessRef.tbParameter23.Enabled = true;
                    CProcessRef.labelParameter21.Text = "Filter Order:";
                    CProcessRef.labelParameter23.Text = "Range(? -5~+5)";
                    CProcessRef.tbParameter21.Text = "-1";
                    CProcessRef.tbParameter22.Text = "1";
                    CProcessRef.tbParameter23.Text = "1";
                    //Parameter 3
                    CProcessRef.tbParameter31.Enabled = false;
                    CProcessRef.tbParameter32.Enabled = false;
                    CProcessRef.tbParameter33.Enabled = false;
                    CProcessRef.labelParameter31.Text = "Parameter 3:";
                    CProcessRef.labelParameter33.Text = "(Parameter Range)";
                    CProcessRef.tbParameter31.Text = "0";
                    CProcessRef.tbParameter32.Text = "0";
                    CProcessRef.tbParameter33.Text = "0";
                    break;
                default:
                    break;
            }
        }

        public void process_btAddProcess_Click()
        {
            if (CProcessRef.cbBoxSeclectProcess.Text == "Select Process Here" || CProcessRef.cbBoxSelectStage.Text == "Select Stage Here")
                MessageBox.Show("Please select a process or a stage before adding.", "Select process or stage",
                                   MessageBoxButtons.OK, MessageBoxIcon.Warning);
            else
            {
                try
                {
                    string abbreviatedName = "Null";
                    switch (CProcessRef.cbBoxSeclectProcess.Text)
                    {
                        case "ACE II":
                            abbreviatedName = "ACEII";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Adaptive Median Filtering":
                            abbreviatedName = "AdaptMed";
                            //parameter protection
                            parameterProcess();
                            //Limit parameter's range
                            if (p1L < 3) { p1L = 3; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            if (p1U > 11) { p1U = 11; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            //calculation options
                            calculateOption();
                            break;

                        case "Anisotropic Diffusion Filter":
                            abbreviatedName = "ADFilter";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Alpha Filtering":
                            abbreviatedName = "Alpha";
                            parameterProcess();
                            if (p1L < 3) { p1L = 3; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            if (p1U > 11) { p1U = 11; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            if (p2L < 0) { p2L = 0; CProcessRef.tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            calculateOption();
                            break;

                        case "Boie-Cox Edge Detection":
                            abbreviatedName = "Boie-Cox";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Boie-Cox-Hysterisis":
                            abbreviatedName = "Boie-Cox-Hysterisis";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Binary Thresholding":
                            abbreviatedName = "BT";
                            //Check lower limit of parameter 1
                            if (p1L < 0)
                            {
                                p1L = 0;
                                CProcessRef.tbParameter11.Text = p1L.ToString();
                            }
                            //Check upper limit of parameter 1
                            if (p1U > 255)
                            {
                                p1U = 255;
                                CProcessRef.tbParameter13.Text = p1U.ToString();
                            }
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Canny Edge Detection":
                            abbreviatedName = "Canny";
                            /*if (p1L < 0)
                            {
                                p1L = 0;
                                CProcessRef.tbParameter11.Text = p1L.ToString();
                            }
                            if (p1U > 10)
                            {
                                p1U = 10;
                                CProcessRef.tbParameter13.Text = p1U.ToString();
                            }
                            if (p2L < p1U)
                            {
                                p2L = p1U;
                                CProcessRef.tbParameter21.Text = p2L.ToString();
                            }
                            if (p2U > 10)
                            {
                                p2U = 10;
                                CProcessRef.tbParameter23.Text = p2U.ToString();
                            }
                            if (p3L < 0.5)
                            {
                                p3L = 0.5;
                                CProcessRef.tbParameter31.Text = p3L.ToString();
                            }
                            if (p3U > 5.0)
                            {
                                p3U = 5.0;
                                CProcessRef.tbParameter33.Text = p3U.ToString();
                            }*/
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Color-to-Gray Conversion - Average":
                            abbreviatedName = "C2GA";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Color-to-Gray Conversion - Luminance":
                            abbreviatedName = "C2GL";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Color Transformation (RGB->HSL,HSV,SCT,CCT,LUV,LAB,XYZ)":
                            abbreviatedName = "ColorXForm";
                            if (p1L < 3)
                            {
                                p1L = 3;
                                CProcessRef.tbParameter11.Text = p1L.ToString();
                            }
                            if (p1U > 9)
                            {
                                p1U = 9;
                                CProcessRef.tbParameter13.Text = p1U.ToString();
                            }
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Contra-Harmonic Filtering":
                            abbreviatedName = "ContraH";
                            parameterProcess();
                            if (p1L < 3) { p1L = 3; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            if (p1U > 11) { p1U = 11; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; CProcessRef.tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            calculateOption();
                            break;

                        case "Contrast-Limited Adaptive Hist Eq":
                            abbreviatedName = "CLAHE";
                            parameterProcess();
                            calculateOption();
                            break;


                        case "Direct Cosine Transform":
                            abbreviatedName = "DCT";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Extract Band":
                            abbreviatedName = "EB";
                            if (p1L < 1)
                            {
                                p1L = 1;
                                CProcessRef.tbParameter11.Text = p1L.ToString();
                            }
                            if (p1U > 3)
                            {
                                p1U = 3;
                                CProcessRef.tbParameter13.Text = p1U.ToString();
                            }
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Edge-Linking":
                            abbreviatedName = "EdgeL";
                            //Check lower limit of parameter 1
                            if (p1L < 0)
                            {
                                p1L = 0;
                                CProcessRef.tbParameter11.Text = p1L.ToString();
                            }
                            //Check upper limit of parameter 1
                            /*if (p1U > 10)
                            {
                                p1U = 10;
                                CProcessRef.tbParameter13.Text = p1U.ToString();
                            }*/
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Fast Fourier Transform":
                            abbreviatedName = "FFT";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Fuzzyc Segmentation":
                            abbreviatedName = "Fuzzyc";
                            parameterProcess();
                            if (p1L < 0) { p1L = 0; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            if (p1U > 20.0) { p1U = 20.0; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; CProcessRef.tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            calculateOption();
                            break;

                        case "Gaussian Filter":
                            abbreviatedName = "GaussianFilter";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Geometric Filtering":
                            abbreviatedName = "Geo";
                            //parameter protection
                            parameterProcess();
                            //Limit parameter's range
                            if (p1L < 3) { p1L = 3; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            if (p1U > 11) { p1U = 11; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            //calculation options
                            calculateOption();
                            break;

                        case "Gray Level Quantization":
                            abbreviatedName = "GLQ";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Haar Transform":
                            abbreviatedName = "HaarT";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Harmonic Filtering":
                            abbreviatedName = "Harmon";
                            //parameter protection
                            parameterProcess();
                            //Limit parameter's range
                            if (p1L < 3) { p1L = 3; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            if (p1U > 11) { p1U = 11; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            //calculation options
                            calculateOption();
                            break;

                        case "High Boost":
                            abbreviatedName = "High Boost";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "High Freq. Emphasis (DC=>On)":
                            abbreviatedName = "HighBoost-DC";
                            /*if (p1L < 64)
                            {
                                p1L = 64;
                                CProcessRef.tbParameter11.Text = p1L.ToString();
                            }*/
                            /*if (p1U > 512)
                            {
                                p1U = 512;
                                CProcessRef.tbParameter13.Text = p1U.ToString();
                            }*/
                            if (p2L < 1.2)
                            {
                                p2L = 1.2;
                                CProcessRef.tbParameter21.Text = p2L.ToString();
                            }
                            if (p2U > 2.5)
                            {
                                p2U = 2.5;
                                CProcessRef.tbParameter23.Text = p2U.ToString();
                            }
                            if (p3L < 1)
                            {
                                p3L = 1;
                                CProcessRef.tbParameter31.Text = p3L.ToString();
                            }
                            if (p3U > 8)
                            {
                                p3U = 8;
                                CProcessRef.tbParameter33.Text = p3U.ToString();
                            }
                            parameterProcess();
                            calculateOption();
                            break;

                        case "High Freq. Emphasis (DC=>Off)":
                            abbreviatedName = "HighBoost";
                            /*if (p1L < 64)
                            {
                                p1L = 64;
                                CProcessRef.tbParameter11.Text = p1L.ToString();
                            }*/
                            /*if (p1U > 512)
                            {
                                p1U = 512;
                                CProcessRef.tbParameter13.Text = p1U.ToString();
                            }*/
                            if (p2L < 1.2)
                            {
                                p2L = 1.2;
                                CProcessRef.tbParameter21.Text = p2L.ToString();
                            }
                            if (p2U > 2.5)
                            {
                                p2U = 2.5;
                                CProcessRef.tbParameter23.Text = p2U.ToString();
                            }
                            if (p3L < 1)
                            {
                                p3L = 1;
                                CProcessRef.tbParameter31.Text = p3L.ToString();
                            }
                            if (p3U > 8)
                            {
                                p3U = 8;
                                CProcessRef.tbParameter33.Text = p3U.ToString();
                            }
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Highpass Spatial Filter":
                            abbreviatedName = "Highpass Spatial Filter";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Histogram Equalization":
                            abbreviatedName = "HistEq";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Histogram Slide":
                            abbreviatedName = "HistSlide";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Histogram Stretch":
                            abbreviatedName = "HistStr";
                            //Check lower limit of parameter 3
                            if (p3L < 0)
                            {
                                p3L = 0;
                                CProcessRef.tbParameter21.Text = p3L.ToString();
                            }
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Histogram Thresholding Segmentation":
                            abbreviatedName = "HistThresh";
                            //parameter protection
                            parameterProcess();
                            //calculation options
                            calculateOption();
                            break;

                        case "Hough Transform":
                            abbreviatedName = "HT";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "HSL -> RGB Transform":
                            abbreviatedName = "HSL-RGB";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "HSV -> RGB Transform":
                            abbreviatedName = "HSV-RGB";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Inverse Direct Cosine Transform":
                            abbreviatedName = "IDCT";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Inverse Fast Fourier Transform":
                            abbreviatedName = "IFFT";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Kuwahara Filter":
                            abbreviatedName = "Kuwahara Filter";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Laplacian Edge Detection":
                            abbreviatedName = "LapEDet";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Label Image":
                            abbreviatedName = "Lbl";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Maximum Filtering":
                            abbreviatedName = "Maxi";
                            //parameter protection
                            parameterProcess();
                            //Limit parameter's range
                            if (p1L < 3) { p1L = 3; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            if (p1U > 11) { p1U = 11; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            //calculation options
                            calculateOption();
                            break;

                        case "Mean Filtering":
                            abbreviatedName = "Mean";
                            parameterProcess();
                            if (p1L < 3) { p1L = 3; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            if (p1U > 11) { p1U = 11; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            calculateOption();
                            break;

                        case "Median Cut Segmentation":
                            abbreviatedName = "MedCut";
                            //parameter protection
                            parameterProcess();
                            //Limit parameter's range
                            if (p1L < 2) { p1L = 2; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            if (p1U > 1000) { p1U = 1000; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            //calculation options
                            calculateOption();
                            break;

                        case "Median Filtering":
                            abbreviatedName = "Med";
                            //parameter protection
                            parameterProcess();
                            //Limit parameter's range
                            if (p1L < 3) { p1L = 3; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            if (p1U > 31) { p1U = 31; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            //calculation options
                            calculateOption();
                            break;

                        case "Midpoint Filtering":
                            abbreviatedName = "MidP";
                            //parameter protection
                            parameterProcess();
                            //Limit parameter's range
                            if (p1L < 3) { p1L = 3; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            if (p1U > 11) { p1U = 11; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            //calculation options
                            calculateOption();
                            break;

                        case "MMSE Filtering":
                            abbreviatedName = "MMSE";
                            parameterProcess();
                            //if (p1L < 0) { p1L = 0; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 20.0) { p1U = 20.0; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; CProcessRef.tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            calculateOption();
                            break;

                        case "Morphological Closing-Circle Filtering":
                            abbreviatedName = "MorphCCir";
                            parameterProcess();
                            //if (p1L < 0) { p1L = 0; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 20.0) { p1U = 20.0; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            calculateOption();
                            break;

                        case "Morphological Closing-Cross Filtering":
                            abbreviatedName = "MorphCCro";
                            parameterProcess();
                            //if (p1L < 3) { p1L = 3; tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 11) { p1U = 11; tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            //if (p3L < 3) { p3L = 3; tbParameter11.Text = p1L.ToString(); }
                            //if (p3U > 11) { p3U = 11; tbParameter13.Text = p1U.ToString(); }                          
                            calculateOption();
                            break;

                        case "Morphological Closing-Rectangle Filtering":
                            abbreviatedName = "MorphCR";
                            parameterProcess();
                            //if (p1L < 3) { p1L = 3; tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 11) { p1U = 11; tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            //if (p3L < 3) { p3L = 3; tbParameter11.Text = p1L.ToString(); }
                            //if (p3U > 11) { p3U = 11; tbParameter13.Text = p1U.ToString(); }                          
                            calculateOption();
                            break;

                        case "Morphological Closing-Square Filtering":
                            abbreviatedName = "MorphCS";
                            parameterProcess();
                            //if (p1L < 0) { p1L = 0; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 20.0) { p1U = 20.0; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; CProcessRef.tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            calculateOption();
                            break;

                        case "Morphological Dilation-Circle Filtering":
                            abbreviatedName = "MorphDCir";
                            parameterProcess();
                            //if (p1L < 0) { p1L = 0; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 20.0) { p1U = 20.0; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            calculateOption();
                            break;

                        case "Morphological Dilation-Cross Filtering":
                            abbreviatedName = "MorphDCro";
                            parameterProcess();
                            //if (p1L < 3) { p1L = 3; tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 11) { p1U = 11; tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            //if (p3L < 3) { p3L = 3; tbParameter11.Text = p1L.ToString(); }
                            //if (p3U > 11) { p3U = 11; tbParameter13.Text = p1U.ToString(); }                          
                            calculateOption();
                            break;

                        case "Morphological Dilation-Rectangle Filtering":
                            abbreviatedName = "MorphDR";
                            parameterProcess();
                            //if (p1L < 3) { p1L = 3; tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 11) { p1U = 11; tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            //if (p3L < 3) { p3L = 3; tbParameter11.Text = p1L.ToString(); }
                            //if (p3U > 11) { p3U = 11; tbParameter13.Text = p1U.ToString(); }                          
                            calculateOption();
                            break;

                        case "Morphological Dilation-Square Filtering":
                            abbreviatedName = "MorphDS";
                            parameterProcess();
                            //if (p1L < 0) { p1L = 0; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 20.0) { p1U = 20.0; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; CProcessRef.tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            calculateOption();
                            break;

                        case "Morphological Erosion-Circle Filtering":
                            abbreviatedName = "MorphECir";
                            parameterProcess();
                            //if (p1L < 0) { p1L = 0; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 20.0) { p1U = 20.0; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            calculateOption();
                            break;

                        case "Morphological Erosion-Cross Filtering":
                            abbreviatedName = "MorphECro";
                            parameterProcess();
                            //if (p1L < 3) { p1L = 3; tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 11) { p1U = 11; tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            //if (p3L < 3) { p3L = 3; tbParameter11.Text = p1L.ToString(); }
                            //if (p3U > 11) { p3U = 11; tbParameter13.Text = p1U.ToString(); }                          
                            calculateOption();
                            break;

                        case "Morphological Erosion-Rectangle Filtering":
                            abbreviatedName = "MorphER";
                            parameterProcess();
                            //if (p1L < 3) { p1L = 3; tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 11) { p1U = 11; tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            //if (p3L < 3) { p3L = 3; tbParameter11.Text = p1L.ToString(); }
                            //if (p3U > 11) { p3U = 11; tbParameter13.Text = p1U.ToString(); }                          
                            calculateOption();
                            break;

                        case "Morphological Erosion-Square Filtering":
                            abbreviatedName = "MorphES";
                            parameterProcess();
                            //if (p1L < 0) { p1L = 0; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 20.0) { p1U = 20.0; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; CProcessRef.tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            calculateOption();
                            break;

                        case "Morphological Opening-Circle Filtering":
                            abbreviatedName = "MorphOCir";
                            parameterProcess();
                            //if (p1L < 0) { p1L = 0; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 20.0) { p1U = 20.0; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            calculateOption();
                            break;

                        case "Morphological Opening-Cross Filtering":
                            abbreviatedName = "MorphOCro";
                            parameterProcess();
                            //if (p1L < 3) { p1L = 3; tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 11) { p1U = 11; tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            //if (p3L < 3) { p3L = 3; tbParameter11.Text = p1L.ToString(); }
                            //if (p3U > 11) { p3U = 11; tbParameter13.Text = p1U.ToString(); }                          
                            calculateOption();
                            break;

                        case "Morphological Opening-Rectangle Filtering":
                            abbreviatedName = "MorphOR";
                            parameterProcess();
                            //if (p1L < 3) { p1L = 3; tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 11) { p1U = 11; tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            //if (p3L < 3) { p3L = 3; tbParameter11.Text = p1L.ToString(); }
                            //if (p3U > 11) { p3U = 11; tbParameter13.Text = p1U.ToString(); }                          
                            calculateOption();
                            break;

                        case "Morphological Opening-Square Filtering":
                            abbreviatedName = "MorphOS";
                            parameterProcess();
                            //if (p1L < 0) { p1L = 0; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 20.0) { p1U = 20.0; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; CProcessRef.tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            calculateOption();
                            break;

                        case "MorphSkel 4-mask,And":
                            abbreviatedName = "MorphSkel 4-mask,And";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "MorphSkel 4-mask,Sequential":
                            abbreviatedName = "MorphSkel 4-mask,Sequential";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "MorphSkel 8-mask,And":
                            abbreviatedName = "MorphSkel 8-mask,And";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "MorphSkel 8-mask,Sequential":
                            abbreviatedName = "MorphSkel 8-mask,Sequential";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Not":
                            abbreviatedName = "Not";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Otsu Thresholding":
                            abbreviatedName = "Otsu";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Parametric AD Filter":
                            abbreviatedName = "ParamADFilter";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "PCT Transform":
                            abbreviatedName = "PCT";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "PCT Median Segmentation":
                            abbreviatedName = "PCTM";
                            parameterProcess();
                            if (p1L < 0) { p1L = 0; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            if (p1U > 1000) { p1U = 1000; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            calculateOption();
                            break;

                        case "Prewitt Edge Detection":
                            abbreviatedName = "Prewitt";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Roberts Edge Detection":
                            abbreviatedName = "Roberts";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Auto Single Threshold":
                            abbreviatedName = "SingleThresh";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "SCT Center Segmentation":
                            abbreviatedName = "SCT";
                            parameterProcess();
                            //if (p1L < 0) { p1L = 0; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            //if (p1U > 20.0) { p1U = 20.0; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; CProcessRef.tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            calculateOption();
                            break;

                        case "Sharpening AlgorithmI ( Mask II )":
                            abbreviatedName = "SharpeningI";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Sharpening AlgorithmII":
                            abbreviatedName = "SharpeningII";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Shen-Castan Edge Detection":
                            abbreviatedName = "Shen-Castan";
                            /*if (p1L < 0)
                            {
                                p1L = 0;
                                CProcessRef.tbParameter11.Text = p1L.ToString();
                            }
                            if (p1U > 10)
                            {
                                p1U = 10;
                                CProcessRef.tbParameter13.Text = p1U.ToString();
                            }
                            if (p2L < p1U)
                            {
                                p2L = p1U;
                                CProcessRef.tbParameter21.Text = p2L.ToString();
                            }
                            if (p2U > 10)
                            {
                                p2U = 10;
                                CProcessRef.tbParameter23.Text = p2U.ToString();
                            }
                            if (p3L < 0.0)
                            {
                                p3L = 0.0;
                                CProcessRef.tbParameter31.Text = p3L.ToString();
                            }
                            if (p3U > 1.0)
                            {
                                p3U = 1.0;
                                CProcessRef.tbParameter33.Text = p3U.ToString();
                            }*/
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Skip/Null":
                            abbreviatedName = "Skip";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Sobel Edge Detection":
                            abbreviatedName = "Sobel";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Spatial Quantization":
                            abbreviatedName = "SQuant";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Threshold(remapped) Segmentation":
                            abbreviatedName = "Thresh";
                            parameterProcess();
                            if (p1L < 0) { p1L = 0; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            if (p1U > 255) { p1U = 255; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            calculateOption();
                            break;

                        case "Unsharp Masking":
                            abbreviatedName = "Unsharp Masking";
                            parameterProcess();
                            calculateOption();
                            break;

                        /*case "Edge Enhancement with Unsharp Masking":
                            abbreviatedName = "UnsharpMask";
                            parameterProcess();
                            calculateOption();
                            break;*/

                        case "Walsh-Hadamard Transform":
                            abbreviatedName = "WHTrans";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Watershed Segmentation":
                            abbreviatedName = "Watershed";
                            parameterProcess();
                            calculateOption();
                            break;

                        case "Yp-Mean Filtering":
                            abbreviatedName = "Yp";
                            parameterProcess();
                            if (p1L < 3) { p1L = 3; CProcessRef.tbParameter11.Text = p1L.ToString(); }
                            if (p1U > 11) { p1U = 11; CProcessRef.tbParameter13.Text = p1U.ToString(); }
                            //if (p2L < 0) { p2L = 0; CProcessRef.tbParameter21.Text = p2L.ToString(); }
                            //if (p2U > unlimited) {p2U = "unlimited";tbParameter23.Text = p2U.ToString();}//(n*n-1)/2
                            calculateOption();
                            break;

                        default:
                            break;
                    }

                    //Calculate stages and add algorith into viewlist.  
                    addProcessTovViewlist(abbreviatedName);
                }
                catch
                {
                    MessageBox.Show("Please check your parameters. Increment should be bigger than 0." +
                         "  Upper bound should be bigger or equal lower bound." + "  Please input digit.",
                        "Process Input Incorrect Format!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }

            }
        }

        private void parameterProcess()
        {
            //no parameter
            if (CProcessRef.tbParameter11.Enabled == false)
            { }

            // one parameter
            if (CProcessRef.tbParameter11.Enabled == true && CProcessRef.tbParameter21.Enabled == false)
            {
                p1I = Convert.ToDouble(CProcessRef.tbParameter12.Text);
                p1L = Convert.ToDouble(CProcessRef.tbParameter11.Text);
                p1U = Convert.ToDouble(CProcessRef.tbParameter13.Text);

                //use this codes to make a exception that cause a message box.
                if (p1I <= 0 || p1U < p1L)
                {
                    int a = 1, b = 0;
                    a = a / b;
                }

                p2I = 0;
                p2L = 0;
                p2U = 0;
                p3I = 0;
                p3L = 0;
                p3U = 0;

            }
            // two parameters
            if (CProcessRef.tbParameter21.Enabled == true && CProcessRef.tbParameter31.Enabled == false)
            {
                p1I = Convert.ToDouble(CProcessRef.tbParameter12.Text);
                p1L = Convert.ToDouble(CProcessRef.tbParameter11.Text);
                p1U = Convert.ToDouble(CProcessRef.tbParameter13.Text);
                //use this codes to make a exception that cause a messenge box.
                if (p1I <= 0 || p1U < p1L)
                {
                    int a = 1, b = 0;
                    a = a / b;
                }

                p2I = Convert.ToDouble(CProcessRef.tbParameter22.Text);
                p2L = Convert.ToDouble(CProcessRef.tbParameter21.Text);
                p2U = Convert.ToDouble(CProcessRef.tbParameter23.Text);
                //use this codes to make a exception that cause a messenge box.
                if (p2I <= 0 || p2U < p2L)
                {
                    int a = 1, b = 0;
                    a = a / b;
                }

                p3I = 0;
                p3L = 0;
                p3U = 0;
            }

            // three parameters
            if (CProcessRef.tbParameter31.Enabled == true)//just has 3 parameters situation
            //if (tbParameter31.Enabled == true && tbParameter41.Enabled == false)//has 4 parameters situation
            {
                p1I = Convert.ToDouble(CProcessRef.tbParameter12.Text);
                p1L = Convert.ToDouble(CProcessRef.tbParameter11.Text);
                p1U = Convert.ToDouble(CProcessRef.tbParameter13.Text);
                //use this codes to make a exception that cause a message box.
                if (p1I <= 0 || p1U < p1L)
                {
                    int a = 1, b = 0;
                    a = a / b;
                }

                p2I = Convert.ToDouble(CProcessRef.tbParameter22.Text);
                p2L = Convert.ToDouble(CProcessRef.tbParameter21.Text);
                p2U = Convert.ToDouble(CProcessRef.tbParameter23.Text);
                //use this codes to make a exception that cause a message box.
                if (p2I <= 0 || p2U < p2L)
                {
                    int a = 1, b = 0;
                    a = a / b;
                }

                p3I = Convert.ToDouble(CProcessRef.tbParameter32.Text);
                p3L = Convert.ToDouble(CProcessRef.tbParameter31.Text);
                p3U = Convert.ToDouble(CProcessRef.tbParameter33.Text);
                //use this codes to make a exception that cause a message box.
                if (p3I <= 0 || p3U < p3L)
                {
                    int a = 1, b = 0;
                    a = a / b;
                }
            }

        }

        private void calculateOption()
        {
            string proOptions1, proOptions2, proOptions3;
            char[] sp = { '.' };
            string[] splitresult;
            //calculate the number of options
            //splitresult[0] is the integer part of the double
            //no parameter
            if (CProcessRef.tbParameter11.Enabled == false)
            {
            }

            // one parameter
            if (CProcessRef.tbParameter11.Enabled == true && CProcessRef.tbParameter21.Enabled == false)
            {
                proOptions1 = Convert.ToString((p1U - p1L) / p1I);
                splitresult = proOptions1.Split(sp);
                processOptions1 = Convert.ToInt16(splitresult[0]) + 1;

                //initiate the array for parameter 1 that under different options. 
                p1Options = new double[processOptions1];
                p1Options[0] = p1L;
                for (int i = 1; i < processOptions1; i++)
                {
                    p1Options[i] = p1Options[i - 1] + p1I;
                }
            }
            // two parameters
            if (CProcessRef.tbParameter21.Enabled == true && CProcessRef.tbParameter31.Enabled == false)
            {
                proOptions1 = Convert.ToString((p1U - p1L) / p1I);
                splitresult = proOptions1.Split(sp);
                processOptions1 = Convert.ToInt16(splitresult[0]) + 1;
                proOptions2 = Convert.ToString((p2U - p2L) / p2I);
                splitresult = proOptions2.Split(sp);
                processOptions2 = Convert.ToInt16(splitresult[0]) + 1;

                p1Options = new double[processOptions1];
                p1Options[0] = p1L;
                for (int i = 1; i < processOptions1; i++)
                {
                    p1Options[i] = p1Options[i - 1] + p1I;
                }

                p2Options = new double[processOptions2];
                p2Options[0] = p2L;
                for (int i = 1; i < processOptions2; i++)
                {
                    p2Options[i] = p2Options[i - 1] + p2I;
                }

            }
            // three parameters
            if (CProcessRef.tbParameter31.Enabled == true)//just has 3 parameters situation
            //if (tbParameter31.Enabled == true && tbParameter41.Enabled == false)//has 4 parameters situation
            {
                proOptions1 = Convert.ToString((p1U - p1L) / p1I);
                splitresult = proOptions1.Split(sp);
                processOptions1 = Convert.ToInt16(splitresult[0]) + 1;
                proOptions2 = Convert.ToString((p2U - p2L) / p2I);
                splitresult = proOptions2.Split(sp);
                processOptions2 = Convert.ToInt16(splitresult[0]) + 1;
                proOptions3 = Convert.ToString((p3U - p3L) / p3I);
                splitresult = proOptions3.Split(sp);
                processOptions3 = Convert.ToInt16(splitresult[0]) + 1;

                p1Options = new double[processOptions1];
                p1Options[0] = p1L;
                for (int i = 1; i < processOptions1; i++)
                {
                    p1Options[i] = p1Options[i - 1] + p1I;
                }

                p2Options = new double[processOptions2];
                p2Options[0] = p2L;
                for (int i = 1; i < processOptions2; i++)
                {
                    p2Options[i] = p2Options[i - 1] + p2I;
                }

                p3Options = new double[processOptions3];
                p3Options[0] = p3L;
                for (int i = 1; i < processOptions3; i++)
                {
                    p3Options[i] = p3Options[i - 1] + p3I;
                }

            }
        }

        private void addProcessTovViewlist(string abbreviatedNam)
        {
            ListViewItem objListView;
            int totalOptionsImage = 1;
            int itemindex = -1;


            //no parameter
            if (CProcessRef.tbParameter11.Enabled == false)
            {
                objListView = CProcessRef.lvProcess.Items.Add(CProcessRef.cbBoxSelectStage.Text);
                objListView.SubItems.Add("0");
                objListView.SubItems.Add(abbreviatedNam);
                objListView.SubItems.Add("-0");
                objListView.SubItems.Add("-0");
                objListView.SubItems.Add("-0");
            }

            // one parameter
            if (CProcessRef.tbParameter11.Enabled == true && CProcessRef.tbParameter21.Enabled == false)
            {
                for (int i = 0; i < processOptions1; i++)
                {
                    objListView = CProcessRef.lvProcess.Items.Add(CProcessRef.cbBoxSelectStage.Text);
                    objListView.SubItems.Add("0");
                    objListView.SubItems.Add(abbreviatedNam);
                    objListView.SubItems.Add(p1Options[i].ToString());
                    objListView.SubItems.Add("-0");
                    objListView.SubItems.Add("-0");

                }
            }
            // two parameters
            if (CProcessRef.tbParameter21.Enabled == true && CProcessRef.tbParameter31.Enabled == false)
            {
                for (int i = 0; i < processOptions1; i++)
                {
                    for (int j = 0; j < processOptions2; j++)
                    {
                        objListView = CProcessRef.lvProcess.Items.Add(CProcessRef.cbBoxSelectStage.Text);
                        objListView.SubItems.Add("0");
                        objListView.SubItems.Add(abbreviatedNam);
                        objListView.SubItems.Add(p1Options[i].ToString());
                        objListView.SubItems.Add(p2Options[j].ToString());
                        objListView.SubItems.Add("-0");
                    }

                }

            }
            // three parameters
            if (CProcessRef.tbParameter31.Enabled == true)//just has 3 parameters situation
            {
                for (int i = 0; i < processOptions1; i++)
                {
                    for (int j = 0; j < processOptions2; j++)
                    {
                        for (int k = 0; k < processOptions3; k++)
                        {
                            objListView = CProcessRef.lvProcess.Items.Add(CProcessRef.cbBoxSelectStage.Text);
                            objListView.SubItems.Add("0");
                            objListView.SubItems.Add(abbreviatedNam);
                            objListView.SubItems.Add(p1Options[i].ToString());
                            objListView.SubItems.Add(p2Options[j].ToString());
                            objListView.SubItems.Add(p3Options[k].ToString());
                        }
                    }
                }
            }

            //calculate the option of every stage
            for (int i = 0; i < CProcessRef.lvProcess.Items.Count; i++)
            {
                if (CProcessRef.lvProcess.Items[i].SubItems[0].Text == CProcessRef.cbBoxSelectStage.Text)
                {
                    //get the index(initial address) of the selected stage 
                    if (itemindex == -1)
                    {   //optionInOneStageCount[0] is the first stage         
                        optionInOneStageCount[Convert.ToInt16(CProcessRef.cbBoxSelectStage.Text) - 1] = 0;
                        itemindex = CProcessRef.lvProcess.Items[i].Index;
                    }
                    //get the number of option within the same stage
                    optionInOneStageCount[Convert.ToInt16(CProcessRef.cbBoxSelectStage.Text) - 1]++;
                }
            }
            //reset the option sequence in the listview
            for (int i = 0; i < optionInOneStageCount[Convert.ToInt16(CProcessRef.cbBoxSelectStage.Text) - 1]; i++)
            {
                CProcessRef.lvProcess.Items[itemindex + i].SubItems[1].Text = (i + 1).ToString();
            }


            //calculate the total options of all stages
            for (int i = 0; i < optionInOneStageCount.Length; i++)
            {
                if (optionInOneStageCount[i] != 0)
                {
                    totalOptionsImage = totalOptionsImage * optionInOneStageCount[i];
                }
            }
            //display the number of total options in GUI
            CProcessRef.tbTotalOptionsImage.Text = totalOptionsImage.ToString();

            //prepare for adding next stage
            if (CProcessRef.cbBoxSelectStage.Text == "Select Stage Here")
                CProcessRef.cbBoxSelectStage.Text = "1";
        }

        public void process_btUp_Click()
        {
            if (CProcessRef.lvProcess.SelectedItems.Count > 0)
            {
                int i;
                int selIdx = CProcessRef.lvProcess.SelectedItems[0].Index;
                string[] cache = new string[6];
                if (selIdx > 0)
                {
                    if (Convert.ToInt16(CProcessRef.lvProcess.Items[selIdx].SubItems[0].Text) > Convert.ToInt16(CProcessRef.lvProcess.Items[selIdx - 1].SubItems[0].Text))
                        CProcessRef.lvProcess.Items[selIdx].SubItems[0].Text = CProcessRef.lvProcess.Items[selIdx - 1].SubItems[0].Text;
                    for (i = 0; i < 6; i++)
                        cache[i] = CProcessRef.lvProcess.Items[selIdx].SubItems[i].Text;
                    for (i = 0; i < 6; i++)
                    {
                        CProcessRef.lvProcess.Items[selIdx].SubItems[i].Text = CProcessRef.lvProcess.Items[selIdx - 1].SubItems[i].Text;
                        CProcessRef.lvProcess.Items[selIdx - 1].SubItems[i].Text = cache[i];
                    }
                    reCalculateOptionCount();
                    CProcessRef.lvProcess.Items[selIdx - 1].Selected = true;
                }
                CProcessRef.lvProcess.Refresh();
                CProcessRef.lvProcess.Focus();
            }
            else
            {
                MessageBox.Show("Make sure a row is highlighted in blue by selecting it. The checkboxes do not count as the selection.", "Row Not Selected!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        public void process_btDown_Click()
        {
            if (CProcessRef.lvProcess.SelectedItems.Count > 0)
            {
                int i;
                int selIdx = CProcessRef.lvProcess.SelectedItems[0].Index;
                string[] cache = new string[6];
                if (selIdx < CProcessRef.lvProcess.Items.Count - 1 && selIdx > -1)
                {
                    if (Convert.ToInt16(CProcessRef.lvProcess.Items[selIdx].SubItems[0].Text) < Convert.ToInt16(CProcessRef.lvProcess.Items[selIdx + 1].SubItems[0].Text))
                        CProcessRef.lvProcess.Items[selIdx].SubItems[0].Text = CProcessRef.lvProcess.Items[selIdx + 1].SubItems[0].Text;
                    for (i = 0; i < 6; i++)
                        cache[i] = CProcessRef.lvProcess.Items[selIdx].SubItems[i].Text;
                    for (i = 0; i < 6; i++)
                    {
                        CProcessRef.lvProcess.Items[selIdx].SubItems[i].Text = CProcessRef.lvProcess.Items[selIdx + 1].SubItems[i].Text;
                        CProcessRef.lvProcess.Items[selIdx + 1].SubItems[i].Text = cache[i];
                    }
                    reCalculateOptionCount();
                    CProcessRef.lvProcess.Items[selIdx + 1].Selected = true;
                }
                CProcessRef.lvProcess.Refresh();
                CProcessRef.lvProcess.Focus();
            }
            else
            {
                MessageBox.Show("Make sure a row is highlighted in blue by selecting it. The checkboxes do not count as the selection.", "Row Not Selected!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        public void process_btDeleteCheckedProcess_Click()
        {
            int checkedProcessItemCount = CProcessRef.lvProcess.CheckedItems.Count;
            if (checkedProcessItemCount == 0)
                MessageBox.Show("No processes are checked.", "Zero Checked Processes", MessageBoxButtons.OK, MessageBoxIcon.Question);
            else
            {
                //delete checked processes
                for (int i = checkedProcessItemCount - 1; i >= 0; i--)
                    CProcessRef.lvProcess.Items.Remove(CProcessRef.lvProcess.CheckedItems[i]);
                reCalculateOptionCount();
            }
        }

        public void Process_btDeleteAllProcesses_Click()
        {
            if (CProcessRef.lvProcess.Items.Count == 0)
                MessageBox.Show("No processes have been added", "Zero Processes", MessageBoxButtons.OK, MessageBoxIcon.Question);
            else
            {
                if (MessageBox.Show("Do you really want to delete all the processes in ListView?",
                        "Delete all processes", MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation)
                         == DialogResult.OK)
                {
                    CProcessRef.lvProcess.Items.Clear();
                    CProcessRef.tbTotalOptionsImage.Text = "0";
                    reCalculateOptionCount();
                }
            }
        }

        private void reCalculateOptionCount()
        {
            int i, count, curStage, totalOptionsImage = 1;
            bool miss = true;
            try
            {
                for (i = 0; i < 20; i++)
                    optionInOneStageCount[i] = 0;
                //Recalculate number of options per stage and recount options column
                count = curStage = 1;
                for (i = 0; i < CProcessRef.lvProcess.Items.Count; i++)
                {
                    optionInOneStageCount[Convert.ToInt16(CProcessRef.lvProcess.Items[i].SubItems[0].Text) - 1] += 1;
                    if (Convert.ToInt16(CProcessRef.lvProcess.Items[i].SubItems[0].Text) > curStage)
                    {
                        count = 1;
                        curStage = Convert.ToInt16(CProcessRef.lvProcess.Items[i].SubItems[0].Text);
                    }
                    CProcessRef.lvProcess.Items[i].SubItems[1].Text = count.ToString();
                    count++;
                }
                //Check if a stage was missed
                for (i = optionInOneStageCount.Length - 1; i >= 0; i--)
                {
                    if (optionInOneStageCount[i] != 0)
                        miss = false;
                    if (miss == false && optionInOneStageCount[i] == 0)
                        MessageBox.Show("Stages cannot be skipped. Please fix stages before running experiment.", "Missing Stage", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }

                //Calculate the total options of all stages
                for (i = 0; i < optionInOneStageCount.Length; i++)
                {
                    if (optionInOneStageCount[i] != 0)
                    {
                        totalOptionsImage = totalOptionsImage * optionInOneStageCount[i];
                    }
                }

                //display the the number of total options for one image in GUI
                if (CProcessRef.lvProcess.Items.Count == 0)
                { CProcessRef.tbTotalOptionsImage.Text = "0"; }
                else
                {
                    CProcessRef.tbTotalOptionsImage.Text = totalOptionsImage.ToString();
                }
            }
            catch
            {
                MessageBox.Show("Stages were recalculated incorrectly. Deleting current table is advised.", "Stage Recalculation Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        public void process_bt_DecreaseStage_Click()
        {
            if (CProcessRef.lvProcess.SelectedItems.Count > 0)
            {
                int i;
                int selIdx = CProcessRef.lvProcess.SelectedItems[0].Index;
                string[] cache = new string[6];
                if (Convert.ToInt16(CProcessRef.lvProcess.Items[selIdx].SubItems[0].Text) > 1)
                {
                    if (selIdx > 0)
                    {
                        CProcessRef.lvProcess.Items[selIdx].SubItems[0].Text = (Convert.ToInt16(CProcessRef.lvProcess.Items[selIdx].SubItems[0].Text) - 1).ToString();
                        while (Convert.ToInt16(CProcessRef.lvProcess.Items[selIdx].SubItems[0].Text) < Convert.ToInt16(CProcessRef.lvProcess.Items[selIdx - 1].SubItems[0].Text))
                        {
                            for (i = 0; i < 6; i++)
                                cache[i] = CProcessRef.lvProcess.Items[selIdx].SubItems[i].Text;
                            for (i = 0; i < 6; i++)
                            {
                                CProcessRef.lvProcess.Items[selIdx].SubItems[i].Text = CProcessRef.lvProcess.Items[selIdx - 1].SubItems[i].Text;
                                CProcessRef.lvProcess.Items[selIdx - 1].SubItems[i].Text = cache[i];
                            }
                            selIdx--;
                            if (selIdx == 0)
                                break;
                        }
                        CProcessRef.lvProcess.Items[selIdx].Selected = true;
                    }
                    else if (selIdx == 0)
                    {
                        CProcessRef.lvProcess.Items[selIdx].SubItems[0].Text = (Convert.ToInt16(CProcessRef.lvProcess.Items[selIdx].SubItems[0].Text) - 1).ToString();
                    }
                    reCalculateOptionCount();
                }
                CProcessRef.lvProcess.Refresh();
                CProcessRef.lvProcess.Focus();
            }
            else
            {
                MessageBox.Show("Make sure a row is highlighted in blue by selecting it. The checkboxes do not count as the selection.", "Row Not Selected!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        public void process_bt_IncreaseStage_Click()
        {
            if (CProcessRef.lvProcess.SelectedItems.Count > 0)
            {
                int i;
                int selIdx = CProcessRef.lvProcess.SelectedItems[0].Index;
                string[] cache = new string[6];
                if (selIdx < CProcessRef.lvProcess.Items.Count - 1 && selIdx > -1)
                {
                    CProcessRef.lvProcess.Items[selIdx].SubItems[0].Text = (Convert.ToInt16(CProcessRef.lvProcess.Items[selIdx].SubItems[0].Text) + 1).ToString();
                    while (Convert.ToInt16(CProcessRef.lvProcess.Items[selIdx].SubItems[0].Text) > Convert.ToInt16(CProcessRef.lvProcess.Items[selIdx + 1].SubItems[0].Text))
                    {
                        for (i = 0; i < 6; i++)
                            cache[i] = CProcessRef.lvProcess.Items[selIdx].SubItems[i].Text;
                        for (i = 0; i < 6; i++)
                        {
                            CProcessRef.lvProcess.Items[selIdx].SubItems[i].Text = CProcessRef.lvProcess.Items[selIdx + 1].SubItems[i].Text;
                            CProcessRef.lvProcess.Items[selIdx + 1].SubItems[i].Text = cache[i];
                        }
                        selIdx++;
                        if (selIdx == CProcessRef.lvProcess.Items.Count - 1)
                            break;
                    }
                    CProcessRef.lvProcess.Items[selIdx].Selected = true;
                }
                else if (selIdx == CProcessRef.lvProcess.Items.Count - 1)
                {
                    CProcessRef.lvProcess.Items[selIdx].SubItems[0].Text = (Convert.ToInt16(CProcessRef.lvProcess.Items[selIdx].SubItems[0].Text) + 1).ToString();
                }
                reCalculateOptionCount();
                CProcessRef.lvProcess.Refresh();
                CProcessRef.lvProcess.Focus();
            }
            else
            {
                MessageBox.Show("Make sure a row is highlighted in blue by selecting it. The checkboxes do not count as the selection.", "Row Not Selected!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
    }
}
