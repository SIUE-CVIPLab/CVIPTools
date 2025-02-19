namespace CVIPGUI
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.dlgFileOpen = new System.Windows.Forms.OpenFileDialog();
            this.dlgFileSave = new System.Windows.Forms.SaveFileDialog();
            this.mnuCVIP = new System.Windows.Forms.MenuStrip();
            this.mnuFile = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileHistogram = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileSpectrum = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileFFTPhase = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileFFTMagnitude = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileLogRemapped = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileLogRemapAll = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileLogRemapRed = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileLogRemapGreen = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileLogRemapBlue = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileViewBand = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileViewRedBand = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileViewGreenBand = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileViewBlueBand = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileSep1 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuFileOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileSep2 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuFileSave = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileSep3 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuFilePrint = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileSep4 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuFileExit = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuView = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewToolbar = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewImageQueue = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewInfoPanel = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewStatusBar = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuLongFileNames = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewSep1 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuViewHistogram = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewSpectrum = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewFFTPhase = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewFFTMagnitude = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewLogRemapped = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewLogRemapAll = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewLogRemapRed = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewLogRemapGreen = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewLogRemapBlue = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewBand = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewBandRed = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewBandGreen = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuViewBandBlue = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuAnalysis = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuAnalysisPreprocessing = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuAnalysisGeometry = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuAnalysisEdgeDetect = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuAnalysisSegment = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuAnalysisTransforms = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuAnalysisFeatures = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuAnalysisClassify = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuEnhancement = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuEnhanceHistograms = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuEnhancePseudocolor = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuEnhanceSharpen = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuEnhanceSmooth = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuRestoration = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuRestoreNoise = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuRestoreSpatialFilters = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuRestoreFreqFilters = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuRestoreGeoTransforms = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuCompression = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuCompressPreprocess = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuCompressLossless = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuCompressLossy = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuCompressPostprocess = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuShowUtilities = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilArithLogic = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilADD = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilSUB = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilMUL = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilDIV = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilArithSep1 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuUtilAND = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilNOT = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilOR = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilXOR = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilCompare = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilCompareImages = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilCompareError = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilPrattMerit = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilConvert = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilBinThreshold = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilDataType = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilHalftone = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilGrayLevelQuant = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilGrayToBinary = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilGrayToColor = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilColorToGray = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilColorSpace = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilLabelImage = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilCreate = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilCheckerboard = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilCircle = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilEllipse = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilLine = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilRectangle = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilCreateSep1 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuUtilCosineWave = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilSineWave = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilSquareWave = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilCreateSep2 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuUtilExtractBand = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilAssembleBands = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilCreateSep3 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuUtilBlackImage = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilAddNoise = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilCreateSep4 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuUtilBorderMask = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilBorderImage = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilEnhance = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilBrightenDarken = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilEdgeEnhancement = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilHistogramEQ = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilHistoStretch = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilPseudocolor = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilSharpen = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilFilter = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilMean = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilMedian = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilLaplacian = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilEmbossFilter = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilFiltSep1 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuUtilSpecifyFilter = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilSpecifyBlur = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilSize = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilCrop = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilDoubleSize = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilResize = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilSpatialQuant = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilStats = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilImageDataRange = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuUtilImageStatistics = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuHelpContents = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuHelpSep1 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuHelpAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuCVIPtoolsWeblink = new System.Windows.Forms.ToolStripMenuItem();
            this.pnlInfo = new CVIPGUI.InfoPanel();
            this.pnlQueue = new CVIPGUI.ImageQueue();
            this.popmnuUtilities = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.popmnuUtilArithLogic = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilADD = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilSUB = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilMUL = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilDIV = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.popmnuUtilAND = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilNOT = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilOR = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilXOR = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilCompare = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilCompareImages = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilPrattMerit = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilConvert = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilBinThreshold = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilDataType = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilHalftone = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilGrayLevelQuant = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilGrayToBinary = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilGrayToColor = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilColorToGray = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilColorSpace = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilLabelImage = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilCreate = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilCheckerboard = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilCircle = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilEllipse = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilLine = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilRectangle = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.popmnuUtilCosineWave = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilSineWave = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilSquareWave = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.popmnuUtilExtractBand = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilAssembleBands = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.popmnuUtilBlackImage = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilAddNoise = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.popmnuUtilBorderMask = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilBorderImage = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilEnhance = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilBrightenDarken = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilEdgeEnhancement = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilHistogramEQ = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilHistoStretch = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilPseudocolor = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilSharpen = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilFilter = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilMean = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilMedian = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilLaplacian = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilEmbossFilter = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator6 = new System.Windows.Forms.ToolStripSeparator();
            this.popmnuUtilSpecifyFilter = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilSpecifyBlur = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilSize = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilCrop = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilDoubleSize = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilResize = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilSpatialQuant = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilStats = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilImageDataRange = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuUtilImageStatistics = new System.Windows.Forms.ToolStripMenuItem();
            this.statbarCVIP = new System.Windows.Forms.StatusStrip();
            this.statbarFileName = new CVIPGUI.NonBlinkingStatusLabel();
            this.statbarColorFormat = new CVIPGUI.NonBlinkingStatusLabel();
            this.statbarImageFormat = new CVIPGUI.NonBlinkingStatusLabel();
            this.statbarDataFormat = new CVIPGUI.NonBlinkingStatusLabel();
            this.statbarDataType = new CVIPGUI.NonBlinkingStatusLabel();
            this.statbarDataRMin = new CVIPGUI.NonBlinkingStatusLabel();
            this.statbarDataRMax = new CVIPGUI.NonBlinkingStatusLabel();
            this.statbarBands = new CVIPGUI.NonBlinkingStatusLabel();
            this.statbarWidth = new CVIPGUI.NonBlinkingStatusLabel();
            this.statbarHeight = new CVIPGUI.NonBlinkingStatusLabel();
            this.toolbarCVIP = new System.Windows.Forms.ToolStrip();
            this.tbOpen = new System.Windows.Forms.ToolStripButton();
            this.tbSave = new System.Windows.Forms.ToolStripButton();
            this.tbPrint = new System.Windows.Forms.ToolStripButton();
            this.tbSep1 = new System.Windows.Forms.ToolStripLabel();
            this.tbCamera = new System.Windows.Forms.ToolStripButton();
            this.tbHistogram = new System.Windows.Forms.ToolStripButton();
            this.tbSep2 = new System.Windows.Forms.ToolStripLabel();
            this.tbRedBand = new System.Windows.Forms.ToolStripButton();
            this.tbGreenBand = new System.Windows.Forms.ToolStripButton();
            this.tbBlueBand = new System.Windows.Forms.ToolStripButton();
            this.tbSep3 = new System.Windows.Forms.ToolStripLabel();
            this.tbColLabel = new System.Windows.Forms.ToolStripLabel();
            this.tbColValue = new System.Windows.Forms.ToolStripLabel();
            this.tbRowLabel = new System.Windows.Forms.ToolStripLabel();
            this.tbRowValue = new System.Windows.Forms.ToolStripLabel();
            this.tbSep4 = new System.Windows.Forms.ToolStripLabel();
            this.tbRLabel = new System.Windows.Forms.ToolStripLabel();
            this.tbRValue = new System.Windows.Forms.ToolStripLabel();
            this.tbGLabel = new System.Windows.Forms.ToolStripLabel();
            this.tbGValue = new System.Windows.Forms.ToolStripLabel();
            this.tbBLabel = new System.Windows.Forms.ToolStripLabel();
            this.tbBValue = new System.Windows.Forms.ToolStripLabel();
            this.tbFEPC = new System.Windows.Forms.ToolStripButton();
            this.tbATAT = new System.Windows.Forms.ToolStripButton();
            this.mnuCVIP.SuspendLayout();
            this.popmnuUtilities.SuspendLayout();
            this.statbarCVIP.SuspendLayout();
            this.toolbarCVIP.SuspendLayout();
            this.SuspendLayout();
            // 
            // dlgFileOpen
            // 
            this.dlgFileOpen.Filter = resources.GetString("dlgFileOpen.Filter");
            this.dlgFileOpen.Multiselect = true;
            this.dlgFileOpen.Title = "Select files to open";
            // 
            // dlgFileSave
            // 
            this.dlgFileSave.Filter = resources.GetString("dlgFileSave.Filter");
            this.dlgFileSave.OverwritePrompt = false;
            this.dlgFileSave.Title = "Save as";
            this.dlgFileSave.FileOk += new System.ComponentModel.CancelEventHandler(this.dlgFileSave_FileOk);
            // 
            // mnuCVIP
            // 
            this.mnuCVIP.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.mnuCVIP.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuFile,
            this.mnuView,
            this.mnuAnalysis,
            this.mnuEnhancement,
            this.mnuRestoration,
            this.mnuCompression,
            this.mnuShowUtilities,
            this.mnuUtilArithLogic,
            this.mnuUtilCompare,
            this.mnuUtilConvert,
            this.mnuUtilCreate,
            this.mnuUtilEnhance,
            this.mnuUtilFilter,
            this.mnuUtilSize,
            this.mnuUtilStats,
            this.mnuHelp,
            this.mnuCVIPtoolsWeblink});
            this.mnuCVIP.Location = new System.Drawing.Point(0, 0);
            this.mnuCVIP.Name = "mnuCVIP";
            this.mnuCVIP.Padding = new System.Windows.Forms.Padding(0, 2, 0, 2);
            this.mnuCVIP.Size = new System.Drawing.Size(953, 24);
            this.mnuCVIP.TabIndex = 1;
            this.mnuCVIP.MouseLeave += new System.EventHandler(this.mnuCVIPtoolsWeblink_MouseLeave);
            // 
            // mnuFile
            // 
            this.mnuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuFileHistogram,
            this.mnuFileSpectrum,
            this.mnuFileViewBand,
            this.mnuFileSep1,
            this.mnuFileOpen,
            this.mnuFileSep2,
            this.mnuFileSave,
            this.mnuFileSep3,
            this.mnuFilePrint,
            this.mnuFileSep4,
            this.mnuFileExit});
            this.mnuFile.Name = "mnuFile";
            this.mnuFile.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.mnuFile.Size = new System.Drawing.Size(33, 20);
            this.mnuFile.Text = "&File";
            // 
            // mnuFileHistogram
            // 
            this.mnuFileHistogram.Enabled = false;
            this.mnuFileHistogram.Image = ((System.Drawing.Image)(resources.GetObject("mnuFileHistogram.Image")));
            this.mnuFileHistogram.ImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(212)))), ((int)(((byte)(234)))), ((int)(((byte)(252)))));
            this.mnuFileHistogram.Name = "mnuFileHistogram";
            this.mnuFileHistogram.Size = new System.Drawing.Size(162, 22);
            this.mnuFileHistogram.Text = "Show Histogram";
            this.mnuFileHistogram.Click += new System.EventHandler(this.mnuFileHistogram_Click);
            // 
            // mnuFileSpectrum
            // 
            this.mnuFileSpectrum.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuFileFFTPhase,
            this.mnuFileFFTMagnitude,
            this.mnuFileLogRemapped});
            this.mnuFileSpectrum.Name = "mnuFileSpectrum";
            this.mnuFileSpectrum.Size = new System.Drawing.Size(162, 22);
            this.mnuFileSpectrum.Text = "Show Spectrum";
            // 
            // mnuFileFFTPhase
            // 
            this.mnuFileFFTPhase.Enabled = false;
            this.mnuFileFFTPhase.Name = "mnuFileFFTPhase";
            this.mnuFileFFTPhase.Size = new System.Drawing.Size(153, 22);
            this.mnuFileFFTPhase.Text = "FFT Phase";
            this.mnuFileFFTPhase.Click += new System.EventHandler(this.mnuFFTPhase_Click);
            // 
            // mnuFileFFTMagnitude
            // 
            this.mnuFileFFTMagnitude.Enabled = false;
            this.mnuFileFFTMagnitude.Name = "mnuFileFFTMagnitude";
            this.mnuFileFFTMagnitude.Size = new System.Drawing.Size(153, 22);
            this.mnuFileFFTMagnitude.Text = "Magnitude";
            this.mnuFileFFTMagnitude.Click += new System.EventHandler(this.mnuFFTMagnitude_Click);
            // 
            // mnuFileLogRemapped
            // 
            this.mnuFileLogRemapped.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuFileLogRemapAll,
            this.mnuFileLogRemapRed,
            this.mnuFileLogRemapGreen,
            this.mnuFileLogRemapBlue});
            this.mnuFileLogRemapped.Name = "mnuFileLogRemapped";
            this.mnuFileLogRemapped.Size = new System.Drawing.Size(153, 22);
            this.mnuFileLogRemapped.Text = "Log-remapped";
            // 
            // mnuFileLogRemapAll
            // 
            this.mnuFileLogRemapAll.Enabled = false;
            this.mnuFileLogRemapAll.Name = "mnuFileLogRemapAll";
            this.mnuFileLogRemapAll.Size = new System.Drawing.Size(135, 22);
            this.mnuFileLogRemapAll.Tag = CVIPGUI.LogRemap.All;
            this.mnuFileLogRemapAll.Text = "All Bands";
            this.mnuFileLogRemapAll.Click += new System.EventHandler(this.mnuLogRemap_Click);
            // 
            // mnuFileLogRemapRed
            // 
            this.mnuFileLogRemapRed.Enabled = false;
            this.mnuFileLogRemapRed.Name = "mnuFileLogRemapRed";
            this.mnuFileLogRemapRed.Size = new System.Drawing.Size(135, 22);
            this.mnuFileLogRemapRed.Tag = CVIPGUI.LogRemap.Red;
            this.mnuFileLogRemapRed.Text = "Red Band";
            this.mnuFileLogRemapRed.Click += new System.EventHandler(this.mnuLogRemap_Click);
            // 
            // mnuFileLogRemapGreen
            // 
            this.mnuFileLogRemapGreen.Enabled = false;
            this.mnuFileLogRemapGreen.Name = "mnuFileLogRemapGreen";
            this.mnuFileLogRemapGreen.Size = new System.Drawing.Size(135, 22);
            this.mnuFileLogRemapGreen.Tag = CVIPGUI.LogRemap.Green;
            this.mnuFileLogRemapGreen.Text = "Green Band";
            this.mnuFileLogRemapGreen.Click += new System.EventHandler(this.mnuLogRemap_Click);
            // 
            // mnuFileLogRemapBlue
            // 
            this.mnuFileLogRemapBlue.Enabled = false;
            this.mnuFileLogRemapBlue.Name = "mnuFileLogRemapBlue";
            this.mnuFileLogRemapBlue.Size = new System.Drawing.Size(135, 22);
            this.mnuFileLogRemapBlue.Tag = CVIPGUI.LogRemap.Blue;
            this.mnuFileLogRemapBlue.Text = "Blue Band";
            this.mnuFileLogRemapBlue.Click += new System.EventHandler(this.mnuLogRemap_Click);
            // 
            // mnuFileViewBand
            // 
            this.mnuFileViewBand.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuFileViewRedBand,
            this.mnuFileViewGreenBand,
            this.mnuFileViewBlueBand});
            this.mnuFileViewBand.Name = "mnuFileViewBand";
            this.mnuFileViewBand.Size = new System.Drawing.Size(162, 22);
            this.mnuFileViewBand.Text = "View Band";
            // 
            // mnuFileViewRedBand
            // 
            this.mnuFileViewRedBand.Enabled = false;
            this.mnuFileViewRedBand.Image = ((System.Drawing.Image)(resources.GetObject("mnuFileViewRedBand.Image")));
            this.mnuFileViewRedBand.ImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(234)))), ((int)(((byte)(220)))));
            this.mnuFileViewRedBand.Name = "mnuFileViewRedBand";
            this.mnuFileViewRedBand.Size = new System.Drawing.Size(105, 22);
            this.mnuFileViewRedBand.Tag = "0";
            this.mnuFileViewRedBand.Text = "Red";
            this.mnuFileViewRedBand.ToolTipText = "Show red band";
            this.mnuFileViewRedBand.Click += new System.EventHandler(this.mnuViewBand_Click);
            // 
            // mnuFileViewGreenBand
            // 
            this.mnuFileViewGreenBand.Enabled = false;
            this.mnuFileViewGreenBand.Image = ((System.Drawing.Image)(resources.GetObject("mnuFileViewGreenBand.Image")));
            this.mnuFileViewGreenBand.ImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(234)))), ((int)(((byte)(220)))));
            this.mnuFileViewGreenBand.Name = "mnuFileViewGreenBand";
            this.mnuFileViewGreenBand.Size = new System.Drawing.Size(105, 22);
            this.mnuFileViewGreenBand.Tag = "1";
            this.mnuFileViewGreenBand.Text = "Green";
            this.mnuFileViewGreenBand.ToolTipText = "Show green band";
            this.mnuFileViewGreenBand.Click += new System.EventHandler(this.mnuViewBand_Click);
            // 
            // mnuFileViewBlueBand
            // 
            this.mnuFileViewBlueBand.Enabled = false;
            this.mnuFileViewBlueBand.Image = ((System.Drawing.Image)(resources.GetObject("mnuFileViewBlueBand.Image")));
            this.mnuFileViewBlueBand.ImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(234)))), ((int)(((byte)(220)))));
            this.mnuFileViewBlueBand.Name = "mnuFileViewBlueBand";
            this.mnuFileViewBlueBand.Size = new System.Drawing.Size(105, 22);
            this.mnuFileViewBlueBand.Tag = "2";
            this.mnuFileViewBlueBand.Text = "Blue";
            this.mnuFileViewBlueBand.ToolTipText = "Show blue band";
            this.mnuFileViewBlueBand.Click += new System.EventHandler(this.mnuViewBand_Click);
            // 
            // mnuFileSep1
            // 
            this.mnuFileSep1.Name = "mnuFileSep1";
            this.mnuFileSep1.Size = new System.Drawing.Size(159, 6);
            // 
            // mnuFileOpen
            // 
            this.mnuFileOpen.Image = ((System.Drawing.Image)(resources.GetObject("mnuFileOpen.Image")));
            this.mnuFileOpen.ImageTransparentColor = System.Drawing.Color.Fuchsia;
            this.mnuFileOpen.Name = "mnuFileOpen";
            this.mnuFileOpen.ShortcutKeyDisplayString = "Ctrl+O";
            this.mnuFileOpen.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.mnuFileOpen.Size = new System.Drawing.Size(162, 22);
            this.mnuFileOpen.Text = "&Open...";
            this.mnuFileOpen.Click += new System.EventHandler(this.mnuFileOpen_Click);
            // 
            // mnuFileSep2
            // 
            this.mnuFileSep2.Name = "mnuFileSep2";
            this.mnuFileSep2.Size = new System.Drawing.Size(159, 6);
            // 
            // mnuFileSave
            // 
            this.mnuFileSave.Enabled = false;
            this.mnuFileSave.Image = ((System.Drawing.Image)(resources.GetObject("mnuFileSave.Image")));
            this.mnuFileSave.ImageTransparentColor = System.Drawing.Color.Fuchsia;
            this.mnuFileSave.Name = "mnuFileSave";
            this.mnuFileSave.ShortcutKeyDisplayString = "Ctrl+S";
            this.mnuFileSave.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.mnuFileSave.Size = new System.Drawing.Size(162, 22);
            this.mnuFileSave.Text = "&Save...";
            this.mnuFileSave.Click += new System.EventHandler(this.mnuFileSave_Click);
            // 
            // mnuFileSep3
            // 
            this.mnuFileSep3.Name = "mnuFileSep3";
            this.mnuFileSep3.Size = new System.Drawing.Size(159, 6);
            // 
            // mnuFilePrint
            // 
            this.mnuFilePrint.Enabled = false;
            this.mnuFilePrint.Image = ((System.Drawing.Image)(resources.GetObject("mnuFilePrint.Image")));
            this.mnuFilePrint.ImageTransparentColor = System.Drawing.Color.Fuchsia;
            this.mnuFilePrint.Name = "mnuFilePrint";
            this.mnuFilePrint.ShortcutKeyDisplayString = "Ctrl+P";
            this.mnuFilePrint.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.P)));
            this.mnuFilePrint.Size = new System.Drawing.Size(162, 22);
            this.mnuFilePrint.Text = "&Print...";
            this.mnuFilePrint.Click += new System.EventHandler(this.mnuFilePrint_Click);
            // 
            // mnuFileSep4
            // 
            this.mnuFileSep4.Name = "mnuFileSep4";
            this.mnuFileSep4.Size = new System.Drawing.Size(159, 6);
            // 
            // mnuFileExit
            // 
            this.mnuFileExit.Name = "mnuFileExit";
            this.mnuFileExit.Size = new System.Drawing.Size(162, 22);
            this.mnuFileExit.Text = "E&xit";
            this.mnuFileExit.Click += new System.EventHandler(this.mnuFileExit_Click);
            // 
            // mnuView
            // 
            this.mnuView.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuViewToolbar,
            this.mnuViewImageQueue,
            this.mnuViewInfoPanel,
            this.mnuViewStatusBar,
            this.mnuLongFileNames,
            this.mnuViewSep1,
            this.mnuViewHistogram,
            this.mnuViewSpectrum,
            this.mnuViewBand});
            this.mnuView.Name = "mnuView";
            this.mnuView.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.mnuView.Size = new System.Drawing.Size(40, 20);
            this.mnuView.Text = "&View";
            this.mnuView.Click += new System.EventHandler(this.mnuView_Click);
            // 
            // mnuViewToolbar
            // 
            this.mnuViewToolbar.Checked = true;
            this.mnuViewToolbar.CheckOnClick = true;
            this.mnuViewToolbar.CheckState = System.Windows.Forms.CheckState.Checked;
            this.mnuViewToolbar.Name = "mnuViewToolbar";
            this.mnuViewToolbar.Size = new System.Drawing.Size(215, 22);
            this.mnuViewToolbar.Text = "&Toolbar";
            this.mnuViewToolbar.CheckedChanged += new System.EventHandler(this.mnuViewToolbar_CheckedChanged);
            // 
            // mnuViewImageQueue
            // 
            this.mnuViewImageQueue.Checked = true;
            this.mnuViewImageQueue.CheckOnClick = true;
            this.mnuViewImageQueue.CheckState = System.Windows.Forms.CheckState.Checked;
            this.mnuViewImageQueue.Name = "mnuViewImageQueue";
            this.mnuViewImageQueue.Size = new System.Drawing.Size(215, 22);
            this.mnuViewImageQueue.Text = "Image Queue";
            this.mnuViewImageQueue.CheckedChanged += new System.EventHandler(this.mnuViewImageQueue_CheckedChanged);
            // 
            // mnuViewInfoPanel
            // 
            this.mnuViewInfoPanel.CheckOnClick = true;
            this.mnuViewInfoPanel.Name = "mnuViewInfoPanel";
            this.mnuViewInfoPanel.Size = new System.Drawing.Size(215, 22);
            this.mnuViewInfoPanel.Text = "CVIP Function &Information";
            this.mnuViewInfoPanel.CheckedChanged += new System.EventHandler(this.mnuViewInfoPanel_CheckedChanged);
            // 
            // mnuViewStatusBar
            // 
            this.mnuViewStatusBar.Checked = true;
            this.mnuViewStatusBar.CheckOnClick = true;
            this.mnuViewStatusBar.CheckState = System.Windows.Forms.CheckState.Checked;
            this.mnuViewStatusBar.Name = "mnuViewStatusBar";
            this.mnuViewStatusBar.Size = new System.Drawing.Size(215, 22);
            this.mnuViewStatusBar.Text = "Status &Bar";
            this.mnuViewStatusBar.CheckedChanged += new System.EventHandler(this.mnuViewStatusBar_CheckedChanged);
            // 
            // mnuLongFileNames
            // 
            this.mnuLongFileNames.Checked = true;
            this.mnuLongFileNames.CheckOnClick = true;
            this.mnuLongFileNames.CheckState = System.Windows.Forms.CheckState.Checked;
            this.mnuLongFileNames.Name = "mnuLongFileNames";
            this.mnuLongFileNames.Size = new System.Drawing.Size(215, 22);
            this.mnuLongFileNames.Text = "Long File Names";
            this.mnuLongFileNames.CheckedChanged += new System.EventHandler(this.mnuLongFileNames_CheckedChanged);
            this.mnuLongFileNames.Click += new System.EventHandler(this.mnuLongFileNames_Click);
            // 
            // mnuViewSep1
            // 
            this.mnuViewSep1.Name = "mnuViewSep1";
            this.mnuViewSep1.Size = new System.Drawing.Size(212, 6);
            // 
            // mnuViewHistogram
            // 
            this.mnuViewHistogram.Enabled = false;
            this.mnuViewHistogram.Image = ((System.Drawing.Image)(resources.GetObject("mnuViewHistogram.Image")));
            this.mnuViewHistogram.ImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(212)))), ((int)(((byte)(234)))), ((int)(((byte)(252)))));
            this.mnuViewHistogram.Name = "mnuViewHistogram";
            this.mnuViewHistogram.Size = new System.Drawing.Size(215, 22);
            this.mnuViewHistogram.Text = "Show Histogram";
            this.mnuViewHistogram.Click += new System.EventHandler(this.mnuFileHistogram_Click);
            // 
            // mnuViewSpectrum
            // 
            this.mnuViewSpectrum.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuViewFFTPhase,
            this.mnuViewFFTMagnitude,
            this.mnuViewLogRemapped});
            this.mnuViewSpectrum.Name = "mnuViewSpectrum";
            this.mnuViewSpectrum.Size = new System.Drawing.Size(215, 22);
            this.mnuViewSpectrum.Text = "Show Spectrum";
            // 
            // mnuViewFFTPhase
            // 
            this.mnuViewFFTPhase.Enabled = false;
            this.mnuViewFFTPhase.Name = "mnuViewFFTPhase";
            this.mnuViewFFTPhase.Size = new System.Drawing.Size(153, 22);
            this.mnuViewFFTPhase.Text = "FFT Phase";
            this.mnuViewFFTPhase.Click += new System.EventHandler(this.mnuFFTPhase_Click);
            // 
            // mnuViewFFTMagnitude
            // 
            this.mnuViewFFTMagnitude.Enabled = false;
            this.mnuViewFFTMagnitude.Name = "mnuViewFFTMagnitude";
            this.mnuViewFFTMagnitude.Size = new System.Drawing.Size(153, 22);
            this.mnuViewFFTMagnitude.Text = "Magnitude";
            this.mnuViewFFTMagnitude.Click += new System.EventHandler(this.mnuFFTMagnitude_Click);
            // 
            // mnuViewLogRemapped
            // 
            this.mnuViewLogRemapped.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuViewLogRemapAll,
            this.mnuViewLogRemapRed,
            this.mnuViewLogRemapGreen,
            this.mnuViewLogRemapBlue});
            this.mnuViewLogRemapped.Name = "mnuViewLogRemapped";
            this.mnuViewLogRemapped.Size = new System.Drawing.Size(153, 22);
            this.mnuViewLogRemapped.Text = "Log-remapped";
            // 
            // mnuViewLogRemapAll
            // 
            this.mnuViewLogRemapAll.Enabled = false;
            this.mnuViewLogRemapAll.Name = "mnuViewLogRemapAll";
            this.mnuViewLogRemapAll.Size = new System.Drawing.Size(135, 22);
            this.mnuViewLogRemapAll.Tag = CVIPGUI.LogRemap.All;
            this.mnuViewLogRemapAll.Text = "All Bands";
            this.mnuViewLogRemapAll.Click += new System.EventHandler(this.mnuLogRemap_Click);
            // 
            // mnuViewLogRemapRed
            // 
            this.mnuViewLogRemapRed.Enabled = false;
            this.mnuViewLogRemapRed.Name = "mnuViewLogRemapRed";
            this.mnuViewLogRemapRed.Size = new System.Drawing.Size(135, 22);
            this.mnuViewLogRemapRed.Tag = CVIPGUI.LogRemap.Red;
            this.mnuViewLogRemapRed.Text = "Red Band";
            this.mnuViewLogRemapRed.Click += new System.EventHandler(this.mnuLogRemap_Click);
            // 
            // mnuViewLogRemapGreen
            // 
            this.mnuViewLogRemapGreen.Enabled = false;
            this.mnuViewLogRemapGreen.Name = "mnuViewLogRemapGreen";
            this.mnuViewLogRemapGreen.Size = new System.Drawing.Size(135, 22);
            this.mnuViewLogRemapGreen.Tag = CVIPGUI.LogRemap.Green;
            this.mnuViewLogRemapGreen.Text = "Green Band";
            this.mnuViewLogRemapGreen.Click += new System.EventHandler(this.mnuLogRemap_Click);
            // 
            // mnuViewLogRemapBlue
            // 
            this.mnuViewLogRemapBlue.Enabled = false;
            this.mnuViewLogRemapBlue.Name = "mnuViewLogRemapBlue";
            this.mnuViewLogRemapBlue.Size = new System.Drawing.Size(135, 22);
            this.mnuViewLogRemapBlue.Tag = CVIPGUI.LogRemap.Blue;
            this.mnuViewLogRemapBlue.Text = "Blue Band";
            this.mnuViewLogRemapBlue.Click += new System.EventHandler(this.mnuLogRemap_Click);
            // 
            // mnuViewBand
            // 
            this.mnuViewBand.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuViewBandRed,
            this.mnuViewBandGreen,
            this.mnuViewBandBlue});
            this.mnuViewBand.Name = "mnuViewBand";
            this.mnuViewBand.Size = new System.Drawing.Size(215, 22);
            this.mnuViewBand.Text = "View Band";
            // 
            // mnuViewBandRed
            // 
            this.mnuViewBandRed.Enabled = false;
            this.mnuViewBandRed.Image = ((System.Drawing.Image)(resources.GetObject("mnuViewBandRed.Image")));
            this.mnuViewBandRed.ImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(234)))), ((int)(((byte)(220)))));
            this.mnuViewBandRed.Name = "mnuViewBandRed";
            this.mnuViewBandRed.Size = new System.Drawing.Size(105, 22);
            this.mnuViewBandRed.Tag = "0";
            this.mnuViewBandRed.Text = "Red";
            this.mnuViewBandRed.ToolTipText = "Show red band";
            this.mnuViewBandRed.Click += new System.EventHandler(this.mnuViewBand_Click);
            // 
            // mnuViewBandGreen
            // 
            this.mnuViewBandGreen.Enabled = false;
            this.mnuViewBandGreen.Image = ((System.Drawing.Image)(resources.GetObject("mnuViewBandGreen.Image")));
            this.mnuViewBandGreen.ImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(234)))), ((int)(((byte)(220)))));
            this.mnuViewBandGreen.Name = "mnuViewBandGreen";
            this.mnuViewBandGreen.Size = new System.Drawing.Size(105, 22);
            this.mnuViewBandGreen.Tag = "1";
            this.mnuViewBandGreen.Text = "Green";
            this.mnuViewBandGreen.ToolTipText = "Show green band";
            this.mnuViewBandGreen.Click += new System.EventHandler(this.mnuViewBand_Click);
            // 
            // mnuViewBandBlue
            // 
            this.mnuViewBandBlue.Enabled = false;
            this.mnuViewBandBlue.Image = ((System.Drawing.Image)(resources.GetObject("mnuViewBandBlue.Image")));
            this.mnuViewBandBlue.ImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(234)))), ((int)(((byte)(220)))));
            this.mnuViewBandBlue.Name = "mnuViewBandBlue";
            this.mnuViewBandBlue.Size = new System.Drawing.Size(105, 22);
            this.mnuViewBandBlue.Tag = "2";
            this.mnuViewBandBlue.Text = "Blue";
            this.mnuViewBandBlue.ToolTipText = "Show blue band";
            this.mnuViewBandBlue.Click += new System.EventHandler(this.mnuViewBand_Click);
            // 
            // mnuAnalysis
            // 
            this.mnuAnalysis.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuAnalysisPreprocessing,
            this.mnuAnalysisGeometry,
            this.mnuAnalysisEdgeDetect,
            this.mnuAnalysisSegment,
            this.mnuAnalysisTransforms,
            this.mnuAnalysisFeatures,
            this.mnuAnalysisClassify});
            this.mnuAnalysis.Name = "mnuAnalysis";
            this.mnuAnalysis.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.mnuAnalysis.Size = new System.Drawing.Size(58, 20);
            this.mnuAnalysis.Text = "&Analysis";
            // 
            // mnuAnalysisPreprocessing
            // 
            this.mnuAnalysisPreprocessing.Name = "mnuAnalysisPreprocessing";
            this.mnuAnalysisPreprocessing.Size = new System.Drawing.Size(185, 22);
            this.mnuAnalysisPreprocessing.Tag = "0";
            this.mnuAnalysisPreprocessing.Text = "Preprocessing";
            this.mnuAnalysisPreprocessing.Click += new System.EventHandler(this.mnuAnalysis_Click);
            // 
            // mnuAnalysisGeometry
            // 
            this.mnuAnalysisGeometry.Name = "mnuAnalysisGeometry";
            this.mnuAnalysisGeometry.Size = new System.Drawing.Size(185, 22);
            this.mnuAnalysisGeometry.Tag = "1";
            this.mnuAnalysisGeometry.Text = "Geometry";
            this.mnuAnalysisGeometry.Click += new System.EventHandler(this.mnuAnalysis_Click);
            // 
            // mnuAnalysisEdgeDetect
            // 
            this.mnuAnalysisEdgeDetect.Name = "mnuAnalysisEdgeDetect";
            this.mnuAnalysisEdgeDetect.Size = new System.Drawing.Size(185, 22);
            this.mnuAnalysisEdgeDetect.Tag = "2";
            this.mnuAnalysisEdgeDetect.Text = "Edge/Line Detection";
            this.mnuAnalysisEdgeDetect.Click += new System.EventHandler(this.mnuAnalysis_Click);
            // 
            // mnuAnalysisSegment
            // 
            this.mnuAnalysisSegment.Name = "mnuAnalysisSegment";
            this.mnuAnalysisSegment.Size = new System.Drawing.Size(185, 22);
            this.mnuAnalysisSegment.Tag = "3";
            this.mnuAnalysisSegment.Text = "Segmentation";
            this.mnuAnalysisSegment.Click += new System.EventHandler(this.mnuAnalysis_Click);
            // 
            // mnuAnalysisTransforms
            // 
            this.mnuAnalysisTransforms.Name = "mnuAnalysisTransforms";
            this.mnuAnalysisTransforms.Size = new System.Drawing.Size(185, 22);
            this.mnuAnalysisTransforms.Tag = "4";
            this.mnuAnalysisTransforms.Text = "Transforms";
            this.mnuAnalysisTransforms.Click += new System.EventHandler(this.mnuAnalysis_Click);
            // 
            // mnuAnalysisFeatures
            // 
            this.mnuAnalysisFeatures.Name = "mnuAnalysisFeatures";
            this.mnuAnalysisFeatures.Size = new System.Drawing.Size(185, 22);
            this.mnuAnalysisFeatures.Tag = "5";
            this.mnuAnalysisFeatures.Text = "Features";
            this.mnuAnalysisFeatures.Click += new System.EventHandler(this.mnuAnalysis_Click);
            // 
            // mnuAnalysisClassify
            // 
            this.mnuAnalysisClassify.Name = "mnuAnalysisClassify";
            this.mnuAnalysisClassify.Size = new System.Drawing.Size(185, 22);
            this.mnuAnalysisClassify.Tag = "6";
            this.mnuAnalysisClassify.Text = "Pattern Classification";
            this.mnuAnalysisClassify.Click += new System.EventHandler(this.mnuAnalysis_Click);
            // 
            // mnuEnhancement
            // 
            this.mnuEnhancement.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuEnhanceHistograms,
            this.mnuEnhancePseudocolor,
            this.mnuEnhanceSharpen,
            this.mnuEnhanceSmooth});
            this.mnuEnhancement.Name = "mnuEnhancement";
            this.mnuEnhancement.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.mnuEnhancement.Size = new System.Drawing.Size(88, 20);
            this.mnuEnhancement.Text = "&Enhancement";
            // 
            // mnuEnhanceHistograms
            // 
            this.mnuEnhanceHistograms.Name = "mnuEnhanceHistograms";
            this.mnuEnhanceHistograms.Size = new System.Drawing.Size(180, 22);
            this.mnuEnhanceHistograms.Tag = "0";
            this.mnuEnhanceHistograms.Text = "Histogram/Contrast";
            this.mnuEnhanceHistograms.Click += new System.EventHandler(this.mnuEnhancement_Click);
            // 
            // mnuEnhancePseudocolor
            // 
            this.mnuEnhancePseudocolor.Name = "mnuEnhancePseudocolor";
            this.mnuEnhancePseudocolor.Size = new System.Drawing.Size(180, 22);
            this.mnuEnhancePseudocolor.Tag = "1";
            this.mnuEnhancePseudocolor.Text = "Pseudocolor";
            this.mnuEnhancePseudocolor.Click += new System.EventHandler(this.mnuEnhancement_Click);
            // 
            // mnuEnhanceSharpen
            // 
            this.mnuEnhanceSharpen.Name = "mnuEnhanceSharpen";
            this.mnuEnhanceSharpen.Size = new System.Drawing.Size(180, 22);
            this.mnuEnhanceSharpen.Tag = "2";
            this.mnuEnhanceSharpen.Text = "Sharpening";
            this.mnuEnhanceSharpen.Click += new System.EventHandler(this.mnuEnhancement_Click);
            // 
            // mnuEnhanceSmooth
            // 
            this.mnuEnhanceSmooth.Name = "mnuEnhanceSmooth";
            this.mnuEnhanceSmooth.Size = new System.Drawing.Size(180, 22);
            this.mnuEnhanceSmooth.Tag = "3";
            this.mnuEnhanceSmooth.Text = "Smoothing";
            this.mnuEnhanceSmooth.Click += new System.EventHandler(this.mnuEnhancement_Click);
            // 
            // mnuRestoration
            // 
            this.mnuRestoration.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuRestoreNoise,
            this.mnuRestoreSpatialFilters,
            this.mnuRestoreFreqFilters,
            this.mnuRestoreGeoTransforms});
            this.mnuRestoration.Name = "mnuRestoration";
            this.mnuRestoration.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.mnuRestoration.Size = new System.Drawing.Size(75, 20);
            this.mnuRestoration.Text = "&Restoration";
            // 
            // mnuRestoreNoise
            // 
            this.mnuRestoreNoise.Name = "mnuRestoreNoise";
            this.mnuRestoreNoise.Size = new System.Drawing.Size(190, 22);
            this.mnuRestoreNoise.Tag = "0";
            this.mnuRestoreNoise.Text = "Noise";
            this.mnuRestoreNoise.Click += new System.EventHandler(this.mnuRestoration_Click);
            // 
            // mnuRestoreSpatialFilters
            // 
            this.mnuRestoreSpatialFilters.Name = "mnuRestoreSpatialFilters";
            this.mnuRestoreSpatialFilters.Size = new System.Drawing.Size(190, 22);
            this.mnuRestoreSpatialFilters.Tag = "1";
            this.mnuRestoreSpatialFilters.Text = "Spatial Filters";
            this.mnuRestoreSpatialFilters.Click += new System.EventHandler(this.mnuRestoration_Click);
            // 
            // mnuRestoreFreqFilters
            // 
            this.mnuRestoreFreqFilters.Name = "mnuRestoreFreqFilters";
            this.mnuRestoreFreqFilters.Size = new System.Drawing.Size(190, 22);
            this.mnuRestoreFreqFilters.Tag = "2";
            this.mnuRestoreFreqFilters.Text = "Frequency Filters";
            this.mnuRestoreFreqFilters.Click += new System.EventHandler(this.mnuRestoration_Click);
            // 
            // mnuRestoreGeoTransforms
            // 
            this.mnuRestoreGeoTransforms.Name = "mnuRestoreGeoTransforms";
            this.mnuRestoreGeoTransforms.Size = new System.Drawing.Size(190, 22);
            this.mnuRestoreGeoTransforms.Tag = "3";
            this.mnuRestoreGeoTransforms.Text = "Geometric Transforms";
            this.mnuRestoreGeoTransforms.Click += new System.EventHandler(this.mnuRestoration_Click);
            // 
            // mnuCompression
            // 
            this.mnuCompression.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuCompressPreprocess,
            this.mnuCompressLossless,
            this.mnuCompressLossy,
            this.mnuCompressPostprocess});
            this.mnuCompression.Name = "mnuCompression";
            this.mnuCompression.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.mnuCompression.Size = new System.Drawing.Size(85, 20);
            this.mnuCompression.Text = "&Compression";
            // 
            // mnuCompressPreprocess
            // 
            this.mnuCompressPreprocess.Name = "mnuCompressPreprocess";
            this.mnuCompressPreprocess.Size = new System.Drawing.Size(148, 22);
            this.mnuCompressPreprocess.Tag = "0";
            this.mnuCompressPreprocess.Text = "Preprocessing";
            this.mnuCompressPreprocess.Click += new System.EventHandler(this.mnuCompression_Click);
            // 
            // mnuCompressLossless
            // 
            this.mnuCompressLossless.Name = "mnuCompressLossless";
            this.mnuCompressLossless.Size = new System.Drawing.Size(148, 22);
            this.mnuCompressLossless.Tag = "1";
            this.mnuCompressLossless.Text = "Lossless";
            this.mnuCompressLossless.Click += new System.EventHandler(this.mnuCompression_Click);
            // 
            // mnuCompressLossy
            // 
            this.mnuCompressLossy.Name = "mnuCompressLossy";
            this.mnuCompressLossy.Size = new System.Drawing.Size(148, 22);
            this.mnuCompressLossy.Tag = "2";
            this.mnuCompressLossy.Text = "Lossy";
            this.mnuCompressLossy.Click += new System.EventHandler(this.mnuCompression_Click);
            // 
            // mnuCompressPostprocess
            // 
            this.mnuCompressPostprocess.Name = "mnuCompressPostprocess";
            this.mnuCompressPostprocess.Size = new System.Drawing.Size(148, 22);
            this.mnuCompressPostprocess.Tag = "3";
            this.mnuCompressPostprocess.Text = "Postprocessing";
            this.mnuCompressPostprocess.Click += new System.EventHandler(this.mnuCompression_Click);
            // 
            // mnuShowUtilities
            // 
            this.mnuShowUtilities.CheckOnClick = true;
            this.mnuShowUtilities.Name = "mnuShowUtilities";
            this.mnuShowUtilities.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.mnuShowUtilities.Size = new System.Drawing.Size(54, 20);
            this.mnuShowUtilities.Text = "&Utilities";
            this.mnuShowUtilities.Click += new System.EventHandler(this.mnuShowUtilities_Click);
            // 
            // mnuUtilArithLogic
            // 
            this.mnuUtilArithLogic.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuUtilADD,
            this.mnuUtilSUB,
            this.mnuUtilMUL,
            this.mnuUtilDIV,
            this.mnuUtilArithSep1,
            this.mnuUtilAND,
            this.mnuUtilNOT,
            this.mnuUtilOR,
            this.mnuUtilXOR});
            this.mnuUtilArithLogic.Name = "mnuUtilArithLogic";
            this.mnuUtilArithLogic.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.mnuUtilArithLogic.Size = new System.Drawing.Size(75, 20);
            this.mnuUtilArithLogic.Text = "Arith/Logic";
            this.mnuUtilArithLogic.Visible = false;
            // 
            // mnuUtilADD
            // 
            this.mnuUtilADD.Name = "mnuUtilADD";
            this.mnuUtilADD.Size = new System.Drawing.Size(118, 22);
            this.mnuUtilADD.Text = "Add";
            this.mnuUtilADD.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilSUB
            // 
            this.mnuUtilSUB.Name = "mnuUtilSUB";
            this.mnuUtilSUB.Size = new System.Drawing.Size(118, 22);
            this.mnuUtilSUB.Text = "Subtract";
            this.mnuUtilSUB.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilMUL
            // 
            this.mnuUtilMUL.Name = "mnuUtilMUL";
            this.mnuUtilMUL.Size = new System.Drawing.Size(118, 22);
            this.mnuUtilMUL.Text = "Multiply";
            this.mnuUtilMUL.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilDIV
            // 
            this.mnuUtilDIV.Name = "mnuUtilDIV";
            this.mnuUtilDIV.Size = new System.Drawing.Size(118, 22);
            this.mnuUtilDIV.Text = "Divide";
            this.mnuUtilDIV.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilArithSep1
            // 
            this.mnuUtilArithSep1.Name = "mnuUtilArithSep1";
            this.mnuUtilArithSep1.Size = new System.Drawing.Size(115, 6);
            // 
            // mnuUtilAND
            // 
            this.mnuUtilAND.Name = "mnuUtilAND";
            this.mnuUtilAND.Size = new System.Drawing.Size(118, 22);
            this.mnuUtilAND.Text = "AND";
            this.mnuUtilAND.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilNOT
            // 
            this.mnuUtilNOT.Name = "mnuUtilNOT";
            this.mnuUtilNOT.Size = new System.Drawing.Size(118, 22);
            this.mnuUtilNOT.Text = "NOT";
            this.mnuUtilNOT.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilOR
            // 
            this.mnuUtilOR.Name = "mnuUtilOR";
            this.mnuUtilOR.Size = new System.Drawing.Size(118, 22);
            this.mnuUtilOR.Text = "OR";
            this.mnuUtilOR.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilXOR
            // 
            this.mnuUtilXOR.Name = "mnuUtilXOR";
            this.mnuUtilXOR.Size = new System.Drawing.Size(118, 22);
            this.mnuUtilXOR.Text = "XOR";
            this.mnuUtilXOR.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilCompare
            // 
            this.mnuUtilCompare.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuUtilCompareImages,
            this.mnuUtilCompareError,
            this.mnuUtilPrattMerit});
            this.mnuUtilCompare.Name = "mnuUtilCompare";
            this.mnuUtilCompare.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.mnuUtilCompare.Size = new System.Drawing.Size(64, 20);
            this.mnuUtilCompare.Text = "Compare";
            this.mnuUtilCompare.Visible = false;
            // 
            // mnuUtilCompareImages
            // 
            this.mnuUtilCompareImages.Name = "mnuUtilCompareImages";
            this.mnuUtilCompareImages.Size = new System.Drawing.Size(188, 22);
            this.mnuUtilCompareImages.Text = "Compare Two Images";
            this.mnuUtilCompareImages.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilCompareError
            // 
            this.mnuUtilCompareError.Name = "mnuUtilCompareError";
            this.mnuUtilCompareError.Size = new System.Drawing.Size(188, 22);
            this.mnuUtilCompareError.Text = "Objective Error Metrics";
            this.mnuUtilCompareError.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilPrattMerit
            // 
            this.mnuUtilPrattMerit.Name = "mnuUtilPrattMerit";
            this.mnuUtilPrattMerit.Size = new System.Drawing.Size(188, 22);
            this.mnuUtilPrattMerit.Text = "Pratt Figure of Merit";
            this.mnuUtilPrattMerit.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilConvert
            // 
            this.mnuUtilConvert.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuUtilBinThreshold,
            this.mnuUtilDataType,
            this.mnuUtilHalftone,
            this.mnuUtilGrayLevelQuant,
            this.mnuUtilGrayToBinary,
            this.mnuUtilGrayToColor,
            this.mnuUtilColorToGray,
            this.mnuUtilColorSpace,
            this.mnuUtilLabelImage});
            this.mnuUtilConvert.Name = "mnuUtilConvert";
            this.mnuUtilConvert.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.mnuUtilConvert.Size = new System.Drawing.Size(57, 20);
            this.mnuUtilConvert.Text = "Convert";
            this.mnuUtilConvert.Visible = false;
            // 
            // mnuUtilBinThreshold
            // 
            this.mnuUtilBinThreshold.Name = "mnuUtilBinThreshold";
            this.mnuUtilBinThreshold.Size = new System.Drawing.Size(209, 22);
            this.mnuUtilBinThreshold.Text = "Binary Threshold";
            this.mnuUtilBinThreshold.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilDataType
            // 
            this.mnuUtilDataType.Name = "mnuUtilDataType";
            this.mnuUtilDataType.Size = new System.Drawing.Size(209, 22);
            this.mnuUtilDataType.Text = "Data Type";
            this.mnuUtilDataType.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilHalftone
            // 
            this.mnuUtilHalftone.Name = "mnuUtilHalftone";
            this.mnuUtilHalftone.Size = new System.Drawing.Size(209, 22);
            this.mnuUtilHalftone.Text = "Halftone";
            this.mnuUtilHalftone.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilGrayLevelQuant
            // 
            this.mnuUtilGrayLevelQuant.Name = "mnuUtilGrayLevelQuant";
            this.mnuUtilGrayLevelQuant.Size = new System.Drawing.Size(209, 22);
            this.mnuUtilGrayLevelQuant.Text = "Gray Level Quantization";
            this.mnuUtilGrayLevelQuant.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilGrayToBinary
            // 
            this.mnuUtilGrayToBinary.Name = "mnuUtilGrayToBinary";
            this.mnuUtilGrayToBinary.Size = new System.Drawing.Size(209, 22);
            this.mnuUtilGrayToBinary.Text = "Gray Code-Natural Binary";
            this.mnuUtilGrayToBinary.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilGrayToColor
            // 
            this.mnuUtilGrayToColor.Name = "mnuUtilGrayToColor";
            this.mnuUtilGrayToColor.Size = new System.Drawing.Size(209, 22);
            this.mnuUtilGrayToColor.Text = "Gray to Color";
            this.mnuUtilGrayToColor.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilColorToGray
            // 
            this.mnuUtilColorToGray.Name = "mnuUtilColorToGray";
            this.mnuUtilColorToGray.Size = new System.Drawing.Size(209, 22);
            this.mnuUtilColorToGray.Text = "Color to Gray";
            this.mnuUtilColorToGray.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilColorSpace
            // 
            this.mnuUtilColorSpace.Name = "mnuUtilColorSpace";
            this.mnuUtilColorSpace.Size = new System.Drawing.Size(209, 22);
            this.mnuUtilColorSpace.Text = "Color Space";
            this.mnuUtilColorSpace.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilLabelImage
            // 
            this.mnuUtilLabelImage.Name = "mnuUtilLabelImage";
            this.mnuUtilLabelImage.Size = new System.Drawing.Size(209, 22);
            this.mnuUtilLabelImage.Text = "Label Image";
            this.mnuUtilLabelImage.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilCreate
            // 
            this.mnuUtilCreate.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuUtilCheckerboard,
            this.mnuUtilCircle,
            this.mnuUtilEllipse,
            this.mnuUtilLine,
            this.mnuUtilRectangle,
            this.mnuUtilCreateSep1,
            this.mnuUtilCosineWave,
            this.mnuUtilSineWave,
            this.mnuUtilSquareWave,
            this.mnuUtilCreateSep2,
            this.mnuUtilExtractBand,
            this.mnuUtilAssembleBands,
            this.mnuUtilCreateSep3,
            this.mnuUtilBlackImage,
            this.mnuUtilAddNoise,
            this.mnuUtilCreateSep4,
            this.mnuUtilBorderMask,
            this.mnuUtilBorderImage});
            this.mnuUtilCreate.Name = "mnuUtilCreate";
            this.mnuUtilCreate.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.mnuUtilCreate.Size = new System.Drawing.Size(49, 20);
            this.mnuUtilCreate.Text = "Create";
            this.mnuUtilCreate.Visible = false;
            // 
            // mnuUtilCheckerboard
            // 
            this.mnuUtilCheckerboard.Name = "mnuUtilCheckerboard";
            this.mnuUtilCheckerboard.Size = new System.Drawing.Size(160, 22);
            this.mnuUtilCheckerboard.Text = "Checkerboard";
            this.mnuUtilCheckerboard.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilCircle
            // 
            this.mnuUtilCircle.Name = "mnuUtilCircle";
            this.mnuUtilCircle.Size = new System.Drawing.Size(160, 22);
            this.mnuUtilCircle.Text = "Circle";
            this.mnuUtilCircle.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilEllipse
            // 
            this.mnuUtilEllipse.Name = "mnuUtilEllipse";
            this.mnuUtilEllipse.Size = new System.Drawing.Size(160, 22);
            this.mnuUtilEllipse.Text = "Ellipse";
            this.mnuUtilEllipse.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilLine
            // 
            this.mnuUtilLine.Name = "mnuUtilLine";
            this.mnuUtilLine.Size = new System.Drawing.Size(160, 22);
            this.mnuUtilLine.Text = "Line";
            this.mnuUtilLine.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilRectangle
            // 
            this.mnuUtilRectangle.Name = "mnuUtilRectangle";
            this.mnuUtilRectangle.Size = new System.Drawing.Size(160, 22);
            this.mnuUtilRectangle.Text = "Rectangle";
            this.mnuUtilRectangle.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilCreateSep1
            // 
            this.mnuUtilCreateSep1.Name = "mnuUtilCreateSep1";
            this.mnuUtilCreateSep1.Size = new System.Drawing.Size(157, 6);
            // 
            // mnuUtilCosineWave
            // 
            this.mnuUtilCosineWave.Name = "mnuUtilCosineWave";
            this.mnuUtilCosineWave.Size = new System.Drawing.Size(160, 22);
            this.mnuUtilCosineWave.Text = "Cosine Wave";
            this.mnuUtilCosineWave.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilSineWave
            // 
            this.mnuUtilSineWave.Name = "mnuUtilSineWave";
            this.mnuUtilSineWave.Size = new System.Drawing.Size(160, 22);
            this.mnuUtilSineWave.Text = "Sine Wave";
            this.mnuUtilSineWave.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilSquareWave
            // 
            this.mnuUtilSquareWave.Name = "mnuUtilSquareWave";
            this.mnuUtilSquareWave.Size = new System.Drawing.Size(160, 22);
            this.mnuUtilSquareWave.Text = "Square Wave";
            this.mnuUtilSquareWave.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilCreateSep2
            // 
            this.mnuUtilCreateSep2.Name = "mnuUtilCreateSep2";
            this.mnuUtilCreateSep2.Size = new System.Drawing.Size(157, 6);
            // 
            // mnuUtilExtractBand
            // 
            this.mnuUtilExtractBand.Name = "mnuUtilExtractBand";
            this.mnuUtilExtractBand.Size = new System.Drawing.Size(160, 22);
            this.mnuUtilExtractBand.Text = "Extract Band";
            this.mnuUtilExtractBand.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilAssembleBands
            // 
            this.mnuUtilAssembleBands.Name = "mnuUtilAssembleBands";
            this.mnuUtilAssembleBands.Size = new System.Drawing.Size(160, 22);
            this.mnuUtilAssembleBands.Text = "Assemble Bands";
            this.mnuUtilAssembleBands.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilCreateSep3
            // 
            this.mnuUtilCreateSep3.Name = "mnuUtilCreateSep3";
            this.mnuUtilCreateSep3.Size = new System.Drawing.Size(157, 6);
            // 
            // mnuUtilBlackImage
            // 
            this.mnuUtilBlackImage.Name = "mnuUtilBlackImage";
            this.mnuUtilBlackImage.Size = new System.Drawing.Size(160, 22);
            this.mnuUtilBlackImage.Text = "Black Image";
            this.mnuUtilBlackImage.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilAddNoise
            // 
            this.mnuUtilAddNoise.Name = "mnuUtilAddNoise";
            this.mnuUtilAddNoise.Size = new System.Drawing.Size(160, 22);
            this.mnuUtilAddNoise.Text = "Add Noise";
            this.mnuUtilAddNoise.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilCreateSep4
            // 
            this.mnuUtilCreateSep4.Name = "mnuUtilCreateSep4";
            this.mnuUtilCreateSep4.Size = new System.Drawing.Size(157, 6);
            // 
            // mnuUtilBorderMask
            // 
            this.mnuUtilBorderMask.Name = "mnuUtilBorderMask";
            this.mnuUtilBorderMask.Size = new System.Drawing.Size(160, 22);
            this.mnuUtilBorderMask.Text = "Border Mask";
            this.mnuUtilBorderMask.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilBorderImage
            // 
            this.mnuUtilBorderImage.Name = "mnuUtilBorderImage";
            this.mnuUtilBorderImage.Size = new System.Drawing.Size(160, 22);
            this.mnuUtilBorderImage.Text = "Border Image";
            this.mnuUtilBorderImage.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilEnhance
            // 
            this.mnuUtilEnhance.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuUtilBrightenDarken,
            this.mnuUtilEdgeEnhancement,
            this.mnuUtilHistogramEQ,
            this.mnuUtilHistoStretch,
            this.mnuUtilPseudocolor,
            this.mnuUtilSharpen});
            this.mnuUtilEnhance.Name = "mnuUtilEnhance";
            this.mnuUtilEnhance.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.mnuUtilEnhance.Size = new System.Drawing.Size(60, 20);
            this.mnuUtilEnhance.Text = "Enhance";
            this.mnuUtilEnhance.Visible = false;
            // 
            // mnuUtilBrightenDarken
            // 
            this.mnuUtilBrightenDarken.Name = "mnuUtilBrightenDarken";
            this.mnuUtilBrightenDarken.Size = new System.Drawing.Size(197, 22);
            this.mnuUtilBrightenDarken.Text = "Brighten/Darken";
            this.mnuUtilBrightenDarken.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilEdgeEnhancement
            // 
            this.mnuUtilEdgeEnhancement.Name = "mnuUtilEdgeEnhancement";
            this.mnuUtilEdgeEnhancement.Size = new System.Drawing.Size(197, 22);
            this.mnuUtilEdgeEnhancement.Text = "Edge Enhancement";
            this.mnuUtilEdgeEnhancement.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilHistogramEQ
            // 
            this.mnuUtilHistogramEQ.Name = "mnuUtilHistogramEQ";
            this.mnuUtilHistogramEQ.Size = new System.Drawing.Size(197, 22);
            this.mnuUtilHistogramEQ.Text = "Histogram Equalization";
            this.mnuUtilHistogramEQ.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilHistoStretch
            // 
            this.mnuUtilHistoStretch.Name = "mnuUtilHistoStretch";
            this.mnuUtilHistoStretch.Size = new System.Drawing.Size(197, 22);
            this.mnuUtilHistoStretch.Text = "Histogram Stretch";
            this.mnuUtilHistoStretch.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilPseudocolor
            // 
            this.mnuUtilPseudocolor.Name = "mnuUtilPseudocolor";
            this.mnuUtilPseudocolor.Size = new System.Drawing.Size(197, 22);
            this.mnuUtilPseudocolor.Text = "Pseudocolor";
            this.mnuUtilPseudocolor.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilSharpen
            // 
            this.mnuUtilSharpen.Name = "mnuUtilSharpen";
            this.mnuUtilSharpen.Size = new System.Drawing.Size(197, 22);
            this.mnuUtilSharpen.Text = "Sharpening";
            this.mnuUtilSharpen.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilFilter
            // 
            this.mnuUtilFilter.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuUtilMean,
            this.mnuUtilMedian,
            this.mnuUtilLaplacian,
            this.mnuUtilEmbossFilter,
            this.mnuUtilFiltSep1,
            this.mnuUtilSpecifyFilter,
            this.mnuUtilSpecifyBlur});
            this.mnuUtilFilter.Name = "mnuUtilFilter";
            this.mnuUtilFilter.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.mnuUtilFilter.Size = new System.Drawing.Size(41, 20);
            this.mnuUtilFilter.Text = "Filter";
            this.mnuUtilFilter.Visible = false;
            // 
            // mnuUtilMean
            // 
            this.mnuUtilMean.Name = "mnuUtilMean";
            this.mnuUtilMean.Size = new System.Drawing.Size(157, 22);
            this.mnuUtilMean.Text = "Mean";
            this.mnuUtilMean.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilMedian
            // 
            this.mnuUtilMedian.Name = "mnuUtilMedian";
            this.mnuUtilMedian.Size = new System.Drawing.Size(157, 22);
            this.mnuUtilMedian.Text = "Median";
            this.mnuUtilMedian.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilLaplacian
            // 
            this.mnuUtilLaplacian.Name = "mnuUtilLaplacian";
            this.mnuUtilLaplacian.Size = new System.Drawing.Size(157, 22);
            this.mnuUtilLaplacian.Text = "Laplacian Filter";
            this.mnuUtilLaplacian.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilEmbossFilter
            // 
            this.mnuUtilEmbossFilter.Name = "mnuUtilEmbossFilter";
            this.mnuUtilEmbossFilter.Size = new System.Drawing.Size(157, 22);
            this.mnuUtilEmbossFilter.Text = "Difference Filter";
            this.mnuUtilEmbossFilter.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilFiltSep1
            // 
            this.mnuUtilFiltSep1.Name = "mnuUtilFiltSep1";
            this.mnuUtilFiltSep1.Size = new System.Drawing.Size(154, 6);
            // 
            // mnuUtilSpecifyFilter
            // 
            this.mnuUtilSpecifyFilter.Name = "mnuUtilSpecifyFilter";
            this.mnuUtilSpecifyFilter.Size = new System.Drawing.Size(157, 22);
            this.mnuUtilSpecifyFilter.Text = "Specify a Filter";
            this.mnuUtilSpecifyFilter.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilSpecifyBlur
            // 
            this.mnuUtilSpecifyBlur.Name = "mnuUtilSpecifyBlur";
            this.mnuUtilSpecifyBlur.Size = new System.Drawing.Size(157, 22);
            this.mnuUtilSpecifyBlur.Text = "Specify a Blur";
            this.mnuUtilSpecifyBlur.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilSize
            // 
            this.mnuUtilSize.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuUtilCrop,
            this.mnuUtilDoubleSize,
            this.mnuUtilResize,
            this.mnuUtilSpatialQuant});
            this.mnuUtilSize.Name = "mnuUtilSize";
            this.mnuUtilSize.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.mnuUtilSize.Size = new System.Drawing.Size(35, 20);
            this.mnuUtilSize.Text = "Size";
            this.mnuUtilSize.Visible = false;
            // 
            // mnuUtilCrop
            // 
            this.mnuUtilCrop.Name = "mnuUtilCrop";
            this.mnuUtilCrop.Size = new System.Drawing.Size(159, 22);
            this.mnuUtilCrop.Text = "Crop";
            this.mnuUtilCrop.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilDoubleSize
            // 
            this.mnuUtilDoubleSize.Name = "mnuUtilDoubleSize";
            this.mnuUtilDoubleSize.Size = new System.Drawing.Size(159, 22);
            this.mnuUtilDoubleSize.Text = "Fast Double Size";
            this.mnuUtilDoubleSize.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilResize
            // 
            this.mnuUtilResize.Name = "mnuUtilResize";
            this.mnuUtilResize.Size = new System.Drawing.Size(159, 22);
            this.mnuUtilResize.Text = "Resize";
            this.mnuUtilResize.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilSpatialQuant
            // 
            this.mnuUtilSpatialQuant.Name = "mnuUtilSpatialQuant";
            this.mnuUtilSpatialQuant.Size = new System.Drawing.Size(159, 22);
            this.mnuUtilSpatialQuant.Text = "Spatial Quant";
            this.mnuUtilSpatialQuant.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilStats
            // 
            this.mnuUtilStats.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuUtilImageDataRange,
            this.mnuUtilImageStatistics});
            this.mnuUtilStats.Name = "mnuUtilStats";
            this.mnuUtilStats.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.mnuUtilStats.Size = new System.Drawing.Size(40, 20);
            this.mnuUtilStats.Text = "Stats";
            this.mnuUtilStats.Visible = false;
            // 
            // mnuUtilImageDataRange
            // 
            this.mnuUtilImageDataRange.Name = "mnuUtilImageDataRange";
            this.mnuUtilImageDataRange.Size = new System.Drawing.Size(170, 22);
            this.mnuUtilImageDataRange.Text = "Image Data Range";
            this.mnuUtilImageDataRange.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuUtilImageStatistics
            // 
            this.mnuUtilImageStatistics.Name = "mnuUtilImageStatistics";
            this.mnuUtilImageStatistics.Size = new System.Drawing.Size(170, 22);
            this.mnuUtilImageStatistics.Text = "Image Statistics";
            this.mnuUtilImageStatistics.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // mnuHelp
            // 
            this.mnuHelp.BackColor = System.Drawing.Color.Yellow;
            this.mnuHelp.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuHelpContents,
            this.mnuHelpSep1,
            this.mnuHelpAbout});
            this.mnuHelp.Name = "mnuHelp";
            this.mnuHelp.Padding = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.mnuHelp.Size = new System.Drawing.Size(40, 20);
            this.mnuHelp.Text = "&Help";
            // 
            // mnuHelpContents
            // 
            this.mnuHelpContents.Name = "mnuHelpContents";
            this.mnuHelpContents.Size = new System.Drawing.Size(170, 22);
            this.mnuHelpContents.Text = "&Contents";
            this.mnuHelpContents.Click += new System.EventHandler(this.mnuHelpContents_Click);
            // 
            // mnuHelpSep1
            // 
            this.mnuHelpSep1.Name = "mnuHelpSep1";
            this.mnuHelpSep1.Size = new System.Drawing.Size(167, 6);
            // 
            // mnuHelpAbout
            // 
            this.mnuHelpAbout.Name = "mnuHelpAbout";
            this.mnuHelpAbout.Size = new System.Drawing.Size(170, 22);
            this.mnuHelpAbout.Text = "&About CVIPtools...";
            this.mnuHelpAbout.Click += new System.EventHandler(this.mnuHelpAbout_Click);
            // 
            // mnuCVIPtoolsWeblink
            // 
            this.mnuCVIPtoolsWeblink.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.mnuCVIPtoolsWeblink.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.mnuCVIPtoolsWeblink.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.mnuCVIPtoolsWeblink.ForeColor = System.Drawing.Color.Blue;
            this.mnuCVIPtoolsWeblink.Name = "mnuCVIPtoolsWeblink";
            this.mnuCVIPtoolsWeblink.Size = new System.Drawing.Size(149, 20);
            this.mnuCVIPtoolsWeblink.Text = "CVIPtools Website";
            this.mnuCVIPtoolsWeblink.Click += new System.EventHandler(this.mnuCVIPtoolsWeblink_Click);
            this.mnuCVIPtoolsWeblink.MouseLeave += new System.EventHandler(this.mnuCVIPtoolsWeblink_MouseLeave);
            this.mnuCVIPtoolsWeblink.MouseMove += new System.Windows.Forms.MouseEventHandler(this.mnuCVIPtoolsWeblink_MouseMove);
            // 
            // pnlInfo
            // 
            this.pnlInfo.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.pnlInfo.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.pnlInfo.Location = new System.Drawing.Point(141, 596);
            this.pnlInfo.Margin = new System.Windows.Forms.Padding(4);
            this.pnlInfo.Name = "pnlInfo";
            this.pnlInfo.Padding = new System.Windows.Forms.Padding(1, 1, 0, 1);
            this.pnlInfo.Size = new System.Drawing.Size(812, 123);
            this.pnlInfo.TabIndex = 2;
            this.pnlInfo.VisibleChanged += new System.EventHandler(this.InfoPanel_VisibleChanged);
            // 
            // pnlQueue
            // 
            this.pnlQueue.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.pnlQueue.Dock = System.Windows.Forms.DockStyle.Left;
            this.pnlQueue.Location = new System.Drawing.Point(0, 55);
            this.pnlQueue.Margin = new System.Windows.Forms.Padding(4);
            this.pnlQueue.Name = "pnlQueue";
            this.pnlQueue.Padding = new System.Windows.Forms.Padding(0, 1, 1, 1);
            this.pnlQueue.Size = new System.Drawing.Size(136, 664);
            this.pnlQueue.TabIndex = 3;
            this.pnlQueue.VisibleChanged += new System.EventHandler(this.ImageQueue_VisibleChanged);
            // 
            // popmnuUtilities
            // 
            this.popmnuUtilities.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.popmnuUtilArithLogic,
            this.popmnuUtilCompare,
            this.popmnuUtilConvert,
            this.popmnuUtilCreate,
            this.popmnuUtilEnhance,
            this.popmnuUtilFilter,
            this.popmnuUtilSize,
            this.popmnuUtilStats});
            this.popmnuUtilities.Name = "popmnuUtilities";
            this.popmnuUtilities.Size = new System.Drawing.Size(135, 180);
            // 
            // popmnuUtilArithLogic
            // 
            this.popmnuUtilArithLogic.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.popmnuUtilADD,
            this.popmnuUtilSUB,
            this.popmnuUtilMUL,
            this.popmnuUtilDIV,
            this.toolStripSeparator1,
            this.popmnuUtilAND,
            this.popmnuUtilNOT,
            this.popmnuUtilOR,
            this.popmnuUtilXOR});
            this.popmnuUtilArithLogic.Name = "popmnuUtilArithLogic";
            this.popmnuUtilArithLogic.Size = new System.Drawing.Size(134, 22);
            this.popmnuUtilArithLogic.Text = "Arith/Logic";
            // 
            // popmnuUtilADD
            // 
            this.popmnuUtilADD.Name = "popmnuUtilADD";
            this.popmnuUtilADD.Size = new System.Drawing.Size(118, 22);
            this.popmnuUtilADD.Text = "Add";
            this.popmnuUtilADD.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilSUB
            // 
            this.popmnuUtilSUB.Name = "popmnuUtilSUB";
            this.popmnuUtilSUB.Size = new System.Drawing.Size(118, 22);
            this.popmnuUtilSUB.Text = "Subtract";
            this.popmnuUtilSUB.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilMUL
            // 
            this.popmnuUtilMUL.Name = "popmnuUtilMUL";
            this.popmnuUtilMUL.Size = new System.Drawing.Size(118, 22);
            this.popmnuUtilMUL.Text = "Multiply";
            this.popmnuUtilMUL.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilDIV
            // 
            this.popmnuUtilDIV.Name = "popmnuUtilDIV";
            this.popmnuUtilDIV.Size = new System.Drawing.Size(118, 22);
            this.popmnuUtilDIV.Text = "Divide";
            this.popmnuUtilDIV.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(115, 6);
            // 
            // popmnuUtilAND
            // 
            this.popmnuUtilAND.Name = "popmnuUtilAND";
            this.popmnuUtilAND.Size = new System.Drawing.Size(118, 22);
            this.popmnuUtilAND.Text = "AND";
            this.popmnuUtilAND.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilNOT
            // 
            this.popmnuUtilNOT.Name = "popmnuUtilNOT";
            this.popmnuUtilNOT.Size = new System.Drawing.Size(118, 22);
            this.popmnuUtilNOT.Text = "NOT";
            this.popmnuUtilNOT.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilOR
            // 
            this.popmnuUtilOR.Name = "popmnuUtilOR";
            this.popmnuUtilOR.Size = new System.Drawing.Size(118, 22);
            this.popmnuUtilOR.Text = "OR";
            this.popmnuUtilOR.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilXOR
            // 
            this.popmnuUtilXOR.Name = "popmnuUtilXOR";
            this.popmnuUtilXOR.Size = new System.Drawing.Size(118, 22);
            this.popmnuUtilXOR.Text = "XOR";
            this.popmnuUtilXOR.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilCompare
            // 
            this.popmnuUtilCompare.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.popmnuUtilCompareImages,
            this.popmnuUtilPrattMerit});
            this.popmnuUtilCompare.Name = "popmnuUtilCompare";
            this.popmnuUtilCompare.Size = new System.Drawing.Size(134, 22);
            this.popmnuUtilCompare.Text = "Compare";
            // 
            // popmnuUtilCompareImages
            // 
            this.popmnuUtilCompareImages.Name = "popmnuUtilCompareImages";
            this.popmnuUtilCompareImages.Size = new System.Drawing.Size(188, 22);
            this.popmnuUtilCompareImages.Text = "Compare Two Images";
            this.popmnuUtilCompareImages.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilPrattMerit
            // 
            this.popmnuUtilPrattMerit.Name = "popmnuUtilPrattMerit";
            this.popmnuUtilPrattMerit.Size = new System.Drawing.Size(188, 22);
            this.popmnuUtilPrattMerit.Text = "Pratt Figure of Merit";
            this.popmnuUtilPrattMerit.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilConvert
            // 
            this.popmnuUtilConvert.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.popmnuUtilBinThreshold,
            this.popmnuUtilDataType,
            this.popmnuUtilHalftone,
            this.popmnuUtilGrayLevelQuant,
            this.popmnuUtilGrayToBinary,
            this.popmnuUtilGrayToColor,
            this.popmnuUtilColorToGray,
            this.popmnuUtilColorSpace,
            this.popmnuUtilLabelImage});
            this.popmnuUtilConvert.Name = "popmnuUtilConvert";
            this.popmnuUtilConvert.Size = new System.Drawing.Size(134, 22);
            this.popmnuUtilConvert.Text = "Convert";
            // 
            // popmnuUtilBinThreshold
            // 
            this.popmnuUtilBinThreshold.Name = "popmnuUtilBinThreshold";
            this.popmnuUtilBinThreshold.Size = new System.Drawing.Size(215, 22);
            this.popmnuUtilBinThreshold.Text = "Binary Threshold";
            this.popmnuUtilBinThreshold.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilDataType
            // 
            this.popmnuUtilDataType.Name = "popmnuUtilDataType";
            this.popmnuUtilDataType.Size = new System.Drawing.Size(215, 22);
            this.popmnuUtilDataType.Text = "Data Type";
            this.popmnuUtilDataType.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilHalftone
            // 
            this.popmnuUtilHalftone.Name = "popmnuUtilHalftone";
            this.popmnuUtilHalftone.Size = new System.Drawing.Size(215, 22);
            this.popmnuUtilHalftone.Text = "Halftone";
            this.popmnuUtilHalftone.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilGrayLevelQuant
            // 
            this.popmnuUtilGrayLevelQuant.Name = "popmnuUtilGrayLevelQuant";
            this.popmnuUtilGrayLevelQuant.Size = new System.Drawing.Size(215, 22);
            this.popmnuUtilGrayLevelQuant.Text = "Gray Level Quantization";
            this.popmnuUtilGrayLevelQuant.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilGrayToBinary
            // 
            this.popmnuUtilGrayToBinary.Name = "popmnuUtilGrayToBinary";
            this.popmnuUtilGrayToBinary.Size = new System.Drawing.Size(215, 22);
            this.popmnuUtilGrayToBinary.Text = "Gray Code - Natural Binary";
            this.popmnuUtilGrayToBinary.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilGrayToColor
            // 
            this.popmnuUtilGrayToColor.Name = "popmnuUtilGrayToColor";
            this.popmnuUtilGrayToColor.Size = new System.Drawing.Size(215, 22);
            this.popmnuUtilGrayToColor.Text = "Gray to Color";
            this.popmnuUtilGrayToColor.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilColorToGray
            // 
            this.popmnuUtilColorToGray.Name = "popmnuUtilColorToGray";
            this.popmnuUtilColorToGray.Size = new System.Drawing.Size(215, 22);
            this.popmnuUtilColorToGray.Text = "Color to Gray";
            this.popmnuUtilColorToGray.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilColorSpace
            // 
            this.popmnuUtilColorSpace.Name = "popmnuUtilColorSpace";
            this.popmnuUtilColorSpace.Size = new System.Drawing.Size(215, 22);
            this.popmnuUtilColorSpace.Text = "Color Space";
            this.popmnuUtilColorSpace.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilLabelImage
            // 
            this.popmnuUtilLabelImage.Name = "popmnuUtilLabelImage";
            this.popmnuUtilLabelImage.Size = new System.Drawing.Size(215, 22);
            this.popmnuUtilLabelImage.Text = "Label Image";
            this.popmnuUtilLabelImage.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilCreate
            // 
            this.popmnuUtilCreate.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.popmnuUtilCheckerboard,
            this.popmnuUtilCircle,
            this.popmnuUtilEllipse,
            this.popmnuUtilLine,
            this.popmnuUtilRectangle,
            this.toolStripSeparator2,
            this.popmnuUtilCosineWave,
            this.popmnuUtilSineWave,
            this.popmnuUtilSquareWave,
            this.toolStripSeparator3,
            this.popmnuUtilExtractBand,
            this.popmnuUtilAssembleBands,
            this.toolStripSeparator4,
            this.popmnuUtilBlackImage,
            this.popmnuUtilAddNoise,
            this.toolStripSeparator5,
            this.popmnuUtilBorderMask,
            this.popmnuUtilBorderImage});
            this.popmnuUtilCreate.Name = "popmnuUtilCreate";
            this.popmnuUtilCreate.Size = new System.Drawing.Size(134, 22);
            this.popmnuUtilCreate.Text = "Create";
            // 
            // popmnuUtilCheckerboard
            // 
            this.popmnuUtilCheckerboard.Name = "popmnuUtilCheckerboard";
            this.popmnuUtilCheckerboard.Size = new System.Drawing.Size(160, 22);
            this.popmnuUtilCheckerboard.Text = "Checkerboard";
            this.popmnuUtilCheckerboard.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilCircle
            // 
            this.popmnuUtilCircle.Name = "popmnuUtilCircle";
            this.popmnuUtilCircle.Size = new System.Drawing.Size(160, 22);
            this.popmnuUtilCircle.Text = "Circle";
            this.popmnuUtilCircle.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilEllipse
            // 
            this.popmnuUtilEllipse.Name = "popmnuUtilEllipse";
            this.popmnuUtilEllipse.Size = new System.Drawing.Size(160, 22);
            this.popmnuUtilEllipse.Text = "Ellipse";
            this.popmnuUtilEllipse.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilLine
            // 
            this.popmnuUtilLine.Name = "popmnuUtilLine";
            this.popmnuUtilLine.Size = new System.Drawing.Size(160, 22);
            this.popmnuUtilLine.Text = "Line";
            this.popmnuUtilLine.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilRectangle
            // 
            this.popmnuUtilRectangle.Name = "popmnuUtilRectangle";
            this.popmnuUtilRectangle.Size = new System.Drawing.Size(160, 22);
            this.popmnuUtilRectangle.Text = "Rectangle";
            this.popmnuUtilRectangle.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(157, 6);
            // 
            // popmnuUtilCosineWave
            // 
            this.popmnuUtilCosineWave.Name = "popmnuUtilCosineWave";
            this.popmnuUtilCosineWave.Size = new System.Drawing.Size(160, 22);
            this.popmnuUtilCosineWave.Text = "Cosine Wave";
            this.popmnuUtilCosineWave.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilSineWave
            // 
            this.popmnuUtilSineWave.Name = "popmnuUtilSineWave";
            this.popmnuUtilSineWave.Size = new System.Drawing.Size(160, 22);
            this.popmnuUtilSineWave.Text = "Sine Wave";
            this.popmnuUtilSineWave.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilSquareWave
            // 
            this.popmnuUtilSquareWave.Name = "popmnuUtilSquareWave";
            this.popmnuUtilSquareWave.Size = new System.Drawing.Size(160, 22);
            this.popmnuUtilSquareWave.Text = "Square Wave";
            this.popmnuUtilSquareWave.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(157, 6);
            // 
            // popmnuUtilExtractBand
            // 
            this.popmnuUtilExtractBand.Name = "popmnuUtilExtractBand";
            this.popmnuUtilExtractBand.Size = new System.Drawing.Size(160, 22);
            this.popmnuUtilExtractBand.Text = "Extract Band";
            this.popmnuUtilExtractBand.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilAssembleBands
            // 
            this.popmnuUtilAssembleBands.Name = "popmnuUtilAssembleBands";
            this.popmnuUtilAssembleBands.Size = new System.Drawing.Size(160, 22);
            this.popmnuUtilAssembleBands.Text = "Assemble Bands";
            this.popmnuUtilAssembleBands.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(157, 6);
            // 
            // popmnuUtilBlackImage
            // 
            this.popmnuUtilBlackImage.Name = "popmnuUtilBlackImage";
            this.popmnuUtilBlackImage.Size = new System.Drawing.Size(160, 22);
            this.popmnuUtilBlackImage.Text = "Black Image";
            this.popmnuUtilBlackImage.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilAddNoise
            // 
            this.popmnuUtilAddNoise.Name = "popmnuUtilAddNoise";
            this.popmnuUtilAddNoise.Size = new System.Drawing.Size(160, 22);
            this.popmnuUtilAddNoise.Text = "Add Noise";
            this.popmnuUtilAddNoise.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(157, 6);
            // 
            // popmnuUtilBorderMask
            // 
            this.popmnuUtilBorderMask.Name = "popmnuUtilBorderMask";
            this.popmnuUtilBorderMask.Size = new System.Drawing.Size(160, 22);
            this.popmnuUtilBorderMask.Text = "Border Mask";
            this.popmnuUtilBorderMask.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilBorderImage
            // 
            this.popmnuUtilBorderImage.Name = "popmnuUtilBorderImage";
            this.popmnuUtilBorderImage.Size = new System.Drawing.Size(160, 22);
            this.popmnuUtilBorderImage.Text = "Border Image";
            this.popmnuUtilBorderImage.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilEnhance
            // 
            this.popmnuUtilEnhance.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.popmnuUtilBrightenDarken,
            this.popmnuUtilEdgeEnhancement,
            this.popmnuUtilHistogramEQ,
            this.popmnuUtilHistoStretch,
            this.popmnuUtilPseudocolor,
            this.popmnuUtilSharpen});
            this.popmnuUtilEnhance.Name = "popmnuUtilEnhance";
            this.popmnuUtilEnhance.Size = new System.Drawing.Size(134, 22);
            this.popmnuUtilEnhance.Text = "Enhance";
            // 
            // popmnuUtilBrightenDarken
            // 
            this.popmnuUtilBrightenDarken.Name = "popmnuUtilBrightenDarken";
            this.popmnuUtilBrightenDarken.Size = new System.Drawing.Size(197, 22);
            this.popmnuUtilBrightenDarken.Text = "Brighten/Darken";
            this.popmnuUtilBrightenDarken.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilEdgeEnhancement
            // 
            this.popmnuUtilEdgeEnhancement.Name = "popmnuUtilEdgeEnhancement";
            this.popmnuUtilEdgeEnhancement.Size = new System.Drawing.Size(197, 22);
            this.popmnuUtilEdgeEnhancement.Text = "Edge Enhancement";
            this.popmnuUtilEdgeEnhancement.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilHistogramEQ
            // 
            this.popmnuUtilHistogramEQ.Name = "popmnuUtilHistogramEQ";
            this.popmnuUtilHistogramEQ.Size = new System.Drawing.Size(197, 22);
            this.popmnuUtilHistogramEQ.Text = "Histogram Equalization";
            this.popmnuUtilHistogramEQ.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilHistoStretch
            // 
            this.popmnuUtilHistoStretch.Name = "popmnuUtilHistoStretch";
            this.popmnuUtilHistoStretch.Size = new System.Drawing.Size(197, 22);
            this.popmnuUtilHistoStretch.Text = "Histogram Stretch";
            this.popmnuUtilHistoStretch.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilPseudocolor
            // 
            this.popmnuUtilPseudocolor.Name = "popmnuUtilPseudocolor";
            this.popmnuUtilPseudocolor.Size = new System.Drawing.Size(197, 22);
            this.popmnuUtilPseudocolor.Text = "Pseudocolor";
            this.popmnuUtilPseudocolor.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilSharpen
            // 
            this.popmnuUtilSharpen.Name = "popmnuUtilSharpen";
            this.popmnuUtilSharpen.Size = new System.Drawing.Size(197, 22);
            this.popmnuUtilSharpen.Text = "Sharpening";
            this.popmnuUtilSharpen.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilFilter
            // 
            this.popmnuUtilFilter.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.popmnuUtilMean,
            this.popmnuUtilMedian,
            this.popmnuUtilLaplacian,
            this.popmnuUtilEmbossFilter,
            this.toolStripSeparator6,
            this.popmnuUtilSpecifyFilter,
            this.popmnuUtilSpecifyBlur});
            this.popmnuUtilFilter.Name = "popmnuUtilFilter";
            this.popmnuUtilFilter.Size = new System.Drawing.Size(134, 22);
            this.popmnuUtilFilter.Text = "Filter";
            // 
            // popmnuUtilMean
            // 
            this.popmnuUtilMean.Name = "popmnuUtilMean";
            this.popmnuUtilMean.Size = new System.Drawing.Size(157, 22);
            this.popmnuUtilMean.Text = "Mean";
            this.popmnuUtilMean.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilMedian
            // 
            this.popmnuUtilMedian.Name = "popmnuUtilMedian";
            this.popmnuUtilMedian.Size = new System.Drawing.Size(157, 22);
            this.popmnuUtilMedian.Text = "Median";
            this.popmnuUtilMedian.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilLaplacian
            // 
            this.popmnuUtilLaplacian.Name = "popmnuUtilLaplacian";
            this.popmnuUtilLaplacian.Size = new System.Drawing.Size(157, 22);
            this.popmnuUtilLaplacian.Text = "Laplacian Filter";
            this.popmnuUtilLaplacian.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilEmbossFilter
            // 
            this.popmnuUtilEmbossFilter.Name = "popmnuUtilEmbossFilter";
            this.popmnuUtilEmbossFilter.Size = new System.Drawing.Size(157, 22);
            this.popmnuUtilEmbossFilter.Text = "Difference Filter";
            this.popmnuUtilEmbossFilter.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // toolStripSeparator6
            // 
            this.toolStripSeparator6.Name = "toolStripSeparator6";
            this.toolStripSeparator6.Size = new System.Drawing.Size(154, 6);
            // 
            // popmnuUtilSpecifyFilter
            // 
            this.popmnuUtilSpecifyFilter.Name = "popmnuUtilSpecifyFilter";
            this.popmnuUtilSpecifyFilter.Size = new System.Drawing.Size(157, 22);
            this.popmnuUtilSpecifyFilter.Text = "Specify a Filter";
            this.popmnuUtilSpecifyFilter.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilSpecifyBlur
            // 
            this.popmnuUtilSpecifyBlur.Name = "popmnuUtilSpecifyBlur";
            this.popmnuUtilSpecifyBlur.Size = new System.Drawing.Size(157, 22);
            this.popmnuUtilSpecifyBlur.Text = "Specify a Blur";
            this.popmnuUtilSpecifyBlur.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilSize
            // 
            this.popmnuUtilSize.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.popmnuUtilCrop,
            this.popmnuUtilDoubleSize,
            this.popmnuUtilResize,
            this.popmnuUtilSpatialQuant});
            this.popmnuUtilSize.Name = "popmnuUtilSize";
            this.popmnuUtilSize.Size = new System.Drawing.Size(134, 22);
            this.popmnuUtilSize.Text = "Size";
            // 
            // popmnuUtilCrop
            // 
            this.popmnuUtilCrop.Name = "popmnuUtilCrop";
            this.popmnuUtilCrop.Size = new System.Drawing.Size(145, 22);
            this.popmnuUtilCrop.Text = "Crop";
            this.popmnuUtilCrop.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilDoubleSize
            // 
            this.popmnuUtilDoubleSize.Name = "popmnuUtilDoubleSize";
            this.popmnuUtilDoubleSize.Size = new System.Drawing.Size(145, 22);
            this.popmnuUtilDoubleSize.Text = "Double Size";
            this.popmnuUtilDoubleSize.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilResize
            // 
            this.popmnuUtilResize.Name = "popmnuUtilResize";
            this.popmnuUtilResize.Size = new System.Drawing.Size(145, 22);
            this.popmnuUtilResize.Text = "Resize";
            this.popmnuUtilResize.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilSpatialQuant
            // 
            this.popmnuUtilSpatialQuant.Name = "popmnuUtilSpatialQuant";
            this.popmnuUtilSpatialQuant.Size = new System.Drawing.Size(145, 22);
            this.popmnuUtilSpatialQuant.Text = "Spatial Quant";
            this.popmnuUtilSpatialQuant.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilStats
            // 
            this.popmnuUtilStats.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.popmnuUtilImageDataRange,
            this.popmnuUtilImageStatistics});
            this.popmnuUtilStats.Name = "popmnuUtilStats";
            this.popmnuUtilStats.Size = new System.Drawing.Size(134, 22);
            this.popmnuUtilStats.Text = "Stats";
            // 
            // popmnuUtilImageDataRange
            // 
            this.popmnuUtilImageDataRange.Name = "popmnuUtilImageDataRange";
            this.popmnuUtilImageDataRange.Size = new System.Drawing.Size(170, 22);
            this.popmnuUtilImageDataRange.Text = "Image Data Range";
            this.popmnuUtilImageDataRange.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // popmnuUtilImageStatistics
            // 
            this.popmnuUtilImageStatistics.Name = "popmnuUtilImageStatistics";
            this.popmnuUtilImageStatistics.Size = new System.Drawing.Size(170, 22);
            this.popmnuUtilImageStatistics.Text = "Image Statistics";
            this.popmnuUtilImageStatistics.Click += new System.EventHandler(this.mnuUtilities_Click);
            // 
            // statbarCVIP
            // 
            this.statbarCVIP.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statbarFileName,
            this.statbarColorFormat,
            this.statbarImageFormat,
            this.statbarDataFormat,
            this.statbarDataType,
            this.statbarDataRMin,
            this.statbarDataRMax,
            this.statbarBands,
            this.statbarWidth,
            this.statbarHeight});
            this.statbarCVIP.Location = new System.Drawing.Point(0, 719);
            this.statbarCVIP.Name = "statbarCVIP";
            this.statbarCVIP.ShowItemToolTips = true;
            this.statbarCVIP.Size = new System.Drawing.Size(953, 22);
            this.statbarCVIP.TabIndex = 4;
            // 
            // statbarFileName
            // 
            this.statbarFileName.AutoSize = false;
            this.statbarFileName.Name = "statbarFileName";
            this.statbarFileName.Size = new System.Drawing.Size(418, 17);
            this.statbarFileName.Spring = true;
            this.statbarFileName.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.statbarFileName.ToolTipText = "File Name";
            // 
            // statbarColorFormat
            // 
            this.statbarColorFormat.AutoSize = false;
            this.statbarColorFormat.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Left;
            this.statbarColorFormat.Name = "statbarColorFormat";
            this.statbarColorFormat.Size = new System.Drawing.Size(50, 17);
            this.statbarColorFormat.ToolTipText = "Color Format";
            // 
            // statbarImageFormat
            // 
            this.statbarImageFormat.AutoSize = false;
            this.statbarImageFormat.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Left;
            this.statbarImageFormat.Name = "statbarImageFormat";
            this.statbarImageFormat.Size = new System.Drawing.Size(50, 17);
            this.statbarImageFormat.ToolTipText = "Image Format";
            // 
            // statbarDataFormat
            // 
            this.statbarDataFormat.AutoSize = false;
            this.statbarDataFormat.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Left;
            this.statbarDataFormat.Name = "statbarDataFormat";
            this.statbarDataFormat.Size = new System.Drawing.Size(60, 17);
            this.statbarDataFormat.ToolTipText = "Data Format";
            this.statbarDataFormat.Click += new System.EventHandler(this.statbarDataFormat_Click);
            // 
            // statbarDataType
            // 
            this.statbarDataType.AutoSize = false;
            this.statbarDataType.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Left;
            this.statbarDataType.Name = "statbarDataType";
            this.statbarDataType.Size = new System.Drawing.Size(60, 17);
            this.statbarDataType.ToolTipText = "Data Type";
            // 
            // statbarDataRMin
            // 
            this.statbarDataRMin.AutoSize = false;
            this.statbarDataRMin.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Left;
            this.statbarDataRMin.Name = "statbarDataRMin";
            this.statbarDataRMin.Size = new System.Drawing.Size(75, 17);
            this.statbarDataRMin.ToolTipText = "Data Range Minimum";
            // 
            // statbarDataRMax
            // 
            this.statbarDataRMax.AutoSize = false;
            this.statbarDataRMax.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Left;
            this.statbarDataRMax.Name = "statbarDataRMax";
            this.statbarDataRMax.Size = new System.Drawing.Size(75, 17);
            this.statbarDataRMax.ToolTipText = "Data Range Maximum";
            // 
            // statbarBands
            // 
            this.statbarBands.AutoSize = false;
            this.statbarBands.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Left;
            this.statbarBands.Name = "statbarBands";
            this.statbarBands.Size = new System.Drawing.Size(50, 17);
            this.statbarBands.ToolTipText = "Number of Bands";
            // 
            // statbarWidth
            // 
            this.statbarWidth.AutoSize = false;
            this.statbarWidth.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Left;
            this.statbarWidth.Name = "statbarWidth";
            this.statbarWidth.Size = new System.Drawing.Size(50, 17);
            this.statbarWidth.ToolTipText = "Image Width";
            // 
            // statbarHeight
            // 
            this.statbarHeight.AutoSize = false;
            this.statbarHeight.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right)));
            this.statbarHeight.Name = "statbarHeight";
            this.statbarHeight.Size = new System.Drawing.Size(50, 17);
            this.statbarHeight.ToolTipText = "Image Height";
            // 
            // toolbarCVIP
            // 
            this.toolbarCVIP.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.toolbarCVIP.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tbOpen,
            this.tbSave,
            this.tbPrint,
            this.tbSep1,
            this.tbCamera,
            this.tbHistogram,
            this.tbSep2,
            this.tbRedBand,
            this.tbGreenBand,
            this.tbBlueBand,
            this.tbSep3,
            this.tbColLabel,
            this.tbColValue,
            this.tbRowLabel,
            this.tbRowValue,
            this.tbSep4,
            this.tbRLabel,
            this.tbRValue,
            this.tbGLabel,
            this.tbGValue,
            this.tbBLabel,
            this.tbBValue,
            this.tbFEPC,
            this.tbATAT});
            this.toolbarCVIP.Location = new System.Drawing.Point(0, 24);
            this.toolbarCVIP.Name = "toolbarCVIP";
            this.toolbarCVIP.Size = new System.Drawing.Size(953, 31);
            this.toolbarCVIP.TabIndex = 5;
            // 
            // tbOpen
            // 
            this.tbOpen.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbOpen.Image = ((System.Drawing.Image)(resources.GetObject("tbOpen.Image")));
            this.tbOpen.ImageTransparentColor = System.Drawing.Color.Fuchsia;
            this.tbOpen.Name = "tbOpen";
            this.tbOpen.Size = new System.Drawing.Size(28, 28);
            this.tbOpen.Text = "Open";
            this.tbOpen.Click += new System.EventHandler(this.mnuFileOpen_Click);
            // 
            // tbSave
            // 
            this.tbSave.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbSave.Enabled = false;
            this.tbSave.Image = ((System.Drawing.Image)(resources.GetObject("tbSave.Image")));
            this.tbSave.ImageTransparentColor = System.Drawing.Color.Fuchsia;
            this.tbSave.Name = "tbSave";
            this.tbSave.Size = new System.Drawing.Size(28, 28);
            this.tbSave.Text = "Save";
            this.tbSave.Click += new System.EventHandler(this.mnuFileSave_Click);
            // 
            // tbPrint
            // 
            this.tbPrint.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbPrint.Enabled = false;
            this.tbPrint.Image = ((System.Drawing.Image)(resources.GetObject("tbPrint.Image")));
            this.tbPrint.ImageTransparentColor = System.Drawing.Color.Fuchsia;
            this.tbPrint.Name = "tbPrint";
            this.tbPrint.Size = new System.Drawing.Size(28, 28);
            this.tbPrint.Text = "Print";
            this.tbPrint.Click += new System.EventHandler(this.mnuFilePrint_Click);
            // 
            // tbSep1
            // 
            this.tbSep1.AutoSize = false;
            this.tbSep1.Name = "tbSep1";
            this.tbSep1.Size = new System.Drawing.Size(10, 28);
            // 
            // tbCamera
            // 
            this.tbCamera.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbCamera.Image = ((System.Drawing.Image)(resources.GetObject("tbCamera.Image")));
            this.tbCamera.ImageTransparentColor = System.Drawing.Color.Silver;
            this.tbCamera.Name = "tbCamera";
            this.tbCamera.Size = new System.Drawing.Size(28, 28);
            this.tbCamera.Text = "Launch Camera";
            this.tbCamera.Click += new System.EventHandler(this.tbCamera_Click);
            // 
            // tbHistogram
            // 
            this.tbHistogram.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbHistogram.Enabled = false;
            this.tbHistogram.Image = ((System.Drawing.Image)(resources.GetObject("tbHistogram.Image")));
            this.tbHistogram.ImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(212)))), ((int)(((byte)(234)))), ((int)(((byte)(252)))));
            this.tbHistogram.Name = "tbHistogram";
            this.tbHistogram.Size = new System.Drawing.Size(28, 28);
            this.tbHistogram.Text = "Show Histogram";
            this.tbHistogram.Click += new System.EventHandler(this.mnuFileHistogram_Click);
            // 
            // tbSep2
            // 
            this.tbSep2.AutoSize = false;
            this.tbSep2.Name = "tbSep2";
            this.tbSep2.Size = new System.Drawing.Size(10, 28);
            // 
            // tbRedBand
            // 
            this.tbRedBand.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbRedBand.Enabled = false;
            this.tbRedBand.Image = ((System.Drawing.Image)(resources.GetObject("tbRedBand.Image")));
            this.tbRedBand.ImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(234)))), ((int)(((byte)(220)))));
            this.tbRedBand.Name = "tbRedBand";
            this.tbRedBand.Size = new System.Drawing.Size(28, 28);
            this.tbRedBand.Tag = "0";
            this.tbRedBand.Text = "Show red band";
            this.tbRedBand.Click += new System.EventHandler(this.mnuViewBand_Click);
            // 
            // tbGreenBand
            // 
            this.tbGreenBand.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbGreenBand.Enabled = false;
            this.tbGreenBand.Image = ((System.Drawing.Image)(resources.GetObject("tbGreenBand.Image")));
            this.tbGreenBand.ImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(234)))), ((int)(((byte)(220)))));
            this.tbGreenBand.Name = "tbGreenBand";
            this.tbGreenBand.Size = new System.Drawing.Size(28, 28);
            this.tbGreenBand.Tag = "1";
            this.tbGreenBand.Text = "Show green band";
            this.tbGreenBand.Click += new System.EventHandler(this.mnuViewBand_Click);
            // 
            // tbBlueBand
            // 
            this.tbBlueBand.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbBlueBand.Enabled = false;
            this.tbBlueBand.Image = ((System.Drawing.Image)(resources.GetObject("tbBlueBand.Image")));
            this.tbBlueBand.ImageTransparentColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(234)))), ((int)(((byte)(220)))));
            this.tbBlueBand.Name = "tbBlueBand";
            this.tbBlueBand.Size = new System.Drawing.Size(28, 28);
            this.tbBlueBand.Tag = "2";
            this.tbBlueBand.Text = "Show blue band";
            this.tbBlueBand.Click += new System.EventHandler(this.mnuViewBand_Click);
            // 
            // tbSep3
            // 
            this.tbSep3.AutoSize = false;
            this.tbSep3.Name = "tbSep3";
            this.tbSep3.Size = new System.Drawing.Size(50, 28);
            // 
            // tbColLabel
            // 
            this.tbColLabel.Name = "tbColLabel";
            this.tbColLabel.Size = new System.Drawing.Size(53, 28);
            this.tbColLabel.Text = "Column:";
            this.tbColLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.tbColLabel.ToolTipText = "Current column";
            // 
            // tbColValue
            // 
            this.tbColValue.AutoSize = false;
            this.tbColValue.Name = "tbColValue";
            this.tbColValue.Size = new System.Drawing.Size(40, 28);
            this.tbColValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.tbColValue.ToolTipText = "Current column";
            // 
            // tbRowLabel
            // 
            this.tbRowLabel.Name = "tbRowLabel";
            this.tbRowLabel.Size = new System.Drawing.Size(33, 28);
            this.tbRowLabel.Text = "Row:";
            this.tbRowLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.tbRowLabel.ToolTipText = "Current row";
            // 
            // tbRowValue
            // 
            this.tbRowValue.AutoSize = false;
            this.tbRowValue.Name = "tbRowValue";
            this.tbRowValue.Size = new System.Drawing.Size(40, 28);
            this.tbRowValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.tbRowValue.ToolTipText = "Current row";
            // 
            // tbSep4
            // 
            this.tbSep4.AutoSize = false;
            this.tbSep4.Name = "tbSep4";
            this.tbSep4.Size = new System.Drawing.Size(30, 28);
            // 
            // tbRLabel
            // 
            this.tbRLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbRLabel.ForeColor = System.Drawing.Color.Red;
            this.tbRLabel.Name = "tbRLabel";
            this.tbRLabel.Size = new System.Drawing.Size(20, 28);
            this.tbRLabel.Text = "R:";
            this.tbRLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.tbRLabel.ToolTipText = "Red pixel value";
            // 
            // tbRValue
            // 
            this.tbRValue.AutoSize = false;
            this.tbRValue.ForeColor = System.Drawing.Color.Red;
            this.tbRValue.Name = "tbRValue";
            this.tbRValue.Size = new System.Drawing.Size(85, 28);
            this.tbRValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.tbRValue.ToolTipText = "Red pixel value";
            // 
            // tbGLabel
            // 
            this.tbGLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbGLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.tbGLabel.Name = "tbGLabel";
            this.tbGLabel.Size = new System.Drawing.Size(20, 28);
            this.tbGLabel.Text = "G:";
            this.tbGLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.tbGLabel.ToolTipText = "Green pixel value";
            // 
            // tbGValue
            // 
            this.tbGValue.AutoSize = false;
            this.tbGValue.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.tbGValue.Name = "tbGValue";
            this.tbGValue.Size = new System.Drawing.Size(85, 28);
            this.tbGValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.tbGValue.ToolTipText = "Green pixel value";
            // 
            // tbBLabel
            // 
            this.tbBLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbBLabel.ForeColor = System.Drawing.Color.Blue;
            this.tbBLabel.Name = "tbBLabel";
            this.tbBLabel.Size = new System.Drawing.Size(19, 28);
            this.tbBLabel.Text = "B:";
            this.tbBLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.tbBLabel.ToolTipText = "Blue pixel value";
            // 
            // tbBValue
            // 
            this.tbBValue.AutoSize = false;
            this.tbBValue.ForeColor = System.Drawing.Color.Blue;
            this.tbBValue.Name = "tbBValue";
            this.tbBValue.Size = new System.Drawing.Size(85, 28);
            this.tbBValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.tbBValue.ToolTipText = "Blue pixel value";
            // 
            // tbFEPC
            // 
            this.tbFEPC.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.tbFEPC.BackColor = System.Drawing.Color.LimeGreen;
            this.tbFEPC.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.tbFEPC.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Bold);
            this.tbFEPC.ForeColor = System.Drawing.Color.White;
            this.tbFEPC.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tbFEPC.Margin = new System.Windows.Forms.Padding(0, 1, 5, 2);
            this.tbFEPC.Name = "tbFEPC";
            this.tbFEPC.Size = new System.Drawing.Size(74, 28);
            this.tbFEPC.Text = "CVIP-FEPC";
            this.tbFEPC.Click += new System.EventHandler(this.tbFEPC_Click);
            this.tbFEPC.MouseEnter += new System.EventHandler(this.tbATATFEPC_MouseEnter);
            this.tbFEPC.MouseLeave += new System.EventHandler(this.tbATATFEPC_MouseLeave);
            // 
            // tbATAT
            // 
            this.tbATAT.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.tbATAT.BackColor = System.Drawing.Color.LimeGreen;
            this.tbATAT.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.tbATAT.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Bold);
            this.tbATAT.ForeColor = System.Drawing.Color.White;
            this.tbATAT.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tbATAT.Margin = new System.Windows.Forms.Padding(0, 1, 1, 2);
            this.tbATAT.Name = "tbATAT";
            this.tbATAT.Size = new System.Drawing.Size(77, 18);
            this.tbATAT.Text = "CVIP-ATAT";
            this.tbATAT.Click += new System.EventHandler(this.tbATAT_Click);
            this.tbATAT.MouseEnter += new System.EventHandler(this.tbATATFEPC_MouseEnter);
            this.tbATAT.MouseLeave += new System.EventHandler(this.tbATATFEPC_MouseLeave);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(953, 741);
            this.ContextMenuStrip = this.popmnuUtilities;
            this.Controls.Add(this.pnlInfo);
            this.Controls.Add(this.pnlQueue);
            this.Controls.Add(this.toolbarCVIP);
            this.Controls.Add(this.mnuCVIP);
            this.Controls.Add(this.statbarCVIP);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.mnuCVIP;
            this.Name = "MainForm";
            this.Text = "CVIPtools for Windows - Southern Illinois University Edwardsville";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.mnuCVIP.ResumeLayout(false);
            this.mnuCVIP.PerformLayout();
            this.popmnuUtilities.ResumeLayout(false);
            this.statbarCVIP.ResumeLayout(false);
            this.statbarCVIP.PerformLayout();
            this.toolbarCVIP.ResumeLayout(false);
            this.toolbarCVIP.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.OpenFileDialog dlgFileOpen;
        private System.Windows.Forms.SaveFileDialog dlgFileSave;
        private System.Windows.Forms.MenuStrip mnuCVIP;
        private System.Windows.Forms.ToolStripMenuItem mnuFile;
        private System.Windows.Forms.ToolStripMenuItem mnuFileHistogram;
        private System.Windows.Forms.ToolStripMenuItem mnuFileSpectrum;
        private System.Windows.Forms.ToolStripMenuItem mnuFileFFTPhase;
        private System.Windows.Forms.ToolStripMenuItem mnuFileFFTMagnitude;
        private System.Windows.Forms.ToolStripMenuItem mnuFileLogRemapped;
        private System.Windows.Forms.ToolStripMenuItem mnuFileLogRemapAll;
        private System.Windows.Forms.ToolStripMenuItem mnuFileLogRemapRed;
        private System.Windows.Forms.ToolStripMenuItem mnuFileLogRemapGreen;
        private System.Windows.Forms.ToolStripMenuItem mnuFileLogRemapBlue;
        private System.Windows.Forms.ToolStripMenuItem mnuFileViewBand;
        private System.Windows.Forms.ToolStripMenuItem mnuFileViewRedBand;
        private System.Windows.Forms.ToolStripMenuItem mnuFileViewGreenBand;
        private System.Windows.Forms.ToolStripMenuItem mnuFileViewBlueBand;
        private System.Windows.Forms.ToolStripSeparator mnuFileSep1;
        private System.Windows.Forms.ToolStripMenuItem mnuFileOpen;
        private System.Windows.Forms.ToolStripSeparator mnuFileSep2;
        private System.Windows.Forms.ToolStripMenuItem mnuFileSave;
        private System.Windows.Forms.ToolStripSeparator mnuFileSep3;
        private System.Windows.Forms.ToolStripMenuItem mnuFilePrint;
        private System.Windows.Forms.ToolStripSeparator mnuFileSep4;
        private System.Windows.Forms.ToolStripMenuItem mnuFileExit;
        private System.Windows.Forms.ToolStripMenuItem mnuView;
        private System.Windows.Forms.ToolStripMenuItem mnuViewToolbar;
        private System.Windows.Forms.ToolStripMenuItem mnuViewImageQueue;
        private System.Windows.Forms.ToolStripMenuItem mnuViewInfoPanel;
        private System.Windows.Forms.ToolStripMenuItem mnuViewStatusBar;
        private System.Windows.Forms.ToolStripMenuItem mnuLongFileNames;
        private System.Windows.Forms.ToolStripSeparator mnuViewSep1;
        private System.Windows.Forms.ToolStripMenuItem mnuViewHistogram;
        private System.Windows.Forms.ToolStripMenuItem mnuViewSpectrum;
        private System.Windows.Forms.ToolStripMenuItem mnuViewFFTPhase;
        private System.Windows.Forms.ToolStripMenuItem mnuViewFFTMagnitude;
        private System.Windows.Forms.ToolStripMenuItem mnuViewLogRemapped;
        private System.Windows.Forms.ToolStripMenuItem mnuViewLogRemapAll;
        private System.Windows.Forms.ToolStripMenuItem mnuViewLogRemapRed;
        private System.Windows.Forms.ToolStripMenuItem mnuViewLogRemapGreen;
        private System.Windows.Forms.ToolStripMenuItem mnuViewLogRemapBlue;
        private System.Windows.Forms.ToolStripMenuItem mnuViewBand;
        private System.Windows.Forms.ToolStripMenuItem mnuViewBandRed;
        private System.Windows.Forms.ToolStripMenuItem mnuViewBandGreen;
        private System.Windows.Forms.ToolStripMenuItem mnuViewBandBlue;
        private System.Windows.Forms.ToolStripMenuItem mnuAnalysis;
        private System.Windows.Forms.ToolStripMenuItem mnuAnalysisPreprocessing;
        private System.Windows.Forms.ToolStripMenuItem mnuAnalysisGeometry;
        private System.Windows.Forms.ToolStripMenuItem mnuAnalysisEdgeDetect;
        private System.Windows.Forms.ToolStripMenuItem mnuAnalysisSegment;
        private System.Windows.Forms.ToolStripMenuItem mnuAnalysisTransforms;
        private System.Windows.Forms.ToolStripMenuItem mnuAnalysisFeatures;
        private System.Windows.Forms.ToolStripMenuItem mnuAnalysisClassify;
        private System.Windows.Forms.ToolStripMenuItem mnuEnhancement;
        private System.Windows.Forms.ToolStripMenuItem mnuEnhanceHistograms;
        private System.Windows.Forms.ToolStripMenuItem mnuEnhancePseudocolor;
        private System.Windows.Forms.ToolStripMenuItem mnuEnhanceSharpen;
        private System.Windows.Forms.ToolStripMenuItem mnuEnhanceSmooth;
        private System.Windows.Forms.ToolStripMenuItem mnuRestoration;
        private System.Windows.Forms.ToolStripMenuItem mnuRestoreNoise;
        private System.Windows.Forms.ToolStripMenuItem mnuRestoreSpatialFilters;
        private System.Windows.Forms.ToolStripMenuItem mnuRestoreFreqFilters;
        private System.Windows.Forms.ToolStripMenuItem mnuRestoreGeoTransforms;
        private System.Windows.Forms.ToolStripMenuItem mnuCompression;
        private System.Windows.Forms.ToolStripMenuItem mnuCompressPreprocess;
        private System.Windows.Forms.ToolStripMenuItem mnuCompressLossless;
        private System.Windows.Forms.ToolStripMenuItem mnuCompressLossy;
        private System.Windows.Forms.ToolStripMenuItem mnuCompressPostprocess;
        public System.Windows.Forms.ToolStripMenuItem mnuShowUtilities;
        public System.Windows.Forms.ToolStripMenuItem mnuUtilArithLogic;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilADD;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilSUB;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilMUL;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilDIV;
        private System.Windows.Forms.ToolStripSeparator mnuUtilArithSep1;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilAND;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilNOT;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilOR;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilXOR;
        public System.Windows.Forms.ToolStripMenuItem mnuUtilCompare;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilCompareImages;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilCompareError;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilPrattMerit;
        public System.Windows.Forms.ToolStripMenuItem mnuUtilConvert;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilBinThreshold;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilDataType;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilHalftone;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilGrayLevelQuant;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilGrayToBinary;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilGrayToColor;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilColorToGray;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilColorSpace;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilLabelImage;
        public System.Windows.Forms.ToolStripMenuItem mnuUtilCreate;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilCheckerboard;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilCircle;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilEllipse;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilLine;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilRectangle;
        private System.Windows.Forms.ToolStripSeparator mnuUtilCreateSep1;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilCosineWave;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilSineWave;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilSquareWave;
        private System.Windows.Forms.ToolStripSeparator mnuUtilCreateSep2;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilExtractBand;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilAssembleBands;
        private System.Windows.Forms.ToolStripSeparator mnuUtilCreateSep3;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilBlackImage;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilAddNoise;
        private System.Windows.Forms.ToolStripSeparator mnuUtilCreateSep4;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilBorderMask;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilBorderImage;
        public System.Windows.Forms.ToolStripMenuItem mnuUtilEnhance;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilBrightenDarken;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilEdgeEnhancement;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilHistogramEQ;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilHistoStretch;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilPseudocolor;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilSharpen;
        public System.Windows.Forms.ToolStripMenuItem mnuUtilFilter;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilMean;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilMedian;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilLaplacian;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilEmbossFilter;
        private System.Windows.Forms.ToolStripSeparator mnuUtilFiltSep1;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilSpecifyFilter;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilSpecifyBlur;
        public System.Windows.Forms.ToolStripMenuItem mnuUtilSize;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilCrop;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilDoubleSize;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilResize;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilSpatialQuant;
        public System.Windows.Forms.ToolStripMenuItem mnuUtilStats;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilImageDataRange;
        private System.Windows.Forms.ToolStripMenuItem mnuUtilImageStatistics;
        private System.Windows.Forms.ToolStripMenuItem mnuHelp;
        private System.Windows.Forms.ToolStripMenuItem mnuHelpContents;
        private System.Windows.Forms.ToolStripSeparator mnuHelpSep1;
        private System.Windows.Forms.ToolStripMenuItem mnuHelpAbout;
        private System.Windows.Forms.ToolStripMenuItem mnuCVIPtoolsWeblink;
        private InfoPanel pnlInfo;
        private ImageQueue pnlQueue;
        private System.Windows.Forms.ContextMenuStrip popmnuUtilities;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilArithLogic;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilADD;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilSUB;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilMUL;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilDIV;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilAND;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilNOT;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilOR;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilXOR;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilCompare;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilCompareImages;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilPrattMerit;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilConvert;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilBinThreshold;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilDataType;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilHalftone;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilGrayLevelQuant;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilGrayToBinary;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilGrayToColor;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilColorToGray;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilColorSpace;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilLabelImage;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilCreate;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilCheckerboard;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilCircle;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilEllipse;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilLine;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilRectangle;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilCosineWave;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilSineWave;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilSquareWave;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilExtractBand;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilAssembleBands;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilBlackImage;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilAddNoise;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilBorderMask;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilBorderImage;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilEnhance;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilBrightenDarken;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilEdgeEnhancement;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilHistogramEQ;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilHistoStretch;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilPseudocolor;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilSharpen;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilFilter;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilMean;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilMedian;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilLaplacian;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilEmbossFilter;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator6;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilSpecifyFilter;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilSpecifyBlur;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilSize;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilCrop;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilDoubleSize;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilResize;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilSpatialQuant;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilStats;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilImageDataRange;
        private System.Windows.Forms.ToolStripMenuItem popmnuUtilImageStatistics;
        private System.Windows.Forms.StatusStrip statbarCVIP;
        private NonBlinkingStatusLabel statbarFileName;
        private NonBlinkingStatusLabel statbarColorFormat;
        private NonBlinkingStatusLabel statbarImageFormat;
        private NonBlinkingStatusLabel statbarDataFormat;
        private NonBlinkingStatusLabel statbarDataType;
        private NonBlinkingStatusLabel statbarDataRMin;
        private NonBlinkingStatusLabel statbarDataRMax;
        private NonBlinkingStatusLabel statbarBands;
        private NonBlinkingStatusLabel statbarWidth;
        private NonBlinkingStatusLabel statbarHeight;
        private System.Windows.Forms.ToolStrip toolbarCVIP;
        private System.Windows.Forms.ToolStripButton tbOpen;
        private System.Windows.Forms.ToolStripButton tbSave;
        private System.Windows.Forms.ToolStripButton tbPrint;
        private System.Windows.Forms.ToolStripLabel tbSep1;
        private System.Windows.Forms.ToolStripButton tbCamera;
        private System.Windows.Forms.ToolStripButton tbHistogram;
        private System.Windows.Forms.ToolStripLabel tbSep2;
        private System.Windows.Forms.ToolStripButton tbRedBand;
        private System.Windows.Forms.ToolStripButton tbGreenBand;
        private System.Windows.Forms.ToolStripButton tbBlueBand;
        private System.Windows.Forms.ToolStripLabel tbSep3;
        private System.Windows.Forms.ToolStripLabel tbColLabel;
        private System.Windows.Forms.ToolStripLabel tbColValue;
        private System.Windows.Forms.ToolStripLabel tbRowLabel;
        private System.Windows.Forms.ToolStripLabel tbRowValue;
        private System.Windows.Forms.ToolStripLabel tbSep4;
        private System.Windows.Forms.ToolStripLabel tbRLabel;
        private System.Windows.Forms.ToolStripLabel tbRValue;
        private System.Windows.Forms.ToolStripLabel tbGLabel;
        private System.Windows.Forms.ToolStripLabel tbGValue;
        private System.Windows.Forms.ToolStripLabel tbBLabel;
        private System.Windows.Forms.ToolStripLabel tbBValue;
        private System.Windows.Forms.ToolStripButton tbFEPC;
        private System.Windows.Forms.ToolStripButton tbATAT;
    }
}
