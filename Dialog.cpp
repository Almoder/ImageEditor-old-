#include "Dialog.h"

using namespace Lab1;

Dialog::Dialog(MainForm^ ptr, int type) 	{
	InitializeComponent(type);
	t = 0; b0 = 0; b1 = 0;
	c = 1.0; g = 1.0;
	this->ptr = ptr;
	this->type = type;
}

Dialog::~Dialog() {
	ptr->backUpFromPictureBox();
	if (components) {
		delete components;
	}
}

Void Dialog::textBox1_KeyDown(Object^  sender, KeyEventArgs^  e) {
	if (textBox1->Text != String::Empty) {
		if (type == 1) {
			trackBar1->Value = Convert::ToInt32(textBox1->Text);
			t = Convert::ToInt32(textBox1->Text);
		}
		if (type == 2) {
			if (Convert::ToDouble(textBox1->Text) * 25.0 >= 100.0) trackBar1->Value = 50;
			else trackBar1->Value = (int)(Convert::ToDouble(textBox1->Text) * 25);
			c = Convert::ToDouble(textBox1->Text);
		}
	}
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
}

Void Dialog::textBox2_KeyDown(Object^  sender, KeyEventArgs^  e) {
	if (textBox2->Text != String::Empty) {
		if (type == 1) {
			trackBar2->Value = Convert::ToInt32(textBox2->Text);
			b0 = Convert::ToInt32(textBox2->Text);
		}
		if (type == 2) {
			if (Convert::ToDouble(textBox2->Text) * 25.0 >= 100.0) trackBar2->Value = 50;
			else trackBar2->Value = (int)(Convert::ToDouble(textBox1->Text) * 25);
			g = Convert::ToDouble(textBox2->Text);
		}
	}
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

}

Void Dialog::textBox3_KeyDown(Object^  sender, KeyEventArgs^  e) {
	if (textBox3->Text != String::Empty) {
		trackBar3->Value = Convert::ToInt32(textBox3->Text);
		b1 = Convert::ToInt32(textBox3->Text);
	}
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
}

Void Dialog::textBox_KeyPressInt(Object^  sender, KeyPressEventArgs^  e) {
	if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar)) {
		e->Handled = true;
	}
}

Void Dialog::textBox_KeyPressDouble(Object^  sender, KeyPressEventArgs^  e) {
	if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) && (e->KeyChar != '.')) {
		e->Handled = true;
	}
}

Void Dialog::trackBar1_ValueChanged(Object^  sender, EventArgs^  e) {
	switch (type) {
	case 1:
		textBox1->Text = trackBar1->Value.ToString();
		t = trackBar1->Value;
		break;
	case 2:
		textBox1->Text = Convert::ToString((double)trackBar1->Value / 25.0);
		c = (double)trackBar1->Value / 25.0;
		break;
	}
}

Void Dialog::trackBar2_ValueChanged(Object^  sender, EventArgs^  e) {
	switch (type) {
	case 1:
		textBox2->Text = trackBar2->Value.ToString();
		b0 = trackBar2->Value;
		break;
	case 2:
		textBox2->Text = Convert::ToString((double)trackBar2->Value / 25.0);
		g = (double)trackBar2->Value / 25.0;
		break;
	}
}

Void Dialog::trackBar3_ValueChanged(Object^  sender, EventArgs^  e) {
	textBox3->Text = trackBar3->Value.ToString();
	b1 = trackBar3->Value;
}

Void Dialog::OnFormClosing(Object^, FormClosingEventArgs^) {
	ptr->backUpFromPictureBox();
}