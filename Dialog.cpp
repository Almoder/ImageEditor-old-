#include "Dialog.h"

using namespace ImageEditor;

Dialog::Dialog(MainForm^ ptr, int type) {
	InitializeComponent();
	this->type = type;
	this->ptr = ptr;
	switch (type) {
	case 1:
		label4->Visible = false;
		label5->Visible = false;
		textBox4->Visible = false;
		textBox5->Visible = false;
		trackBar4->Visible = false;
		trackBar5->Visible = false;
		confirmButton->Location = System::Drawing::Point(15, 58);
		this->Size = System::Drawing::Size(this->Size.Width, confirmButton->Location.Y + 52);
		this->Text = L"Бинаризация";
		break;
	case 2:
		label1->Visible = false;
		label2->Visible = false;
		label3->Visible = false;
		textBox1->Visible = false;
		textBox2->Visible = false;
		textBox3->Visible = false;
		trackBar1->Visible = false;
		trackBar2->Visible = false;
		trackBar3->Visible = false;
		label4->Location = System::Drawing::Point(12, 9);
		label5->Location = System::Drawing::Point(12, 24);
		textBox4->Location = System::Drawing::Point(40, 9);
		textBox5->Location = System::Drawing::Point(40, 24);
		trackBar4->Location = System::Drawing::Point(90, 9);
		trackBar5->Location = System::Drawing::Point(90, 24);
		confirmButton->Location = System::Drawing::Point(15, 43);
		this->Size = System::Drawing::Size(this->Size.Width, confirmButton->Location.Y + 52);
		this->Text = L"Степенное преобразование";
		break;
	default:
		break;
	}
}

Dialog::~Dialog() {
	if (components)	{
		delete components;
	}
}

Void Dialog::textBoxKeyDown(Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	switch (safe_cast<TextBox^>(sender)->TabIndex) {
	case 5:
		switch (e->KeyCode) {
		case Keys::Up:
			textBox3->Focus();
			break;
		case Keys::Down:
			textBox2->Focus();
			break;
		case Keys::Enter:
			e->SuppressKeyPress = true;
			break;
		case Keys::Escape:
			Close();
		}
		break;
	case 6:
		switch (e->KeyCode) {
		case Keys::Up:
			textBox1->Focus();
			break;
		case Keys::Down:
			textBox3->Focus();
			break;
		case Keys::Enter:
			e->SuppressKeyPress = true;
			break;
		case Keys::Escape:
			Close();
		}
		break;
	case 7:
		switch (e->KeyCode) {
		case Keys::Up:
			textBox2->Focus();
			break;
		case Keys::Down:
			textBox1->Focus();
			break;
		case Keys::Enter:
			e->SuppressKeyPress = true;
			break;
		case Keys::Escape:
			Close();
		}
		break;
	case 8:
		switch (e->KeyCode) {
		case Keys::Up:
			textBox4->Focus();
			break;
		case Keys::Down:
			textBox4->Focus();
			break;
		case Keys::Enter:
			e->SuppressKeyPress = true;
			break;
		case Keys::Escape:
			Close();
		}
		break;
	case 9:
		switch (e->KeyCode) {
		case Keys::Up:
			textBox4->Focus();
			break;
		case Keys::Down:
			textBox4->Focus();
			break;
		case Keys::Enter:
			e->SuppressKeyPress = true;
			break;
		case Keys::Escape:
			Close();
		}
		break;
	default:
		break;
	}
}

Void Dialog::textBoxKeyPress(Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	switch (safe_cast<TextBox^>(sender)->TabIndex){
	case 5:	case 6:	case 7:
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar)) e->Handled = true;
		break;
	case 8:	case 9:
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) && (e->KeyChar != '.')) e->Handled = true;
		break;
	default:
		break;
	}
}

Void Dialog::textBoxTextChanged(Object^ sender, EventArgs^ e) {
	switch (safe_cast<TextBox^>(sender)->TabIndex) {
	case 5:
		if (textBox1->Text != String::Empty && Convert::ToInt32(textBox1->Text) <= 255) {
			trackBar1->Value = Convert::ToInt32(textBox1->Text);
		}
		else trackBar1->Value = 0;
		break;
	case 6:
		if (textBox2->Text != String::Empty && Convert::ToInt32(textBox2->Text) <= 255) {
			trackBar2->Value = Convert::ToInt32(textBox2->Text);
		}
		else trackBar2->Value = 0;
		break;
	case 7:
		if (textBox3->Text != String::Empty && Convert::ToInt32(textBox3->Text) <= 255) {
			trackBar3->Value = Convert::ToInt32(textBox3->Text);
		}
		else trackBar3->Value = 0;
		break;
	case 8:
		if (textBox4->Text != String::Empty) {
			try {
				if (Convert::ToDouble(textBox4->Text) * 100.0 >= 400.0) trackBar4->Value = 400;
				else trackBar4->Value = (int)(Convert::ToDouble(textBox4->Text) * 100.0);
			}
			catch (System::FormatException^ exc) {
				delete exc;
				return;
			}
		}
		else trackBar4->Value = 0;
		break;
	case 9:
		if (textBox5->Text != String::Empty) {
			try {
				if (Convert::ToDouble(textBox5->Text) * 100.0 >= 400.0) trackBar5->Value = 400;
				else trackBar5->Value = (int)(Convert::ToDouble(textBox5->Text) * 100.0);
			}
			catch (System::FormatException^ exc) {
				delete exc;
				return;
			}
		}
		else trackBar5->Value = 0;
		break;
	default:
		break;
	}
}

Void Dialog::trackBarValueChanged(Object^ sender, EventArgs^ e) {
	switch (safe_cast<TrackBar^>(sender)->TabIndex) {
	case 12:
		textBox1->Text = trackBar1->Value.ToString();
		break;
	case 13:
		textBox2->Text = trackBar2->Value.ToString();
		break;
	case 14:
		textBox3->Text = trackBar3->Value.ToString();
		break;
	case 15:
		textBox4->Text = Convert::ToString((double)trackBar4->Value / 100.0);
		break;
	case 16:
		textBox5->Text = Convert::ToString((double)trackBar5->Value / 100.0);
		break;
	default:
		break;
	}
}

Void Dialog::confirmButtonClick(Object^ sender, EventArgs^ e) {
	switch (type) {
	case 1:
		if (textBox1->Text == String::Empty || textBox2->Text == String::Empty || textBox2->Text == String::Empty) return;
		ptr->dialogBinar(trackBar1->Value, trackBar2->Value, trackBar3->Value);
		break;
	case 2:
		if (textBox4->Text == String::Empty || textBox5->Text == String::Empty) return;
		ptr->dialogPower((double)trackBar4->Value / 100.0, (double)trackBar5->Value / 100.0);
		break;
	default:
		break;
	}
	this->Close();
}