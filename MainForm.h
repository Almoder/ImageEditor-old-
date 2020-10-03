namespace Lab1 {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	ref class MainForm;
	ref class Entry;

	public ref class Entry {
	public: 
		String^ data;
		unsigned int type;
		Entry(void);
		Entry(int);
		Entry(int, int, int, int);
		Entry(int, double, double);
	private: 
		void initData(int);
	};

	public ref class MainForm : public System::Windows::Forms::Form	{
	private: 
		Windows::Forms::MenuStrip^  menuStrip;
		Windows::Forms::ToolStripMenuItem^  fileMI, ^openMI, ^saveMI, ^saveAsMI, ^exitMI;
		Windows::Forms::ToolStripMenuItem^  actionsMI, ^transformMI, ^binarMI;
		Windows::Forms::ToolStripMenuItem^  powerMI, ^negativeMI, ^halftoneMI;
		Windows::Forms::ToolStripMenuItem^  viewMI, ^toolpanelMI, ^changeBrightMI, ^aboutMI;
		Windows::Forms::TabControl^  tabControl;
		Windows::Forms::TabPage^  editorPage, ^logPage;
	    Windows::Forms::Panel^  editorPanel, ^toolPanel;
		Windows::Forms::PictureBox^  pictureBox;
		Windows::Forms::GroupBox^  transformBox, ^binaryBox, ^powerBox;
		Windows::Forms::Label^  toolboxTitle, ^label1_1, ^label1_2, ^label2_1, ^label2_2, ^label2_3, ^label3_1, ^label3_2;
		Windows::Forms::Button^  negativeButton, ^halftoneButton;
		Windows::Forms::TextBox^  binaryBoxTextBox1, ^binaryBoxTextBox2, ^binaryBoxTextBox3, ^powerBoxTextBox1, ^powerBoxTextBox2;
		Windows::Forms::TrackBar^  binaryBoxTrackBar1, ^binaryBoxTrackBar2, ^binaryBoxTrackBar3, ^powerBoxTrackBar1, ^powerBoxTrackBar2;
		Windows::Forms::ListBox^  logBox;
		System::ComponentModel::BackgroundWorker^ backgroundWorker;
		System::ComponentModel::Container^ components;
		array<Bitmap^>^ images;
		array<Entry^>^ log;
		String^ fileName;
		int size, logsize, current, sFDindex, t, b0, b1;
		double c, g;
		System::Windows::Forms::ProgressBar^  progressBar;


	public:
		MainForm(void);
	protected:
		~MainForm();

#pragma region Windows Form Designer generated code

		void InitializeComponent(void) {
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->fileMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->actionsMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->transformMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->negativeMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->halftoneMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->binarMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->powerMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeBrightMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->viewMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolpanelMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->editorPage = (gcnew System::Windows::Forms::TabPage());
			this->toolPanel = (gcnew System::Windows::Forms::Panel());
			this->powerBox = (gcnew System::Windows::Forms::GroupBox());
			this->powerBoxTrackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->powerBoxTrackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->powerBoxTextBox2 = (gcnew System::Windows::Forms::TextBox());
			this->powerBoxTextBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label3_2 = (gcnew System::Windows::Forms::Label());
			this->label3_1 = (gcnew System::Windows::Forms::Label());
			this->binaryBox = (gcnew System::Windows::Forms::GroupBox());
			this->binaryBoxTrackBar3 = (gcnew System::Windows::Forms::TrackBar());
			this->binaryBoxTrackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->binaryBoxTrackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->binaryBoxTextBox3 = (gcnew System::Windows::Forms::TextBox());
			this->binaryBoxTextBox2 = (gcnew System::Windows::Forms::TextBox());
			this->binaryBoxTextBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2_3 = (gcnew System::Windows::Forms::Label());
			this->label2_2 = (gcnew System::Windows::Forms::Label());
			this->label2_1 = (gcnew System::Windows::Forms::Label());
			this->transformBox = (gcnew System::Windows::Forms::GroupBox());
			this->halftoneButton = (gcnew System::Windows::Forms::Button());
			this->negativeButton = (gcnew System::Windows::Forms::Button());
			this->label1_2 = (gcnew System::Windows::Forms::Label());
			this->label1_1 = (gcnew System::Windows::Forms::Label());
			this->toolboxTitle = (gcnew System::Windows::Forms::Label());
			this->editorPanel = (gcnew System::Windows::Forms::Panel());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->logPage = (gcnew System::Windows::Forms::TabPage());
			this->logBox = (gcnew System::Windows::Forms::ListBox());
			this->backgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->menuStrip->SuspendLayout();
			this->tabControl->SuspendLayout();
			this->editorPage->SuspendLayout();
			this->toolPanel->SuspendLayout();
			this->powerBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->powerBoxTrackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->powerBoxTrackBar1))->BeginInit();
			this->binaryBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->binaryBoxTrackBar3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->binaryBoxTrackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->binaryBoxTrackBar1))->BeginInit();
			this->transformBox->SuspendLayout();
			this->editorPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->logPage->SuspendLayout();
			this->SuspendLayout();
			this->menuStrip->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->menuStrip->Font = (gcnew System::Drawing::Font(L"Arial", 9));
			this->menuStrip->ForeColor = System::Drawing::SystemColors::Window;
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->fileMI, this->actionsMI,
					this->viewMI, this->aboutMI
			});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(724, 24);
			this->menuStrip->TabIndex = 0;
			this->menuStrip->Text = L"menuStrip1";
			this->fileMI->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->openMI, this->saveMI,
					this->saveAsMI, this->exitMI
			});
			this->fileMI->ForeColor = System::Drawing::SystemColors::Window;
			this->fileMI->Name = L"fileMI";
			this->fileMI->Size = System::Drawing::Size(49, 20);
			this->fileMI->Text = L"Файл";
			this->openMI->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->openMI->ForeColor = System::Drawing::SystemColors::Window;
			this->openMI->Name = L"openMI";
			this->openMI->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->openMI->Size = System::Drawing::Size(229, 22);
			this->openMI->Text = L"Открыть";
			this->openMI->Click += gcnew System::EventHandler(this, &MainForm::openMIClick);
			this->saveMI->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->saveMI->ForeColor = System::Drawing::SystemColors::Window;
			this->saveMI->Name = L"saveMI";
			this->saveMI->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->saveMI->Size = System::Drawing::Size(229, 22);
			this->saveMI->Text = L"Сохранить";
			this->saveMI->Click += gcnew System::EventHandler(this, &MainForm::saveMIClick);
			this->saveAsMI->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->saveAsMI->ForeColor = System::Drawing::SystemColors::Window;
			this->saveAsMI->Name = L"saveAsMI";
			this->saveAsMI->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
				| System::Windows::Forms::Keys::S));
			this->saveAsMI->Size = System::Drawing::Size(229, 22);
			this->saveAsMI->Text = L"Сохранить как";
			this->saveAsMI->Click += gcnew System::EventHandler(this, &MainForm::saveAsMIClick);
			this->exitMI->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->exitMI->ForeColor = System::Drawing::SystemColors::Window;
			this->exitMI->Name = L"exitMI";
			this->exitMI->Size = System::Drawing::Size(229, 22);
			this->exitMI->Text = L"Выход";
			this->exitMI->Click += gcnew System::EventHandler(this, &MainForm::exitMIClick);
			this->actionsMI->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->transformMI, this->changeBrightMI });
			this->actionsMI->Name = L"actionsMI";
			this->actionsMI->Size = System::Drawing::Size(72, 20);
			this->actionsMI->Text = L"Действия";
			this->transformMI->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->transformMI->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->negativeMI,
					this->halftoneMI, this->binarMI, this->powerMI
			});
			this->transformMI->ForeColor = System::Drawing::SystemColors::Window;
			this->transformMI->Name = L"transformMI";
			this->transformMI->Size = System::Drawing::Size(185, 22);
			this->transformMI->Text = L"Преобразовать";
			this->negativeMI->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->negativeMI->ForeColor = System::Drawing::SystemColors::Window;
			this->negativeMI->Name = L"negativeMI";
			this->negativeMI->Size = System::Drawing::Size(148, 22);
			this->negativeMI->Text = L"Негатив";
			this->negativeMI->Click += gcnew System::EventHandler(this, &MainForm::negativeClick);
			this->halftoneMI->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->halftoneMI->ForeColor = System::Drawing::SystemColors::Window;
			this->halftoneMI->Name = L"halftoneMI";
			this->halftoneMI->Size = System::Drawing::Size(148, 22);
			this->halftoneMI->Text = L"Полутоновое";
			this->halftoneMI->Click += gcnew System::EventHandler(this, &MainForm::halftoneClick);
			this->binarMI->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->binarMI->ForeColor = System::Drawing::SystemColors::Window;
			this->binarMI->Name = L"binarMI";
			this->binarMI->Size = System::Drawing::Size(148, 22);
			this->binarMI->Text = L"Бинарное";
			this->binarMI->Click += gcnew System::EventHandler(this, &MainForm::binarClick);
			this->powerMI->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->powerMI->ForeColor = System::Drawing::SystemColors::Window;
			this->powerMI->Name = L"powerMI";
			this->powerMI->Size = System::Drawing::Size(148, 22);
			this->powerMI->Text = L"Степенное";
			this->powerMI->Click += gcnew System::EventHandler(this, &MainForm::powerClick);
			this->changeBrightMI->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->changeBrightMI->ForeColor = System::Drawing::SystemColors::Window;
			this->changeBrightMI->Name = L"changeBrightMI";
			this->changeBrightMI->Size = System::Drawing::Size(185, 22);
			this->changeBrightMI->Text = L"Извенение яркости";
			this->viewMI->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolpanelMI });
			this->viewMI->Name = L"viewMI";
			this->viewMI->Size = System::Drawing::Size(41, 20);
			this->viewMI->Text = L"Вид";
			this->toolpanelMI->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->toolpanelMI->CheckOnClick = true;
			this->toolpanelMI->ForeColor = System::Drawing::SystemColors::Window;
			this->toolpanelMI->Name = L"toolpanelMI";
			this->toolpanelMI->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::T));
			this->toolpanelMI->Size = System::Drawing::Size(233, 22);
			this->toolpanelMI->Text = L"Панель инструментов";
			this->toolpanelMI->Click += gcnew System::EventHandler(this, &MainForm::toolPanelShowHide);
			this->aboutMI->Name = L"aboutMI";
			this->aboutMI->Size = System::Drawing::Size(68, 20);
			this->aboutMI->Text = L"Справка";
			this->tabControl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl->Controls->Add(this->editorPage);
			this->tabControl->Controls->Add(this->logPage);
			this->tabControl->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tabControl->ForeColor = System::Drawing::SystemColors::Window;
			this->tabControl->HotTrack = true;
			this->tabControl->Location = System::Drawing::Point(0, 24);
			this->tabControl->Margin = System::Windows::Forms::Padding(5, 0, 5, 5);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(724, 390);
			this->tabControl->SizeMode = System::Windows::Forms::TabSizeMode::FillToRight;
			this->tabControl->TabIndex = 2;
			this->editorPage->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->editorPage->Controls->Add(this->toolPanel);
			this->editorPage->Controls->Add(this->editorPanel);
			this->editorPage->ForeColor = System::Drawing::SystemColors::Window;
			this->editorPage->Location = System::Drawing::Point(4, 24);
			this->editorPage->Name = L"editorPage";
			this->editorPage->Padding = System::Windows::Forms::Padding(3);
			this->editorPage->Size = System::Drawing::Size(716, 362);
			this->editorPage->TabIndex = 0;
			this->editorPage->Text = L"Редактор";
			this->toolPanel->AutoScroll = true;
			this->toolPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->toolPanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->toolPanel->Controls->Add(this->powerBox);
			this->toolPanel->Controls->Add(this->binaryBox);
			this->toolPanel->Controls->Add(this->transformBox);
			this->toolPanel->Controls->Add(this->toolboxTitle);
			this->toolPanel->Dock = System::Windows::Forms::DockStyle::Right;
			this->toolPanel->Location = System::Drawing::Point(529, 3);
			this->toolPanel->Name = L"toolPanel";
			this->toolPanel->Size = System::Drawing::Size(184, 356);
			this->toolPanel->TabIndex = 3;
			this->powerBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->powerBox->Controls->Add(this->powerBoxTrackBar2);
			this->powerBox->Controls->Add(this->powerBoxTrackBar1);
			this->powerBox->Controls->Add(this->powerBoxTextBox2);
			this->powerBox->Controls->Add(this->powerBoxTextBox1);
			this->powerBox->Controls->Add(this->label3_2);
			this->powerBox->Controls->Add(this->label3_1);
			this->powerBox->ForeColor = System::Drawing::SystemColors::InactiveCaption;
			this->powerBox->Location = System::Drawing::Point(-2, 145);
			this->powerBox->Name = L"powerBox";
			this->powerBox->Size = System::Drawing::Size(184, 56);
			this->powerBox->TabIndex = 3;
			this->powerBox->TabStop = false;
			this->powerBox->Text = L"Степенное";
			this->powerBoxTrackBar2->AutoSize = false;
			this->powerBoxTrackBar2->Location = System::Drawing::Point(63, 33);
			this->powerBoxTrackBar2->Maximum = 50;
			this->powerBoxTrackBar2->Name = L"powerBoxTrackBar2";
			this->powerBoxTrackBar2->Size = System::Drawing::Size(109, 15);
			this->powerBoxTrackBar2->TabIndex = 9;
			this->powerBoxTrackBar2->TickStyle = System::Windows::Forms::TickStyle::None;
			this->powerBoxTrackBar2->Value = 25;
			this->powerBoxTrackBar2->ValueChanged += gcnew System::EventHandler(this, &MainForm::powerBoxTrackBar2ValueChanged);
			this->powerBoxTrackBar1->AutoSize = false;
			this->powerBoxTrackBar1->Location = System::Drawing::Point(63, 17);
			this->powerBoxTrackBar1->Maximum = 50;
			this->powerBoxTrackBar1->Name = L"powerBoxTrackBar1";
			this->powerBoxTrackBar1->Size = System::Drawing::Size(109, 15);
			this->powerBoxTrackBar1->TabIndex = 8;
			this->powerBoxTrackBar1->TickStyle = System::Windows::Forms::TickStyle::None;
			this->powerBoxTrackBar1->Value = 25;
			this->powerBoxTrackBar1->ValueChanged += gcnew System::EventHandler(this, &MainForm::powerBoxTrackBar1ValueChanged);
			this->powerBoxTextBox2->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->powerBoxTextBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->powerBoxTextBox2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->powerBoxTextBox2->ForeColor = System::Drawing::SystemColors::Window;
			this->powerBoxTextBox2->Location = System::Drawing::Point(26, 33);
			this->powerBoxTextBox2->Name = L"powerBoxTextBox2";
			this->powerBoxTextBox2->Size = System::Drawing::Size(31, 14);
			this->powerBoxTextBox2->TabIndex = 6;
			this->powerBoxTextBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->powerBoxTextBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::powerBoxTextBox2KeyDown);
			this->powerBoxTextBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBox_KeyPressDouble);
			this->powerBoxTextBox1->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->powerBoxTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->powerBoxTextBox1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->powerBoxTextBox1->ForeColor = System::Drawing::SystemColors::Window;
			this->powerBoxTextBox1->Location = System::Drawing::Point(26, 17);
			this->powerBoxTextBox1->Name = L"powerBoxTextBox1";
			this->powerBoxTextBox1->Size = System::Drawing::Size(31, 14);
			this->powerBoxTextBox1->TabIndex = 5;
			this->powerBoxTextBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->powerBoxTextBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::powerBoxTextBox1KeyDown);
			this->powerBoxTextBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBox_KeyPressDouble);
			this->label3_2->AutoSize = true;
			this->label3_2->ForeColor = System::Drawing::SystemColors::Window;
			this->label3_2->Location = System::Drawing::Point(5, 33);
			this->label3_2->Name = L"label3_2";
			this->label3_2->Size = System::Drawing::Size(16, 15);
			this->label3_2->TabIndex = 3;
			this->label3_2->Text = L"G";
			this->label3_1->AutoSize = true;
			this->label3_1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3_1->ForeColor = System::Drawing::SystemColors::Window;
			this->label3_1->Location = System::Drawing::Point(5, 17);
			this->label3_1->Name = L"label3_1";
			this->label3_1->Size = System::Drawing::Size(16, 15);
			this->label3_1->TabIndex = 2;
			this->label3_1->Text = L"C";
			this->binaryBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->binaryBox->Controls->Add(this->binaryBoxTrackBar3);
			this->binaryBox->Controls->Add(this->binaryBoxTrackBar2);
			this->binaryBox->Controls->Add(this->binaryBoxTrackBar1);
			this->binaryBox->Controls->Add(this->binaryBoxTextBox3);
			this->binaryBox->Controls->Add(this->binaryBoxTextBox2);
			this->binaryBox->Controls->Add(this->binaryBoxTextBox1);
			this->binaryBox->Controls->Add(this->label2_3);
			this->binaryBox->Controls->Add(this->label2_2);
			this->binaryBox->Controls->Add(this->label2_1);
			this->binaryBox->ForeColor = System::Drawing::SystemColors::InactiveCaption;
			this->binaryBox->Location = System::Drawing::Point(-2, 74);
			this->binaryBox->Name = L"binaryBox";
			this->binaryBox->Size = System::Drawing::Size(184, 71);
			this->binaryBox->TabIndex = 2;
			this->binaryBox->TabStop = false;
			this->binaryBox->Text = L"Бинаризация";
			this->binaryBoxTrackBar3->AutoSize = false;
			this->binaryBoxTrackBar3->Location = System::Drawing::Point(63, 49);
			this->binaryBoxTrackBar3->Maximum = 255;
			this->binaryBoxTrackBar3->Name = L"binaryBoxTrackBar3";
			this->binaryBoxTrackBar3->Size = System::Drawing::Size(109, 15);
			this->binaryBoxTrackBar3->TabIndex = 10;
			this->binaryBoxTrackBar3->TickStyle = System::Windows::Forms::TickStyle::None;
			this->binaryBoxTrackBar3->ValueChanged += gcnew System::EventHandler(this, &MainForm::binaryBoxTrackBar3ValueChanged);
			this->binaryBoxTrackBar2->AutoSize = false;
			this->binaryBoxTrackBar2->Location = System::Drawing::Point(63, 33);
			this->binaryBoxTrackBar2->Maximum = 255;
			this->binaryBoxTrackBar2->Name = L"binaryBoxTrackBar2";
			this->binaryBoxTrackBar2->Size = System::Drawing::Size(109, 15);
			this->binaryBoxTrackBar2->TabIndex = 9;
			this->binaryBoxTrackBar2->TickStyle = System::Windows::Forms::TickStyle::None;
			this->binaryBoxTrackBar2->ValueChanged += gcnew System::EventHandler(this, &MainForm::binaryBoxTrackBar2ValueChanged);
			this->binaryBoxTrackBar1->AutoSize = false;
			this->binaryBoxTrackBar1->Location = System::Drawing::Point(63, 17);
			this->binaryBoxTrackBar1->Maximum = 255;
			this->binaryBoxTrackBar1->Name = L"binaryBoxTrackBar1";
			this->binaryBoxTrackBar1->Size = System::Drawing::Size(109, 15);
			this->binaryBoxTrackBar1->TabIndex = 8;
			this->binaryBoxTrackBar1->TickStyle = System::Windows::Forms::TickStyle::None;
			this->binaryBoxTrackBar1->ValueChanged += gcnew System::EventHandler(this, &MainForm::binaryBoxTrackBar1ValueChanged);
			this->binaryBoxTextBox3->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->binaryBoxTextBox3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->binaryBoxTextBox3->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->binaryBoxTextBox3->ForeColor = System::Drawing::SystemColors::Window;
			this->binaryBoxTextBox3->Location = System::Drawing::Point(26, 49);
			this->binaryBoxTextBox3->Name = L"binaryBoxTextBox3";
			this->binaryBoxTextBox3->Size = System::Drawing::Size(31, 14);
			this->binaryBoxTextBox3->TabIndex = 7;
			this->binaryBoxTextBox3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->binaryBoxTextBox3->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::binaryBoxTextBox3KeyDown);
			this->binaryBoxTextBox3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBox_KeyPressInt);
			this->binaryBoxTextBox2->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->binaryBoxTextBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->binaryBoxTextBox2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->binaryBoxTextBox2->ForeColor = System::Drawing::SystemColors::Window;
			this->binaryBoxTextBox2->Location = System::Drawing::Point(26, 33);
			this->binaryBoxTextBox2->Name = L"binaryBoxTextBox2";
			this->binaryBoxTextBox2->Size = System::Drawing::Size(31, 14);
			this->binaryBoxTextBox2->TabIndex = 6;
			this->binaryBoxTextBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->binaryBoxTextBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::binaryBoxTextBox2KeyDown);
			this->binaryBoxTextBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBox_KeyPressInt);
			this->binaryBoxTextBox1->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->binaryBoxTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->binaryBoxTextBox1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->binaryBoxTextBox1->ForeColor = System::Drawing::SystemColors::Window;
			this->binaryBoxTextBox1->Location = System::Drawing::Point(26, 17);
			this->binaryBoxTextBox1->Name = L"binaryBoxTextBox1";
			this->binaryBoxTextBox1->Size = System::Drawing::Size(31, 14);
			this->binaryBoxTextBox1->TabIndex = 5;
			this->binaryBoxTextBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->binaryBoxTextBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::binaryBoxTextBox1KeyDown);
			this->binaryBoxTextBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBox_KeyPressInt);
			this->label2_3->AutoSize = true;
			this->label2_3->ForeColor = System::Drawing::SystemColors::Window;
			this->label2_3->Location = System::Drawing::Point(5, 49);
			this->label2_3->Name = L"label2_3";
			this->label2_3->Size = System::Drawing::Size(21, 15);
			this->label2_3->TabIndex = 4;
			this->label2_3->Text = L"b1";
			this->label2_2->AutoSize = true;
			this->label2_2->ForeColor = System::Drawing::SystemColors::Window;
			this->label2_2->Location = System::Drawing::Point(5, 33);
			this->label2_2->Name = L"label2_2";
			this->label2_2->Size = System::Drawing::Size(21, 15);
			this->label2_2->TabIndex = 3;
			this->label2_2->Text = L"b0";
			this->label2_1->AutoSize = true;
			this->label2_1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2_1->ForeColor = System::Drawing::SystemColors::Window;
			this->label2_1->Location = System::Drawing::Point(5, 17);
			this->label2_1->Name = L"label2_1";
			this->label2_1->Size = System::Drawing::Size(14, 15);
			this->label2_1->TabIndex = 2;
			this->label2_1->Text = L"T";
			this->transformBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->transformBox->Controls->Add(this->halftoneButton);
			this->transformBox->Controls->Add(this->negativeButton);
			this->transformBox->Controls->Add(this->label1_2);
			this->transformBox->Controls->Add(this->label1_1);
			this->transformBox->ForeColor = System::Drawing::SystemColors::InactiveCaption;
			this->transformBox->Location = System::Drawing::Point(-2, 18);
			this->transformBox->Name = L"transformBox";
			this->transformBox->Size = System::Drawing::Size(184, 56);
			this->transformBox->TabIndex = 1;
			this->transformBox->TabStop = false;
			this->transformBox->Text = L"Преобразования";
			this->halftoneButton->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->halftoneButton->Font = (gcnew System::Drawing::Font(L"Arial", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->halftoneButton->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->halftoneButton->Location = System::Drawing::Point(89, 33);
			this->halftoneButton->Margin = System::Windows::Forms::Padding(0, 3, 3, 3);
			this->halftoneButton->Name = L"halftoneButton";
			this->halftoneButton->Size = System::Drawing::Size(89, 17);
			this->halftoneButton->TabIndex = 3;
			this->halftoneButton->Text = L"Применить";
			this->halftoneButton->UseVisualStyleBackColor = true;
			this->halftoneButton->Click += gcnew System::EventHandler(this, &MainForm::halftoneClick);
			this->negativeButton->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->negativeButton->Font = (gcnew System::Drawing::Font(L"Arial", 8));
			this->negativeButton->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->negativeButton->Location = System::Drawing::Point(89, 17);
			this->negativeButton->Margin = System::Windows::Forms::Padding(0, 3, 3, 3);
			this->negativeButton->Name = L"negativeButton";
			this->negativeButton->Size = System::Drawing::Size(89, 17);
			this->negativeButton->TabIndex = 2;
			this->negativeButton->Text = L"Применить";
			this->negativeButton->UseVisualStyleBackColor = true;
			this->negativeButton->Click += gcnew System::EventHandler(this, &MainForm::negativeClick);
			this->label1_2->AutoSize = true;
			this->label1_2->ForeColor = System::Drawing::SystemColors::Window;
			this->label1_2->Location = System::Drawing::Point(5, 33);
			this->label1_2->Name = L"label1_2";
			this->label1_2->Size = System::Drawing::Size(81, 15);
			this->label1_2->TabIndex = 1;
			this->label1_2->Text = L"Полутоновое";
			this->label1_1->AutoSize = true;
			this->label1_1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1_1->ForeColor = System::Drawing::SystemColors::Window;
			this->label1_1->Location = System::Drawing::Point(5, 17);
			this->label1_1->Name = L"label1_1";
			this->label1_1->Size = System::Drawing::Size(52, 15);
			this->label1_1->TabIndex = 0;
			this->label1_1->Text = L"Негатив";
			this->toolboxTitle->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->toolboxTitle->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->toolboxTitle->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->toolboxTitle->Location = System::Drawing::Point(0, 0);
			this->toolboxTitle->Name = L"toolboxTitle";
			this->toolboxTitle->Size = System::Drawing::Size(180, 18);
			this->toolboxTitle->TabIndex = 0;
			this->toolboxTitle->Text = L"Инструменты";
			this->editorPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->editorPanel->AutoScroll = true;
			this->editorPanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->editorPanel->Controls->Add(this->pictureBox);
			this->editorPanel->Location = System::Drawing::Point(3, 3);
			this->editorPanel->Name = L"editorPanel";
			this->editorPanel->Size = System::Drawing::Size(522, 356);
			this->editorPanel->TabIndex = 1;
			this->pictureBox->Location = System::Drawing::Point(0, 0);
			this->pictureBox->Margin = System::Windows::Forms::Padding(5);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(1, 1);
			this->pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;
			this->logPage->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->logPage->Controls->Add(this->logBox);
			this->logPage->ForeColor = System::Drawing::SystemColors::Window;
			this->logPage->Location = System::Drawing::Point(4, 24);
			this->logPage->Name = L"logPage";
			this->logPage->Padding = System::Windows::Forms::Padding(3);
			this->logPage->Size = System::Drawing::Size(716, 362);
			this->logPage->TabIndex = 1;
			this->logPage->Text = L"Log";
			this->logBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->logBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->logBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->logBox->ForeColor = System::Drawing::SystemColors::Window;
			this->logBox->FormattingEnabled = true;
			this->logBox->ItemHeight = 15;
			this->logBox->Location = System::Drawing::Point(3, 3);
			this->logBox->Name = L"logBox";
			this->logBox->ScrollAlwaysVisible = true;
			this->logBox->Size = System::Drawing::Size(710, 330);
			this->logBox->TabIndex = 0;
			this->backgroundWorker->WorkerReportsProgress = true;
			this->backgroundWorker->WorkerSupportsCancellation = true;
			this->progressBar->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->progressBar->Location = System::Drawing::Point(240, 6);
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(480, 10);
			this->progressBar->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			this->progressBar->TabIndex = 1;
			this->progressBar->Visible = false;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->ClientSize = System::Drawing::Size(724, 417);
			this->Controls->Add(this->progressBar);
			this->Controls->Add(this->tabControl);
			this->Controls->Add(this->menuStrip);
			this->MainMenuStrip = this->menuStrip;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Image Editor";
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->tabControl->ResumeLayout(false);
			this->editorPage->ResumeLayout(false);
			this->toolPanel->ResumeLayout(false);
			this->powerBox->ResumeLayout(false);
			this->powerBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->powerBoxTrackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->powerBoxTrackBar1))->EndInit();
			this->binaryBox->ResumeLayout(false);
			this->binaryBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->binaryBoxTrackBar3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->binaryBoxTrackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->binaryBoxTrackBar1))->EndInit();
			this->transformBox->ResumeLayout(false);
			this->transformBox->PerformLayout();
			this->editorPanel->ResumeLayout(false);
			this->editorPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->logPage->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		void InitializeBackgoundWorker();
