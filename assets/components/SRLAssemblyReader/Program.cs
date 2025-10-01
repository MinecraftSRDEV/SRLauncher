using System;
using System.IO;
using System.Reflection;

class Program
{
    static void Main(string[] args)
    {
        string asmPath = args[0];
        if (!File.Exists(asmPath))
        {
            Console.WriteLine("404");
            return;
        }

        try
        {
            Assembly asm = Assembly.LoadFrom(asmPath);

            foreach (AssemblyName reference in asm.GetReferencedAssemblies())
            {
                Console.WriteLine(reference.FullName);
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
        }
    }
}
