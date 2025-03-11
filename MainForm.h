#pragma once
#include "Ball.h"

namespace OOP2 {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class MainForm : public Form {
    private:
        Ball* ball;
        Timer^ moveTimer;
        Timer^ drawTimer;
        PictureBox^ frame;

    public:
        MainForm() {
            InitializeComponent();
            ball = new Ball(frame->Width, frame->Height);

            moveTimer = gcnew Timer();
            moveTimer->Interval = 20;
            moveTimer->Tick += gcnew EventHandler(this, &MainForm::OnMoveTimer);
            moveTimer->Start();

            drawTimer = gcnew Timer();
            drawTimer->Interval = 10;
            drawTimer->Tick += gcnew EventHandler(this, &MainForm::OnDrawTimer);
            drawTimer->Start();
        }

        void OnMoveTimer(Object^ sender, EventArgs^ e) {
            ball->move();
        }

        void OnDrawTimer(Object^ sender, EventArgs^ e) {
            frame->Invalidate();
        }

    protected:
        ~MainForm() {
            delete ball;
        }

    private:
        void InitializeComponent() {
            this->frame = gcnew PictureBox();
            this->SuspendLayout();

            // PictureBox
            this->frame->Location = Point(10, 10);
            this->frame->Size = System::Drawing::Size(500, 400);
            this->frame->BackColor = Color::White;
            this->frame->BorderStyle = BorderStyle::FixedSingle;
            this->frame->Paint += gcnew PaintEventHandler(this, &MainForm::frame_Paint);

            // Form
            this->Controls->Add(this->frame);
            this->Text = L"PopBall v2: Moving Ball";
            this->ClientSize = System::Drawing::Size(520, 420);
            this->ResumeLayout(false);
        }

        void frame_Paint(Object^ sender, PaintEventArgs^ e) {
            Graphics^ g = e->Graphics;
            g->Clear(Color::White);
            ball->draw(g);
        }
    };
}
