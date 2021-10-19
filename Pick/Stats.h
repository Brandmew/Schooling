#pragma once

namespace Pick {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Globals;
	/// <summary>
	/// Summary for Stats
	/// </summary>
	public ref class Stats : public System::Windows::Forms::Form
	{
	public:
		Stats(void)
		{
			pGlbs = &Glbs;
			InitializeComponent();

			this->SuspendLayout();
			this->trackBar1->Maximum = MAXBIRDS;
			this->trackBar1->Value = pGlbs->BirdsCount;
			this->VelocityMaxBar->Maximum = (int) MAXBIRDVEL ;
			this->VelocityMaxBar->Minimum = MINBIRDVEL;
			this->VelocityMaxBar->Value = (int) pGlbs->BirdTopVel;
			this->VelocityMinTrackBar->Maximum = (int) MAXBIRDVEL;
			this->VelocityMinTrackBar->Minimum = MINBIRDVEL;
			this->VelocityMinTrackBar->Value = (int) pGlbs->BirdBottomVel;
			this->AttractDistBar->Value = (int) pGlbs->AttractDist;
			this->AttractDistBar->Maximum = (int)pGlbs->AttractDistMax;
			this->AttractDistBar->Minimum = (int)1;
			this->CollisionBar->Value = (int) pGlbs->CollDist;
			this->RoostInfBar->Value = (int) pGlbs->RoostInf;
			this->RoostSizeBar->Value = (int) MAXROOSTSIZE;
			this->RoostSizeBar->Value = (int) pGlbs->RoostSphere._radius;
			this->VisualAngBar->Value  = (int) ( pGlbs->VisualAngle * (360.0f / D3DX_PI) );
			this->AttractInfBar->Value = (int) pGlbs->AttractInf * 10;
			this->CollistionBar->Value = (int) pGlbs->CollInf * 10;
			this->HeadOnBar->Value = (int)  ( pGlbs->HeadOnEvation * (360.0f / D3DX_PI) );
			this->checkBox_eviro->Checked = pGlbs->EnvTog.bval;
			this->checkBox1->Checked = pGlbs->FPSTog.bval;
			this->checkEnvVar->Checked = pGlbs->EnvNumTog.bval;
			this->checkBoxBeABird->Checked = pGlbs->BeABirdTog.bval;
			this->checkBoxCircleCam->Checked = pGlbs->CameraCircleTog.bval;
			this->checkShowShip->Checked = pGlbs->ShowShip.bval;
			this->ResumeLayout(true);
			pGlbs->DlgOpen = true;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Stats()
		{
			if (components)
			{
				delete components;
			}
			pGlbs->DlgOpen = false;
		}
	private: System::Windows::Forms::Button^  OK;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TrackBar^  VelocityMaxBar;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TrackBar^  VelocityMinTrackBar;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TrackBar^  AttractDistBar;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TrackBar^  CollisionBar;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TrackBar^  RoostInfBar;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TrackBar^  RoostSizeBar;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TrackBar^  VisualAngBar;

	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TrackBar^  AttractInfBar;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TrackBar^  CollistionBar;

	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TrackBar^  HeadOnBar;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::CheckBox^  checkBox_eviro;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::CheckBox^  checkEnvVar;
	private: System::Windows::Forms::CheckBox^  checkBoxBeABird;
	private: System::Windows::Forms::CheckBox^  checkBoxCircleCam;
	private: System::Windows::Forms::Button^  TakeSnapButton;
	private: System::Windows::Forms::CheckBox^  checkShowShip;




	protected: 

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
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Stats::typeid));
			this->OK = (gcnew System::Windows::Forms::Button());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->VelocityMaxBar = (gcnew System::Windows::Forms::TrackBar());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->VelocityMinTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->AttractDistBar = (gcnew System::Windows::Forms::TrackBar());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->CollisionBar = (gcnew System::Windows::Forms::TrackBar());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->RoostInfBar = (gcnew System::Windows::Forms::TrackBar());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->RoostSizeBar = (gcnew System::Windows::Forms::TrackBar());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->VisualAngBar = (gcnew System::Windows::Forms::TrackBar());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->AttractInfBar = (gcnew System::Windows::Forms::TrackBar());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->CollistionBar = (gcnew System::Windows::Forms::TrackBar());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->HeadOnBar = (gcnew System::Windows::Forms::TrackBar());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->checkBox_eviro = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkEnvVar = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxBeABird = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxCircleCam = (gcnew System::Windows::Forms::CheckBox());
			this->TakeSnapButton = (gcnew System::Windows::Forms::Button());
			this->checkShowShip = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VelocityMaxBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VelocityMinTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->AttractDistBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CollisionBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RoostInfBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RoostSizeBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VisualAngBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->AttractInfBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CollistionBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HeadOnBar))->BeginInit();
			this->SuspendLayout();
			// 
			// OK
			// 
			this->OK->Location = System::Drawing::Point(337, 660);
			this->OK->Name = L"OK";
			this->OK->Size = System::Drawing::Size(75, 23);
			this->OK->TabIndex = 0;
			this->OK->Text = L"OK";
			this->OK->UseVisualStyleBackColor = true;
			this->OK->Click += gcnew System::EventHandler(this, &Stats::OK_Click);
			// 
			// trackBar1
			// 
			this->trackBar1->AutoSize = false;
			this->trackBar1->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->trackBar1->Location = System::Drawing::Point(12, 25);
			this->trackBar1->Maximum = 2000;
			this->trackBar1->MaximumSize = System::Drawing::Size(400, 40);
			this->trackBar1->Minimum = 2;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(400, 31);
			this->trackBar1->SmallChange = 30;
			this->trackBar1->TabIndex = 1;
			this->trackBar1->TickFrequency = 50;
			this->trackBar1->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->trackBar1->Value = 50;
			this->trackBar1->ValueChanged += gcnew System::EventHandler(this, &Stats::trackBar1_ValueChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(57, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"How many";
			// 
			// VelocityMaxBar
			// 
			this->VelocityMaxBar->AutoSize = false;
			this->VelocityMaxBar->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->VelocityMaxBar->Location = System::Drawing::Point(12, 81);
			this->VelocityMaxBar->Maximum = 300;
			this->VelocityMaxBar->MaximumSize = System::Drawing::Size(400, 40);
			this->VelocityMaxBar->Minimum = 2;
			this->VelocityMaxBar->Name = L"VelocityMaxBar";
			this->VelocityMaxBar->Size = System::Drawing::Size(400, 31);
			this->VelocityMaxBar->SmallChange = 30;
			this->VelocityMaxBar->TabIndex = 3;
			this->VelocityMaxBar->TickFrequency = 5;
			this->VelocityMaxBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->VelocityMaxBar->Value = 50;
			this->VelocityMaxBar->ValueChanged += gcnew System::EventHandler(this, &Stats::VelocityMaxBar_ValueChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(9, 65);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(97, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Maximum Velocity";
			// 
			// VelocityMinTrackBar
			// 
			this->VelocityMinTrackBar->AutoSize = false;
			this->VelocityMinTrackBar->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->VelocityMinTrackBar->Location = System::Drawing::Point(12, 137);
			this->VelocityMinTrackBar->Maximum = 300;
			this->VelocityMinTrackBar->MaximumSize = System::Drawing::Size(400, 40);
			this->VelocityMinTrackBar->Minimum = 2;
			this->VelocityMinTrackBar->Name = L"VelocityMinTrackBar";
			this->VelocityMinTrackBar->Size = System::Drawing::Size(400, 31);
			this->VelocityMinTrackBar->SmallChange = 30;
			this->VelocityMinTrackBar->TabIndex = 5;
			this->VelocityMinTrackBar->TickFrequency = 5;
			this->VelocityMinTrackBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->VelocityMinTrackBar->Value = 50;
			this->VelocityMinTrackBar->ValueChanged += gcnew System::EventHandler(this, &Stats::VelocityMinTrackBar_ValueChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 121);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(88, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Minimum Velocity";
			// 
			// AttractDistBar
			// 
			this->AttractDistBar->AutoSize = false;
			this->AttractDistBar->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->AttractDistBar->Location = System::Drawing::Point(12, 193);
			this->AttractDistBar->Maximum = 1000;
			this->AttractDistBar->MaximumSize = System::Drawing::Size(400, 40);
			this->AttractDistBar->Minimum = 2;
			this->AttractDistBar->Name = L"AttractDistBar";
			this->AttractDistBar->Size = System::Drawing::Size(400, 31);
			this->AttractDistBar->SmallChange = 30;
			this->AttractDistBar->TabIndex = 7;
			this->AttractDistBar->TickFrequency = 5;
			this->AttractDistBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->AttractDistBar->Value = 50;
			this->AttractDistBar->ValueChanged += gcnew System::EventHandler(this, &Stats::AttractDistBar_ValueChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(9, 177);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(97, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Attraction Distance";
			// 
			// CollisionBar
			// 
			this->CollisionBar->AutoSize = false;
			this->CollisionBar->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->CollisionBar->Location = System::Drawing::Point(12, 249);
			this->CollisionBar->Maximum = 300;
			this->CollisionBar->MaximumSize = System::Drawing::Size(400, 40);
			this->CollisionBar->Minimum = 2;
			this->CollisionBar->Name = L"CollisionBar";
			this->CollisionBar->Size = System::Drawing::Size(400, 31);
			this->CollisionBar->SmallChange = 30;
			this->CollisionBar->TabIndex = 9;
			this->CollisionBar->TickFrequency = 5;
			this->CollisionBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->CollisionBar->Value = 50;
			this->CollisionBar->ValueChanged += gcnew System::EventHandler(this, &Stats::CollisionBar_ValueChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(9, 233);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(88, 13);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Evasion Distance";
			// 
			// RoostInfBar
			// 
			this->RoostInfBar->AutoSize = false;
			this->RoostInfBar->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->RoostInfBar->Location = System::Drawing::Point(12, 305);
			this->RoostInfBar->Maximum = 300;
			this->RoostInfBar->MaximumSize = System::Drawing::Size(400, 40);
			this->RoostInfBar->Minimum = 2;
			this->RoostInfBar->Name = L"RoostInfBar";
			this->RoostInfBar->Size = System::Drawing::Size(400, 31);
			this->RoostInfBar->SmallChange = 30;
			this->RoostInfBar->TabIndex = 11;
			this->RoostInfBar->TickFrequency = 5;
			this->RoostInfBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->RoostInfBar->Value = 50;
			this->RoostInfBar->ValueChanged += gcnew System::EventHandler(this, &Stats::RoostInfBar_ValueChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(9, 289);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(82, 13);
			this->label6->TabIndex = 12;
			this->label6->Text = L"Roost Influence";
			// 
			// RoostSizeBar
			// 
			this->RoostSizeBar->AutoSize = false;
			this->RoostSizeBar->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->RoostSizeBar->Location = System::Drawing::Point(12, 360);
			this->RoostSizeBar->Maximum = 300;
			this->RoostSizeBar->MaximumSize = System::Drawing::Size(400, 40);
			this->RoostSizeBar->Minimum = 2;
			this->RoostSizeBar->Name = L"RoostSizeBar";
			this->RoostSizeBar->Size = System::Drawing::Size(400, 31);
			this->RoostSizeBar->SmallChange = 30;
			this->RoostSizeBar->TabIndex = 13;
			this->RoostSizeBar->TickFrequency = 5;
			this->RoostSizeBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->RoostSizeBar->Value = 50;
			this->RoostSizeBar->ValueChanged += gcnew System::EventHandler(this, &Stats::RoostSizeBar_ValueChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(9, 344);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(58, 13);
			this->label7->TabIndex = 14;
			this->label7->Text = L"Roost Size";
			// 
			// VisualAngBar
			// 
			this->VisualAngBar->AutoSize = false;
			this->VisualAngBar->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->VisualAngBar->Location = System::Drawing::Point(12, 415);
			this->VisualAngBar->Maximum = 360;
			this->VisualAngBar->MaximumSize = System::Drawing::Size(400, 40);
			this->VisualAngBar->Minimum = 1;
			this->VisualAngBar->Name = L"VisualAngBar";
			this->VisualAngBar->Size = System::Drawing::Size(400, 31);
			this->VisualAngBar->SmallChange = 30;
			this->VisualAngBar->TabIndex = 15;
			this->VisualAngBar->TickFrequency = 5;
			this->VisualAngBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->VisualAngBar->Value = 50;
			this->VisualAngBar->ValueChanged += gcnew System::EventHandler(this, &Stats::VisualAngBar_ValueChanged);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(9, 399);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(66, 13);
			this->label8->TabIndex = 16;
			this->label8->Text = L"Visual Angle";
			// 
			// AttractInfBar
			// 
			this->AttractInfBar->AutoSize = false;
			this->AttractInfBar->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->AttractInfBar->Location = System::Drawing::Point(12, 468);
			this->AttractInfBar->Maximum = 100;
			this->AttractInfBar->MaximumSize = System::Drawing::Size(400, 40);
			this->AttractInfBar->Name = L"AttractInfBar";
			this->AttractInfBar->Size = System::Drawing::Size(400, 31);
			this->AttractInfBar->SmallChange = 30;
			this->AttractInfBar->TabIndex = 17;
			this->AttractInfBar->TickFrequency = 5;
			this->AttractInfBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->AttractInfBar->Value = 50;
			this->AttractInfBar->ValueChanged += gcnew System::EventHandler(this, &Stats::AttractInfBar_ValueChanged);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(9, 452);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(95, 13);
			this->label9->TabIndex = 18;
			this->label9->Text = L"Attraction Strength";
			// 
			// CollistionBar
			// 
			this->CollistionBar->AutoSize = false;
			this->CollistionBar->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->CollistionBar->Location = System::Drawing::Point(12, 524);
			this->CollistionBar->Maximum = 100;
			this->CollistionBar->MaximumSize = System::Drawing::Size(400, 40);
			this->CollistionBar->Name = L"CollistionBar";
			this->CollistionBar->Size = System::Drawing::Size(400, 31);
			this->CollistionBar->SmallChange = 30;
			this->CollistionBar->TabIndex = 19;
			this->CollistionBar->TickFrequency = 5;
			this->CollistionBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->CollistionBar->Value = 50;
			this->CollistionBar->ValueChanged += gcnew System::EventHandler(this, &Stats::CollistionBar_ValueChanged);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(9, 508);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(127, 13);
			this->label10->TabIndex = 20;
			this->label10->Text = L"Collision Evasion Strength";
			// 
			// HeadOnBar
			// 
			this->HeadOnBar->AutoSize = false;
			this->HeadOnBar->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->HeadOnBar->Location = System::Drawing::Point(12, 577);
			this->HeadOnBar->Maximum = 360;
			this->HeadOnBar->MaximumSize = System::Drawing::Size(400, 40);
			this->HeadOnBar->Name = L"HeadOnBar";
			this->HeadOnBar->Size = System::Drawing::Size(400, 31);
			this->HeadOnBar->SmallChange = 30;
			this->HeadOnBar->TabIndex = 21;
			this->HeadOnBar->TickFrequency = 5;
			this->HeadOnBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->HeadOnBar->Value = 50;
			this->HeadOnBar->ValueChanged += gcnew System::EventHandler(this, &Stats::HeadOnBar_ValueChanged);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(9, 561);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(119, 13);
			this->label11->TabIndex = 22;
			this->label11->Text = L"Head On Evasion Angle";
			// 
			// checkBox_eviro
			// 
			this->checkBox_eviro->AutoSize = true;
			this->checkBox_eviro->Location = System::Drawing::Point(12, 615);
			this->checkBox_eviro->Name = L"checkBox_eviro";
			this->checkBox_eviro->Size = System::Drawing::Size(115, 17);
			this->checkBox_eviro->TabIndex = 23;
			this->checkBox_eviro->Text = L"Show Environment";
			this->checkBox_eviro->UseVisualStyleBackColor = true;
			this->checkBox_eviro->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Stats::checkBox_eviro_MouseClick);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(12, 638);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(130, 17);
			this->checkBox1->TabIndex = 24;
			this->checkBox1->Text = L"Show Technical Stats";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Stats::checkBox1_MouseClick);
			// 
			// checkEnvVar
			// 
			this->checkEnvVar->AutoSize = true;
			this->checkEnvVar->Location = System::Drawing::Point(12, 660);
			this->checkEnvVar->Name = L"checkEnvVar";
			this->checkEnvVar->Size = System::Drawing::Size(99, 17);
			this->checkEnvVar->TabIndex = 25;
			this->checkEnvVar->Text = L"Show Variables";
			this->checkEnvVar->UseVisualStyleBackColor = true;
			this->checkEnvVar->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Stats::checkEnvVar_MouseClick);
			// 
			// checkBoxBeABird
			// 
			this->checkBoxBeABird->AutoSize = true;
			this->checkBoxBeABird->Location = System::Drawing::Point(145, 615);
			this->checkBoxBeABird->Name = L"checkBoxBeABird";
			this->checkBoxBeABird->Size = System::Drawing::Size(72, 17);
			this->checkBoxBeABird->TabIndex = 26;
			this->checkBoxBeABird->Text = L"Pilot View";
			this->checkBoxBeABird->UseVisualStyleBackColor = true;
			this->checkBoxBeABird->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Stats::checkBoxBeABird_MouseClick);
			// 
			// checkBoxCircleCam
			// 
			this->checkBoxCircleCam->AutoSize = true;
			this->checkBoxCircleCam->Location = System::Drawing::Point(145, 638);
			this->checkBoxCircleCam->Name = L"checkBoxCircleCam";
			this->checkBoxCircleCam->Size = System::Drawing::Size(91, 17);
			this->checkBoxCircleCam->TabIndex = 27;
			this->checkBoxCircleCam->Text = L"Circle Camera";
			this->checkBoxCircleCam->UseVisualStyleBackColor = true;
			this->checkBoxCircleCam->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Stats::checkBoxCircleCam_MouseClick);
			// 
			// TakeSnapButton
			// 
			this->TakeSnapButton->Location = System::Drawing::Point(337, 615);
			this->TakeSnapButton->Name = L"TakeSnapButton";
			this->TakeSnapButton->Size = System::Drawing::Size(75, 23);
			this->TakeSnapButton->TabIndex = 28;
			this->TakeSnapButton->Text = L"Snapshot";
			this->TakeSnapButton->UseVisualStyleBackColor = true;
			this->TakeSnapButton->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Stats::TakeSnapButton_MouseClick);
			// 
			// checkShowShip
			// 
			this->checkShowShip->AutoSize = true;
			this->checkShowShip->Location = System::Drawing::Point(145, 660);
			this->checkShowShip->Name = L"checkShowShip";
			this->checkShowShip->Size = System::Drawing::Size(82, 17);
			this->checkShowShip->TabIndex = 29;
			this->checkShowShip->Text = L"Show Ships";
			this->checkShowShip->UseVisualStyleBackColor = true;
			this->checkShowShip->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Stats::checkShowShip_MouseClick);
			// 
			// Stats
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(426, 695);
			this->Controls->Add(this->checkShowShip);
			this->Controls->Add(this->TakeSnapButton);
			this->Controls->Add(this->checkBoxCircleCam);
			this->Controls->Add(this->checkBoxBeABird);
			this->Controls->Add(this->checkEnvVar);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->checkBox_eviro);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->HeadOnBar);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->CollistionBar);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->AttractInfBar);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->VisualAngBar);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->RoostSizeBar);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->RoostInfBar);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->CollisionBar);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->AttractDistBar);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->VelocityMinTrackBar);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->VelocityMaxBar);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->OK);
			this->DoubleBuffered = true;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Stats";
			this->Text = L"Variables";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Stats::Stats_FormClosed);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VelocityMaxBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VelocityMinTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->AttractDistBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CollisionBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RoostInfBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RoostSizeBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VisualAngBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->AttractInfBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CollistionBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HeadOnBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void OK_Click(System::Object^  sender, System::EventArgs^  e) {
				this->Close();
				pGlbs->DlgOpen = false;
				}
	private: System::Void trackBar1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				pGlbs->BirdsCount = this->trackBar1->Value;
				pGlbs->BirdsLLTail = Mob::InitaliseLinked(&Bird[0], pGlbs->BirdsCount);
  				}
