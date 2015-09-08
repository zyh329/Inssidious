#include "UiTamperConditions.h"
#include <ctime>

UiTamperConditions::UiTamperConditions(QWidget *parent, TamperType tamperType)
	: UiTamperModule(parent, tamperType)
{
	pTamperConfig = (void*)new TamperConditionsConfig{0, 0, 0, 0};

	conditionsDescriptionLabel = new QLabel();
	conditionsDescriptionLabel->setText(conditionsDescriptionText);
	conditionsDescriptionLabel->setContentsMargins(0, 6, 0, 12);
	conditionsDescriptionLabel->setAlignment(Qt::AlignHCenter);
	conditionsDescriptionLabel->setFont(moduleDescriptionFont);
	conditionsDescriptionLabel->setPalette(moduleTextPaletteInactive);

	lossSpinBox = new QSpinBox();
	lossSpinBox->setRange(0, 100);
	lossSpinBox->setPrefix(lossText);
	lossSpinBox->setSuffix("%");
	lossSpinBox->setSingleStep(5);
	lossSpinBox->setFixedSize(66, 22);
	lossSpinBox->setStyleSheet(spinBoxStyleSheet);
	lossSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

	delaySpinBox = new QSpinBox();
	delaySpinBox->setRange(0, 100);
	delaySpinBox->setPrefix(delayText);
	delaySpinBox->setSuffix("%");
	delaySpinBox->setSingleStep(5);
	delaySpinBox->setFixedSize(66, 22);
	delaySpinBox->setStyleSheet(spinBoxStyleSheet);
	delaySpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

	junkSpinBox = new QSpinBox();
	junkSpinBox->setRange(0, 100);
	junkSpinBox->setPrefix(junkText);
	junkSpinBox->setSuffix("%");
	junkSpinBox->setSingleStep(5);
	junkSpinBox->setFixedSize(66, 22);
	junkSpinBox->setStyleSheet(spinBoxStyleSheet);
	junkSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

	tcpResetSpinBox = new QSpinBox();
	tcpResetSpinBox->setRange(0, 100);
	tcpResetSpinBox->setPrefix(tcpResetText);
	tcpResetSpinBox->setSuffix("%");
	tcpResetSpinBox->setSingleStep(1);
	tcpResetSpinBox->setFixedSize(66, 22);
	tcpResetSpinBox->setStyleSheet(spinBoxStyleSheet);
	tcpResetSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

	randomizeConditions = new QPushButton();
	randomizeConditions->setStyleSheet(buttonStyleSheet);
	randomizeConditions->setText("Randomize Conditions");
	randomizeConditions->setFont(moduleDescriptionFont);
	randomizeConditions->setFixedSize(130, 30);
	randomizeConditions->setContentsMargins(0, 0, 0, 0);

	//resetConditions = new QPushButton();
	//resetConditions->setStyleSheet(buttonStyleSheet);
	//resetConditions->setText("Reset Conditions");
	//resetConditions->setFont(moduleDescriptionFont);
	//resetConditions->setFixedSize(130, 30);
	//resetConditions->setDisabled(true);
	//resetConditions->setContentsMargins(0, 0, 0, 0);

	
	spinboxChildLayout = new QGridLayout();
	spinboxChildLayout->setSpacing(4);
	spinboxChildLayout->addWidget(lossSpinBox, 0, 0, Qt::AlignCenter);
	spinboxChildLayout->addWidget(junkSpinBox, 0, 1, Qt::AlignCenter);
	spinboxChildLayout->addWidget(delaySpinBox, 1, 0, Qt::AlignCenter);
	spinboxChildLayout->addWidget(tcpResetSpinBox, 1, 1, Qt::AlignCenter);

	conditionsLayout = new QGridLayout();
	conditionsLayout->setHorizontalSpacing(20);
	//conditionsLayout->setColumnMinimumWidth(1, 146);
	//conditionsLayout->setColumnMinimumWidth(2, 146);
	conditionsLayout->addWidget(conditionsDescriptionLabel, 1, 1, 1, 2, Qt::AlignCenter);
	conditionsLayout->addWidget(randomizeConditions, 2, 1, 2, 1, Qt::AlignCenter);	
	conditionsLayout->addItem(spinboxChildLayout, 2, 2, 1, 1, Qt::AlignCenter);


	connect(randomizeConditions, &QPushButton::clicked, this, &UiTamperConditions::onRandomizeConditionsClicked);
	connect(lossSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UiTamperConditions::onLossSpinBoxChange);
	connect(junkSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UiTamperConditions::onJunkSpinBoxChange);
	connect(delaySpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UiTamperConditions::onDelaySpinBoxChange);
	connect(tcpResetSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &UiTamperConditions::onResetSpinBoxChange);


	moduleLayout->addLayout(conditionsLayout);
}

UiTamperConditions::~UiTamperConditions()
{

}
void UiTamperConditions::toggleState(bool active)
{
	if (active)
	{
		conditionsDescriptionLabel->setPalette(moduleTextPaletteActive);
		
		onRandomizeConditionsClicked();
	}
	else
	{
		conditionsDescriptionLabel->setPalette(moduleTextPaletteInactive);

		lossSpinBox->setValue(0);
		delaySpinBox->setValue(0);
		junkSpinBox->setValue(0);
		tcpResetSpinBox->setValue(0);
	}
}


void UiTamperConditions::onRandomizeConditionsClicked()
{
	if (!selected)
	{
		emit tamperButtonClicked(this, pTamperConfig);
		return;
	}

	srand(time(nullptr));
	lossSpinBox->setValue(rand() % 30);
	junkSpinBox->setValue(rand() % 30);
	delaySpinBox->setValue(rand() % 100);
	tcpResetSpinBox->setValue(rand() % 20);
}

void UiTamperConditions::onLossSpinBoxChange(int value)
{
	((TamperConditionsConfig*)pTamperConfig)->chanceLoss = value;
}

void UiTamperConditions::onJunkSpinBoxChange(int value)
{
	((TamperConditionsConfig*)pTamperConfig)->chanceCorrupt = value;
}

void UiTamperConditions::onDelaySpinBoxChange(int value)
{
	((TamperConditionsConfig*)pTamperConfig)->chanceDelay = value;
}

void UiTamperConditions::onResetSpinBoxChange(int value)
{
	((TamperConditionsConfig*)pTamperConfig)->chanceReset = value;
}
