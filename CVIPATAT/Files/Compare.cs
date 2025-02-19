/***************************************************************************
* =========================================================================
*
*			 CVIP_ATAT - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*              File Name: Compare.cs 
*            Description: Class used to compare test and ideal images.
*    Initial Coding Date: January 31, 2020
*Last Modification Made: July 21, 2021
*  Programming Language: Visual Studio C#.NET 2019
*             Credit(s): Charles Stacey with Code from 
*                        Wenjun(Evan) Bian and Pelin Guvenc
*                        Southern Illinois University at Edwardsville
*
*		  Copyright (c): 2010-2021 SIUE - Scott Umbaugh
****************************************************************************/

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.IO;
using System.Threading;

namespace CVIP_ATAT.Files
{
    class Compare
    {
        CVIPATATForm CVIPComRef; // Needed for CVIPtools processes.
        ManualResetEvent mainThreadCTL; //Used to pause/resume compare thread.

        string resultsFolder; //Results Image Folder Location.
        string idealFolder; //Ideal Image Folder Location.
        string[] results, ideal; //Holds the filenames of all images.
        string algFile; //Algorithm File Location
        double[] errorValues; //Holds the error values to be compared to.
        bool average; //Value that tells if the user wants to view the algorithm averages.
        bool stdDev; //True if the user wants standard deviation.
        int band = 1; //Holds Maximum Number of Bands in Images
        int xorThresh; //Xor Threashold Value
        int arraySize; //Total array size for data needed.
        string errorCode = "0"; //Error code used to display messages to user.
        double[,] allValues;

        string[] metrics = { "RMS", "SNR", "SUB", "DICE", "JACC", "OVER", "XOR" };
        string[] algorithms; //Holds algorithm string for every test image.

        int[] errorCheck = new int[7]; //Tells if error is used.

        int tImage, iImage; //Temporary images.

        //Create Comparison Object
        public Compare(string ResultImageFolder, string IdealImageFolder, string algorithmFile, double[] errors, bool[] avgStd, int thresh, CVIPATATForm CVIPATATreference, ManualResetEvent threadCTL)
        {
            CVIPComRef = CVIPATATreference;
            mainThreadCTL = threadCTL;
            resultsFolder = ResultImageFolder;
            idealFolder = IdealImageFolder;
            algFile = algorithmFile;
            errorValues = errors;
            average = avgStd[0];
            stdDev = avgStd[1];
            xorThresh = thresh;
            for (int i = 0; i < 19; i += 3)
            {
                errorCheck[i / 3] = 0;
                if (errorValues[i] != -1000)
                    errorCheck[i / 3] = 1;
            }
        }

