////////////////////////////////////////
/// Copyright 2025 MinecraftSRDEV    ///
///                                  ///
/// Debug Bridge to SRLauncher       ///
////////////////////////////////////////

using System.Text;
using System.IO.Pipes;
using UnityEngine;

namespace SRDebugBridgeNamespace
{
    public class ComunicationBridge
    {
        public static void connectToLauncher()
        {
            SRDebugBridge.runningDebugger = false;
            client = new NamedPipeClientStream(".", "DebugBridge", PipeDirection.InOut);
            Debug.Log("Connecting to SRLauncher...");
            client.Connect(1000);
            if (client.IsConnected)
            {
                Debug.Log("Connected to SRLauncher");
                Debug.Log("Debug bridge v." + SRDebugBridge.VERSION.ToString());
                SRDebugBridge.runningDebugger = true;
            }
            else
            {
                Debug.Log("Unable to connect");
            }
        }

        public static void sendMessage(string message)
        {
            byte[] requestBytes = Encoding.UTF8.GetBytes(message);
            client.Write(requestBytes, 0, requestBytes.Length);
            client.Flush();
        }

        public static void disconnect()
        {
            try
            {
                client.Flush();
                client.Close();
                SRDebugBridge.runningDebugger = false;
            }
            catch (Exception) { }
        }

        public static NamedPipeClientStream client;
    }
    public class loggerClass : MonoBehaviour
    {
        private void OnEnable()
        {
            Application.logMessageReceived += HandleLog;
        }

        private void OnDisable()
        {
            Application.logMessageReceived -= HandleLog;
        }

        private void HandleLog(string logString, string stackTrace, LogType type)
        {
            string log = "";
            switch (type)
            {
                case LogType.Log:
                    {
                        log += "0";
                        break;
                    }
                case LogType.Warning:
                    {
                        log += "1";
                        break;
                    }
                case LogType.Error:
                    {
                        log += "2";
                        break;
                    }
                case LogType.Exception:
                    {
                        log += "3";
                        break;
                    }
                default:
                    {
                        log += "0";
                        break;
                    }
            }
            log += logString;
            ComunicationBridge.sendMessage(log);
        }

        private void OnApplicationQuit()
        {
            Debug.Log("Shutting down communication pipe");
            ComunicationBridge.disconnect();
        }
    }

    public class SRDebugBridge
    {
        public static void Load()
        {
            var go = new GameObject("DebugBridgeRoot");
            UnityEngine.Object.DontDestroyOnLoad(go);

            go.AddComponent<loggerClass>();
            go.AddComponent<DBGui>();

            Debug.Log("Debug bridge loaded successfully, Version: " + VERSION.ToString());

            ComunicationBridge.connectToLauncher();
        }

        public static void Unload()
        {
            Debug.Log("Unloading debug bridge");

            UnityEngine.Object.DestroyObject(SRDebugBridge.debugGui);
            UnityEngine.Object.DestroyObject(SRDebugBridge.loggingSystem);
        }

        private static GameObject debugGui;
        private static GameObject loggingSystem;

        public static string VERSION = "1.2";

        public static bool runningDebugger = false;
    }

    public class DBGui : MonoBehaviour
    {
        private void Update()
        {
            if(Input.GetKeyDown(KeyCode.Y))
            {
                show_UI = !show_UI;
            }
        }

        private void OnGUI()
        {
            int screenX = Screen.width;
            int screenY = Screen.height;

            string buttonText = "Debugging disabled";
            string tittleText = "SRLauncher Debug Bridge GUI v." + SRDebugBridge.VERSION;


            if (show_UI)
            {
                if (SRDebugBridge.runningDebugger == true)
                {
                    buttonText = "Stop debugging";
                }

                GUI.Box(new Rect(0, screenY - 200, 300, 200), tittleText);

                GUI.Label(new Rect(10, screenY - 150, 290, 20), "Comunication status: " + SRDebugBridge.runningDebugger.ToString());


                if (GUI.Button(new Rect(10, screenY - 25, 140, 20), buttonText))
                {
                    ComunicationBridge.disconnect();
                }

                if (GUI.Button(new Rect(10, screenY - 50, 140, 20), "Try to connect"))
                {
                    ComunicationBridge.connectToLauncher();
                }
            }
            else
            {
                GUI.Label(new Rect(10, screenY - 20, 400, 20), "Press Y to open debug bridge menu");
                return;
            }
        }

        private void OnLevelWasLoaded(int lvl)
        {
            level = lvl;
        }

        private int level = 0;

        private bool show_UI = false;
    }
}
