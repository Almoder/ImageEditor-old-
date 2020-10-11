#include "MainForm.h"

namespace ImageEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	public ref class Dialog : public System::Windows::Forms::Form
	{
	private: 
		Windows::Forms::Label^  label1, ^label2, ^label3;
		Windows::Forms::TextBox^  textBox1, ^textBox2, ^textBox3;
		Windows::Forms::TrackBar^  trackBar1, ^trackBar2, ^trackBar3;
		System::ComponentModel::Container ^components;
		int t, b0, b1;
		double c, g;
		MainForm^ ptr;
	public:  
		int type;

		Dialog(MainForm^, int);
	protected:
		~Dialog();

#pragma region Windows Form Designer generated code

			 void InitializeComponent(int type)
			 {
				 switch (type) {
				 case 1:
					 label1 = (gcnew System::Windows::Forms::Label());
					 label2 = (gcnew System::Windows::Forms::Label());
					 label3 = (gcnew System::Windows::Forms::Label());
					 textBox1 = (gcnew System::Windows::Forms::TextBox());
					 textBox2 = (gcnew System::Windows::Forms::TextBox());
					 textBox3 = (gcnew System::Windows::Forms::TextBox());
					 trackBar1 = (gcnew System::Windows::Forms::TrackBar());
					 trackBar2 = (gcnew System::Windows::Forms::TrackBar());
					 trackBar3 = (gcnew System::Windows::Forms::TrackBar());
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(trackBar1))->BeginInit();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(trackBar2))->BeginInit();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(trackBar3))->BeginInit();
					 SuspendLayout();
					 // 
					 // label1
					 // 
					 label1->AutoSize = true;
					 label1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 label1->ForeColor = System::Drawing::SystemColors::Window;
					 label1->Location = System::Drawing::Point(12, 9);
					 label1->Margin = System::Windows::Forms::Padding(3, 0, 3, 3);
					 label1->Name = L"label1";
					 label1->Size = System::Drawing::Size(58, 15);
					 label1->TabIndex = 0;
					 label1->TextAlign = ContentAlignment::MiddleRight;
					 label1->Text = L"Порог (t):";
					 // 
					 // label2
					 // 
					 label2->AutoSize = true;
					 label2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 label2->ForeColor = System::Drawing::SystemColors::Window;
					 label2->Location = System::Drawing::Point(46, 24);
					 label2->Margin = System::Windows::Forms::Padding(3);
					 label2->Name = L"label2";
					 label2->Size = System::Drawing::Size(24, 15);
					 label2->TabIndex = 1;
					 label2->TextAlign = ContentAlignment::MiddleRight;
					 label2->Text = L"b0:";
					 // 
					 // label3
					 // 
					 label3->AutoSize = true;
					 label3->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 label3->ForeColor = System::Drawing::SystemColors::Window;
					 label3->Location = System::Drawing::Point(46, 39);
					 label3->Margin = System::Windows::Forms::Padding(3);
					 label3->Name = L"label3";
					 label3->Size = System::Drawing::Size(24, 15);
					 label3->TabIndex = 2;
					 label3->TextAlign = ContentAlignment::MiddleRight;
					 label3->Text = L"b1:";
					 // 
					 // textBox1
					 // 
					 textBox1->BackColor = System::Drawing::SystemColors::WindowFrame;
					 textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
					 textBox1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 textBox1->ForeColor = System::Drawing::SystemColors::Window;
					 textBox1->Location = System::Drawing::Point(76, 10);
					 textBox1->MaxLength = 3;
					 textBox1->Name = L"textBox1";
					 textBox1->Size = System::Drawing::Size(41, 14);
					 textBox1->Text = L"1";
					 textBox1->TabIndex = 3;
					 textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
					 textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dialog::textBox1_KeyDown);
					 textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Dialog::textBox_KeyPressInt);
					 // 
					 // textBox2
					 // 
					 textBox2->BackColor = System::Drawing::SystemColors::WindowFrame;
					 textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
					 textBox2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 textBox2->ForeColor = System::Drawing::SystemColors::Window;
					 textBox2->Location = System::Drawing::Point(76, 25);
					 textBox2->MaxLength = 3;
					 textBox2->Name = L"textBox2";
					 textBox2->Size = System::Drawing::Size(41, 14);
					 textBox2->Text = L"1";
					 textBox2->TabIndex = 4;
					 textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
					 textBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dialog::textBox2_KeyDown);
					 textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Dialog::textBox_KeyPressInt);
					 // 
					 // textBox3
					 // 
					 textBox3->BackColor = System::Drawing::SystemColors::WindowFrame;
					 textBox3->BorderStyle = System::Windows::Forms::BorderStyle::None;
					 textBox3->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 textBox3->ForeColor = System::Drawing::SystemColors::Window;
					 textBox3->Location = System::Drawing::Point(76, 40);
					 textBox3->MaxLength = 3;
					 textBox3->Name = L"textBox3";
					 textBox3->Size = System::Drawing::Size(41, 14);
					 textBox3->Text = L"1";
					 textBox3->TabIndex = 5;
					 textBox3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
					 textBox3->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dialog::textBox3_KeyDown);
					 textBox3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Dialog::textBox_KeyPressInt);
					 // 
					 // trackBar1
					 // 
					 trackBar1->AutoSize = false;
					 trackBar1->Location = System::Drawing::Point(123, 10);
					 trackBar1->Margin = System::Windows::Forms::Padding(0);
					 trackBar1->Maximum = 255;
					 trackBar1->Name = L"trackBar1";
					 trackBar1->Size = System::Drawing::Size(137, 15);
					 trackBar1->TabIndex = 6;
					 trackBar1->TickStyle = System::Windows::Forms::TickStyle::None;
					 trackBar1->ValueChanged += gcnew System::EventHandler(this, &Dialog::trackBar1_ValueChanged);
					 // 
					 // trackBar2
					 // 
					 trackBar2->AutoSize = false;
					 trackBar2->Location = System::Drawing::Point(123, 25);
					 trackBar2->Margin = System::Windows::Forms::Padding(0);
					 trackBar2->Maximum = 255;
					 trackBar2->Name = L"trackBar2";
					 trackBar2->Size = System::Drawing::Size(137, 15);
					 trackBar2->TabIndex = 7;
					 trackBar2->TickStyle = System::Windows::Forms::TickStyle::None;
					 trackBar2->ValueChanged += gcnew System::EventHandler(this, &Dialog::trackBar2_ValueChanged);
					 // 
					 // trackBar3
					 // 
					 trackBar3->AutoSize = false;
					 trackBar3->Location = System::Drawing::Point(123, 40);
					 trackBar3->Margin = System::Windows::Forms::Padding(0);
					 trackBar3->Maximum = 255;
					 trackBar3->Name = L"trackBar3";
					 trackBar3->Size = System::Drawing::Size(137, 15);
					 trackBar3->TabIndex = 8;
					 trackBar3->TickStyle = System::Windows::Forms::TickStyle::None;
					 trackBar3->ValueChanged += gcnew System::EventHandler(this, &Dialog::trackBar3_ValueChanged);
					 // 
					 // Dialog
					 // 
					 AutoScaleDimensions = System::Drawing::SizeF(6, 13);
					 AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					 BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
						 static_cast<System::Int32>(static_cast<System::Byte>(45)));
					 ClientSize = System::Drawing::Size(273, 62);
					 Controls->Add(trackBar3);
					 Controls->Add(trackBar2);
					 Controls->Add(trackBar1);
					 Controls->Add(textBox3);
					 Controls->Add(textBox2);
					 Controls->Add(textBox1);
					 Controls->Add(label3);
					 Controls->Add(label2);
					 Controls->Add(label1);
					 FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
					 MaximumSize = System::Drawing::Size(289, 101);
					 MinimumSize = System::Drawing::Size(289, 101);
					 Name = L"Dialog";
					 StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
					 Text = L"Бинаризация";
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(trackBar1))->EndInit();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(trackBar2))->EndInit();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(trackBar3))->EndInit();
					 ResumeLayout(false);
					 PerformLayout();
					 break;
				 case 2:
					 label1 = (gcnew System::Windows::Forms::Label());
					 label2 = (gcnew System::Windows::Forms::Label());
					 textBox1 = (gcnew System::Windows::Forms::TextBox());
					 textBox2 = (gcnew System::Windows::Forms::TextBox());
					 trackBar1 = (gcnew System::Windows::Forms::TrackBar());
					 trackBar2 = (gcnew System::Windows::Forms::TrackBar());
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(trackBar1))->BeginInit();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(trackBar2))->BeginInit();
					 SuspendLayout();
					 // 
					 // label1
					 // 
					 label1->AutoSize = true;
					 label1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 label1->ForeColor = System::Drawing::SystemColors::Window;
					 label1->Location = System::Drawing::Point(12, 9);
					 label1->Margin = System::Windows::Forms::Padding(3, 0, 3, 3);
					 label1->Name = L"label1";
					 label1->Size = System::Drawing::Size(58, 15);
					 label1->TabIndex = 0;
					 label1->Text = L"C:";
					 label1->TextAlign = ContentAlignment::MiddleRight;
					 // 
					 // label2
					 // 
					 label2->AutoSize = true;
					 label2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 label2->ForeColor = System::Drawing::SystemColors::Window;
					 label2->Location = System::Drawing::Point(12, 24);
					 label2->Margin = System::Windows::Forms::Padding(3);
					 label2->Name = L"label2";
					 label2->Size = System::Drawing::Size(58, 15);
					 label2->TabIndex = 1;
					 label2->TextAlign = ContentAlignment::MiddleRight;
					 label2->Text = L"Gamma:";
					 // 
					 // textBox1
					 // 
					 textBox1->BackColor = System::Drawing::SystemColors::WindowFrame;
					 textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
					 textBox1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 textBox1->ForeColor = System::Drawing::SystemColors::Window;
					 textBox1->Location = System::Drawing::Point(76, 10);
					 textBox1->MaxLength = 3;
					 textBox1->Name = L"textBox1";
					 textBox1->Size = System::Drawing::Size(41, 14);
					 textBox1->TabIndex = 3;
					 textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
					 textBox1->Text = L"1";
					 textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dialog::textBox1_KeyDown);
					 textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Dialog::textBox_KeyPressDouble);
					 // 
					 // textBox2
					 // 
					 textBox2->BackColor = System::Drawing::SystemColors::WindowFrame;
					 textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
					 textBox2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						 static_cast<System::Byte>(204)));
					 textBox2->ForeColor = System::Drawing::SystemColors::Window;
					 textBox2->Location = System::Drawing::Point(76, 25);
					 textBox2->MaxLength = 3;
					 textBox2->Name = L"textBox2";
					 textBox2->Size = System::Drawing::Size(41, 14);
					 textBox2->TabIndex = 4;
					 textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
					 textBox2->Text = L"1";
					 textBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dialog::textBox2_KeyDown);
					 textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Dialog::textBox_KeyPressDouble);
					 // 
					 // trackBar1
					 // 
					 trackBar1->AutoSize = false;
					 trackBar1->Location = System::Drawing::Point(123, 10);
					 trackBar1->Margin = System::Windows::Forms::Padding(0);
					 trackBar1->Maximum = 50;
					 trackBar1->Name = L"trackBar1";
					 trackBar1->Size = System::Drawing::Size(137, 15);
					 trackBar1->TabIndex = 6;
					 trackBar1->TickStyle = System::Windows::Forms::TickStyle::None;
					 trackBar1->ValueChanged += gcnew System::EventHandler(this, &Dialog::trackBar1_ValueChanged);
					 trackBar1->Value = 25;
					 // 
					 // trackBar2
					 // 
					 trackBar2->AutoSize = false;
					 trackBar2->Location = System::Drawing::Point(123, 25);
					 trackBar2->Margin = System::Windows::Forms::Padding(0);
					 trackBar2->Maximum = 50;
					 trackBar2->Name = L"trackBar2";
					 trackBar2->Size = System::Drawing::Size(137, 15);
					 trackBar2->TabIndex = 7;
					 trackBar2->TickStyle = System::Windows::Forms::TickStyle::None;
					 trackBar2->ValueChanged += gcnew System::EventHandler(this, &Dialog::trackBar2_ValueChanged);
					 trackBar2->Value = 25;
					 // 
					 // Dialog
					 // 
					 AutoScaleDimensions = System::Drawing::SizeF(6, 13);
					 AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					 BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
						 static_cast<System::Int32>(static_cast<System::Byte>(45)));
					 ClientSize = System::Drawing::Size(273, 62);
					 Controls->Add(trackBar2);
					 Controls->Add(trackBar1);
					 Controls->Add(textBox2);
					 Controls->Add(textBox1);
					 Controls->Add(label2);
					 Controls->Add(label1);
					 FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
					 MaximumSize = System::Drawing::Size(289, 88);
					 MinimumSize = System::Drawing::Size(289, 88);
					 Name = L"Dialog";
					 StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
					 Text = L"Степенное";
					 FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ImageEditor::Dialog::OnFormClosing);
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(trackBar1))->EndInit();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(trackBar2))->EndInit();
					 ResumeLayout(false);
					 PerformLayout();
					 break;
				 }

			 }
#pragma endregion
	private: 
		Void textBox1_KeyDown(Object^, KeyEventArgs^);
		Void textBox2_KeyDown(Object^, KeyEventArgs^);
		Void textBox3_KeyDown(Object^, KeyEventArgs^);
		Void textBox_KeyPressInt(Object^, KeyPressEventArgs^);
		Void textBox_KeyPressDouble(Object^, KeyPressEventArgs^);
		Void trackBar1_ValueChanged(Object^, EventArgs^);
		Void trackBar2_ValueChanged(Object^, EventArgs^);
		Void trackBar3_ValueChanged(Object^, EventArgs^);
		Void OnFormClosing(Object^, FormClosingEventArgs^);
	};
}