        //Run Comparison Test
        public void compareImages(ref int progress)
        {
            int[] tempImage = new int[3]; //Image files
            int[] idealArray; //Holds all ideal images
            int resultsBand, idealBand; //Used for band changes.
            double[] funcResults; //Holds return values from error metric processes                      
            string fileName, justFile, line; //File information strings
            int split, columnOfArray, lineCheck; //Used to split the full path into the different components (Filename/Algorithm)
            int minProgress = progress; //Progress variable for GUI.
            int resultsImage, idealImage; //Holds currently used images
            int tRow, iRow, tCol, iCol; //Row and column numbers

            //Determine if the output directory was created.
            if (Directory.Exists(resultsFolder))
            {
                //Get File Names
                results = Directory.GetFiles(resultsFolder, "*", SearchOption.AllDirectories);
                ideal = Directory.GetFiles(idealFolder, "*", SearchOption.AllDirectories);

                //Remove ideal file extensions
                string[] idealNoExt = new string[ideal.Length];
                idealArray = new int[ideal.Length];
                for (int i = 0; i < ideal.Length; i++)
                {
                    try
                    {
                        idealArray[i] = CVIPComRef.CVIPTool.Read_Image(ref ideal[i]);
                    }
                    catch { idealArray[i] = 0; }
                    idealNoExt[i] = Path.GetFileNameWithoutExtension(ideal[i]);
                }

                //Determines max number of bands for ideal images.
                bandTest(ideal);

                //Create Output Files
                createOrDeleteOutputFiles(band);

                //Gets Number of Algorithms:
                List<string> algList = new List<string>();
                algorithms = new string[results.Length];
                for (int fileNumber = 0; fileNumber < results.Length; fileNumber++)
                {
                    justFile = Path.GetFileName(results[fileNumber]);
                    line = "";
                    //Get algorithms:
                    try
                    {
                        split = justFile.IndexOf(".");
                        justFile = justFile.Substring(split + 1, justFile.Length - split - 1);
                        split = justFile.IndexOf("_");
                        justFile = justFile.Substring(split + 1, justFile.Length - split - 1);
                        split = justFile.IndexOf("_");
                        justFile = justFile.Substring(0, split);
                        lineCheck = 0;

                        using (StreamReader sr = new StreamReader(algFile))
                        {
                            while (!sr.EndOfStream)
                            {
                                line = sr.ReadLine();
                                if (String.IsNullOrEmpty(line)) continue;
                                if (line.Contains(justFile))
                                {
                                    line = line.Remove(0, justFile.Length + 3);
                                    if (algList.Contains(line))
                                    { }
                                    else
                                        algList.Add(line);
                                    lineCheck = 1;
                                    break;
                                }
                            }
                        }
                    }
                    catch (Exception e)
                    {
                        lineCheck = 0;
                    }
                    if (lineCheck == 1)
                        algorithms[fileNumber] = line;
                    else
                        algorithms[fileNumber] = "Algorithm ID Not Found.";
                }

                //Holds all error metric results
                allValues = new double[results.Length, arraySize];

                //Tests Each File
                for (int fileNumber = 0; fileNumber < results.Length; fileNumber++)
                {
                    mainThreadCTL.WaitOne();
                    try //Error check for entire file calculation process
                    {
                        //Splits the filename from the algorithm name.
                        justFile = Path.GetFileName(results[fileNumber]);
                        split = justFile.IndexOf(".");
                        fileName = justFile.Substring(0, split);

                        //Get both images
                        resultsImage = CVIPComRef.CVIPTool.Read_Image(ref results[fileNumber]);
                        idealImage = idealArray[Array.IndexOf(idealNoExt, fileName)];

                        //If the band number does not match the overall, the bands are changed.
                        resultsBand = CVIPComRef.CVIPTool.GetNoOfBands_Image(ref resultsImage);
                        idealBand = CVIPComRef.CVIPTool.GetNoOfBands_Image(ref idealImage);

                        //Check if the images are the same size
                        tRow = CVIPComRef.CVIPTool.GetNoOfRows_Image(ref resultsImage);
                        iRow = CVIPComRef.CVIPTool.GetNoOfRows_Image(ref idealImage);
                        tCol = CVIPComRef.CVIPTool.GetNoOfCols_Image(ref resultsImage);
                        iCol = CVIPComRef.CVIPTool.GetNoOfCols_Image(ref idealImage);

                        //Runs test if the images are the same size
                        if (tRow == iRow && tCol == iCol)
                        {
                            //Checks if bands are the same
                            if (resultsBand != band)
                            {
                                //Converts three bands to one by taking the luminance.
                                if (band == 1)
                                {
                                    tempImage[0] = CVIPComRef.CVIPTool.Luminance_Image(ref resultsImage);
                                    CVIPComRef.CVIPTool.Delete_Image(ref resultsImage);
                                    resultsImage = tempImage[0];
                                }
                                //Converts one band to three by copying band to three images and assembling them
                                else
                                {
                                    tempImage[0] = CVIPComRef.CVIPTool.Duplicate_Image(ref resultsImage);
                                    tempImage[1] = CVIPComRef.CVIPTool.Duplicate_Image(ref resultsImage);
                                    tempImage[2] = CVIPComRef.CVIPTool.Duplicate_Image(ref resultsImage);
                                    CVIPComRef.CVIPTool.Delete_Image(ref resultsImage);
                                    resultsImage = CVIPComRef.CVIPTool.Assemble_Bands(tempImage);
                                    CVIPComRef.CVIPTool.Delete_Image(ref tempImage[0]);
                                    CVIPComRef.CVIPTool.Delete_Image(ref tempImage[1]);
                                    CVIPComRef.CVIPTool.Delete_Image(ref tempImage[2]);
                                }
                                if (!errorCode.Contains("3"))
                                {
                                    errorCode += "3";
                                }
                            }
                            //Checks if bands are the same
                            if (idealBand != band)
                            {
                                //Converts three bands to one.
                                if (band == 1)
                                {
                                    tempImage[0] = CVIPComRef.CVIPTool.Luminance_Image(ref idealImage);
                                    CVIPComRef.CVIPTool.Delete_Image(ref idealImage);
                                    idealImage = tempImage[0];
                                }
                                //Converts one band to three
                                else
                                {
                                    tempImage[0] = CVIPComRef.CVIPTool.Duplicate_Image(ref idealImage);
                                    tempImage[1] = CVIPComRef.CVIPTool.Duplicate_Image(ref idealImage);
                                    tempImage[2] = CVIPComRef.CVIPTool.Duplicate_Image(ref idealImage);
                                    CVIPComRef.CVIPTool.Delete_Image(ref idealImage);
                                    idealImage = CVIPComRef.CVIPTool.Assemble_Bands(tempImage);
                                    CVIPComRef.CVIPTool.Delete_Image(ref tempImage[0]);
                                    CVIPComRef.CVIPTool.Delete_Image(ref tempImage[1]);
                                    CVIPComRef.CVIPTool.Delete_Image(ref tempImage[2]);
                                }
                                if (!errorCode.Contains("3"))
                                {
                                    errorCode += "3";
                                }
                            }

                            columnOfArray = 0;
                            //RMS Enabled
                            if (errorCheck[0] == 1)
                            {
                                funcResults = performSingleFunction(ref resultsImage, ref idealImage, 0);
                                if (band == 1)
                                    allValues[fileNumber, columnOfArray] = funcResults[0];
                                else
                                {
                                    allValues[fileNumber, columnOfArray] = funcResults[0];
                                    allValues[fileNumber, columnOfArray + 1] = funcResults[1];
                                    allValues[fileNumber, columnOfArray + 2] = funcResults[2];
                                }
                                columnOfArray += band;
                            }
                            //SNR Enabled
                            if (errorCheck[1] == 1)
                            {
                                funcResults = performSingleFunction(ref resultsImage, ref idealImage, 1);
                                if (band == 1)
                                    allValues[fileNumber, columnOfArray] = funcResults[0];
                                else
                                {
                                    allValues[fileNumber, columnOfArray] = funcResults[0];
                                    allValues[fileNumber, columnOfArray + 1] = funcResults[1];
                                    allValues[fileNumber, columnOfArray + 2] = funcResults[2];
                                }
                                columnOfArray += band;
                            }
                            //SUB Enabled
                            if (errorCheck[2] == 1)
                            {
                                tImage = CVIPComRef.CVIPTool.Duplicate_Image(ref resultsImage);
                                iImage = CVIPComRef.CVIPTool.Duplicate_Image(ref idealImage);
                                funcResults = performSUB(ref tImage, ref iImage);
                                CVIPComRef.CVIPTool.Delete_Image(ref tImage);
                                CVIPComRef.CVIPTool.Delete_Image(ref iImage);
                                if (band == 1)
                                    allValues[fileNumber, columnOfArray] = funcResults[3];
                                else
                                {
                                    allValues[fileNumber, columnOfArray] = funcResults[3];
                                    allValues[fileNumber, columnOfArray + 1] = funcResults[8];
                                    allValues[fileNumber, columnOfArray + 2] = funcResults[13];
                                }
                                columnOfArray += band;
                            }
                            //DICE Enabled
                            if (errorCheck[3] == 1)
                            {
                                funcResults = performSingleFunction(ref resultsImage, ref idealImage, 3);
                                if (band == 1)
                                    allValues[fileNumber, columnOfArray] = funcResults[0];
                                else
                                {
                                    allValues[fileNumber, columnOfArray] = funcResults[0];
                                    allValues[fileNumber, columnOfArray + 1] = funcResults[1];
                                    allValues[fileNumber, columnOfArray + 2] = funcResults[2];
                                }
                                columnOfArray += band;
                            }
                            //Jaccard Enabled
                            if (errorCheck[4] == 1)
                            {
                                funcResults = performSingleFunction(ref resultsImage, ref idealImage, 4);
                                if (band == 1)
                                    allValues[fileNumber, columnOfArray] = funcResults[0];
                                else
                                {
                                    allValues[fileNumber, columnOfArray] = funcResults[0];
                                    allValues[fileNumber, columnOfArray + 1] = funcResults[1];
                                    allValues[fileNumber, columnOfArray + 2] = funcResults[2];
                                }
                                columnOfArray += band;
                            }
                            //Overlap Enabled
                            if (errorCheck[5] == 1)
                            {
                                funcResults = performSingleFunction(ref resultsImage, ref idealImage, 5);
                                if (band == 1)
                                    allValues[fileNumber, columnOfArray] = funcResults[0];
                                else
                                {
                                    allValues[fileNumber, columnOfArray] = funcResults[0];
                                    allValues[fileNumber, columnOfArray + 1] = funcResults[1];
                                    allValues[fileNumber, columnOfArray + 2] = funcResults[2];
                                }
                                columnOfArray += band;
                            }
                            //XOR Enabled
                            if (errorCheck[6] == 1)
                            {
                                tImage = CVIPComRef.CVIPTool.Duplicate_Image(ref resultsImage);
                                iImage = CVIPComRef.CVIPTool.Duplicate_Image(ref idealImage);
                                funcResults = performXOR(ref tImage, ref iImage);
                                CVIPComRef.CVIPTool.Delete_Image(ref tImage);
                                CVIPComRef.CVIPTool.Delete_Image(ref iImage);
                                if (band == 1)
                                    allValues[fileNumber, columnOfArray] = funcResults[0];
                                else
                                {
                                    allValues[fileNumber, columnOfArray] = funcResults[0];
                                    allValues[fileNumber, columnOfArray + 1] = funcResults[1];
                                    allValues[fileNumber, columnOfArray + 2] = funcResults[2];
                                }
                                columnOfArray += band;
                            }
                        }//Size Check End
                        else
                        {
                            //Used for displaying xS's in the results
                            allValues[fileNumber, 0] = -1000;
                            if (!errorCode.Contains("1"))
                            {
                                errorCode += "1";
                            }
                        }

                        //Delete images
                        CVIPComRef.CVIPTool.Delete_Image(ref resultsImage);
                    }
                    catch
                    {
                        //Used for displaying xN's in the results
                        allValues[fileNumber, 0] = -2000;
                        if (errorCode.Contains("2"))
                        {
                            errorCode += "2";
                        }
                    }
                    //Updates Progress Bar
                    progress = (int)(minProgress + (double)minProgress * ((double)fileNumber / (double)results.Length));
                }//Image Loop End
                try
                {
                    for (int i = 0; i < ideal.Length; i++)
                        CVIPComRef.CVIPTool.Delete_Image(ref idealArray[i]);
                }
                catch { }
                try
                {
                    //Write results.
                    writeResultsFile();
                    //Calculate averages and/or standard deviation.
                    if (average == true || stdDev == true)
                    {
                        writeAlgorithmFile(algList);
                    }
                }
                catch
                {
                    MessageBox.Show("Comparison crashed while creating output files", "Output process crash!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                displayErrorMessage();
            }//Compare Calculations End
            else
            {
                MessageBox.Show("No Output Directory", "Error: No Output Directory!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            //Final Progress Update (Progress = 100%)
            progress = minProgress * 2;
            //Garbage Collection
            GC.Collect();
        }//Compare Process End

        //Determines maximum band size.
        private void bandTest(string[] rFolder)
        {
            int image;
            for (int i = 0; i < rFolder.Length; i++)
            {
                image = CVIPComRef.CVIPTool.Read_Image(ref rFolder[i]);
                if (image != 0)
                {
                    if (CVIPComRef.CVIPTool.GetNoOfBands_Image(image) != 1)
                    {
                        band = 3;
                        break;
                    }
                    CVIPComRef.CVIPTool.Delete_Image(ref image);
                }
            }
        }

        //Creates the output csv files.
        private void createOrDeleteOutputFiles(int band)
        {
            string imgFileName = CVIPComRef.CVIP_projectPath + "//Image Results.csv";
            string algFileName = CVIPComRef.CVIP_projectPath + "//Algorithm Results.csv";
            string imgLine = "Results,Algorithm";

            arraySize = 0;

            //Write Images Results File
            if (File.Exists(imgFileName))
                File.Delete(imgFileName);
            using (StreamWriter csvFile = new StreamWriter(imgFileName))
            {
                for (int metric = 0; metric < 7; metric++)
                {
                    if (errorCheck[metric] == 1)
                    {
                        imgLine += "," + metrics[metric] + "R, T/F";
                        if (band == 3)
                        {
                            imgLine += "," + metrics[metric] + "G, T/F";
                            imgLine += "," + metrics[metric] + "B, T/F";
                        }
                        arraySize += band;
                    }
                }
                csvFile.WriteLine(imgLine);
            }

            //Write Algorithm Results File
            if (average == true || stdDev == true)
            {
                imgLine = "Algorithm";
                if (File.Exists(algFileName))
                    File.Delete(algFileName);
                using (StreamWriter csvFile = new StreamWriter(algFileName))
                {
                    if (average == true)
                    {
                        for (int metric = 0; metric < 7; metric++)
                        {
                            if (errorCheck[metric] == 1)
                            {
                                if (band == 1)
                                    imgLine += "," + metrics[metric] + "Avg";
                                else
                                {
                                    imgLine += "," + metrics[metric] + "R Avg";
                                    imgLine += "," + metrics[metric] + "G Avg";
                                    imgLine += "," + metrics[metric] + "B Avg";
                                }
                            }
                        }
                    }
                    if (stdDev == true)
                    {
                        for (int metric = 0; metric < 7; metric++)
                        {
                            if (errorCheck[metric] == 1)
                            {
                                if (band == 1)
                                    imgLine += "," + metrics[metric] + "StdDev";
                                else
                                {
                                    imgLine += "," + metrics[metric] + "R StdDev";
                                    imgLine += "," + metrics[metric] + "G StdDev";
                                    imgLine += "," + metrics[metric] + "B StdDev";
                                }
                            }
                        }
                    }
                    csvFile.WriteLine(imgLine);
                }
            }
        }

        //Returns the RMS, SNR, DICE, JACCARD, or OVERLAP results.
        private double[] performSingleFunction(ref int resultImage, ref int idealImage, int errorIndex)
        {
            object fRMSValue;
            int tempImage;
            float[] temp_float;
            double[] resultsRMS = new double[10];
            tImage = CVIPComRef.CVIPTool.Duplicate_Image(ref resultImage);
            iImage = CVIPComRef.CVIPTool.Duplicate_Image(ref idealImage);
            switch (errorIndex)
            {
                case 0:
                    fRMSValue = CVIPComRef.CVIPTool.Rms_Error(ref tImage, ref iImage);
                    //Converts fRMSValue to float and then to double.
                    temp_float = (float[])fRMSValue;
                    for (int s = 0; s < temp_float.Length; s++)
                    {
                        resultsRMS[s] = temp_float[s];
                    }
                    break;
                case 1:
                    fRMSValue = CVIPComRef.CVIPTool.Snr(ref tImage, ref iImage);
                    //Converts fRMSValue to float and then to double.
                    temp_float = (float[])fRMSValue;
                    for (int s = 0; s < temp_float.Length; s++)
                    {
                        resultsRMS[s] = temp_float[s];
                    }
                    break;
                case 3:
                    tempImage = CVIPComRef.CVIPTool.Remap_Image(ref tImage, (int)dataType.CVIP_BYTE, 0, 255);
                    CVIPComRef.CVIPTool.Delete_Image(ref tImage);
                    tImage = tempImage;
                    tempImage = CVIPComRef.CVIPTool.Remap_Image(ref iImage, (int)dataType.CVIP_BYTE, 0, 255);
                    CVIPComRef.CVIPTool.Delete_Image(ref iImage);
                    iImage = tempImage;
                    resultsRMS = CVIPComRef.CVIPTool.Dice_Coef(ref tImage, ref iImage);
                    break;
                case 4:
                    tempImage = CVIPComRef.CVIPTool.Remap_Image(ref tImage, (int)dataType.CVIP_BYTE, 0, 255);
                    CVIPComRef.CVIPTool.Delete_Image(ref tImage);
                    tImage = tempImage;
                    tempImage = CVIPComRef.CVIPTool.Remap_Image(ref iImage, (int)dataType.CVIP_BYTE, 0, 255);
                    CVIPComRef.CVIPTool.Delete_Image(ref iImage);
                    iImage = tempImage;
                    resultsRMS = CVIPComRef.CVIPTool.Jaccard_Index(ref tImage, ref iImage);
                    break;
                case 5:
                    tempImage = CVIPComRef.CVIPTool.Remap_Image(ref tImage, (int)dataType.CVIP_BYTE, 0, 255);
                    CVIPComRef.CVIPTool.Delete_Image(ref tImage);
                    tImage = tempImage;
                    tempImage = CVIPComRef.CVIPTool.Remap_Image(ref iImage, (int)dataType.CVIP_BYTE, 0, 255);
                    CVIPComRef.CVIPTool.Delete_Image(ref iImage);
                    iImage = tempImage;
                    resultsRMS = CVIPComRef.CVIPTool.Overlap_Coef(ref tImage, ref iImage);
                    break;
                default:
                    resultsRMS = null;
                    break;
            }
            CVIPComRef.CVIPTool.Delete_Image(ref tImage);
            CVIPComRef.CVIPTool.Delete_Image(ref iImage);
            return resultsRMS;
        }

        //Returns the Subtraction value of the images.
        private double[] performSUB(ref int testImage, ref int idealImage)
        {
            double[] resultsSUB = new double[20]; // results for subtraction 3 bands * 5 hist features maximum.
            int NoOfRows, NoOfCols;
            int CVIPResultImage, CVIPTempImage, tempImage;
            object HistFeature;

            //Ideal image has more bands than test image.
            CVIPResultImage = CVIPComRef.CVIPTool.Subtract_Image(ref testImage, ref idealImage);

            tempImage = CVIPComRef.CVIPTool.Remap_Image(ref CVIPResultImage, (int)dataType.CVIP_BYTE, 0, 255);
            CVIPComRef.CVIPTool.Delete_Image(ref CVIPResultImage);
            CVIPResultImage = tempImage;

            NoOfCols = CVIPComRef.CVIPTool.GetNoOfCols_Image(ref CVIPResultImage);
            NoOfRows = CVIPComRef.CVIPTool.GetNoOfRows_Image(ref CVIPResultImage);

            //create a labeled image(white integer image)   
            //i am not sure it is right to use new_image() to create a labed image instead of lable();
            //maybe right, since it takes the whole new image as a labled image
            //parameters:  imageFormat, colorFormat, imageBands, imageHeight, imageWidth, dataType, dataFormat
            CVIPTempImage = CVIPComRef.CVIPTool.New_Image((int)imageFormat.VIP, (int)colorFormat.GRAY_SCALE, 1, NoOfRows, NoOfCols, (int)dataType.CVIP_INTEGER, (int)dataFormat.REAL);

            //the return  contains "mean, standard deviation, skew, energy and entropy" histogram features of each band. 
            //If the original image is a color image, the first five values are for band 0,
            //the next five data are for band 1, and so on.
            HistFeature = CVIPComRef.CVIPTool.Hist_Feature(ref CVIPResultImage, ref CVIPTempImage, 0, 0);
            resultsSUB = (double[])HistFeature;

            //delete image
            //neednot delete CVIPImage and CVIPIdealImage since subtract() will delete them
            CVIPComRef.CVIPTool.Delete_Image(ref CVIPResultImage);
            CVIPComRef.CVIPTool.Delete_Image(ref CVIPTempImage);

            return resultsSUB;
        }

        //Returns the XOR value of the images.
        private double[] performXOR(ref int testImage, ref int idealImage)
        {
            double[] fXORValue = new double[3];
            int tempImage, tempIdealImage;
            tempImage = CVIPComRef.CVIPTool.Remap_Image(ref testImage, (int)dataType.CVIP_BYTE, 0, 255);
            CVIPComRef.CVIPTool.Delete_Image(ref testImage);
            testImage = tempImage;
            tempIdealImage = CVIPComRef.CVIPTool.Remap_Image(ref idealImage, (int)dataType.CVIP_BYTE, 0, 255);
            CVIPComRef.CVIPTool.Delete_Image(ref idealImage);
            idealImage = tempIdealImage;

            tempImage = CVIPComRef.CVIPTool.Threshold_Segment(ref testImage, xorThresh, (int)threshInByte.CVIP_NO);
            CVIPComRef.CVIPTool.Delete_Image(ref testImage);
            testImage = tempImage;
            tempIdealImage = CVIPComRef.CVIPTool.Threshold_Segment(ref idealImage, xorThresh, (int)threshInByte.CVIP_NO);
            CVIPComRef.CVIPTool.Delete_Image(ref idealImage);
            idealImage = tempIdealImage;

            fXORValue = (double[])CVIPComRef.CVIPTool.Xor_Error(ref idealImage, ref testImage);

            CVIPComRef.CVIPTool.Delete_Image(ref tempIdealImage);
            CVIPComRef.CVIPTool.Delete_Image(ref tempImage);
            return fXORValue;
        }

        //Writes the results file.
        private void writeResultsFile()
        {
            string imgFileName = CVIPComRef.CVIP_projectPath + "//Image Results.csv";
            string[] imgLine = new string[2 + (arraySize * 2)];
            int arrayIndex, index;
            GC.Collect();
            using (StreamWriter csvFile = new StreamWriter(imgFileName, true))
            {
                for (int imageNumber = 0; imageNumber < results.Length; imageNumber++)
                {
                    mainThreadCTL.WaitOne();
                    arrayIndex = 0;
                    imgLine[0] = "\"" + Path.GetFileName(results[imageNumber]) + "\"";
                    imgLine[1] = "\"" + algorithms[imageNumber] + "\"";
                    index = 2;
                    if (allValues[imageNumber, 0] == -1000)
                    {
                        for (int wrongSize = 0; wrongSize < arraySize * 2; wrongSize++)
                            imgLine[wrongSize + 2] = "xS";
                    }
                    else if (allValues[imageNumber, 0] == -2000)
                    {
                        for (int wrongSize = 0; wrongSize < arraySize * 2; wrongSize++)
                            imgLine[wrongSize + 2] = "xN";
                    }
                    else
                    {
                        arrayIndex = 0;
                        for (int column = 0; column < errorValues.Length; column++)
                        {
                            if (errorValues[column] != -1000)
                            {
                                if (allValues[imageNumber, arrayIndex] < 0) //SNR Infinity Check
                                    imgLine[index] = "Inf";
                                else
                                    imgLine[index] = allValues[imageNumber, arrayIndex].ToString();
                                if (column >= 3 && column <= 17)
                                {
                                    if (allValues[imageNumber, arrayIndex] >= errorValues[column] || imgLine[index] == "Inf")
                                        imgLine[index + 1] = "true";
                                    else
                                        imgLine[index + 1] = "false";
                                }
                                else
                                {
                                    if (allValues[imageNumber, arrayIndex] <= errorValues[column] || imgLine[index] == "Inf")
                                        imgLine[index + 1] = "true";
                                    else
                                        imgLine[index + 1] = "false";
                                }
                                index += 2;
                                arrayIndex++;
                                if (band == 1)
                                    column += 2;
                            }
                        }
                        csvFile.WriteLine(string.Join(",", imgLine));
                    }
                }
            }
        }

        //Writes the algorithm file.
        private void writeAlgorithmFile(List<string> algList)
        {
            string algFileName = CVIPComRef.CVIP_projectPath + "//Algorithm Results.csv";
            string imgLine;
            int algorithmIndex, valueIndex;
            double value;

            double[] averageArray = new double[arraySize];
            int[] imageCount = new int[arraySize];

            using (StreamWriter csvFile = new StreamWriter(algFileName, true))
            {
                for (int algNumber = 0; algNumber < algList.Count; algNumber++)
                {
                    mainThreadCTL.WaitOne();
                    imgLine = "\"" + algList[algNumber] + "\"";

                    //Calculate the Averages
                    for (valueIndex = 0; valueIndex < arraySize/* / band*/; valueIndex++)
                    {
                        imageCount[valueIndex] = 0;
                        averageArray[valueIndex] = 0;
                        for (int fileNumber = 0; fileNumber < results.Length; fileNumber++)
                        {
                            //If the images were successful:
                            if (allValues[fileNumber, 0] != -1000 && allValues[fileNumber, 0] != -2000)
                            {
                                algorithmIndex = algList.IndexOf(algorithms[fileNumber]);
                                if (algorithmIndex == algNumber)
                                {
                                    averageArray[valueIndex] += allValues[fileNumber, valueIndex];
                                    imageCount[valueIndex]++;
                                }
                            }
                        }
                        imgLine += "," + (averageArray[valueIndex] / (double)imageCount[valueIndex]).ToString();
                    }
                    //Print Standard Deviation Results
                    if (stdDev == true)
                    {
                        for (valueIndex = 0; valueIndex < arraySize/* / band*/; valueIndex++)
                        {
                            double total = 0;
                            for (int fileNumber = 0; fileNumber < results.Length; fileNumber++)
                            {
                                //If the images were successful:
                                if (allValues[fileNumber, 0] != -1000 && allValues[fileNumber, 0] != -2000)
                                {
                                    algorithmIndex = algList.IndexOf(algorithms[fileNumber]);
                                    if (algorithmIndex == algNumber)
                                    {
                                        total += Math.Pow(allValues[fileNumber, valueIndex] - (averageArray[valueIndex] / (double)imageCount[valueIndex]), 2);
                                    }
                                }
                            }
                            value = Math.Sqrt(total / (double)imageCount[valueIndex]);
                            imgLine += "," + value.ToString();
                        }
                    }
                    csvFile.WriteLine(imgLine);
                }//Algorithm Loop End
            }
        }//writeAlgorithmFile Function End

        //Alerts user of errors
        private void displayErrorMessage()
        {
            string errorMessage = "";
            string errorType = "Comparison Errors/Warnings";
            if (errorCode != "0")
            {
                if (errorCode.Contains("1"))
                    errorMessage += "ErrorCode 1: Different Sized Images Found. Images with different sizes will be marked with xS's in the results sheet\n\n";
                if (errorCode.Contains("2"))
                    errorMessage += "ErrorCode 2: Images Caused Crash. Crashed images will be marked with xN's in the results sheet\n\n";
                if (errorCode.Contains("3"))
                    errorMessage += "ErrorCode 3: Different Band Numbers Identified. All images converted to max ideal band number: " + band.ToString() + "\n\n";
                MessageBox.Show(errorMessage, errorType, MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
    }
}

