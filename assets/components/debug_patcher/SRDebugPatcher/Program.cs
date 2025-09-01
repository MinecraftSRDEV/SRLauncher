using Mono.Cecil;
using Mono.Cecil.Cil;
using System;
using System.IO;
using System.Linq;
using System.Reflection.Emit;
using System.Reflection.Metadata;

class SRPatcher
{
    // Usge: AssemblyPath bridgePath
    static void Main(string[] args)
    {
        if (args.Length < 1)
        {
            return;
        }

        string asmPath = args[0];
        string bridgePath = args[1];
        string backupPath = asmPath + ".bak";

        Console.WriteLine("amsPath: {0}", asmPath);

        if (!File.Exists(asmPath))
        {
            Console.WriteLine("Nie znaleziono Assembly-CSharp.dll!");
            return;
        }

        if (!File.Exists(backupPath))
            File.Copy(asmPath, backupPath);

        var resolver = new DefaultAssemblyResolver();
        resolver.AddSearchDirectory(Path.GetDirectoryName(asmPath));

        var readerParams = new ReaderParameters { AssemblyResolver = resolver };
        var assembly = Mono.Cecil.AssemblyDefinition.ReadAssembly(asmPath, readerParams);
        var module = assembly.MainModule;


        var srBridgeDll = Path.Combine(Path.GetDirectoryName(asmPath), "DebugBridge.dll");
        if (!File.Exists(srBridgeDll))
        {
            Console.WriteLine("Brak DebugBridge.dll w katalogu Managed!");
            return;
        }

        var bridgeAsm = Mono.Cecil.AssemblyDefinition.ReadAssembly(srBridgeDll);
        var bridgeType = bridgeAsm.MainModule.Types.First(t => t.Name == "SRDebugBridge");
        var onLoad = bridgeType.Methods.First(m => m.Name == "Load");

        var imported = module.ImportReference(onLoad);

        // Szukamy punktu startowego gry (np. SceneContext.Awake)
        var targetType = module.Types.First(t => t.Name == "GameContext");
        var targetMethod = targetType.Methods.First(m => m.Name == "Awake");

        var il = targetMethod.Body.GetILProcessor();

        // Wstrzyknięcie na początek metody
        var firstInstr = targetMethod.Body.Instructions[0];
        il.InsertBefore(firstInstr, il.Create(Mono.Cecil.Cil.OpCodes.Call, imported));

        assembly.Write(asmPath + "_patched");

        Console.WriteLine("Patch zakończony sukcesem!");
    }
}
