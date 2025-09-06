using System;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text.Json;

class Program
{
    public class ModMeta
    {
        public bool hasOnload { get; set; }
        public bool hasOnUnload { get; set; }
        public bool conSRML { get; set; }
    }

    static void Main(string[] args)
    {
        string dllPath = args[0];

        Assembly asm = Assembly.LoadFrom(dllPath);

        var metaOut = new ModMeta
        {
            hasOnload = hasMethod(asm, "OnLoad"),
            hasOnUnload = hasMethod(asm, "OnUnload"),

            conSRML = usesRef(asm, "SRML")
        };

        Console.WriteLine(JsonSerializer.Serialize(metaOut));
    }

    private static bool hasMethod(Assembly asm, string methodName)
    {
        try
        {
            return asm.GetTypes()
                .SelectMany(t => t.GetMethods(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Static))
                .Any(m => m.Name == methodName);
        }
        catch (ReflectionTypeLoadException ex)
        {
            var loadedTypes = ex.Types.Where(t => t != null);

            return loadedTypes
                .SelectMany(t => t.GetMethods(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Static))
                .Any(m => m.Name == methodName);
        }
    }

    private static bool usesRef(Assembly asm, string name)
    {
        var references = asm.GetReferencedAssemblies();

        foreach (var reference in references)
        {
        }

        return references.Any(r => r.Name.Equals(name, StringComparison.OrdinalIgnoreCase));
    }
}
