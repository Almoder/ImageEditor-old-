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
		Engine^ engine = nullptr;
		PictureBox^ curPictureBox = nullptr;
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
	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::SplitContainer^ splitContainer;
	private: System::Windows::Forms::StatusStrip^ statusStrip;
	private: System::Windows::Forms::ToolStripStatusLabel^ countLabel;
	private: System::Windows::Forms::ToolStripStatusLabel^ cur1Label;
	private: System::Windows::Forms::ToolStripStatusLabel^ cur2Label;
	private: System::Windows::Forms::ToolStripProgressBar^ toolStripProgressBar1;
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
			this->splitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->countLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->cur1Label = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->cur2Label = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripProgressBar1 = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->menuStrip->SuspendLayout();
			this->tabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer))->BeginInit();
			this->splitContainer->Panel1->SuspendLayout();
			this->splitContainer->Panel2->SuspendLayout();
			this->splitContainer->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
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
			this->undoItem->Click += gcnew System::EventHandler(this, &MainForm::undoItemClick);
			// 
			// redoItem
			// 
			this->redoItem->Name = L"redoItem";
			this->redoItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::X));
			this->redoItem->Size = System::Drawing::Size(183, 22);
			this->redoItem->Text = L"Redo";
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
			this->doubleItem->Name = L"doubleItem";
			this->doubleItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D));
			this->doubleItem->Size = System::Drawing::Size(194, 22);
			this->doubleItem->Text = L"Double picture";
			this->doubleItem->Click += gcnew System::EventHandler(this, &MainForm::doubleItemClick);
			this->doubleItem->CheckOnClick = true;
			// 
			// tabControl
			// 
			this->tabControl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl->Appearance = System::Windows::Forms::TabAppearance::FlatButtons;
			this->tabControl->Controls->Add(this->tabPage1);
			this->tabControl->Controls->Add(this->tabPage2);
			this->tabControl->Location = System::Drawing::Point(0, 24);
			this->tabControl->Margin = System::Windows::Forms::Padding(3, 0, 3, 0);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(524, 258);
			this->tabControl->TabIndex = 1;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->tableLayout);
			this->tabPage1->Controls->Add(this->splitContainer);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(516, 229);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Editor";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tableLayout
			// 
			this->tableLayout->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayout->AutoScroll = true;
			this->tableLayout->ColumnCount = 1;
			this->tableLayout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayout->Location = System::Drawing::Point(363, 3);
			this->tableLayout->Name = L"tableLayout";
			this->tableLayout->RowCount = 12;
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
			this->tableLayout->Size = System::Drawing::Size(150, 223);
			this->tableLayout->TabIndex = 1;
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
			this->splitContainer->Size = System::Drawing::Size(357, 223);
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
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(499, 229);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Log";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// statusStrip
			// 
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->countLabel, this->cur1Label,
					this->cur2Label, this->toolStripProgressBar1
			});
			this->statusStrip->Location = System::Drawing::Point(0, 283);
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
			// toolStripProgressBar1
			// 
			this->toolStripProgressBar1->Name = L"toolStripProgressBar1";
			this->toolStripProgressBar1->Size = System::Drawing::Size(300, 16);
			this->toolStripProgressBar1->Visible = false;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ClientSize = System::Drawing::Size(524, 305);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->tabControl);
			this->Controls->Add(this->menuStrip);
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
			this->splitContainer->Panel1->ResumeLayout(false);
			this->splitContainer->Panel1->PerformLayout();
			this->splitContainer->Panel2->ResumeLayout(false);
			this->splitContainer->Panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer))->EndInit();
			this->splitContainer->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
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
	};
}