private: System::Void VelocityMaxBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				pGlbs->BirdTopVel = (float) this->VelocityMaxBar->Value;
				if(pGlbs->BirdBottomVel > pGlbs->BirdTopVel) 
				{  
					pGlbs->BirdBottomVel = pGlbs->BirdTopVel;
					this->VelocityMinTrackBar->Value = (int) pGlbs->BirdBottomVel;
				}
			}

private: System::Void VelocityMinTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				pGlbs->BirdBottomVel = (float) this->VelocityMinTrackBar->Value;
				if(pGlbs->BirdBottomVel > pGlbs->BirdTopVel)
				{
					pGlbs->BirdTopVel = pGlbs->BirdBottomVel;
					this->VelocityMaxBar->Value = (int)pGlbs->BirdTopVel;
				}
			}
private: System::Void AttractDistBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				pGlbs->AttractDist = (float) this->AttractDistBar->Value;
				if(pGlbs->CollDist > pGlbs->AttractDist)
				{
					pGlbs->CollDist = pGlbs->AttractDist;
					this->CollisionBar->Value = (int) pGlbs->CollDist;
				}
			}
private: System::Void CollisionBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				pGlbs->CollDist = (float) this->CollisionBar->Value;
				if(pGlbs->CollDist > pGlbs->AttractDist)
				{
					pGlbs->AttractDist = pGlbs->CollDist;
					this->AttractDistBar->Value = (int) pGlbs->AttractDist;
				}
			}
