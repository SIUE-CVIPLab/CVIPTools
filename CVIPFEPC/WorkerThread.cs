/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: WorkerThread.cs
'           Description: Contains the code for
'                        CVIPFEPC WorkerThread class
'         Related Files: MainForm.cs
'   Initial Coding Date: January 2012
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Patrick Solt
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2012 Scott Umbaugh and SIUE
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
using System.ComponentModel;
using System.Text;
using System.Threading;

namespace CVIPFEPC
{
    public enum RunTestState
    {
        Ready,
        InitializingTest,
        ExtractFeatures,
        CalculateCentroid,
        NormalizeFeatures,
        CreateFeatureFiles,
        ClassifyTestTraining,
        ClassifyLeaveOneOut,
        ParseResults,
        CombinatoricTest,
        TestComplete
    }
    public class WorkEventArgs
    {
        private string msgError = null;
        private bool workCancelled = false;
        private bool workerReportsProgress = true;
        private object workResult = null;
        private Exception workException = null;
        private RunTestState workType = RunTestState.Ready;
        private WorkerThread workerThread = null;

        protected string msgStatus = null;
        protected int workProgressPercent = 0;
        protected ProgressChangedEventArgs argsProgress = null;
        protected WorkCompletedEventArgs argsCompleted = null;
        public WorkEventArgs() { }
        public WorkEventArgs(WorkerThread worker)
        {
            this.workerThread = worker;
        }
        public WorkEventArgs(RunTestState workType, WorkerThread worker)
            : this(worker)
        {
            this.workType = workType;
        }
        public object InvokeDelegate(Delegate del)
        {
            return this.workerThread.InvokeDelegate(del);
        }
        public object InvokeDelegate(Delegate del, object[] args)
        {
            return this.workerThread.InvokeDelegate(del, args);
        }
        public virtual void NewJob()
        {
            this.msgError = null;
            this.msgStatus = null;
            this.workCancelled = false;
            this.workException = null;
            this.workProgressPercent = 0;
            this.workResult = null;
        }
        public virtual void NewJob(RunTestState workType)
        {
            NewJob();
            this.workType = workType;
        }
        public void ReportProgress()
        {
            if (this.workerReportsProgress)
                this.workerThread.ReportProgress(this.ProgressChangedArgs);
        }
        public void ReportProgress(string status)
        {
            this.msgStatus = status;
            ReportProgress();
        }

        public string ErrorMsg
        {
            get { return this.msgError; }
            set { this.msgError = value; }
        }
        public Exception Exception
        {
            get { return this.workException; }
            set { this.workException = value; }
        }
        public virtual int ProgressPercentage
        {
            get { return this.workProgressPercent; }
            set { this.workProgressPercent = value; }
        }
        public string StatusMessage
        {
            get { return this.msgStatus; }
            set { this.msgStatus = value; }
        }
        public bool WorkCancelled
        {
            get { return this.workCancelled; }
            set { this.workCancelled = value; }
        }
        public bool WorkerReportsProgress
        {
            get { return this.workerReportsProgress; }
            set { this.workerReportsProgress = value; }
        }
        public object WorkResult
        {
            get { return this.workResult; }
            set { this.workResult = value; }
        }
        public virtual ProgressChangedEventArgs ProgressChangedArgs
        {
            get
            {
                if (this.argsProgress == null)
                    this.argsProgress = new ProgressChangedEventArgs(this);
                return this.argsProgress;
            }
        }
        public virtual WorkCompletedEventArgs WorkCompletedArgs
        {
            get
            {
                if (this.argsCompleted == null)
                    this.argsCompleted = new WorkCompletedEventArgs(this);
                return this.argsCompleted;
            }
        }
        public bool CancellationRequested { get { return this.workerThread.CancellationRequested; } }
        public RunTestState WorkType { get { return this.workType; } }
        public WorkerThread WorkerThread { get { return this.workerThread; } }
    }
    public class ProgressChangedEventArgs
    {
        protected WorkEventArgs argsWork = null;
        public ProgressChangedEventArgs() { }
        public ProgressChangedEventArgs(WorkEventArgs argsWork)
        {
            this.argsWork = argsWork;
        }
        public int ProgressPercentage { get { return this.argsWork.ProgressPercentage; } }
        public string StatusMessage { get { return this.argsWork.StatusMessage; } }
        public RunTestState WorkType { get { return this.argsWork.WorkType; } }
    }
    public class WorkCompletedEventArgs
    {
        protected WorkEventArgs argsWork = null;
        public WorkCompletedEventArgs() { }
        public WorkCompletedEventArgs(WorkEventArgs argsWork)
        {
            this.argsWork = argsWork;
        }
        public string ErrorMsg { get { return this.argsWork.ErrorMsg; } }
        public Exception Exception { get { return this.argsWork.Exception; } }
        public bool WorkCancelled { get { return this.argsWork.WorkCancelled; } }
        public RunTestState WorkType { get { return this.argsWork.WorkType; } }
        public object WorkResult { get { return this.argsWork.WorkResult; } }
    }
    public class MultiStepJobEventArgs : WorkEventArgs
    {
        private int stepsFinished = 0;
        private int stepsTotal = 0;
        public MultiStepJobEventArgs() { }
        public MultiStepJobEventArgs(WorkerThread worker)
            : base(worker) { }
        public MultiStepJobEventArgs(RunTestState jobType, WorkerThread worker)
            : base(jobType, worker) { }
        public MultiStepJobEventArgs(int numSteps, WorkerThread worker)
            : base(worker)
        {
            this.stepsTotal = numSteps;
        }
        public MultiStepJobEventArgs(int numSteps, RunTestState jobType, WorkerThread worker)
            : base(jobType, worker)
        {
            this.stepsTotal = numSteps;
        }
        public override void NewJob()
        {
            base.NewJob();
            this.stepsFinished = 0;
        }
        public override void NewJob(RunTestState jobType)
        {
            base.NewJob(jobType);
            this.stepsFinished = 0;
        }
        public void NewJob(int numSteps, RunTestState jobType)
        {
            NewJob(jobType);
            this.stepsTotal = numSteps;
        }
        public void JobComplete(int success) { this.stepsFinished = success; }
        public void StepComplete() { this.stepsFinished++; }
        public int StepsFinished { get { return this.stepsFinished; } }
        public int StepsTotal { get { return this.stepsTotal; } }
        public override int ProgressPercentage
        {
            get
            {
                int progress = 0;
                if (this.stepsTotal > 0)
                    progress = (int)((((double)this.stepsFinished / (double)this.stepsTotal) * 100.0) + 0.5);
                return progress;
            }
        }
        public override ProgressChangedEventArgs ProgressChangedArgs
        {
            get
            {
                if (this.argsProgress == null)
                    this.argsProgress = new MultiStepJobProgressChangedArgs(this);
                return this.argsProgress;
            }
        }
        public override WorkCompletedEventArgs WorkCompletedArgs
        {
            get
            {
                if (this.argsCompleted == null)
                    this.argsCompleted = new MultiStepJobCompletedArgs(this);
                return this.argsCompleted;
            }
        }
    }
    public class MultiStepJobProgressChangedArgs : ProgressChangedEventArgs
    {
        public MultiStepJobProgressChangedArgs() { }
        public MultiStepJobProgressChangedArgs(MultiStepJobEventArgs argsWork)
            : base((WorkEventArgs)argsWork) { }

