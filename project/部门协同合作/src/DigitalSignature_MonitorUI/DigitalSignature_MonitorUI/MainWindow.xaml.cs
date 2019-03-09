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

namespace DigitalSignature_MonitorUI
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public static TextBox output;
        RunProcess RP;
        public Thread thread;

        public MainWindow()
        {
            InitializeComponent();
            output = ___TextBox_Out;
            App.fi = new System.IO.FileInfo("DigitalSignature_Monitor.exe");
            RP = new RunProcess(App.fi);
            thread = new Thread(RP.RunOrder);
            thread.Start();
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
    }
}
