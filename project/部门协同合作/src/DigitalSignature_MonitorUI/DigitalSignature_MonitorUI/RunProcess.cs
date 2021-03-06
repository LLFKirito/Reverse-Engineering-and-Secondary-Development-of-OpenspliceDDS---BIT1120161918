﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;

namespace DigitalSignature_MonitorUI
{
    //管道通信，与OpenCV实现的傅里叶变换程序进行通信
    class ReadErrorThread
    {
        System.Threading.Thread m_Thread;
        System.Diagnostics.Process m_Process;
        String m_Error;
        bool m_HasExisted;
        object m_LockObj = new object();

        public String Error
        {
            get
            {
                return m_Error;
            }
        }

        public bool HasExisted
        {
            get
            {
                lock (m_LockObj)
                {
                    return m_HasExisted;
                }
            }

            set
            {
                lock (m_LockObj)
                {
                    m_HasExisted = value;
                }
            }
        }

        private void ReadError()
        {
            StringBuilder strError = new StringBuilder();
            while (!m_Process.HasExited)
            {
                strError.Append(m_Process.StandardError.ReadLine());
            }

            strError.Append(m_Process.StandardError.ReadToEnd());

            m_Error = strError.ToString();
            HasExisted = true;
        }

        public ReadErrorThread(System.Diagnostics.Process p)
        {
            HasExisted = false;
            m_Error = "";
            m_Process = p;
            m_Thread = new Thread(new ThreadStart(ReadError));
            m_Thread.Start();
        }

    }
    class RunProcess
    {
        public delegate void delefun();
        private String m_Error;
        private String m_Output;
        private FileInfo fi;
        System.Diagnostics.Process p = new System.Diagnostics.Process();
        public RunProcess(FileInfo fi)
        {
            this.fi = fi;
        }

        public String Error
        {
            get
            {
                return m_Error;
            }
        }

        public String Output
        {
            get
            {
                return m_Output;
            }
        }
        public bool HasError
        {
            get
            {
                return m_Error != "" && m_Error != null;
            }
        }


        string outstr;
        public void RunOrder()
        {
            StringBuilder outputStr = new StringBuilder();

            try
            {
                Microsoft.Win32.RegistryKey key;
                key = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(@"software\microsoft\PCHealth\ErrorReporting\", true);
                int doReport = (int)key.GetValue("DoReport");

                if (doReport != 0)
                {
                    key.SetValue("DoReport", 0);
                }

                int showUI = (int)key.GetValue("ShowUI");
                if (showUI != 0)
                {
                    key.SetValue("ShowUI", 0);
                }
            }
            catch
            {
            }


            m_Error = "";
            m_Output = "";
            try
            {
                //前面都不用管。
                System.Diagnostics.Process p = new System.Diagnostics.Process();

                p.StartInfo.FileName = this.fi.FullName;
                p.StartInfo.UseShellExecute = false;
                p.StartInfo.RedirectStandardInput = true;
                p.StartInfo.RedirectStandardOutput = true;
                p.StartInfo.RedirectStandardError = true;
                p.StartInfo.CreateNoWindow = true;

                p.Start();
                ReadErrorThread readErrorThread = new ReadErrorThread(p);
                while (!readErrorThread.HasExisted)
                {
                    outstr = p.StandardOutput.ReadLine();
                    System.Windows.Application.Current.Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new delefun(Put_Output));
                    Thread.Sleep(1);
                }

                m_Error = readErrorThread.Error;
                m_Output = outputStr.ToString();
            }
            catch (Exception e)
            {
                m_Error = e.Message;
            }
        }
        public void Put_Output()
        {
            outstr += "\n";
            MainWindow.output.AppendText(outstr);
            MainWindow.output.ScrollToEnd();
        }
    }
}
