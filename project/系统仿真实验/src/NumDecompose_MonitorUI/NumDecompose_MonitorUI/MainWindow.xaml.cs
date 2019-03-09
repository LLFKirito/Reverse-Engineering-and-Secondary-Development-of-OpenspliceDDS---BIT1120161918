using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace NumDecompose_MonitorUI
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public static TextBox output1, output2, output3;
        RunProcess RP;
        public Thread thread;


        public MainWindow()
        {
            InitializeComponent();
            output1 = ___TextBox_NodeNum_Out;
            output2 = ___TextBox_SendSize_Out;
            output3 = ___TextBox_NodeInformation_Out;
            App.fi = new System.IO.FileInfo("NumDecompose_Monitor.exe");
            RP = new RunProcess(App.fi);
            thread = new Thread(RP.RunOrder);
            thread.Start();
        }

        private void TextBox_TextChanged(object sender, EventArgs e)
        {
            
            
        }
    }
}
