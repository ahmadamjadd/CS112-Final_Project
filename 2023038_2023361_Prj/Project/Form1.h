#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include<algorithm>
#include <cstdlib>
#include <ctime>
#include <vcclr.h> 
namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:

	public:
		Bitmap^ bmp;
		double** dataSet, ** result, **permutated_matrix, **result_permutated, *signature_values, **sorted_matrix, **sorted_coefficient_matrix;
		int** result_dis, **result_permutated_dis, ** sorted_discrete_matrix;
		int num_of_cols, num_of_rows;
		bool is_file_read, is_sig_calculated, is_permutated, is_permutated_sorted_discritized, is_permutated_shuffled_discritized, is_permutated_discrtized, is_discrtized;
	private: System::Windows::Forms::PictureBox^ pictureBox1;









	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::ToolStripMenuItem^ discretizeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ bitmapBlackToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ bitMToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ permutedToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ bitMapBlackToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ bitMapGreenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ sortedToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ bITMAPBlackToolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^ bITMAPGreenToolStripMenuItem1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;


	public:
		Color newColor;

		void Bitmap_Image_Generator(int** array, int width, int height, PictureBox^ picturebox)
		{
			bmp = gcnew Bitmap(width, height);

			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					if (array[i][j] == 0 || array[i][j] == -842150451)
					{
						bmp->SetPixel(i, j, Color::Black);

					}
					else {
						bmp->SetPixel(i, j, Color::White);
					}
				}
			}
			picturebox->Invalidate();
			picturebox->Image = bmp;
			picturebox->Refresh();

		}

		void max_value(double** array, int width, int height)
		{

			for (int j = 0; j < height; ++j) {
				// Find the maximum value in the column
				double maxVal = array[0][j];
				for (int i = 1; i < width; ++i)
				{
					maxVal = max(array[i][j], maxVal);
				}


				// Scale values in the column
				double max = 255.000;
				if (maxVal != 0) { // Avoid division by zero
					for (int i = 0; i < width; ++i)
					{
						double value = array[i][j];
						value = (value / maxVal) * 255;
						if (value < 0)
							value *= -1;
						array[i][j] = value;

					}
				}
				else { // If maximum value is 0, set all values in the column to 0
					for (int i = 0; i < width; ++i) {
						array[i][j] = 0;
					}
				}
			}

		}


		void green_shade(int** array, double** array2, int width, int height, PictureBox^ picturebox)
		{

			bmp = gcnew Bitmap(width, height);
			
			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					Color colorpixel = bmp->GetPixel(i, j);
					newColor = Color::FromArgb(colorpixel.R, array2[i][j], colorpixel.B);
					if (array[i][j] == 0)
					{
						bmp->SetPixel(i, j, Color::FromArgb(newColor.R, newColor.G, newColor.B));

					}
					else {
						bmp->SetPixel(i, j, Color::FromArgb(newColor.R, newColor.G, newColor.B));
					}
				}
			}

			picturebox->Invalidate();
			picturebox->Image = bmp;
			picturebox->Refresh();

		}
		void zoom_in(PictureBox^ picturebox) {
			picturebox->Width = picturebox->Width * 1.5;
			picturebox->Height = picturebox->Height * 1.5;
		}
		void zoom_out(PictureBox^ picturebox) {
			picturebox->Width = picturebox->Width / 1.5;
			picturebox->Height = picturebox->Height / 1.5;
		}

		double calculateMean(double arr[], int size)
		{
			double sum = 0.0;
			for (int i = 0; i < size; i++)
			{
				sum += arr[i];
			}
			return sum / size;
		}
		double calculatePearsonCoefficient(double arr1[], double arr2[], int size)
		{

			double mean1 = calculateMean(arr1, size);
			double mean2 = calculateMean(arr2, size);

			double covariance = 0.0;
			double var1 = 0.0, var2 = 0.0;

			for (int i = 0; i < size; i++)
			{
				covariance += (arr1[i] - mean1) * (arr2[i] - mean2);
				var1 += pow(arr1[i] - mean1, 2);
				var2 += pow(arr2[i] - mean2, 2);
			}

			covariance /= size;
			var1 /= size;
			var2 /= size;

			double correlation = covariance / (sqrt(var1) * sqrt(var2));


			return correlation;

		}

		void DiscretizeMatrix(double** result, int** result_dis, int rows, int cols)
		{

			double* temp = new double[rows];
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < rows; j++)
				{
					temp[j] = result[j][i];
				}

				double mean = calculateMean(temp, rows);
				for (int j = 0; j < rows; j++)
				{
					if (result[j][i] > mean)
					{
						result_dis[j][i] = 1;
					}
					else
					{
						result_dis[j][i] = 0;
					}

				}
			}



			delete[] temp;
		}

		void Find_Signature_Values(double** array1, double* array2, int num_of_rows, int num_of_cols)
		{
			for (int i = 0; i < num_of_rows; ++i)
			{
				int sum = 0;
				double mean = 0.0;
				double product = 0.0;

				// Calculate sum of elements in the row
				for (int j = 0; j < num_of_cols; ++j)
				{
					sum += array1[i][j];
				}

				// Calculate mean of elements in the row
				mean = static_cast<double>(sum) / 4.00;

				// Multiply sum with mean
				product = sum * mean;
				array2[i] = product;
			}
			is_sig_calculated = true;
		}

		void CalPearsonCoefficeint(double** dataSet, double** result, int num_of_row, int num_of_cols)
		{
			double* array1 = new double[num_of_cols];
			double* array2 = new double[num_of_cols];
			for (int i = 0; i < num_of_rows; i++)
			{
				for (int j = 0; j < num_of_rows; j++)
				{
					for (int k = 0; k < num_of_cols; k++)
					{
						array1[k] = dataSet[i][k];
					}
					for (int k = 0; k < num_of_cols; k++)
					{
						array2[k] = dataSet[j][k];
					}
					result[i][j] = calculatePearsonCoefficient(array1, array2, num_of_cols);
				}
			}

			delete[] array1, array2;

		}

		void sort_permutated_matrix(double** permutated_matrix, double* sig_values, double** sorted_matrix, int rows, int cols)
		{
				int* indices = new int[rows];

				for (int i = 0; i < rows; i++)
				{
					indices[i] = i;
				}

				for (int i = 0; i < rows - 1; i++)
				{
					for (int j = 0; j < rows - i - 1; j++)
					{
						if (sig_values[indices[j]] > sig_values[indices[j + 1]])
						{
							int temp = indices[j];
							indices[j] = indices[j + 1];
							indices[j + 1] = temp;
						}
					}
				}

				for (int i = 0; i < rows; i++)
				{
					int row_index = indices[i];
					for (int j = 0; j < cols; j++)
					{
						sorted_matrix[i][j] = permutated_matrix[row_index][j];
					}
				}
				delete[] indices;
		}

		void shuffle_matrix(double** dataSet, double** permutated_matrix, int rows, int cols)
		{
			srand(time(0));
			double* temp_row = new double[num_of_cols];
			for (int i = 0; i < num_of_rows; i++)
			{
				int random_row_index = rand() % num_of_rows;
				for (int j = 0; j < num_of_cols; j++)
				{
					temp_row[j] = dataSet[i][j];
				}

				for (int j = 0; j < num_of_cols; j++)
				{
					permutated_matrix[i][j] = dataSet[random_row_index][j];
				}
				for (int j = 0; j < num_of_cols; j++)
				{
					permutated_matrix[random_row_index][j] = temp_row[j];
				}
			}
			is_permutated = true;


			delete[] temp_row;

		}

		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->discretizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bitmapBlackToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bitMToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->permutedToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bitMapBlackToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bitMapGreenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->sortedToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bITMAPBlackToolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bITMAPGreenToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(21, 92);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(330, 353);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->fileToolStripMenuItem,
					this->discretizeToolStripMenuItem, this->permutedToolStripMenuItem, this->sortedToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1546, 28);
			this->menuStrip1->TabIndex = 12;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->openToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(46, 24);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(128, 26);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openToolStripMenuItem_Click);
			// 
			// discretizeToolStripMenuItem
			// 
			this->discretizeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->bitmapBlackToolStripMenuItem,
					this->bitMToolStripMenuItem
			});
			this->discretizeToolStripMenuItem->Name = L"discretizeToolStripMenuItem";
			this->discretizeToolStripMenuItem->Size = System::Drawing::Size(88, 24);
			this->discretizeToolStripMenuItem->Text = L"Discretize";
			// 
			// bitmapBlackToolStripMenuItem
			// 
			this->bitmapBlackToolStripMenuItem->Name = L"bitmapBlackToolStripMenuItem";
			this->bitmapBlackToolStripMenuItem->Size = System::Drawing::Size(194, 26);
			this->bitmapBlackToolStripMenuItem->Text = L"Bitmap Normal";
			this->bitmapBlackToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::bitmapBlackToolStripMenuItem_Click);
			// 
			// bitMToolStripMenuItem
			// 
			this->bitMToolStripMenuItem->Name = L"bitMToolStripMenuItem";
			this->bitMToolStripMenuItem->Size = System::Drawing::Size(194, 26);
			this->bitMToolStripMenuItem->Text = L"Bitmap Green";
			this->bitMToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::bitMToolStripMenuItem_Click);
			// 
			// permutedToolStripMenuItem
			// 
			this->permutedToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->bitMapBlackToolStripMenuItem1,
					this->bitMapGreenToolStripMenuItem
			});
			this->permutedToolStripMenuItem->Name = L"permutedToolStripMenuItem";
			this->permutedToolStripMenuItem->Size = System::Drawing::Size(86, 24);
			this->permutedToolStripMenuItem->Text = L"Permuted";
			// 
			// bitMapBlackToolStripMenuItem1
			// 
			this->bitMapBlackToolStripMenuItem1->Name = L"bitMapBlackToolStripMenuItem1";
			this->bitMapBlackToolStripMenuItem1->Size = System::Drawing::Size(183, 26);
			this->bitMapBlackToolStripMenuItem1->Text = L"Bitmap Black";
			this->bitMapBlackToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::bitMapBlackToolStripMenuItem1_Click);
			// 
			// bitMapGreenToolStripMenuItem
			// 
			this->bitMapGreenToolStripMenuItem->Name = L"bitMapGreenToolStripMenuItem";
			this->bitMapGreenToolStripMenuItem->Size = System::Drawing::Size(183, 26);
			this->bitMapGreenToolStripMenuItem->Text = L"Bitmap Green";
			this->bitMapGreenToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::bitMapGreenToolStripMenuItem_Click);
			// 
			// sortedToolStripMenuItem
			// 
			this->sortedToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->bITMAPBlackToolStripMenuItem2,
					this->bITMAPGreenToolStripMenuItem1
			});
			this->sortedToolStripMenuItem->Name = L"sortedToolStripMenuItem";
			this->sortedToolStripMenuItem->Size = System::Drawing::Size(67, 24);
			this->sortedToolStripMenuItem->Text = L"Sorted";
			// 
			// bITMAPBlackToolStripMenuItem2
			// 
			this->bITMAPBlackToolStripMenuItem2->Name = L"bITMAPBlackToolStripMenuItem2";
			this->bITMAPBlackToolStripMenuItem2->Size = System::Drawing::Size(182, 26);
			this->bITMAPBlackToolStripMenuItem2->Text = L"Bitmap black";
			this->bITMAPBlackToolStripMenuItem2->Click += gcnew System::EventHandler(this, &Form1::bITMAPBlackToolStripMenuItem2_Click);
			// 
			// bITMAPGreenToolStripMenuItem1
			// 
			this->bITMAPGreenToolStripMenuItem1->Name = L"bITMAPGreenToolStripMenuItem1";
			this->bITMAPGreenToolStripMenuItem1->Size = System::Drawing::Size(182, 26);
			this->bITMAPGreenToolStripMenuItem1->Text = L"Bitmap green";
			this->bITMAPGreenToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::bITMAPGreenToolStripMenuItem1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(21, 63);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(85, 24);
			this->button1->TabIndex = 13;
			this->button1->Text = L"Zoom In";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(112, 63);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(94, 23);
			this->button2->TabIndex = 14;
			this->button2->Text = L"Zoom Out";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click_1);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1546, 470);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Clustering - Unsupervised Learning";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
	}



