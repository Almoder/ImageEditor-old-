#include "MainForm.h"

namespace Lab1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	public ref class Dialog : public System::Windows::Forms::Form
	{
	private: int t, b0, b1;
	private: double c, g;
	public:  int type;
	private: MainForm^ ptr;
	public:
		Dialog(MainForm^ ptr, int type)	{
			InitializeComponent(type);
			t = 0; b0 = 0; b1 = 0;
			c = 1.0; g = 1.0;
			this->ptr = ptr;
			this->type = type;
		}

	protected:
		~Dialog() {
			ptr->bkpPictureBox();
			if (components) {
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::TrackBar^  trackBar2;
	private: System::Windows::Forms::TrackBar^  trackBar3;

	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code

			 void InitializeComponent(int type)
			 {
				 switch (type) {
				 case 1:
					 this->label1 = (gcnew System::Windows::Forms::Label());
					 this->label2 = (gcnew System::Windows::Forms::Label());
					 this->label3 = (gcnew System::Windows::Forms::Label());
					 this->textBox1 = (gcnew System::Windows::Forms::TextBox());
					 this->textBox2 = (gcnew System::Windows::Forms::TextBox());
					 this->textBox3 = (gcnew System::Windows::Forms::TextBox());
					 this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
					 this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
					 this->trackBar3 = (gcnew System::Windows::Forms::TrackBar());
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->BeginInit();
					 this->SuspendLayout();
					 // 
					 // label1
					 // 
					 this->label1->AutoSize = true;
					 this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 this->label1->ForeColor = System::Drawing::SystemColors::Window;
					 this->label1->Location = System::Drawing::Point(12, 9);
					 this->label1->Margin = System::Windows::Forms::Padding(3, 0, 3, 3);
					 this->label1->Name = L"label1";
					 this->label1->Size = System::Drawing::Size(58, 15);
					 this->label1->TabIndex = 0;
					 this->label1->TextAlign = ContentAlignment::MiddleRight;
					 this->label1->Text = L"Порог (t):";
					 // 
					 // label2
					 // 
					 this->label2->AutoSize = true;
					 this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 this->label2->ForeColor = System::Drawing::SystemColors::Window;
					 this->label2->Location = System::Drawing::Point(46, 24);
					 this->label2->Margin = System::Windows::Forms::Padding(3);
					 this->label2->Name = L"label2";
					 this->label2->Size = System::Drawing::Size(24, 15);
					 this->label2->TabIndex = 1;
					 this->label2->TextAlign = ContentAlignment::MiddleRight;
					 this->label2->Text = L"b0:";
					 // 
					 // label3
					 // 
					 this->label3->AutoSize = true;
					 this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 this->label3->ForeColor = System::Drawing::SystemColors::Window;
					 this->label3->Location = System::Drawing::Point(46, 39);
					 this->label3->Margin = System::Windows::Forms::Padding(3);
					 this->label3->Name = L"label3";
					 this->label3->Size = System::Drawing::Size(24, 15);
					 this->label3->TabIndex = 2;
					 this->label3->TextAlign = ContentAlignment::MiddleRight;
					 this->label3->Text = L"b1:";
					 // 
					 // textBox1
					 // 
					 this->textBox1->BackColor = System::Drawing::SystemColors::WindowFrame;
					 this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
					 this->textBox1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 this->textBox1->ForeColor = System::Drawing::SystemColors::Window;
					 this->textBox1->Location = System::Drawing::Point(76, 10);
					 this->textBox1->MaxLength = 3;
					 this->textBox1->Name = L"textBox1";
					 this->textBox1->Size = System::Drawing::Size(41, 14);
					 this->textBox1->Text = L"1";
					 this->textBox1->TabIndex = 3;
					 this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
					 this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dialog::textBox1_KeyDown);
					 this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Dialog::textBox_KeyPress);
					 // 
					 // textBox2
					 // 
					 this->textBox2->BackColor = System::Drawing::SystemColors::WindowFrame;
					 this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
					 this->textBox2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 this->textBox2->ForeColor = System::Drawing::SystemColors::Window;
					 this->textBox2->Location = System::Drawing::Point(76, 25);
					 this->textBox2->MaxLength = 3;
					 this->textBox2->Name = L"textBox2";
					 this->textBox2->Size = System::Drawing::Size(41, 14);
					 this->textBox2->Text = L"1";
					 this->textBox2->TabIndex = 4;
					 this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
					 this->textBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dialog::textBox2_KeyDown);
					 this->textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Dialog::textBox_KeyPress);
					 // 
					 // textBox3
					 // 
					 this->textBox3->BackColor = System::Drawing::SystemColors::WindowFrame;
					 this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::None;
					 this->textBox3->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 this->textBox3->ForeColor = System::Drawing::SystemColors::Window;
					 this->textBox3->Location = System::Drawing::Point(76, 40);
					 this->textBox3->MaxLength = 3;
					 this->textBox3->Name = L"textBox3";
					 this->textBox3->Size = System::Drawing::Size(41, 14);
					 this->textBox3->Text = L"1";
					 this->textBox3->TabIndex = 5;
					 this->textBox3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
					 this->textBox3->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dialog::textBox3_KeyDown);
					 this->textBox3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Dialog::textBox_KeyPress);
					 // 
					 // trackBar1
					 // 
					 this->trackBar1->AutoSize = false;
					 this->trackBar1->Location = System::Drawing::Point(123, 10);
					 this->trackBar1->Margin = System::Windows::Forms::Padding(0);
					 this->trackBar1->Maximum = 255;
					 this->trackBar1->Name = L"trackBar1";
					 this->trackBar1->Size = System::Drawing::Size(137, 15);
					 this->trackBar1->TabIndex = 6;
					 this->trackBar1->TickStyle = System::Windows::Forms::TickStyle::None;
					 this->trackBar1->ValueChanged += gcnew System::EventHandler(this, &Dialog::trackBar1_ValueChanged);
					 // 
					 // trackBar2
					 // 
					 this->trackBar2->AutoSize = false;
					 this->trackBar2->Location = System::Drawing::Point(123, 25);
					 this->trackBar2->Margin = System::Windows::Forms::Padding(0);
					 this->trackBar2->Maximum = 255;
					 this->trackBar2->Name = L"trackBar2";
					 this->trackBar2->Size = System::Drawing::Size(137, 15);
					 this->trackBar2->TabIndex = 7;
					 this->trackBar2->TickStyle = System::Windows::Forms::TickStyle::None;
					 this->trackBar2->ValueChanged += gcnew System::EventHandler(this, &Dialog::trackBar2_ValueChanged);
					 // 
					 // trackBar3
					 // 
					 this->trackBar3->AutoSize = false;
					 this->trackBar3->Location = System::Drawing::Point(123, 40);
					 this->trackBar3->Margin = System::Windows::Forms::Padding(0);
					 this->trackBar3->Maximum = 255;
					 this->trackBar3->Name = L"trackBar3";
					 this->trackBar3->Size = System::Drawing::Size(137, 15);
					 this->trackBar3->TabIndex = 8;
					 this->trackBar3->TickStyle = System::Windows::Forms::TickStyle::None;
					 this->trackBar3->ValueChanged += gcnew System::EventHandler(this, &Dialog::trackBar3_ValueChanged);
					 // 
					 // Dialog
					 // 
					 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
					 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					 this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
						 static_cast<System::Int32>(static_cast<System::Byte>(45)));
					 this->ClientSize = System::Drawing::Size(273, 62);
					 this->Controls->Add(this->trackBar3);
					 this->Controls->Add(this->trackBar2);
					 this->Controls->Add(this->trackBar1);
					 this->Controls->Add(this->textBox3);
					 this->Controls->Add(this->textBox2);
					 this->Controls->Add(this->textBox1);
					 this->Controls->Add(this->label3);
					 this->Controls->Add(this->label2);
					 this->Controls->Add(this->label1);
					 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
					 this->MaximumSize = System::Drawing::Size(289, 101);
					 this->MinimumSize = System::Drawing::Size(289, 101);
					 this->Name = L"Dialog";
					 this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
					 this->Text = L"Бинаризация";
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->EndInit();
					 this->ResumeLayout(false);
					 this->PerformLayout();
					 break;
				 case 2:
					 this->label1 = (gcnew System::Windows::Forms::Label());
					 this->label2 = (gcnew System::Windows::Forms::Label());
					 this->textBox1 = (gcnew System::Windows::Forms::TextBox());
					 this->textBox2 = (gcnew System::Windows::Forms::TextBox());
					 this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
					 this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
					 this->SuspendLayout();
					 // 
					 // label1
					 // 
					 this->label1->AutoSize = true;
					 this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 this->label1->ForeColor = System::Drawing::SystemColors::Window;
					 this->label1->Location = System::Drawing::Point(12, 9);
					 this->label1->Margin = System::Windows::Forms::Padding(3, 0, 3, 3);
					 this->label1->Name = L"label1";
					 this->label1->Size = System::Drawing::Size(58, 15);
					 this->label1->TabIndex = 0;
					 this->label1->Text = L"C:";
					 this->label1->TextAlign = ContentAlignment::MiddleRight;
					 // 
					 // label2
					 // 
					 this->label2->AutoSize = true;
					 this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 this->label2->ForeColor = System::Drawing::SystemColors::Window;
					 this->label2->Location = System::Drawing::Point(12, 24);
					 this->label2->Margin = System::Windows::Forms::Padding(3);
					 this->label2->Name = L"label2";
					 this->label2->Size = System::Drawing::Size(58, 15);
					 this->label2->TabIndex = 1;
					 this->label2->TextAlign = ContentAlignment::MiddleRight;
					 this->label2->Text = L"Gamma:";
					 // 
					 // textBox1
					 // 
					 this->textBox1->BackColor = System::Drawing::SystemColors::WindowFrame;
					 this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
					 this->textBox1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 this->textBox1->ForeColor = System::Drawing::SystemColors::Window;
					 this->textBox1->Location = System::Drawing::Point(76, 10);
					 this->textBox1->MaxLength = 3;
					 this->textBox1->Name = L"textBox1";
					 this->textBox1->Size = System::Drawing::Size(41, 14);
					 this->textBox1->TabIndex = 3;
					 this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
					 this->textBox1->Text = L"1";
					 this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dialog::textBox1_KeyDown);
					 this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Dialog::textBox_KeyPress);
					 // 
					 // textBox2
					 // 
					 this->textBox2->BackColor = System::Drawing::SystemColors::WindowFrame;
					 this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
					 this->textBox2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 this->textBox2->ForeColor = System::Drawing::SystemColors::Window;
					 this->textBox2->Location = System::Drawing::Point(76, 25);
					 this->textBox2->MaxLength = 3;
					 this->textBox2->Name = L"textBox2";
					 this->textBox2->Size = System::Drawing::Size(41, 14);
					 this->textBox2->TabIndex = 4;
					 this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
					 this->textBox2->Text = L"1";
					 this->textBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dialog::textBox2_KeyDown);
					 this->textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Dialog::textBox_KeyPress);
					 // 
					 // trackBar1
					 // 
					 this->trackBar1->AutoSize = false;
					 this->trackBar1->Location = System::Drawing::Point(123, 10);
					 this->trackBar1->Margin = System::Windows::Forms::Padding(0);
					 this->trackBar1->Maximum = 50;
					 this->trackBar1->Name = L"trackBar1";
					 this->trackBar1->Size = System::Drawing::Size(137, 15);
					 this->trackBar1->TabIndex = 6;
					 this->trackBar1->TickStyle = System::Windows::Forms::TickStyle::None;
					 this->trackBar1->ValueChanged += gcnew System::EventHandler(this, &Dialog::trackBar1_ValueChanged);
					 this->trackBar1->Value = 25;
					 // 
					 // trackBar2
					 // 
					 this->trackBar2->AutoSize = false;
					 this->trackBar2->Location = System::Drawing::Point(123, 25);
					 this->trackBar2->Margin = System::Windows::Forms::Padding(0);
					 this->trackBar2->Maximum = 50;
					 this->trackBar2->Name = L"trackBar2";
					 this->trackBar2->Size = System::Drawing::Size(137, 15);
					 this->trackBar2->TabIndex = 7;
					 this->trackBar2->TickStyle = System::Windows::Forms::TickStyle::None;
					 this->trackBar2->ValueChanged += gcnew System::EventHandler(this, &Dialog::trackBar2_ValueChanged);
					 this->trackBar2->Value = 25;
					 // 
					 // Dialog
					 // 
					 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
					 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					 this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
						 static_cast<System::Int32>(static_cast<System::Byte>(45)));
					 this->ClientSize = System::Drawing::Size(273, 62);
					 this->Controls->Add(this->trackBar2);
					 this->Controls->Add(this->trackBar1);
					 this->Controls->Add(this->textBox2);
					 this->Controls->Add(this->textBox1);
					 this->Controls->Add(this->label2);
					 this->Controls->Add(this->label1);
					 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
					 this->MaximumSize = System::Drawing::Size(289, 88);
					 this->MinimumSize = System::Drawing::Size(289, 88);
					 this->Name = L"Dialog";
					 this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
					 this->Text = L"Степенное";
					 this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Lab1::Dialog::OnFormClosing);
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
					 this->ResumeLayout(false);
					 this->PerformLayout();
					 break;
				 }

			 }
#pragma endregion
	private: Void textBox1_KeyDown(Object^, KeyEventArgs^);
	private: Void textBox2_KeyDown(Object^, KeyEventArgs^);
	private: Void textBox3_KeyDown(Object^, KeyEventArgs^);
	private: Void textBox_KeyPress(Object^, KeyPressEventArgs^);
	private: Void trackBar1_ValueChanged(Object^, EventArgs^);
	private: Void trackBar2_ValueChanged(Object^, EventArgs^);
	private: Void trackBar3_ValueChanged(Object^, EventArgs^);
	private: Void OnFormClosing(Object^, FormClosingEventArgs^);
	};
}
