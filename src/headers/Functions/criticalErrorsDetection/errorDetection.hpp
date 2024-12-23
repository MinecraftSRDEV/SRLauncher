void signalHandler(int signal) {
    std::string errorMsg = "CRITICAL ERROR: " + std::to_string(signal);
    MessageBoxA(NULL, errorMsg.c_str(), "CRITICAL ERROR!", MB_ICONERROR | MB_OK);
    std::exit(signal);
}

LONG WINAPI exceptionHandler(EXCEPTION_POINTERS* exceptionInfo) {
    std::cerr << "Wykryto wyjątek SEH! Kod wyjątku: " << std::hex << exceptionInfo->ExceptionRecord->ExceptionCode << std::endl;

    if (exceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION) {
        std::cerr << "Błąd: Naruszenie ochrony pamięci (SIGSEGV odpowiednik)." << std::endl;
    }

    MessageBoxA(NULL, "CRITICAL ERROR", "CRITICAL ERROR!", MB_ICONERROR | MB_OK);

    std::exit(EXIT_FAILURE);
}

void addErrorHandlers()
{
    std::signal(SIGABRT, signalHandler); // abort()
    SetUnhandledExceptionFilter(exceptionHandler); // SEH
}

void generateArtificialMemoryError()
{
    int* ptr = nullptr;
    *ptr = 42;
}