#pragma endregion
	private: 
		Void openMIClick(Object^, EventArgs^);
		Void saveMIClick(Object^, EventArgs^);
		Void saveAsMIClick(Object^, EventArgs^);
		Void exitMIClick(Object^, EventArgs^);
		Void negativeClick(Object^, EventArgs^);
		Void halftoneClick(Object^, EventArgs^);
		Void binarClick(Object^, EventArgs^);
		Void powerClick(Object^, EventArgs^);
		Bitmap^ negative(Bitmap^, BackgroundWorker^);
		Bitmap^ halftone(Bitmap^, BackgroundWorker^);
		Bitmap^ binar(Bitmap^, int, int, int);
		Bitmap^ power(Bitmap^, double, double);
		Void toolPanelShowHide(Object^, EventArgs^);
		Void textBox_KeyPressInt(Object^, KeyPressEventArgs^);
		Void textBox_KeyPressDouble(Object^, KeyPressEventArgs^);
		Void progressBar_SizeChanged(Object^, EventArgs^);
		Void buttonsEnable(bool);
		Void binaryBoxTextBox1KeyDown(Object^, KeyEventArgs^);
		Void binaryBoxTextBox2KeyDown(Object^, KeyEventArgs^);
		Void binaryBoxTextBox3KeyDown(Object^, KeyEventArgs^);
		Void powerBoxTextBox1KeyDown(Object^, KeyEventArgs^);
		Void powerBoxTextBox2KeyDown(Object^, KeyEventArgs^);
		Void binaryBoxTrackBar1ValueChanged(Object^, EventArgs^);
		Void binaryBoxTrackBar2ValueChanged(Object^, EventArgs^);
		Void binaryBoxTrackBar3ValueChanged(Object^, EventArgs^);
		Void powerBoxTrackBar1ValueChanged(Object^, EventArgs^);
		Void powerBoxTrackBar2ValueChanged(Object^, EventArgs^);
		Void backgroundWorkerDoWork(Object^, DoWorkEventArgs^);
		Void backgroundWorkerRunWorkerCompleted(Object^, RunWorkerCompletedEventArgs^);
	public:
		Void dialogBinar(int, int, int);
		Void dialogPower(double, double);
		Void backUpFromPictureBox();
	};
}
