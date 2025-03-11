#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

int main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    OOP2::MainForm^ form = gcnew OOP2::MainForm();
    Application::Run(form);

    return 0;
}
