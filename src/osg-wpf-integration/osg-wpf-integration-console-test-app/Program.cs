// See https://aka.ms/new-console-template for more information

// https://docs.microsoft.com/en-us/dotnet/api/system.runtime.interopservices.dllimportattribute?redirectedfrom=MSDN&view=net-6.0



using System;
using System.Runtime.InteropServices;

namespace MyApp // Note: actual namespace depends on the project name.
{
    internal class Program
    {
        [DllImport("osg-app-wrapper.dll", CharSet = CharSet.Auto)]
        public static extern UInt64 fibonacci_return42();

        [DllImport("osg-app-wrapper.dll", CharSet = CharSet.Auto)]
        public static extern void fibonacci_init(UInt64 a, UInt64 b);

        [DllImport("osg-app-wrapper.dll", CharSet = CharSet.Auto)]
        public static extern bool fibonacci_next();

        [DllImport("osg-app-wrapper.dll", CharSet = CharSet.Auto)]
        public static extern long fibonacci_current();

        [DllImport("osg-app-wrapper.dll", CharSet = CharSet.Auto)]
        public static extern uint fibonacci_index();


        static void Main(string[] args)
        {
            //Console.WriteLine(fibonacci_return42());
            fibonacci_init(1, 1);
            fibonacci_next();
            Console.WriteLine(fibonacci_current());
            fibonacci_next();
            Console.WriteLine(fibonacci_current());
            fibonacci_next();
            Console.WriteLine(fibonacci_current());
            fibonacci_next();
            Console.WriteLine(fibonacci_current());
            fibonacci_next();
            Console.WriteLine(fibonacci_current());
            Console.WriteLine(fibonacci_index());
        }
    }
}