        public int StepsFinished { get { return this.WorkArgs.StepsFinished; } }
        public int StepsTotal { get { return this.WorkArgs.StepsTotal; } }
        private MultiStepJobEventArgs WorkArgs { get { return this.argsWork as MultiStepJobEventArgs; } }
    }
    public class MultiStepJobCompletedArgs : WorkCompletedEventArgs
    {
        public MultiStepJobCompletedArgs() { }
        public MultiStepJobCompletedArgs(MultiStepJobEventArgs argsWork)
            : base((WorkEventArgs)argsWork) { }
        private MultiStepJobEventArgs WorkArgs { get { return this.argsWork as MultiStepJobEventArgs; } }
    }

    public delegate void DoWorkHandler(WorkEventArgs e);
    public delegate void ProgressChangedHandler(ProgressChangedEventArgs e);
    public delegate void WorkCompletedHandler(WorkCompletedEventArgs e);

    public class WorkerThread
    {
        private static Dictionary<RunTestState, string> statusStrings = null;
        public static string LookupString(RunTestState state) { return WorkerThread.statusStrings[state]; }
        static WorkerThread()
        {
            WorkerThread.statusStrings = new Dictionary<RunTestState, string>();
            WorkerThread.statusStrings.Add(RunTestState.Ready, "Ready");
            WorkerThread.statusStrings.Add(RunTestState.InitializingTest, "Initializing test objects");
            WorkerThread.statusStrings.Add(RunTestState.ExtractFeatures, "Extracting features");
            WorkerThread.statusStrings.Add(RunTestState.CalculateCentroid, "Calculating centroids");
            WorkerThread.statusStrings.Add(RunTestState.NormalizeFeatures, "Normalizing features");
            WorkerThread.statusStrings.Add(RunTestState.CreateFeatureFiles, "Creating feature files");
            WorkerThread.statusStrings.Add(RunTestState.ClassifyTestTraining, "Running classifier");
            WorkerThread.statusStrings.Add(RunTestState.ClassifyLeaveOneOut, "Leave-One-Out test");
            WorkerThread.statusStrings.Add(RunTestState.ParseResults, "Parsing result files");
            WorkerThread.statusStrings.Add(RunTestState.CombinatoricTest, "Running combinatoric test");
            WorkerThread.statusStrings.Add(RunTestState.TestComplete, "Test complete");
        }