private: System::Void RoostInfBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				pGlbs->RoostInf = (float) this->RoostInfBar->Value;
			}
private: System::Void RoostSizeBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				pGlbs->RoostSphere._radius = (float) this->RoostSizeBar->Value;
			}

private: System::Void VisualAngBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				pGlbs->VisualAngle = (float) ( (this->VisualAngBar->Value) / (360.0f / D3DX_PI) );
			}
private: System::Void AttractInfBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				pGlbs->AttractInf = (float) this->AttractInfBar->Value / 10;
			}
private: System::Void CollistionBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				pGlbs->CollInf = (float) this->CollistionBar->Value / 10;
			}
private: System::Void HeadOnBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				pGlbs->HeadOnEvation = (float) this->HeadOnBar->Value / (360.0f / D3DX_PI);
			}
private: System::Void checkBox_eviro_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				pGlbs->EnvTog.bval = this->checkBox_eviro->Checked;
			}
private: System::Void checkBox1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				pGlbs->FPSTog.bval = this->checkBox1->Checked;
			}
private: System::Void checkEnvVar_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				pGlbs->EnvNumTog.bval = this->checkEnvVar->Checked;
			}
private: System::Void checkBoxBeABird_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				pGlbs->BeABirdTog.bval = this->checkBoxBeABird->Checked;
			}
private: System::Void checkBoxCircleCam_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				pGlbs->CameraCircleTog.bval = this->checkBoxCircleCam->Checked;
			}
private: System::Void TakeSnapButton_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				pGlbs->Snapshot.bval = true;
			}
private: System::Void checkShowShip_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				pGlbs->ShowShip.bval = this->checkShowShip->Checked;
			}
private: System::Void Stats_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				pGlbs->DlgOpen = false;
			}
};
}
