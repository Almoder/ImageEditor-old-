#include "Engine.h"

namespace ImageEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MainForm1
	/// </summary>
	public ref class MainForm : public Form
	{
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::ProgressBar^ progressBar;
		
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ textBox9;
	private: System::Windows::Forms::Button^ button10;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::ComboBox^ comboBox1;

	private: System::Windows::Forms::Button^ button11;
	private: System::Windows::Forms::Button^ button12;
	private: System::Windows::Forms::TextBox^ textBox11;
	private: System::Windows::Forms::TextBox^ textBox10;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Label^ label12;
	
		Engine^ engine = nullptr;
		PictureBox^ curPictureBox = nullptr;
		Drawing::Point newPb = Point(0, 0);

		   int curLabel = 1, filterSize = 3;
	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::Panel^ gallery;


	private: System::Windows::Forms::TableLayoutPanel^ propTable;
	private: System::Windows::Forms::Label^ typeLabel;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ description;


	private: System::Windows::Forms::DomainUpDown^ comboBox2;
	public:
		MainForm(void);

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MainForm();
	private: System::Windows::Forms::MenuStrip^ menuStrip;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ fileItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openItem;
	private: System::Windows::Forms::ToolStripMenuItem^ saveItem;
	private: System::Windows::Forms::ToolStripMenuItem^ saveAsItem;
	private: System::Windows::Forms::ToolStripMenuItem^ undoItem;
	private: System::Windows::Forms::ToolStripMenuItem^ redoItem;
	private: System::Windows::Forms::ToolStripMenuItem^ viewItem;
	private: System::Windows::Forms::ToolStripMenuItem^ doubleItem;
	private: System::Windows::Forms::TabControl^ tabControl;
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::TabPage^ tabPage3;
	private: System::Windows::Forms::SplitContainer^ splitContainer;
	private: System::Windows::Forms::StatusStrip^ statusStrip;
	private: System::Windows::Forms::ToolStripStatusLabel^ countLabel;
	private: System::Windows::Forms::ToolStripStatusLabel^ cur1Label;
	private: System::Windows::Forms::ToolStripStatusLabel^ cur2Label;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayout;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->fileItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->undoItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->redoItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->viewItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->doubleItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tableLayout = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::DomainUpDown());
			this->splitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->gallery = (gcnew System::Windows::Forms::Panel());
			this->propTable = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->countLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->cur1Label = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->cur2Label = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->typeLabel = (gcnew System::Windows::Forms::Label());
			this->description = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->menuStrip->SuspendLayout();
			this->tabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tableLayout->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer))->BeginInit();
			this->splitContainer->Panel1->SuspendLayout();
			this->splitContainer->Panel2->SuspendLayout();
			this->splitContainer->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->tabPage2->SuspendLayout();
			this->propTable->SuspendLayout();
			this->statusStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip
			// 
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->fileItem, this->viewItem });
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(524, 24);
			this->menuStrip->TabIndex = 0;
			this->menuStrip->Text = L"menuStrip1";
			// 
			// fileItem
			// 
			this->fileItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->openItem, this->saveItem,
					this->saveAsItem, this->undoItem, this->redoItem
			});
			this->fileItem->Name = L"fileItem";
			this->fileItem->Size = System::Drawing::Size(37, 20);
			this->fileItem->Text = L"File";
			// 
			// openItem
			// 
			this->openItem->Name = L"openItem";
			this->openItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->openItem->Size = System::Drawing::Size(183, 22);
			this->openItem->Text = L"Open";
			this->openItem->Click += gcnew System::EventHandler(this, &MainForm::openItemClick);
			// 
			// saveItem
			// 
			this->saveItem->Name = L"saveItem";
			this->saveItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->saveItem->Size = System::Drawing::Size(183, 22);
			this->saveItem->Text = L"Save";
			this->saveItem->Click += gcnew System::EventHandler(this, &MainForm::saveItemClick);
			// 
			// saveAsItem
			// 
			this->saveAsItem->Name = L"saveAsItem";
			this->saveAsItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
				| System::Windows::Forms::Keys::S));
			this->saveAsItem->Size = System::Drawing::Size(183, 22);
			this->saveAsItem->Text = L"SaveAs";
			this->saveAsItem->Click += gcnew System::EventHandler(this, &MainForm::saveAsItemClick);
			// 
			// undoItem
			// 
			this->undoItem->Name = L"undoItem";
			this->undoItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Z));
			this->undoItem->Size = System::Drawing::Size(183, 22);
			this->undoItem->Text = L"Undo";
			this->undoItem->Visible = false;
			this->undoItem->Click += gcnew System::EventHandler(this, &MainForm::undoItemClick);
			// 
			// redoItem
			// 
			this->redoItem->Name = L"redoItem";
			this->redoItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::X));
			this->redoItem->Size = System::Drawing::Size(183, 22);
			this->redoItem->Text = L"Redo";
			this->redoItem->Visible = false;
			this->redoItem->Click += gcnew System::EventHandler(this, &MainForm::redoItemClick);
			// 
			// viewItem
			// 
			this->viewItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->doubleItem });
			this->viewItem->Name = L"viewItem";
			this->viewItem->Size = System::Drawing::Size(44, 20);
			this->viewItem->Text = L"View";
			// 
			// doubleItem
			// 
			this->doubleItem->CheckOnClick = true;
			this->doubleItem->Name = L"doubleItem";
			this->doubleItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D));
			this->doubleItem->Size = System::Drawing::Size(194, 22);
			this->doubleItem->Text = L"Double picture";
			this->doubleItem->Click += gcnew System::EventHandler(this, &MainForm::doubleItemClick);
			// 
			// tabControl
			// 
			this->tabControl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl->Appearance = System::Windows::Forms::TabAppearance::FlatButtons;
			this->tabControl->Controls->Add(this->tabPage1);
			this->tabControl->Controls->Add(this->tabPage2);
			this->tabControl->Controls->Add(this->tabPage3);
			this->tabControl->Location = System::Drawing::Point(0, 24);
			this->tabControl->Margin = System::Windows::Forms::Padding(3, 0, 3, 0);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(524, 254);
			this->tabControl->TabIndex = 1;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->tableLayout);
			this->tabPage1->Controls->Add(this->splitContainer);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(516, 225);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Editor";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tableLayout
			// 
			this->tableLayout->AutoScroll = true;
			this->tableLayout->ColumnCount = 2;
			this->tableLayout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayout->Controls->Add(this->textBox11, 1, 25);
			this->tableLayout->Controls->Add(this->textBox10, 1, 24);
			this->tableLayout->Controls->Add(this->label14, 0, 25);
			this->tableLayout->Controls->Add(this->label13, 0, 24);
			this->tableLayout->Controls->Add(this->label12, 0, 23);
			this->tableLayout->Controls->Add(this->button12, 0, 22);
			this->tableLayout->Controls->Add(this->button11, 0, 26);
			this->tableLayout->Controls->Add(this->label11, 0, 19);
			this->tableLayout->Controls->Add(this->button10, 0, 18);
			this->tableLayout->Controls->Add(this->textBox9, 1, 17);
			this->tableLayout->Controls->Add(this->textBox8, 1, 16);
			this->tableLayout->Controls->Add(this->label10, 0, 15);
			this->tableLayout->Controls->Add(this->button9, 0, 17);
			this->tableLayout->Controls->Add(this->button8, 0, 16);
			this->tableLayout->Controls->Add(this->button7, 0, 14);
			this->tableLayout->Controls->Add(this->button6, 0, 13);
			this->tableLayout->Controls->Add(this->textBox7, 1, 14);
			this->tableLayout->Controls->Add(this->textBox6, 1, 13);
			this->tableLayout->Controls->Add(this->label9, 0, 12);
			this->tableLayout->Controls->Add(this->button5, 0, 11);
			this->tableLayout->Controls->Add(this->textBox5, 1, 10);
			this->tableLayout->Controls->Add(this->textBox4, 1, 9);
			this->tableLayout->Controls->Add(this->label8, 0, 10);
			this->tableLayout->Controls->Add(this->label7, 0, 9);
			this->tableLayout->Controls->Add(this->label6, 0, 8);
			this->tableLayout->Controls->Add(this->button4, 0, 7);
			this->tableLayout->Controls->Add(this->button3, 1, 7);
			this->tableLayout->Controls->Add(this->textBox3, 1, 6);
			this->tableLayout->Controls->Add(this->textBox2, 1, 5);
			this->tableLayout->Controls->Add(this->label5, 0, 6);
			this->tableLayout->Controls->Add(this->label4, 0, 5);
			this->tableLayout->Controls->Add(this->label3, 0, 4);
			this->tableLayout->Controls->Add(this->label2, 0, 3);
			this->tableLayout->Controls->Add(this->button2, 0, 2);
			this->tableLayout->Controls->Add(this->button1, 0, 1);
			this->tableLayout->Controls->Add(this->label1, 0, 0);
			this->tableLayout->Controls->Add(this->textBox1, 1, 4);
			this->tableLayout->Controls->Add(this->comboBox1, 0, 20);
			this->tableLayout->Controls->Add(this->comboBox2, 0, 21);
			this->tableLayout->Dock = System::Windows::Forms::DockStyle::Right;
			this->tableLayout->ForeColor = System::Drawing::Color::Black;
			this->tableLayout->Location = System::Drawing::Point(363, 3);
			this->tableLayout->Name = L"tableLayout";
			this->tableLayout->Padding = System::Windows::Forms::Padding(2, 0, 0, 0);
			this->tableLayout->RowCount = 28;
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayout->Size = System::Drawing::Size(150, 219);
			this->tableLayout->TabIndex = 1;
			// 
			// textBox11
			// 
			this->textBox11->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox11->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox11->Location = System::Drawing::Point(67, 500);
			this->textBox11->Margin = System::Windows::Forms::Padding(0);
			this->textBox11->MaxLength = 2;
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(66, 20);
			this->textBox11->TabIndex = 40;
			this->textBox11->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxTextChanged);
			this->textBox11->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::textBoxKeyDown);
			this->textBox11->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBoxKeyPress);
			// 
			// textBox10
			// 
			this->textBox10->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox10->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox10->Location = System::Drawing::Point(67, 480);
			this->textBox10->Margin = System::Windows::Forms::Padding(0);
			this->textBox10->MaxLength = 4;
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(66, 20);
			this->textBox10->TabIndex = 39;
			this->textBox10->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxTextChanged);
			this->textBox10->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::textBoxKeyDown);
			this->textBox10->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBoxKeyPress);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label14->Location = System::Drawing::Point(2, 500);
			this->label14->Margin = System::Windows::Forms::Padding(0);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(65, 20);
			this->label14->TabIndex = 38;
			this->label14->Text = L"Order";
			this->label14->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label13->Location = System::Drawing::Point(2, 480);
			this->label13->Margin = System::Windows::Forms::Padding(0);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(65, 20);
			this->label13->TabIndex = 37;
			this->label13->Text = L"Radius";
			this->label13->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->tableLayout->SetColumnSpan(this->label12, 2);
			this->label12->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label12->Location = System::Drawing::Point(2, 460);
			this->label12->Margin = System::Windows::Forms::Padding(0);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(131, 20);
			this->label12->TabIndex = 36;
			this->label12->Text = L"Frequency domain";
			this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// button12
			// 
			this->tableLayout->SetColumnSpan(this->button12, 2);
			this->button12->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button12->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button12->Location = System::Drawing::Point(2, 440);
			this->button12->Margin = System::Windows::Forms::Padding(0);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(131, 20);
			this->button12->TabIndex = 35;
			this->button12->Text = L"Confirm";
			this->button12->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &MainForm::button12Click);
			// 
			// button11
			// 
			this->tableLayout->SetColumnSpan(this->button11, 2);
			this->button11->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button11->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button11->Location = System::Drawing::Point(2, 520);
			this->button11->Margin = System::Windows::Forms::Padding(0);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(131, 20);
			this->button11->TabIndex = 34;
			this->button11->Text = L"Confirm";
			this->button11->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &MainForm::button11Click);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->tableLayout->SetColumnSpan(this->label11, 2);
			this->label11->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(2, 380);
			this->label11->Margin = System::Windows::Forms::Padding(0);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(131, 20);
			this->label11->TabIndex = 31;
			this->label11->Text = L"Filters";
			this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// button10
			// 
			this->tableLayout->SetColumnSpan(this->button10, 2);
			this->button10->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button10->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button10->Location = System::Drawing::Point(2, 360);
			this->button10->Margin = System::Windows::Forms::Padding(0);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(131, 20);
			this->button10->TabIndex = 30;
			this->button10->Text = L"Autolevel";
			this->button10->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &MainForm::button10Click);
			// 
			// textBox9
			// 
			this->textBox9->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox9->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox9->Location = System::Drawing::Point(67, 340);
			this->textBox9->Margin = System::Windows::Forms::Padding(0);
			this->textBox9->MaxLength = 4;
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(66, 20);
			this->textBox9->TabIndex = 29;
			this->textBox9->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxTextChanged);
			this->textBox9->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::textBoxKeyDown);
			this->textBox9->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBoxKeyPress);
			// 
			// textBox8
			// 
			this->textBox8->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox8->Location = System::Drawing::Point(67, 320);
			this->textBox8->Margin = System::Windows::Forms::Padding(0);
			this->textBox8->MaxLength = 4;
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(66, 20);
			this->textBox8->TabIndex = 28;
			this->textBox8->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxTextChanged);
			this->textBox8->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::textBoxKeyDown);
			this->textBox8->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBoxKeyPress);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->tableLayout->SetColumnSpan(this->label10, 2);
			this->label10->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(2, 300);
			this->label10->Margin = System::Windows::Forms::Padding(0);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(131, 20);
			this->label10->TabIndex = 27;
			this->label10->Text = L"Nonlinear";
			this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// button9
			// 
			this->button9->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button9->Location = System::Drawing::Point(2, 340);
			this->button9->Margin = System::Windows::Forms::Padding(0);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(65, 20);
			this->button9->TabIndex = 26;
			this->button9->Text = L"Contrast";
			this->button9->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MainForm::button9Click);
			// 
			// button8
			// 
			this->button8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button8->Location = System::Drawing::Point(2, 320);
			this->button8->Margin = System::Windows::Forms::Padding(0);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(65, 20);
			this->button8->TabIndex = 25;
			this->button8->Text = L"Brightness";
			this->button8->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MainForm::button8Click);
			// 
			// button7
			// 
			this->button7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button7->Location = System::Drawing::Point(2, 280);
			this->button7->Margin = System::Windows::Forms::Padding(0);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(65, 20);
			this->button7->TabIndex = 24;
			this->button7->Text = L"Contrast";
			this->button7->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MainForm::button7Click);
			// 
			// button6
			// 
			this->button6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->Location = System::Drawing::Point(2, 260);
			this->button6->Margin = System::Windows::Forms::Padding(0);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(65, 20);
			this->button6->TabIndex = 23;
			this->button6->Text = L"Brightness";
			this->button6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MainForm::button6Click);
			// 
			// textBox7
			// 
			this->textBox7->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox7->Location = System::Drawing::Point(67, 280);
			this->textBox7->Margin = System::Windows::Forms::Padding(0);
			this->textBox7->MaxLength = 4;
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(66, 20);
			this->textBox7->TabIndex = 22;
			this->textBox7->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxTextChanged);
			this->textBox7->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::textBoxKeyDown);
			this->textBox7->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBoxKeyPress);
			// 
			// textBox6
			// 
			this->textBox6->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox6->Location = System::Drawing::Point(67, 260);
			this->textBox6->Margin = System::Windows::Forms::Padding(0);
			this->textBox6->MaxLength = 4;
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(66, 20);
			this->textBox6->TabIndex = 21;
			this->textBox6->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxTextChanged);
			this->textBox6->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::textBoxKeyDown);
			this->textBox6->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBoxKeyPress);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->tableLayout->SetColumnSpan(this->label9, 2);
			this->label9->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(2, 240);
			this->label9->Margin = System::Windows::Forms::Padding(0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(131, 20);
			this->label9->TabIndex = 18;
			this->label9->Text = L"Linear";
			this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// button5
			// 
			this->tableLayout->SetColumnSpan(this->button5, 2);
			this->button5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->Location = System::Drawing::Point(2, 220);
			this->button5->Margin = System::Windows::Forms::Padding(0);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(131, 20);
			this->button5->TabIndex = 17;
			this->button5->Text = L"Confirm";
			this->button5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MainForm::button5Click);
			// 
			// textBox5
			// 
			this->textBox5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox5->Location = System::Drawing::Point(67, 200);
			this->textBox5->Margin = System::Windows::Forms::Padding(0);
			this->textBox5->MaxLength = 5;
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(66, 20);
			this->textBox5->TabIndex = 16;
			this->textBox5->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxTextChanged);
			this->textBox5->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::textBoxKeyDown);
			this->textBox5->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBoxKeyPress);
			// 
			// textBox4
			// 
			this->textBox4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox4->Location = System::Drawing::Point(67, 180);
			this->textBox4->Margin = System::Windows::Forms::Padding(0);
			this->textBox4->MaxLength = 5;
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(66, 20);
			this->textBox4->TabIndex = 15;
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxTextChanged);
			this->textBox4->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::textBoxKeyDown);
			this->textBox4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBoxKeyPress);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(2, 200);
			this->label8->Margin = System::Windows::Forms::Padding(0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(65, 20);
			this->label8->TabIndex = 14;
			this->label8->Text = L"Power (G)";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(2, 180);
			this->label7->Margin = System::Windows::Forms::Padding(0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(65, 20);
			this->label7->TabIndex = 13;
			this->label7->Text = L"Multiplier (C)";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->tableLayout->SetColumnSpan(this->label6, 2);
			this->label6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(2, 160);
			this->label6->Margin = System::Windows::Forms::Padding(0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(131, 20);
			this->label6->TabIndex = 12;
			this->label6->Text = L"Power";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// button4
			// 
			this->button4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Location = System::Drawing::Point(2, 140);
			this->button4->Margin = System::Windows::Forms::Padding(0);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(65, 20);
			this->button4->TabIndex = 11;
			this->button4->Text = L"Adaptive";
			this->button4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MainForm::button4Click);
			// 
			// button3
			// 
			this->button3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Location = System::Drawing::Point(67, 140);
			this->button3->Margin = System::Windows::Forms::Padding(0);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(66, 20);
			this->button3->TabIndex = 10;
			this->button3->Text = L"Confirm";
			this->button3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::button3Click);
			// 
			// textBox3
			// 
			this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox3->Location = System::Drawing::Point(67, 120);
			this->textBox3->Margin = System::Windows::Forms::Padding(0);
			this->textBox3->MaxLength = 3;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(66, 20);
			this->textBox3->TabIndex = 9;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxTextChanged);
			this->textBox3->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::textBoxKeyDown);
			this->textBox3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBoxKeyPress);
			// 
			// textBox2
			// 
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox2->Location = System::Drawing::Point(67, 100);
			this->textBox2->Margin = System::Windows::Forms::Padding(0);
			this->textBox2->MaxLength = 3;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(66, 20);
			this->textBox2->TabIndex = 8;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxTextChanged);
			this->textBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::textBoxKeyDown);
			this->textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBoxKeyPress);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(2, 120);
			this->label5->Margin = System::Windows::Forms::Padding(0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(65, 20);
			this->label5->TabIndex = 6;
			this->label5->Text = L"Value2 (b1)";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(2, 100);
			this->label4->Margin = System::Windows::Forms::Padding(0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(65, 20);
			this->label4->TabIndex = 5;
			this->label4->Text = L"Value1 (b0)";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(2, 80);
			this->label3->Margin = System::Windows::Forms::Padding(0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(65, 20);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Threshold";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->tableLayout->SetColumnSpan(this->label2, 2);
			this->label2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(2, 60);
			this->label2->Margin = System::Windows::Forms::Padding(0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(131, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Binarization";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// button2
			// 
			this->tableLayout->SetColumnSpan(this->button2, 2);
			this->button2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(2, 40);
			this->button2->Margin = System::Windows::Forms::Padding(0);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(131, 20);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Halftone";
			this->button2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2Click);
			// 
			// button1
			// 
			this->tableLayout->SetColumnSpan(this->button1, 2);
			this->button1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(2, 20);
			this->button1->Margin = System::Windows::Forms::Padding(0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(131, 20);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Negative";
			this->button1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->tableLayout->SetColumnSpan(this->label1, 2);
			this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(2, 0);
			this->label1->Margin = System::Windows::Forms::Padding(0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(131, 20);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Primitive";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// textBox1
			// 
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox1->Location = System::Drawing::Point(67, 80);
			this->textBox1->Margin = System::Windows::Forms::Padding(0);
			this->textBox1->MaxLength = 3;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(66, 20);
			this->textBox1->TabIndex = 7;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MainForm::textBoxTextChanged);
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::textBoxKeyDown);
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBoxKeyPress);
			// 
			// comboBox1
			// 
			this->tableLayout->SetColumnSpan(this->comboBox1, 2);
			this->comboBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->comboBox1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
				L"Low-frequency", L"Rect", L"Cross", L"Rhombus",
					L"Horizontal lines", L"Vertical lines", L"Diagonal 45", L"Diagonal 135"
			});
			this->comboBox1->Location = System::Drawing::Point(2, 400);
			this->comboBox1->Margin = System::Windows::Forms::Padding(0);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(131, 21);
			this->comboBox1->TabIndex = 32;
			this->comboBox1->Text = L"Type";
			// 
			// comboBox2
			// 
			this->comboBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->tableLayout->SetColumnSpan(this->comboBox2, 2);
			this->comboBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->comboBox2->Items->Add(L"3x3");
			this->comboBox2->Items->Add(L"5x5");
			this->comboBox2->Items->Add(L"7x7");
			this->comboBox2->Items->Add(L"9x9");
			this->comboBox2->Items->Add(L"11x11");
			this->comboBox2->Items->Add(L"13x13");
			this->comboBox2->Items->Add(L"15x15");
			this->comboBox2->Location = System::Drawing::Point(2, 420);
			this->comboBox2->Margin = System::Windows::Forms::Padding(0);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->ReadOnly = true;
			this->comboBox2->Size = System::Drawing::Size(131, 16);
			this->comboBox2->TabIndex = 41;
			this->comboBox2->Text = L"Size";
			// 
			// splitContainer
			// 
			this->splitContainer->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitContainer->Location = System::Drawing::Point(3, 3);
			this->splitContainer->Margin = System::Windows::Forms::Padding(0);
			this->splitContainer->Name = L"splitContainer";
			// 
			// splitContainer.Panel1
			// 
			this->splitContainer->Panel1->AutoScroll = true;
			this->splitContainer->Panel1->Controls->Add(this->pictureBox1);
			// 
			// splitContainer.Panel2
			// 
			this->splitContainer->Panel2->AutoScroll = true;
			this->splitContainer->Panel2->Controls->Add(this->pictureBox2);
			this->splitContainer->Size = System::Drawing::Size(357, 219);
			this->splitContainer->SplitterDistance = 180;
			this->splitContainer->TabIndex = 0;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(100, 50);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MainForm::pictureBoxClick);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(0, 0);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(100, 50);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &MainForm::pictureBoxClick);
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->gallery);
			this->tabPage2->Controls->Add(this->propTable);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(516, 225);
			this->tabPage2->TabIndex = 2;
			this->tabPage2->Text = L"Gallery";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// gallery
			// 
			this->gallery->AutoScroll = true;
			this->gallery->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->gallery->Dock = System::Windows::Forms::DockStyle::Fill;
			this->gallery->Location = System::Drawing::Point(0, 0);
			this->gallery->Margin = System::Windows::Forms::Padding(6, 3, 3, 3);
			this->gallery->Name = L"gallery";
			this->gallery->Size = System::Drawing::Size(366, 225);
			this->gallery->TabIndex = 1;
			// 
			// propTable
			// 
			this->propTable->ColumnCount = 2;
			this->propTable->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->propTable->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->propTable->Controls->Add(this->label15, 0, 1);
			this->propTable->Controls->Add(this->typeLabel, 0, 0);
			this->propTable->Controls->Add(this->description, 0, 2);
			this->propTable->Dock = System::Windows::Forms::DockStyle::Right;
			this->propTable->Location = System::Drawing::Point(366, 0);
			this->propTable->Name = L"propTable";
			this->propTable->Padding = System::Windows::Forms::Padding(2, 0, 0, 0);
			this->propTable->RowCount = 8;
			this->propTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->propTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->propTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->propTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->propTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->propTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->propTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->propTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->propTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->propTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->propTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->propTable->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->propTable->Size = System::Drawing::Size(150, 225);
			this->propTable->TabIndex = 0;
			// 
			// tabPage3
			// 
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(516, 225);
			this->tabPage3->TabIndex = 1;
			this->tabPage3->Text = L"Log";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// statusStrip
			// 
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->countLabel, this->cur1Label,
					this->cur2Label
			});
			this->statusStrip->Location = System::Drawing::Point(0, 279);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->Size = System::Drawing::Size(524, 22);
			this->statusStrip->TabIndex = 2;
			this->statusStrip->Text = L"statusStrip1";
			// 
			// countLabel
			// 
			this->countLabel->Name = L"countLabel";
			this->countLabel->Size = System::Drawing::Size(52, 17);
			this->countLabel->Text = L"Count: 0";
			// 
			// cur1Label
			// 
			this->cur1Label->Name = L"cur1Label";
			this->cur1Label->Size = System::Drawing::Size(44, 17);
			this->cur1Label->Text = L"Cur1: 0";
			// 
			// cur2Label
			// 
			this->cur2Label->Name = L"cur2Label";
			this->cur2Label->Size = System::Drawing::Size(44, 17);
			this->cur2Label->Text = L"Cur2: 0";
			this->cur2Label->Visible = false;
			// 
			// progressBar
			// 
			this->progressBar->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->progressBar->Location = System::Drawing::Point(90, 6);
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(430, 10);
			this->progressBar->TabIndex = 3;
			// 
			// typeLabel
			// 
			this->propTable->SetColumnSpan(this->typeLabel, 2);
			this->typeLabel->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->typeLabel->Location = System::Drawing::Point(5, 0);
			this->typeLabel->Name = L"typeLabel";
			this->typeLabel->Size = System::Drawing::Size(142, 20);
			this->typeLabel->TabIndex = 0;
			this->typeLabel->Text = L"Gallery is empty";
			this->typeLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// description
			// 
			this->description->AutoEllipsis = true;
			this->propTable->SetColumnSpan(this->description, 2);
			this->description->Dock = System::Windows::Forms::DockStyle::Fill;
			this->description->Location = System::Drawing::Point(5, 40);
			this->description->Name = L"description";
			this->propTable->SetRowSpan(this->description, 3);
			this->description->Size = System::Drawing::Size(142, 60);
			this->description->TabIndex = 1;
			this->description->Text = L"Empty";
			// 
			// label15
			// 
			this->propTable->SetColumnSpan(this->label15, 2);
			this->label15->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label15->Location = System::Drawing::Point(5, 20);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(142, 20);
			this->label15->TabIndex = 2;
			this->label15->Text = L"Description";
			this->label15->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ClientSize = System::Drawing::Size(524, 301);
			this->Controls->Add(this->progressBar);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->tabControl);
			this->Controls->Add(this->menuStrip);
			this->DoubleBuffered = true;
			this->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->MainMenuStrip = this->menuStrip;
			this->Name = L"MainForm";
			this->ShowIcon = false;
			this->Text = L"MainForm";
			this->SizeChanged += gcnew System::EventHandler(this, &MainForm::MainFormSizeChanged);
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->tabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tableLayout->ResumeLayout(false);
			this->tableLayout->PerformLayout();
			this->splitContainer->Panel1->ResumeLayout(false);
			this->splitContainer->Panel1->PerformLayout();
			this->splitContainer->Panel2->ResumeLayout(false);
			this->splitContainer->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer))->EndInit();
			this->splitContainer->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->tabPage2->ResumeLayout(false);
			this->propTable->ResumeLayout(false);
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		Void openItemClick(Object^, EventArgs^);
		Void saveItemClick(Object^, EventArgs^);
		Void saveAsItemClick(Object^, EventArgs^);
		Void undoItemClick(Object^, EventArgs^);
		Void redoItemClick(Object^, EventArgs^);
		Void doubleItemClick(Object^, EventArgs^);
		Void pictureBoxClick(Object^, EventArgs^);
		Void MainFormSizeChanged(Object^, EventArgs^);
		Void setColors();
		Void addPB();
		Void progressBarIncValue();
		Void updatePictures();
		Void disableControls();
		Void button1Click(Object^, EventArgs^);
		Void button2Click(Object^, EventArgs^);
		Void button3Click(Object^, EventArgs^);
		Void button4Click(Object^, EventArgs^);
		Void button5Click(Object^, EventArgs^);
		Void button6Click(Object^, EventArgs^);
		Void button7Click(Object^, EventArgs^);
		Void button8Click(Object^, EventArgs^);
		Void button9Click(Object^, EventArgs^);
		Void button10Click(Object^, EventArgs^);
		Void button11Click(Object^, EventArgs^);
		Void button12Click(Object^, EventArgs^);
		Void textBoxKeyDown(Object^, KeyEventArgs^);
		Void textBoxKeyPress(Object^, KeyPressEventArgs^);
		Void textBoxTextChanged(Object^, EventArgs^);
	};
}
