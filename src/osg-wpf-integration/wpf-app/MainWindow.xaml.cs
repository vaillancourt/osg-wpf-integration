using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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

using System.Runtime.InteropServices;


namespace wpf_app
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        [DllImport("osg-app-wrapper.dll", CharSet = CharSet.Auto)]
        public static extern void osgWpf_Init(IntPtr aHwnd);

        [DllImport("osg-app-wrapper.dll", CharSet = CharSet.Auto)]
        public static extern void osgWpf_ShutDown();

        [DllImport("osg-app-wrapper.dll", CharSet = CharSet.Auto)]
        public static extern void osgWpf_Frame();

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            textBoxLog.Text = "bla bla bla\nblablabal";
            
            osgWpf_Init(myWFH.Child.Handle);
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            osgWpf_ShutDown();
        }

        private void myControl_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
        {
            //osgWpf_Frame();
        }
    }
}