private: System::Void openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	openFileDialog1->ShowDialog();
	String^ Path = openFileDialog1->FileName;
	pin_ptr<const wchar_t> wch = PtrToStringChars(Path);
	int len = Path->Length;
	wchar_t* wchPtr = const_cast<wchar_t*>(wch);
	wstring convertedString(wchPtr, len);
	string nativepath(convertedString.begin(), convertedString.end());
	ifstream reader;
	reader.open(nativepath);
	if (!reader.is_open())
	{
		MessageBox::Show("Error opening file!\n");
		return;
	}
	int val1, val2;
	//double value;
	reader >> val1 >> val2;
	num_of_rows = val1;
	num_of_cols = val2;

	dataSet = new double* [num_of_rows];
	result_dis = new int* [num_of_rows];
	result = new double* [num_of_rows];
	for (int i = 0; i < num_of_rows; i++)
	{
		dataSet[i] = new double[num_of_cols];
		result_dis[i] = new int[num_of_rows];
		result[i] = new double[num_of_rows];
	}

	string line;
	string value;
	int row = 0, col;
	while (getline(reader, line))
	{
		istringstream ss(line);
		col = 0;
		if (line.empty())
			continue;
		while (ss >> value)
		{
			dataSet[row][col] = stof(value);
			col++;
		}
		row++;
	}
	is_file_read = true;
	MessageBox::Show("Data read!", "Successfull", MessageBoxButtons::OK, MessageBoxIcon::Information);
	
}
private: System::Void bitmapBlackToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	if (is_file_read)
	{
		pictureBox1->Invalidate();
		CalPearsonCoefficeint(dataSet, result, num_of_rows, num_of_cols);
		DiscretizeMatrix(result, result_dis, num_of_rows, num_of_cols);
		MessageBox::Show("Matrix is Discretized\n", "Successfull", MessageBoxButtons::OK, MessageBoxIcon::Information);
		Bitmap_Image_Generator(result_dis, num_of_rows, num_of_rows, pictureBox1);
		is_discrtized = true;
	}
	else
	{
		MessageBox::Show("File NOT read yet!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

}
private: System::Void bitMToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	if (is_file_read)
	{
		if (is_discrtized)
		{
			max_value(result, num_of_rows, num_of_rows);
			green_shade(result_dis, result, num_of_rows, num_of_rows, pictureBox1);
			MessageBox::Show("Bitmap Color coded!", "Successfull", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else
		{
			MessageBox::Show("Data NOT discritized yet!", "Click Discritize -> Bitmap Black", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	else
	{
		MessageBox::Show("File NOT read yet!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

}
private: System::Void bitMapBlackToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {

	if (is_file_read)
	{
		permutated_matrix = new double* [num_of_rows];
		result_permutated_dis = new int* [num_of_rows];
		result_permutated = new double* [num_of_rows];
		for (int i = 0; i < num_of_rows; i++)
		{
			permutated_matrix[i] = new double[num_of_cols];
			result_permutated_dis[i] = new int[num_of_rows];
			result_permutated[i] = new double[num_of_rows];
		}

		shuffle_matrix(dataSet, permutated_matrix, num_of_rows, num_of_cols);
		MessageBox::Show("Matrix is permuted\n", "Successfull", MessageBoxButtons::OK, MessageBoxIcon::Information);
		CalPearsonCoefficeint(permutated_matrix, result_permutated, num_of_rows, num_of_cols);
		DiscretizeMatrix(result_permutated, result_permutated_dis, num_of_rows, num_of_cols);
		Bitmap_Image_Generator(result_permutated_dis, num_of_rows, num_of_rows, pictureBox1);
		is_permutated_shuffled_discritized = true;
	}
	else
	{
		MessageBox::Show("File NOT read yet!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

}
private: System::Void bitMapGreenToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	
	if (is_file_read)
	{
		if (is_permutated_shuffled_discritized)
		{
			max_value(result_permutated, num_of_rows, num_of_rows);
			green_shade(result_permutated_dis, result_permutated, num_of_rows, num_of_rows, pictureBox1);
			MessageBox::Show("Bitmap Color coded!", "Successfull", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else
		{
			MessageBox::Show("Data NOT permutated yet!", "Click Permuted -> Bitmap Black", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	else
	{
		MessageBox::Show("File NOT read yet!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

}
private: System::Void bITMAPBlackToolStripMenuItem2_Click(System::Object^ sender, System::EventArgs^ e) {
	if (is_file_read)
	{
		sorted_matrix = new double* [num_of_rows];
		sorted_coefficient_matrix = new double* [num_of_rows];
		sorted_discrete_matrix = new int* [num_of_rows];
		for (int i = 0; i < num_of_rows; i++)
		{
			sorted_matrix[i] = new double[num_of_cols];
			sorted_coefficient_matrix[i] = new double[num_of_rows];
			sorted_discrete_matrix[i] = new int[num_of_rows];
		}
		signature_values = new double[num_of_rows];
		if (is_permutated)
		{
			Find_Signature_Values(permutated_matrix, signature_values, num_of_rows, num_of_cols);
			sort_permutated_matrix(permutated_matrix, signature_values, sorted_matrix, num_of_rows, num_of_cols);
			MessageBox::Show("Matrix is Sorted\n", "Successfull", MessageBoxButtons::OK, MessageBoxIcon::Information);
			CalPearsonCoefficeint(sorted_matrix, sorted_coefficient_matrix, num_of_rows, num_of_cols);
			DiscretizeMatrix(sorted_coefficient_matrix, sorted_discrete_matrix, num_of_rows, num_of_cols);
			Bitmap_Image_Generator(sorted_discrete_matrix, num_of_rows, num_of_rows, pictureBox1);
			is_permutated_sorted_discritized = true;

		}
		else
		{
			MessageBox::Show("Data NOT shuffled Yet!", "Permute -> Bitmap Black", MessageBoxButtons::OK, MessageBoxIcon::Error);

		}
	}
	else
	{
		MessageBox::Show("File NOT read yet!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

}
private: System::Void bITMAPGreenToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {

	if (is_file_read)
	{
		
			if (is_permutated_sorted_discritized)
			{
				max_value(sorted_coefficient_matrix, num_of_rows, num_of_rows);
				green_shade(sorted_discrete_matrix, sorted_coefficient_matrix, num_of_rows, num_of_rows, pictureBox1);
				MessageBox::Show("Bitmap Color coded!", "Successfull", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else
			{
				MessageBox::Show("Data NOT sorted Yet!", "Click Sort -> Bitmap Black", MessageBoxButtons::OK, MessageBoxIcon::Error);

			}
	
	}
	else
	{
		MessageBox::Show("File NOT read yet!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}


}

private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	
	pictureBox1->Width = pictureBox1->Width * 1.5;
	pictureBox1->Height = pictureBox1->Height * 1.5;
}
private: System::Void button2_Click_1(System::Object^ sender, System::EventArgs^ e) {
	
	float width = 330;
	float height = 353;
	float cal_width = pictureBox1->Width / 1.5;
	float cal_height = pictureBox1->Height / 1.5;
	if (cal_width < width && cal_height < height)
	{
		pictureBox1->Width = width / 1.5;
		pictureBox1->Height = height / 1.5;
	}
	else
	{
		pictureBox1->Width = pictureBox1->Width / 1.5;
		pictureBox1->Height = pictureBox1->Height / 1.5;
	}
}
};
}
