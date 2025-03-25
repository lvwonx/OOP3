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
        bool tracking = false;
        bool pushing = false;
        int x1, y1, x2, y2, nt;

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
            if (pushing) nt++;
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

            this->frame->Location = Point(10, 10);
            this->frame->Size = System::Drawing::Size(500, 400);
            this->frame->BackColor = Color::White;
            this->frame->BorderStyle = BorderStyle::FixedSingle;
            this->frame->Paint += gcnew PaintEventHandler(this, &MainForm::frame_Paint);
            this->frame->MouseDown += gcnew MouseEventHandler(this, &MainForm::OnMouseDown);
            this->frame->MouseUp += gcnew MouseEventHandler(this, &MainForm::OnMouseUp);
            this->frame->MouseMove += gcnew MouseEventHandler(this, &MainForm::OnMouseMove);
            this->MouseWheel += gcnew MouseEventHandler(this, &MainForm::OnMouseWheel);

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

        void OnMouseWheel(Object^ sender, MouseEventArgs^ e) {
            float factor = (e->Delta > 0) ? 1.1f : 0.9f;
            ball->scaleSpeed(factor);
        }

        void OnMouseDown(Object^ sender, MouseEventArgs^ e) {
            if (e->Button == System::Windows::Forms::MouseButtons::Right) {
                tracking = true;
                ball->followTo(e->X, e->Y);
            }
            else if (e->Button == System::Windows::Forms::MouseButtons::Left) {
                pushing = true;
                x1 = e->X;
                y1 = e->Y;
                nt = 0;
            }
        }

        void OnMouseUp(Object^ sender, MouseEventArgs^ e) {
            if (e->Button == System::Windows::Forms::MouseButtons::Right) {
                tracking = false;
            }
            else if (e->Button == System::Windows::Forms::MouseButtons::Left) {
                pushing = false;
                x2 = e->X;
                y2 = e->Y;
                if (nt > 0) {
                    ball->setSpeed((x2 - x1) / (float)nt, (y2 - y1) / (float)nt);
                }
            }
            else if (e->Button == Windows::Forms::MouseButtons::Middle) {
                ball->togglePause();
            }
        }

        void OnMouseMove(Object^ sender, MouseEventArgs^ e) {
            if (tracking) {
                ball->followTo(e->X, e->Y);
            }
        }
    };
}