        public event DoWorkHandler DoWork;
        public event ProgressChangedHandler ProgressChanged;
        public event WorkCompletedHandler WorkCompleted;

        private bool bAbortRequested = false;
        private bool bCancellationRequested = false;
        private bool bIsBusy = false;
        private object locker = new object();

        private AutoResetEvent arEvntStartWork = new AutoResetEvent(false);
        private Queue<WorkEventArgs> qWorkPending = new Queue<WorkEventArgs>();
        private Thread thrdWorker = null;
        private WorkEventArgs argsWork = null;

        public WorkerThread()
        {
            this.thrdWorker = new Thread(this.WorkerThreadStart);
        }
        public WorkerThread(DoWorkHandler handler)
            : this()
        {
            this.DoWork += handler;
        }
        public void Abort()
        {
            this.thrdWorker.Abort();
        }
        public object InvokeDelegate(Delegate del)
        {
            return InvokeDelegate(del, null);
        }
        public object InvokeDelegate(Delegate del, object[] args)
        {
            object ret = null;
            ISynchronizeInvoke synchronizer = del.Target as ISynchronizeInvoke;
            if ((synchronizer == null) || !synchronizer.InvokeRequired)
            {
                ret = del.DynamicInvoke(args);
            }
            else
            {
                try { ret = synchronizer.Invoke(del, args); }
                catch { }
            }
            return ret;
        }
        public bool Join(int millisecondsTimeout)
        {
            return this.thrdWorker.Join(millisecondsTimeout);
        }
        private void ProcessDelegate(Delegate del, params object[] args)
        {
            Delegate temp = del;
            if (temp != null)
            {
                Delegate[] delegates = temp.GetInvocationList();
                foreach (Delegate handler in delegates)
                    InvokeDelegate(handler, args);
            }
        }
        public void ReportProgress(ProgressChangedEventArgs argsProgress)
        {
            ProgressChangedHandler progressChanged = this.ProgressChanged;
            if (progressChanged != null)
                ProcessDelegate(progressChanged, argsProgress);
        }
        public void RequestAbort()
        {
            lock (locker)
            {
                this.bAbortRequested = true;
                this.bCancellationRequested = true;
            }
            this.arEvntStartWork.Set();
        }
        public void RequestCancel()
        {
            lock (locker)
            {
                if (this.bIsBusy)
                    this.bCancellationRequested = true;
            }
        }
        public void QueueWork()
        {
            QueueWork(new WorkEventArgs(this));
        }
        public void QueueWork(WorkEventArgs argsWork)
        {
            lock (locker)
            {
                if (this.bIsBusy)
                {
                    this.qWorkPending.Enqueue(argsWork);
                }
                else
                {
                    this.argsWork = argsWork;
                    this.arEvntStartWork.Set();
                }
            }
        }
        public void SetApartmentState(ApartmentState state)
        {
            this.thrdWorker.SetApartmentState(state);
        }
        public void StartThread()
        {
            this.thrdWorker.Start();
        }
        private void WorkerThreadStart()
        {
            while (true)
            {
                this.arEvntStartWork.WaitOne();
                lock (locker)
                {
                    this.bCancellationRequested = false;
                    this.bIsBusy = true;
                }
                if (this.AbortRequested)
                    return;

                DoWorkHandler doWork = this.DoWork;
                if (doWork != null)
                {
                    try
                    {
                        doWork(this.argsWork);
                    }
                    catch (Exception e) { this.argsWork.Exception = e; }

                    if (this.AbortRequested)
                        return;

                    WorkCompletedHandler workCompleted = this.WorkCompleted;
                    if (workCompleted != null)
                        ProcessDelegate(workCompleted, this.argsWork.WorkCompletedArgs);
                }
                lock (locker)
                {
                    this.argsWork = null;
                    this.bIsBusy = (this.qWorkPending.Count > 0);
                    if (this.bIsBusy)
                    {
                        this.argsWork = this.qWorkPending.Dequeue();
                        this.arEvntStartWork.Set();
                    }
                }
            }
        }

        public bool AbortRequested
        {
            get { lock (locker) { return this.bAbortRequested; } }
            protected set { lock (locker) { this.bAbortRequested = value; } }
        }
        public bool CancellationRequested
        {
            get { lock (locker) { return this.bCancellationRequested; } }
            protected set { lock (locker) { this.bCancellationRequested = value; } }
        }
        public bool IsBusy
        {
            get { lock (locker) { return this.bIsBusy; } }
            protected set { lock (locker) { this.bIsBusy = value; } }
        }
        public bool IsBackground
        {
            get { return this.thrdWorker.IsBackground; }
            set { this.thrdWorker.IsBackground = value; }
        }
        public string Name
        {
            get { return this.thrdWorker.Name; }
            set { this.thrdWorker.Name = value; }
        }
        public ThreadPriority Priority
        {
            get { return this.thrdWorker.Priority; }
            set { this.thrdWorker.Priority = value; }
        }
    }
}
