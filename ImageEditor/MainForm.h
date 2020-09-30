namespace Lab1 {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	ref class MainForm;	//<-ПРОТОТИПЫ КЛАССОВ
	ref class Entry;	//<-(Designer сосать)

	public ref class Entry {
	private: void initData(int);
	public: String^ data;
	public: unsigned int type;
			Entry(void);
			Entry(int);
			Entry(int, int, int, int);
			Entry(int, double, double);
	};

	public ref class MainForm : public System::Windows::Forms::Form	{
	private: System::Windows::Forms::MenuStrip^  menuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  fileMI;
	private: System::Windows::Forms::ToolStripMenuItem^  openMI;
	private: System::Windows::Forms::ToolStripMenuItem^  saveMI;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsMI;
	private: System::Windows::Forms::ToolStripMenuItem^  exitMI;
	private: System::Windows::Forms::ToolStripMenuItem^  actionsMI;
	private: System::Windows::Forms::ToolStripMenuItem^  transformMI;
	private: System::Windows::Forms::ToolStripMenuItem^  binarMI;
	private: System::Windows::Forms::ToolStripMenuItem^  powerMI;
	private: System::Windows::Forms::ToolStripMenuItem^  negativeMI;
	private: System::Windows::Forms::ToolStripMenuItem^  halftoneMI;
	private: System::Windows::Forms::ToolStripMenuItem^  viewMI;
	private: System::Windows::Forms::ToolStripMenuItem^  toolpanelMI;
	private: System::Windows::Forms::ToolStripMenuItem^  chngBrightMI;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutMI;
	private: System::Windows::Forms::TabControl^  tabControl;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::PictureBox^  pictureBox;
	private: System::Windows::Forms::Panel^  editorPanel;
	private: System::Windows::Forms::Panel^  toolPanel;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  toolboxTitle;
	private: System::Windows::Forms::Label^  label1_1;
	private: System::Windows::Forms::Label^  label1_2;
	private: System::Windows::Forms::Label^  label2_1;
	private: System::Windows::Forms::Label^  label2_2;
	private: System::Windows::Forms::Label^  label2_3;
	private: System::Windows::Forms::Label^  label3_1;
	private: System::Windows::Forms::Label^  label3_2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  binTBx1;
	private: System::Windows::Forms::TextBox^  binTBx2;
	private: System::Windows::Forms::TextBox^  binTBx3;
	private: System::Windows::Forms::TextBox^  powTBx1;
	private: System::Windows::Forms::TextBox^  powTBx2;
	private: System::Windows::Forms::TrackBar^  binTBr3;
	private: System::Windows::Forms::TrackBar^  binTBr2;
	private: System::Windows::Forms::TrackBar^  binTBr1;
	private: System::Windows::Forms::TrackBar^  powTBr2;
	private: System::Windows::Forms::TrackBar^  powTBr1;
	private: System::Windows::Forms::ListBox^  logBox;
	private: System::ComponentModel::Container ^components;
	private: array<Bitmap^>^ images;
	private: array<Entry^>^ log;
	private: int size, logsize, current;

	public:
		MainForm(void)
		{
			InitializeComponent();
			size = 0; logsize = 0;
			current = 0;
			images = nullptr;
			log = nullptr;
		}

	protected:

		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
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
			this->chngBrightMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->viewMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolpanelMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutMI = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editorPanel = (gcnew System::Windows::Forms::Panel());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->toolPanel = (gcnew System::Windows::Forms::Panel());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->powTBr2 = (gcnew System::Windows::Forms::TrackBar());
			this->powTBr1 = (gcnew System::Windows::Forms::TrackBar());
			this->powTBx2 = (gcnew System::Windows::Forms::TextBox());
			this->powTBx1 = (gcnew System::Windows::Forms::TextBox());
			this->label3_2 = (gcnew System::Windows::Forms::Label());
			this->label3_1 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->binTBr3 = (gcnew System::Windows::Forms::TrackBar());
			this->binTBr2 = (gcnew System::Windows::Forms::TrackBar());
			this->binTBr1 = (gcnew System::Windows::Forms::TrackBar());
			this->binTBx3 = (gcnew System::Windows::Forms::TextBox());
			this->binTBx2 = (gcnew System::Windows::Forms::TextBox());
			this->binTBx1 = (gcnew System::Windows::Forms::TextBox());
			this->label2_3 = (gcnew System::Windows::Forms::Label());
			this->label2_2 = (gcnew System::Windows::Forms::Label());
			this->label2_1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1_2 = (gcnew System::Windows::Forms::Label());
			this->label1_1 = (gcnew System::Windows::Forms::Label());
			this->toolboxTitle = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->logBox = (gcnew System::Windows::Forms::ListBox());
			this->menuStrip->SuspendLayout();
			this->editorPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->BeginInit();
			this->tabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->toolPanel->SuspendLayout();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->powTBr2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->powTBr1))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->binTBr3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->binTBr2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->binTBr1))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->tabPage2->SuspendLayout();
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
			this->openMI->Click += gcnew System::EventHandler(this, &MainForm::openClick);
			this->saveMI->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->saveMI->ForeColor = System::Drawing::SystemColors::Window;
			this->saveMI->Name = L"saveMI";
			this->saveMI->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->saveMI->Size = System::Drawing::Size(229, 22);
			this->saveMI->Text = L"Сохранить";
			this->saveAsMI->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->saveAsMI->ForeColor = System::Drawing::SystemColors::Window;
			this->saveAsMI->Name = L"saveAsMI";
			this->saveAsMI->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
				| System::Windows::Forms::Keys::S));
			this->saveAsMI->Size = System::Drawing::Size(229, 22);
			this->saveAsMI->Text = L"Сохранить как";
			this->exitMI->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->exitMI->ForeColor = System::Drawing::SystemColors::Window;
			this->exitMI->Name = L"exitMI";
			this->exitMI->Size = System::Drawing::Size(229, 22);
			this->exitMI->Text = L"Выход";
			this->exitMI->Click += gcnew System::EventHandler(this, &MainForm::exitMIClick);
			this->actionsMI->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->transformMI, this->chngBrightMI });
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
			this->chngBrightMI->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->chngBrightMI->ForeColor = System::Drawing::SystemColors::Window;
			this->chngBrightMI->Name = L"chngBrightMI";
			this->chngBrightMI->Size = System::Drawing::Size(185, 22);
			this->chngBrightMI->Text = L"Извенение яркости";
			this->chngBrightMI->Click += gcnew System::EventHandler(this, &MainForm::chngBrightClick);
			this->viewMI->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolpanelMI });
			this->viewMI->Name = L"viewMI";
			this->viewMI->Size = System::Drawing::Size(41, 20);
			this->viewMI->Text = L"Вид";
			this->toolpanelMI->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->toolpanelMI->Checked = true;
			this->toolpanelMI->CheckState = System::Windows::Forms::CheckState::Indeterminate;
			this->toolpanelMI->ForeColor = System::Drawing::SystemColors::Window;
			this->toolpanelMI->Name = L"toolpanelMI";
			this->toolpanelMI->Size = System::Drawing::Size(199, 22);
			this->toolpanelMI->Text = L"Панель инструментов";
			this->toolpanelMI->Click += gcnew System::EventHandler(this, &MainForm::toolPanelShowHide);
			this->aboutMI->Name = L"aboutMI";
			this->aboutMI->Size = System::Drawing::Size(68, 20);
			this->aboutMI->Text = L"Справка";
			this->editorPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->editorPanel->AutoScroll = true;
			this->editorPanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->editorPanel->Controls->Add(this->pictureBox);
			this->editorPanel->Location = System::Drawing::Point(3, 3);
			this->editorPanel->Name = L"editorPanel";
			this->editorPanel->Size = System::Drawing::Size(525, 361);
			this->editorPanel->TabIndex = 1;
			this->pictureBox->Location = System::Drawing::Point(0, 0);
			this->pictureBox->Margin = System::Windows::Forms::Padding(5);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(359, 261);
			this->pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox->TabIndex = 0;
			this->pictureBox->TabStop = false;
			this->tabControl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl->Controls->Add(this->tabPage1);
			this->tabControl->Controls->Add(this->tabPage2);
			this->tabControl->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tabControl->ForeColor = System::Drawing::SystemColors::Window;
			this->tabControl->Location = System::Drawing::Point(0, 24);
			this->tabControl->Margin = System::Windows::Forms::Padding(5, 0, 5, 5);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(724, 390);
			this->tabControl->SizeMode = System::Windows::Forms::TabSizeMode::FillToRight;
			this->tabControl->TabIndex = 2;
			this->tabPage1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->tabPage1->Controls->Add(this->toolPanel);
			this->tabPage1->Controls->Add(this->editorPanel);
			this->tabPage1->ForeColor = System::Drawing::SystemColors::Window;
			this->tabPage1->Location = System::Drawing::Point(4, 24);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(716, 362);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Редактор";
			this->toolPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->toolPanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->toolPanel->Controls->Add(this->groupBox3);
			this->toolPanel->Controls->Add(this->groupBox2);
			this->toolPanel->Controls->Add(this->groupBox1);
			this->toolPanel->Controls->Add(this->toolboxTitle);
			this->toolPanel->Dock = System::Windows::Forms::DockStyle::Right;
			this->toolPanel->Location = System::Drawing::Point(529, 3);
			this->toolPanel->Name = L"toolPanel";
			this->toolPanel->Size = System::Drawing::Size(184, 356);
			this->toolPanel->TabIndex = 3;
			this->groupBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox3->Controls->Add(this->powTBr2);
			this->groupBox3->Controls->Add(this->powTBr1);
			this->groupBox3->Controls->Add(this->powTBx2);
			this->groupBox3->Controls->Add(this->powTBx1);
			this->groupBox3->Controls->Add(this->label3_2);
			this->groupBox3->Controls->Add(this->label3_1);
			this->groupBox3->ForeColor = System::Drawing::SystemColors::InactiveCaption;
			this->groupBox3->Location = System::Drawing::Point(-2, 145);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(184, 56);
			this->groupBox3->TabIndex = 3;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Степенное";
			this->powTBr2->AutoSize = false;
			this->powTBr2->Location = System::Drawing::Point(63, 33);
			this->powTBr2->Maximum = 255;
			this->powTBr2->Minimum = 1;
			this->powTBr2->Name = L"powTBr2";
			this->powTBr2->Size = System::Drawing::Size(109, 15);
			this->powTBr2->TabIndex = 9;
			this->powTBr2->TickStyle = System::Windows::Forms::TickStyle::None;
			this->powTBr2->Value = 1;
			this->powTBr1->AutoSize = false;
			this->powTBr1->Location = System::Drawing::Point(63, 17);
			this->powTBr1->Maximum = 255;
			this->powTBr1->Minimum = 1;
			this->powTBr1->Name = L"powTBr1";
			this->powTBr1->Size = System::Drawing::Size(109, 15);
			this->powTBr1->TabIndex = 8;
			this->powTBr1->TickStyle = System::Windows::Forms::TickStyle::None;
			this->powTBr1->Value = 1;
			this->powTBx2->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->powTBx2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->powTBx2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->powTBx2->ForeColor = System::Drawing::SystemColors::Window;
			this->powTBx2->Location = System::Drawing::Point(26, 33);
			this->powTBx2->Name = L"powTBx2";
			this->powTBx2->Size = System::Drawing::Size(31, 14);
			this->powTBx2->TabIndex = 6;
			this->powTBx2->Text = L"1";
			this->powTBx2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->powTBx1->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->powTBx1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->powTBx1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->powTBx1->ForeColor = System::Drawing::SystemColors::Window;
			this->powTBx1->Location = System::Drawing::Point(26, 17);
			this->powTBx1->Name = L"powTBx1";
			this->powTBx1->Size = System::Drawing::Size(31, 14);
			this->powTBx1->TabIndex = 5;
			this->powTBx1->Text = L"1";
			this->powTBx1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
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
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox2->Controls->Add(this->binTBr3);
			this->groupBox2->Controls->Add(this->binTBr2);
			this->groupBox2->Controls->Add(this->binTBr1);
			this->groupBox2->Controls->Add(this->binTBx3);
			this->groupBox2->Controls->Add(this->binTBx2);
			this->groupBox2->Controls->Add(this->binTBx1);
			this->groupBox2->Controls->Add(this->label2_3);
			this->groupBox2->Controls->Add(this->label2_2);
			this->groupBox2->Controls->Add(this->label2_1);
			this->groupBox2->ForeColor = System::Drawing::SystemColors::InactiveCaption;
			this->groupBox2->Location = System::Drawing::Point(-2, 74);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(184, 71);
			this->groupBox2->TabIndex = 2;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Бинаризация";
			this->binTBr3->AutoSize = false;
			this->binTBr3->Location = System::Drawing::Point(63, 49);
			this->binTBr3->Maximum = 50;
			this->binTBr3->Name = L"binTBr3";
			this->binTBr3->Size = System::Drawing::Size(109, 15);
			this->binTBr3->TabIndex = 10;
			this->binTBr3->TickStyle = System::Windows::Forms::TickStyle::None;
			this->binTBr3->Value = 25;
			this->binTBr2->AutoSize = false;
			this->binTBr2->Location = System::Drawing::Point(63, 33);
			this->binTBr2->Maximum = 50;
			this->binTBr2->Name = L"binTBr2";
			this->binTBr2->Size = System::Drawing::Size(109, 15);
			this->binTBr2->TabIndex = 9;
			this->binTBr2->TickStyle = System::Windows::Forms::TickStyle::None;
			this->binTBr2->Value = 25;
			this->binTBr1->AutoSize = false;
			this->binTBr1->Location = System::Drawing::Point(63, 17);
			this->binTBr1->Maximum = 50;
			this->binTBr1->Name = L"binTBr1";
			this->binTBr1->Size = System::Drawing::Size(109, 15);
			this->binTBr1->TabIndex = 8;
			this->binTBr1->TickStyle = System::Windows::Forms::TickStyle::None;
			this->binTBr1->Value = 25;
			this->binTBx3->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->binTBx3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->binTBx3->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->binTBx3->ForeColor = System::Drawing::SystemColors::Window;
			this->binTBx3->Location = System::Drawing::Point(26, 49);
			this->binTBx3->Name = L"binTBx3";
			this->binTBx3->Size = System::Drawing::Size(31, 14);
			this->binTBx3->TabIndex = 7;
			this->binTBx3->Text = L"1";
			this->binTBx3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->binTBx2->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->binTBx2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->binTBx2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->binTBx2->ForeColor = System::Drawing::SystemColors::Window;
			this->binTBx2->Location = System::Drawing::Point(26, 33);
			this->binTBx2->Name = L"binTBx2";
			this->binTBx2->Size = System::Drawing::Size(31, 14);
			this->binTBx2->TabIndex = 6;
			this->binTBx2->Text = L"1";
			this->binTBx2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->binTBx1->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->binTBx1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->binTBx1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->binTBx1->ForeColor = System::Drawing::SystemColors::Window;
			this->binTBx1->Location = System::Drawing::Point(26, 17);
			this->binTBx1->Name = L"binTBx1";
			this->binTBx1->Size = System::Drawing::Size(31, 14);
			this->binTBx1->TabIndex = 5;
			this->binTBx1->Text = L"1";
			this->binTBx1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->binTBx1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::textBox_KeyPress);
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
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->button2);
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Controls->Add(this->label1_2);
			this->groupBox1->Controls->Add(this->label1_1);
			this->groupBox1->ForeColor = System::Drawing::SystemColors::InactiveCaption;
			this->groupBox1->Location = System::Drawing::Point(-2, 18);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(184, 56);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Преобразования";
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->button2->Font = (gcnew System::Drawing::Font(L"Arial", 8.4, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->button2->Location = System::Drawing::Point(89, 33);
			this->button2->Margin = System::Windows::Forms::Padding(0, 3, 3, 3);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(89, 17);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Применить";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::halftoneClick);
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->button1->Font = (gcnew System::Drawing::Font(L"Arial", 8.4, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->button1->Location = System::Drawing::Point(89, 17);
			this->button1->Margin = System::Windows::Forms::Padding(0, 3, 3, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(89, 17);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Применить";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::negativeClick);
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
			this->tabPage2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->tabPage2->Controls->Add(this->logBox);
			this->tabPage2->ForeColor = System::Drawing::SystemColors::Window;
			this->tabPage2->Location = System::Drawing::Point(4, 24);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(716, 362);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Log";
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
			this->logBox->Size = System::Drawing::Size(670, 345);
			this->logBox->TabIndex = 0;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(43)),
				static_cast<System::Int32>(static_cast<System::Byte>(45)));
			this->ClientSize = System::Drawing::Size(724, 417);
			this->Controls->Add(this->tabControl);
			this->Controls->Add(this->menuStrip);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip;
			this->MinimumSize = System::Drawing::Size(192, 456);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Image Editor";
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->editorPanel->ResumeLayout(false);
			this->editorPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox))->EndInit();
			this->tabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->toolPanel->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->powTBr2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->powTBr1))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->binTBr3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->binTBr2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->binTBr1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: Void openClick(Object^, EventArgs^);
	private: Void exitMIClick(Object^  sender, EventArgs^  e);
	private: Void negativeClick(Object^, EventArgs^);
	private: Void halftoneClick(Object^, EventArgs^);
	private: Void binarClick(Object^, EventArgs^);
	private: Void chngBrightClick(Object^, EventArgs^);
	private: Void powerClick(Object^, EventArgs^);
	private: Bitmap^ negative(Bitmap^);
	private: Bitmap^ halftone(Bitmap^);
	private: Bitmap^ binar(Bitmap^, int, int, int);
	private: Bitmap^ power(Bitmap^, double, double);
	public:  Void dialogBinar(int, int, int);
	public:  Void dialogPower(double, double);
	public:  Void bkpPictureBox();
	private: Void toolPanelShowHide(Object^, EventArgs^);
	private: Void textBox_KeyPress(Object^, KeyPressEventArgs^);
	private: Void MainForm_SizeChanged(Object^, EventArgs^);
	};
}
