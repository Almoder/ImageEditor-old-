#include "MainForm.h"

namespace ImageEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Dialog
	/// </summary>
	public ref class Dialog : public System::Windows::Forms::Form {
	public:
		int type = 0;
		ImageEditor::MainForm^ ptr = nullptr;

		Dialog(MainForm^, int);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Dialog();
	private: 
		System::Windows::Forms::Label^ label1, ^label2, ^label3, ^label4, ^label5;
		System::Windows::Forms::TextBox^ textBox1, ^textBox2, ^textBox3, ^textBox4, ^textBox5;
		System::Windows::Forms::TrackBar^ trackBar1, ^trackBar2, ^trackBar3, ^trackBar4, ^trackBar5;
		System::Windows::Forms::Button^ confirmButton;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void) {
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->confirmButton = (gcnew System::Windows::Forms::Button());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar3 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar4 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar5 = (gcnew System::Windows::Forms::TrackBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar5))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(11, 15);
			this->label1->TabIndex = 0;
			this->label1->Text = L"t";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->label2->Location = System::Drawing::Point(12, 24);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(21, 15);
			this->label2->TabIndex = 1;
			this->label2->Text = L"b0";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->label3->Location = System::Drawing::Point(12, 39);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(21, 15);
			this->label3->TabIndex = 2;
			this->label3->Text = L"b1";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->label4->Location = System::Drawing::Point(12, 54);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(14, 15);
			this->label4->TabIndex = 3;
			this->label4->Text = L"c";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->label5->Location = System::Drawing::Point(12, 69);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(14, 15);
			this->label5->TabIndex = 4;
			this->label5->Text = L"g";
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->textBox1->Location = System::Drawing::Point(40, 9);
			this->textBox1->MaxLength = 3;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(40, 14);
			this->textBox1->TabIndex = 5;
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Dialog::textBoxTextChanged);
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dialog::textBoxKeyDown);
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Dialog::textBoxKeyPress);
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->textBox2->Location = System::Drawing::Point(40, 24);
			this->textBox2->MaxLength = 3;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(40, 14);
			this->textBox2->TabIndex = 6;
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Dialog::textBoxTextChanged);
			this->textBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dialog::textBoxKeyDown);
			this->textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Dialog::textBoxKeyPress);
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox3->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->textBox3->Location = System::Drawing::Point(40, 39);
			this->textBox3->MaxLength = 3;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(40, 14);
			this->textBox3->TabIndex = 7;
			this->textBox3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &Dialog::textBoxTextChanged);
			this->textBox3->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dialog::textBoxKeyDown);
			this->textBox3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Dialog::textBoxKeyPress);
			// 
			// textBox4
			// 
			this->textBox4->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->textBox4->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox4->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->textBox4->Location = System::Drawing::Point(40, 54);
			this->textBox4->MaxLength = 4;
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(40, 14);
			this->textBox4->TabIndex = 8;
			this->textBox4->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &Dialog::textBoxTextChanged);
			this->textBox4->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dialog::textBoxKeyDown);
			this->textBox4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Dialog::textBoxKeyPress);
			// 
			// textBox5
			// 
			this->textBox5->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->textBox5->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox5->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->textBox5->Location = System::Drawing::Point(40, 69);
			this->textBox5->MaxLength = 4;
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(40, 14);
			this->textBox5->TabIndex = 9;
			this->textBox5->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox5->TextChanged += gcnew System::EventHandler(this, &Dialog::textBoxTextChanged);
			this->textBox5->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Dialog::textBoxKeyDown);
			this->textBox5->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Dialog::textBoxKeyPress);
			// 
			// confirmButton
			// 
			this->confirmButton->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->confirmButton->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->confirmButton->Location = System::Drawing::Point(15, 88);
			this->confirmButton->Name = L"confirmButton";
			this->confirmButton->Size = System::Drawing::Size(138, 17);
			this->confirmButton->TabIndex = 10;
			this->confirmButton->Text = L"применить";
			this->confirmButton->UseVisualStyleBackColor = true;
			this->confirmButton->Click += gcnew System::EventHandler(this, &Dialog::confirmButtonClick);
			// 
			// trackBar1
			// 
			this->trackBar1->AutoSize = false;
			this->trackBar1->Location = System::Drawing::Point(90, 9);
			this->trackBar1->Maximum = 255;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(148, 15);
			this->trackBar1->TabIndex = 12;
			this->trackBar1->TickStyle = System::Windows::Forms::TickStyle::None;
			this->trackBar1->ValueChanged += gcnew System::EventHandler(this, &Dialog::trackBarValueChanged);
			// 
			// trackBar2
			// 
			this->trackBar2->AutoSize = false;
			this->trackBar2->Location = System::Drawing::Point(90, 24);
			this->trackBar2->Maximum = 255;
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(148, 15);
			this->trackBar2->TabIndex = 13;
			this->trackBar2->TickStyle = System::Windows::Forms::TickStyle::None;
			this->trackBar2->ValueChanged += gcnew System::EventHandler(this, &Dialog::trackBarValueChanged);
			// 
			// trackBar3
			// 
			this->trackBar3->AutoSize = false;
			this->trackBar3->Location = System::Drawing::Point(90, 39);
			this->trackBar3->Maximum = 255;
			this->trackBar3->Name = L"trackBar3";
			this->trackBar3->Size = System::Drawing::Size(148, 15);
			this->trackBar3->TabIndex = 14;
			this->trackBar3->TickStyle = System::Windows::Forms::TickStyle::None;
			this->trackBar3->ValueChanged += gcnew System::EventHandler(this, &Dialog::trackBarValueChanged);
			// 
			// trackBar4
			// 
			this->trackBar4->AutoSize = false;
			this->trackBar4->LargeChange = 25;
			this->trackBar4->Location = System::Drawing::Point(90, 54);
			this->trackBar4->Maximum = 400;
			this->trackBar4->Name = L"trackBar4";
			this->trackBar4->Size = System::Drawing::Size(148, 15);
			this->trackBar4->TabIndex = 15;
			this->trackBar4->TickStyle = System::Windows::Forms::TickStyle::None;
			this->trackBar4->ValueChanged += gcnew System::EventHandler(this, &Dialog::trackBarValueChanged);
			// 
			// trackBar5
			// 
			this->trackBar5->AutoSize = false;
			this->trackBar5->LargeChange = 25;
			this->trackBar5->Location = System::Drawing::Point(90, 69);
			this->trackBar5->Maximum = 400;
			this->trackBar5->Name = L"trackBar5";
			this->trackBar5->Size = System::Drawing::Size(148, 15);
			this->trackBar5->TabIndex = 16;
			this->trackBar5->TickStyle = System::Windows::Forms::TickStyle::None;
			this->trackBar5->ValueChanged += gcnew System::EventHandler(this, &Dialog::trackBarValueChanged);
			// 
			// Dialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->ClientSize = System::Drawing::Size(242, 110);
			this->Controls->Add(this->trackBar5);
			this->Controls->Add(this->trackBar4);
			this->Controls->Add(this->trackBar3);
			this->Controls->Add(this->trackBar2);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->confirmButton);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"Dialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Dialog";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar5))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		Void textBoxKeyDown(Object^, System::Windows::Forms::KeyEventArgs^);
		Void textBoxKeyPress(Object^, System::Windows::Forms::KeyPressEventArgs^);
		Void textBoxTextChanged(Object^, EventArgs^);
		Void trackBarValueChanged(Object^, EventArgs^);
		Void confirmButtonClick(Object^, EventArgs^);
	};
}
