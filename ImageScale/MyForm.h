#pragma once

namespace ImageScale {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		Bitmap^ image, ^ startImage;
	private: System::Windows::Forms::Label^ label_sigma;
	private: System::Windows::Forms::TrackBar^ trackBar_sigma;
	private: System::Windows::Forms::Button^ button_gaussian;
	private: System::Windows::Forms::Label^ label_kernel;
	private: System::Windows::Forms::TrackBar^ trackBar_kernelN;
	private: System::Windows::Forms::Label^ label_scale;
	private: System::Windows::Forms::Button^ button_bilinear;
	private: System::Windows::Forms::Button^ button_bicubic;


	private: System::Windows::Forms::TrackBar^ trackBar_scale;


	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Button^ button_openImage;
	protected:

	private: System::Windows::Forms::Button^ button_reset;
	private: System::Windows::Forms::Panel^ panel_image;

	private: System::Windows::Forms::Panel^ panel2;

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
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button_openImage = (gcnew System::Windows::Forms::Button());
			this->button_reset = (gcnew System::Windows::Forms::Button());
			this->panel_image = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->button_bicubic = (gcnew System::Windows::Forms::Button());
			this->button_bilinear = (gcnew System::Windows::Forms::Button());
			this->label_scale = (gcnew System::Windows::Forms::Label());
			this->trackBar_scale = (gcnew System::Windows::Forms::TrackBar());
			this->label_sigma = (gcnew System::Windows::Forms::Label());
			this->trackBar_sigma = (gcnew System::Windows::Forms::TrackBar());
			this->button_gaussian = (gcnew System::Windows::Forms::Button());
			this->label_kernel = (gcnew System::Windows::Forms::Label());
			this->trackBar_kernelN = (gcnew System::Windows::Forms::TrackBar());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_scale))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_sigma))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_kernelN))->BeginInit();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->button_openImage);
			this->panel1->Controls->Add(this->button_reset);
			this->panel1->Controls->Add(this->panel_image);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(301, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(901, 574);
			this->panel1->TabIndex = 27;
			// 
			// button_openImage
			// 
			this->button_openImage->Location = System::Drawing::Point(9, 2);
			this->button_openImage->Name = L"button_openImage";
			this->button_openImage->Size = System::Drawing::Size(75, 23);
			this->button_openImage->TabIndex = 16;
			this->button_openImage->Text = L"Open Image";
			this->button_openImage->UseVisualStyleBackColor = true;
			this->button_openImage->Click += gcnew System::EventHandler(this, &MyForm::button_openImage_Click);
			// 
			// button_reset
			// 
			this->button_reset->Location = System::Drawing::Point(104, 2);
			this->button_reset->Name = L"button_reset";
			this->button_reset->Size = System::Drawing::Size(75, 23);
			this->button_reset->TabIndex = 28;
			this->button_reset->Text = L"Reset Image";
			this->button_reset->UseVisualStyleBackColor = true;
			this->button_reset->Click += gcnew System::EventHandler(this, &MyForm::button_reset_Click);
			// 
			// panel_image
			// 
			this->panel_image->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel_image->Location = System::Drawing::Point(9, 31);
			this->panel_image->Name = L"panel_image";
			this->panel_image->Size = System::Drawing::Size(599, 531);
			this->panel_image->TabIndex = 17;
			this->panel_image->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel_image_Paint);
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->button_bicubic);
			this->panel2->Controls->Add(this->button_bilinear);
			this->panel2->Controls->Add(this->label_scale);
			this->panel2->Controls->Add(this->trackBar_scale);
			this->panel2->Controls->Add(this->label_sigma);
			this->panel2->Controls->Add(this->trackBar_sigma);
			this->panel2->Controls->Add(this->button_gaussian);
			this->panel2->Controls->Add(this->label_kernel);
			this->panel2->Controls->Add(this->trackBar_kernelN);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel2->Location = System::Drawing::Point(0, 0);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(301, 574);
			this->panel2->TabIndex = 28;
			// 
			// button_bicubic
			// 
			this->button_bicubic->Location = System::Drawing::Point(13, 120);
			this->button_bicubic->Name = L"button_bicubic";
			this->button_bicubic->Size = System::Drawing::Size(118, 23);
			this->button_bicubic->TabIndex = 52;
			this->button_bicubic->Text = L"Scale (Bicubic)";
			this->button_bicubic->UseVisualStyleBackColor = true;
			this->button_bicubic->Click += gcnew System::EventHandler(this, &MyForm::button_bicubic_Click);
			// 
			// button_bilinear
			// 
			this->button_bilinear->Location = System::Drawing::Point(13, 91);
			this->button_bilinear->Name = L"button_bilinear";
			this->button_bilinear->Size = System::Drawing::Size(118, 23);
			this->button_bilinear->TabIndex = 51;
			this->button_bilinear->Text = L"Scale (Bilinear)";
			this->button_bilinear->UseVisualStyleBackColor = true;
			this->button_bilinear->Click += gcnew System::EventHandler(this, &MyForm::button_bilinear_Click);
			// 
			// label_scale
			// 
			this->label_scale->AutoSize = true;
			this->label_scale->Location = System::Drawing::Point(10, 61);
			this->label_scale->Name = L"label_scale";
			this->label_scale->Size = System::Drawing::Size(15, 13);
			this->label_scale->TabIndex = 50;
			this->label_scale->Text = L"N";
			// 
			// trackBar_scale
			// 
			this->trackBar_scale->Location = System::Drawing::Point(4, 29);
			this->trackBar_scale->Maximum = 100;
			this->trackBar_scale->Minimum = 1;
			this->trackBar_scale->Name = L"trackBar_scale";
			this->trackBar_scale->Size = System::Drawing::Size(293, 45);
			this->trackBar_scale->SmallChange = 2;
			this->trackBar_scale->TabIndex = 49;
			this->trackBar_scale->TickFrequency = 2;
			this->trackBar_scale->Value = 10;
			this->trackBar_scale->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar_scale_Scroll);
			// 
			// label_sigma
			// 
			this->label_sigma->AutoSize = true;
			this->label_sigma->Location = System::Drawing::Point(10, 291);
			this->label_sigma->Name = L"label_sigma";
			this->label_sigma->Size = System::Drawing::Size(36, 13);
			this->label_sigma->TabIndex = 48;
			this->label_sigma->Text = L"Sigma";
			// 
			// trackBar_sigma
			// 
			this->trackBar_sigma->Location = System::Drawing::Point(4, 259);
			this->trackBar_sigma->Maximum = 500;
			this->trackBar_sigma->Minimum = 1;
			this->trackBar_sigma->Name = L"trackBar_sigma";
			this->trackBar_sigma->Size = System::Drawing::Size(293, 45);
			this->trackBar_sigma->SmallChange = 2;
			this->trackBar_sigma->TabIndex = 47;
			this->trackBar_sigma->Value = 100;
			this->trackBar_sigma->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar_sigma_Scroll);
			// 
			// button_gaussian
			// 
			this->button_gaussian->Location = System::Drawing::Point(13, 310);
			this->button_gaussian->Name = L"button_gaussian";
			this->button_gaussian->Size = System::Drawing::Size(75, 23);
			this->button_gaussian->TabIndex = 46;
			this->button_gaussian->Text = L"Gaussian";
			this->button_gaussian->UseVisualStyleBackColor = true;
			this->button_gaussian->Click += gcnew System::EventHandler(this, &MyForm::button_gaussian_Click);
			// 
			// label_kernel
			// 
			this->label_kernel->AutoSize = true;
			this->label_kernel->Location = System::Drawing::Point(10, 240);
			this->label_kernel->Name = L"label_kernel";
			this->label_kernel->Size = System::Drawing::Size(15, 13);
			this->label_kernel->TabIndex = 45;
			this->label_kernel->Text = L"N";
			// 
			// trackBar_kernelN
			// 
			this->trackBar_kernelN->Location = System::Drawing::Point(4, 208);
			this->trackBar_kernelN->Maximum = 9;
			this->trackBar_kernelN->Minimum = 1;
			this->trackBar_kernelN->Name = L"trackBar_kernelN";
			this->trackBar_kernelN->Size = System::Drawing::Size(293, 45);
			this->trackBar_kernelN->SmallChange = 2;
			this->trackBar_kernelN->TabIndex = 44;
			this->trackBar_kernelN->TickFrequency = 2;
			this->trackBar_kernelN->Value = 1;
			this->trackBar_kernelN->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar_kernelN_Scroll);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1202, 574);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->panel2);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->panel1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_scale))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_sigma))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_kernelN))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button_openImage_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_reset_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void panel_image_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
	private: System::Void trackBar_kernelN_Scroll(System::Object^ sender, System::EventArgs^ e);
	private: System::Void trackBar_sigma_Scroll(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_gaussian_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void trackBar_scale_Scroll(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_bilinear_Click(System::Object^ sender, System::EventArgs^ e);	
	private: System::Void button_bicubic_Click(System::Object^ sender, System::EventArgs^ e);

	private: Color BicubicInterpolation(float x, float y, Bitmap^ bitmap);
	private: float CubicInterpolate(float p0, float p1, float p2, float p3, float t);
};
}
